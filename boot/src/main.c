#include <stdio.h>
#include <string.h>
#include "../../infra/io/crud/client_crud.h"
#include "../../cli/menu.h"
#include "../../utils/stringUtils.h"
#include "../../core/credit/credit.h"
#include "../../infra/io/crud/credit_crud.h"


int main() {

    //loadClientCsv(2);
    //while (1)
        //printMenu();

        credit_t *c = loadCreditCsv(1);
    credit_t *credit = createCredit();

    return 0;
}

