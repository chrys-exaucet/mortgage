//
// Created by Roy on 12/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../core/client/client.h"
#include "../utils/stringUtils.h"


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
    system("exit");
}

void generateIban() {
    printf("Generate IBAN\n");
}

void grantCredit() {
    printf("Grant credit\n");
}

void printRemainingCapital() {
    printf("Print remaining capital\n");
}

void printCushioningRate() {
    printf("Print cushioning rate\n");
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
    system("cls");
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
    char buffer[3] = "";
    do
    {
        readString(buffer, 2);
        userChoice = atoi(buffer);
        printf("\n");

        switch (userChoice)
        {
            default:
                system("cls");
                break;

            case 0:
                printf("Vous avez choisi le %d\n", userChoice);
                system("cls");
                exitMenu();
                break;

            case 1:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                createClient();
                system("pause");
                break;

            case 2:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                updateClient();
                system("pause");
                break;

            case 3:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                deleteClient();
                system("pause");
                break;

            case 4:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                generateIban();
                system("pause");
                break;

            case 5:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                grantCredit();
                system("pause");
                break;

            case 6:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                printRemainingCapital();
                system("pause");
                break;

            case 7:
                system("cls");
                printf("Vous avez choisi le %d\n", userChoice);
                printCushioningRate();
                system("pause");
                break;
        }

        canExitLoop= isNumberInList(userChoice, choiceList, choiceListLength);
    }while(canExitLoop == 0);

}
