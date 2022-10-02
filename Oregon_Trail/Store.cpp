// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Store.h"
using namespace std;

Store::Store() // default constructor
    {
        oxenPrice = 0.0;
        foodPrice = 0.0;
        bulletPrice = 0.0;
        wagonPartPrice = 0.0;
        medicalAidPrice = 0.0;
        priceMultiplier = 0.0;
    }

Store::Store(double oxen, double food, double bullet, double wagon, double medical, double price) // parameterized constructor
    {
        priceMultiplier = price;
        oxenPrice = priceMultiplier * oxen;
        foodPrice = priceMultiplier * food;
        bulletPrice = priceMultiplier * bullet;
        wagonPartPrice  = priceMultiplier * wagon;
        medicalAidPrice = priceMultiplier * medical;
    }

double Store::getOxenPrice() //  oxen price getter
    {
        return oxenPrice;
    }

void Store::setOxenPrice(double newOxenPrice) // oxen price setter
    {
        oxenPrice = priceMultiplier * newOxenPrice;
    }

double Store::getFoodPrice() // food price setter
    {
        return foodPrice;
    }

void Store::setFoodPrice(double newFoodPrice) // food price setter
    {
        foodPrice = priceMultiplier * newFoodPrice;
    }

double Store::getBulletPrice() // bullet price getter
    {
        return bulletPrice;
    }
    
void Store::setBulletPrice(double newBulletPrice) // bullet price setter
    {
        bulletPrice = priceMultiplier * newBulletPrice;
    }

double Store::getWagonPrice() // wagon price getter
    {
        return wagonPartPrice;
    }

void Store::setWagonPrice(double newWagonPrice) // wagon price setter
    {
        wagonPartPrice = priceMultiplier * newWagonPrice;
    }

double Store::getMedicalPrice() // medical getter
    {
        return medicalAidPrice;
    }

void Store::setMedicalPrice(double newMedicalPrice) // medical setter
    {
        medicalAidPrice = priceMultiplier * newMedicalPrice;
    }

double Store::getMultiplier() // multiplier getter
    {
        return priceMultiplier;
    }

void Store::setMultiplier(double newMultiplier) // multiplier setter
    {
        priceMultiplier = newMultiplier;
    }
