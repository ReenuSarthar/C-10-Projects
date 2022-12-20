#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct patient{
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char date[12];
}p;

struct doctor{
    int id;
    char name[50];
    char address[50];
    char specialize[50];
    char date[12];
}d;

FILE *fp;

int main(){

    int ch;
    while(1){
        system("cls");
        printf("\t\t\t\t***********Welcome to R.K Hospital**************\n");
        printf("\n");
        printf("\t\t\t\t\t<== Hospital Management System ==>\n");
        printf("\n\n\n");
        printf("\t\t\t\t\t*********************************\n");
        printf("\t\t\t\t\t*\t1.Admit Patient\t\t*\n");
        printf("\t\t\t\t\t*\t2.Patient List\t\t*\n");
        printf("\t\t\t\t\t*\t3.Discharge Patient\t*\n");
        printf("\t\t\t\t\t*\t4.Add Doctor\t\t*\n");
        printf("\t\t\t\t\t*\t5.Doctors List\t\t*\n");
        printf("\t\t\t\t\t*\t0.Exit\t\t\t*\n");
         printf("\t\t\t\t\t*********************************\n");
         printf("\n\n\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            admitPatient();
            break;

        case 2:
            patientList();
            break;

        case 3:
            dischargePatient();
            break;

        case 4:
            addDoctor();
            break;

        case 5:
            doctorList();
            break;

        default:
            printf("\t\t\t\t\tInvalid Choice...\n\n");

        }
        printf("\n\n\t\t\t\t\tPress Any Key To Continue...");
        getch();
    }

    return 0;
}

void admitPatient(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("patient.txt", "ab");

    printf("\t\t\t\t\tEnter Patient id: ");
    scanf("%d", &p.id);

    printf("\t\t\t\t\tEnter Patient name: ");
    fflush(stdin);
    gets(p.patientName);

    printf("\t\t\t\t\tEnter Patient Address: ");
    fflush(stdin);
    gets(p.patientAddress);

    printf("\t\t\t\t\tEnter Patient Disease: ");
    fflush(stdin);
    gets(p.disease);

    printf("\n\t\t\t\t\tPatient Added Successfully");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void patientList(){

    system("cls");
    printf("\t\t\t\t\t<== Patient List ==>\n\n");
    printf("\t\t\t%s \t%s \t%s \t%s \t%s\n", "Id", "Patient Name", "Address", "Disease", "Date");
    printf("\t\t\t----------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    while(fread(&p, sizeof(p), 1, fp) == 1){
        printf("\t\t\t%d \t%s \t\t%s \t\t%s \t\t%s\n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }

    fclose(fp);
}


void dischargePatient(){
    int id, f=0;
    system("cls");
    printf("\t\t\t\t\t<== Discharge Patient ==>\n\n");
    printf("\t\t\t\t\tEnter Patient id to discharge: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1){

        if(id == p.id){
            f=1;
        }else{
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if(f==1){
        printf("\n\n\t\t\t\t\tPatient Discharged Successfully.");
    }else{
        printf("\n\n\t\t\t\t\tRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");

}

void addDoctor(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    int f=0;

    system("cls");
    printf("\t\t\t\t\t<== Add Doctor ==>\n\n");

    fp = fopen("doctor.txt", "ab");

    printf("\t\t\t\t\tEnter Doctor id: ");
    scanf("%d", &d.id);

    printf("\t\t\t\t\tEnter Doctor Name: ");
    fflush(stdin);
    gets(d.name);

    printf("\t\t\t\t\tEnter Doctor Address: ");
    fflush(stdin);
    gets(d.address);

    printf("\t\t\t\t\tDoctor Specialize in: ");
    fflush(stdin);
    gets(d.specialize);

    printf("\t\t\t\t\tDoctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}



void doctorList(){
    system("cls");
    printf("\t\t\t\t\t<== Doctor List ==>\n\n");

    printf("\t\t\t%s \t%s \t%s \t%s \t\t%s\n", "id", "Name", "Address", "Specialize","Date");
    printf("\t\t\t-----------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while(fread(&d, sizeof(d), 1, fp) == 1){
        printf("\t\t\t%d \t%s \t%s \t\t%s \t\t%s\n", d.id, d.name, d.address, d.specialize, d.date);
    }

    fclose(fp);
}
