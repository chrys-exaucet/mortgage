#include <stdio.h>
#include <string.h>
#include "../../infra/io/crud/client_crud.h"


int main() {
    printf("Welcome to the so called mortgage  app!\n");
    //deleteClientCsv(1);

    client_t client = {
            1,
            "Chrys",
            "NGOMA",
            "xx/04/1999",
            {NULL},
            {NULL},
            5,
            6,
            7


    };
    saveClientCsv(client);

    client.demandStatus = 14;
    client.status = 15;
    updateClientCsv(client);
    return 0;
}
