#include <vector>
#include <iostream>
#include "alloc.cpp"

using namespace std;

int main() {
    for (size_t i = 0; i < 66; ++i) {
        cout << i << " -> " << align(i) << '\n';
    }
}
