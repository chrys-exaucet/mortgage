//
// Created by @chrys on 2/11/2021.
//
#include "client.h"
#include <string.h>
#include <stdio.h>

// #include "csv-parser"

iban_t defaultIBAN = {
        {DEFAULT_IBAN_START},
        DEFAULT_BANK_CODE,
        DEFAULT_AGENCY_CODE,
        DEFAULT_ACCOUNT_NUMBER,
        DEFAULT_KEY
};

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

//Roy
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
    sprintf(creditDateStr, "%s", ctime(&creditDate));
    //Deleting eventual new line char
    char *p = strchr(creditDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
        //*(p + 1) = '\0';
    }
}

