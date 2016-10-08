#include "environment.h"
using namespace std;

Environment::Environment()
{
    this->frames = vector<Frame*>();
}

Environment::Environment(vector<Frame*> frames)
{
    this->frames = frames;
}

string Environment::toString()
{
    return "Environment";
}
