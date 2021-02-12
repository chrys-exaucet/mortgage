//
// Created by Roy on 12/02/2021.
//

#include <stdio.h>
#include <string.h>
#include "credit_crud.h"
#include "../parser.csv/csv.h"
#include "../../../core/credit/credit.h"
#include "../../../utils/file_utils.h"


int creditIdExists(int creditId)
{
    char filename [] = "credit.csv";
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
            if(atoi(id) == creditId)
                return 0;
        }
        return -1;
    }
}

int getLineIndexFromCreditId(int creditId)
{
    char filename [] = "credit.csv";
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
            if(atoi(id) == creditId)
                return i;
        }
        return -1;
    }
}

void writeCreditInfoToLineAt(int lineNumber, credit_t credit, CSV_BUFFER *csvBuffer)
{
    if(&credit == NULL)
        return;
    else
    {
        char stringBuffer[100] = "";
        itoa(credit.id, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 0, stringBuffer);//id
        itoa(credit.clientId, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 0, stringBuffer);//client id

    }
}

