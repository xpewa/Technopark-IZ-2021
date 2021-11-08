#include <ctime>
#include <iostream>

extern "C" {
  #include <malloc.h>
  #include "test_stress_static.h"
  #include "test_stress_shared.h"
}

#define SIZE 100000000
#define REPEAT 10

int main() {
  int* records = (int*) malloc(SIZE * sizeof(int));
  for (size_t i = 0; i < SIZE; ++i) {
    records[i] = i % 2 == 0 ? 1 : 2;
  }

  double time_static = 0;
  double time_shared = 0;

  size_t count_static;
  size_t count_shared;

  for (int i = 0; i < REPEAT; ++i) {
    clock_t begin_static = clock();
    count_static = countRPeaksStatic(records, SIZE, 1);
    clock_t end_static = clock();

    time_static += (double) (end_static - begin_static) / CLOCKS_PER_SEC;

    clock_t begin_shared = clock();
    count_shared = countRPeaksShared(records, SIZE, 1);
    clock_t end_shared = clock();

    time_shared += (double) (end_shared - begin_shared) / CLOCKS_PER_SEC;
  }
  if (count_static == count_shared && count_static == SIZE / 2) {
    std::cout << "OK" << std::endl;
    std::cout << time_static / REPEAT << std::endl;
    std::cout << time_shared / REPEAT << std::endl;
  }
  else {
    std::cout << "TEST ERROR" << std::endl;
  }

  free(records);
  return 0;
}