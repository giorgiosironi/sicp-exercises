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
    for (int i = 0; i < length; i++) {
        char c = input.at(i);
        cout << "Character: " << c << endl;
        if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
            continue;
        }

        string atom = "";
        char next = c;
        do {
            atom += next;
            if (length > i + 1) {
                next = input.at(i+1);
            } else {
                next = 0;
            }
        } while (0 != next && nonAtom.find(next) == nonAtom.end() && ++i);
        tokens.push_back(atom);
    }
    return tokens;
    return vector<string>({ input });
}
