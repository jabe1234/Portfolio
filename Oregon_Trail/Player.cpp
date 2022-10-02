// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Player.h"
using namespace std;

Player::Player() // default constructor
    {
        playerName = "";
        oxen = 0;
        food = 0;
        bullets = 0;
        wagonParts = 0;
        medicalAid = 0;
        money = 0.0;
        location = 0;
        for (int i = 0; i < 4; i++)
            {
                companions[i] = "";
            }
        comArrSize = 4;
        living = true;
        for (int i = 0; i < 4; i++)
            {
                companionsLiving[i] = true;
            }
        wagonHealth = true;
    }

Player::Player(string newPlayerName, int newOxen, int newFood, int newBullets, int newWagonParts, int newMedicalAid, double newMoney, int newLocation, string newCompanions[], bool newLiving) // paramterized constructor
    {
        playerName = newPlayerName;
        oxen = newOxen;
        food = newFood;
        bullets = newBullets;
        wagonParts = newWagonParts;
        medicalAid = newMedicalAid;
        money = newMoney;
        location = newLocation;
        for (int i = 0; i < 4; i++)
            {
                companions[i] = newCompanions[i];
            }
        comArrSize = 4;
        living = newLiving;
        for (int i = 0; i < 4; i++)
            {
                companionsLiving[i] = true;
            }
        wagonHealth = true;
    }

string Player::getPlayerName() // player name getter
    {
        return playerName;
    }

void Player::setPlayerName(string newPlayerName) // player name setter
    {
        playerName = newPlayerName;
    }

int Player::getOxen() // oxen getter
    {
        return oxen;
    }

void Player::setOxen(int newOxen) // oxen setter
    {
        oxen = newOxen;
    }

int Player::getFood() // food getter
    {
        return food;
    }

void Player::setFood(int newFood) // food setter
    {
        food = newFood;
    }

void Player::huntingRabbit() // adds 5 pounds of rabbit meat
    {
        food = food + 5;
    }

void Player::huntingFox() // adds 10 pounds of fox meat
    {
        food = food + 10;
    }

void Player::huntingDeer() // adds 60 pounds of deer meat
    {
        food = food + 60;
    }

void Player::huntingBear() // adds 200 pounds of bear meat
    {
        food = food + 200;
    }

void Player::huntingMoose() // adds 500 pounds of moose meat
    {
        food = food + 500;
    }

int Player::getBullets() // bullet getter
    {
        return bullets;
    }

void Player::setBullets(int newBullets) // bullet setter
    {
        bullets = newBullets;
    }

int Player::getWagon() //wagon getter
    {
        return wagonParts;
    }

void Player::setWagon(int newWagon) // wagon setter
    {
        wagonParts = newWagon;
    }

bool Player::getWagonHealth() // wagon health getter
    {
        return wagonHealth;
    }

void Player::setWagonHealth(bool health) // wagon health setter
    {
        wagonHealth = health;
    }

int Player::getMedical() //medical getter
    {
        return medicalAid;
    }

void Player::setMedical(int newMedical) // medical setter
    {
        medicalAid = newMedical;
    }

double Player::getMoney() // money  getter
    {
        return money;
    }

void Player::setMoney(double newMoney) // money  setter
    {
        money = newMoney;
    }

int Player::getLocation() // location setter
    {
        return location;
    }

void Player::setLocation(int newLocation) // location setter
    {
        location = newLocation;
    }

/*
 * This function moves the player a given amount
 * parameters - integer length to move player
 * return - none
*/

void Player::travelTrail(int random)
    {
        location = location + random;
    }
    
string Player::getCompanionAt(int index) // companion getter
    {
        return companions[index];
    }

bool Player::setCompanionAt(int index, string newCompanion) // companion setter
    {
        if (index >= 0 && index <= 3)
            {
                companions[index] = newCompanion;
                return true;
            }
        return false;
        
    }

int Player::getComArrSize() // companion array size getter
    {
        return 4;
    }

void Player::setComArrSize() // companion array size setter
    {
        comArrSize = 4;
    }

bool Player::getLiving() // living getter
    {
        return living;
    }

void Player::setLiving(bool newLiving) // living setter
    {
        living = newLiving;
    }

bool Player::getLivingAt(int index) // living companion getter
    {
        return companionsLiving[index];
    }

bool Player::setLivingAt(int index, bool alive) // living companion setter
    {
        if (index >= 0 && index <= 3)
            {
                companionsLiving[index] = alive;
                return true;
            }
        return false;
    }
