
#include "string.h"
#include "book_management.h"

#define CreateNode(p)  p=(Book*)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p); 

/*Initialize the linked list*/
BookList* lookbook()                        
{ 
    int x;Book *first,*p,*last;
    CreateNode(first);     /* 建立附加头结点 */
    last=first;                    /* last始终指向当前最后一个结点 */
    while(1)
    { scanf("%d",&x);if(!x) break; /* 输入x为0则退出循环 */
       CreateNode(p);p->data=x;   /* 建立一个新结点 */
       last->next=p;last=p;         /*新结点插入到链表结尾*/
    }
    last->next=NULL;        /*最后一个结点指针域赋值为NULL*/
    BookList *k;
    k=(BookList*)malloc(sizeof(BookList));
    k->list=first;
    k->length=x;
    return k;
} 

/*add new poit to list*/
Book addbook(Book *h)      /* h 传入单链表头结点指针*/
{  
    Book *p=h->next;
    h->next=p->next;
    DeleteNode(p);
}

/*delet the linked list*/
Book deletallbook(Book *h)      /* h 传入单链表头结点指针*/
{  
    Book *p=h,*q;
    while(p!=NULL)       /* p没有指向链表尾则循环 */
    { q=p;                                 /* 保存p */ 
        p=p->next;                      /* p向前推进一个结点 */
        DeleteNode(q);               /* 删除结点*q */
    }
    return NULL;
} 
/*print all the book information*/
void printbook(BookList h)     /* h为头指针 */
{   
    Book *p=h.list->next;
    int interval=7;  
    /*p指向第一个数据结点, 如果链表不带附加头结点则p=h;*/
    //打印表头
    printf("ID");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("Title");
    for(int i=1;i<=h.title_longest+interval-5;i++)printf(" ");
    printf("Author");
    for(int i=1;i<=h.authors_longest+interval-5;i++)printf(" ");
    printf("year");
    for(int i=1;i<=interval;i++)printf(" ");
    printf("copies\n");

    while(p) 
    { 
        int tl=strlen(p->title);
        int al=strlen(p->authors);

        printf("%d",p->id);//这里只考虑了id小于10--
        for(int i=1;i<=interval+1;i++)printf(" ");
        printf("%s",p->title);
        for(int i=1;i<=h.title_longest+interval-tl;i++)printf(" ");
        printf("%s",p->authors);
        for(int i=1;i<=h.authors_longest+interval-tl;i++)printf(" ");
        printf("%d",p->year);
        for(int i=1;i<=interval;i++)printf(" ");
        printf("%d\n",p->copies);

        p=p->next; 
    }
} 
/*delet one book*/
void deletbook(Book *h)     /* h为头指针 */
{   
    Book *p=h->next;
    h->next=p->next;
    DeleteNode(p);
        
} 
