// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef STORE_H
#define STORE_H

class Store
{
public:
Store();
Store(double,double,double,double,double,double);

double getOxenPrice();
void setOxenPrice(double);

double getFoodPrice();
void setFoodPrice(double);

double getBulletPrice();
void setBulletPrice(double);

double getWagonPrice();
void setWagonPrice(double);

double getMedicalPrice();
void setMedicalPrice(double);

double getMultiplier();
void setMultiplier(double);

private:
double oxenPrice;
double foodPrice;
double bulletPrice;
double wagonPartPrice;
double medicalAidPrice;
double priceMultiplier; 

};

#endif