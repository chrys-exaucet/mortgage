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
        csv_set_field(csvBuffer, lineNumber, 1, stringBuffer);//client id
        creditStartDateToString(credit.startDate, stringBuffer);
        csv_set_field(csvBuffer, lineNumber, 2, stringBuffer);//credit start date
        csv_set_field(csvBuffer, lineNumber, 3, credit.incomeSources);//income source
        csv_set_field(csvBuffer, lineNumber, 4, credit.healthState);//health state
        itoa(credit.annualFiscalIncome, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 5, stringBuffer);//annual fiscal income
        itoa(credit.annualIncome, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 6, stringBuffer);//annual income
        sprintf(stringBuffer, "%.2f", credit.insuranceCoast);
        csv_set_field(csvBuffer, lineNumber, 7, stringBuffer);//insurance coast
        itoa(credit.availableSaving, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 8, stringBuffer);//available saving
        itoa(credit.salary, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 9, stringBuffer);//salary
        goodToString(credit.good, stringBuffer);
        csv_set_field(csvBuffer, lineNumber, 10, stringBuffer);//good
        itoa(credit.fiscalResidence, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 11, stringBuffer);//fiscal residence
        itoa(credit.bankRate, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 12, stringBuffer);//bank rate
        itoa(credit.duration, stringBuffer, 10);
        csv_set_field(csvBuffer, lineNumber, 13, stringBuffer);//duration

    }
}

int saveCreditCsv(credit_t credit)
{
    if(&credit == NULL)
        return -1;
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    char filename [] = "credit.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)//file doesn't exist
    {
        FILE *file = fopen(filePath, "w");
        fclose(file);
        free(file);
        //csv_set_field_delim(csvBuffer, ';');
        csv_set_field(csvBuffer, 0, 0, "id");
        csv_set_field(csvBuffer, 0, 1, "client_id");
        csv_set_field(csvBuffer, 0, 2, "credit_start_date");
        csv_set_field(csvBuffer, 0, 3, "income_source");
        csv_set_field(csvBuffer, 0, 4, "health_state");
        csv_set_field(csvBuffer, 0, 5, "annual_fiscal_income");
        csv_set_field(csvBuffer, 0, 6, "annual_income");
        csv_set_field(csvBuffer, 0, 7, "insurance_coast");
        csv_set_field(csvBuffer, 0, 8, "available_saving");
        csv_set_field(csvBuffer, 0, 9, "salary");
        csv_set_field(csvBuffer, 0, 10, "good");
        csv_set_field(csvBuffer, 0, 11, "fiscal_residence");
        csv_set_field(csvBuffer, 0, 12, "bank_rate");
        csv_set_field(csvBuffer, 0, 13, "duration");
    }
    else
    {
        csv_load(csvBuffer, filePath);
    }

    int nextLineIndex = csvBuffer->rows + 0;
    writeCreditInfoToLineAt(nextLineIndex, credit, csvBuffer);

    //print_buffer(csvBuffer);
    csv_save(filePath, csvBuffer);
    //csv_destroy_buffer();
    return 0;
}

int deleteCreditCsv(int creditId)
{
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    char filename [] = "credit.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)
        return -1;
    else
    {
        if(creditIdExists(creditId) != 0)
            return -1;
        else
        {
            csv_load(csvBuffer, filePath);
            csv_remove_row(csvBuffer, getLineIndexFromCreditId(creditId));
            csv_save(filePath, csvBuffer);
        }
    }
    return 0;
}

int updateCreditCsv(credit_t credit)
{
    CSV_BUFFER *csvBuffer = csv_create_buffer();
    char filename [] = "credit.csv";
    char filePath [20] = "../infra/db/";
    strcat(filePath, filename);

    if(fileExists(filePath) != 0)
        return -1;
    else
    {
        if(creditIdExists(credit.id) != 0)
            return -1;
        else
        {
            int lineIndex = getLineIndexFromCreditId(credit.id);
            csv_load(csvBuffer, filePath);
            csv_clear_row(csvBuffer, lineIndex);
            writeCreditInfoToLineAt(lineIndex, credit, csvBuffer);
            //print_buffer(csvBuffer);
            csv_save(filePath, csvBuffer);
        }
    }
    return 0;
}

int loadCreditCsv(credit_t *credit)
{

}