// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Player.h"
#include <stdlib.h>
using namespace std;

#ifndef RAIDERS_H
#define RAIDERS_H

class Raiders
{
public:
Raiders();


double getRaiderProbability();
void setRaiderProbability(double);


private:
double raiderProbability;

};

#endif