#include <iostream>
#include <fstream>
#include "input.h"
#include "lexer.h"
#include "reader.h"
#include "length.h"
#include "input_end_exception.h"
using namespace std;

std::vector<Value*> input(string filename)
{
    ifstream ifs;
    ifs.open(filename);
    // https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
    string input(
        (istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>())
    );
    cout << "Input length: " << input.size() << endl;
    //std::string input_line = "";
    //while (input == "") {
    //while (!cin.eof()) {
    //    // TODO: this is overwriting input at each cycle
    //    getline(cin, input_line);
    //    input = input + input_line;
    //    //cout << "input: " << input << endl;
    //    if (cin.eof() && input_line == "") {
    //        break;
    //        //throw InputEndException();
    //    }
    //}
	Lexer lexer;
	Reader reader;

    List* parsed = reader.parse(lexer.tokenize(input));
    cout << "parsed: " << parsed->to_string() << endl;
	return parsed->to_vector();
}
