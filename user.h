
#include "book_management.h"

void userCLI( User* k, BookList *all_book );

void SearchBook( BookList *all_book );

void librarianCLI( BookList *all_book, UserList*all_user );

int input_add_loan(User* user,BookList*all_book);

int input_remove_loan(User* user,BookList*all_book);

Book input_remove_book(BookList *all_book);

Book input_add_book(BookList *all_book);