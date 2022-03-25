#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"

void reg(UserList* ul)
{
    User login_user;
    char name[80],password[80];
    printf("Please enter a username: ");
    fgets(name,80,stdin);
    printf("Please enter a password: ");
    fgets(password,80,stdin);
    int judge=1;
    User *p=ul->list->next;
    //find if the name is avaible
    for(int i=1;i<=ul->length-1;i++)
    {
        if(!strcmp(p->username,name))
        {
            judge=0;
            break;
        }
        else
        {
            p=p->next;
        }
    }
    if(judge==0||!strcmp(p->username,"librarian"))
    {
        printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
    }
    else if( !strcmp(p->username,"")||!strcmp(p->password,""))
    {
        printf("Sorry, registration unsuccessful, the username or password can't be blank.\n");
    }
    else if(judge==1)
    {
        //导入近user.txt或者先放入用户链表中。

        login_user.username=(char*)malloc(sizeof(char)*80);
        // printf("%s\n",fenduan);
        strcpy(login_user.username,name);
        
        login_user.password=(char*)malloc(sizeof(char)*80);
        //printf("%s\n",fenduan);
        strcpy(login_user.password,password);
        login_user.loans=NULL;
           
        add_user(login_user,ul);
    }
    return;
}

User* login(UserList* ul)
{
    char name[80],password[80];
    printf("Please enter your username: ");
    fgets(name,80,stdin);
    printf("Please enter your password: ");
    fgets(password,80,stdin);
    int judge=0;
    User *p=ul->list->next;
    //find if the user is exist
    for(int i=1;i<=ul->length-1;i++)
    {
        if(!strcmp(p->username,name))
        {
            if(!strcmp(p->password,password)){
               judge=1; 
               break;
            }  
        }
        else
        {
            p=p->next;
        }
    }
    if(!strcmp(p->username,"librarian")&&!strcmp(p->password,"librarian"))
        judge=2;
    if(judge==0)
    {
        printf("Sorry, login unsuccessful, the username and password you entered are not exists.\n");
        return NULL;
    }
    else if(judge==2)
    {
        User* admin;
        admin->username="librarian";
        admin->password="librarian";
        admin->loans=NULL;
        return admin;
    }
    else if(judge==1)return p;
    

}
