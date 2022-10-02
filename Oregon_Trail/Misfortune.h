// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef MISFORTUNE_H
#define MISFORTUNE_H

class Misfortune
{
public:
Misfortune();
Misfortune(double,double,double,double,int,int,int,int,int);

double getProbability();
void setProbability(double);

double getTravelChance();
void setTravelChance(double);

double getStayChance();
void setStayChance(double);

double getMoneyEffect();
void setMoneyEffect(double);

int getOxenEffect();
void setOxenEffect(int);

int getFoodEffect();
void setFoodEffect(int);

int getBulletEffect();
void setBulletEffect(int);

int getWagonEffect();
void setWagonEffect(int);

int getMedicalEffect();
void setMedicalEffect(int);

private:
double probability;
double travelChance;
double stayChance;
double moneyEffect;
int oxenEffect;
int foodEffect;
int bulletEffect;
int wagonEffect;
int medicalEffect;
};

#endif