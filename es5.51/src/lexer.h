#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
using namespace std;

class Lexer {
    public:
        vector<string> tokenize(string input);
};

#endif
