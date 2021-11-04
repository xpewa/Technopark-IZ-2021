#include <gtest/gtest.h>

extern "C" {
#include "lib_static.h"
}

TEST(null_array, count_zero) {
  uint32_t const count_records = 0;
  int* records = NULL;
  uint16_t R_window = 1;

  uint32_t count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 0);
}

TEST(small_array, count_one) {
  uint32_t const count_records = 5;
  int records[count_records] = {1, 2, 3, 2, 1};
  uint16_t R_window = 1;

  uint32_t count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 1);
}

TEST(small_array, count_two) {
  uint32_t const count_records = 10;
  int records[count_records] = {3, 2, 1, 0, -1, 5, 6, 7, 8, 9};
  uint16_t R_window = 5;

  uint32_t count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 2);
}

TEST(test3, count) {
  uint32_t const count_records = 15;
  int records[count_records] = {1, 2, 1, 10, -1, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4};
  uint16_t R_window = 5;

  uint32_t count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 2);
}
