#include "lib_static.h"
#include <stdlib.h>

size_t countRPeaks(const int* records, const size_t size, const size_t R_window) {
  if (records == NULL || size == 0) {
    return 0;
  }
  size_t  count = 0;
  size_t  i = 1;
  if (abs(records[0]) > abs(records[1])) {
    ++count;
    i = R_window + 1;
  }
  while (i < size) {
    if (i == size - 1) {
      if (abs(records[i]) > abs(records[i-1])) {
        ++count;
        break;
      }
    }
    if (abs(records[i]) > abs(records[i-1]) && abs(records[i]) > abs(records[i+1])) {
        ++count;
        i += R_window + 1;
    }
    else {
      ++i;
    }
  }
  return count;
}
