//
// Created by @chrys on 2/11/2021.
//
#include "client.h"
#include <string.h>

// #include "csv-parser"

void createClient(client_t *client) {

};

void deleteClient(int clientId) {

};

void updateClient(client_t *client) {

};

iban_t createIBAN(int clientId) {
    iban_t iban = defaultIBAN;
    iban.accountNumber += DEFAULT_ACCOUNT_NUMBER_INCREMENT;
    iban.key += DEFAULT_KEY_INCREMENT;
    return iban;
};

void getTAC() {

};

int getCRD(time_t date, int dueMonths) {

    return dueMonths;
};

