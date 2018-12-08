#include <iostream>
#include "input.h"
#include "lexer.h"
#include "reader.h"
#include "length.h"
#include "input_end_exception.h"

std::vector<Value*> input()
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
    // superceded:
    //if (length(parsed) != 1) {
    //    throw std::length_error("Only one expression should be typed in at the repl. Got the list " + parsed->to_string() + " instead");
    //}
	return parsed->to_vector();
}
