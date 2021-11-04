#include "../include/lib_static.h"
#include <stdlib.h>

static uint32_t findPeakInRange(const int* array, const uint32_t size, const uint32_t begin, const uint32_t end) {
  int max = 0;
  uint32_t max_index = 0;
  for (uint32_t i = begin + 1;  i + 1 < end; ++i) {
    if (abs(array[i]) > abs(array[i-1]) && abs(array[i]) > abs(array[i+1])) {
      if (abs(array[i]) > max) {
        max = abs(array[i]);
        max_index = i;
      }
    }
  }
  if (begin == 0 && abs(array[0]) > abs(array[1])) {
    if (abs(array[0]) > max)
      return 0;
  }

  if (begin != 0) {
    if (abs(array[begin]) > abs(array[begin + 1]) &&
        abs(array[begin]) > abs(array[begin - 1])) {
      if (abs(array[begin]) > max)
        return begin;
    }
  }

  if (end == size) {
    if (abs(array[size - 1]) > abs(array[size - 2])) {
      if (abs(array[size - 1]) >  max)
        return size - 1;
    }
  }

  return max == 0 ? -1 : max_index;
}

uint32_t countRPeaks(const int* records, const uint32_t size, const uint16_t R_window) {
  if (records == NULL || size == 0) {
    return 0;
  }
  uint32_t count = 0;
  uint32_t start_interval = 0;
  while (start_interval < size) {
    uint32_t end_interval = start_interval + R_window < size ? start_interval + R_window : size;
    uint32_t peak = findPeakInRange(records, size, start_interval, end_interval);
    if (peak != -1) {
      start_interval = peak + R_window + 1;
      ++count;
    }
    else
      start_interval = end_interval;
  }
  return count;
}
