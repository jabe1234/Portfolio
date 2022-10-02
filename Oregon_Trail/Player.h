// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
Player();
Player(string,int,int,int,int,int,double,int,string[],bool);

string getPlayerName();
void setPlayerName(string);

int getOxen();
void setOxen(int);

int getFood();
void setFood(int);

void huntingRabbit();
void huntingFox();
void huntingDeer();
void huntingBear();
void huntingMoose();

int getBullets();
void setBullets(int);

int getWagon();
void setWagon(int);

bool getWagonHealth();
void setWagonHealth(bool);

int getMedical();
void setMedical(int);

double getMoney();
void setMoney(double);

int getLocation();
void setLocation(int);

void travelTrail(int);

string getCompanionAt(int);
bool setCompanionAt(int,string);

int getComArrSize();
void setComArrSize();

bool getLiving();
void setLiving(bool);

bool getLivingAt(int);
bool setLivingAt(int, bool);


private:
string playerName;
int oxen;
int food;
int bullets;
int wagonParts;
bool wagonHealth;
int medicalAid;
double money;
int location;
string companions[4];
int comArrSize;
bool living;
bool companionsLiving[4];

};

#endif