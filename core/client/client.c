//
// Created by @chrys on 2/11/2021.
//

//
// Created by Roy on 2/12/2021.
//


#include "client.h"
#include "../../utils/strings/stringUtils.h"
#include "../../infra/io/parser.csv/csv.h"
#include "../../utils/file/file_utils.h"
#include "../../infra/io/crud/client_crud.h"
#include "../../infra/io/crud/credit_crud.h"
#include "../../utils/time/time_utils.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int lastAccountNumber = DEFAULT_ACCOUNT_NUMBER;
int lastKey = DEFAULT_KEY;

void readFirstName(char *buffer, client_t *client) {
    printf("\nPrenoms : ");
    readString(buffer, 50);
    strcpy(client->firstName, buffer);
}

void readLastName(char *buffer, client_t *client) {
    printf("\nNom : ");
    readString(buffer, 50);
    strcpy(client->lastName, buffer);
}

void readBirthday(char *buffer, client_t *client) {
    printf("\nDate de naissance : ");
    readString(buffer, 50);
    strcpy(client->birthday, buffer);
}

void readAddress(char *buffer, client_t *client) {
    //address
    address_t address;
    address.city = malloc(20 * sizeof(char));
    address.postalCode = malloc(20 * sizeof(char));
    printf("\nAdresse :");
    printf("\n\tNumero de voie : ");
    readString(buffer, 50);
    address.road.number = atoi(buffer);
    printf("\n\tType de voie (0. Boulevard, 1. Rue, 2. Avenue): ");
    readString(buffer, 50);
    address.road.type = atoi(buffer);
    printf("\n\tVille : ");
    readString(buffer, 50);
    strcpy(address.city, buffer);
    printf("\n\tCode postal :");
    readString(buffer, 50);
    strcpy(address.postalCode, buffer);
    client->address = address;
}

void readStatus(char *buffer, client_t *client) {
    //client status
    printf("\nStatut professionnel (0. Non salarie, 1. CDD, 2. Interim, 3. Liberal, 4. CDI valide, 5. CDI essai) : ");
    readString(buffer, 50);
    client->status = atoi(buffer);
}

void readClientId(char *buffer, client_t *client) {
    int id = 0;
    do {
        printf("\nId :");
        readString(buffer, 4);
        id = atoi(buffer);

        if (clientIdExists(id) == 0)
            printf("Cet id est deja utilise");

    } while (clientIdExists(id) == 0);
    client->id = id;
}

client_t *createClient() {
    client_t *client = malloc(sizeof(client_t));
    client->firstName = malloc(50 * sizeof(char));
    client->lastName = malloc(50 * sizeof(char));

    char buffer[50] = "";
    int isReadingOk;
    printf("*Creation d'un client*\n\n");

    readClientId(buffer, client);
    readFirstName(buffer, client);
    readLastName(buffer, client);
    readBirthday(buffer, client);

    iban_t iban;
    client->iban = createIBAN();

    readAddress(buffer, client);

    //getting current time
    time_t rawTime;
    time(&rawTime);
    struct tm *timeInfo = localtime(&rawTime);
    time_t creditDate = mktime(timeInfo);
    client->creditDate = creditDate;

    //demandStatus
    client->demandStatus = 0;

    readStatus(buffer, client);

    saveClientCsv(*client);

    return client;
}

void deleteClient() {
    char buffer[5] = "";
    printf("\nSuppression d'un client");
    printClients();
    printf("Entrez l'id du client que vous desirez supprimer (-1 pour annuler):");
    readString(buffer, 5);
    int id = atoi(buffer);
    if (clientIdExists(id) != 0) {
        printf("\nDesole, ce client n'existe pas.\n");
        return;
    }
    deleteClientCsv(id);
}

void updateClient() {
    char buffer[50] = "";
    printf("\nModification d'un client");
    printClients();
    printf("Entrez l'id du client que vous desirez modifier (-1 pour annuler):");
    readString(buffer, 3);
    int id = atoi(buffer);
    client_t *client = loadClientCsv(id);
    if (clientIdExists(id) != 0) {
        printf("\nDesole, ce client n'existe pas.\n");
        printf("Echec de la modification");
        return;
    }

    printf("\nQue desirez-vous modifier ?\n");
    printf("\t1. Prenom\n");
    printf("\t2. Nom\n");
    printf("\t3. Date de naissance\n");
    printf("\t4. Adresse\n");
    printf("\t5. Statut\n");
    readString(buffer, 5);
    int choice = atoi(buffer);
    switch (choice) {
        case 1:
            readFirstName(buffer, client);
            break;
        case 2:
            readLastName(buffer, client);
            break;
        case 3:
            readBirthday(buffer, client);
            break;
        case 4:
            readAddress(buffer, client);
            break;
        case 5:
            readStatus(buffer, client);
            break;
        default:
            printf("Choix invalide\n");
            printf("Echec de la modification");
            return;
    }
    updateClientCsv(*client);
    printf("Client modifie avec success");

}

iban_t createIBAN() {

    iban_t iban;
    iban.start = DEFAULT_IBAN_START;
    iban.bankCode = DEFAULT_BANK_CODE;
    iban.agencyCode = DEFAULT_AGENCY_CODE;
    iban.accountNumber = lastAccountNumber + DEFAULT_ACCOUNT_NUMBER_INCREMENT;
    iban.key = lastKey + DEFAULT_KEY_INCREMENT;

    lastAccountNumber = iban.accountNumber;
    lastKey = iban.key;

    if (lastKey == 99)
        lastKey = DEFAULT_KEY;

    return iban;
}

void ibanToString(iban_t iban, char *ibanStr) {
    sprintf(ibanStr, "%s %d %d %ld %d", iban.start,
            iban.bankCode, iban.agencyCode, iban.accountNumber,
            iban.key);
}

void addressToString(address_t address, char *addressStr) {
    sprintf(addressStr, "%d %d %s %s", address.road.number, address.road.type,
            address.postalCode, address.city);
}

void creditDateToString(time_t creditDate, char *creditDateStr) {
    strftime(creditDateStr, 99, "%d/%m/%Y", gmtime(&creditDate));
    //Deleting eventual new line char
    char *p = strchr(creditDateStr, '\n');
    if (p != NULL) {
        *p = '\0';
    }
}

void printIban(iban_t i) {
    printf("IBAN : ");
    printf("%s %d %d %ld %d \n", i.start,
           i.bankCode, i.agencyCode, i.accountNumber,
           i.key);
}

void printAddress(address_t a) {
    char roadType[20] = "";
    switch (a.road.type) {
        case 0:
            strcpy(roadType, "Boulevard");
            break;
        case 1:
            strcpy(roadType, "Route");
            break;

        case 2:
        default:
            break;
    }
    printf("Adresse : ");
    printf("%d %s, %s %s\n", a.road.number, roadType,
           a.city, a.postalCode);

}

void printTime(time_t t) {
    char dateStr[20] = "";
    strftime(dateStr, 19, "%d/%m/%Y", gmtime(&t));
    printf(" %s\n", dateStr);
}

void getDemandStatusStr(enum DemandStatus demandStatus, char *demandStatusStr) {
    switch (demandStatus) {
        case -1:
            strcpy(demandStatusStr, " refusee");
            break;
        case 0:
            strcpy(demandStatusStr, " attente");
            break;
        case 1:
            strcpy(demandStatusStr, " acceptee");
            break;
        default:
            strcpy(demandStatusStr, " Unknown demand state");
            break;
    }
    strcat(demandStatusStr, "\n");
}

void getClientStatusStr(enum ClientStatus clientStatus, char *clientStatusStr) {
    switch (clientStatus) {
        case 0:
            strcpy(clientStatusStr, "Non salarie");
            break;
        case 1:
            strcpy(clientStatusStr, "CDD");
            break;
        case 2:
            strcpy(clientStatusStr, "Interim");
            break;
        case 3:
            strcpy(clientStatusStr, "Liberal");
            break;
        case 4:
            strcpy(clientStatusStr, "CDI valide");
            break;
        case 5:
            strcpy(clientStatusStr, "CDI essai");
            break;
        default:
            strcpy(clientStatusStr, "Unknow client status");
            break;
    }
    strcat(clientStatusStr, "\n");
}

void printClient(client_t c) {
    printf("\nFiche client\n*******\n");
    printf("Nom : %s %s\n", c.firstName, c.lastName);
    printf("Ne le : %s\n", c.birthday);
    printIban(c.iban);
    printAddress(c.address);
    printf("Date du credit : ");
    printTime(c.creditDate);
    char buffer[50] = "";
    getDemandStatusStr(c.demandStatus, buffer);
    printf("Statut de la demande : %s", buffer);
    getClientStatusStr(c.status, buffer);
    printf("Statut : %s", buffer);


}

void printClients() {
    char filename[] = "client.csv";
    char filePath[20] = "../infra/db/";
    strcat(filePath, filename);

    if (fileExists(filePath) != 0) {
        printf("\n*** Aucun client ***\n");
        return;
    } else {
        CSV_BUFFER *csvBuffer = csv_create_buffer();
        csv_set_field_delim(csvBuffer, ';');
        csv_load(csvBuffer, filePath);
        char stringBuffer[50] = "";
        int id = 0;
        char name[50] = "";
        char birthday[11] = "";
        char creditDate[11] = "";

        printf("\n\n%33s\n", "Liste des clients");
        printf("+-------------------");
        printf("--------------------");
        printf("---------------+");
        printf("\n");
        printf("|%3s|%25s|%11s|%12s|\n", "id", "Client name", "Birthday", "Credit date");
        //printf("+%3s+%30s+%11s+%11s+\n", "-", "-", "-", "-");
        printf("+-------------------");
        printf("--------------------");
        printf("---------------+");
        printf("\n");

        for (int i = 1; i < csvBuffer->rows; ++i) {
            csv_get_field(stringBuffer, 49, csvBuffer, i, 0);//id
            id = atoi(stringBuffer);
            csv_get_field(stringBuffer, 49, csvBuffer, i, 1);//first name
            strcpy(name, stringBuffer);
            csv_get_field(stringBuffer, 49, csvBuffer, i, 2);//last name
            strcat(name, " ");
            strcat(name, stringBuffer);
            csv_get_field(stringBuffer, 49, csvBuffer, i, 3);//birthday
            strcpy(birthday, stringBuffer);
            csv_get_field(stringBuffer, 49, csvBuffer, i, 6);//credit date
            strcpy(creditDate, stringBuffer);
            printf("|%3d|%25s|%11s|%12s|\n", id, name, birthday, creditDate);

        }
        printf("+-------------------");
        printf("--------------------");
        printf("---------------+");
        printf("\n\n");
    }
}

int getCreditId(int clientId) {
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    csv_set_field_delim(csvBuffer, ';');
    char filePath[] = "../infra/db/credit.csv";
    if (fileExists(filePath) != 0)
        return -1;
    csv_load(csvBuffer, filePath);
    int retrievedClientId = 0;
    char stringBuffer[4] = "";
    for (int i = 1; i < csvBuffer->rows; ++i) {
        csv_get_field(stringBuffer, 3, csvBuffer, i, 1);
        retrievedClientId = atoi(stringBuffer);
        if (clientId == retrievedClientId) {
            csv_get_field(stringBuffer, 3, csvBuffer, i, 0);
            return atoi(stringBuffer);
        }
    }
    return -1;
}

void saveAmortizationTable(int clientId) {
    client_t *client = loadClientCsv(clientId);
    int creditId = getCreditId(clientId);
    credit_t *credit = loadCreditCsv(creditId);
    char buffer[50] = "";

    char filePath[150] = "../infra/io/amortization_table/";
    char idStr[4] = "";
    char lineWriter[110] = "";
    strcat(filePath, itoa(client->id, idStr, 10));
    strcat(filePath, "_");
    strcpy(buffer, client->firstName);
    stringToLower(buffer);
    strcat(filePath, buffer);
    strcat(filePath, "_");
    strcpy(buffer, client->lastName);
    stringToLower(buffer);
    strcat(filePath, buffer);
    strcat(filePath, "_");
    strcat(filePath, "amortization_table");
    strcat(filePath, ".txt");
    FILE *file = fopen(filePath, "w");


    fprintf(file, "\n%57s\n", "Tableau d'amortissement");
    fprintf(file, "+-------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "---------------+");
    fprintf(file, "\n");

    creditStartDateToString(credit->startDate, buffer);
    fprintf(file, "| Nom : %17s %s | %s : %11s | %s %13s |\n", client->firstName,
            client->lastName, "Date de naissance",
            client->birthday, "Date du pret :", buffer);

    float rate = 0;
    switch (credit->bankRate) {
        case FIX:
            rate = EURIBOR_FIXED_BANK_RATE;
            break;
        case VARIABLE:
            rate = VARIABLE_BANK_RATE;
            break;
        case CAPED:
            rate = CAPED_BANK_RATE_LIMIT;
            break;
    }
    ibanToString(client->iban, buffer);
    fprintf(file, "| IBAN : %20s | %s %15.2f%% | %s %15d %s |\n",
            buffer, "Taux du pret :", rate, "Duree :", credit->duration * 12, "mois");

    double monthlyPaymentInsuranceInclued = (0.03 * credit->totalRebate) / (credit->duration * 12.0);
    fprintf(file, "| Assurance : %14.2f%% | %s %15.2f | %s %12.2f |\n", 0.30,
            "Mensualite HA :", credit->monthlyPayment, "Mensualite AC :", monthlyPaymentInsuranceInclued);

    fprintf(file, "+-------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "---------------+");
    fprintf(file, "\n");
    fprintf(file, "+-------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "---------------+");
    fprintf(file, "\n");

    fprintf(file, "| %6s | %13s | %14s | %14s | %15s | %15s |\n",
            "Mois", "Date", "Interets", "Capital", "Mensualite", "CRD");
    fprintf(file, "+-------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "---------------+");
    fprintf(file, "\n");

    //Line pattern to repeat for each month
    float interest;
    float capital;
    float crd;
    time_t t;
    for (int i = 0; i < credit->duration * 12; ++i) {
        t = addMonthsToDate(credit->startDate, i);
        strftime(buffer, 99, "%d/%m/%Y", gmtime(&t));
        interest = getInterest(*credit, i);
        capital = getCapital(*credit, i);
        crd = getCRD(*credit, i);


        printf("| %6d | %13s | %14.2f | %14.2f | %15.2f | %15.2f |\n",
               i + 1, buffer, interest, capital, credit->monthlyPayment, crd);
    }


    //Footer
    fprintf(file, "+-------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "--------------------");
    fprintf(file, "---------------+");
    fprintf(file, "\n");

    free(file);
    free(client);
    free(credit);

}

void printAmortizationTable() {
    char buffer[50] = "";
    printClients();
    printf("\nEntrez l'id du client dont vous voulez voir le tableau d'ammortissment :");
    readString(buffer, 4);
    int clientId = atoi(buffer);
    //int clientId = 1;
    if (clientIdExists(clientId) != 0) {
        printf("\n\nDesole ce client n'existe pas !\n");
        return;
    } else {
        if (getCreditId(clientId) == -1) {
            printf("\n\nDesole ce client n'a aucun credit !\n");
            return;
        }
    }


    client_t *client = loadClientCsv(clientId);
    int creditId = getCreditId(clientId);
    credit_t *credit = loadCreditCsv(creditId);

    saveAmortizationTable(clientId);


    printf("\n%57s\n", "Tableau d'amortissement");
    printf("+-------------------");
    printf("--------------------");
    printf("--------------------");
    printf("--------------------");
    printf("---------------+");
    printf("\n");

    creditStartDateToString(credit->startDate, buffer);
    printf("| Nom : %17s %s | %s : %11s | %s %13s |\n", client->firstName,
           client->lastName, "Date de naissance",
           client->birthday, "Date du pret :", buffer);

    float rate = 0;
    switch (credit->bankRate) {
        case FIX:
            rate = EURIBOR_FIXED_BANK_RATE;
            break;
        case VARIABLE:
            rate = VARIABLE_BANK_RATE;
            break;
        case CAPED:
            rate = CAPED_BANK_RATE_LIMIT;
            break;
    }
    ibanToString(client->iban, buffer);
    printf("| IBAN : %20s | %s %15.2f%% | %s %15d %s |\n",
           buffer, "Taux du pret :", rate, "Duree :", credit->duration * 12, "mois");

    double monthlyPaymentInsuranceInclued = (0.03 * credit->totalRebate) / (credit->duration * 12.0);
    printf("| Assurance : %14.2f%% | %s %15.2f | %s %12.2f |\n", 0.30,
           "Mensualite HA :", credit->monthlyPayment, "Mensualite AC :", monthlyPaymentInsuranceInclued);

    printf("+-------------------");
    printf("--------------------");
    printf("--------------------");
    printf("--------------------");
    printf("---------------+");
    printf("\n");
    printf("+-------------------");
    printf("--------------------");
    printf("--------------------");
    printf("--------------------");
    printf("---------------+");
    printf("\n");

    printf("| %6s | %13s | %14s | %14s | %15s | %15s |\n",
           "Mois", "Date", "Interets", "Capital", "Mensualite", "CRD");
    printf("+-------------------");
    printf("--------------------");
    printf("--------------------");
    printf("--------------------");
    printf("---------------+");
    printf("\n");

    //Line pattern to repeat for each month
    float interest;
    float capital;
    float crd;
    time_t t;
    for (int i = 0; i < credit->duration * 12; ++i) {
        t = addMonthsToDate(credit->startDate, i);
        strftime(buffer, 99, "%d/%m/%Y", gmtime(&t));
        interest = getInterest(*credit, i);
        capital = getCapital(*credit, i);
        crd = getCRD(*credit, i);


        printf("| %6d | %13s | %14.2f | %14.2f | %15.2f | %15.2f |\n",
               i + 1, buffer, interest, capital, credit->monthlyPayment, crd);
    }


    //Footer
    printf("+-------------------");
    printf("--------------------");
    printf("--------------------");
    printf("--------------------");
    printf("---------------+");
    printf("\n");


}

void printRemainingCapital() {
    char buffer[50] = "";
    printClients();
    printf("\nEntrez l'id du client dont vous voulez voir le Capital Restant Du (CRD):");
    readString(buffer, 4);
    int clientId = atoi(buffer);
    if (clientIdExists(clientId) != 0) {
        printf("\n\nDesole ce client n'existe pas !\n");
        return;
    } else {
        if (getCreditId(clientId) == -1) {
            printf("\n\nDesole ce client n'a aucun credit !\n");
            return;
        }
    }

    client_t *client = loadClientCsv(clientId);
    int creditId = getCreditId(clientId);
    credit_t *credit = loadCreditCsv(creditId);

    creditStartDateToString(credit->startDate, buffer);
    printf("| Nom : %17s %s | %s : %11s | %s %13s |\n", client->firstName,
           client->lastName, "Date de naissance",
           client->birthday, "Date de début du pret :", buffer);


    char crdDate[50];
    printf("\nEntrez la date pour  laquelle vous voulez voir le Capital Restant Du (CRD)  au format dd/MM/YYYY:");
    readString(buffer, 50);
    strcpy(crdDate, buffer);
    time_t targetDate = toDate(crdDate);
    int remainingMonths = getMonthDiff(targetDate, credit->startDate);

    if (remainingMonths < 0) {
        printf("\nLa date pour  laquelle vous voulez voir le Capital Restant Du (CRD) est antérieure au  début du crédit:");
        return;
    }
    if (remainingMonths > credit->duration * 12) {
        printf("\nLa date pour  laquelle vous voulez voir le Capital Restant Du (CRD) est postérieure à la fin du crédit:");
        return;
    }

    float crd = getCRD(*credit, remainingMonths);
    printf("  Capital Restant Du:  %15.2f |\n", crd);
    printf("  Mensualité restant à payer payer:  %d |\n", remainingMonths);

}


