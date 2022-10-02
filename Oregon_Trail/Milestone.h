// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef MILESTONE_H
#define MILESTONE_H

class Milestone
{
public:
Milestone();
Milestone(string,int);

string getMilestoneName();
void setMilestoneName(string);

int getMilestoneLength();
void setMilestoneLength(int);

private:
string milestoneName;
int milestoneLength;

};

#endif