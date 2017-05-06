#include "lexer.h"
#include <iostream>
using namespace std;

// https://igor.io/2012/12/07/sexpr-lexer.html
vector<string> Lexer::tokenize(string input)
{
    for (string::iterator it = input.begin(); it != input.end(); ++it) {
        cout << *it << endl;
    }
    return vector<string>({ input });
}
