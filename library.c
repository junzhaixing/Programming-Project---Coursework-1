#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"
#include "user.h"
#include "utility.h"
#include "reg_login.h"

// Initialise library data
void initLibrary( BookList *all_book, UserList *all_user){

  char* bookFile="book.txt";
  FILE *fp = NULL;
  fp = fopen(bookFile, "r");
  int bookFile_error=load_books(fp, all_book);
  if(bookFile_error==-2){
    printf("Error loading book file\n");
    exit(0);
  }
  fclose(fp);
  
  char* userFile="user.txt";
  fp = NULL;
  fp = fopen(userFile, "r");
  int userFile_error=load_users(fp, all_user);
  if(userFile_error==-2){
    printf("Error loading user file\n");
    exit(0);
  }
  fclose(fp);
  
  char* loanFile="loans.txt";
  fp = NULL;
  fp = fopen(loanFile, "r");
  int loanFile_error=load_loans(fp, all_user, all_book);
  if(loanFile_error==-2){
    printf("Error loading loan file\n");
    exit(0); 
  }
  fclose(fp);
  
  return;
}


// Free any allocated library data
void exitLibrary( BookList *all_book, UserList *all_user) {
    //store the book data to the file
    char* bookFile="book.txt";
    FILE *fp = NULL;
    fp = fopen(bookFile, "w+");
    int bookFile_error=store_books(fp,all_book);
    fclose(fp);
    if(bookFile_error==-2)
    printf("Error store book file");
    //store the user data to the file
    char* userFile="user.txt";
    fp = NULL;
    fp = fopen(userFile, "w+");
    int userFile_error=store_users(fp,all_user);
    fclose(fp);
    if(userFile_error==-2)
    printf("Error store book file");
    //store the loan data to the file
    char* loanFile="loans.txt";
    fp = NULL;
    fp = fopen(loanFile, "w+");
    int loanFile_error=store_loans(fp, all_user);
    fclose(fp);
    if(loanFile_error==-2)
    printf("Error store book file");
    
    // free the allocated lists
    delete_book(all_book);
    User *p=all_user->list,*q;
    while(p)      
    {   
        free(p->username);
        free(p->password);
        delete_book(p->loans);
        free(p->loans);
        q=p;                         
        p=p->next;           
        DeleteNode(q);            
    }
    return;
}


// Library menu system
void libraryCLI(){
    int libraryOpen = 1;
    int option;
    
    // create the library structure 
    BookList *all_book = (BookList *)malloc( sizeof(BookList) );
    UserList *all_user = (UserList *)malloc( sizeof(UserList) );
    
    // read the library
    initLibrary( all_book, all_user );
    
    while( libraryOpen ){
        printf("\nPlease choose an option\n1) Register an account\n2) login\n3) Search for book\n4) Display all book\n5) Quit\n Option:");
        option = optionChoice();

        if( option == 1 ) {//user register
            reg( all_user );
        }
        else if( option == 2 ) {
            User* k=login( all_user );//user login
            if(k!=NULL)
            {
                if(!strcmp(k->username,"librarian")&&!strcmp(k->password,"librarian"))
                    librarianCLI(all_book, all_user);
                else userCLI( k, all_book );
            }
      
        }
        else if( option == 3 ) {//search for book
            SearchBook( all_book );
        }
        else if( option == 4 ) {//diplay the book
            printf("\n");
            printbook(*all_book,1);
        }
        else if( option == 5 ) {
            libraryOpen = 0;
            printf("\nThank you for using the library!\nGoodbye!\n");
        }
        else
            printf("\nSorry,the option you entered was invalid, please try again.\n");
    }
    
    // free the library structure
    exitLibrary( all_book, all_user);
    free( all_book );
    free( all_user );
    return;
}

