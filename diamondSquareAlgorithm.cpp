#include <stdlib.h>
#include <vector>
#include <stdexcept>

namespace props {

  int side = 5;
  // for indexing
  int max = side-1;
  int maxHeight = 255;
  int validNeighbors = 4;

  // 2d vector 'terrain' with side*side dimensions, populated with zeroes
  // using vector instead of array because it has bounds checking
  // in the at() method. it might be faster to use an array
  // and if statements
  std::vector<std::vector<int> >
  terrain(
    side,
    std::vector<int>(side));
}

int main() {

  // set corners to random values
  props::terrain[0][0] =                    rand() % props::maxHeight;
  props::terrain[0][props::max] =           rand() % props::maxHeight;
  props::terrain[props::max][0] =           rand() % props::maxHeight;
  props::terrain[props::max][props::max] =  rand() % props::maxHeight;

  // begin recursion
  divide(props::side);
}

int attemptAccess(int x, int y) {
  try {
    return props::terrain.at(x).at(y);
  }
  
  catch (std::out_of_range& err) {
    props::validNeighbors--;
    return 0;
  }
}

void square(int x, int y, int size) {
  props::validNeighbors = 4;

  int topLeft = attemptAccess(x - size, y - size);
  int topRight = attemptAccess(x + size, y - size);
  int bottomLeft = attemptAccess(x + size, y + size);
  int bottomRight = attemptAccess(x - size, y + size);

  int average = (int)(
    (topLeft + topRight + bottomLeft + bottomRight) / props::validNeighbors
  );

  props::terrain[x][y] = average;
}

void diamond(int x, int y, int size) {
  props::validNeighbors = 4;

  int right = attemptAccess(x + size, y);
  int top = attemptAccess(x, y - size);
  int left = attemptAccess(x - size, y);
  int bottom = attemptAccess(x, y + size);

  int average = (int)(
    (top + right + left + bottom + left) / 4
  );

  props::terrain[x][y] = average;

}

void divide(int size) {
  // x and y are grid coordinates, but ultimately only
  // one var is necessary. it's just more readable this way
  int x = size >> 2;
  int y = x;
  int half = x;

  if (half < 1) {
    return;
  }

  // i haven't tested these and i'm new to c++ looping

  // square steps
  for(int i = half; i < props::max; i = i + size) {
    for(int i2 = half; i < props::max; i = i + size) {
      square(x, y, half);
    }
  }
  // diamond steps
  for(int i = 0; i < props::side; i = i + half) {
    for(int i = y + half % size; props::side; i = i + size) {
      diamond(x, y, half);
    }
  }

  divide(size);

}