#include "environment.h"
#include "frame.h"
#include <iostream>
using namespace std;

Environment::Environment()
{
    this->frames = vector<Frame*>();
    this->frames.push_back(new Frame());
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

void Environment::set(Symbol* symbol, Value* value)
{
    for (int i = this->frames.size() - 1; i >= 0; i--) {
        auto frameResult = this->frames.at(i)->lookup(symbol);
        if (frameResult != NULL) {
            this->frames.at(i)->set(symbol, value);
            return;
        }
    }
    this->frames[this->frames.size() - 1]->set(symbol, value);
    return;
}

Frame* Environment::firstFrame()
{
    return this->frames[this->frames.size() - 1];
}

string Environment::toString()
{
    return "Environment";
}
