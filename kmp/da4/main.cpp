/*
 * 1-2
 * KMP
 * [0; 2^32 - 1]
 */

#include <iostream>
#include <inttypes.h>

#include "tvector.h"
#include "tvector.cpp"  // Couse of template...

#define IS_INT(c) ((c) >= '0' && (c) <= '9')


bool IS_EOF = false;
inline uint32_t read_int() {
    int c;
    uint32_t res = 0;
    while ((c = getchar()) != EOF && IS_INT(c)) {
        res = res * 10 + (c - '0');
    }

    if (EOF == c) {
        IS_EOF = true;
    }

    return res;
}


inline void read_input(TVector<uint32_t> &inp) {
    uint32_t tmp;
    while (tmp = read_int(), !IS_EOF) {
        inp.PushBack(tmp);
    }
}

void sp(TVector p) {
    for (int i = 0; i < p.Size(); ++i) {

    }
}



int main() {
    TVector<uint32_t> data;
    read_input(data);
    for (unsigned int i = 0; i < data.Size(); ++i) {
        std::cout << data[i] << "\t";
    }
    return 0;
}
