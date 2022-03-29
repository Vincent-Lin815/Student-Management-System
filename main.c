#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void gotoxy(int x, int y);
void printChar(char c, int num);
void printTitle();
void add(FILE *fp);
void modify(FILE *fp);
void show(FILE *fp);
void indivisual_view(FILE *fp);
FILE *delete(FILE *fp);
void chg_password();
FILE *tp;

typedef struct person{
    char name[100];
    char dept[50];
    int roll;
    float sgpa[12];
    float cgpa;
}Student;

struct password{
    char pass[25];
}pa;

int main()
{
    SetConsoleTitle("Student Management System | NTU");
    FILE *fp;
    int k = 0, option;
    char pwd[50];
    
    if((fp = fopen("db.txt", "rb+")) == NULL){
        if((fp = fopen("db.txt", "ab+")) == NULL){
            printf("Can't open or create database!");
            return 0;
        }
    }
    
    system("color 9f");
    gotoxy(42, 8);
    printf("Login (if first login press enter)");
    gotoxy(42, 10);
    printf("____________________________________");
	gotoxy(42,11);
	printf("|\tEnter password :             |");
	gotoxy(42,12);
	printf("|__________________________________|");
	gotoxy(65,11);
	while(k < 10){
	    pwd[k] = getch();
	    char c = pwd[k];
	    if(c == 13){
            break;
        }else{
            printf("*");
        }
        k++;
	}
    pwd[k] = '\0';

    // check if the password is correct
    tp = fopen("F:/Password.txt","r+");
    fgets(pa.pass, 25, tp);
    
    if(strcmp(pwd, pa.pass) == 0){
        system("cls");
        gotoxy(10,3);
		printf("<<<< Loading Please Wait >>>>");
        for(int i = 0; i < 5; i++){
            printf("\t(*_*)");
            Sleep(500);
        }
        printf("\n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *       Welcome      *");
		printf("\n\n\t\t\t\t\t     *                    *");
		printf("\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();

        printTitle();
        printf("\n\n\t\t\t       The Vincent University\n\t\t\t");
        printChar('=', 38);
        printf("\n\n\n\t\t\t       press any key to Enter");
        getch();

        while(1){
            printTitle();
            printf("\n\t");
            printChar('*', 64);

            printf("\n\t\t1. Add Student");
            printf("\n\t\t2. Modify Student");
            printf("\n\t\t3. Show All Student");
            printf("\n\t\t4. Individual View");
            printf("\n\t\t5. Remove Student");
            printf("\n\t\t6. Change Password");
            printf("\n\t\t7. Logout\n\t");

            printChar('*', 64);
            printf("\n\tEnter Your Option --> ");
            scanf("%d", &option);

            switch (option){
                case 1:
                    add(fp);
                    break;
                case 2:
                    modify(fp);
                    break;
                case 3:
                    show(fp);
                    break;
                case 4:
                    indivisual_view(fp);
                    break;
                case 5:
                    fp = delete(fp);
                    break;
                case 6:
                    system("cls");
                    system("color 5f");
                    chg_password();
                    break;
                case 7:
                    return 1;
                    break;
                default:
                    printf("\n\tNo action detected");
                    printf("\n\tPress any key to continue");
                    getch();
            }
        }
    }else{
        printf("Password wrong, get out!");
        getch();
    }

    return 1;
}

void gotoxy(int x, int y){
    COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(ConsoleHandle, CRD);
}

void printChar(char c, int num){
    while(num--){
        putchar(c);
    }
}

void printTitle(){
    system("cls");
    system("COLOR 03");
    printf("\n\n\t");
    printChar('=',19);
    printf(" Student Management System ");
    printChar('=',19);
    printf("\n");
}

void add(FILE *fp){
    printTitle();

    char another = 'y', c;
    float cgpa = 0;
    Student s;

    rewind(fp);
    while(another == 'y' | another == 'Y'){
        printf("\n\tPlease enter full name of student: ");
        rewind(stdin);
        fgets(s.name, 100, stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("\n\tPlease enter department name: ");
        rewind(stdin);
        fgets(s.dept, 50, stdin);
        s.dept[strlen(s.dept)-1]='\0';


        printf("\n\tPlease enter roll number: ");
        scanf("%d", &s.roll);

        printf("\n\tPlease enter sgpa for 12 semesters: \n");
        for(int i = 0; i < 12; i++){
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];
        }

        cgpa/=12.0;
        s.cgpa=cgpa;

        fwrite(&s,sizeof(s),1,fp);
        printf("\n\tAdd another student (Y/N)");
        rewind(stdin);
        another = getch();
    }
}

void modify(FILE *fp){
    printTitle();

    int tempRoll, flag = 0;
    Student s;
    float cgpa = 0;

    printf("\n\n\tEnter roll number of student to modify the record : ");
    scanf("%d", &tempRoll);

    rewind(fp);
    while(fread(&s, sizeof(s), 1, fp) == 1){
        if(s.roll == tempRoll){
            flag = 1;
            break;
        }
    }

    if(flag == 1){
        fseek(fp,-sizeof(s),SEEK_CUR);
        printf("\n\n\t\t\t\tRecord found\n\t\t\t");
        printChar('=',38);
        printf("\n\n\t\t\tStudent Name: %s",s.name);
        printf("\n\n\t\t\tStudent Roll: %d\n\t\t\t",s.roll);
        printChar('=',38);
        printf("\n\n\n\tEnter New Data for the student");

        printf("\n\n\n\tPlease enter full name of student: ");
        rewind(stdin);
        fgets(s.name, 100, stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("\n\tPlease enter department name: ");
        rewind(stdin);
        fgets(s.dept, 50, stdin);
        s.dept[strlen(s.dept)-1]='\0';


        printf("\n\tPlease enter roll number: ");
        scanf("%d", &s.roll);

        printf("\n\tPlease enter sgpa for 12 semesters: \n");
        for(int i = 0; i < 12; i++){
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];
        }

        cgpa/=12.0;
        s.cgpa=cgpa;

        fwrite(&s,sizeof(s),1,fp);
    }else{
        printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
    }

    printf("\n\n\t");
    system("pause");
}

void show(FILE *fp){
    printTitle();
    Student s;

    rewind(fp);

    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("\n\tName : %s", s.name);
        printf("\n\tDepartment : %s", s.dept);
        printf("\n\tRoll : %d", s.roll);
        printf("\n\n\tSGPA: ");
        for(int i = 0; i < 12; i++){
            printf("| %.2f |",s.sgpa[i]);
        }
        printf("\n\tCGPA : %.2f\n\n", s.cgpa);
    }

    system("pause");
}

void indivisual_view(FILE *fp){
    printTitle();

    char another = 'y';
    int tempRoll, flag = 0;
    Student s;

    while(another == 'y' | another == 'Y'){
        printf("\n\n\tEnter roll number: ");
        scanf("%d", &tempRoll);

        rewind(fp);

        while(fread(&s, sizeof(s), 1, fp) == 1){
            if(s.roll == tempRoll){
                flag = 1;
                break;
            }
        }

        if(flag == 1){
            printf("\n\tName : %s", s.name);
            printf("\n\tDepartment : %s", s.dept);
            printf("\n\tRoll : %d", s.name);
            printf("\n\n\tSGPA: ");
            for(int i = 0; i < 12; i++){
                printf("| %.2f |",s.sgpa[i]);
            }
            printf("\n\tCGPA : %.2f\n\n", s.cgpa);
            printChar('-', 65);
        }else{
            printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
        }

        printf("\n\n\t\tShow another student information? (Y/N)?");
        rewind(stdin);
        another=getchar();
    }
}

FILE *delete(FILE *fp){
    printTitle();

    FILE *ft;
    int tempRoll, flag = 0;
    Student s;

    if((ft = fopen("tempDB.txt", "wb+")) == NULL){
        printf("\n\n\t\t\t\\t!!! INVALID PATH !!!\n\t\t");
        system("pause");
        return fp;
    }

    printf("\n\n\tEnter Roll number of Student to Delete the Record");
    printf("\n\n\t\t\tRoll No. : ");
    scanf("%d",&tempRoll);

    rewind(fp);
    while(fread(&s, sizeof(s), 1, fp) == 1){
        if(s.roll == tempRoll){
            flag = 1;
            printf("\n\tRecord Deleted for");
            printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.dept,s.roll);
            continue;
        }

        fwrite(&s, sizeof(s), 1, ft);
    }

    if(flag == 0) printf("\n\n\t\tNO STUDENT FOUND WITH THE INFORMATION\n\t");

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("tempDB.txt","db.txt");

    if((fp = fopen("db.txt", "rb+")) == NULL){
        printf("ERROR");
        return NULL;
    }

    printChar('-',65);
    printf("\n\t");
    system("pause");
    return fp;
}

void chg_password(){
    char c;
    printf("\nPlease enter a new password: ");
    rewind(stdin);
    gets(pa.pass);
    printf("\nSave password? (y/n) : ");
    rewind(stdin);
    scanf("%c", &c);
    if(c == 'y'|| c == 'Y'){
        tp = fopen("password.txt","w+");
        fwrite(&pa, sizeof(pa), 1, tp);
        fclose(tp);
		printf("\n\tPassword Saved\n");
    }else{
        printf("Password not saved :\n");
		printf("Press any key to continue >>>");
		getch();
    }
}