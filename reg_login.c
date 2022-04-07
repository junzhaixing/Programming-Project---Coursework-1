#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

//user register
void reg(UserList* ul)
{
    User login_user;
    char name[1024],password[1024];
    printf("\nPlease enter a username: ");
    fgets(name,1024,stdin);
    removeNewLine(name);
    printf("Please enter a password: ");
    fgets(password,1024,stdin);
    removeNewLine(password);
    
    int judge=1;
    User *p=ul->list->next;
    int c='-';
    //find if the username have blank
    if( strlen(name)==0||strlen(password)==0)
    {
        printf("Sorry, registration unsuccessful, the username or password can't be blank.\n");
        return;
    }
    //find if the username and password have '-'
    else if(strchr(name,c)!=NULL||(strchr(password,c)!=NULL))
    {
        printf("Sorry, registration unsuccessful, the username or password can't have \'-\' .\n");
        return;
    }
    //find if the username and password have two or more consecutive Spaces
    for(int i=0;i<strlen(name)-1;i++){
        if(name[i]==' '&&name[i+1]==' '){
            printf("Sorry,the username can't have two or more consecutive Spaces.\n");
            return;
        }
    }
    //find if the password have two or more consecutive Spaces
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
    //find if the username is librarian
    if(judge==0||(!strcmp(name,"librarian")))
    {
        printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
    }
    else if(judge==1)
    {
        //put new user to user link List 
        login_user.username=(char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(login_user.username,name);
        login_user.password=(char*)malloc(sizeof(char)*(strlen(password)+1));
        strcpy(login_user.password,password);
        login_user.loans=NULL;
        login_user.next=NULL;
           
        add_user(login_user,ul);
        printf("Registered library account succuessfully!\n");
    }
    return;
}

//get user login
User* login(UserList* ul)
{
    char name[1024],password[1024];
    printf("\nPlease enter your username: ");
    fgets(name,1024,stdin);
    removeNewLine(name);
    printf("Please enter your password: ");
    fgets(password,1024,stdin);
    
    removeNewLine(password);
    int judge=0;
    User *p=ul->list->next;
    //find if the user is exist
    while(p)
    {
        if(!strcmp(p->username,name))
        {
            if(!strcmp(password, p->password)){
               judge=1;
               break;
            }  
        }
        p=p->next;
    }
    //judge if the user is librarian
    if((!strcmp(name,"librarian"))&&(!strcmp(password,"librarian")))
    {   
        judge=2; 
    }
    //return the information for difference condition
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
    else if(judge==1){
        return p;
    }
    return NULL;    
}
