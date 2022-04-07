
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"

// Code module for main()
// opens the library menu
int main( int argc, char **argv )
{
    
    if( argc != 4 )
    {
        printf("Error, the arguments input is not enough.\n");
        printf("Please input \"./library book.txt user.txt loans.txt\".\n"); 
        // exit the application if there is an error
        return 0;
    }
    
    if(strcmp(argv[1],"book.txt")||strcmp(argv[2],"user.txt")||strcmp(argv[3],"loans.txt")){
        printf("Error, the filename input is not correct.\n");
        printf("Please input \"./library book.txt user.txt loans.txt\".\n");
        return 0;
    }

    libraryCLI();
    return 0;
}

