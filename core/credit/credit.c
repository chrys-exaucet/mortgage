//
// Created by @chrys on 2/11/2021.
//

#include <stdio.h>
#include <string.h>
#include "credit.h"

void creditStartDateToString(time_t creditStartDate, char *creditStartDateStr)
{
    sprintf(creditStartDateStr, "%s", ctime(&creditStartDate));
    //Deleting eventual new line char
    char *p = strchr(creditStartDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
        //*(p + 1) = '\0';
    }
}

void goodToString(good_t good, char *goodStr)
{
    sprintf(goodStr, "%s %s %d", good.type, good.origin, good.value);
}