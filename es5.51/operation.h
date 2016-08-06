#ifndef OPERATION_H
#define OPERATION_H

class Operation: public Value {
    public:
        virtual Value* execute(std::vector<Value*> elements) = 0;
};

#endif
