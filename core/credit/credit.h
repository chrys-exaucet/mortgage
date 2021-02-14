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
    unsigned long otherIncomeSources;
    char *healthState;
    unsigned long annualFiscalIncome;
    unsigned long annualIncome;
    float insuranceCoast;
    float taeg;
    float tmi;
    float monthlyPayment;
    float interest;
    unsigned int availableSaving;
    unsigned long monthlySalary;
    unsigned long otherRebates;
    unsigned long monthlyPension;
    unsigned long fixedChargesAmount;
    unsigned long cost;
    unsigned long totalRebate;
    unsigned int dossierFee;
    unsigned long crd;
    struct Good good;
    enum FiscalResidence fiscalResidence;
    enum BankRate bankRate;
    enum CreditDuration duration;

} credit_t;


void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr);

void goodToString(good_t good, char *goodStr);

credit_t *createCredit();

// Amortization table related

// tax
time_t getDateIncrementedByMonths(time_t date, int monthsNumber);

float getFixedCreditTax();

float getCapedCreditTax(credit_t credit);

float getVariableCreditTax(credit_t credit);

float getCurrentCreditTax(credit_t credit);

float getInsurenceTax(credit_t credit);


// crd related
float getTAEG(credit_t credit);

float getTMI(credit_t credit);

float getCreditCost(credit_t credit);

float getInterest(credit_t credit, int month);

float getTotalRebate(credit_t credit);

float getCapital(credit_t credit, int month);

float getCRD(credit_t credit, int month);


#endif //MORTGAGE_CREDIT_H