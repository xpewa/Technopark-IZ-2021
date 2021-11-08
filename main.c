#include <stdio.h>
#include <malloc.h>
#include "lib.h"

int main(void) {
  size_t count_records = 0;
  printf("Enter count of records: \n");
  if (scanf("%zu", &count_records) != 1) {
    printf("Value entered incorrectly!\n");
    return 1;
  }

  int* records = NULL;
  if (count_records > 0)
    records = (int*) malloc(count_records * sizeof(int));

  printf("Enter ECG records: \n");
  for (int i = 0; i < count_records; ++i)
    if (scanf("%d", &records[i]) != 1) {
        printf("Value entered incorrectly!\n");
        free(records);
        return 1;
    }

  size_t R_window = 1;
  printf("Enter R_window: \n");
  if (R_window < 1 || scanf("%zu", &R_window) != 1)  {
    printf("Value entered incorrectly!\n");
    free(records);
    return 1;
  }

  size_t count_R_peaks = countRPeaks(records, count_records, R_window);
  printf("Count of R-peaks = %zu \n", count_R_peaks);

  free(records);
  return 0;
}
