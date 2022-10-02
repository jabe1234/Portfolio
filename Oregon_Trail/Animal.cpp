// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Animal.h"
using namespace std;

Animal::Animal() // default constructor
    {
        animal = "";
        meat = 0;
        bulletRequired = 0;
        chance = 0.0;
    }

Animal::Animal(string newAnimal, int newMeat, int newBulletsRequired, double newChance) // parameterized constructor
    {
        animal = newAnimal;
        meat = newMeat;
        bulletRequired = newBulletsRequired;
        chance = newChance;
    }

string Animal::getAnimal() // animal getter
    {
        return animal;
    }

void Animal::setAnimal(string newAnimal) // animal  setter
    {
        animal = newAnimal;
    }
    
int Animal::getMeat() // meat getter
    {
        return meat;
    }

void Animal::setMeat(int newMeat) // meat setter
    {
        meat = newMeat;
    }

int Animal::getBullet() // bullet getter
    {
        return bulletRequired;
    }

void Animal::setBullet(int newBullet) // bullet setter
    {
        bulletRequired = newBullet;
    }
    
double Animal::getChance() // chance getter
    {
        return chance;
    }

void Animal::setChance(double newChance) // chance setter
    {
        chance = newChance;
    }