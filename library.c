#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"
#include "user.h"
#include "utility.h"


#include "reg_login.h"


////
// Code module for main library menu and file management
// Reads the book and initialises the problem data

// Initialise library data
// Input: 
// bookfile - name of book file
// theLibrary - library data structure

void initLibrary( BookList *all_book, UserList *all_user){

  char* bookFile="book.txt";
  FILE *fp = NULL;
  fp = fopen(bookFile, "r");
  int bookFile_error=load_books(fp, all_book);
  fclose(fp);
  if(bookFile_error==-2)
  printf("Error loading book file\n");
  
  char* userFile="user.txt";
  fp = NULL;
  fp = fopen(userFile, "r");
  int userFile_error=load_users(fp, all_user);
  fclose(fp);
  if(userFile_error==-2)
  printf("Error loading user file\n");
  

  char* loanFile="loans.txt";
  fp = NULL;
  fp = fopen(loanFile, "r");
  int loanFile_error=load_loans(fp, all_user, all_book);
  fclose(fp);
  if(loanFile_error==-2)
  printf("Error loading loan file\n");
  

  //printf("Error\nBook file does not exist: %s\n",bookFile);
  //exit(0);
  
  return;
}


// Free any allocated library data
// Input: 
// theLibrary - library data structure

void exitLibrary( BookList *all_book, UserList *all_user) {

    char* bookFile="book.txt";
    FILE *fp = NULL;
    fp = fopen(bookFile, "w+");
    int bookFile_error=store_books(fp,all_book);
    fclose(fp);
    if(bookFile_error==-2)
    printf("Error store book file");
    
    char* userFile="user.txt";
    fp = NULL;
    fp = fopen(userFile, "w+");
    int userFile_error=store_users(fp,all_user);
    fclose(fp);
    if(userFile_error==-2)
    printf("Error store book file");

    char* loanFile="loans.txt";
    fp = NULL;
    fp = fopen(loanFile, "w+");
    int loanFile_error=store_loans(fp, all_user);
    fclose(fp);
    if(loanFile_error==-2)
    printf("Error store book file");
    
    // free the allocated lists
    delete_book(all_book);
    //printf("deletebook\n");
    User *p=all_user->list,*q;
    while(p)       /* p没有指向链表尾则循环 */
    {   
        //free(p->username);
        //free(p->password);
        //delete_book(p->loans);
        free(p->loans);
        q=p;                        /* 保存p */ 
        p=p->next;           /* p向前推进一个结点 */
        DeleteNode(q);             /* 删除结点*q */
    }
    return;
}

// DO NOT ALTER THIS FUNCTION
// Library menu system

void libraryCLI(){
    int libraryOpen = 1;
    int option;
    
    // create the library structure 
    BookList *all_book = (BookList *)malloc( sizeof(BookList) );
    UserList *all_user = (UserList *)malloc( sizeof(UserList) );
    
    initLibrary( all_book, all_user );
    
    printbook(*all_book);
    User *p=all_user->list->next;
    User *k=all_user->list->next;
    while(p){
        printf("%s\t%s\n",p->username,p->password);
        p=p->next;
    }
    while(k){
        printf("%s\n",k->username);
        printbook(*(k->loans));
        k=k->next;
    }

    while( libraryOpen ){
        printf("\nPlease choose an option\n1) Register\n2) login\n3) Search for book\n4) Display all book\n5) Quit\n Option:");
        option = optionChoice();

        if( option == 1 ) {
            reg( all_user );//user list设置
        }
        else if( option == 2 ) {
            User* k=login( all_user );//user list还未设置
            if(k!=NULL)
            {
                if(!strcmp(k->username,"librarian")&&!strcmp(k->password,"librarian"))
                    librarianCLI(all_book, all_user);
                else userCLI( k, all_book );
            }
      
        }
        else if( option == 3 ) {
            //search for book
            SearchBook( all_book );
        }
        else if( option == 4 ) {
            //zhanshiliebiaohanshu
            printbook(*all_book);
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

