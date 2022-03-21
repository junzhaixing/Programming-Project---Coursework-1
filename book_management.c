
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeNewLine(char* string) {

    size_t length = strlen(string);

    if((length > 0) && (string[length-1] == '\n')) {
        string[length-1] ='\0';
    }
    return;
}


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file){
    

}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookList *all_book){

    int x=1;
    Book *first,*last;
    CreateNode(first);     /* 建立附加头结点 */
    all_book->list = first;
    last=first;          /* last始终指向当前最后一个结点 */
    
    
    char line[100];
    
    int hang;
    
    while((fgets(line,100,file)) != NULL)
    { 
        removeNewLine(line);
        Book *p;
        CreateNode(p);
        //const char s[2] = "-";
        char* fenduan;
        fenduan=strtok(line, "-");
        p->id=(int)atoi(fenduan);

        fenduan=strtok(NULL, "-");
        p->title=(char*)malloc(sizeof(char)*80);
        //printf("%s\n",fenduan);
        strcpy(p->title,fenduan);

        fenduan=strtok(NULL, "-");
        p->authors=(char*)malloc(sizeof(char)*80);
        //printf("%s\n",fenduan);
        strcpy(p->authors,fenduan);

        fenduan=strtok(NULL, "-");
        p->year=(int)atoi(fenduan);
        
        fenduan=strtok(NULL, "-");
        p->copies=(int)atoi(fenduan);
        
        //printf("%d\t%s\t\t%s\t%d\t%d\n",p->id,p->title,p->authors,p->year,p->copies);
        
        last->next=p;last=p; /*新结点插入到链表结尾*/
        x++;        
    }
    
    last->next=NULL;        /*最后一个结点指针域赋值为NULL*/
    all_book->length=x;
    //BookList *k;
    //k=(BookList*)malloc(sizeof(BookList));
    //k->list=first;
    //k->length=x;
    return 0;

}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book){

}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book){

}

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title){

}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author){

}

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year){

}

//******************************************************
void printbook(BookList h)     /* h为头指针 */
{   
    
    Book *p=h.list->next;
    int interval=7;  
    /*p指向第一个数据结点, 如果链表不带附加头结点则p=h;*/
    //打印表头
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    /*printf("ID");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("Title");
    for(int i=1;i<=h.title_longest+interval-5;i++)printf(" ");
    printf("Author");
    for(int i=1;i<=h.authors_longest+interval-5;i++)printf(" ");
    printf("year");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("copies\n");*/

    while(p) 
    { 
        
        int tl=strlen(p->title);
        int al=strlen(p->authors);
        
        printf("%d\t%s\t%s\t%d\t%d\n",p->id,p->title,p->authors,p->year,p->copies);
        /*printf("%d",p->id);//这里只考虑了id小于10--
        for(int i=1;i<=interval+1;i++)printf(" ");
        printf("%s",p->title);
        for(int i=1;i<=h.title_longest+interval-tl;i++)printf(" ");
        printf("%s",p->authors);
        for(int i=1;i<=h.authors_longest+interval-tl;i++)printf(" ");
        printf("%d",p->year);
        for(int i=1;i<=interval;i++)printf(" ");
        printf("%d\n",p->copies);*/

        p=p->next; 
    }
    return;
} 

int main(){

    
    //char *title;
    //title=(char*)malloc(sizeof(char)*6);
    //scanf("%s",title);
    //int l=strlen(title);
    //printf("%s %d\n",title,l);
    //scanf("%s",title);
    //l=strlen(title);
    //printf("%s %d\n",title,l);
    //free((void *)title); 

    char* bookFile="book.txt";
    
    BookList *all_book = (BookList *)malloc( sizeof(BookList) );
    FILE *fp = NULL;
    fp = fopen(bookFile, "r");
    if(fp==NULL)
    {
    // use the error message and exit the program if it does not
    printf("Error\nBook file does not exist: %s\n",bookFile);
    exit(0);
    }
    else
    {
    load_books(fp, all_book);
    fclose(fp);
    
    }
    
    printbook(*all_book);
    free(all_book);
    return 0;
}