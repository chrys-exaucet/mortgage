#include <stdio.h>
#include "../../cli/menu/menu.h"
#include "../../core/credit/credit.h"
#include "../../infra/io/crud/credit_crud.h"
#include "../../utils/strings/stringUtils.h"


int main() {

    //run();

    credit_t *c = loadCreditCsv(1);


    //createClient();
    printAmortizationTable(1);
    saveAmortizationTable(1);

    //credit_t *credit = createCredit();
    return 0;

}

