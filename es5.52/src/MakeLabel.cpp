#include "make_label.h"

Symbol* MakeLabel::next(string prefix) {
    counter++;
    return new Symbol(prefix + std::to_string(counter));
}

void MakeLabel::reset() {
    counter = 0;
}

int MakeLabel::current() {
    return counter;
}

void reset_labels() {
	make_label.reset();
}

MakeLabel make_label;
