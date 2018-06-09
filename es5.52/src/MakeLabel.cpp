#include "make_label.h"

Symbol* MakeLabel::next(string prefix) {
    counter++;
    return new Symbol(prefix + std::to_string(counter));
}

void MakeLabel::reset() {
    counter = 0;
}
