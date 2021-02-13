//
// Created by @chrys on 2/11/2021.
//

#ifndef MORTGAGE_CREDIT_H
#define MORTGAGE_CREDIT_H

#include "../good/good.h"
#include "../client/client.h"

enum FiscalResidence {
    FRANCE,
    EU,
    NOT_EU
};

enum BankRate {
    FIX,
    VARIABLE,
    CAPED
};

enum CreditDuration {
    FIFTEEN = 15,
    TWENTY = 20,
    TWENTY_FIVE = 25
};

typedef struct Credit {
    int id;
    int clientId;
    time_t startDate;
    char *incomeSources;
    char *healthState;
    unsigned long annualFiscalIncome;
    unsigned long annualIncome;
    float insuranceCoast;
    unsigned int availableSaving;
    // Monthly salary in Euros
    unsigned long salary;
    struct Good good;
    enum FiscalResidence fiscalResidence;
    enum BankRate bankRate;
    enum CreditDuration duration;

} credit_t;

credit_t getClientCredit(int clientId, int creditId);

double getTimeToLive();

unsigned long getAnnualIncomes(int salary);

int isEligible(int clientId);

int isStatusValid(enum ClientStatus clientStatus, char args[]);

int isSalaryValid(unsigned salary);

int isFiscalRevenueValid(unsigned long revenue);


void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr);

void goodToString(good_t good, char *goodStr);

credit_t *createCredit();

#endif //MORTGAGE_CREDIT_H