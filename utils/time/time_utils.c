//
// Created by Utilisateur on 2/14/2021.
//

#include "time_utils.h"

#include <assert.h>

int IsLeapYear(int year) {
    if (year % 4 != 0) return 1;
    if (year % 400 == 0) return 0;
    if (year % 100 == 0) return 1;
    return 0;
}

int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int GetDaysInMonth(int year, int month) {
    assert(month >= 0);
    assert(month < 12);

    int days = daysInMonths[month];

    if (month == 1 && IsLeapYear(year) == 0) // February of a leap year
        days += 1;

    return days;
}

struct tm addMonthInStruct(struct tm d, int months) {
    int isLastDayInMonth = d.tm_mday == GetDaysInMonth(d.tm_year, d.tm_mon);

    int year = d.tm_year + months / 12;
    int month = d.tm_mon + months % 12;

    if (month > 11) {
        year += 1;
        month -= 12;
    }
    int day;
    if (isLastDayInMonth)
        day = GetDaysInMonth(year, month); // Last day of month maps to last day of result month
    else
        day = d.tm_mday < GetDaysInMonth(year, month) ? d.tm_mday : GetDaysInMonth(year, month);

    struct tm result;

    result.tm_year = year;
    result.tm_mon = month;
    result.tm_mday = day;

    result.tm_hour = d.tm_hour;
    result.tm_min = d.tm_min;
    result.tm_sec = d.tm_sec;

    return result;
}

time_t addMonthsToDate(const time_t date, int months) {
    struct tm d;
    localtime_s(&d, &date);
    struct tm result = addMonthInStruct(d, months);
    return mktime(&result);
}


int getYearDiff(time_t date1, time_t date2) {

    struct tm d1;
    struct tm d2;
    localtime_s(&d1, &date1);
    localtime_s(&d2, &date2);
    return d1.tm_year - d2.tm_year;
}


