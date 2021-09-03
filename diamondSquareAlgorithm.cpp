#include <stdlib.h>
#include <vector>
#include <stdexcept>

namespace props {

  const static unsigned int side = 5;
  // for indexing
  const static unsigned int max = side-1;
  const static unsigned int maxHeight = 255;
  unsigned int validNeighbors = 4;

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
  // the recursion
  // it divides into half-sized chunks until it can't

  int half = size >> 2; // integer division by 2

  if (half < 1) {
    return;
  }

  // i haven't tested these and i'm new to c++ looping

  // horiz = horizontal, vert = vertical
  // square steps
  for(int horiz = half; horiz < props::max; horiz = horiz + size) {
    for(int vert = half; vert < props::max; vert = vert + size) {
      square(horiz, vert, half);
    }
  }
  // diamond steps
  for(int horiz = 0; horiz < props::side; horiz = horiz + half) {
    for(int vert = half + half % size; props::side; vert = vert + size) {
      diamond(horiz, vert, half);
    }
  }

  divide(size);
}
