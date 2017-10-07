#ifndef ANNOUNCE_OUTPUT_H
#define ANNOUNCE_OUTPUT_H
#include "operation.h"

class AnnounceOutput: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
