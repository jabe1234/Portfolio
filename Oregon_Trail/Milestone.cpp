// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Milestone.h"
using namespace std;

Milestone::Milestone() // default constructor
    {
        milestoneLength = 0;
        milestoneName = "";
    }

Milestone::Milestone(string name, int length) // parameterized consructor
    {
        milestoneName = name;
        milestoneLength = length;
    }

string Milestone::getMilestoneName() // milestone name getter
    {
        return milestoneName;
    }

void Milestone::setMilestoneName(string name) // milestone name setter
    {
        milestoneName = name;
    }

int Milestone::getMilestoneLength() // milestone length getter
    {
        return milestoneLength;
    }

void Milestone::setMilestoneLength(int length) // milestone length setter
    {
        milestoneLength = length;
    }