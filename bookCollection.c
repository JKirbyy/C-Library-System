#include <stdio.h>
#include <string.h>
#include <math.h>
#include "librarystructures.h"
#include "hashthree.h"
#include "registerStudent.h"
#include "bookCollection.h"

void listBooks() /*lists every book in the array */
{
	for (int i=0; i <50; i++) 
	{
		if (bookCollection[i][0].added == 1)
		{
			int x = 0;
			while (bookCollection[i][x].added == 1)
			{
				printf("%s. Subject Code: %s\n", bookCollection[i][x].name, bookCollection[i][x].subject);
				x++;
			}
		}
	}
	
}

void removeBook (int subjectIndex, int bookIndex) /*removes a book from the array*/
{
	int startingIndex = bookIndex;
	
	while (bookCollection[subjectIndex][startingIndex + 1].added == 1) /*re shuffles books so all books that are added are grouped together to aid the search algorthimn */
	{
		bookCollection[subjectIndex][startingIndex] = bookCollection[subjectIndex][startingIndex + 1]; 
		startingIndex++;
	}
	
	bookCollection[subjectIndex][startingIndex].added = 0; /*the last book in the reshuffle will either be a duplicate or the one to be removed */
}


void returnBook (int bookIndex, int studentIndex) /*returns a book a student has borrowed */
{
	bookIndex = bookIndex - 1; /*because the bookIndex entered by the user is 1 too large */
	
	if (studentRegister[studentIndex].borrowedBooks[bookIndex].borrowed == 1) /*if the student has borrowed the book at the selected index */
	{
		studentRegister[studentIndex].borrowedBooks[bookIndex].borrowed = 0;
		studentRegister[studentIndex].booksOut = studentRegister[studentIndex].booksOut - 1;
		int subjectIndex = searching(studentRegister[studentIndex].borrowedBooks[bookIndex].subject);
		
		for (int i = 0; i < 50; i++) /*change to dynamic array size */
		{
			if (strcmp(bookCollection[subjectIndex][i].name, studentRegister[studentIndex].borrowedBooks[bookIndex].name) == 0) /*if names the same*/
			{
				bookCollection[subjectIndex][i].borrowed = 0;
			}
		}
		
		searching(studentRegister[studentIndex].borrowedBooks[bookIndex].subject); /*the searching function lists the books, this lists them after the return to show the book is now avaiable and the return has taken place */
	}
	
	else
	{
		printf("You have selected an empty slot or this book has already been returned. \n");
	}
}

void borrowBook (int indexOne, int indexTwo, char username[]) /*borrows a book from the array */
{
	if (bookCollection[indexOne][indexTwo - 1].borrowed == 1)
	{
		printf("Book is unavaliable. \n");
	}
	
	else 
	{
		bookCollection[indexOne][indexTwo - 1].borrowed = 1; /*minus 1 because the list of books starts at 1 not 0 */
		int index = search(username);
		int i = 0;
		
		while(studentRegister[index].borrowedBooks[i].borrowed == 1)
		{
			i++;
		}
		
		if (i < 5) /*if student has not borrowed too many books */
		{
			studentRegister[index].borrowedBooks[i] = bookCollection[indexOne][indexTwo -1]; /*add book to array of borrowed books */
			printf("Book Borrowed. \n");
			studentRegister[index].booksOut++;
		}
		
		else 
		{
			printf("Maximum book capacity already reached. Return a book in order to borrow a new one. \n");
		}
	}
}

void addBook (struct book bookToAdd) /*adds a book to the array*/
{
	int index = hash(bookToAdd.subject, 50);
	int handledIndex = collisionTest(index, bookToAdd); /*checks for and handles data collisions*/
	bookToAdd.added = 1;
	bookToAdd.borrowed = 0;
	
	for(int i=0; i<50; i++) 
	{
		if(bookCollection[handledIndex][i].added == 0) /*if slot empty*/
		{	
			bookCollection[handledIndex][i] = bookToAdd;
			printf("\n Book Added at %i \n", handledIndex);
			break; /*prevents every space being taken up by book */
			
		}
	}
}

int searching (char subject[]) /*searches for a subject and lists every book of that subject */
{
	int found = 0;
	int index = hash(subject, 50); /*change to dynamic value */
	int added = bookCollection[index][0].added;
	int newIndex = -5;
	
	while (added == 1) /*finds the proper index in the case of a data collision */
	{
		if (strcmp(bookCollection[index][0].subject, subject) == 0) /*if subjects the same*/
		{
			newIndex = index;
			break;
		}
		
		else
		{
			index++;
			added = bookCollection[index][0].added;
		}
	}
		
	
	if (newIndex != -5) /* if subject found */
	{
		for (int i=0; i<50; i++) /*needs to change to dynamic value */
		{
			if (bookCollection[newIndex][i].added == 0)
			{
				break;
			}
			
			if (bookCollection[newIndex][i].borrowed == 1)
			{
				printf("%i. %s. Not Available.\n", i+1, bookCollection[newIndex][i].name);
			}
			
			else
			{	
				printf("%i. %s \n", i+1, bookCollection[newIndex][i].name); /*need to minus 1 when collecting book */
			}
			
		}
		
		return newIndex;

	}
	
	else
	{
		printf("Subject Not Found");
		return -5;
	}
}


