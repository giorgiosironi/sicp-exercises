#include "assertion.h"
#include <execinfo.h>
#include <iostream>
#define BT_BUF_SIZE 100
using namespace std;

void dump_stacktrace() {
    void *buffer[BT_BUF_SIZE];
    int nptrs;
    char **strings;
    nptrs = backtrace(buffer, BT_BUF_SIZE);
    cerr << "backtrace() returned " << nptrs << " addresses" << endl;
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < nptrs; j++) {
        printf("%s\n", strings[j]);
    }

    free(strings);
}
