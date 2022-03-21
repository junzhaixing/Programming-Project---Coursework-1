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

void initLibrary( char *bookFile, BookList *all_book ) {



  // TO DO :
  
  // dynamically allocate the bookList array for storing books
  theLibrary->bookList = (Book *)malloc( sizeof(Book)*(theLibrary->maxBooks) );
  // check the book file exists 
  FILE *fp = NULL;
  fp = fopen(bookFile, "r");
  if(fp==NULL)
  {
  // use the error message and exit the program if it does not
    printf("Error\nBook file does not exist: %s\n",bookFile);
    exit(0);
  }
  else
  {
  // open it if it exists

  // use the readBooks function to read in the file and add the book records into the bookList array
    theLibrary->numBooks = readBooks( fp, theLibrary->bookList );
  // remember to close the file
    fclose(fp);
  // Initialise the User data
    for(int i=0; i<theLibrary->maxBorrowed; i++)
    {
        //theLibrary->theUser.borrowed[i]=( Book *)malloc( sizeof(Book) );
        //theLibrary->theUser.borrowed[i]->available=0;
        theLibrary->theUser.borrowed[i]=NULL;
    }
    //theLibrary->theUser.numBorrowed = 0;

  
  }
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

int readBooks( FILE *books, Book *bookList ) {

  int numBooks = 0;

  // TO DO:

  char line[80];
  //(fgets(line,80,books)) != NULL

  //(read = getline(&str,&len,books)) != -1
  //str[read-1]='\0';

  //size_t len = 0;
  //char *str = NULL;
  //ssize_t read;

  int readnumber=0;
  int book,choicetodo;
  // read from the book file pointer
  while((fgets(line,80,books)) != NULL)
  {
      book=readnumber/3;
      choicetodo=readnumber%3;
      removeNewLine(line); //去掉行末换行符
      if(choicetodo==0)
      {
          strcpy(&bookList[book].author[0],line);
          bookList[book].available=1;
          //printf("%s",bookList[book].title);
      }
      else if(choicetodo==1)
      {
          strcpy(&bookList[book].title[0],line);
          //printf("%s",bookList[book].author);
      }
      //fprintf(stdout,"%s",str);
      
      readnumber++;
  }
  numBooks=readnumber/3;
  // assign values to a Book structure in the bookList array for each complete record
  
  // read data until the file ends
  
  return numBooks;
}

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

void libraryCLI( char *bookFile ) {
    int libraryOpen = 1;
    int option;

    // create the library structure 
    BookList *all_book = (BookList *)malloc( sizeof(BookList) );

    initLibrary( bookFile, all_book );
   
    while( libraryOpen ){
        printf("\nPlease choose an option\n1) Register\n2) login\n3) Search for book\n4) Display all book\n5) Quit\n Option:");
        option = optionChoice();

        if( option == 1 ) {
            reg( theuser );//user list还未设置
        }
        else if( option == 2 ) {
            Userjudge k=login(theuser);//user list还未设置
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

    return;
}

