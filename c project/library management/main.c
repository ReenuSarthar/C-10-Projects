#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
}b;

struct student{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
}s;

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
         printf("\n\n\n");
        printf("\t\t\t\t***********Welcome to Innovaskill Library***************\n");
        printf("\n");
        printf("\t\t\t\t\t<== Library Management System ==>\n");
        printf("\n\n\n");
        printf("\t\t\t\t\t*********************************\n");
        printf("\t\t\t\t\t*\t1.Add Book\t\t*\n");
        printf("\t\t\t\t\t*\t2.Books List\t\t*\n");
        printf("\t\t\t\t\t*\t3.Remove Book\t\t*\n");
        printf("\t\t\t\t\t*\t4.Issue Book\t\t*\n");
        printf("\t\t\t\t\t*\t5.Issued Book List\t*\n");
        printf("\t\t\t\t\t*\t0.Exit\t\t\t*\n");
        printf("\t\t\t\t\t*********************************\n");
         printf("\n\n\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;

        default:
            printf("\t\t\t\t\tInvalid Choice...\n\n");

        }
        printf("\n\t\t\t\t\tPress Any Key To Continue...");
        getch();
    }

    return 0;
}


void addBook(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("\t\t\t\t\tEnter book id: ");
    scanf("%d", &b.id);

    printf("\t\t\t\t\tEnter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("\t\t\t\t\tEnter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("\t\t\t\t\tBook Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}


void booksList(){

    system("cls");
    printf("\t\t\t\t\t\t<== Available Books ==>\n\n");
    printf("\t\t\t%s\t\t%s \t\t%s \t\t\t   %s\n\n", "Book id", "Book Name", "Author", "Date");
    printf("\t\t\t--------------------------------------------------------------------------\n");
    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("\t\t\t%d\t\t%s \t\t\t%s \t\t\t%s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del(){
    int id, f=0;
    system("cls");
    printf("\t\t\t\t\t<== Remove Books ==>\n\n");
    printf("\t\t\t\t\tEnter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(id == b.id){
            f=1;
        }else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if(f==1){
        printf("\n\n\t\t\t\t\tDeleted Successfully.");
    }else{
        printf("\n\n\t\t\t\t\tRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");

}


void issueBook(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f=0;

    system("cls");
    printf("\t\t\t\t\t<== Issue Books ==>\n\n");

    printf("\t\t\t\t\tEnter Book id to issue: ");
    scanf("%d", &s.id);

    //Check if we have book of given id
    fp = fopen("books.txt", "rb");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        if(b.id == s.id){
            strcpy(s.bookName, b.bookName);
            f=1;
            break;
        }
    }

    if(f==0){
        printf("\t\t\t\t\tNo book found with this id\n");
        printf("\t\t\t\t\tPlease try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("\t\t\t\t\tEnter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("\t\t\t\t\tEnter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("\t\t\t\t\tEnter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("\t\t\t\t\tBook Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList(){
    system("cls");
/*  printf("\t\t\t\t\t\t<== Available Books ==>\n\n");
    printf("\t\t\t%s\t\t%s \t\t%s \t\t\t   %s\n\n", "Book id", "Book Name", "Author", "Date");
    printf("\t\t\t--------------------------------------------------------------------------\n");
    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("\t\t\t%d\t\t%s \t\t\t%s \t\t\t%s\n", b.id, b.bookName, b.authorName, b.date);*/
    printf("\t\t\t\t\t\t<== Book Issue List ==>\n\n");

    printf("\t%s \t\t%s \t\t%s \t\t%s \t\t%s \t\t%s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");
    printf("\t------------------------------------------------------------------------------------------------\n");
    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("\t%d \t\t%s \t\t%s \t%d \t\t%s \t\t         %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
