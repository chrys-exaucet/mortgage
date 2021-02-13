//
// Created by @chrys on 2/11/2021.
//
#include "client.h"
#include "../../utils/stringUtils.h"
#include "../../infra/io/parser.csv/csv.h"
#include "../../utils/file_utils.h"
#include "../../infra/io/crud/client_crud.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

// #include "csv-parser"

iban_t defaultIBAN = {
        {DEFAULT_IBAN_START},
        DEFAULT_BANK_CODE,
        DEFAULT_AGENCY_CODE,
        DEFAULT_ACCOUNT_NUMBER,
        DEFAULT_KEY
};

void readFirstName(char *buffer, client_t *client)
{
    printf("\nPrenoms : ");
    readString(buffer, 50);
    strcpy(client->firstName, buffer);
}

void readLastName(char *buffer, client_t *client)
{
    printf("\nNom : ");
    readString(buffer, 50);
    strcpy(client->lastName, buffer);
}

void readBirthday(char *buffer, client_t *client)
{
    printf("\nDate de naissance : ");
    readString(buffer, 50);
    strcpy(client->birthday, buffer);
}

void readAddress(char *buffer, client_t *client)
{
    //address
    address_t address;
    address.city = malloc(20 * sizeof(char));
    address.postalCode = malloc(20 * sizeof(char));
    printf("\nAdresse :");
    printf("\n\tNumero de route : ");
    readString(buffer, 50);
    address.road.number = atoi(buffer);
    printf("\n\tType de route (0. Boulevard, 1. Route, 2. Inconnu): ");
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

void readStatus(char *buffer, client_t *client)
{
    //client status
    printf("\nStatut (0. Non salarie, 1. CDD, 2. Interim, 3. Liberal, 4. CDI, 5. CDI valide, 6. CDI essai) : ");
    readString(buffer, 50);
    client->status = atoi(buffer);
}

void readClientId(char *buffer, client_t *client)
{
    int id = 0;
    do{
        printf("\nId :");
        readString(buffer, 4);
        id = atoi(buffer);

        if(clientIdExists(id) == 0)
            printf("Cet id est deja utilise");

    } while (clientIdExists(id) == 0);
    client->id = id;
}

client_t *createClient() {
    //init client
    client_t *client = malloc(sizeof(client_t));
    client->firstName = malloc(50 * sizeof(char));
    client->lastName = malloc(50 * sizeof(char));

    char buffer[50] = "";
    int isReadingOk = 0;
    printf("*Creation d'un client*\n\n");

    readClientId(buffer, client);
    readFirstName(buffer, client);
    readLastName(buffer, client);
    readBirthday(buffer, client);

    //iban : Need to review createIBAN function (weird behaviour)
    iban_t iban;
    client->iban = createIBAN(4);

    readAddress(buffer, client);

    //creditDate : default attribution for now just for tests purpose
    struct tm t ={0,0,0,13,2-1,2021 - 1900};
    time_t creditDate = mktime(&t);
    printf("\nDate d'obtention du credit : 13/02/2021");
    client->creditDate = creditDate;

    //demandStatus
    client->demandStatus = 1;

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
    if(clientIdExists(id) != 0)
    {
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
    if(clientIdExists(id) != 0)
    {
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
    switch (choice)
    {
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

iban_t createIBAN(int clientId) {
    iban_t iban = defaultIBAN;
    iban.accountNumber += DEFAULT_ACCOUNT_NUMBER_INCREMENT;
    iban.key += DEFAULT_KEY_INCREMENT;
    return iban;
}

void getTAC() {

}

int getCRD(time_t date, int dueMonths) {

    return dueMonths;
}


void ibanToString(iban_t iban, char *ibanStr)
{
    sprintf(ibanStr, "%s %d %d %ld %d %ld", iban.start,
            iban.bankCode, iban.agencyCode, iban.accountNumber,
            iban.key);
}

void addressToString(address_t address, char *addressStr)
{
    //improvement : have a function returning correct strings for enums
    sprintf(addressStr, "%d %d %s %s", address.road.number, address.road.type,
            address.postalCode, address.city);
}

void creditDateToString(time_t creditDate, char *creditDateStr)
{
    strftime(creditDateStr, 99, "%d/%m/%Y", gmtime(&creditDate));
    //Deleting eventual new line char
    char *p = strchr(creditDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
        //*(p + 1) = '\0';
    }
}

void printIban(iban_t i)
{
    printf("IBAN : ");
    printf("%s %d %d %ld %d %ld\n", i.start,
           i.bankCode, i.agencyCode, i.accountNumber,
           i.key, i.lastAccountNumber);
}

void printAddress(address_t a)
{
    char roadType[20] = "";
    switch (a.road.type)
    {
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

void printTime(time_t t)
{
    char dateStr[20] = "";
    strftime(dateStr, 19, "%d/%m/%Y", gmtime(&t));
    printf(" %s\n", dateStr);
}

void getDemandStatusStr(enum DemandStatus demandStatus, char *demandStatusStr)
{
    switch (demandStatus)
    {
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

void getClientStatusStr(enum ClientStatus clientStatus, char *clientStatusStr)
{
    switch (clientStatus)
    {
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
            strcpy(clientStatusStr, "CDI");
            break;
        case 5:
            strcpy(clientStatusStr, "CDI valide");
            break;
        case 6:
            strcpy(clientStatusStr, "CDI essai");
            break;
        default:
            strcpy(clientStatusStr, "Unknow client status");
            break;
    }
    strcat(clientStatusStr, "\n");
}

void printClient(client_t c)
{
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

void printClients()
{
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) !=0)
    {
        printf("\n*** Aucun client ***\n");
        return;
    }
    else
    {
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

        for (int i = 1; i < csvBuffer->rows ; ++i)
        {
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

            /*printf("+-------------------");
            printf("--------------------");
            printf("---------------+");
            printf("\n");*/

        }
        printf("+-------------------");
        printf("--------------------");
        printf("---------------+");
        printf("\n\n");
    }
}

