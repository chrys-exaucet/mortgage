//
// Created by Roy on 12/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


int isNumberInList(const int number, const int list [], const int listSize)
{
    for (int i = 0; i < listSize; ++i) {
        if (number == list[i])
            return 1;
    }
    return 0;
}

void exitMenu() {
    printf("Exit menu\n");
}

void createCustomer() {
    printf("Create Customer");
}

void updateCustomer() {
    printf("Update Customer");
}

void deleteCustomer() {
    printf("Delete Customer");
}

void generateIban() {
    printf("Generate IBAN");
}

void grantCredit() {
    printf("Grant credit");
}

void printRemainingCapital() {
    printf("Print remaining capital");
}

void printCushioningRate() {
    printf("Print cushioning rate");
}

void printMenuHeader()
{
    FILE *file = fopen("../infra/db/menu_header", "r");
    if(file ==  NULL)
        return;
    char character;
    do {
        character = fgetc(file);
        printf("%c", character);
    } while (character != EOF);
    printf("\n");
}

void printMenu()
{
    char userChoice;
    const int choiceList [] = {0, 1, 2, 3, 4, 5, 6, 7};
    const int choiceListLength = sizeof(choiceList) / sizeof (choiceList[0]);
    printMenuHeader();
    printf("*********************************************************************************\n");
    printf("*\t1. Creer un client\t\t\t\t\t\t\t*\n");
    printf("*\t2. Modifier un client\t\t\t\t\t\t\t*\n");
    printf("*\t3. Supprimer un client\t\t\t\t\t\t\t*\n");
    printf("*\t4. IBAN\t\t\t\t\t\t\t\t\t*\n");
    printf("*\t5. Octroyer un credit\t\t\t\t\t\t\t*\n");
    printf("*\t6. Afficher le capital restant\t\t\t\t\t\t*\n");
    printf("*\t7. Afficher le taux d'amortissement du credit\t\t\t\t*\n");
    printf("*\t0. Quitter\t\t\t\t\t\t\t\t*\n");
    printf("*********************************************************************************\n");
    printf("Votre choix : ");

    int canExitLoop = 0;
    do
    {
        scanf("%d", &userChoice);
        printf("\n");

        switch (userChoice)
        {
            default:
                break;

            case 0:
                printf("Vous avez choisi le %d\n", userChoice);
                exitMenu();
                break;

            case 1:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                createCustomer();
                break;

            case 2:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                updateCustomer();
                break;

            case 3:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                deleteCustomer();
                break;

            case 4:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                generateIban();
                break;

            case 5:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                grantCredit();
                break;

            case 6:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                printRemainingCapital();
                break;

            case 7:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                printCushioningRate();
                break;
        }

        canExitLoop= isNumberInList(userChoice, choiceList, choiceListLength);
    } while ( canExitLoop == 0);

}
