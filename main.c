#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "rental.h"
#include "customer.h"
#include "game.h"

int displayMainMenu()
{
    int choice;
    printf("\nMain Menu:\n");
    printf("1. Customer Options\n");
    printf("2. Game Options\n");
    printf("3. Rental Options\n");
    printf("4. Exit the Program\n");
    printf("Choose an option (1-4): ");
    scanf("%d", &choice);
    return choice;
}

int displaySubMenu(const char *menuName)
{
    int choice;
    printf("\n%s Submenu:\n", menuName);
    printf("1. Add\n");
    printf("2. Search\n");
    printf("3. Display All\n");
    printf("4. Back to Main Menu\n");
    printf("Choose an option (1-4): ");
    scanf("%d", &choice);
    return choice;
}

void handleSubMenuc(const char *menuName)
{
    TOF tof;
    tof = *open_file("customer.data", "N");
    int id;
    Customer c;
    while (1)
    {
        int choice = displaySubMenu(menuName);
        switch (choice)
        {
        case 1:

            printf("Adding in %s...\n", menuName);
            break;
        case 2:

            printf("enter ID: ");
            scanf("%d", id);
            if (search_customer(&tof, id, &c) == 1)
            {
                printf("ID :%d, First name: %s, Last name: %s ,ContactInfo: %s\n", c.customerid, c.firstName, c.lastName, c.contactInfo);
            }
            else
            {
                printf("the game doesn't exist \n");
                printf("Searching in %s...\n", menuName);
                break;
            case 3:
                printf("Displaying all in %s...\n", menuName);
                displayAllcustomer(&tof);
                break;
            case 4:
                printf("Returning to Main Menu from %s...\n", menuName);
                return;
            default:
                printf("Invalid choice! Please try again.\n");
            }
        }
    }

    void handleSubMenug(const char *menuName)
    {

        TOF tof;
        Game g;
        while (1)
        {

            int choice = displaySubMenu(menuName);
            switch (choice)
            {
            case 1:
                printf("enter ID: ");
                scanf("%d", &g.gameid);
                printf("enter Title: ");
                scanf("%s", &g.title);
                printf("enter rentalprice: ");
                scanf("%f", &g.rentalPrice);
                insert_game(&g);
                printf("Adding in %s...\n", menuName);

                break;
            case 2:

                int id;
                printf("enter ID: ");
                scanf("%d", id);
                if (search_game(&tof, id, g) == 1)
                {
                    printf("id: %d \n title: %s \n rentalprice: %f \n", g.gameid, g.title, g.rentalPrice);
                }
                else
                {
                    printf("the game doesn't exist \n");
                }
                printf("Searching in %s...\n", menuName);
                break;

            case 3:

                printf("Displaying all in %s...\n", menuName);
                displayAllgame(&tof);
                break;

            case 4:

                printf("Returning to Main Menu from %s...\n", menuName);
                return;
            default:
                printf("Invalid choice! Please try again.\n");
            }
        }
    }

    void handleSubMenur(const char *menuName)
    {

        RentalD rd;
        RentalR rr, r;
        TOF tof;
        Customer c;
        Game g;
        int gid, cid, id;

        while (1)
        {
            int choice = displaySubMenu(menuName);
            switch (choice)
            {
            case 1:
                printf("enter ID: ");
                scanf("%d", &rr.rentalID);
                printf("enter customer id: ");
                scanf("%d", &cid);
                printf("enter game id: ");
                scanf("%d", &gid);
                printf("enter rental date: ");
                scanf("%s", &rr.rentalDate);
                printf("enter return date: ");
                scanf("%s", &rr.returnDate);

                if (search_game(&tof, gid, &g) == 1)
                {
                    rr.game = g;
                }
                else
                {
                    printf("the game doesn't exist \n");
                }

                if (search_customer(tof, cid, c) == 1)
                {
                    rr.customer = c;
                }
                else
                {
                    printf("the game doesn't exist \n");
                }

                saverentaldisk(tof, rr);

                printf("Adding in %s...\n", menuName);

                break;
            case 2:

                printf("enter ID: ");
                scanf("%d", &id);

                if (search_rental(&tof, &id, &r) == 1)
                {
                    printf("id:");
                }
                else
                {
                    printf("the game doesn't exist \n");

                    printf("Searching in %s...\n", menuName);

                    break;
                case 3:
                    printf("Displaying all in %s...\n", menuName);
                    displayAllrentals(tof);
                    break;
                case 4:
                    printf("Returning to Main Menu from %s...\n", menuName);
                    return;
                default:
                    printf("Invalid choice! Please try again.\n");
                }
            }
        }

        int main()
        {

            {
                TOF *tof = NULL;
                char path[100];
                char mode;
                int choix;

                printf("Entrez le chemin du fichier : ");
                scanf("%s", path);

                printf("Mode d'ouverture (A: Ouvrir un fichier existant, N: Nouveau fichier) : ");
                scanf(" %c", &mode);

                tnof = open_file(path, mode);

                if (tnof == NULL)
                {
                    printf("Erreur lors de l'ouverture du fichier.\n");
                    return -1;
                }

                do
                {

                    while (1)
                    {
                        int choice = displayMainMenu();
                        switch (choice)
                        {
                        case 1:
                            handleSubMenuc("Customer Options");
                            break;
                        case 2:
                            handleSubMenug("Game Options");
                            break;
                        case 3:
                            handleSubMenur("Rental Options");
                            break;
                        case 4:
                            printf("Exiting the program. Goodbye!\n");
                            return 0;
                        default:
                            printf("Invalid choice! Please try again.\n");
                        }
                    }
                }
            }
        }
    }
}