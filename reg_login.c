#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

void reg(UserList* ul)
{
    User login_user;
    char name[1024],password[1024];
    printf("Please enter a username: ");
    fgets(name,1024,stdin);
    removeNewLine(name);
    printf("Please enter a password: ");
    fgets(password,1024,stdin);
    removeNewLine(password);
    
    int judge=1;
    User *p=ul->list->next;
    int c='-';
    if( strlen(name)==0||strlen(password)==0)
    {
        printf("Sorry, registration unsuccessful, the username or password can't be blank.\n");
        return;
    }
    else if(strchr(name,c)!=NULL||(strchr(password,c)!=NULL))
    {
        printf("Sorry, registration unsuccessful, the username or password can't have \'-\' .\n");
        return;
    }
    for(int i=0;i<strlen(name)-1;i++){
        if(name[i]==' '&&name[i+1]==' '){
            printf("Sorry,the username can't have two or more consecutive Spaces.\n");
            return;
        }
    }
    for(int i=0;i<strlen(password)-1;i++){
        if(password[i]==' '&&password[i+1]==' '){
            printf("Sorry,the password can't have two or more consecutive Spaces.\n");
            return;
        }
    }
    //find if the name is avaible
    while(p)
    {
        if(!strcmp(p->username,name))
        {
            judge=0;
            break;
        }
        
        p=p->next;  
    }
    
    if(judge==0||(!strcmp(name,"librarian")))
    {
        printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
    }
    else if(judge==1)
    {
        //放入用户链表中。
        printf("add\n");
        login_user.username=(char*)malloc(sizeof(char)*(strlen(name)+1));
        // printf("%s\n",fenduan);
        strcpy(login_user.username,name);
        
        login_user.password=(char*)malloc(sizeof(char)*(strlen(password)+1));
        //printf("%s\n",fenduan);
        strcpy(login_user.password,password);
        login_user.loans=NULL;
        login_user.next=NULL;
           
        add_user(login_user,ul);
        printf("registe succuess!");
    }
    return;
}

User* login(UserList* ul)
{
    char name[1024],password[1024];
    printf("Please enter your username: ");
    fgets(name,1024,stdin);
    removeNewLine(name);
    printf("Please enter your password: ");
    fgets(password,1024,stdin);
    
    removeNewLine(password);
    //printf("%d %s\n",strlen(password),password);
    int judge=0;
    User *p=ul->list->next;
    //find if the user is exist
    while(p)
    {
        //printf("%s\t%s\n",p->password,p->username);
        //printf("%d\t%d\n",strlen(password),strlen(p->password));
        //for(int i=0;i<strlen(p->password);i++){
            //printf("%c\n",p->password[i]);}
        //printf("%d\n",strncmp(password, p->password, strlen(password)));
        //printf("%d %d\n",(!strcmp(p->username,name)),(!strncmp(password, p->password, strlen(password))));
        if(!strcmp(p->username,name))
        {
            //printf("%s\t%s\n",p->username,p->password);
            if(!strncmp(password, p->password, strlen(p->password))){
               judge=1;
               break;
            }  
        }
        
        p=p->next;
        
    }
    if((!strcmp(name,"librarian"))&&(!strcmp(password,"librarian")))
    {   
        judge=2;
        
    }
    if(judge==0)
    {
        printf("Sorry, login unsuccessful, the username and password you entered are not exists.\n");
        return NULL;
    }
    else if(judge==2)
    {
        User* admin;
        admin=malloc(sizeof(User));
        
        admin->username="librarian";
        admin->password="librarian";
        admin->next=NULL;
        admin->loans=NULL;
        
        return admin;
    }
    else if(judge==1)
    return p;
    
}
