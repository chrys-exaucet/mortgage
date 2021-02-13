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
    CDI,
    CDI_VALIDATED,
    CDI_ESSAY,
};

typedef struct IBAN {
    char start[4];
    unsigned int bankCode;
    unsigned int agencyCode;
    unsigned long accountNumber;
    unsigned int key;
    unsigned long lastAccountNumber;
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

iban_t createIBAN(int clientId);

client_t *createClient();

void deleteClient();

void updateClient();

void getTAC();

int getCRD(time_t date, int dueMonths);

void ibanToString(iban_t iban, char *ibanStr);

void addressToString(address_t address, char *addressStr);

void creditDateToString(time_t creditDate, char *creditDateStr);

void demandStatusToString(int demandStatus, char *demandStatusStr);

void printClient(client_t c);

void printClients();


#endif //MORTGAGE_CLIENT_H
