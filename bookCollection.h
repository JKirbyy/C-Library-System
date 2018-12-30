#ifndef Book_Collection
#define Book_Collection

#include "librarystructures.h"

void listBooks();
void removeBook (int subjectIndex, int bookIndex);
void returnBook (int bookIndex, int studentIndex);
void borrowBook (int indexOne, int indexTwo, char username[]);
void addBook (struct book bookToAdd);
int searching (char subject[]);

#endif