
// Name:Yutong Ke
// Username:
// Date started:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "library.h"

////
// Code module for main()
// opens the library menu
int main( int argc, char **argv )
{
    //char bookFile[40];

    //TO DO :
    /*
    if( argc != 2 )
    {
        // check that correct number of command line arguments are entered    
        // use the error message 
        printf("Error\nExpected use: ./library books.txt\n"); 
        // exit the application if there is an error
        return 0;
    }

    // assign command line value to filename string
    strcpy(&bookFile[0],argv[1]);
    */
    //printf("%s\n",bookFile);                 test

    // DO NOT ALTER
    // start the system
    //printf("\nIntialising library system!\n");
    libraryCLI();
    //printf("\nClosing library system!\n\n");

    return 0;
}

