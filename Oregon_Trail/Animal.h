// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef ANIMAL_H
#define ANIMAL_H

class Animal
{
public:
Animal();
Animal(string,int,int,double);

string getAnimal();
void setAnimal(string);

int getMeat();
void setMeat(int);

int getBullet();
void setBullet(int);

double getChance();
void setChance(double);

private:
string animal;
int meat;
int bulletRequired;
double chance;

};

#endif