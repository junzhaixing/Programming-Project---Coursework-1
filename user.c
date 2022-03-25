#include <stdio.h>
#include <stdlib.h>


#include "user.h"
#include "utility.h"

#include "book_management.h"
////
// Code module for the library user
// They can look for available books,
// borrow and return books

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

void librarianCLI( BookList *all_book, UserList *all_user) {
    int librarianLoggedIn = 1;
    int option;

    while( librarianLoggedIn ){
        printf("\n(logged in as: librarian)\n");
        printf("Please choose an option:\n");
        printf("1) Add a book\n2) Remove a book\n3) Search for book\n4) Display all books\n5) Log out\n Option: ");
        option = optionChoice();

        if( option == 1 ) {
            //tianjiashu,--
            int success=add_book((input_add_book(all_book)),all_book);
            if( success == 0)   
            printf("Book was successfully added!\n"); 
        }
        else if( option == 2 ) {//移除书--
            Book p=input_remove_book(all_book);
            int success=remove_book(p,all_book);
            remove_loansBy_libraian(p.id, all_user,all_book);
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
            removeNewLine(title);
            BookList k=find_book_by_title (title,all_book);
            printbook(k);
        }
        else if( option == 2 ) {//按作者--
            char author[80];
            printf("Please enter the author:");
            fgets(author,80,stdin);
            removeNewLine(author);
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
            printf("Sorry,you already have a copy of this book on loan");
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
    if(remove.id==0)printf("Sorry,the id you entered was invalid, please try again.\n");
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
    printf("Enter the title of the book you wish to add: ");
    fgets(input.title,80,stdin);
    removeNewLine(input.title);
    if(input.title=="")
    printf("Sorry,the title can't be empty, please try again.\n");
    
    input.authors=(char*)malloc(sizeof(char)*80);
    printf("Enter the author of the book you wish to add: ");
    fgets(input.authors,80,stdin);
    removeNewLine(input.authors);
    if(input.authors=="")
    printf("Sorry,the author can't be empty, please try again.\n");

    printf("Enter the year of the book you wish to add was released: ");
    input.year = optionChoice();
    if(input.year==0)printf("Sorry,the year you entered was invalid, please try again.\n");
    
    printf("Enter the number of copies of the book that you wish to add: ");
    input.copies = optionChoice();

    input.next=NULL;

    Book *last;
    last=all_book->list;
    while(last->next){
        last=last->next;
    }
    input.id=last->id+1;//有问题，关于id

    return input;
}
