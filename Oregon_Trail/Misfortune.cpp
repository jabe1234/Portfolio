// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include "Misfortune.h"
using namespace std;

Misfortune::Misfortune() // default constructor
    {
        probability = 0.4;
        travelChance = 0.0;
        stayChance = 0.0;
        moneyEffect = 0.0;
        oxenEffect = 0;
        foodEffect = 0;
        bulletEffect  = 0;
        wagonEffect  = 0;
        medicalEffect = 0;
    }

Misfortune::Misfortune(double newProbability, double newTravel, double newStay, double money, int oxen, int food, int bullet, int wagon, int medical) // parameterized constructor
    {
        probability = newProbability;
        travelChance = newTravel;
        stayChance = newStay;
        moneyEffect  = money;
        oxenEffect =  oxen;
        foodEffect = food;
        bulletEffect =  bullet;
        wagonEffect = wagon;
        medicalEffect = medical;
    }

double Misfortune::getProbability() // probability getter
    {
        return probability;
    }

void Misfortune::setProbability(double newProbability) // probability setter
    {
        probability = newProbability;
    }

double Misfortune::getTravelChance() // travel chance getter
    {
        return travelChance;
    }

void Misfortune::setTravelChance(double travel) // travel chance setter
    {
        travelChance = travel;
    }

double Misfortune::getStayChance() // stay chance getter
    {
        return stayChance;
    }

void Misfortune::setStayChance(double stay) // stay chance setter
    {
        stayChance = stay;
    }

double Misfortune::getMoneyEffect() // money getter
    {
        return moneyEffect;
    }

void Misfortune::setMoneyEffect(double money) // money setter
    {
        moneyEffect = money;
    }

int Misfortune::getOxenEffect() //  oxen getter
    {
        return oxenEffect;
    }

void Misfortune::setOxenEffect(int oxen) // oxen setter
    {
        oxenEffect = oxen;
    }

int Misfortune::getFoodEffect()//food getter
    {
        return foodEffect;
    }

void Misfortune::setFoodEffect(int food) // food setter
    {
        foodEffect = food;
    }

int Misfortune::getBulletEffect() // bullet getter
    {
        return bulletEffect;
    }

void Misfortune::setBulletEffect(int bullet) // bullet setter
    {
        bulletEffect = bullet;
    }

int Misfortune::getWagonEffect() // wagon getter
    {
        return wagonEffect;
    }

void Misfortune::setWagonEffect(int wagon) // wagon setter
    {
        wagonEffect = wagon;
    }

int Misfortune::getMedicalEffect() // medical getter
    {
        return medicalEffect;
    }

void Misfortune::setMedicalEffect(int medical) // medical setter
    {
        medicalEffect = medical;
    }
