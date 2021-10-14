#include <stdio.h>
#include <malloc.h>
#include "books.h"

int continue_scan() {
  char c = " ";
  printf("Do you want to add else one book? Enter y or n.\n");
  while (scanf("%c", &c) != 1 || c != 'y' && c != 'n');
  if (c == 'y') {
    return SUCCESS;
  }
  return ERROR;
}

int scan_book(t_book* book) {
  return scanf("%s%s%d%d%d",
               book->ISBN,
               book->tile,
               &book->year_publishing,
               &book->count,
               &book->count_readers);
}

int scan_reader(t_reader* reader) {
  return scanf("%25s%d%d%d",
               reader->surname,
               &reader->date[0],
               &reader->date[1],
               &reader->date[2]);
}

int scan_books(t_library* library) {
  while (continue_scan() == SUCCESS) {
    t_book* book = (t_book*)calloc(1, sizeof(t_book));
    if (book == NULL) {
      return ERROR_MEMORY;
    }
    printf("ISBN: XXX-X-XXXXXX-XX-X "
           "Title\n"
           "Year of publishing\n"
           "Count of book\n"
           "Count of readers\n");
    if (scan_book(book) != COUNT_PARAMETERS_OF_BOOK) {
      printf("Re-enter, please.\n");
      continue;
    }
    if (validate_book(book) != SUCCESS) {
      printf("Validate error. Re-enter.\n");
      continue;
    }
    if (book->count_readers == 0) {
      book->readers = NULL;
    } else {
      book->readers = (t_reader*)calloc(book->count_readers, sizeof(t_reader));
      if (book->readers == NULL) {
        return ERROR_MEMORY;
      }
    }
    for (int i = 0; i < book->count_readers; ++i) {
      printf("Surname\n"
             "day month year\n");
      while (scan_reader(book->readers + i) != COUNT_PARAMETERS_OF_READER) {
        printf("Re-enter, please\n");
      }
      if (validate_reader(book->readers + i) != SUCCESS) {
        printf("Validate error. Re-enter\n");
        --i;
        continue;
      }
    }
    book->next = NULL;
    push_book(library, book);
  }
  return SUCCESS;
}

int main(void) {
  t_library* library = create_library();
  int res = scan_books(library);
  if (res == ERROR_MEMORY) {
    printf("Memory error.");
    free_library(library);
    return 0;
  }
  int c_readers = count_readers(library);
  printf("Count of readers: %d\n", c_readers);
  t_book* reader_books = books_on_hands(library);
  if (reader_books != NULL) {
    printf("Codes of the books taken:\n");
    for (int i = 0; i < c_readers; ++i) {
      printf("%17s\n", reader_books[i].ISBN);
    }
    free(reader_books);
  }

  free_library(library);
  return 0;
}