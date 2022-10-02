// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Raiders.h"
using namespace std;

Raiders::Raiders() // default constructor
    {
        raiderProbability = 0.0;
    }

double Raiders::getRaiderProbability() // probability getter
    {
        return raiderProbability;
    }

void Raiders::setRaiderProbability(double newRaider) // probability setter
    {
        raiderProbability = newRaider;
    }