#include "reader.h"
#include "symbol.h"
#include "cons.h"
#include "nil.h"
#include <iostream>
using namespace std;

// https://igor.io/2012/12/08/sexpr-reader.html
Value* Reader::parse(vector<string> input)
{
	auto ast = vector<Value*>();

    for (int i = 0; i < input.size(); ++i) {
		auto token = input.at(i);

        if ("(" != token && ")" != token) {
            // extract atoms
            ast.push_back(new Symbol(token));
			//$ast[] = $this->normalizeAtom($token);
            continue;
        }

		if ("(" == token) {
			// parse list recursively
			auto temp = this->extract_list_tokens(input, i);
			auto list_tokens = get<0>(temp);
			i = get<1>(temp);
			ast.push_back(this->parse(list_tokens));	
			continue;
		}
    }

    return Cons::from_vector(ast);
}

tuple<vector<string>,int> Reader::extract_list_tokens(vector<string> tokens, int i)
{
	int level = 0;
	int init = i;

	for (int length = tokens.size(); i < length; i++) {
		string token = tokens.at(i);
		
		if ("(" == token) {
			level++;
		}

		if (")" == token) {
			level--;
		}

	    if (0 == level) {
            // TODO: prellocate capacity of slice
            auto slice = vector<string>();
            for (int j = init + 1; j < i; j++) {
                slice.push_back(tokens.at(j));
            }
            return make_tuple(
                slice, 
                i
            );
        }
	}
}
