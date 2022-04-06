
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void first_book_get(BookList *p){
    //String longest value initialization
    p->authors_longest=0;
    p->title_longest=0;
    p->length=1;
    //Header node initialization
    p->list->id=10000;
    
    p->list->title=(char*)malloc(sizeof(char)*5);
    p->list->title="xuni";
    
    p->list->authors=(char*)malloc(sizeof(char)*5);
    p->list->authors="xuni";
    
    p->list->next=NULL;
    
    p->list->year=0000;
    p->list->copies=0;
}

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file,BookList *all_book){
    Book *last;
    last=all_book->list->next;
    
    while(last){

        fprintf(file,"%d-%s-%s-%d-%d\n", last->id,last->title,last->authors,last->year,last->copies);
        last=last->next;
    }
    return 0;
}

int store_users(FILE *file,UserList *all_user){
    User *last;
    last=all_user->list->next;
    if(strcmp(last->username,"librarian"))
    fprintf(file,"%s-%s\n", "librarian","librarian");
    while(last){
        fprintf(file,"%s-%s\n", last->username,last->password);
        last=last->next;
    }
    return 0;
}

int store_loans(FILE *file,UserList *all_user){
    User *last;
    last=all_user->list->next;

    while(last){
        fprintf(file,"%s", last->username);
        Book *p;
        p=last->loans->list->next;
        while(p){
            fprintf(file,"-%d", p->id);
            p=p->next;
        }
        fprintf(file,"\n");
        last=last->next;
    }
    return 0;
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
    CreateNode(first);     
    all_book->list = first;
    first_book_get(all_book);
    
    last=first;          
    
    char line[1024];
    while((fgets(line,1024,file)) != NULL)
    { 
        //removeNewLine(line);
        Book *p;

        CreateNode(p);
        //const char s[2] = "-";
        char* fenduan;
        fenduan=strtok(line, "-");
        p->id=(int)atoi(fenduan);

        fenduan=strtok(NULL, "-");
        p->title=(char*)malloc(sizeof(char)*(strlen(fenduan)+1));
        // printf("%s\n",fenduan);
        strcpy(p->title,fenduan);
        int l_title=strlen(p->title);
        if(l_title>all_book->title_longest) all_book->title_longest=l_title;

        fenduan=strtok(NULL, "-");
        p->authors=(char*)malloc(sizeof(char)*(strlen(fenduan)+1));
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
        last->next=p;last=p; 
        x++;        
    }
    /*last point is NULL*/
    last->next=NULL;        
    all_book->length=x;
    
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
    
    first=(User*)malloc(sizeof(User));
    all_user->list = first;

    //头节点虚拟初始化
    first->username="xuni";
    first->password="xuni";
    first->loans=NULL;
    
    // last always points to last pointer 
    last=first;         
    char line[1024];
    while((fgets(line,1024,file)) != NULL)
    { 
        //printf("%d %s\n",strlen(line),line);
        removeNewLine(line);
        //printf("%d %s\n",strlen(line),line);
        User *p;
        p=(User*)malloc(sizeof(User));
        //const char s[2] = "-";
        char* fenduan;
        fenduan=strtok(line, "-");
        p->username=(char*)malloc(sizeof(char)*(strlen(fenduan)+1));
        //printf("%s\n",fenduan);
        strcpy(p->username,fenduan);
        
        fenduan=strtok(NULL, "-");
        p->password=(char*)malloc(sizeof(char)*(strlen(fenduan)+1));
        //printf("%d %s\n",strlen(fenduan),fenduan);
        strcpy(p->password,fenduan);
        //printf("%s %d\n",p->password,strlen(p->password));

        p->loans=(BookList*)malloc(sizeof(BookList));
        p->loans->list=(Book*)malloc(sizeof(Book));
        first_book_get(p->loans);
        
        //printf("%s\t\t%s\n",p->username,p->password);
        
        //new pointer get to the last of booklist
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

int load_loans(FILE *file, UserList *all_user,BookList *all_book){
    if(file==NULL||all_user==NULL){
        return -2;
    }
    
    char line[1024];
    while((fgets(line,1024,file)) != NULL)
    { 
        removeNewLine(line);
        User *p=all_user->list->next;
        
        char* fenduan;
        fenduan=strtok(line, "-");
        
        //找到对应的user指针
        while(p){
            if(!strcmp(p->username,fenduan)){
                break;
            }
            p=p->next;
        }
        
        //实现添加,巧妙的数据结构
        while( fenduan != NULL ) {
            fenduan = strtok(NULL, "-");
            if(fenduan == NULL)break;
            int id=(int)atoi(fenduan);
            add_loans(id,2,p,all_book);
        }
      
    }
    
    return 0;
}

int add_loans(int id, int option,User* user,BookList *all_book){
    Book *last;
    last=all_book->list->next;
    

    while(last){
        if(last->id==id)
            break;
        last=last->next;
    }

    if(option==1){
        
        last->copies--;
    }
    if(last==NULL)return -2;
    //printf("%d\n",last->id);
    
    add_book(*last,user->loans);
    
    user->loans->length++;
    return 0;
}

int remove_loans(int id, User* user,BookList *all_book){
    Book *p,*last;
    last=user->loans->list->next;
    p=all_book->list->next;
    while(last->id==id){
        last=last->next;
    }
    while(p){
        if(p->id==id){
            p->copies++;
            break;
        }
        p=p->next;
    }
    remove_book(*last,user->loans);
    user->loans->length--;
    return 0;
}

int remove_loansBy_libraian(int id, UserList* all_user,BookList *all_book){
    User *p;
    p=all_user->list->next;
    while(p){
        Book* k=p->loans->list->next;
        int h_i=0;
        while(k)
        {
        if(k->id==id){
            h_i=1;
            break;
            }
        k=k->next;
        }
        if(h_i==1) remove_loans(id,p,all_book);
        p=p->next;
    }
    return 0;
}

int add_user(User user,UserList *all_user){

    User *p,*last;
    last=all_user->list;
    p=(User*)malloc(sizeof(User));

    p->username=(char*)malloc(sizeof(char)*(strlen(user.username)+1));
    strcpy(p->username,user.username);

    p->password=(char*)malloc(sizeof(char)*(strlen(user.password)+1));
    strcpy(p->password,user.password);

    p->loans=(BookList*)malloc(sizeof(BookList));
    p->loans->list=(Book*)malloc(sizeof(Book));
    first_book_get(p->loans);

    while(last->next){
        last=last->next;
    }
    last->next=p;
    p->next=NULL;
    all_user->length++;

    return 0;
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book,BookList *all_book){

   
    Book *p,*last;
    last=all_book->list;
    CreateNode(p);
    p->id=book.id;
    
    p->title=(char*)malloc(sizeof(char)*(strlen(book.title)+1));
    strcpy(p->title,book.title);
    int l_title=strlen(p->title);
    if(l_title>all_book->title_longest) all_book->title_longest=l_title;
    
    p->authors=(char*)malloc(sizeof(char)*(strlen(book.authors)+1));
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

    return 0;

}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book,BookList *all_book){
    //if (!all_book)
		//load_books(all_book);
    Book *p=all_book->list;
    int judge=1;
    while(p){
        if (book.id==p->next->id)
        {
            free(p->next->title);
            free(p->next->authors);
            Book *h=p->next;
            p->next=p->next->next;
            DeleteNode(h);
            all_book->length--;
            judge=0;
            break;
        }
        p=p->next;
    }
    if(judge==0)return 0;
    else return 1;
}

void delete_book(BookList *all_book){
    Book *p=all_book->list,*q;
    while(p)       /* p没有指向链表尾则循环 */
    {   
        q=p;                        /* 保存p */ 
        p=p->next;           /* p向前推进一个结点 */
        //free((void *)(q->title));
        //q->title=NULL;
        //free((void *)(q->authors));
        //q->authors=NULL;
        DeleteNode(q);             /* 删除结点*q */
    }
    return ;
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

//display all book
void printbook(BookList h,int option)    
{   
    
    Book *p=h.list->next;
    if(p==NULL&&option==1){
        printf("There have no book in this library!\n");
        return;
    }
    else if(p==NULL&&option==2){
        printf("You don't borrow book!\n");
        return;
    }
    int interval=7;  
    
    //printf the header
    
    printf("%-5s","ID");
    for(int i=1;i<=interval-5;i++)printf(" ");
    printf("Title");
    for(int i=1;i<=h.title_longest+interval-5;i++)printf(" ");
    printf("Author");
    for(int i=1;i<=h.authors_longest+interval-6;i++)printf(" ");
    printf("%-5s","year");
    if(option==1){
        for(int i=1;i<=interval;i++)printf(" ");
        printf("copies\n");
    }
    else if(option==2){
        printf("\n");
    }
    
    while(p) 
    { 
        int tl=strlen(p->title);
        int al=strlen(p->authors);
        
        //printf("%d\t%s\t%s\t%d\t%d\n",p->id,p->title,p->authors,p->year,p->copies);
        printf("%-5d",p->id);
        for(int i=1;i<=interval-5;i++)printf(" ");
        printf("%s",p->title);
        for(int i=1;i<=h.title_longest+interval-tl;i++)printf(" ");
        printf("%s",p->authors);
        for(int i=1;i<=h.authors_longest+interval-al;i++)printf(" ");
        printf("%-5d",p->year);

        if(option==1){
            for(int i=1;i<=interval;i++)printf(" ");
            printf("%d\n",p->copies);
        }
        else if(option==2){
            printf("\n");
        }

        p=p->next; 
    }
    return;
} 

/*
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

    char* bookFile="user.txt";
    
    //BookList *all_book = (BookList *)malloc( sizeof(BookList) );
    UserList *all_user = (UserList *)malloc( sizeof(UserList) );

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
        //load_books(fp, all_book);
        load_users(fp, all_user);
        
        fclose(fp);
        
    }
    
    //printbook(*all_book);
    //SearchBook( all_book );
    //add_book(input_add_book(all_book),all_book);
    //remove_book((input_remove_book(all_book)),all_book);
     
    //printbook(*all_book);
    //fp = fopen(bookFile, "w+");
    //store_books(fp,all_book);
    //fclose(fp);

    //search 测试
    //const char *title_test="Harry";
    //char title_test[80]="Harry";
    //const char *author_test="asdff";
    //unsigned int year_test=1997;
    //printbook(find_book_by_title (title_test,all_book));
    //printbook(find_book_by_author (author_test,all_book));
    //printbook(find_book_by_year (year_test,all_book));
    //user 测试
    
    printf("%s\t\t%s\n",all_user->list->next->username,all_user->list->next->password);
    //free(all_book);
    free( all_user );

    //char* name;
    //name=(char*)malloc(sizeof(char)*80);
    //fgets(name,80,stdin);
    //printf("%s %ld\n",name,strlen(name));
    return 0;
}
*/