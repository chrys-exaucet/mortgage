#include "../../cli/menu/menu.h"
#include "../../core/client/client.h"
#include "../../core/credit/credit.h"
#include "../../infra/io/crud/credit_crud.h"

int main() {
    while (1)
        run();

    credit_t *c = loadCreditCsv(1);
    printAmortizationTable();
    return 0;

}

