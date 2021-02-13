//
// Created by @chrys on 2/11/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "credit.h"
#include "../../utils/stringUtils.h"
#include "../../infra/io/crud/client_crud.h"
#include "../../infra/io/crud/credit_crud.h"
#include "../../core/client//client.h"

void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr)
{
    sprintf(creditStartDateStr, "%s", ctime(&creditStartDate));
    //Deleting eventual new line char
    char *p = strchr(creditStartDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
        //*(p + 1) = '\0';
    }
}

void goodToString(good_t good, char *goodStr)
{
    sprintf(goodStr, "%s %s %d", good.type, good.origin, good.value);
}

void readCreditId(char *buffer, credit_t *credit)
{
    int id = 0;
    do{
        printf("\nId du credit :");
        readString(buffer, 4);
        id = atoi(buffer);

        if(creditIdExists(id) == 0)
            printf("Cet id est deja utilise");

    } while (creditIdExists(id) == 0);
    credit->id = id;
}

void readCliId(char *buffer, credit_t *credit)
{
    int id = 0;
    do{
        printf("\nId du client :");
        readString(buffer, 4);
        id = atoi(buffer);

        if(creditIdExists(id) != 0)
            printf("Aucun client n'a cet identifiant");

    } while (creditIdExists(id) != 0);
    credit->clientId = id;
    client_t *client = loadClientCsv(id);

    char errorMessage[80] = "Desole, aucun credit ne peut etre octroye a ce client. ";
    switch (client->status)
    {
        case PRO_UNEMPLOYED:
            strcat(errorMessage, "(non salarie)");
            return;
        case PRO_CDD:
            strcat(errorMessage, "(CDD)");
            return;
        case PRO_INTERIM:
            strcat(errorMessage, "(interim)");
            return;
        case CDI_ESSAY:
            strcat(errorMessage, "(CDI essai)");
            break;

        case PRO_LIBERAL:
            printf("\nLe client a-t-il des revenus stables sur l'annee ? (1. Oui, 2. Non)");
            readString(buffer, 2);
            if(atoi(buffer) == 2)
            {
                printf("\n%s", errorMessage);
                return;
            }
            break;

        case CDI_VALIDATED:
            break;
    }

}

void readStartDate(char *buffer, credit_t *credit)
{
    //getting current time
    time_t rawTime;
    time(&rawTime);
    struct tm *timeInfo = localtime(&rawTime);
    credit->startDate = mktime(timeInfo);
}

void readIncomeSources(char *buffer, credit_t *credit)
{
    credit->incomeSources = malloc(50 * sizeof(char));
    printf("\nSources de revenus : ");
    readString(buffer, 50);
    strcpy(credit->incomeSources, buffer);
}

void readHealthState(char *buffer, credit_t *credit)
{
    credit->healthState = malloc(50 * sizeof(char));
    printf("\nEtat de sante : ");
    readString(buffer, 50);
    strcpy(credit->healthState, buffer);
}

void readAnnualFiscalIncome(char *buffer, credit_t *credit)
{
    printf("\nRevenu fiscal de l'annee de reference");
    printf("\nsur le dernier avis d'imposition :");
    readString(buffer, 50);
    unsigned long annualFiscalIncome = atol(buffer);

    //Logic to implement later
}

void readSalary(char *buffer, credit_t *credit)
{
    printf("\nSalaire mensuel : ");
    readString(buffer, 10);
    credit->salary = atol(buffer);
}

void readAvailableSaving(char *buffer, credit_t *credit)
{
    printf("\nMontant d'epargne disponible :");
    readString(buffer, 10);
    unsigned int availableSaving = atoi(buffer);
    //Logic to implement later
}

void readGood(char *buffer, credit_t *credit)
{
    good_t good;
    good.origin = malloc(50 * sizeof(char));
    char *goodTypes[] = {
            "Maison neuve",
            "Maison a renover",
            "Immeuble",
            "Appartement",
            "Studio",
            "Place de parking"};
    printf("\nInformations sur le bien voulu:\n");
    printf("\tType de bien voulu :\n");
    printf("\t\t1. %s\n", *(goodTypes + 0));
    printf("\t\t2. %s\n", *(goodTypes + 1));
    printf("\t\t3. %s\n", *(goodTypes + 2));
    printf("\t\t4. %s\n", *(goodTypes + 3));
    printf("\t\t5. %s\n", *(goodTypes + 4));
    printf("\t\t6. %s\n", *(goodTypes + 5));
    printf("\t\t7. Autre\n");
    printf("\t\tVotre choix : ");
    readString(buffer, 2);
    int choix = atoi(buffer);
    switch (choix)
    {
        case 1:
            strcpy(good.type, *(goodTypes + 0));
            break;
        case 2:
            strcpy(good.type, *(goodTypes + 1));
            break;
        case 3:
            strcpy(good.type, *(goodTypes + 2));
            break;
        case 4:
            strcpy(good.type, *(goodTypes + 3));
            break;
        case 5:
            strcpy(good.type, *(goodTypes + 4));
            break;
        case 6:
            strcpy(good.type, *(goodTypes + 5));
            break;
        case 7:
            printf("\n\t\tType de bien : ");
            readString(buffer, 20);
            strcpy(good.type, buffer);
            break;
        default:
            break;
    }

    printf("\n\tOrigine du bien (ville) :");
    readString(buffer, 50);
    strcpy(good.origin, buffer);

    printf("\n\tValeur :");
    readString(buffer, 10);
    good.value = atoi(buffer);
    printf("\n");

    credit->good = good;
}

void readBankRate(char *buffer, credit_t *credit)
{
    printf("\nType de taux souhaite :\n");
    printf("\t1. Fixe\n");
    printf("\t2. Variable\n");
    printf("\t3. Cape\n");
    printf("\tVotre choix :");
    readString(buffer, 50);
    switch (atoi(buffer))
    {
        case 1:
            credit->bankRate = FIX;
            break;
        case 2:
            credit->bankRate = VARIABLE;
            break;
        case 3:
            credit->bankRate = CAPED;
            break;
        default:
            break;
    }
    printf("\n");
}

void readFiscalResidence(char *buffer, credit_t *credit)
{
    printf("\nResidence Fiscale\n");
    printf("\t1. France\n");
    printf("\t2. Union europeenne\n");
    printf("\t3. Hors union europeenne\n");
    printf("\tVotre choix :");
    readString(buffer, 50);
    switch (atoi(buffer))
    {
        case 1:
            credit->fiscalResidence = FRANCE;
            break;
        case 2:
            credit->bankRate = EU;
            break;
        case 3:
            credit->bankRate = NOT_EU;
            printf("\nCredit non octroye (hors UE)\n");
            break;
        default:
            break;
    }

}


void createCredit()
{

}