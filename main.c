#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include "lib_static.h"
#include <inttypes.h>

int main(void) {
  uint32_t count_records = 0;
  printf("Enter count of records: \n");
  scanf("%" SCNu32, &count_records);

  int* records = (int*) malloc(count_records * sizeof(int));

  printf("Enter ECG records: \n");
  for (int i = 0; i < count_records; ++i)
    scanf("%d", &records[i]);

  uint16_t R_window = 0;
  printf("Enter R_window: \n");
  while (R_window < 1)
    scanf("%" SCNu16, &R_window);

  uint32_t count_R_peaks = countRPeaks(records, count_records, R_window);
  printf("Count of R-peaks = %" PRIu32 "\n", count_R_peaks);

  free(records);
  return 0;
}
