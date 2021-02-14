//
// Created by Roy on 12/02/2021.
//

#include<stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../../core/client/client.h"
#include "../../utils/strings/stringUtils.h"
#include "../../core/credit/credit.h"


void run() {
    char userChoice;
    const int choiceList[] = {0, 1, 2, 3, 4, 5, 6, 7};
    const int choiceListLength = sizeof(choiceList) / sizeof(choiceList[0]);
    system("cls");
    printMenuHeader();
    printf("*********************************************************************************\n");
    printf("*\t1. Creer un client\t\t\t\t\t\t\t*\n");
    printf("*\t2. Modifier un client\t\t\t\t\t\t\t*\n");
    printf("*\t3. Supprimer un client\t\t\t\t\t\t\t*\n");
    printf("*\t4. Octroyer un credit\t\t\t\t\t\t\t*\n");
    printf("*\t5. Afficher le Capital restant\t\t\t\t\t\t*\n");
    printf("*\t6. Afficher le tableau d'amortissement du credit\t\t\t*\n");
    printf("*\t0. Quitter\t\t\t\t\t\t\t\t*\n");
    printf("*********************************************************************************\n");
    printf("Votre choix : ");

    int canExitLoop = 0;
    char buffer[3] = "";
    do {
        readString(buffer, 2);
        userChoice = atoi(buffer);
        printf("\n");

        switch (userChoice) {
            default:
                system("cls");
                break;

            case 0:
                system("cls");
                exitMenu();
                break;

            case 1:
                system("cls");
                client_t *client = createClient();
                printClient(*client);
                system("pause");
                break;

            case 2:
                system("cls");
                updateClient();
                system("pause");
                break;

            case 3:
                system("cls");
                deleteClient();
                system("pause");
                break;

            case 4:
                system("cls");
                createCredit();
                system("pause");
                break;

            case 5:
                system("cls");
                printRemainingCapital();
                system("pause");
                break;

            case 6:
                system("cls");
                printCushioningRate();
                system("pause");
                break;
        }

        canExitLoop = isNumberInList(userChoice, choiceList, choiceListLength);
    } while (canExitLoop == 0);

}

void printRemainingCapital() {
    // TODO: Remaining Capital
    printf("Print remaining totalRebate\n");
}

void printCushioningRate() {
    // TODO: Caushioning Rate
    printf("Print cushioning rate\n");
}

void printMenuHeader() {
    FILE *file = fopen("../cli/menu_header", "r");
    if (file == NULL)
        return;
    char character;
    do {
        character = fgetc(file);
        printf("%c", character);
    } while (character != EOF);
    printf("\n");
}

int isNumberInList(const int number, const int list[], const int listSize) {
    for (int i = 0; i < listSize; ++i) {
        if (number == list[i])
            return 1;
    }
    return 0;
}

void exitMenu() {
    printf(" A bientot sur Mortgage!\n");
    system("exit");
}


