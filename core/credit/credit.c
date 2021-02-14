//
// Created by @chrys on 2/11/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "credit.h"
#include "../../utils/strings/stringUtils.h"
#include "../../utils/time/time_utils.h"
#include "../../infra/io/crud/client_crud.h"
#include "../../infra/io/crud/credit_crud.h"

void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr) {
    strftime(creditStartDateStr, 99, "%d/%m/%Y", gmtime(&creditStartDate));
    //Deleting eventual new line char
    char *p = strchr(creditStartDateStr, '\n');
    if (p != NULL) {
        *p = '\0';
    }
}

void goodToString(good_t good, char *goodStr) {
    sprintf(goodStr, "%s %s %d", good.type, good.origin, good.value);
}

void readCreditId(char *buffer, credit_t *credit) {
    int id;
    do {
        printf("\nId du credit :");
        readString(buffer, 4);
        id = atoi(buffer);

        if (creditIdExists(id) == 0)
            printf("Cet id est deja utilise");

    } while (creditIdExists(id) == 0);
    credit->id = id;
}

int readClientStatus(char *buffer, credit_t *credit) {
    int id;
    do {
        printf("\nId du client :");
        readString(buffer, 4);
        id = atoi(buffer);

        if (clientIdExists(id) != 0)
            printf("Aucun client n'a cet identifiant");

    } while (clientIdExists(id) != 0);
    credit->clientId = id;
    client_t *client = loadClientCsv(id);

    char errorMessage[100] = "Desole, aucun credit ne peut etre octroye a ce client. ";
    switch (client->status) {
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
            printf("\nAvez vous des revenus stables sur l'annee ? (1. Oui, 2. Non)");
            readString(buffer, 2);
            if (atoi(buffer) == 2) {
                strcat(errorMessage, "(revenus instables)");
                printf("\n%s", errorMessage);
                return -1;
            }
            return 0;

        case CDI_VALIDATED:
            return 0;
    }

}

void readStartDate(credit_t *credit) {
    //getting current time
    time_t rawTime;
    time(&rawTime);
    struct tm *timeInfo = localtime(&rawTime);
    credit->startDate = mktime(timeInfo);
}


void readGood(char *buffer, credit_t *credit) {
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
    int choice = atoi(buffer);
    switch (choice) {
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

    do {
        printf("\n\tValeur :");
        readString(buffer, 10);
        good.value = atoi(buffer);
        if (good.value <= 0)
            printf("\nValeur invalide.");
    } while (good.value <= 0);
    printf("\n");

    credit->good = good;
}

void readOtherIncomeSources(char *buffer, credit_t *credit) {
    credit->otherIncomeSources = 0;
    printf("\nAvez vous d'autres revenus sur l'annee "
           "(primes, bonus, salaires variables, gains poker, paris sportifs, pensions alimentaires)? "
           "Si, oui, veuillez entrer le montant "
           "(en Euros), Sinon, entrez O : ");
    readString(buffer, 50);
    credit->otherIncomeSources = atol(buffer);
}

void readAnnualFiscalIncome(char *buffer, credit_t *credit) {
    printf("\nRevenu fiscal de l'annee de reference");
    printf("\nsur le dernier avis d'imposition :");
    readString(buffer, 50);
    unsigned long annualFiscalIncome = atol(buffer);
    if (annualFiscalIncome != credit->annualIncome)
        printf("\nVous devrez justifier cette variation de revenus avec documents");
    credit->annualFiscalIncome = annualFiscalIncome;
}

int readFiscalResidence(char *buffer, credit_t *credit) {
    do {
        printf("\nResidence Fiscale\n");
        printf("\t1. France\n");
        printf("\t2. Union europeenne\n");
        printf("\t3. Hors union europeenne\n");
        printf("\tVotre choix :");
        readString(buffer, 50);
    } while (atoi(buffer) != 1 && atoi(buffer) != 2 && atoi(buffer) != 3);

    switch (atoi(buffer)) {
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

void readHealthState(char *buffer, credit_t *credit) {

    credit->healthState = malloc(50 * sizeof(char));
    do {
        printf("\nEtat de sante : \n");
        printf("\t1. Bien portant\n");
        printf("\t2. Souffrant d'une pathlogie grave\n");
        printf("\tVotre choix: ");
        readString(buffer, 3);
    } while (atoi(buffer) != 1 && atoi(buffer) != 2);

    switch (atoi(buffer)) {
        case 1:
            strcpy(credit->healthState, "Bien portant");
            break;
        case 2:
            strcpy(credit->healthState, "Pathologie grave");
            break;
        default:
            strcpy(credit->healthState, "Bien portant");
            break;
    }
}

void readSalary(char *buffer, credit_t *credit) {

    printf("\nSalaire mensuel (en Euros) : ");
    readString(buffer, 10);
    credit->monthlySalary = atol(buffer);
    do {
        printf("\nSur combien de mois est ce que vous percevez le salaire mensuel ?\n");
        printf("\t1. 12 mois\n");
        printf("\t2. 13 mois\n");
        printf("\tEntrez votre choix:");
        readString(buffer, 10);
    } while (atoi(buffer) != 1 && atoi(buffer) != 2);

    switch (atoi(buffer)) {
        case 1:
            credit->annualIncome = 12 * credit->monthlySalary + credit->otherIncomeSources;
            break;
        case 2 :
            credit->annualIncome = 13 * credit->monthlySalary + credit->otherIncomeSources;
            break;
    }
}

int readAvailableSaving(char *buffer, credit_t *credit) {
    printf("\nMontant d'epargne disponible (Montant de l'apport personnel) :");
    readString(buffer, 10);
    float availableSaving = atoi(buffer);
    if (availableSaving <= credit->good.value * 0.1) {
        printf("\n Votre epargne personnel vous permet pas d'obtenir le financement necessaire à l'octroi de ce credit immobilier");
        return 1;
    }
    credit->availableSaving = availableSaving;
    return 0;
}

void readBankRate(char *buffer, credit_t *credit) {
    do {
        printf("\nType de taux souhaite :\n");
        printf("\t1. Fixe\n");
        printf("\t2. Variable\n");
        printf("\t3. Cape\n");
        printf("\tVotre choix :");
        readString(buffer, 50);
    } while (atoi(buffer) != 1 && atoi(buffer) != 2 && atoi(buffer) != 3);

    switch (atoi(buffer)) {
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

void readDuration(char *buffer, credit_t *credit) {
    do {
        printf("\nDuree du credit :\n");
        printf("\t1. 15 ans\n");
        printf("\t2. 20 ans\n");
        printf("\t3. 25 ans\n");
        printf("\tVotre choix : ");
        readString(buffer, 3);
    } while (atoi(buffer) < 1 || atoi(buffer) > 3);

    switch (atoi(buffer)) {
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

void readMonthlyRebate(char *buffer, credit_t *credit) {
    credit->otherRebates = 0;
    printf("\nMontant de remboursement mensuel de vos autres credits en cours"
           "(en Euros): ");
    readString(buffer, 50);
    credit->otherRebates = atol(buffer);
}

void readMonthlyPension(char *buffer, credit_t *credit) {
    credit->monthlyPension = 0;

    printf("\nMontant de la  pension alimentaires ( en Euros). Entrez 0 si aucune pension:"
           "(en Euros): ");
    readString(buffer, 50);
    credit->monthlyPension = atol(buffer);
}

void readFixedCharges(char *buffer, credit_t *credit) {
    credit->fixedChargesAmount = 0;
    printf("\nMontant de vos autres charges fixes (loyer, alimentation, abonnements et souscriptions,"
           " en Euros): ");
    readString(buffer, 50);
    credit->fixedChargesAmount = atol(buffer);
}

void calculateCreditParams(credit_t *credit) {
    // initial values (before month 1)
    credit->good.cost = credit->good.value + DEFAULT_NOTARY_FEE;
    credit->dossierFee = credit->good.cost * 0.001;
    credit->insuranceCoast = getInsurenceTax(*credit) * credit->good.cost;
    credit->taeg = getCurrentCreditTax(*credit) + 0.001 + getInsurenceTax(*credit);
    credit->tmi = credit->taeg / 12;
    credit->cost = credit->good.cost * credit->taeg;
    credit->totalRebate = credit->good.cost + credit->cost;
    credit->monthlyPayment = credit->totalRebate / (credit->duration * 12);
    credit->crd = credit->totalRebate;
    credit->interest = credit->crd * getCurrentCreditTax(*credit);
}

int canHaveCredit(credit_t *credit) {

    calculateCreditParams(credit);

    float necessaryAmountToLive =
            (credit->annualIncome / 12) - (credit->monthlyPension + credit->otherRebates + credit->fixedChargesAmount);

    if (necessaryAmountToLive < 1.25 * credit->monthlyPayment) {
        printf("\nVotre reste à vivre ne vous permet pas d’obtenir le financement necessaire à l’octroi de ce credit immobilier :\n");
        return 1;
    }
    if (credit->monthlyPayment > 0.33 * (credit->annualIncome / 12)) {
        printf("\nVotre capacité d’endettement ne vous permet pas d’obtenir le financement nécessaire à l’octroi de ce crédit immobilier :\n");
        return 1;
    }
    if ((credit->otherRebates) &&
        (credit->monthlyPayment + credit->otherRebates > 0.33 * (credit->annualIncome / 12))) {
        printf("\nVotre capacité d’endettement ne vous permet pas d’obtenir le financement nécessaire à l’octroi de ce crédit immobilier :\n");

        return 1;
    }
    return 0;
}

credit_t *createCredit() {
    credit_t *credit = malloc(sizeof(credit_t));
    char buffer[50] = "";


    readCreditId(buffer, credit);
    if (readClientStatus(buffer, credit) != 0)
        return credit;
    readGood(buffer, credit);
    if (readAvailableSaving(buffer, credit) != 0)
        return credit;
    readSalary(buffer, credit);
    readOtherIncomeSources(buffer, credit);
    readAnnualFiscalIncome(buffer, credit);
    if (readFiscalResidence(buffer, credit) != 0)
        return credit;
    readHealthState(buffer, credit);
    readBankRate(buffer, credit);
    readDuration(buffer, credit);
    readMonthlyRebate(buffer, credit);
    readMonthlyPension(buffer, credit);
    readFixedCharges(buffer, credit);
    readStartDate(credit);
    if (canHaveCredit(credit) != 0)
        return credit;
    updateClientCsv(*loadClientCsv(credit->clientId));
    saveCreditCsv(*credit);

    return credit;

}


time_t getDateIncrementedByMonths(time_t date, int monthsNumber) {
    return addMonthsToDate(date, monthsNumber);
}

float getFixedCreditTax() {
    return EURIBOR_FIXED_BANK_RATE;
}

float getVariableCreditTax(credit_t credit) {
    time_t now = time(0);
    float tax = VARIABLE_BANK_RATE;

    int years = getYearDiff(now, credit.startDate);
    if (years >= 5)
        tax = VARIABLE_BANK_RATE * 4 - 0.25 * (years - 4);
    else
        tax = VARIABLE_BANK_RATE * years;

    return tax;
}

float getCapedCreditTax(credit_t credit) {
    time_t now = time(0);
    float tax = VARIABLE_BANK_RATE;

    int years = getYearDiff(now, credit.startDate);
    if (years >= 5)
        tax = VARIABLE_BANK_RATE * 4 - 0.25 * (years - 4);
    else
        tax = VARIABLE_BANK_RATE * years;

    if (tax > CAPED_BANK_RATE_LIMIT)
        tax = CAPED_BANK_RATE_LIMIT;

    return tax;
}

float getCurrentCreditTax(credit_t credit) {
    switch (credit.bankRate) {
        case FIX:
            return getFixedCreditTax();
        case VARIABLE:
            return getVariableCreditTax(credit);
        case CAPED:
            return getCapedCreditTax(credit);
    }
}

float getInsurenceTax(credit_t credit) {
    if (strcmp(credit.healthState, "Pathologie grave") == 0)
        return BAD_HEALTH_CARE_TAX;
    return GOOD_HEALTH_CARE_TAX;
}

float getTAEG(credit_t credit) {
    return getCurrentCreditTax(credit) + credit.dossierFee * 0.001 + credit.insuranceCoast;
}

float getTMI(credit_t credit) {
    return getTAEG(credit) / 12;
}

float getCreditCost(credit_t credit) {
    return credit.good.cost * getTAEG(credit);
}

float getTotalRebate(credit_t credit) {
    return credit.good.cost + getCreditCost(credit);
}

float getCapital(credit_t credit, int month) {
    return credit.monthlyPayment + getInterest(credit, month);
}

float getCRD(credit_t credit, int month) {
    if (month == 36)
        return 0;
    if (month == 0)
        return credit.crd;
    else
        return getCRD(credit, month - 1) - getCapital(credit, month - 1);
}

float getInterest(credit_t credit, int month) {
    return getCRD(credit, month) * getCurrentCreditTax(credit);
}

