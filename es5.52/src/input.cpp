#include <iostream>
#include "input.h"
#include "lexer.h"
#include "reader.h"
#include "length.h"
#include "input_end_exception.h"

std::vector<Value*> input()
{
    std::string input = "";
    std::string input_line = "";
    //while (input == "") {
    while (!cin.eof()) {
        // TODO: this is overwriting input at each cycle
        getline(cin, input_line);
        input = input + input_line;
        cout << "input" << input << endl;
        if (cin.eof() && input_line == "") {
            throw InputEndException();
        }
    }
	Lexer lexer;
	Reader reader;

    List* parsed = reader.parse(lexer.tokenize(input));
    cout << "parsed: " << parsed->to_string() << endl;
    // superceded:
    //if (length(parsed) != 1) {
    //    throw std::length_error("Only one expression should be typed in at the repl. Got the list " + parsed->to_string() + " instead");
    //}
	return parsed->to_vector();
}
