#include "e_time.h"

const uint32_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint32_t countLeapYears(Date d);

uint32_t e_time(Date dt1, Date dt2)
{

		uint32_t i;
		uint32_t n1, n2;

    n1 = dt1.year*365 + dt1.day;

    // Add days for months in given date
    for(i=0; i<dt1.month - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);

    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'

    n2 = dt2.year*365 + dt2.day;
    for(i=0; i<dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    // return difference between two counts
    return (n1 - n2);

}

uint32_t countLeapYears(Date d)
{
    uint32_t years = d.year;

    // Check if the current year needs to be considered
    // for the count of leap years or not
    if (d.month <= 2)
        years--;

    // An year is a leap year if it is a multiple of 4,
    // multiple of 400 and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
}
