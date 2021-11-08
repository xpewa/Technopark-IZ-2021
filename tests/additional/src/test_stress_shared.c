#include "test_stress_shared.h"
#include "lib.h"

size_t countRPeaksShared(const int* records, const size_t size, const size_t R_window) {
  return countRPeaks(records, size, R_window);
}
