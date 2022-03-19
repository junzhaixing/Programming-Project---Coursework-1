#include <stdio.h>
#include <stdlib.h>

#include "libraryStructures.h"
#include "librarian.h"
#include "utility.h"
#include <book_management.h>
////
// Code module for librarian
// They can list the books and see what is borrowed





// List the books on the screen
// Format should be "author - title" on each line

void listBooks( Book *bookList, int numBooks ) {

  // TO DO :
  //
  // list the books in format "name - title"
  for(int i=0; i<numBooks; i++)
  {
      printf("%s - %s\n",bookList[i].author,bookList[i].title);
  }
  return;
}


// DO NOT ALTER THIS CODE

// Menu system for the librarian

void librarianCLI( Library *theLibrary ) {
    int librarianLoggedIn = 1;
    int option;

    while( librarianLoggedIn ){
        printf("\n(logged in as: librarian)\n");
        printf("Please choose an option:\n");
        printf("1) Add a book\n 2) Remove a book\n3) Search for book\n4) Display all books\n5) Log out\n Option: ");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nadd a book\n");//tianjiashu,--
            
        }
        else if( option == 2 ) {//移除书--
            printf("\nList of borrowed books:\n");
            listBorrowedBooks( theLibrary->bookList, theLibrary->numBooks );
        }
        else if( option == 3 ) {//查找书--
            librarianLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else if( option == 4 ) {//展示书--
            librarianLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else if( option == 5 ) {
            librarianLoggedIn = 0;
            printf("\nLogging out...\n");
        }
        else
            printf("\nSorry,the option you entered was invalid, please try again.\n");
    }
    return;
}

