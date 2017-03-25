#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <vector>
#include "frame.h"
using namespace std;

class Environment: public Value {
    private:
        vector<Frame*> frames;
    public:
        Environment();
        Environment(vector<Frame*> frames);
        Environment* extend(Frame* additionalFrame);
        Value* lookup(Symbol* symbol);
        Frame* firstFrame();
        void set(Symbol* symbol, Value* value);
        virtual std::string toString();
};

#endif
