
void borrowBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed );

void listMyBooks( User *theUser, Book *bookList, int maxBorrowed );

void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed );

void userCLI( char* name, BookList *all_book );

void listBooks( Book *bookList, int numBooks );

void SearchBook( Book *bookList, int numBooks );

void librarianCLI( BookList *all_book );