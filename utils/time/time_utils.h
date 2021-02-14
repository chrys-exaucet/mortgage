//
// Created by Utilisateur on 2/14/2021.
//

#ifndef MORTGAGE_TIME_UTILS_H
#define MORTGAGE_TIME_UTILS_H

#include <time.h>


time_t addMonthsToDate(const time_t date, int months);

int getYearDiff(time_t date1, time_t date2);

int getMonthDiff(time_t date1, time_t date2);

time_t toDate(char *str);

#endif //MORTGAGE_TIME_UTILS_H
