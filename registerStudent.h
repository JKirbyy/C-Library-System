#ifndef Register_Student
#define Register_Student

#include "librarystructures.h"

int validateUsername(char username[]);
int validatePassword(char password[]);
int passwordHash(char password[]);
void listStudents();
int login(char username[], char password[]);
void registerStud();
int search (char username[]);
int listBorrowedBooks (int index);

int collisionHandlingStudent (int hashValue, struct student studentToAdd);
#endif
