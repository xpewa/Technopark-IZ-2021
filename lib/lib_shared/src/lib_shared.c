#include "lib.h"

#define _GNU_SOURSE

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

void static findLocalMax(const int* records, size_t size, size_t* shared_memory,
                         size_t size_column, size_t process_number, size_t count_processes) {
  size_t part_begin = process_number == 0 ? 1 : (size / count_processes) * process_number;
  size_t part_end = process_number == count_processes - 1 ? size - 1 : (size / count_processes) * (process_number + 1);
  if (process_number == 0 && abs(records[0]) > abs(records[1])) {
    ++(*(shared_memory + 0 * size_column + 0));
    *(shared_memory + 0 * size_column + 1) = 1;
  }
  for (size_t i = part_begin; i < part_end; ++i) {
    if (abs(records[i]) > abs(records[i-1]) && abs(records[i]) > abs(records[i+1])) {
      ++(*(shared_memory + (process_number) * size_column + 0));
      size_t size_local_max = *(shared_memory + (process_number) * size_column + 0);
      *(shared_memory + (process_number) * size_column + size_local_max) = i;
    }
  }
  if (process_number == count_processes - 1 && abs(records[size - 1]) > abs(records[size - 2])) {
    ++(*(shared_memory + (count_processes - 1) * size_column + 0));
    size_t size_local_max = *(shared_memory + (count_processes - 1) * size_column + 0);
    *(shared_memory + (count_processes - 1) * size_column  + size_local_max) = size - 1;
  }
}

size_t static countLocalMax(const size_t* shared_memory, size_t size_column, size_t count_processes, size_t R_window) {
  size_t count = 0;
  size_t last_max = - R_window - 1;
  for (int i = 0; i < count_processes; ++i) {
    size_t size_local_max = *(shared_memory + i * size_column + 0);
    for (int j = 1; j < size_local_max + 1; ++j) {
      if (*(shared_memory + i * size_column + j) >= (last_max + R_window + 1)) {
        last_max = *(shared_memory + i * size_column + j);
        ++count;
      }
    }
  }
  return count;
}

size_t countRPeaks(const int* records, size_t size, size_t R_window) {
  if (records == NULL || size == 0) {
    return 0;
  }
  size_t count_processes = sysconf(_SC_NPROCESSORS_ONLN); //количество доступных процессоров

  pid_t pids[count_processes];

  size_t size_column = size / 2 + 1;
  size_t* shared_memory = mmap(NULL, size_column * count_processes * sizeof(size_t),
                            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
  if (shared_memory == MAP_FAILED) {
    return 0;
  }

  for (size_t i = 0; i < count_processes; ++i) {
    pids[i] = fork();
    if (pids[i] == 0) {
      findLocalMax(records, size, shared_memory, size_column, i, count_processes);

      exit(EXIT_SUCCESS);
    }
  }

  int status;
  for (size_t i = 0; i < count_processes; ++i) {
    if (waitpid(pids[i], &status, 0) != pids[i]) {
      return 0;
    }
  }

  for (int i = 0; i < count_processes; ++i) {
    for (int j = 0; j < *(shared_memory + i * size_column + 0); ++j) {
    }
  }

  size_t count = countLocalMax(shared_memory, size_column, count_processes, R_window);

  if (munmap(shared_memory, size_column * count_processes * sizeof(size_t)) != 0) {
    return 0;
  }

  return count;
}
