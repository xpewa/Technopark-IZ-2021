#include "test_stress_static.h"
#include "lib.h"

size_t countRPeaksStatic(const int* records, const size_t size, const size_t R_window) {
  return countRPeaks(records, size, R_window);
}
