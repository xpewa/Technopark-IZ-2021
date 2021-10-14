#include "books.h"
#include <stdio.h>
#include <malloc.h>

int count_readers(t_library* library) {
    int count = 0;
    t_book* tmp = library->book_head;
    while (tmp != NULL) {
        count += tmp->count_readers;
        tmp = tmp->next;
    }
    return count;
}

t_book* books_on_hands(t_library* library) {
    if (library->book_head == NULL || count_readers(library) == 0) {
        return NULL;
    }
    t_book* res = (t_book*)calloc(count_readers(library), sizeof(t_book));
    t_book* tmp = library->book_head;
    int i = 0;
    while (tmp != NULL) {
        for (int j = 0; j < tmp->count_readers; ++j) {
            res[i] = *tmp;
            ++i;
        }
        tmp = tmp->next;
    }
    return res;
}

t_library* create_library() {
    t_library* library = (t_library*) calloc(1, sizeof(t_library));
    library->book_head = NULL;
    return library;
}

void push_book(t_library* library, t_book* book) {
    if (library->book_head == NULL) {
        library->book_head = book;
        return;
    }
    t_book* tmp = library->book_head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = book;
}

int static validate_isbn(const char* isbn) {
    for (int i = 0; i < 3; ++i) {
        if (isbn[i]-'0' < 0 || isbn[i]-'0' > 9) {
          return ERROR;
        }
    }
    if (isbn[3] != '-' || isbn[5] != '-' || isbn[12] != '-' || isbn[15] != '-') {
      return ERROR;
    }
    if (isbn[4]-'0' < 0 || isbn[4]-'0' > 9) {
      return ERROR;
    }
    for (int i = 6; i < 12; ++i) {
        if (isbn[i]-'0' < 0 || isbn[i]-'0' > 9) {
          return ERROR;
        }
    }
    for (int i = 13; i < 15; ++i) {
        if (isbn[i]-'0' < 0 || isbn[i]-'0' > 9) {
          return ERROR;
        }
    }
    if (isbn[16]-'0' < 0 || isbn[16]-'0' > 9) {
      return ERROR;
    }
    if (isbn[17] != '\0') {
      return ERROR;
    }
    return SUCCESS;
}

int validate_book(t_book* book) {
    if (validate_isbn(book->ISBN) == ERROR || book->count_readers < 0 || book->count < 0) {
      return ERROR;
    }
    return SUCCESS;
}

int validate_reader(t_reader* reader) {
    if (reader->date[0] < 1 || reader->date[0] > 31) {
      return ERROR;
    }
    if (reader->date[1] < 1 || reader->date[1] > 12) {
      return ERROR;
    }
    return SUCCESS;
}

void pop_book(t_library* library) {
    if (library->book_head == NULL) {
      return;
    }
    t_book* tmp = library->book_head;
    library->book_head = library->book_head->next;
    free(tmp->readers);
    free(tmp);
}

void free_library(t_library* library) {
    while (library->book_head != NULL) {
      pop_book(library);
    }
    free(library);
}