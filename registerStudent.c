#include "registerStudent.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "librarystructures.h"
#include "hashthree.h"
#include "bookCollection.h"
#include <string.h>


void listStudents() /*lists all students in the array */
{
	for (int i = 0; i < 274; i++)
	{
		if (studentRegister[i].added == 1)
		{
			printf("%s \n", studentRegister[i].username);
		}
	}
}

int passwordHash(char password[]) /*hashes the password*/
{
	int i;
	char switchcase;
	int alphabetValues[100]; /* work out best size for memory management sake */
	int count = 0;
	int hash = 1;  /* 1 to allow the alphabet value to be the same */
	
	for (i=0; password[i] != '\0'; i++)
	{
		switchcase = password[i];
		
		switch(switchcase) 
		{

			case 'a':
				alphabetValues[i] = 1;
				break;
			
			case 'b':
				alphabetValues[i] = 2;
				break;
				
			case 'c':
				alphabetValues[i] = 3;
				break;
				
			case 'd':
				alphabetValues[i] = 4;
				break;
				
			case 'e':
				alphabetValues[i] = 5;
				break;
				
			case 'f':
				alphabetValues[i] = 6;
				break;
				
			case 'g':
				alphabetValues[i] = 7;
				break;
				
			case 'h':
				alphabetValues[i] = 8;
				break;
				
			case 'i':
				alphabetValues[i] = 9;
				break;
				
			case 'j':
				alphabetValues[i] = 10;
				break;
				
			case 'k':
				alphabetValues[i] = 11;
				break;
				
			case 'l':
				alphabetValues[i] = 12;
				break;
				
			case 'm':
				alphabetValues[i] = 13;
				break;
				
			case 'n':
				alphabetValues[i] = 14;
				break;
			
			case 'o':
				alphabetValues[i] = 15;
				break;
				
			case 'p':
				alphabetValues[i] = 16;
				break;
				
			case 'q':
				alphabetValues[i] = 17;
				break;
				
			case 'r':
				alphabetValues[i] = 18;
				break;
				
			case 's':
				alphabetValues[i] = 19;
				break;
				
			case 't':
				alphabetValues[i] = 20;
				break;
				
			case 'u':
				alphabetValues[i] = 21;
				break;
				
			case 'v':
				alphabetValues[i] = 22;
				break;
				
			case 'w':
				alphabetValues[i] = 23;
				break;
				
			case 'x':
				alphabetValues[i] = 24;
				break;
				
			case 'y':
				alphabetValues[i] = 25;
				break;
				
			case 'z':
				alphabetValues[i] = 26;
				break;
				
			default :
				alphabetValues[i] = 2;
				
			
		}
		
		count++;
	}
	
	for (i=0; i < count; i++) 
	{
		int value = alphabetValues[i];
		/*printf("%i", value);*/
		hash = hash * alphabetValues[i];
	}
	
	/*printf("\n hash: %i%", hash);*/
	
	if (hash < 0)
	{
		hash = hash * -1;
	}
	
	return hash;
}

int listBorrowedBooks (int index) /*lists every book the user has borrowed*/
{
	for (int i = 0; i < 5; i++)
	{
		if (studentRegister[index].borrowedBooks[i].borrowed == 1)
		{
			printf("%i. %s. \n", i+1, studentRegister[index].borrowedBooks[i].name);
		}
	}
}
		
int login (char username[], char password[]) /*checks if the login credentials are valid*/
{
	int index = search(username);
	int hashedPassword = passwordHash(password);
	
	if (studentRegister[index].password == hashedPassword)
	{
		return 1;
	}
	
	else 
	{
		printf("Login Unsuccesful. \n");
		return -5;
	}
}

int search (char username[]) /*returns the index of the student with the passed username*/
{
	/*printf("\n Search Called");*/
	int index = hash(username, 274);
	int added = studentRegister[index].added;
	
	while (added == 1) /*searches for the student in consideration of data collisions*/
	{
		if (strcmp(studentRegister[index].username, username) == 0) /*if usernames the same*/
		{
			return index;
		}
		
		else
		{
			index++;
			added = studentRegister[index].added;
		}
	}
		
	return -5; /*not found */
}	
	
	
int validateUsername(char username[]) /*checks if the username is valid*/
{
	int length = 1;
	int charAmount = 0;
	
	for (int i=0; username[i] != '\0'; i++)
	{
		if (isalpha(username[i]) == 0 && isdigit(username[i]) == 0) /*if a special character is used*/
		{
			return 1;
		}
		
		if (isalpha(username[i]) != 0)
		{
			charAmount++;
		}
		length++;
	}
	
	if (length > 16 || length < 6) /*if too long or short*/
	{
		return 2;
	}

	if (charAmount < 4)
	{
		return 3;
	}
	
	if (search(username) != -5) /*if the username already in array*/
	{
		printf("return 4");
		return 4;
	}
	
	else 
	{
		return 0;
	}
}

int validatePassword(char password[]) /*returns int based on if the username already exists, if the username is too long or short or if the username contains unwanted characters */
{
	int length = 1;
	int numAmount = 0;
	int charAmount = 0;

	
	for (int i=0; password[i] != '\0'; i++) /*counts the number of chars and numbers*/
	{
		if (isalpha(password[i]) == 0 && isdigit(password[i]) == 0)
		{
			return 1;
		}
		
		if (isalpha(password[i]) != 0)
		{
			charAmount++;
		}
		
		
		
		if (isdigit(password[i]) != 0)
		{
			numAmount++;
		}
			
		length++;
	}
	
	if (length > 16 || length < 8)
	{
		return 2;
	}
	

	if (charAmount < 4 || numAmount < 2)
	{
		return 3;
	}
	
	else
	{
		return 0;
	}
	
	
}

int collisionHandlingStudent (int hashValue, struct student studentToAdd) /*handles collisions for the student array*/
{
	/*while having only one collision handling function would be more modular, this would require the copying and reinitialising of a whole array which would be ineffecient*/
	int newHash;
	/*printf("\n colhandling called*/
	
	
	if (studentRegister[hashValue].added == 1) /* if student has been added */
	{

		if (strcmp(studentRegister[hashValue].username, studentToAdd.username) != 0 ) /*not the same name*/
		{
			/*printf("Data Collision");*/
			
			
			if (hashValue > 49) /*this should be size of array */
			{
				newHash = 0;
			}
			
			else 
			{
				newHash = hashValue + 1;
			}
			
			int newIndex = collisionHandlingStudent(newHash, studentToAdd);
			return newIndex;/*Data Collision Occured*/
		}
		
		else 
		{
			return hashValue; /*Student has already been added */
		}
	}
	
	else
	{
		return hashValue;
	}
}

void registerStud() /*adds a student to the array of students */
{
	int finished = 0;
	char username[18], password[18]; 
	int usernameCheck;
	int passwordCheck;

	while (finished == 0)
	{
		printf("\n Enter Username (must be between 6 and 16 characters long and contain only letters and numbers)");
		scanf("%17s", username);

		usernameCheck = validateUsername(username);
		
		if (usernameCheck == 1) /*unwated characters */
		{
			printf("\n Username contains special characters.");
			continue;
		}
		
		else if (usernameCheck == 2) /*username too long or short */
		{
			printf("\n Username too long or too short.");
			continue;
		}
		
		else if (usernameCheck == 3) /*not enough chars */
		{
			printf("\n Username contains too little characters.");
			continue;
		}
		
		else if (usernameCheck == 4) /*username already exists*/
		{
			printf("\n Username already exists.");
			continue;
		}
		
		
		printf("\n Enter Password (Must be between 8 and 16 characters long and contain a mix of numbers (atleast 2) and characters");
		scanf("%17s", password); /*limits input to 19 chars, saving one for terminate char */
		if (password[0] == 'z')
		{
			finished = 1;
			break;
		}
		passwordCheck = validatePassword(password);
		
		if (passwordCheck == 1) /*unwated characters */
		{
			printf("\n Password contains special characters.");
			continue;
		}
		
		else if (passwordCheck == 2) /*password too long or short*/
		{
			printf("\n Password too long or too short.");
			continue;
		}
		
		else if (passwordCheck == 3) /*not enough nums or chars */
		{
			printf("\n Password doesn't contain enough numbers or characters.");
			continue;
		}
		
		char passwordTwo[18];
		printf("Enter Password Again");
		scanf("%17s", passwordTwo);
		
		if(strcmp(password, passwordTwo) != 0)
		{
			printf("\n Passwords do not match");
			continue;
		}
		
		
		if (usernameCheck == 0 && passwordCheck == 0) /*creates a new student struct and adds it to the student array */
		{
			struct student newStudent;
			int hashedPassword = passwordHash(password);
			strcpy(newStudent.username, username);
			/*strcpy(newStudent.password, password);*/
			newStudent.password = hashedPassword;
			int index = hash(username, 274); /*add data collision */
			int newIndex = collisionHandlingStudent(index, newStudent);		
			/*printf("new index: %i \n", newIndex);*/
			newStudent.added = 1;
			newStudent.booksOut = 0;
			studentRegister[newIndex] = newStudent;
			printf("Student Added.\n");
			break;
		}
		
	}	
}
			
		
	
	