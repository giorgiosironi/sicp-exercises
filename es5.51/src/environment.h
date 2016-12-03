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
        virtual std::string toString();
};

#endif
