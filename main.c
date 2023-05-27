#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int day;
    int month;
    int year;
} date;
typedef struct
{
    char firstname[30];
    char lastname[30];
    date dob;
    char address[50];
    char phonenumber[30];
    char email[50];
} contacts;
contacts s[10000];
int count=0,warning=1,n=0,p[30];
void load ()
{
    FILE *f;
    char fname[100];
    printf("enter file name:  ");
    getchar();
    gets(fname);
    f=fopen(fname,"r");
    if(f!=NULL)
    {
        while (!feof(f))
        {
            fscanf(f,"%[^,],",s[count].lastname);
            fscanf(f,"%[^,],",s[count].firstname);
            fscanf(f,"%d-%d-%d,",&s[count].dob.day,&s[count].dob.month,&s[count].dob.year);
            fscanf(f,"%[^,],",s[count].address);
            fscanf(f,"%[^,],",s[count].phonenumber);
            fscanf(f,"%s\n",s[count].email);
            count++;
        }
        fclose(f);
    }
    else
        printf("file not found\n");
}
int countdigits(int year)
{
    int counter=0,y=year;
    while(y!=0)
    {
        y=y/10;
        counter++;
    }
    return counter;
}
void DOB(int *day, int *month, int *year)
{
    int i,d,m,y,c=0;
    while (c<3)
    {
        c=3;
        if(*day>31||*day<=0)
        {
            c--;
            printf("Invalid day,the day should be between 1-31.\n");
        }
        if(*month>12||*month<=0)
        {
            c--;
            printf("Invalid month,the month should be between 1-12.\n");
        }
        if(*year>2021||countdigits(*year)!=4)
        {
            c--;
            printf("Invalid year.\n");
        }
        if (c<3) {
        printf("please enter the correct date:");
        scanf("%d/%d/%d",day,month,year);
        }
    }
}
int check09(char err[])
{
    int i;
    for(i=0; i<strlen(err); i++)
    {
        if(err[i]<'0'||err[i]>'9')
            return 0;
    }
    return 1;
}
void validphoneno(char err[])
{
    int x;
    while(1)
    {
        x=check09(err);
        if(x==0)
        {
            printf("Invalid phone number\n");
            printf("enter phone no:");
            scanf("%s",err);
        }
        else
            return ;
    }
}
void validemailaddress (char a[])
{
    while(1)
    {
        int count=0;
        for( int i=0; i<strlen(a); i++)
        {
            if (a[i]=='@')
                count++;
        }
        char sub[]=".com";
        int i=0,j=0,x;
        while(a[i]!='\0'&& sub[j]!='\0')
        {
            if(sub[j]==a[i])
            {
                i++;
                j++;
            }
            else
                i++;
        }

        if(sub[j]=='\0')
            x=1;
        else
            x=0;

        if(count==0||x==0)
        {
            printf("email is invalid\nplease enter a valid email address:\n");
            scanf("%s",a);
        }
        else
            break;
    }
}
void search()
{
    int j=0;

    contacts x;
    printf("Enter the last name of the contact you want: ");
    scanf("%s",x.lastname);
    for(int i=0; i<count; i++)
    {
        if(strcasecmp(x.lastname,s[i].lastname)==0)
        {
            printf("%d-%s\t%s\t%d-%d-%d\t%s\t%s\t%s\n",j+1,s[i].lastname,s[i].firstname,s[i].dob.day,s[i].dob.month,s[i].dob.year,s[i].address,s[i].phonenumber,s[i].email);
            n++;
            p[j++]=i;
        }
    }
    if (!n)
        printf("There doesn't exist a contact whose name is (%s)\n",x.lastname);
}
void add()
{
    int i;
    count++;
    warning = 0;
    printf("enter the last name:");
    scanf("%s",s[count-1].lastname);
    printf("enter the first name:");
    scanf("%s",s[count-1].firstname);
    printf("enter the DOB (DD/MM/YY):");
    scanf("%d/%d/%d",&s[count-1].dob.day,&s[count-1].dob.month,&s[count-1].dob.year);
    DOB(&s[count-1].dob.day,&s[count-1].dob.month,&s[count-1].dob.year);
    printf("enter the address:");
    scanf("\n%[^\n]",s[count-1].address);
    printf("enter the phone number:");
    scanf("%s",s[count-1].phonenumber);
    validphoneno(s[count-1].phonenumber);
    printf("enter the email address:");
    scanf("%s",s[count-1].email);
    validemailaddress (s[count-1].email);
}
void deletee()
{
    int x=0,y=0,i,z;
    contacts a;
    printf("Enter the last name of the contact: ");
    scanf("%s", a.lastname);
    printf("Enter the first name of the contact: ");
    scanf("%s", a.firstname);
    while (!x)
    {
        if (!strcasecmp(s[y].lastname, a.lastname))
        {
            if (!strcasecmp(s[y].firstname, a.firstname))
            {
                z=1;
                warning=0;
                for (i=y; i<count-1; i++)
                {
                    strcpy(s[i].lastname, s[i+1].lastname);
                    strcpy(s[i].firstname,s[i+1].firstname);
                    s[i].dob.day = s[i+1].dob.day;
                    s[i].dob.month = s[i+1].dob.month;
                    s[i].dob.year = s[i+1].dob.year;
                    strcpy(s[i].address, s[i+1].address);
                    strcpy(s[i].phonenumber, s[i+1].phonenumber);
                    strcpy(s[i].email, s[i+1].email);

                }
                count--;
            }
        }
        else if (y>count && !z)
        {
            printf("NOT FOUND!\n");
            x=1;
        }
        else if (y>count && z)
            x=1;
        else
            y++;
    }
}
void modify()
{
    search();
    if(n!=0)
    {
        printf("0-Exit modification\n");
        printf("please choose the number of the contact you want from the above menu\n");
        int choice;
        scanf("%d",&choice);
        while (choice>n||choice<0)
        {
            printf("this number is not included in the menu\nplease choose the number of the contact you want from the above\n");
            scanf("%d",&choice);
        }
        if(choice==0)
            return ;
        int k=choice-1;
        int y=p[k];
        int x;
        while(1)
        {
            printf("please choose the field you want to modify\n1.last name\n2.first name\n3.date of birth\n4.address\n5.phone number\n6.email address\n0.exit modification\n");
            scanf("%d",&x);
            while(x>6||x<0)
            {
                printf("This number is not written in the menu\nplease choose the number of the field from the above menu\n");
                scanf("%d",&x);
            }
            switch(x)
            {
            case 1:
                 warning = 0;
                printf("please enter the updated last name\n");
                scanf("%s",s[y].lastname);
                break;
            case 2:
                 warning = 0;
                printf("please enter the updated first name\n");
                scanf("%s",s[y].firstname);
                break;
            case 3:
                 warning = 0;
                printf("please enter the updated date of birth in this form DD/MM/YY\n");
                scanf("%d/%d/%d",&s[y].dob.day,&s[y].dob.month,&s[y].dob.year);
                DOB(&s[y].dob.day,&s[y].dob.month,&s[y].dob.year);
                break;
            case 4:
                 warning = 0;
                printf("please enter the updated address\n");
                scanf("\n%[^\n]",s[y].address);
                break;
            case 5:
                 warning = 0;
                printf("please enter the updated phone number\n");
                scanf("%s",s[y].phonenumber);
                validphoneno(s[y].phonenumber);
                break;
            case 6:
                 warning = 0;
                printf("please enter the updated email\n");
                scanf("%s",s[y].email);
                validemailaddress(s[y].email);
                break;
            case 0:
                return ;
            }
        }
    }
}
void SortByLname()
{
    int i,j;
     warning = 0;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
            if(strcasecmp(s[i].lastname,s[j].lastname)==1)
            {
                contacts temp;
                temp=s[i];
                s[i]=s[j];
                s[j]=temp;
            }
    }
}
void SortByDOB()
{
    int i,j;
     warning = 0;
    for(i=0; i<count; i++)
    {
        for(j=i+1; j<count; j++)
        {
            if(s[i].dob.year>s[j].dob.year)
            {
                contacts temp;
                temp=s[i];
                s[i]=s[j];
                s[j]=temp;
            }
            else if(s[i].dob.year==s[j].dob.year)
            {
                if(s[i].dob.month>s[j].dob.month)
                {
                    contacts temp;
                    temp=s[i];
                    s[i]=s[j];
                    s[j]=temp;
                }

                else if(s[i].dob.month==s[j].dob.month)
                {
                    if(s[i].dob.day>s[j].dob.day)
                    {
                        contacts temp;
                        temp=s[i];
                        s[i]=s[j];
                        s[j]=temp;
                    }
                }
            }
        }
    }
}
void print ()
{
    int i;
    warning=0;
    int x;
    printf("Choose how to sort:\n1-Sort by last name\n2-Sort by date of birth\n");
    scanf("%d",&x);
    if(x==1)
        SortByLname();
    else if (x==2)
        SortByDOB();
    for(i=0; i<count; i++)
    {
        printf("%s\t",s[i].lastname);
        printf("%s\t",s[i].firstname);
        printf("%d-%d-%d\t",s[i].dob.day,s[i].dob.month,s[i].dob.year);
        printf("%s\t",s[i].address);
        printf("%s\t",s[i].phonenumber);
        printf("%s\n",s[i].email);
    }
}
void save ()
{
    FILE *f;
    char fnamee[100];
    printf("enter file name:  ");
    getchar();
    gets(fnamee);
    f=fopen(fnamee,"w");
    int j;
    warning=1;
    for(j=0; j<count; j++)
    {
        fprintf(f,"%s,",s[j].lastname);
        fprintf(f,"%s,",s[j].firstname);
        fprintf(f,"%d-%d-%d,",s[j].dob.day,s[j].dob.month,s[j].dob.year);
        fprintf(f,"%s,",s[j].address);
        fprintf(f,"%s,",s[j].phonenumber);
        fprintf(f,"%s\n",s[j].email);
    }
    fclose(f);
}
void quit ()
{
    int m;
    if (warning==1)
        exit(0);
    else
    {
        printf("If you exit without saving your changes will be discarded\n");
        printf("Do you want to exit without saving?\n1.YES\n2.NO\n");
        scanf("%d",&m);
        if (m==1)
            exit(0);
    }

}
int main()
{
    int x;
    while (1)
    {
        printf("please choose a function:\n");
        printf("1.LOAD\n2.SEARCH\n3.ADD\n4.DELETE\n5.MODIFY\n6.PRINT\n7.SAVE\n8.QUIT\n");
        scanf("%d",&x);
        if(x==1)
            load();
        else if (x==2)
            search();
        else if (x==3)
            add();
        else if (x==4)
            deletee();
        else if(x==5)
            modify();
        else if(x==6)
            print();
        else if (x==7)
            save();
        else if (x==8)
            quit();
        else
            printf("wrong input!\n");
    }
    return 0;
}





