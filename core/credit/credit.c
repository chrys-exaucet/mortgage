//
// Created by @chrys on 2/11/2021.
//

#include <stdio.h>
#include <string.h>
#include "credit.h"

void creditStartDateToString(time_t creditDate, char *creditDateStr)
{
    sprintf(creditDateStr, "%s", ctime(&creditDate));
    //Deleting eventual new line char
    char *p = strchr(creditDateStr, '\n');
    if(p !=NULL)
    {
        *p = '\0';
        //*(p + 1) = '\0';
    }
}