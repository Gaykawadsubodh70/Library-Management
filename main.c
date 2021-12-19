#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void login();
void sign_up();
void login_interface();
void home();
char name[20];
char user_name1[20]="Subodh@123",pass1[20]="Pass@123";

int main()
{
    login_interface();
    home();
}

void home()
{

}

void login_interface()
{
    int ch=0;
    while(ch!=4)
    {
        printf("\n\n");
        printf("\n***** Welcome to Central Library *****\n");
        printf("\n\n");
        printf("        1. Login\n");
        printf("        2. Sign Up\n");
        printf("        3. Exit\n");
        printf("\n");
        scanf("%d",&ch);
        printf("***************************************\n");

        

        switch (ch)
        {
        case 1: login();
            break;
        case 2: sign_up();
            break;
        case 3: exit(0);
            break;
        
        default: printf("\nEnter a valid choice");
            break;
        }
    }
    return;
}

void login()
{
    char user_name[20],pass[20];
    printf("\nEnter a username : ");
    scanf("%s",user_name);
    printf("\nEnter a password : ");
    scanf("%s",pass);
    if(strcmp(user_name,user_name1)&&strcmp(pass,pass1))
    printf("\n\n       login failed       \n");
    else
    {
        printf("\n\n       login succesfully        \n");
    }
     
}

void sign_up()
{

    printf("\nEnter a name : ");
    scanf("%s",name);
    printf("\nset username : ");
    scanf("%s",user_name1);
    printf("\nset password : ");
    scanf("%s",pass1);

    printf("\n\n       Your details are saved succesfully        \n");
}