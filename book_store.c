#include "book_management.h"

#define CreateNode(p)  p=(Book*)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p); 

/*Initialize the linked list*/
BookList lookbook()                        
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
    BookList K;
    K.list=first;
    K.length=x;
    return K;
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
void printbook(Book *h)     /* h为头指针 */
{   
    Book *p=h->next;  
    /*p指向第一个数据结点, 如果链表不带附加头结点则p=h;*/
    printf("ID Title Author year copies");
     while(p) 
    { 
        printf("%4d %s %s %4d %4d\n",p->id,p->title,p->authors,p->year,p->copies);
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
