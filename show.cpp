#include <stdio.h>
#include <iostream>
#include <diamondSquareAlgorithm.cpp>

// one day i will learn why this doesn't work
int main() {
  for (const auto row : props::terrain) {

      for (const int column : props::terrain[row]) {

        std::cout << props::terrain[row][column] << ' ';

      }

      std::cout << std::endl;
  }
}