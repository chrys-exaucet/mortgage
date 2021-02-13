#include <stdio.h>
#include <string.h>
#include "../../infra/io/crud/client_crud.h"
#include "../../cli/menu.h"
#include "../../utils/stringUtils.h"

void testCrud()
{
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

    //client_t *cli = loadClientCsv(5);

    //printf("first_name %s", cli->firstName);
}



int main() {

    //loadClientCsv(2);
    while (1)
        printMenu();

    //client_t *cli = createClient();
    //cli->id = 4;
    //saveClientCsv(*cli);

    //client_t *cli = loadClientCsv(4);

    //printClient(*cli);

    //deleteClient();
    //while(1)
        //updateClient();

    return 0;
}

