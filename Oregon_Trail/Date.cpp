// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Date.h"
#include <stdlib.h>
using namespace std;

Date::Date() // default constructor
    {
        month = "MARCH";
        monthNumber = 03;
        day = 28;
        year = 1847;
        dayOfWeek = "SUNDAY";
    }

Date::Date(string newMonth, int newMonthNumber, int newDay, int newYear) // parameterized constructor
    {
        month = newMonth;
        monthNumber = newMonthNumber;
        day = newDay;
        year = newYear;
        dayOfWeek = "";
    }

string Date::getMonth() // month getter
    {
        return month;
    }

void Date::setMonth(string newMonth) //month setter
    {
        month = newMonth;
    }
    
int Date::getMonthNumber() //int month getter
    {
        return monthNumber;
    }

void Date::setMonthNumber(int newMonthNumber) // int month setter
    {
        monthNumber = newMonthNumber;
    }

/*
 * This function ensures that the correct month corrolates with the current day
 * parameters - none
 * return - none
*/

void Date::switchOverMonth()
    {
        if (monthNumber == 3 && day > 31)
            {
                day = day - 31;
                monthNumber = 4;
                month = "APRIL";
            }
        
        if (monthNumber == 4 && day > 30)
            {
                day = day - 30;
                monthNumber = 5;
                month = "MAY";
            }

        if (monthNumber == 5 && day > 31)
            {
                day = day - 31;
                monthNumber = 6;
                month = "JUNE";
            }
        
        if  (monthNumber == 6 && day > 30)
            {
                day = day - 30;
                monthNumber = 7;
                month = "JULY";
            }
        
        if (monthNumber == 7 && day > 31)
            {
                day = day - 31;
                monthNumber = 8;
                month = "AUGUST";
            }
        
        if (monthNumber == 8 && day > 31)
            {
                day = day - 31;
                monthNumber = 9;
                month = "SEPTEMBER";
            }
        
        if (monthNumber == 9 && day > 30)
            {
                day = day - 30;
                monthNumber = 10;
                month = "OCTOBER";
            }
        
        if (monthNumber == 10 && day > 31)
            {
                day = day- 31;
                monthNumber = 11;
                month = "NOVEMBER";
            }
    }

int Date::getDay() // day getter
    {
        return day;
    }

void Date::setDay(int newDay) // day setter
    {
        day = newDay;
    }

string Date::getDayOfWeek() // day of the week getter
    {
        return dayOfWeek;
    }

void Date::setDayOfWeek() // day of the week setter
    {
        if (monthNumber == 3)
            {
                if (day % 7 == 1)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 4)
            {
                if (day % 7 == 5)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 5)
            {
                if (day % 7 == 3)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 6)
            {
                if (day % 7 == 0)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 7)
            {
                if (day % 7 == 5)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 8)
            {
                if (day % 7 == 2)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 9)
            {
                if (day % 7 == 6)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 10)
            {
                if (day % 7 == 4)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 1)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
        if (monthNumber == 11)
            {
                if (day % 7 == 1)
                    {
                        dayOfWeek = "MONDAY";
                    }
                if (day % 7 == 2)
                    {
                        dayOfWeek = "TUESDAY";
                    }
                if (day % 7 == 3)
                    {
                        dayOfWeek = "WEDNESDAY";
                    }
                if (day % 7 == 4)
                    {
                        dayOfWeek = "THURSDAY";
                    }
                if (day % 7 == 5)
                    {
                        dayOfWeek = "FRIDAY";
                    }
                if (day % 7 == 6)
                    {
                        dayOfWeek = "SATURDAY";
                    }
                if (day % 7 == 0)
                    {
                        dayOfWeek = "SUNDAY";
                    }
            }
    }

int Date::getYear() // year getter
    {
        return year;
    }

void Date::setYear(int newYear) // year setter
    {
        year = newYear;
    }

/*
 * This function moves the day based on random number put into function
 * parameters - int number of days to move the date forward
 * return - none
*/

void Date::chooseRest(int random) 
    {
        day = day + random;
    }

/*
 * This function moves the day forward two weeks
 * parameters - none
 * return - none
*/

void Date::chooseContinue()
    {
        day = day + 14;
    }

/*
 * This function moes the day forward one
 * parameters - none
 * returns -  none
*/

void Date::chooseHunting()
    {
        day = day + 1;
    }