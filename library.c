#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libraryStructures.h"
#include "library.h"
#include "user.h"
#include "librarian.h"
#include "utility.h"


#include "reg_login.h"
#include "book_management.h"

////
// Code module for main library menu and file management
// Reads the book and initialises the problem data

// Initialise library data
// Input: 
// bookfile - name of book file
// theLibrary - library data structure

void initLibrary( BookList *all_book, UserList *all_user) {

  char* bookFile="book.txt";
  FILE *fp = NULL;
  fp = fopen(bookFile, "r");
  int bookFile_error=load_books(fp, all_book);
  fclose(fp);
  if(bookFile_error==-2)
  printf("Error loading book file");

  char* userFile="user.txt";
  fp = NULL;
  fp = fopen(userFile, "r");
  int userFile_error=load_users(fp, all_user);
  fclose(fp);
  if(userFile_error==-2)
  printf("Error loading user file");

  
  //printf("Error\nBook file does not exist: %s\n",bookFile);
  //exit(0);
  
  return;
}

// Read in book file and create the books data structure
// the book file is in a fixed format:
// * book author
// * book title
// * blank line
// Input:
//   books - file pointer to text input file
//   bookList - alocated array for storing Book structures
// Output:
//   numBooks - number of books read



// Free any allocated library data
// Input: 
// theLibrary - library data structure

void exitLibrary( BookList *all_book ) {

  // TO DO:

  // free the allocated lists
  Book *p=all_book->list,*q;
    while(p!=NULL)       /* p没有指向链表尾则循环 */
    { q=p;                                 /* 保存p */ 
        p=p->next;                      /* p向前推进一个结点 */
        DeleteNode(q);               /* 删除结点*q */
    }
    
  return;
}

// DO NOT ALTER THIS FUNCTION
// Library menu system

void libraryCLI( ) {
    int libraryOpen = 1;
    int option;

    // create the library structure 
    BookList *all_book = (BookList *)malloc( sizeof(BookList) );
    UserList *all_user = (UserList *)malloc( sizeof(UserList) );

    initLibrary( bookFile, all_book, all_user );
   
    while( libraryOpen ){
        printf("\nPlease choose an option\n1) Register\n2) login\n3) Search for book\n4) Display all book\n5) Quit\n Option:");
        option = optionChoice();

        if( option == 1 ) {
            reg( all_user );//user list设置
        }
        else if( option == 2 ) {
            Userjudge k=login( all_user );//user list还未设置
            if(k.judge==1)
                UserCLI( k.username, all_book );
            else if(k.judge==2)
                librarianCLI(all_book);
        }
        else if( option == 3 ) {
            //search for book
            printf("\nbook\n");
        }
        else if( option == 4 ) {
            //zhanshiliebiaohanshu
            printf("\nall book is\n");
        }
        else if( option == 5 ) {
            libraryOpen = 0;
            printf("\nThank you for using the library!\nGoodbye!\n");
        }
        else
            printf("\nSorry,the option you entered was invalid, please try again.\n");
    }

    exitLibrary( all_book );

    // free the library structure
    free( all_book );
    free( all_user );

    return;
}

