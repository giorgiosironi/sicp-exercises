#include <iostream>
#include <string>
#include <ctype.h>
#include <boost/regex.hpp>
#include "read.h"
#include "symbol.h"
#include "integer.h"
#include "nil.h"
using namespace std;


Value* Read::execute(std::vector<Value*> elements)
{
    std::string input;
    getline(cin, input);

    return this->parse(input);
}

Value* Read::parse(std::string input)
{
    //sexp = [[]]
	auto sexp = vector<Value*>();
	sexp.push_back(new Nil());
    //word = ''
    //in_str = False
    //for char in string:
    //    if char == '(' and not in_str:
    //        sexp.append([])
    //    elif char == ')' and not in_str:
    //        if word:
    //            sexp[-1].append(word)
    //            word = ''
    //        temp = sexp.pop()
    //        sexp[-1].append(temp)
    //    elif char in (' ', '\n', '\t') and not in_str:
    //        if word:
    //            sexp[-1].append(word)
    //            word = ''
    //    elif char == '\"':
    //        in_str = not in_str
    //    else:
    //        word += char
    //return sexp[0]

    boost::regex expr("[0-9]+");
    if (boost::regex_match(input, expr)) {
        return new Integer(stoi(input));
    }
    return new Symbol(input);
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

