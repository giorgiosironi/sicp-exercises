#include "lexer.h"
#include <iostream>
#include <typeinfo>
#include <set>
using namespace std;

// https://igor.io/2012/12/07/sexpr-lexer.html
vector<string> Lexer::tokenize(string input)
{
    auto nonAtom = set<char>({ '(', ')', ' ', });
    auto tokens = vector<string>({});
    int length = input.size();
    int i = 0;
    for (string::iterator it = input.begin(); it != input.end(); ++it) {
        char c = *it;
        if (*it == '(' || *it == ')') {
            tokens.push_back(string(1, c));
            continue;
        }

        string atom = "";
        char next = c;
        do {
            atom += next;
            if (length > i + 1) {
                next = input.at(i+1);
                ++it;
                ++i;
            } else {
                next = 0;
            }
        } while (0 != next && nonAtom.find(next) == nonAtom.end());
        tokens.push_back(atom);
    }
    return tokens;
    return vector<string>({ input });
}
