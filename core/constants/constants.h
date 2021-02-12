//
// Created by @chrys on 2/11/2021.
//

#ifndef MORTGAGE_CONSTANTS_H
#define MORTGAGE_CONSTANTS_H

// IBAN related

#define DEFAULT_IBAN_START "FR21"
#define DEFAULT_BANK_CODE 30001
#define DEFAULT_AGENCY_CODE 00021
#define DEFAULT_ACCOUNT_NUMBER 0000000001
#define DEFAULT_ACCOUNT_NUMBER_INCREMENT 2
#define DEFAULT_KEY 10
#define DEFAULT_KEY_INCREMENT 2


// Bank related
static const float FIXED_BANK_RATE = 0.0095;
static const float CAPED_BANK_RATE_LIMIT = 0.10;
static const unsigned long DEFAULT_NOTARY_FEE = 15000;


// health care percentage
static const double GOOD_HEALTH_CARE_TAX = 0.0090;
static const double BAD_HEALTH_CARE_TAX = 0.03;

#endif //MORTGAGE_CONSTANTS_H
