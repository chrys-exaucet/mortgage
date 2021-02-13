//
// Created by Roy on 11/02/2021.
//

#include <string.h>
#include <time.h>
#include "client_crud.h"
#include "../parser.csv/csv.h"
#include "../../../core/client/client.h"
#include "../../../utils/file_utils.h"
#include "../../../utils/stringUtils.h"


int clientIdExists(int clientId)
{
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) !=0)
        return -1;
    else
    {
        CSV_BUFFER *csvBuffer = csv_create_buffer();
        csv_load(csvBuffer, filePath);
        char id[4] = "";
        for (int i = 1; i < csvBuffer->rows; ++i)
        {
            csv_get_field(id, 4, csvBuffer, i, 0);
            if(atoi(id) == clientId)
                return 0;
        }
        return -1;
    }
}

int getLineIndexFromClientId(int clientId)
{
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) !=0)
        return -1;
    else
    {
        CSV_BUFFER *csvBuffer = csv_create_buffer();
        csv_load(csvBuffer, filePath);
        char id[4] = "";
        for (int i = 1; i < csvBuffer->rows; ++i)
        {
            csv_get_field(id, 4, csvBuffer, i, 0);
            if(atoi(id) == clientId)
                return i;
        }
        return -1;
    }
}

void writeClientInfoToLineAt(int lineNumber, client_t  client, CSV_BUFFER *csvBuffer)
{
    if(&client == NULL)
        return;
    else
    {
        char stringBuffer[100] = "";
        itoa(client.id, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 0, stringBuffer);//id
        csv_set_field(csvBuffer, lineNumber, 1, client.firstName);
        csv_set_field(csvBuffer, lineNumber, 2, client.lastName);
        csv_set_field(csvBuffer, lineNumber, 3, client.birthday);
        memset(stringBuffer, 0, strlen(stringBuffer));
        ibanToString(client.iban, stringBuffer);
        csv_set_field(csvBuffer, lineNumber, 4, stringBuffer);//iban
        memset(stringBuffer, 0, strlen(stringBuffer));
        addressToString(client.address, stringBuffer);
        csv_set_field(csvBuffer, lineNumber, 5, stringBuffer);//address
        memset(stringBuffer, 0, strlen(stringBuffer));
        creditDateToString(client.creditDate, stringBuffer);
        csv_set_field(csvBuffer, lineNumber, 6, stringBuffer);//credit date
        memset(stringBuffer, 0, strlen(stringBuffer));
        itoa(client.demandStatus, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 7, stringBuffer);//demand status
        itoa(client.status, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 8, stringBuffer);//client status
    }
}

int saveClientCsv(client_t client)
{
    if(&client == NULL)
        return -1;
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    csv_set_field_delim(csvBuffer, ';');
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)//file doesn't exist
    {
        FILE *file = fopen(filePath, "w");
        fclose(file);
        free(file);
        csv_set_field(csvBuffer, 0, 0, "id");
        csv_set_field(csvBuffer, 0, 1, "first_name");
        csv_set_field(csvBuffer, 0, 2, "last_name");
        csv_set_field(csvBuffer, 0, 3, "birthday_date");
        csv_set_field(csvBuffer, 0, 4, "iban");
        csv_set_field(csvBuffer, 0, 5, "address");
        csv_set_field(csvBuffer, 0, 6, "credit_date");
        csv_set_field(csvBuffer, 0, 7, "demand_status");
        csv_set_field(csvBuffer, 0, 8, "client_status");
    }
    else
    {
        csv_load(csvBuffer, filePath);
    }

    int nextLineIndex = csvBuffer->rows + 0;
    writeClientInfoToLineAt(nextLineIndex, client, csvBuffer);

    //print_buffer(csvBuffer);
    csv_save(filePath, csvBuffer);
    //csv_destroy_buffer();
    return 0;
}

int deleteClientCsv(int clientId)
{
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    csv_set_field_delim(csvBuffer, ';');
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)
        return -1;
    else
    {
        if(clientIdExists(clientId) != 0)
            return -1;
        else
        {
            csv_load(csvBuffer, filePath);
            csv_remove_row(csvBuffer, getLineIndexFromClientId(clientId));
            csv_save(filePath, csvBuffer);
        }
    }
    return 0;
}

int updateClientCsv(client_t client)
{
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    csv_set_field_delim(csvBuffer, ';');
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)
        return -1;
    else
    {
        if(clientIdExists(client.id) != 0)
            return -1;
        else
        {
            int lineIndex = getLineIndexFromClientId(client.id);
            csv_load(csvBuffer, filePath);
            csv_clear_row(csvBuffer, lineIndex);
            writeClientInfoToLineAt(lineIndex, client, csvBuffer);
            //print_buffer(csvBuffer);
            csv_save(filePath, csvBuffer);
        }
    }
    return 0;
}

client_t *loadClientCsv(int clientId)
{
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    csv_set_field_delim(csvBuffer, ';');
    csv_set_field_delim(csvBuffer, ';');
    char filename [] = "client.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)
        return NULL;
    else
    {
        if(clientIdExists(clientId) != 0)
            return NULL;
        else
        {
            int lineIndex = getLineIndexFromClientId(clientId);
            char str[100] = "";
            csv_load(csvBuffer, filePath);
            client_t *client = malloc(sizeof(client_t));
            csv_get_field(str, 99, csvBuffer, lineIndex, 0);//id
            client->id = atoi(str);

            csv_get_field(str, 99, csvBuffer, lineIndex, 1);//first name
            client->firstName = malloc(50 * sizeof(char));
            strcpy(client->firstName, str);

            csv_get_field(str, 99, csvBuffer, lineIndex, 2);//last name
            client->lastName = malloc(50 * sizeof(char));;
            strcpy(client->lastName, str);
            csv_get_field(str, 99, csvBuffer, lineIndex, 3);//birthday
            strcpy(client->birthday, str);
            csv_get_field(str, 99, csvBuffer, lineIndex, 4);//iban
            //printf("iban = %s", str);
            char **ibanTokens = str_split(str, ' ');
            iban_t iban = {
                    {},
                    atoi(*(ibanTokens + 1)),
                    atoi(*(ibanTokens + 2)),
                    atol(*(ibanTokens + 3)),
                    atoi(*(ibanTokens + 4)),
                    0
                    //atol(*(ibanTokens + 5)),
            };
            strcpy((char *)iban.start, *(ibanTokens + 0));
            client->iban = iban;
            //free(ibanTokens);

            csv_get_field(str, 99, csvBuffer, lineIndex, 5);//address
            char **addressTokens = str_split(str, ' ');
            road_t road = {
                    (int)*(addressTokens + 0),
                    (int)*(addressTokens + 1)
            };
            address_t address = {
                    road,
                    *(addressTokens + 2),
                    *(addressTokens + 3)
            };
            client->address = address;

            csv_get_field(str, 99, csvBuffer, lineIndex, 6);//credit date
            char **creditDateTokens = str_split(str, '/');
            struct tm t = {
                    0,
                    0,
                    0,
                    atoi(*(creditDateTokens + 0)),
                    atoi(*(creditDateTokens + 1)) - 1,
                    atoi(*(creditDateTokens + 2)) - 1900,
                    };

            time_t rawTime = mktime(&t);
            client->creditDate = rawTime;

            csv_get_field(str, 99, csvBuffer, lineIndex, 7);//demand status
            client->demandStatus = atoi(str);
            csv_get_field(str, 99, csvBuffer, lineIndex, 8);//status
            client->status = atoi(str);

            return client;
        }
    }
    return NULL;
}