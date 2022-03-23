
void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed );

void userCLI( User* k, BookList *all_book )

void SearchBook( BookList *all_book );

void librarianCLI( BookList *all_book );

int input_add_loan(User* user,BookList*all_book);

int input_remove_loan(User* user,BookList*all_book);

Book input_remove_book(BookList *all_book);

Book input_add_book(BookList *all_book);