
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

void first_book_get(BookList *p){
    //最长值初始化
    p->authors_longest=0;
    p->title_longest=0;
    p->length=1;
    //头节点虚拟初始化
    p->list->id=10000;
    
    p->list->title="xuni";
    //strcpy(p->title,book.title);
    
    p->list->authors="xuni";
    //strcpy(p->authors,book.authors);
    
    p->list->year=0000;
    p->list->copies=0;
}

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file,BookList *all_book){
    

}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookList *all_book){

    if(file == NULL||all_book == NULL){
        return -2;
    }

    int x=1;
    Book *first,*last;
    CreateNode(first);     /* 建立附加头结点 */
    all_book->list = first;
    first_book_get(all_book);
    
    last=first;          /* last始终指向当前最后一个结点 */
    //最长值初始化
    all_book->authors_longest=0;
    all_book->title_longest=0;
    
    char line[100];
    while((fgets(line,100,file)) != NULL)
    { 
        //removeNewLine(line);
        Book *p;

        CreateNode(p);
        //const char s[2] = "-";
        char* fenduan;
        fenduan=strtok(line, "-");
        p->id=(int)atoi(fenduan);

        fenduan=strtok(NULL, "-");
        p->title=(char*)malloc(sizeof(char)*80);
        // printf("%s\n",fenduan);
        strcpy(p->title,fenduan);
        int l_title=strlen(p->title);
        if(l_title>all_book->title_longest) all_book->title_longest=l_title;

        fenduan=strtok(NULL, "-");
        p->authors=(char*)malloc(sizeof(char)*80);
        //printf("%s\n",fenduan);
        strcpy(p->authors,fenduan);
        int l_authors=strlen(p->authors);
        if(l_authors>all_book->authors_longest) all_book->authors_longest=l_authors;

        fenduan=strtok(NULL, "-");
        p->year=(int)atoi(fenduan);
        
        fenduan=strtok(NULL, "-");
        p->copies=(int)atoi(fenduan);
        //test
        //printf("%d\t%s\t\t%s\t%d\t%d\n",p->id,p->title,p->authors,p->year,p->copies);
        /*新结点插入到链表结尾*/
        last->next=p;last=p; 
        x++;        
    }
    /*最后一个结点指针域赋值为NULL*/
    last->next=NULL;        
    all_book->length=x;
    //BookList *k;
    //k=(BookList*)malloc(sizeof(BookList));
    //k->list=first;
    //k->length=x;
    return 0;

}

//load users to list
int load_users(FILE *file, UserList *all_user)
{
    if(file==NULL||all_user==NULL){
        return -2;
    }
    int x=1;
    User *first,*last;
    /* 建立附加头结点 */
    first=(User*)malloc(sizeof(User));
    all_user->list = first;
    last=first;          /* last始终指向当前最后一个结点 */
    char line[100];
    while((fgets(line,100,file)) != NULL)
    { 
        removeNewLine(line);
        User *p;
        p=(User*)malloc(sizeof(p));
        //const char s[2] = "-";
        char* fenduan;
        fenduan=strtok(line, "-");
        p->username=(char*)malloc(sizeof(char)*80);
        // printf("%s\n",fenduan);
        strcpy(p->username,fenduan);
        
        fenduan=strtok(NULL, "-");
        p->password=(char*)malloc(sizeof(char)*80);
        //printf("%s\n",fenduan);
        strcpy(p->password,fenduan);
           
        //printf("%s\t\t%s\n",p->username,p->password);
        
        /*新结点插入到链表结尾*/
        last->next=p;last=p; 
        x++;        
    }
    /*最后一个结点指针域赋值为NULL*/
    last->next=NULL;        
    all_user->length=x;
    //BookList *k;
    //k=(BookList*)malloc(sizeof(BookList));
    //k->list=first;
    //k->length=x;
    return 0;

}
//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book,BookList *all_book){

    Book *p,*last;
    last=all_book->list;
    CreateNode(p);
    p->id=book.id;
    
    p->title=(char*)malloc(sizeof(char)*80);
    strcpy(p->title,book.title);
    int l_title=strlen(p->title);
    if(l_title>all_book->title_longest) all_book->title_longest=l_title;
    
    p->authors=(char*)malloc(sizeof(char)*80);
    strcpy(p->authors,book.authors);
    int l_authors=strlen(p->authors);
    if(l_authors>all_book->authors_longest) all_book->authors_longest=l_authors;

    p->year=book.year;
    p->copies=book.copies;

    while(last->next){
        last=last->next;
    }
    last->next=p;
    p->next=NULL;
    all_book->length++;



}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book,BookList *all_book){
    //if (!all_book)
		//load_books(all_book);
    Book *p=all_book->list;
    int judge=0;
    while(p){
        if (book.id==p->next->book_id)
        {
            Book *h=p->next;
            p->next=h->next;
            DeleteNode(h);
            judge=1;
            break;
        }
        p=p->next;
    }
    if(judge==1)return 1;
    else return 0;
}

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title,BookList *all_book){
    //if (!all_book)
		//load_books(all_book);
    Book *p=all_book->list->next;
    BookList *find_book = (BookList *)malloc( sizeof(BookList) );

    int x=1;
    Book *first;
    CreateNode(first);     /* 建立附加头结点 */
    find_book->list = first;
    first_book_get(find_book);

    while(p){
        if (!strcmp(p->title,title))
        {
            add_book(*p,find_book);
        }
        p=p->next;
    }

	return *find_book;
}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author,BookList *all_book){
    //if (!all_book)
		//load_books(all_book);
    Book *p=all_book->list->next;
    BookList *find_book = (BookList *)malloc( sizeof(BookList) );

    int x=1;
    Book *first;
    CreateNode(first);     /* 建立附加头结点 */
    find_book->list = first;
    first_book_get(find_book);
    
    while(p){
        if (!strcmp(p->authors,author))
        {
            add_book(*p,find_book);
        }
        p=p->next;
    }

	return *find_book;

}

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year,BookList *all_book){
    //if (!all_book)
		//load_books(all_book);
    Book *p=all_book->list->next;
    BookList *find_book = (BookList *)malloc( sizeof(BookList) );

    int x=1;
    Book *first;
    CreateNode(first);     /* 建立附加头结点 */
    find_book->list = first;
    first_book_get(find_book);
    
    while(p){
        if (p->year==year)
        {
            add_book(*p,find_book);
        }
        p=p->next;
    }

	return *find_book;

}

//******************************************************
void printbook(BookList h)     /* h为头指针 */
{   
    
    Book *p=h.list->next;
    int interval=7;  
    /*p指向第一个数据结点, 如果链表不带附加头结点则p=h;*/
    //打印表头
    //printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    printf("ID");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("Title");
    for(int i=1;i<=h.title_longest+interval-5;i++)printf(" ");
    printf("Author");
    for(int i=1;i<=h.authors_longest+interval-6;i++)printf(" ");
    printf("year");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("copies\n");

    while(p) 
    { 
        
        int tl=strlen(p->title);
        int al=strlen(p->authors);
        
        //printf("%d\t%s\t%s\t%d\t%d\n",p->id,p->title,p->authors,p->year,p->copies);
        printf("%d",p->id);//这里只考虑了id小于10--
        for(int i=1;i<=interval+1;i++)printf(" ");
        printf("%s",p->title);
        for(int i=1;i<=h.title_longest+interval-tl;i++)printf(" ");
        printf("%s",p->authors);
        for(int i=1;i<=h.authors_longest+interval-al;i++)printf(" ");
        printf("%d",p->year);
        for(int i=1;i<=interval;i++)printf(" ");
        printf("%d\n",p->copies);

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
    //UserList *all_user = (UserList *)malloc( sizeof(UserList) );

    FILE *fp = NULL;
    fp = fopen(bookFile, "r");
    if(fp==NULL)
    {
        //use the error message and exit the program if it does not
        printf("Error\nBook file does not exist: %s\n",bookFile);
        exit(0);
    }
    else
    {
        load_books(fp, all_book);
        //load_users(fp, all_user);
        fclose(fp);}
    
    printbook(*all_book);
    //search 测试
    //const char *title_test="Harry";
    //const char *author_test="asdff";
    //unsigned int year_test=1997;
    //printbook(find_book_by_title (title_test,all_book));
    //printbook(find_book_by_author (author_test,all_book));
    //printbook(find_book_by_year (year_test,all_book));
    //user 测试
    //printf("%s\t\t%s\n",all_user->list->next->username,all_user->list->next->password);
    free(all_book);
    //free( all_user );
    return 0;
}