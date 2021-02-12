#include <stdio.h>
#include <string.h>
#include "../../infra/io/crud/client_crud.h"
#include "../../cli/menu.h"


int main() {
    printf("Welcome to the so called mortgage  app!\n");

    printMenu();


    //deleteClientCsv(1);
    time_t  currentTime;
    currentTime = (time_t)localtime(&currentTime);
    client_t client = {
            1,
            "Chrys",
            "NGOMA",
            "xx/04/1999",
            {NULL},
            {NULL},
            currentTime,
            6,
            7


    };
    //saveClientCsv(client);

    client_t *cli = loadClientCsv(5);

    printf("first_name %s", cli->firstName);

    return 0;
}
