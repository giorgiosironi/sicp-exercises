#include "lexer.h"
#include <iostream>
using namespace std;

vector<string> Lexer::tokenize(string input)
{
    for (string::iterator it = input.begin(); it != input.end(); ++it) {
        cout << *it << endl;
    }
    return vector<string>({ input });
}
