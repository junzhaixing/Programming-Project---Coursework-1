#include <stdio.h>
#include <stdlib.h>


#include "user.h"
#include "utility.h"

#include "book_management.h"
////
// Code module for the library user
// They can look for available books,
// borrow and return books

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

void userCLI( User* user, BookList *all_book ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n(logged in as: %s)\n",user->username);
        printf("Please choose an option:\n");
        printf("1) Borrow a book\n 2) Return a book\n3) Search for book\n4) Display all books\n5) Log out\n Option: ");
        option = optionChoice();

        if( option == 1 ) {//借书
            int L=input_add_loan(user, all_book);
            if( L != 0 ){
                int success=add_loans(L, user, all_book);
                if( success == 0)   
                    printf("Book was successfully loaned!\n");
            }
    
        }
        else if( option == 2 ) {//还书
            int L=input_remove_loan(user, all_book);
            if( L != 0 ){
                int success=remove_loans(L, user, all_book);
                if( success == 0)   
                    printf("Returned book successfully!\n");
            }
        }
        else if( option == 3 ) {//查找书--
            SearchBook( all_book );
            
        }
        else if( option == 4 ) {//展示书--
            printbook(*all_book);
        }
        else if( option == 5 ) {
            userLoggedIn = 0;
            printf("\nLogging out...\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}

// Menu system for the librarian

void librarianCLI( BookList *all_book ) {
    int librarianLoggedIn = 1;
    int option;

    while( librarianLoggedIn ){
        printf("\n(logged in as: librarian)\n");
        printf("Please choose an option:\n");
        printf("1) Add a book\n2) Remove a book\n3) Search for book\n4) Display all books\n5) Log out\n Option: ");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nadd a book\n");//tianjiashu,--
            int success=add_book((input_add_book(all_book)),all_book);
            if( success == 0)   
            printf("Book was successfully added!\n"); 
        }
        else if( option == 2 ) {//移除书--
            printf("\nList of borrowed books:\n");
            int success=remove_book((input_remove_book(all_book)),all_book);
            if( success == 0)   
            printf("Book was successfully removed!\n");
            
        }
        else if( option == 3 ) {//查找书--
            
            SearchBook( all_book );
        }
        else if( option == 4 ) {//展示书--
            printbook(*all_book);
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


void SearchBook( BookList *all_book )//--
{
    int SearchIn=1;
    int option;

    printf("\nLoading search menu...\n");
    while( SearchIn ){
        printf("\nLoading search menu...\n");  
        printf("Please choose an option:\n");
        printf("1) Find book by title\n2) Find book by author\n3) Find book by year\n4) Return to previous menu\n Option: ");
        option = optionChoice();

        if( option == 1 ) {//按名字搜--
            char title[80];
            printf("Please enter the title:");
            fgets(title,80,stdin);
            BookList k=find_book_by_title (title,all_book);
            printbook(k);
        }
        else if( option == 2 ) {//按作者--
            char author[80];
            printf("Please enter the author:");
            fgets(author,80,stdin);
            BookList k=find_book_by_author (author,all_book);
            printbook(k);
            
        }
        else if( option == 3 ) {//按年--
            int year;
            printf("Please enter the author:");
            year = optionChoice();
            if(year==0)
               printf("Sorry,the year you entered was invalid, please try again.\n");
            else 
            {
               BookList k=find_book_by_year (year,all_book);
               printbook(k);
            }
        }
        else if( option == 4 ) {//退出--
            SearchIn = 0;
            printf("\nReturning to previous menu...\n");
        }
        else
            printf("\nSorry,the option you entered was invalid, please try again.\n");
      }
}

int input_add_loan(User* user,BookList*all_book){
    int l_id;
    printf("Enter the id of the book you wish to loan: \n");
    l_id=optionChoice();
    if(l_id==0){
    printf("Sorry,the id you entered was invalid, please try again.\n");
    return 0;}
    Book* k=all_book->list->next;
    int h_i=0;
    while(k)
    {
        if(k->id==l_id){
            h_i=1;
            break;
        }
        k=k->next;
    }
    if(h_i==0){
        printf("Sorry, the id you enterd don't exsist.\n");
        return 0;
    }
    Book* p=user->loans->list->next;
    while(p)
    {
        if(p->id==l_id){
            printf("Sorry,you already have a copy of this book on loan")
            return 0;
        }
        p=p->next;

    }
    return l_id;
}

int input_remove_loan(User* user,BookList*all_book){
    int l_id;
    printf("Below the list of book you are currently borrowing: \n");
    printbook(*all_book);

    printf("Enter the ID number of the book you wish to return: \n");
    l_id=optionChoice();
    if(l_id==0){
    printf("Sorry,the id you entered was invalid, please try again.\n");
    return 0;}
    Book* k=user->loans->list->next;
    int h_i=0;
    while(k)
    {
        if(k->id==l_id){
            h_i=1;
            break;
        }
        k=k->next;
    }
    if(h_i==0){
        printf("Sorry,you don't have the copy of this book!\n");
        return 0;
    }
    if(k->copies==0){
        printf("Sorry,the copy of this book is none!\n");
        return 0;
    }
    return l_id;
}

Book input_remove_book(BookList *all_book){
    Book remove;

    printf("Enter the id of the book you wish to remove: \n");
    remove.id = optionChoice();
    if(year==0)printf("Sorry,the id you entered was invalid, please try again.\n");
    remove.title="meiyong";
    remove.authors="meiyong";
    remove.year=1;
    remove.copies=1;
    remove.next=NULL;

    return remove;

}

Book input_add_book(BookList *all_book){

    Book input;

    input.title=(char*)malloc(sizeof(char)*80);
    printf("Enter the title of the book you wish to add: \n");
    fgets(input.title,80,stdin);
    if(input.title=="")
    printf("Sorry,the title can't be empty, please try again.\n");
    
    input.authors=(char*)malloc(sizeof(char)*80);
    printf("Enter the author of the book you wish to add: \n");
    fgets(input.authors,80,stdin);
    if(input.authors=="")
    printf("Sorry,the author can't be empty, please try again.\n");

    printf("Enter the year of the book you wish to add was released: \n");
    input.year = optionChoice();
    if(year==0)printf("Sorry,the year you entered was invalid, please try again.\n");
    
    printf("Enter the number of copies of the book that you wish to add: \n");
    input.copies = optionChoice();

    input.next=NULL;
    input.id=all_book->length;//有问题，关于id

    return input;
}
