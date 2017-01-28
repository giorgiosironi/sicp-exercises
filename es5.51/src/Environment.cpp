#include "environment.h"
#include <iostream>
using namespace std;

Environment::Environment()
{
    this->frames = vector<Frame*>();
}

Environment::Environment(vector<Frame*> frames)
{
    this->frames = frames;
}

Value* Environment::lookup(Symbol* symbol)
{
    for (int i = this->frames.size() - 1; i >= 0; i--) {
        auto frameResult = this->frames.at(i)->lookup(symbol);
        if (frameResult != NULL) {
            return frameResult;
        }
    }
    return NULL;
}

Environment* Environment::extend(Frame* additionalFrame)
{
    auto frames = this->frames;
    frames.push_back(additionalFrame);
    return new Environment(frames);
}

string Environment::toString()
{
    return "Environment";
}
