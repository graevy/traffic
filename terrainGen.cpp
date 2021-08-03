#include <stdlib.h>
#include <math.h> // included purely for round(). is there a syntax for including a single function?


int* main(int n) {
  int dimension = (int) pow(2, n) + 1;
  int arr[dimension][dimension];
  diamondSquare(arr, n);
  return *arr;
}

// populates the entire array
void diamondSquare(int Array[][], int size)
{
 int CHUNK_X = sizeof(Array[0][0]);
 int CHUNK_Z = sizeof(Array[0]);
 int half = size / 2;

 // base case
 if (half < 1)
  return;
  
 // square steps
 for (int z = half; z < CHUNK_Z; z+=size)
  for (int x = half; x < CHUNK_X; x+=size)
   squareStep(Array, x % CHUNK_X, z % CHUNK_Z, half);
   
 // diamond steps
 int col = 0;
 for (int x = 0; x < CHUNK_X; x += half)
 {
  col++;
  // odd columns
  if (col % 2 == 1)
   for (int z = half; z < CHUNK_Z; z += size)
    diamondStep(Array, x % CHUNK_X, z % CHUNK_Z, half);
  // evens
  else
   for (int z = 0; z < CHUNK_Z; z += size)
    diamondStep(Array, x % CHUNK_X, z % CHUNK_Z, half);
 }

 // recursive call
 diamondSquare(Array, size / 2);
}

void squareStep(int Array[][], int x, int z, int reach)
{
 int CHUNK_X = sizeof(Array[0][0]);
 int CHUNK_Z = sizeof(Array[0]);

 int count = 0;
 float avg = 0.0f;
 if (x - reach >= 0 && z - reach >= 0)
 {
  avg += Array[x-reach][z-reach];
  count++;
 }
 if (x - reach >= 0 && z + reach < CHUNK_Z)
 {
  avg += Array[x-reach][z+reach];
  count++;
 }
 if (x + reach < CHUNK_X && z - reach >= 0)
 {
  avg += Array[x+reach][z-reach];
  count++;
 }
 if (x + reach < CHUNK_X && z + reach < CHUNK_Z)
 {
  avg += Array[x+reach][z+reach];
  count++;
 }
 avg += random(reach);
 avg /= count;
 Array[x][z] = round(avg);
}

void diamondStep(int Array[][], int x, int z, int reach)
{
 int CHUNK_X = sizeof(Array[0][0]);
 int CHUNK_Z = sizeof(Array[0]);

 int count = 0;
 float avg = 0.0f;
 if (x - reach >= 0)
 {
  avg += Array[x-reach][z];
  count++;
 }
 if (x + reach < CHUNK_X)
 {
  avg += Array[x+reach][z];
  count++;
 }
 if (z - reach >= 0)
 {
  avg += Array[x][z-reach];
  count++;
 }
 if (z + reach < CHUNK_Z)
 {
  avg += Array[x][z+reach];
  count++;
 } avg += random(reach);
 avg /= count;
 Array[x][z] = (int)avg;
}

inline static float random(int range)
{
 return (rand() % (range * 2)) - range;
}