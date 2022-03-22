#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include <stdio.h>

#define CreateNode(p)  p=(Book*)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p); 
// git commit -m "xxx"
// git push 
/*You can extend the structs (Book and BookList) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/

typedef struct _Book {
	    unsigned int id; //Book ID
		char *title; //book title
		char *authors; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
		struct _Book *next; //pointer to the next book element

		
}Book;

typedef struct _BookList {
	Book* list; // pointer to a list of struct Book.
	unsigned int length; // number of elements in the (Book*) List 

	 //for printf排版整齐
	int title_longest;//record longest length of title
	int authors_longest;//record longest author of title
}BookList;

typedef struct _User {
	    
		char *username; //username
		char *password; //user password
		struct _User *next;

		//Book *borrowed[4];//--要改
        //int numBorrowed;
}User;

typedef struct _UserList {
	 User* list; // pointer to a list of struct user.
	 unsigned int length; // number of elements in the (user*) List 
}UserList;

typedef struct _Userjudge {//for change the admin and user part
	    
		char *username; //username
		int judge; //judge the id
}Userjudge;

void first_book_get(BookList *p);

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file,BookList *all_book);

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookList *all_book);

int load_users(FILE *file, UserList *all_user);

int load_loans(FILE *file, UserList *all_loan);

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book,BookList *all_book);

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book,BookList *all_book);

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title,BookList *all_book);

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author,BookList *all_book);

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year,BookList *all_book);













#endif