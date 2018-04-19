#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<Windows.h>
struct psmgr
{
    char url[50];
    char id[50];
    char password[50];
};
struct psmgr info;
void entry(void);
void display(void);
char encryptedUrl[100];
char encryptedId[100];
char encryptedPass[100];
char encryptedInfo[100];
char decryptedInfo[100];
void infoEncription(char *P);
void infoDecription(char *P);
void edit(void);
COORD c= {0,0};
char password[50];
char userPassword[50];
char encriptedP[50];
char decryptedP[50];
char userEncryptedP[50];
char userDecryptedP[50];
char newUserPassword[50];
char newMasterpassword[50];
FILE *fp;
FILE *ifp;
int checkPassword(void);
void inputMasterPassword(void);
void inputUserPassword(void);
void encryption(char *P);
void decryption(char *P);
void userEncryption(char *P);
void userDecryption(char *P);
void box(int x1,int y1, int x2, int y2);
void horizontalLine(int y, int x1, int x2);
void verticalLine(int x, int y1, int y2);
void gotoxy(int x,int y);
void color(int c);
void menu(void);
void firstWindow(void);
void clearWindow(void);
void secondWindow(void);
void changePassword(void);
void inputNewMasterPassword(void);
void inputNewUserPassword(void);
int main()
{
    int a,choice,choiceUninstall;
    int deleteAll;
    fp=fopen("C:\\psmgr.txt","r+");
    fscanf(fp,"%d",&a);
    fscanf(fp,"%s",&password);
    fclose(fp);
    while(1)
    {
x:

        if(a==0&&strlen(password)!=0)
        {
            secondWindow();
            inputUserPassword();
//y:
            fp=fopen("C:\\psmgr.txt","r");
            fseek(fp,1,0);
            fgets(encriptedP,50,fp);
            fscanf(fp,"%s",&encriptedP);
            decryption(encriptedP);
            fclose(fp);
            if(strcmp(userPassword,decryptedP)==0)
            {
afterChangeP:
                fp=fopen("C:\\psmgr.txt","a");
                system("cls");
                color(11);
                box(1,1,77,40);
                horizontalLine(5,2,77);
                verticalLine(20,6,40);
                menu();
                gotoxy(16,22);
                printf(" ");
                gotoxy(16,22);
                scanf("%d",&choice);
                if(choice==1)
                {
                    entry();
                    color(14);
                    gotoxy(34,35);
                    system("pause");
                    clearWindow();
                }
                else if(choice==2)
                {
                    system("cls");
                    color(11);
                    box(1,1,77,200);
                    display();
                    color(14);
                    system("pause");
                    system("cls");
                }
                else if(choice==3)
                {
                    edit();
                    color(14);
                    gotoxy(34,35);
                    system("pause");
                    clearWindow();
                }
                else if(choice==4)
                {
                    changePassword();
                    color(14);
                    gotoxy(34,35);
                    system("pause");
                    clearWindow();
                    goto afterChangeP;
                }
                else if(choice==5)
                {
                    //remove("C:\\psmgr.txt");
                    gotoxy(25,10);
                    color(12);
                    printf("Are You Sure To Delete All Data?");
                    gotoxy(25,12);
                    color(10);
                    printf("Press 1 For Yes");
                    gotoxy(25,14);
                    printf("Press 2 For No");
                    gotoxy(25,16);
                    color(14);
                    printf("Enter Choice: ");
                    scanf("%d",&deleteAll);
                    if(deleteAll==1)
                    {
                        ifp=fopen("C:\\psmgrinfo.txt","w");
                        remove("C:\psmgrinfo.txt");
                        fclose(ifp);
                        system("cls");
                        gotoxy(25,13);
                        color(12);
                        printf("All Data Has Been Deleted.");
                        gotoxy(25,15);
                        color(14);
                        system("pause");
                    }
                    else if(deleteAll==2)
                    {
                        goto afterChangeP;
                    }

                }
                else if(choice==6)
                {
                    system("cls");
                    gotoxy(36,10);
                    color(10);
                    printf("GOOD BYE.");
                    gotoxy(2,14);
                    color(1);
                    exit(0);
                }

                goto afterChangeP;
            }
            else
            {
                system("cls");
                gotoxy(15,5);
                color(12);
                printf("Incorrect Password.");
                gotoxy(15,7);
                color(14);
                printf("Forgot Password?");
                gotoxy(15,9);
                color(13);
                printf("You Can Reset This Application.");
                gotoxy(15,11);
                color(15);
                printf("If You Reset This Application All Stored Data Will Be Deleted.");
                gotoxy(15,13);
                color(12);
                printf("Press 1 for Reset Application.");
                gotoxy(15,15);
                color(14);
                printf("Press 2 for Re-Enter Password.");
                gotoxy(15,18);
                color(10);
                printf("Enter Choice: ");
                scanf("%d",&choiceUninstall);
                if(choiceUninstall==1)
                {
                    remove("C:\\psmgr.txt");
                    remove("C:\\psmgrinfo.txt");
                    system("cls");
                    gotoxy(20,10);
                    color(12);
                    printf("Program Has Been Reset.");
                    gotoxy(20,13);
                    color(14);
                    system("pause");
                    system("cls");
                    goto wrongP;
                }
                else if(choiceUninstall==2)
                {
                    system("cls");
                    goto x;
                }
            }
        }

        else
        {
wrongP:
            firstWindow();
            gotoxy(21,17);
            inputMasterPassword();
            encryption(password);
            a=0;
            fp=fopen("C:\\psmgr.txt","w+");
            fprintf(fp,"%d",a);
            fputs(encriptedP,fp);
            fclose(fp);
            system("cls");
            goto x;
        }
        gotoxy(30,38);
    }
    gotoxy(1,50);
    return 0;
}

void inputMasterPassword(void)
{
    char ch;
    int i;
    i=0;
    for(;;)
    {
        ch=getch();
        if(ch=='\r')
        {
            password[i]='\0';
            break;
        }

        if(ch!='\b')
        {
            password[i]=ch;
            printf("*");
            i++;
        }
        if(ch=='\b')
        {
            printf("\b \b");
            i--;
        }
    }
    printf("\n");
}

int checkPassword(void)
{
    if(strcmp(userPassword,decryptedP)!=0)
        return 0;
    else
        return 1;
}


void inputUserPassword(void)
{
    char ch;
    int i;
    i=0;
    for(;;)
    {
        ch=getch();
        if(ch=='\r')
        {
            userPassword[i]='\0';
            break;
        }

        if(ch!='\b')
        {
            userPassword[i]=ch;
            printf("*");
            i++;
        }
        if(ch=='\b')
        {
            printf("\b \b");
            i--;
        }
    }
}

void encryption(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {
        if(P[i]>=89&&P[i]<=90||P[i]>=120&&P[i]<=122)
            encriptedP[i]=P[i]-23;
        else if(P[i]>=48&&P[i]<=54)
            encriptedP[i]=P[i]+3;
        else if(P[i]>=55&&P[i]<=57)
            encriptedP[i]=P[i]-7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            encriptedP[i]=P[i];
        else
            encriptedP[i]=P[i]+3;
    }
    encriptedP[i]='\0';
}

void decryption(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {

        if(P[i]>=65&&P[i]<=67||P[i]>=97&&P[i]<=99)
            decryptedP[i]=P[i]+23;
        else if(P[i]>=51&&P[i]<=57)
            decryptedP[i]=P[i]-3;
        else if(P[i]>=48&&P[i]<=50)
            decryptedP[i]=P[i]+7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            decryptedP[i]=P[i];
        else
            decryptedP[i]=P[i]-3;

    }
    decryptedP[i]='\0';
}

void userEncryption(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {
        if(P[i]>=89&&P[i]<=90||P[i]>=120&&P[i]<=122)
            userEncryptedP[i]=P[i]-23;
        else if(P[i]>=48&&P[i]<=54)
            userEncryptedP[i]=P[i]+3;
        else if(P[i]>=55&&P[i]<=57)
            userEncryptedP[i]=P[i]-7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            userEncryptedP[i]=P[i];
        else
            userEncryptedP[i]=P[i]+3;
    }
    userEncryptedP[i]='\0';
}

void userDecryption(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {

        if(P[i]>=65&&P[i]<=67||P[i]>=97&&P[i]<=99)
            userDecryptedP[i]=P[i]+23;
        else if(P[i]>=51&&P[i]<=57)
            userDecryptedP[i]=P[i]-3;
        else if(P[i]>=48&&P[i]<=50)
            userDecryptedP[i]=P[i]+7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            userDecryptedP[i]=P[i];
        else
            userDecryptedP[i]=P[i]-3;

    }
    userDecryptedP[i]='\0';
}

void box(int x1,int y1, int x2, int y2)
{
    int i;
    gotoxy(32,3);
    //color(11);
    gotoxy(x1,y1);
    printf("%c",201);

    for(i=x1+1; i<=x2; i++)
    {
        gotoxy(i,y1);
        printf("%c",205);
    }

    gotoxy(x2+1,y1);
    printf("%c",187);

    for(i=y1+1; i<=y2; i++)
    {
        gotoxy(x2+1,i);
        printf("%c",186);
    }

    gotoxy(x1,y1+1);
    for(i=y1+1; i<=y2; i++)
    {
        gotoxy(x1,i);
        printf("%c",186);
    }

    gotoxy(x1,y2+1);
    printf("%c",200);
    gotoxy(x2+1,y2+1);
    printf("%c",188);

    gotoxy(x1+1,y2+1);
    for(i=x1+1; i<=x2; i++)
    {
        gotoxy(i,y2+1);
        printf("%c",205);
    }

}

void horizontalLine(int y, int x1, int x2)
{
    int i;
    for(i=x1; i<=x2; i++)
    {
        gotoxy(i,y);
        printf("%c",196);
    }
}

void verticalLine(int x, int y1, int y2)
{
    int i;
    for(i=y1; i<=y2; i++)
    {
        gotoxy(x,i);
        printf("%c",179);
    }
}

void menu(void)
{
    color(13);
    gotoxy(31,3);
    printf("PASSWORD MANAGER");
    gotoxy(5,7);
    color(10);
    printf("MAIN MENU");
    color(10);
    horizontalLine(8,3,15);
    color(10);
    gotoxy(3,10);
    printf("1.");
    gotoxy(3,12);
    printf("2.");
    gotoxy(3,14);
    printf("3.");
    gotoxy(3,16);
    printf("4.");
    gotoxy(3,18);
    printf("5.");
    gotoxy(3,20);
    printf("6.");

    color(7);
    gotoxy(5,10);
    printf("Add New Data");
    gotoxy(5,12);
    printf("Show All Data");
    gotoxy(5,14);
    printf("Edit Data");
    gotoxy(5,16);
    printf("Change Password");
    gotoxy(5,18);
    printf("Delete All");
    gotoxy(5,20);
    printf("Exit");
    color(14);
    gotoxy(3,22);
    printf("Enter Choice: ");
}

void gotoxy(int x,int y)
{
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void firstWindow(void)
{
    color(11);
    box(5,3,70,30);
    gotoxy(14,6);
    color(13);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    gotoxy(17,8);
    color(14);
    printf("   WELCOME TO PASSWORD MANAGER BY MAMUN");
    gotoxy(14,10);
    color(13);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    gotoxy(14,7);
    printf("#");
    gotoxy(14,8);
    printf("#");
    gotoxy(14,9);
    printf("#");
    gotoxy(61,7);
    printf("#");
    gotoxy(61,8);
    printf("#");
    gotoxy(61,9);
    printf("#");
    gotoxy(28,15);
    color(10);
    printf("Enter Master Password");
    color(7);
    box(19,16,55,17);
}

void entry(void)
{
    ifp=fopen("C:\\psmgrinfo.txt","a+");
    color(14);
    gotoxy(36,8);
    printf("Enter your information:");
    gotoxy(24,10);
    color(10);
    printf("Enter URL     : ");
    color(7);
    scanf("%s",encryptedUrl);
    infoEncription(encryptedUrl);
    strcpy(info.url,encryptedInfo);
    gotoxy(24,12);
    color(10);
    printf("Enter ID      : ");
    color(7);
    scanf("%s",encryptedId);
    infoEncription(encryptedId);
    strcpy(info.id,encryptedInfo);
    gotoxy(24,14);
    color(10);
    printf("Enter Password: ");
    color(7);
    scanf("%s",encryptedPass);
    infoEncription(encryptedPass);
    strcpy(info.password,encryptedInfo);

    fwrite(&info,sizeof(info),1,ifp);
    fflush(ifp);
    fclose(ifp);
}

void display(void)
{
    int cnt=1;
    int i=9;
    ifp=fopen("C:\\psmgrinfo.txt","r+");
    if(fread(&info,sizeof(info),1,ifp)==NULL)
    {
        gotoxy(28,10);
        color(12);
        printf("There Is No Data In Memory.");
        gotoxy(28,13);
    }
    else
    {
        rewind(ifp);
        while(fread(&info,sizeof(info),1,ifp)!=NULL)
        {
            infoDecription(info.url);
            gotoxy(32,7);
            color(10);
            printf("DATA IN MEMORY");
            gotoxy(30,8);
            printf("------------------");
            gotoxy(15,i+1);
            color(7);
            printf("     URL     : ");
            color(15);
            printf("%s",decryptedInfo);
            infoDecription(info.id);
            gotoxy(15,i+2);
            color(10);
            printf("%d.",cnt);
            color(7);
            printf("   ID      : ",cnt);
            color(15);
            printf("%s",decryptedInfo);
            infoDecription(info.password);
            gotoxy(15,i+3);
            color(7);
            printf("     Password: ");
            color(15);
            printf("%s",decryptedInfo);
            gotoxy(5,i+5);
            color(8);
            printf("----------------------------------------------------------------------");
            i=i+5;
            cnt++;
        }
        color(14);
        gotoxy(25,i+1);
        fflush(ifp);
    }
}

void infoEncription(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {
        if(P[i]>=89&&P[i]<=90||P[i]>=120&&P[i]<=122)
            encryptedInfo[i]=P[i]-23;
        else if(P[i]>=48&&P[i]<=54)
            encryptedInfo[i]=P[i]+3;
        else if(P[i]>=55&&P[i]<=57)
            encryptedInfo[i]=P[i]-7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            encryptedInfo[i]=P[i];
        else
            encryptedInfo[i]=P[i]+3;
    }
    encryptedInfo[i]='\0';
}

void infoDecription(char *P)
{
    int i;
    for(i=0; P[i]!='\0'; i++)
    {

        if(P[i]>=65&&P[i]<=67||P[i]>=97&&P[i]<=99)
            decryptedInfo[i]=P[i]+23;
        else if(P[i]>=51&&P[i]<=57)
            decryptedInfo[i]=P[i]-3;
        else if(P[i]>=48&&P[i]<=50)
            decryptedInfo[i]=P[i]+7;
        else if(((P[i]>=0&&P[i]<=64)&&P[i]!=32)||(P[i]>=91&&P[i]<=96)||(P[i]>=123))
            decryptedInfo[i]=P[i];
        else
            decryptedInfo[i]=P[i]-3;

    }
    decryptedInfo[i]='\0';
}

void clearWindow(void)
{
    int m,n;
    for(m=6; m<=39; m++)
    {

        for(n=21; n<=76; n++)
        {
            gotoxy(n,m);
            printf(" ");
        }
    }
}

void secondWindow(void)
{
    color(11);
    box(5,3,70,30);
    gotoxy(14,6);
    color(10);
    printf("################################################");
    gotoxy(17,8);
    color(13);
    printf("   WELCOME TO PASSWORD MANAGER BY MAMUN");
    gotoxy(14,10);
    color(10);
    printf("################################################");
    gotoxy(14,7);
    printf("%c",178);
    gotoxy(14,8);
    printf("%c",178);
    gotoxy(14,9);
    printf("%c",178);
    gotoxy(61,7);
    printf("%c",178);
    gotoxy(61,8);
    printf("%c",178);
    gotoxy(61,9);
    printf("%c",178);
    gotoxy(30,15);
    color(10);
    printf("Enter Password");
    color(7);
    box(19,16,55,17);
    gotoxy(21,17);
}

void edit(void)
{
    int d,l,n,location;
    gotoxy(18,5);
    color(10);
    if((ifp=fopen("C:\\psmgrinfo.txt","r+"))==NULL||fread(&info,sizeof(info),1,ifp)==NULL)
    {
        gotoxy(35,20);
        color(12);
        printf("There Is No Data To Be Edited");
        gotoxy(25,9);
    }
    else
    {
        gotoxy(28,12);
        printf("Enter Serial Number Of Data To Be Edited: ");
        scanf("%d",&d);
        location=(d-1)*sizeof(info);
        fseek(ifp,location,0);
        color(14);
        gotoxy(28,14);
        printf("Enter Your Information:");
        gotoxy(28,16);
        color(10);
        printf("Enter URL     : ");
        color(7);
        scanf("%s",encryptedUrl);
        infoEncription(encryptedUrl);
        strcpy(info.url,encryptedInfo);
        gotoxy(28,18);
        color(10);
        printf("Enter ID      : ");
        color(7);
        scanf("%s",encryptedId);
        infoEncription(encryptedId);
        strcpy(info.id,encryptedInfo);
        gotoxy(28,20);
        color(10);
        printf("Enter Password: ");
        color(7);
        scanf("%s",encryptedPass);
        infoEncription(encryptedPass);
        strcpy(info.password,encryptedInfo);
        fwrite(&info,sizeof(info),1,ifp);
        fflush(ifp);
        fclose(ifp);
        gotoxy(28,24);
        color(13);
        printf("Data Has Been Edited Successfully");
    }
}


void changePassword(void)
{
    int a;
change:
    gotoxy(40,12);
    color(10);
    printf("Enter Old Password");
    gotoxy(35,13);
    color(7);
    box(31,14,65,15);
    gotoxy(40,18);
    color(10);
    printf("Enter New Password");
    gotoxy(35,19);
    color(7);
    box(31,20,65,21);
    gotoxy(33,15);
    inputNewMasterPassword();
    gotoxy(32,21);
    inputNewUserPassword();

    fp=fopen("C:\\psmgr.txt","r");
    fseek(fp,1,0);
    fgets(encriptedP,50,fp);
    fscanf(fp,"%s",&encriptedP);
    decryption(encriptedP);
    fclose(fp);
    if(strcmp(newMasterpassword,decryptedP)==0)
    {
        strcpy(password,newUserPassword);
        encryption(password);
        a=0;
        fp=fopen("C:\\psmgr.txt","w+");
        fprintf(fp,"%d",a);
        fputs(encriptedP,fp);
        fclose(fp);
        gotoxy(32,25);
        color(13);
        printf("Password Has Been Changed Successfully.");
    }
    else
    {
        gotoxy(33,15);
        color(12);
        clearWindow();
        gotoxy(33,15);
        printf("Incorrect old password. Try again.");
        color(14);
        gotoxy(33,17);
        system("pause");
        clearWindow();
        goto change;
    }

}

void inputNewUserPassword(void)
{
    char ch;
    int i;
    i=0;
    for(;;)
    {
        ch=getch();
        if(ch=='\r')
        {
            newUserPassword[i]='\0';
            break;
        }

        if(ch!='\b')
        {
            newUserPassword[i]=ch;
            printf("*");
            i++;
        }
        if(ch=='\b')
        {
            printf("\b \b");
            i--;
        }
    }
}


void inputNewMasterPassword(void)
{
    char ch;
    int i;
    i=0;
    for(;;)
    {
        ch=getch();
        if(ch=='\r')
        {
            newMasterpassword[i]='\0';
            break;
        }

        if(ch!='\b')
        {
            newMasterpassword[i]=ch;
            printf("*");
            i++;
        }
        if(ch=='\b')
        {
            printf("\b \b");
            i--;
        }
    }
}
