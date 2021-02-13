#include "../../cli/menu/menu.h"
#include "../../core/credit/credit.h"
#include "../../infra/io/crud/credit_crud.h"


int main() {
    // run();
    credit_t *c = loadCreditCsv(1);
    credit_t *credit = createCredit();
    return 0;

}

