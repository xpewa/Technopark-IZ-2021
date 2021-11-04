#include <gtest/gtest.h>

extern "C" {
#include "lib_static.h"
}

TEST(test1, null_zero) {
  size_t  const count_records = 0;
  int* records = NULL;
  size_t  R_window = 1;

  size_t  count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 0);
}

TEST(test2, one_peak_one_window) {
  size_t  const count_records = 5;
  int records[count_records] = {1, 2, 3, 2, 1};
  size_t  R_window = 1;

  size_t  count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 1);
}

TEST(test3, peaks_at_begin_end) {
  size_t  const count_records = 10;
  int records[count_records] = {3, 2, 1, 0, -1, 5, 6, 7, 8, 9};
  size_t  R_window = 5;

  size_t  count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 2);
}

TEST(test4, skip_peak) {
  size_t  const count_records = 15;
  int records[count_records] = {1, 2, 1, 10, -1, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4};
  size_t  R_window = 5;

  size_t  count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 2);
}

TEST(test5, even_window) {
  size_t  const count_records = 10;
  int records[count_records] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
  size_t  R_window = 2;

  size_t  count_R_peaks = countRPeaks(records, count_records, R_window);

  EXPECT_EQ(count_R_peaks, 3);
}
