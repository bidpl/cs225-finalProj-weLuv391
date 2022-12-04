/* Binh-Minh's (bmn4) code for CS225 mp_mazes, pseudo code from lecture slides */
#include "dsets.h"
#include <stdexcept>

void DisjointSets::addelements(int num) {
    elems_.insert(elems_.end(), num, -1);
}


int DisjointSets::find(int elem) {
    if(elem < 0 || (unsigned) elem >= elems_.size()) {
        throw std::out_of_range("DisjointSets:find: out of bounds index " + std::to_string(elem));
    }

    if(elems_[elem] < 0) {
        return elem;
    }

    // Path compression
    int root = find(elems_[elem]);
    elems_[elem] = root;
    return root;
}


void DisjointSets::setunion(int a, int b) {
    // Union by rank
    a = find(a);
    b = find(b);

    // If in same set do nothing
    if(a == b) {
        return;
    }

    // Else merger smaller tree into bigger tree
    if(elems_[b] < elems_[a]) {
        elems_[b] += elems_[a];
        elems_[a] = b;
    } else {
        // equal tie break left arg
        elems_[a] += elems_[b];
        elems_[b] = a;
    }
}


int DisjointSets::size(int elem) {
    return -1*elems_[find(elem)];
}

