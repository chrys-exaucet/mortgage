//
// Created by @chrys on 2/11/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "credit.h"
#include "../../utils/strings/stringUtils.h"
#include "../../infra/io/crud/client_crud.h"
#include "../../infra/io/crud/credit_crud.h"
#include "../../core/client//client.h"

void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr)
{
    strftime(creditStartDateStr, 99, "%d/%m/%Y", gmtime(&creditStartDate));
    //Deleting eventual new line char
    char *p = strchr(creditStartDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
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

int readCliId(char *buffer, credit_t *credit)
{
    int id = 0;
    do{
        printf("\nId du client :");
        readString(buffer, 4);
        id = atoi(buffer);

        if(clientIdExists(id) != 0)
            printf("Aucun client n'a cet identifiant");

    } while (clientIdExists(id) != 0);
    credit->clientId = id;
    client_t *client = loadClientCsv(id);

    char errorMessage[100] = "Desole, aucun credit ne peut etre octroye a ce client. ";
    switch (client->status)
    {
        case PRO_UNEMPLOYED:
            strcat(errorMessage, "(non salarie)");
            printf("\n%s", errorMessage);
            return -1;
        case PRO_CDD:
            strcat(errorMessage, "(CDD)");
            printf("\n%s", errorMessage);
            return -1;
        case PRO_INTERIM:
            strcat(errorMessage, "(interim)");
            printf("\n%s", errorMessage);
            return -1;
        case CDI_ESSAY:
            strcat(errorMessage, "(CDI essai)");
            printf("\n%s", errorMessage);
            return -1;

        case PRO_LIBERAL:
            printf("\nLe client a-t-il des revenus stables sur l'annee ? (1. Oui, 2. Non)");
            readString(buffer, 2);
            if(atoi(buffer) == 2)
            {
                strcat(errorMessage, "(revenus instables)");
                printf("\n%s", errorMessage);
                return -1;
            }
            return 0;

        case CDI_VALIDATED:
            return 0;
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
    printf("\nEtat de sante : \n");
    printf("\t1. Bien portant\n");
    printf("\t2. Souffrant d'une pathlogie grave\n");
    printf("\tVotre choix : ");
    readString(buffer, 3);
    switch (atoi(buffer))
    {
        default:
            strcpy(credit->healthState, "Bien portant");
            break;
        case 1:
            strcpy(credit->healthState, "Bien portant");
            break;
        case 2:
            strcpy(credit->healthState, "Pathologie grave");
            break;

    }
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
    printf("\nSur combien de temps le client percoit-il ce salaire ?\n");
    printf("\t1. 12 mois\n");
    printf("\t2. 13 mois\n");
    printf("\tVotre choix :");
    readString(buffer, 10);
    credit->annualIncome = atoi(buffer) * credit->salary;
}

int readAvailableSaving(char *buffer, credit_t *credit)
{
    printf("\nMontant d'epargne disponible :");
    readString(buffer, 10);
    unsigned int availableSaving = atoi(buffer);
    //TODO: Logic to implement later
    return 0;
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

    do
    {
        printf("\n\tValeur :");
        readString(buffer, 10);
        good.value = atoi(buffer);
        if(good.value <= 0)
            printf("\nValeur invalide.");
    } while (good.value <= 0);
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

int readFiscalResidence(char *buffer, credit_t *credit)
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
            return 0;
        case 2:
            credit->fiscalResidence = EU;
            return 0;
        case 3:
            credit->fiscalResidence = NOT_EU;
            printf("\nCredit non octroye (hors UE)\n");
            return -1;
        default:
            return -1;
    }

}

void readDuration(char *buffer, credit_t *credit)
{
    do
    {
        printf("\nDuree du credit :\n");
        printf("\t1. 15 ans\n");
        printf("\t2. 20 ans\n");
        printf("\t3. 25 ans\n");
        printf("\tVotre choix : ");
        readString(buffer, 3);
    }while(atoi(buffer) < 1 || atoi(buffer) > 3);

    switch (atoi(buffer))
    {
        case 1:
            credit->duration = FIFTEEN;
            break;
        case 2:
            credit->duration = TWENTY;
            break;
        case 3:
            credit->duration = TWENTY_FIVE;
            break;
    }

}

credit_t *createCredit()
{
    credit_t *credit = malloc(sizeof (credit_t));
    char buffer[50] = "";


    readCreditId(buffer, credit);
    if (readCliId(buffer, credit) != 0)
        return credit;
    readGood(buffer, credit);
    if (readAvailableSaving(buffer, credit) != 0)
        return credit;
    readSalary(buffer, credit);
    readIncomeSources(buffer, credit);
    readAnnualFiscalIncome(buffer, credit);
    if (readFiscalResidence(buffer, credit) != 0)
        return credit;
    readHealthState(buffer, credit);
    readBankRate(buffer, credit);
    readDuration(buffer, credit);

    //Things to add later by Chrys

    saveCreditCsv(*credit);
    return credit;

}

void printCredits()
{

}