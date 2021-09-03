#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>



int main() {

    const static unsigned int size = 100;
    std::vector<std::vector<int> > foo (size);

    for (int i=0; i<size; i++) {
        for (int i=0; i<size; i++) {
            std::cout << std::to_string(foo[i][i]);
        }
    }

}