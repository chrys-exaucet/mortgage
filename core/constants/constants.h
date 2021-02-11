//
// Created by @chrys on 2/11/2021.
//

#ifndef MORTGAGE_CONSTANTS_H
#define MORTGAGE_CONSTANTS_H

// IBAN related
static const char DEFAULT_IBAN_START[4] = "FR21";
static const unsigned int DEFAULT_BANK_CODE = 30001;
static const unsigned int DEFAULT_AGENCY_CODE = 00021;
static const unsigned long DEFAULT_ACCOUNT_NUMBER = 0000000001;
static const int DEFAULT_ACCOUNT_NUMBER_INCREMENT = 2;
static const int DEFAULT_KEY = 10;
static const int DEFAULT_KEY_INCREMENT = 2;


// Bank related
static const float FIXED_BANK_RATE = 0.0095;
static const float CAPED_BANK_RATE_LIMIT = 0.10;
static const unsigned long DEFAULT_NOTARY_FEE = 15000;


// health care percentage
static const double GOOD_HEALTH_CARE_TAX = 0.0090;
static const double BAD_HEALTH_CARE_TAX = 0.03;

#endif //MORTGAGE_CONSTANTS_H
