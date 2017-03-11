#ifndef ASSERTION_H
#define ASSERTION_H
#include <vector>
#include <iostream>

template <typename T> void assert_elements(std::vector<T> v, int count)
{
    if (v.size() != count) {
        cout << "Need " << count << " elements" << endl;
        exit(1);
    }
}

#endif
