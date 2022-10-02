// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
public:
Date();
Date(string,int,int,int);

string getMonth();
void setMonth(string);

int getMonthNumber();
void setMonthNumber(int);

void switchOverMonth();

int getDay();
void setDay(int);

string getDayOfWeek();
void setDayOfWeek();

int getYear();
void setYear(int);

void chooseRest(int);

void chooseContinue();

void chooseHunting();

private:;
string month;
int monthNumber;
int day;
string dayOfWeek;
int year;

};

#endif