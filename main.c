#include <stdio.h>
#include <malloc.h>
#include "lib_static.h"

int main(void) {
  size_t count_records = 0;
  printf("Enter count of records: \n");
  scanf("%zu", &count_records);

  int* records = NULL;
  if (count_records > 0)
    records = (int*) malloc(count_records * sizeof(int));

  printf("Enter ECG records: \n");
  for (int i = 0; i < count_records; ++i)
    scanf("%d", &records[i]);

  size_t R_window = 0;
  printf("Enter R_window: \n");
  while (R_window < 1)
    scanf("%zu", &R_window);

  size_t count_R_peaks = countRPeaks(records, count_records, R_window);
  printf("Count of R-peaks = %zu \n", count_R_peaks);

  free(records);
  return 0;
}
