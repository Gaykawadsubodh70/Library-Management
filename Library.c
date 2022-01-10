
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_NAME 50

// Login creditial
#define MAX_USER_NAME 30
#define MAX_PASSWORD_LENGTH 20

// File name
#define FILE_NAME "Libray Data.bin"


#define FILE_SIZE sizeof(Book_info)
typedef struct{
    int year;
    int month;
    int day;
}DATE;
typedef struct
{
    int book_id;
    char bookName[MAX_SIZE_NAME];
    char AuthorName[MAX_SIZE_NAME];
    char StudentName[MAX_SIZE_NAME];
    int Student_Adress[MAX_SIZE_NAME];
    int quantity;
    DATE issueDate;
} Book_info;

typedef struct
{
    char userName[MAX_USER_NAME];
    char password[MAX_PASSWORD_LENGTH];
} Login_info;

void Welcome()
{ // SHOW BANNER
    printf("\n\n\n");
    printf("\n\t\t\t *****----****----****----****----****----****----****--**\n");
    printf("\n\t\t\t          ========================================          ");
    printf("\n\t\t\t          =                WELCOME               =          ");
    printf("\n\t\t\t          =                  TO                  =          ");
    printf("\n\t\t\t          =               LIBRARY                =          ");
    printf("\n\t\t\t          =              MANAGEMENT              =          ");
    printf("\n\t\t\t          =                SYSTEM                =          ");
    printf("\n\t\t\t          ========================================          ");
    printf("\n");
    printf("\n\t\t\t *****----****----****----****----****----****----****--**\n");
    printf("\n\t\t\tPress Any Key to Continue");
    getch();
}

void Main_menu()
{ /// MAIN MENU AFTER SUCCEFULL LOGIN

    int choice=0;
    do
    {
    printf("\n\t\t\t1.ADD BOOK");
    printf("\n\t\t\t2.SHOW BOOKS");
    printf("\n\t\t\t3.DELETE BOOK");
    printf("\n\t\t\t4.SEARCH BOOK");
    printf("\n\t\t\t0.EXIT");
    printf("\n\t\t\tEnter Your Choice: "); 
    scanf("%d", &choice);
        switch (choice)
        {
        case 1:Add_BOOK();
            break;
        case 2: Veiw_Books();
            break;
        case 3: delete_book();
            break;
        case 4: Search_book();
            break;
        case 0:
        printf("Thank you for using");
        exit(0);
            break;

        default:
            printf("\n\t\t\tEnter Valid Choice");
        }
    } while (choice != 0);
}
void Add_BOOK()
{
    Book_info Book = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%d",&Book.book_id);

    printf("\n\t\t\tBook Name  = ");
    fflush(stdin);
    fgets(Book.bookName,MAX_SIZE_NAME,stdin);

    printf("\n\t\t\tAuthor Name  = ");
    fflush(stdin);
    fgets(Book.AuthorName,MAX_SIZE_NAME,stdin);

    printf("\n\t\t\tQuantity  = ");
    fflush(stdin);
    scanf("%d",&Book.quantity);
    // printf("\n\t\t\tStudent Name  = ");
    // fflush(stdin);
    // fgets(Book.StudentName, MAX_SIZE_NAME, stdin);

    printf("\n\t\t\tEnter date in format (day/month/year): ");
    scanf("%d/%d/%d",&Book.issueDate.day,&Book.issueDate.month,&Book.issueDate.year);
    //subodh edited this line
    
    printf("\n\t\t\t BOOK ADDED SUCCFULLY!!\n\n");
    fwrite(&Book, sizeof(Book), 1, fp);
    fclose(fp);
    Main_menu();
}

void Veiw_Books(){
    int found =0;
    FILE *fp=NULL;
    Book_info showBook={0};

    fp= fopen(FILE_NAME,"rb");

    if(fp==NULL){
        printf("File is not opened\n");
        exit(1);
    }
    printf("\n\t\t\tBOOK LIST");
    printf("\n\t\t\t-----------------------------------------------------------------------------------------\n");
    printf("\t\t\t Id   Book Name                      Author Name                    Quantity Issued Date\n");
    while(fread(&showBook,sizeof(showBook),1,fp)){

        remove_newline_ch(showBook.bookName);
        remove_newline_ch(showBook.AuthorName);
        
        printf("\n\t\t\t %-4d %-30s %-30s   %-6d %d/%d/%d",showBook.book_id,showBook.bookName,showBook.AuthorName,showBook.quantity,showBook.issueDate.day,showBook.issueDate.month,showBook.issueDate.year);
        printf("\n\t\t\t-----------------------------------------------------------------------------------------\n");
        found =1;
    }
    fclose(fp);
    if(!found){
        printf("\n\t\t\t No Record");
    }
    printf("\n\t\t\tPress Any Key to go in main menu....");
        fflush(stdin);

    getchar();
}
void delete_book(){
    int found=0;
    FILE *fp=NULL;
    FILE *temp=NULL;
    int delete;
    Book_info Book={0};
    fp= fopen(FILE_NAME,"rb");
     if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    temp=fopen("tmp.bin","wb");
     if(temp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    printf("\n\t\t\tDELETE BOOK");
    printf("\n\t\t\t-------------------------------------------------------------------------\n");
    printf("\n\t\t\tEnter BOOK ID. for DELETE: ");
    scanf("%d",&delete);

    while(fread(&Book,sizeof(Book),1,fp)){
        if(Book.book_id!= delete){
            fwrite(&Book,sizeof(Book),1,temp);
        }
        else{
            found =1;
        }
    }
    if(!found){
        printf("\n\t\t\tBOOK NOT FOUND or check book id");
    }
    else{
        printf("\n\t\t\tBOOK DELETED SUCEFULLY....");
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);

}
void Search_book()
{
    Book_info showBook={0};
    FILE *fp=NULL;
    //clrscr();
    int found=0;
    int id;
    printf("1.Search by Id\n");
    printf("2.Search by Name\n");
    fp=fopen(FILE_NAME,"rb+");
    rewind(fp);
    switch(getch())
    {
        case '1':
        {
            //clrscr();
            printf("Search Book by Id\n\n");
            printf("Enter book id : \n");
            scanf("%d",&id);
            while(fread(&showBook,sizeof(showBook),1,fp)==1)
            {
                if(showBook.book_id==id)
                {
                    printf("The book is available \n");
                    printf("\n\t\t\t--------------------------------------------------------------------------------\n");
                    remove_newline_ch(showBook.bookName);
                    remove_newline_ch(showBook.AuthorName);
                    printf("\t\t\t Id   Book Name                      Author Name                    Quantity Issued Date\n");
                    printf("\n\t\t\t %-4d %-30s %-30s   %-6d %d/%d/%d",showBook.book_id,showBook.bookName,showBook.AuthorName,showBook.quantity,showBook.issueDate.day,showBook.issueDate.month,showBook.issueDate.year);
                    printf("\n\t\t\t--------------------------------------------------------------------------------\n");
                    found =1;
                }
            }
            if(found!=0)
            {
                printf("no record found \n");
            }
            Main_menu();
            break;

        }

        case '2':
        {
            char str[MAX_SIZE_NAME];
            //clrscr();
            printf("search by Name \n\n");
            printf("Enter book name \n\n");
            scanf("%s",str);
            int id=0;
            while(fread(&showBook,sizeof(showBook),1,fp)==1)
            {
                if(strcmp(showBook.bookName,(str))==0);
                {
                    printf("The book is available \n");
                    printf("\n\t\t\t--------------------------------------------------------------------------------\n");
                    remove_newline_ch(showBook.bookName);
                    remove_newline_ch(showBook.AuthorName);
                    printf("\t\t\t Id   Book Name                      Author Name                    Quantity Issued Date\n");
                    printf("\n\t\t\t %-4d %-30s %-30s   %-6d %d/%d/%d",showBook.book_id,showBook.bookName,showBook.AuthorName,showBook.quantity,showBook.issueDate.day,showBook.issueDate.month,showBook.issueDate.year);
                    found++;
                }
            }
            if(found!=0)
            {
                printf("no record found \n");
            }
            Main_menu();
            break;

        }
        default:
                getch();
                Search_book();
    
    }
    fclose(fp);
}
int main()
{
    Welcome();
    Main_menu();
    return 0;
}
void remove_newline_ch(char *line)
{
    int new_line=strlen(line)-1;
    if(line[new_line]=='\n')
        line[new_line]='\0';
    return(line);
}
