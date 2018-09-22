#include <iostream>
#include <string>
#include <ctype.h>
#include <boost/regex.hpp>
#include <stdexcept>
#include "read.h"
#include "symbol.h"
#include "integer.h"
#include "float.h"
#include "string.h"
#include "bool.h"
#include "nil.h"
#include "cons.h"
#include "lexer.h"
#include "reader.h"
#include "length.h"
#include "input_end_exception.h"
using namespace std;


Value* Read::execute(std::vector<Value*> elements)
{
    std::string input = "";
    while (input == "") {
        getline(cin, input);
        if (cin.eof() && input == "") {
            throw InputEndException();
        }
    }
	Lexer lexer;
	Reader reader;

    List* parsed = reader.parse(lexer.tokenize(input));
    if (length(parsed) != 1) {
        throw std::length_error("Only one expression should be typed in at the repl. Got the list " + parsed->to_string() + " instead");
    }
	return parsed->car();
}

Value* Read::parse(std::string input)
{
	// add a terminator
	input = input + "\n";
    //sexp = [[]]
	auto sexp = vector<Value*>();
	sexp.push_back(new Nil());
    //word = ''
	string word = "";
    //in_str = False
	bool in_str = false;
    //for char in string:
	for (char& c : input) {
		if (c == '(' && !in_str) {
			sexp.push_back(new Nil());
		} else if (c == ')' && !in_str) {
			if (!word.empty()) {
				int last_element = sexp.size() - 1;
                this->append_to_last_element(sexp, word);
				word = "";
            }
            int last_element = sexp.size() - 1;
            Value* temp = sexp[last_element];
            sexp.pop_back();
            this->append_to_last_element(sexp, temp);
		} else if ((c == ' ' || c == '\n' || c == '\t') && !in_str) {
            if (word != "") {
				this->append_to_last_element(sexp, word);
                word = "";
            }
        } else if (c == '\"') {
			word.push_back('\"');
            in_str = !in_str;
        } else {
            word.push_back(c);
        }
	}
    Value* result = ((Cons*) sexp[0])->car();
	return result;
}

void Read::append_to_last_element(std::vector<Value*> &sexp, std::string word)
{
    this->append_to_last_element(sexp, this->to_value(word));
}

Value* Read::to_value(std::string word)
{
    cerr << "[e] " << "Read::to_value " << word << endl;
    // by default, a symbol
	Value* value = new Symbol(word);
	boost::smatch what;

    if (word == "#t") {
        value = new Bool(true);
    } else if (word == "#f") {
        value = new Bool(false);
    }

    // an integer
	boost::regex int_expr("[0-9]+");
	if (boost::regex_match(word, int_expr)) {
		value = new Integer(stoi(word));
	}

    // a float
	boost::regex float_expr("[0-9]+\\.[0-9]+");
	if (boost::regex_match(word, float_expr)) {
		value = new Float(stof(word));
    }

    // a string
	boost::regex string_expr("\"(.*)\"");
	if (boost::regex_match(word, what, string_expr)) {
		value = new String(what[1]);
	}

    // quoted expression
	boost::regex quoted_expr("'(.*)");
	if (boost::regex_match(word, what, quoted_expr)) {
		value = Cons::from_vector({
            new Symbol("quote"),
            this->to_value(what[1])
        });
	}

    return value;
}

void Read::append_to_last_element(std::vector<Value*> &sexp, Value* value)
{
	int last_element = sexp.size() - 1;
	if (*sexp[last_element] == *NIL) {
		sexp[last_element] = new Cons(value, new Nil());
	} else {
		Cons* current_list = dynamic_cast<Cons *>(sexp[last_element]);
		current_list = current_list->append(value);
		sexp[last_element] = current_list;
	}
}

/*
 *
https://en.wikipedia.org/wiki/S-expression#Parsing
def parse_sexp(string):
    """
    >>> parse_sexp("(+ 5 (+ 3 5))")
    [['+', '5', ['+', '3', '5']]]
    
    """
    sexp = [[]]
    word = ''
    in_str = False
    for char in string:
        if char == '(' and not in_str:
            sexp.append([])
        elif char == ')' and not in_str:
            if word:
                sexp[-1].append(word)
                word = ''
            temp = sexp.pop()
            sexp[-1].append(temp)
        elif char in (' ', '\n', '\t') and not in_str:
            if word:
                sexp[-1].append(word)
                word = ''
        elif char == '\"':
            in_str = not in_str
        else:
            word += char
    return sexp[0]
*/

std::string Read::to_string() const
{
    return std::string("Operation-Read");
}

