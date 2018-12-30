#include <stdio.h>
#include <string.h>
#include <math.h>
#include "librarystructures.h"
#include "hashthree.h"
#include "registerStudent.h"
#include "bookCollection.h"

int hash (char name[], int sizeOfArray) /*hashes the inputted string within range of the size of the array */
{
	int i;
	char switchcase;
	int alphabetValues[100];
	int hash = 1;  /* 1 because we will be multiplying this value */
	int count = 0;
	
	for (i=0; name[i] != '\0'; i++)
	{
		switchcase = name[i];
		
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
				alphabetValues[i] = 27; 
				
			
		}
		
		count++;
	}
	
	for (i=0; i < count; i++) /*multiplies each number created to get the hashvalue*/
	{
		hash = hash * alphabetValues[i];
	}
	
	if (hash < 0) /*in some cases the hash value was a negative number so this turns it back into a positive */
	{
		hash = hash * -1;
	}

	int index =  hash % sizeOfArray; /*keeps the hash value within the size of the array*/
 
	return index;
}


int collisionTest (int hashValue, struct book bookAdded) /*tests for collisions and handles them */
{
	int newHash;
	
	if (bookCollection[hashValue][0].added != 0) /*if subject has been added */
	{

		if (strcmp(bookCollection[hashValue][0].subject, bookAdded.subject) != 0 ) /*if they have different names but have the same index*/
		{
			/*printf("Data Collision");*/
			
			if (hashValue > 49) /*the maximum array index*/
			{
				newHash = 0;
			}
			
			else 
			{
				newHash = hashValue + 1;
			}
			
			int newIndex = collisionTest(newHash, bookAdded); /*calls itself to keep iterating through the array until an empty slot is found*/
			return newIndex;
		}
		
		else 
		{
			return hashValue; /*Subject has already been added */
		}
	}
	
	else
	{
		return hashValue;
	}
}



