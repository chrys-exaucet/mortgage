//
// Created by Roy on 12/02/2021.
//

#ifndef MORTGAGE_CREDIT_CRUD_H
#define MORTGAGE_CREDIT_CRUD_H

#include "../../../core/credit/credit.h"

int creditIdExists(int creditId);

int saveCreditCsv(credit_t credit);

int deleteCreditCsv(int creditId);

int updateCreditCsv(credit_t credit);

credit_t *loadCreditCsv(int creditId);

#endif //MORTGAGE_CREDIT_CRUD_H
