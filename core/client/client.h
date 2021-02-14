//
// Created by @chrys on 2/11/2021.
//

#ifndef MORTGAGE_CLIENT_H
#define MORTGAGE_CLIENT_H

#include <time.h>
#include "../address/address.h"
#include "../constants/constants.h"

enum DemandStatus {
    ACCEPTED = 1,
    PENDING = 0,
    DENIED = -1
};

enum ClientStatus {
    PRO_UNEMPLOYED,
    PRO_CDD,
    PRO_INTERIM,
    PRO_LIBERAL,
    CDI_VALIDATED,
    CDI_ESSAY,
};

typedef struct IBAN {
    char *start;
    unsigned int bankCode;
    unsigned int agencyCode;
    unsigned long accountNumber;
    unsigned int key;
} iban_t;


typedef struct Client {
    int id;
    char *firstName;
    char *lastName;
    char birthday[11];
    iban_t iban;
    address_t address;
    time_t creditDate;
    enum DemandStatus demandStatus;
    enum ClientStatus status;
} client_t;


client_t *createClient();

iban_t createIBAN();

void deleteClient();

void updateClient();

void ibanToString(iban_t iban, char *ibanStr);

void addressToString(address_t address, char *addressStr);

void creditDateToString(time_t creditDate, char *creditDateStr);

void getClientStatusStr(enum ClientStatus clientStatus, char *clientStatusStr);

void getDemandStatusStr(int demandStatus, char *demandStatusStr);

void printClient(client_t c);

void printClients();


void printAmortizationTable();
void saveAmortizationTable(int clientId);

#endif //MORTGAGE_CLIENT_H
