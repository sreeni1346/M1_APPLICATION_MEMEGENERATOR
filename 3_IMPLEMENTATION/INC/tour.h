#include<stdio.h>
#include<stdlib.h>
#include<string.h>



enum state{main_menu,login_system};
enum state currentwindow=main_menu;

typedef struct userprofile
{
    char user_fname[100];
    char user_password[100];
    char user_place[100];
    float ticket_price;
    int user_numtick;
    struct userprofile *next;
}userprofile;

void ShowBrochure();

void login_client(userprofile*);
void booking_ticket(userprofile*);
void printing_ticket(userprofile*);
void cancelling_ticket(userprofile*);
void changing_pass(userprofile*);
void logout_client();
void checking_ticket(userprofile*);
void displaying_all_bookings(userprofile*);
void WriteToFile(userprofile*);
void exit_system();

char current_client[100];
userprofile* InitializeListing(userprofile *hello)
{
    userprofile* text,*petrol,temporary;
    FILE *fileopen;
    int counting_cooridantes=0;
    int z;
   // float following;
    fileopen=fopen("users.txt","r");

    if(fileopen==NULL)
        return NULL;

    if(fgetc(fileopen)==EOF)
        break;

    rewind(fileopen);
	while(fscanf(fileopen,"%90s %90s %90s %90f %90d",temporary.user_fname,temporary.user_password,temporary.user_place,&temporary.ticket_price,&temporary.user_numtick)!=EOF)
	{
		petrol=(userprofile*)malloc(sizeof(userprofile));
		strcpy(petrol->user_fname,temporary.user_fname);
		strcpy(petrol->user_password,temporary.user_password);
		strcpy(petrol->user_place,temporary.user_place);
		petrol->ticket_price=temporary.ticket_price;
		petrol->user_numtick=temporary.user_numtick;
		petrol->next=NULL;

		if(hello==NULL)
            hello=text=petrol;
		else
		{
			hello->next=petrol;
			hello=petrol;
		}
	}
	fclose(fileopen);
    return text;
}

void WriteToFile(userprofile *hello)
{
    FILE *fileopen;
    fileopen=fopen("users.txt","w");
    while(hello!=NULL)
    {
        fprintf(fileopen,"%s %s %s %f %d\n",hello->user_fname,hello->user_password,hello->user_place,hello->ticket_price,hello->user_numtick);
        hello=hello->next;
    }
    fclose(fileopen);
}

void ShowBrochure()
{
	system("CLS");
    printf("\tPRICE LIST\n=============================\n1. AA - Isla Gigantis Tours - P 3000\n2. BB - Mag-Aso Falls Tours - P 5000\n3. CC - Mambukal Resort Tours - P 2000\n4. DD - Boracay Beach Resort - P 10000\n"
           "5. EE - Whispering Palms Island Resort - P 12000\n6. FF - La Vista Highlands - P 5000\n7. GG - Punta Bulata Resort & Spa - P 7000\n8. HH - Big BamBoo Beach Resort - P 8000\n9. II - Nature's Village Resort - P 12000\n10. JJ - Artistic Diving & Beach Resort - P 14000\n");
}

void checking_ticket(userprofile *hello)
{
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,current_client))
            break;
        hello=hello->next;
    }
    if(!strcmp(hello->user_place,"\0") || hello->ticket_price==0.0 || hello->user_numtick==0)
    {
        printf("You do not have a ticket booked yet\n");
        return;
    }
    float tot=0.0;
    tot=(hello->ticket_price)*(hello->user_numtick);
    printf("You have booked %d tickets for a sum total of P %f for tour code %s\n",hello->user_numtick,tot,hello->user_place);
}

userprofile* Adding_Client(userprofile* hello)
{
    userprofile *trans;
    trans=hello;
    userprofile *newwonderers;
    newwonderers=(userprofile*)malloc(sizeof(userprofile));
    //fflush(stdin);
    printf("Enter Username or Email\n");
    scanf("%90s",newwonderers->user_fname);
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,newwonderers->user_fname))
        {
            printf("That email already exists\n");
            return trans;
        }
        hello=hello->next;
    }
    hello=trans;
    //fflush(stdin);
    printf("Enter password\n");
    scanf(" %20s[^\n]",newwonderers->user_password);
    newwonderers->next=NULL;
    strcpy(newwonderers->user_place,"N/A");
    newwonderers->ticket_price=0.0;
    newwonderers->user_numtick=0;

    if(hello==NULL)
    {
        hello=trans=newwonderers;
    }
    else
    {
        while(hello->next!=NULL)
        {
            hello=hello->next;
        }
        hello->next=newwonderers;
    }
    WriteToFile(trans);
    return trans;
}

void login_client(userprofile* hello)
{
    char client_username[100];
    char client_password[100];
    //fflush(stdin);
    printf("\n\n");
    printf("\t\tEnter Email/Username:\n\t\t");
    scanf("%90s",client_username);
    fflush(stdin);
    printf("\n\t\tEnter Password:\n\t\t");
    scanf(" %90s[^\n]",client_password);
    while(hello!=NULL)
    {
        if((!strcmp(hello->user_fname,client_username)) && (!strcmp(hello->user_password,client_password)))
        {
            currentwindow=login_system;
            strcpy(current_client,client_username);

            printf("\n\t\tLogin successful!\n");
            system("PAUSE");
            return;
        }
        else if((!strcmp(hello->user_fname,client_username)) && (strcmp(hello->user_password,client_password)))
        {
            printf("Password mismatch\n");
            return;
        }
        hello=hello->next;
    }
    printf("Sorry, no such user record was found\n");
}

void booking_ticket(userprofile *hello)
{
    userprofile *trans=hello;
    char place[100];
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,current_client))
            break;
        hello=hello->next;
    }
    if(hello==NULL)
        return;
    if(hello->ticket_price!=0.0)
    {
        printf("You must cancel your previous ticket before buying a new one\n");
        return;
    }
    ShowBrochure();
    float pricelist[]={3000.0,5000.0,2000.0,10000.0,12000.0,5000.0,7000.0,8000.0,12000.0,14000.0};
    fflush(stdin);
    printf("\nEnter place code (eg: AA, BB)\n");
    scanf(" %90[^\n]s",place);
    char choice;
    fflush(stdin);
    printf("\nWould You Like to Confirm Booking?\n[1] - Yes\n[2] - No\n");
    scanf("%5s",&choice);
    float price;
    if(choice!='1')
        return;
    if(strcmp(place,"LL")==0)
        price=pricelist[0];
    else if(strcmp(place,"AA")==0)
        price=pricelist[1];
    else if(strcmp(place,"BB")==0)
        price=pricelist[2];
    else if(strcmp(place,"CC")==0)
        price=pricelist[3];
    else if(strcmp(place,"DD")==0)
        price=pricelist[4];
    else if(strcmp(place,"EE")==0)
        price=pricelist[5];
    else if(strcmp(place,"FF")==0)
        price=pricelist[6];
    else if(strcmp(place,"GG")==0)
        price=pricelist[7];
    else if(strcmp(place,"HH")==0)
        price=pricelist[8];
    else if(strcmp(place,"II")==0)
        price=pricelist[9];
    else
    {
        printf("That tour code doesn't exist\n");
        return;
    }
    printf("Enter the number of tickets you want to book?\n");
    scanf("%d",&hello->user_numtick);
    if(hello->user_numtick==0)
        return;
    strcpy(hello->user_place,place);
    hello->ticket_price=price;
    WriteToFile(trans);
    printf("Bookings Done!!\n");
    system("PAUSE");

}

void printing_ticket(userprofile *hello)
{
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,current_client))
            break;
        hello=hello->next;
    }
    if(!strcmp(hello->user_place,"\0") || hello->ticket_price==0.0 || hello->user_numtick==0)
    {
        printf("You do not have a ticket booked yet\n");
        return;
    }
    float tot=0.0;
    tot=(hello->ticket_price)*(hello->user_numtick);
    FILE *fileopen;
    char filename[50];
    strcpy(filename,hello->user_fname);
    strcat(filename,"_ticket.txt");
    fileopen=fopen(filename,"w");
    if(fileopen==NULL)
    {
        printf("Problem opening the file\n");
        return;
    }
    if(fgetc(fileopen)==EOF)
    {
        fprintf("TOURISM TICKET\n===============\n\n");
	     fflush(stdin);
    }
    fprintf(fileopen,"Email ID: %s\nTour Code: %s\nTicket Cost: P %f\nNumber of tickets: %d\nTotal Cost: P %f\n",hello->user_fname,hello->user_place,hello->ticket_price,hello->user_numtick,tot);
    fclose(fileopen);
}
//TMS1353f
void cancelling_ticket(userprofile *hello)
{
    userprofile *trans=hello;
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,current_client))
            break;
        hello=hello->next;
    }

    int flag=-1;

    if(hello==NULL)
        printf("No such user\n");

    if(strcmp(hello->user_place,"AA")==0)
        flag++;
    else if(strcmp(hello->user_place,"BB")==0)
        flag++;
    else if(strcmp(hello->user_place,"CC")==0)
        flag++;
    else if(strcmp(hello->user_place,"DD")==0)
        flag++;
    else if(strcmp(hello->user_place,"EE")==0)
        flag++;
    else if(strcmp(hello->user_place,"FF")==0)
        flag++;
    else if(strcmp(hello->user_place,"GG")==0)
        flag++;
    else if(strcmp(hello->user_place,"HH")==0)
        flag++;
    else if(strcmp(hello->user_place,"II")==0)
        flag++;
    else if(strcmp(hello->user_place,"JJ")==0)
        flag++;
    else
    {
        printf("You haven't booked a tour yet\n");
        return;
    }
    if(flag==0)
    {
        printf("Your ticket has been successfully cancelled\nA refund of P %f for Tour Code %s for %d tickets will soon be made to your original source of purchase\n",hello->ticket_price,hello->user_place,hello->user_numtick);
        strcpy(hello->user_place,"N/A");
        hello->ticket_price=0.0;
        hello->user_numtick=0;
        WriteToFile(trans);
    }
}

void changing_pass(userprofile *hello)
{
    userprofile *trans=hello;
    char passcurr[100];
    fflush(stdin);
    printf("Enter your current password to continue:\n");
    scanf(" %[^\n]90s",passcurr);
    while(hello!=NULL)
    {
        if(!strcmp(hello->user_fname,current_client))
            break;
        hello=hello->next;
    }
    if(hello==NULL)
        return;
    if(!strcmp(passcurr,hello->user_password))
    {
        printf("Enter new password:\n");
        scanf(" %90[^\n]s",hello->user_password);
    }
    WriteToFile(trans);
}

void logout_client()
{
    if(currentwindow==main_menu || strcmp(current_client,"\0")==0)
    {
        printf("You must be logged in to logout\n");
        return;
    }
    strcpy(current_client,"\0");
    currentwindow=main_menu;
    printf("You have been successfully logged out\n");
}

void exit_system()
{
    printf("Exiting...\nThank you for Travelling with us\n\nPress \"Enter/Return\" to exit");
    char exitprog;
    fflush(stdin);
    scanf("%c",&exitprog);
}
