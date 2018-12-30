#include "registerStudent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "librarystructures.h"
#include "hashthree.h"
#include <string.h>
#include "bookCollection.h"

void main ()
{
	
int finished = 0;
int input = 0;
char username[18];
char password[18];
int bookCount = 0;
char librarianPassword[50];

printf("Set Librarian Passcode.\n");
scanf("%s", librarianPassword);
	
while (finished == 0)
{
	printf("\n1. Student \n");
	printf("2. Librarian \n");
	printf("3. Exit");
	scanf("%i", &input);
	
	if (input == 1)
	{
		while (1==1)
		{
			input = 0;
		
			printf("\n1. Login \n");
			printf("2. Register \n");
			printf("3. Escape");
			scanf("%i", &input);
		
			if (input == 1)
			{
				
				printf("Enter Username \n");
				scanf("%17s", username);
				printf("Enter Password \n");
				scanf("%17s", password);
				
				if (login(username, password) == 1)
				{
					while(1==1)
					{
						input = 0;
						printf("1. Search and Borrow Books \n");
						printf("2. Return Book \n");
						printf("3. List Books \n");
						printf("4. Escape \n");
						scanf("%i", &input);
						
						if (input == 1)
						{
							char subject[18];
							printf("Enter subject code \n");
							scanf("%17s", subject);
							
							int index = searching(subject);
							
							if (index != -5)
							{
								input = 0;
								printf("Enter the number of the book you would like to borrow or press '999' to escape \n");
								scanf("%i", &input);
								
								if (input == 999)
								{
									continue;
								}
								
								borrowBook(index, input, username);
								continue;
							}
							
							else
							{
								continue;
							}
							
						}
						
						else if (input == 2)
						{
							int studentIndex = search(username);
							int bookIndex;
							listBorrowedBooks(studentIndex);
							printf("Enter the number of the book you would like to return \n");
							scanf("%i", &bookIndex);
							returnBook(bookIndex, studentIndex);
							continue;
							
						}
						
						else if (input == 3)
						{
							listBooks();
						}
						
						else if (input == 4)
						{
							break;
						}
						
						else
						{
							printf("Invalid Input \n");
							continue;
						}
					}
						
				}
				
				else
				{
					continue;
				}
		
			}
			
			else if (input == 2)
			{
				registerStud();
				continue;
			}
			
			else if (input == 3)
			{
				finished = 0;
				break;
			}
			
			else
			{
				printf("Incorrect Input \n");
				continue;
			}
			
		}
	}
	
	else if (input == 2)
	{
		char passcode[50];
		printf("Enter librarian passcode.\n");
		scanf("%s", passcode);
		
		if (strcmp(passcode, librarianPassword) != 0)
		{
			printf("Incorrect passcode.\n");
			continue;
		}
		
		while (1 == 1)
		{
			input = 0;
			printf("\n1. Add Book \n");
			printf("2. Remove Book \n");
			printf("3. List Books \n");
			printf("4. List Students \n");
			printf("5. Escape \n");
			scanf("%i", &input);
			
			if (input == 1)
			{
				char name[50];
				char subject[50];
				printf("Enter book name. \n");
				scanf("%s", name);
				printf("Enter book subject. \n");
				scanf("%s", subject);

				struct book newBook;
				struct student newStudent;
				strcpy(newBook.name, name);
				strcpy(newBook.subject, subject);
				addBook(newBook);
				bookCount++;
				continue;
			}
			
			else if (input == 2)
			{
				char subjectToRemove[50];
				printf("Enter the subject of the book you would like to remove. \n");
				scanf("%s", subjectToRemove);
				int subjectIndex = searching(subjectToRemove);
				
				if (subjectIndex != -5)
				{
					int bookIndex;
					printf("Enter the number of the book you'd like to remove. \n");
					scanf("%i", &bookIndex);
					bookIndex = bookIndex - 1; /*because the list of books begins at 1 */
					removeBook(subjectIndex, bookIndex);
					continue;
				}
				
				else 
				{
					continue;
				} 
			}
			
			else if (input == 3)
			{
				listBooks();
			}
			
			else if (input == 4)
			{
				listStudents();
			}
			
			else if (input == 5)
			{
				break;
			}
			
			else
			{
				printf("Input invalid. \n");
			}
		}
			
			
		
	}
	
	else if (input == 3)
	{
		finished = 1;
		break;
	}
	
	else
	{
		printf("Incorrect Input \n");
		continue;
	}
}
}