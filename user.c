#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"
#include "utility.h"

// Menu system for search book
void SearchBook( BookList *all_book )
{
    int SearchIn=1;
    int option;

    printf("\nLoading search menu...\n");
    while( SearchIn ){  
        printf("\nPlease choose an option:\n");
        printf("1) Find book by title\n2) Find book by author\n3) Find book by year\n4) Return to previous menu\n Option: ");
        option = optionChoice();

        if( option == 1 ) {//search by title
            char title[1024];
            printf("\nPlease enter the title: ");
            fgets(title,1024,stdin);
            removeNewLine(title);
            BookList k=find_book_by_title (title,all_book);
            printbook(k,1);
        }
        else if( option == 2 ) {//search by author
            char author[1024];
            printf("\nPlease enter the author: ");
            fgets(author,1024,stdin);
            removeNewLine(author);
            BookList k=find_book_by_author (author,all_book);
            printbook(k,1);
            
        }
        else if( option == 3 ) {//search by year
            int year;
            printf("\nPlease enter the year: ");
            year = optionChoice();
            if(year==-1)
               printf("Sorry,the year you entered was invalid, please try again.\n");
            else 
            {
               BookList k=find_book_by_year (year,all_book);
               printbook(k,1);
            }
        }
        else if( option == 4 ) {//return back
            SearchIn = 0;
            printf("\nReturning to previous menu...\n");
        }
        else
            printf("\nSorry,the option you entered was invalid, please try again.\n");
      }
}

//collect user input and judge the input 
int input_add_loan(User* user,BookList*all_book){
    int l_id;
    printf("\nEnter the ID of the book you wish to borrow: ");
    l_id=optionChoice();
    if(l_id==-1){
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
    if(k->copies==0){
        printf("Sorry, the id you enterd have no copies.\n");
        return 0;
    }
    Book* p=user->loans->list->next;
    while(p)
    {
        if(p->id==l_id){
            printf("Sorry, you already have a copy of this book on loan.\n");
            return 0;
        }
        p=p->next;

    }
    return l_id;
}

//collect user input and judge the input 
int input_remove_loan(User* user,BookList*all_book){
    int l_id;
    printf("\nBelow the list of book you are currently borrowing: \n");
    printbook(*(user->loans),2);

    printf("Enter the ID number of the book you wish to return: ");
    l_id=optionChoice();
    if(l_id==-1){
        printf("Sorry,the id you entered was invalid.\n");
        return 0;
    }
    Book* k=user->loans->list->next;
    int h_i=0;
    //judge if user not have this book
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
    //judge if library don't have copies of this book
    if(k->copies==0){
        printf("Sorry,the copy of this book is none!\n");
        return 0;
    }
    return l_id;
}

Book* input_remove_book(BookList *all_book){
    Book* remove;
    remove =malloc(sizeof(Book));
    printf("\nEnter the id of the book you wish to remove: ");
    remove->id = optionChoice();
    
    if(remove->id==-1){
        printf("Sorry,the id you entered was invalid.\n");
        return NULL;
        }
    
    Book* same=all_book->list->next;
    int judge=0;
    while(same){
        if(remove->id==same->id){
            judge=1;
            break;
        }
        same=same->next;
    }
    if(judge==0){
        printf("Sorry,the library don't have this book.\n");
        return NULL;
    }
    remove->title="meiyong";
    remove->authors="meiyong";
    remove->year=1;
    remove->copies=1;
    remove->next=NULL;

    return remove;
}

//Enter the book information and make sure there are no errors
Book* input_add_book(BookList *all_book){

    Book* input;
    input=malloc(sizeof(Book));
    char title[1024],authors[1024];
    int c='-';

    printf("\nEnter the title of the book you wish to add: ");
    fgets(title,1024,stdin);
    removeNewLine(title);
    if(strlen(title)==0){
        printf("Sorry,the title can't be empty.\n");
        return NULL;
    }
    else if(strchr(title,c)!=NULL)
    {
        printf("Sorry,title can't have \'-\' .\n");
        return NULL;
    }
    for(int i=0;i<strlen(title)-1;i++){
        if(title[i]==' '&&title[i+1]==' '){
            printf("Sorry,the title can't have two or more consecutive Spaces.\n");
            return NULL;
        }
    }
    printf("Enter the author of the book you wish to add: ");
    fgets(authors,1024,stdin);
    removeNewLine(authors);
    if(strlen(authors)==0){
        printf("Sorry,the author can't be empty.\n");
        return NULL;
    }
    else if(strchr(authors,c)!=NULL)
    {
        printf("Sorry, authors can't have \'-\' .\n");
        return NULL;;
    }
    for(int i=0;i<strlen(authors)-1;i++){
        if(authors[i]==' '&&authors[i+1]==' '){
            printf("Sorry,the title can't have two or more consecutive Spaces.\n");
            return NULL;
        }
    }

    Book* same=all_book->list->next;
    while(same){
        if((!strcmp(same->title,title))&&(!strcmp(same->authors,authors))){
            printf("Sorry,the library is already have this book.\n");
            return NULL;
        }
        same=same->next;
    }

    printf("Enter the year of the book you wish to add was released: ");
    
    input->year = optionChoice();
    if(input->year==-1||input->year>2022){
        printf("Sorry,the year you entered was invalid.\n");
        return NULL;
    }
    
    printf("Enter the number of copies of the book that you wish to add: ");
    input->copies = optionChoice();
    if(input->copies==-1){
        printf("Sorry,the copies you entered was invalid.\n");
        return NULL;
    }

    input->title=(char*)malloc(sizeof(char)*(strlen(title)+1));
    strcpy(input->title,title);
    input->authors=(char*)malloc(sizeof(char)*(strlen(authors)+1));
    strcpy(input->authors,authors);
    input->next=NULL;
    //The ID will take precedence over the previously deleted ID value, 
    //and if it does not, it will be added last  
    Book *last;
    last=all_book->list;
    while(last->next){
        Book *temp=last;
        last=last->next;
        if(last->id-temp->id>1){
            input->id=temp->id+1;
            return input;
        }
    }
    input->id=last->id+1;//id is the bigggist id +1

    return input;
}

// Menu system for the user
void userCLI( User* user, BookList *all_book ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n(logged in as: %s)\n",user->username);
        printf("Please choose an option:\n");
        printf("1) Borrow a book\n2) Return a book\n3) Search for book\n4) Display all books\n5) Log out\n Option: ");
        option = optionChoice();

        if( option == 1 ) {//borrow one book
            int L=input_add_loan(user, all_book);
            if( L != 0 ){
                int success=add_loans(L, 1, user, all_book);
                if( success == 0)   
                    printf("You have successfully borrowed the book!\n");
            }
    
        }
        else if( option == 2 ) {//return book
            int L=input_remove_loan(user, all_book);
            if( L != 0 ){
                int success=remove_loans(L, user, all_book);
                if( success == 0)   
                    printf("Returned book successfully!\n");
            }
        }
        else if( option == 3 ) {//search for one book
            SearchBook( all_book );
            
        }
        else if( option == 4 ) {//diplay the book
            printf("\n");
            printbook(*all_book,1);
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

        if( option == 1 ) {//add a book
            Book* add=input_add_book(all_book);
            if(add!=NULL) {
                int success=add_book(*add,all_book,1);
                if( success == 0)   
                printf("Book was successfully added!\n"); 
            }  
        }
        else if( option == 2 ) {//remove a book
            Book* p=input_remove_book(all_book);
            if(p!=NULL) {
                remove_loansBy_libraian(p->id, all_user,all_book);
                int success=remove_book(*p,all_book);
                
                if( success == 0)   
                printf("Book was successfully removed!\n");
            }
        }
        else if( option == 3 ) {//search for one book
            SearchBook( all_book );
        }
        else if( option == 4 ) {//diplay the book
            printf("\n");
            printbook(*all_book,1);
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
