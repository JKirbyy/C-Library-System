//Header File For Library Data Structures

#ifndef Library_Structures
#define Library_Structures

struct book 
	{
		char subject[50];
		char name[50];
		int added;  
		int borrowed;
		char borrowedBy[50];
	};

struct book bookCollection[50][50];

struct student
	{
		char username[18];
		int password; 
		int booksOut;
		struct book borrowedBooks[5]; /*maximum books they can take out */
		int added;
	};	
		
		
typedef struct student Student;
	
struct student studentRegister[274];

#endif