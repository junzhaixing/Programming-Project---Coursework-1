#include <stdio.h>

#include <string.h>

#include <book_management.h>

void reg(UserList ul)
{
    char name[80],password[80];
    printf("Please enter a username: ");
    fgets(name,80,stdin);
    printf("Please enter a password: ");
    fgets(password,80,stdin);
    int judge=1;
    User *p=ul.list->next;
    //find if the name is avaible
    for(int i=1;i<=ul.length;i++)
    {
        if(p->username==name)
        {
            judge=0;
            break;
        }
        else
        {
            p=p->next;
        }
    }
    if(judge==0)
    {
        printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
    }
    else if(judge==1)
    {
        //导入近user.txt或者先放入用户链表中。
    }
}

int login(UserList ul)
{
    char name[80],password[80];
    printf("Please enter your username: ");
    fgets(name,80,stdin);
    printf("Please enter your password: ");
    fgets(password,80,stdin);
    int judge=1;
    User *p=ul.list->next;
    //find if the user is exist
    for(int i=1;i<=ul.length;i++)
    {
        if(p->username==name)
        {
            judge=0;
            break;
        }
        else
        {
            p=p->next;
        }
    }
    if(judge==0)
    {
        printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
    }
    else if(judge==1)
    {
        //导入近user.txt或者先放入用户链表中。
    }

}
