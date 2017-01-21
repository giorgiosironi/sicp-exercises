#include <iostream>
#include <string>
#include <ctype.h>
#include <boost/regex.hpp>
#include "read.h"
#include "symbol.h"
#include "integer.h"
#include "string.h"
#include "nil.h"
#include "cons.h"
using namespace std;


Value* Read::execute(std::vector<Value*> elements)
{
    std::string input;
    getline(cin, input);

    return this->parse(input);
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
	for(char& c : input) {
		cout << "Read: " << c << endl;
    //    if char == '(' and not in_str:
    //        sexp.append([])
		if (c == '(' && !in_str) {
			sexp.push_back(new Nil());
    //    elif char == ')' and not in_str:
		} else if (c == ')' && !in_str) {
    //        if word:
			if (!word.empty()) {
    //            sexp[-1].append(word)
    //            word = ''
				int last_element = sexp.size() - 1;
				/*
				if sexp[last_element] is nil:
					substitute with new cons
                */
				if (sexp[last_element]->toString() == "NIL") {
                    sexp[last_element] = new Cons(new String(word), new Nil());
                /*
				else:
					append as last element
				*/
				} else {
                    Cons* current_list = dynamic_cast<Cons *>(sexp[last_element]);
                    current_list->append(new String(word));
                    sexp[last_element] = current_list;
				}
				word = "";
            }
        //        temp = sexp.pop()
            int last_element = sexp.size() - 1;
            Value* temp = sexp[last_element];
            sexp.pop_back();
        //        sexp[-1].append(temp)
			if (sexp[last_element]->toString() == "NIL") {
				sexp[last_element] = new Cons(new String(word), new Nil());
			} else {
				Cons* current_list = dynamic_cast<Cons *>(sexp[last_element]);
				current_list->append(temp);
				sexp[last_element] = current_list;
			}
    //    elif char in (' ', '\n', '\t') and not in_str:
		} else if ((c == ' ' || c == '\n' || c == '\t') && !in_str) {
    //        if word:
            if (word != "") {
    //            sexp[-1].append(word)
                int last_element = sexp.size() - 1;
				Value* value = new String(word);
				boost::regex expr("[0-9]+");
				if (boost::regex_match(word, expr)) {
			  	    value = new Integer(stoi(input));
				}
				if (sexp[last_element]->toString() == "NIL") {
                    sexp[last_element] = new Cons(value, new Nil());
				} else {
					Cons* current_list = dynamic_cast<Cons *>(sexp[last_element]);
					current_list->append(value);
                    sexp[last_element] = current_list;
				}
    //            word = ''
                word = "";
            }
    //    elif char == '\"':
        } else if (c == '\"') {
    //        in_str = not in_str
            in_str = !in_str;
    //    else:
        } else {
    //        word += char
            word.push_back(c);
        }
	}
    Value* result = ((Cons*) sexp[0])->car();
    cout << "Result: " << result->toString() << endl;
	return result;
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

std::string Read::toString()
{
    return std::string("Operation-Read");
}

