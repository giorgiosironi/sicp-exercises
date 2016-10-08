#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <vector>
#include "frame.h"
using namespace std;

class Environment {
    private:
        vector<Frame*> frames;
    public:
        Environment(vector<Frame*> frames);
};

#endif
