#include <stdio.h>
#include <stdlib.h>

#include "libraryStructures.h"
#include "user.h"
#include "utility.h"

////
// Code module for the library user
// They can look for available books,
// borrow and return books

// List the books that are available to borrow
// Input
// bookList - the array of Book structures
// numBooks - the number of books

void listAvailableBooks( Book *bookList, int numBooks ) {

  // TO DO :  

  // print out available books with format "list number - author - title" on each line
  for(int i=0; i<numBooks; i++)
  {
      if(bookList[i].available==1)
            printf("%d - %s - %s\n",i,bookList[i].author,bookList[i].title);
  }

  return;
}

// Borrow a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void borrowBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  
  int borrow_booknumber;
  // For any error message you should return to the menu
  //char borrowline[80];
  // check that the user can borrow a book
  if( theUser->numBorrowed>=4 )
  {
      printf("You have to return a book before you can borrow another\n");
      return;
  }
    

  // request the choice of book 
  printf("Which book? (number):");
  borrow_booknumber=optionChoice();
  
  int errorjudge=0,showerror=1;
  if(borrow_booknumber>=0 && borrow_booknumber<numBooks )
  {
      
    errorjudge=1;
        if(bookList[borrow_booknumber].available==1)
        {
              for(int j=0; j<maxBorrowed; j++)
                {
                    if(theUser->borrowed[j]==NULL)
                    {
                        //printf("1\n");
                        //strcpy(theUser->borrowed[j]->author,bookList[borrow_booknumber].author);
                        //strcpy(theUser->borrowed[j]->title,bookList[borrow_booknumber].title);
                        //printf("2\n");
                        Book* borrowedl = &bookList[borrow_booknumber];
                        theUser->borrowed[j] = borrowedl;
                        theUser->borrowed[j]->available=0;
                        theUser->numBorrowed++;
                        showerror=0;
                        break;
                    }
                            
                }
              //bookList[i].available=0;
              
        }
          
      
      
  }
  if(showerror==1)
  {
       if(errorjudge==1)printf("Book is not available\n");
       else if(errorjudge==0)printf("Error\nInvalid choice\n");
  }
  //listMyBooks( theUser, bookList, maxBorrowed ); 
  // check that the choice is valid 
  // error messages
  //printf("Error\nInvalid choice\n");
  //printf("Book is not available\n");
  
  // borrow the book, update the data structures

  return; 
}

// List books I have borrowed 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// maxBorrowed - max books we can borrow

void listMyBooks( User *theUser, Book *bookList, int maxBorrowed ) {

  // TO DO :  
  int shownumber=0;
  // list my books in format "number - author - title"
  for(int i=0; i<maxBorrowed; i++)
  {
      if(theUser->borrowed[i]!=NULL)
      {
          printf("%d - %s - %s\n",shownumber,theUser->borrowed[i]->author,theUser->borrowed[i]->title);
          shownumber++;
      }
            
  }
  return;
}

// Return a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  
  int booknumber;
  //int deletlength;
  // For any error message you should return to the menu
  
 
  // check that we have borrowed books 
  // error messages
  if( theUser->numBorrowed==0)
  {
        printf("Error\nYou have not borrowed any books\n");
        return;
  }
    

  // request the choice of book 
  // message
  printf("Which book? (number):");
  booknumber=optionChoice();
  if( 0<=booknumber && booknumber<(theUser->numBorrowed) )
  {
       int truebooknumber,jishu;
       jishu=booknumber+1;
       int cishu=0;
       while(jishu>0)
       {
           if(theUser->borrowed[cishu]!=NULL)jishu--;
           cishu++;
           //printf("%d\n",cishu);
       }
       truebooknumber=cishu-1;
       //printf("%d\n",truebooknumber);

       //for(int i=0; i<numBooks; i++)
       //{
          //if(strncmp (theUser->borrowed[truebooknumber]->title, bookList[i].title,strlen( theUser->borrowed[truebooknumber]->title ))==0)
         //{
               //bookList[i].available=1;
               //printf("%s - %s - %d\n",bookList[i].author,bookList[i].title, bookList[i].available);
               //printf("returnok\n");
         //}
       //}

       theUser->borrowed[truebooknumber]->available=1;
       theUser->borrowed[truebooknumber]=NULL;

       //deletlength=strlen(theUser->borrowed[truebooknumber]->author);
       //memset(theUser->borrowed[truebooknumber]->author, 0x00, sizeof (char) * deletlength);

       //deletlength=strlen(theUser->borrowed[truebooknumber]->title);
       //memset(theUser->borrowed[truebooknumber]->title, 0x00, sizeof (char) * deletlength);
       
       theUser->numBorrowed--;
  }
  else
  {
    // check the choice is valid
    // error messages
    printf("Error\nInvalid choice\n");
  }
  
  // return the book and update data structures 

  return;
}

// DO NOT ALTER THIS FUNCTION

// Menu system for library user

void userCLI( Library *theLibrary ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n User options\n 1 List available books\n 2 Borrow book\n 3 Return book\n 4 Log out\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nList available books:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
        }
        else if( option == 2 ) {
            printf("\nBorrow book from library:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
            borrowBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 3 ) {
            printf("\nReturn book from my list:\n");
            listMyBooks( &(theLibrary->theUser), theLibrary->bookList, theLibrary->maxBorrowed );
            returnBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 4 ) {
            userLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}

