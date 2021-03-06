#include "lexer.h"
#include <set>
using namespace std;

// https://igor.io/2012/12/07/sexpr-lexer.html
vector<string> Lexer::tokenize(string input)
{
    auto whitespace = set<char>({ ' ', '\n' });
    auto nonAtom = set<char>({ '(', ')', ' ', '\n' });

    auto tokens = vector<string>({});
    int length = input.size();
    for (int i = 0; i < length; i++) {
        char c = input.at(i);

        if (whitespace.find(c) != whitespace.end()) {
            continue;
        }

        if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
            continue;
        }

        if (c == '\'') {
            tokens.push_back(string(1, c));
            continue;
        }

        // TODO: support escapings like \"
        if (c == '"') {
            string thestring = "";
            char next = c;
            do {
                thestring += next;
                if (length > i + 1) {
                    next = input.at(i+1);
                } else {
                    next = 0;
                }
            } while (0 != next && next != '"' && ++i);
            thestring += next;
            ++i;
            tokens.push_back(thestring);
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
}
