#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tour.h"
userprofile* InitializeListing(userprofile*);
userprofile* Adding_Client(userprofile*);


int main()
{
    printf("\t\t\t**** || TOURISM MANAGEMENT SYSTEM || ****\n");
    userprofile *hello=NULL;
    int choice1,choice2;
    hello=InitializeListing(hello);
    while (1)
    {

        if(currentwindow==main_menu)
        {

            printf("\n\t\t\t\tAdd User - 1\n\t\t\t\tLogin User - 2\n\t\t\t\tBrochure - 3\n\t\t\t\tExit - 4\n\n\t\t\t\tEnter:");
            scanf("%d",&choice1);
            switch(choice1)
            {
                case 1:
                    hello=Adding_Client(hello);
                    break;
                case 2:
                    login_client(hello);
                    break;
                case 3:
                    ShowBrochure();
                    break;
                case 4:
                    exit_system();
                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
        else if(currentwindow==login_system)
        {
        system("CLS");
        printf("\n\t\t\t\t=========================");
		printf("\n\t\t\t\tTOURISM MANAGEMENT SYSTEM");
		printf("\n\t\t\t\t=========================\n");
            printf("\n\t\t\t\tBook Package - 1\n\t\t\t\tCheck Ticket - 2\n\t\t\t\tPrint Ticket - 3\n\t\t\t\tCancel Ticket - 4\n\t\t\t\tChange Password - 5"
                   "\n\t\t\t\tLogout User - 6\n\t\t\t\tBrochure - 7\n\t\t\t\tExit - 8\n");
            scanf("%d",&choice2);
            switch(choice2)
            {
                case 1:
                    booking_ticket(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 2:
                    checking_ticket(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 3:
                    printing_ticket(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 4:
                    cancelling_ticket(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 5:
                    changing_pass(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 6:
                    logout_client(hello);
                    system("PAUSE");
                    system("CLS");
                    break;
                case 7:
                    ShowBrochure();
                    system("PAUSE");
                    system("CLS");
                    break;
                case 8:
                    exit_system();
                    exit(0);
                    break;
                default:
                    printf("Not a valid input at this stage\n");
            }
        }
    }
    return 0;
}