#ifndef IS_INSTANCE_OF_H
#define IS_INSTANCE_OF_H
#include "operation.h"
#include "bool.h"
// note: the easier way to implement templates is to put everything into 
// the header file

template<class T>
class IsInstanceOf: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

template <class T>
Value* IsInstanceOf<T>::execute(std::vector<Value*> elements)
{
    T* casted = dynamic_cast<T *>(elements[0]);
    if (casted != NULL) {
        return new Bool(true);
    } else {
        return new Bool(false);
    }
}

template <class T>
std::string IsInstanceOf<T>::to_string() const
{
    // TODO: output type "name"
    return "IsInstanceOf<T>";
}

#endif
