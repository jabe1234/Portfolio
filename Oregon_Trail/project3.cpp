// CSCI 1300 Fall 2020
// Author: Jay Bentley
// Recitation: 210 - Steven Wilmes
// Project 3

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Animal.h"
#include "Date.h"
#include "Misfortune.h"
#include "Player.h"
#include "Raiders.h"
#include "Store.h"
#include "Milestone.h"
using namespace std;

/*
 * This function takes a line and splits it based a splitter character
 * paramters - a string that is going to be split, a character to split the line by, an array of strings to store the split string, and an integer that is the capacity of the storage array
 * returns - nothing returns but the array will have the segments of the  split string stored in it
*/

void split(string line, char spliter, string array[], int capacity)
    {
        int i = 0;
        int f = 0;
        bool checker = false;

          for (int g = 0; g < line.length(); g++) // splits the line by ','
                {
                    if (i > 4)
                        {
                            checker = true; // checks if the array is hitting capacity
                        }
                    if (line[g] == spliter)
                        {
                            array[i] = line.substr(f,g - f);
                            i++;
                            f = g + 1;
                        }
                }
        if (checker == false) // captures the end of the line after the last splitter character
        {
            array[i] = line.substr(f,line.length() - f);
        }
    }

/*
 * This function prints the players stats at the beginning of every turn
 * parameters - the player object with the stats stored in it, an array of milestone objects, and an integer that indexs which milestone the useris approaching
 * returns - no return but prints all the stats to the terminal
*/

void turnUpdate(Date date1, Player player1, Milestone milestones[], int milestoneCounter)
    {
        date1.switchOverMonth(); 
        date1.setDayOfWeek();
        cout << date1.getDayOfWeek() << " " << date1.getMonth() << " " << date1.getDay() << " " << date1.getYear() << endl << endl;
        cout << "TOTAL MILEAGE IS " << player1.getLocation() << endl;
        cout << "MILEAGE UNTIL NEXT MILESTONE IS " << (milestones[milestoneCounter].getMilestoneLength() - player1.getLocation()) << endl;
        cout << "OXEN      FOOD      BULLETS      WAGON PARTS      MEDICAL AID      MONEY"<< endl;
        cout << player1.getOxen() << "          " << player1.getFood() << "         " << player1.getBullets() << "             " << player1.getWagon() << "            " << player1.getMedical() << "                " << player1.getMoney() << endl;
    }

/*
 * This function calculayes how many people are alive in your party
 * parameters - the player object
 * retuns - integer of how many party members are currently alive
*/

int aliveCompanions(Player player1)
    {
        int aliveFriends = 1; // accounts for main character being alive
        for (int i = 0; i < 4; i++)
                        {
                            if (player1.getLivingAt(i) == true)
                                {
                                    aliveFriends = aliveFriends + 1;
                                }
                        }
        return aliveFriends;
    }

/*
 * This function creates all the milestone objects required for the game
 * parameters - an array of milestone objects to store the information in 
 * returns - no return
*/

void createMilestones(Milestone milestones[])
    {
        int i = 0;
        string line = "";
        string storage[2];
        ifstream in_file;
        in_file.open("milestones.txt"); // pulls information from txt file

        while (getline(in_file,line))
            {
                split(line, ',', storage, 2);
                milestones[i].setMilestoneName(storage[0]);
                int length = stoi(storage[1]);
                milestones[i].setMilestoneLength(length);
                i++;
            }
        
        in_file.close();
    }

/*
 * This function updates a counter to ensure the player is approaching the correct milestone
 * parameters - an array of milestone objects and the player object
 * returns - integer to update the correct milestone counter
*/

int updateMilestone(Milestone milestones[], Player player1)
    {
        int counter = 0;
        while (player1.getLocation() >= milestones[counter].getMilestoneLength())
            {
                counter++;
            }
        return counter;
    }

/*
 * This function pulls the player into the store interface to buy anything they need
 * parameters - the player object, the store object, and the string name of the fort they are current at
 * return - updated player object with updated stats
*/

Player shopping(Player player1, Store store1, string storeName)
    {
        cout << "WELCOME TO " << storeName << "'S STORE." << endl;
        cout << "YOU CAN PURCHASE ANYTHING YOU MIGHT NEED ON YOUR TRAVELS." << endl;

        double bill = 0;
        double availableMoney = player1.getMoney();

        int choice = 0;

        while (choice != 6)
            {
                int oxenChoice = 0;
                int foodChoice = 0;
                int bulletChoice = 0;
                int wagonChoice = 0;
                int medicalChoice = 0;


                cout << endl << "=== STORE ===" << endl; // prints store menu
                cout << "1. OXEN" << endl;
                cout << "2. FOOD" << endl;
                cout << "3. BULLETS" << endl;
                cout << "4. WAGON PARTS" << endl;
                cout << "5. MEDICAL AID KITS" << endl;
                cout << "6. QUIT SHOPPING" << endl;
                cin >> choice;

                switch (choice)
                    {
                        case 1:
                            do
                                {
                                    if (player1.getMoney() < store1.getOxenPrice()) // checks if they have enough money
                                        {
                                            cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER YOKE OF OXEN." << endl;
                                            break;
                                        }
                                    
                                    if (player1.getOxen() == 5) // checks for full oxen
                                        {
                                            cout << "YOU ALREADY HAVE THE MAXIUMUM AMOUNT OF YOKES OF OXEN." << endl;
                                            break;
                                        }

                                    cout << "HOW MANY YOKES OF OXEN WOULD YOU LIKE TO PURCHASE FOR $" << store1.getOxenPrice() << " EACH?" << endl;
                                    cin >> oxenChoice;

                                    if ((store1.getOxenPrice() * oxenChoice) > player1.getMoney()) // checks if they have enough money
                                        {
                                            cout << "THE COST OF THE QUANTITY OF YOKES OF OXEN CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }
                                    else if (player1.getOxen() + oxenChoice > 5) // checks if they have too many oxen
                                        {
                                            cout << "YOUR WAGON CAN ONLY HAVE 5 YOKES OF OXEN. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }

                                } while ((oxenChoice + player1.getOxen()) > 5 || (store1.getOxenPrice() * oxenChoice) > player1.getMoney() || oxenChoice < 0);
                                
                                bill = bill + (store1.getOxenPrice() * oxenChoice); // updates bill
                                availableMoney = availableMoney - (store1.getOxenPrice() * oxenChoice);
                                player1.setMoney(availableMoney); // updates player money
                                oxenChoice = oxenChoice + player1.getOxen();
                                player1.setOxen(oxenChoice); // updates player oxen
        
                                cout << "YOUR CURRENT BILL IS $" << bill << endl;
                                cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                                break;
                                
                        case 2:
                            do
                                {
                                    if (player1.getMoney() < store1.getFoodPrice()) // checks if they have enough money
                                        {
                                            cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER POUND OF FOOD." << endl;
                                            break;
                                        }

                                    cout << "HOW MANY POUNDS OF FOOD WOULD YOU LIKE TO PURCHASE FOR $" << store1.getFoodPrice() << " EACH?" << endl;
                                    cin >> foodChoice;

                                    if ((store1.getFoodPrice() * foodChoice) > player1.getMoney()) // checks if they have enough money
                                        {
                                            cout << "THE COST OF THE QUANTITY OF POUNDS OF FOOD CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }
                                } while (foodChoice < 0 || (store1.getFoodPrice() * foodChoice) > player1.getMoney());
        
                                bill = bill + (store1.getFoodPrice() * foodChoice);
                                availableMoney = availableMoney - (store1.getFoodPrice() * foodChoice);
                                player1.setMoney(availableMoney);
                                foodChoice = foodChoice + player1.getFood();
                                player1.setFood(foodChoice);

                                cout << "YOUR CURRENT BILL IS $" << bill << endl;
                                cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                                break;

                        case 3:
                            do
                                {
                                    if (player1.getMoney() < store1.getBulletPrice()) // checks if they have enough money
                                        {
                                            cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER BOX OF BULLETS." << endl;
                                            break;
                                        }

                                    cout << "HOW MANY BOXES OF 20 BULLETS WOULD YOU LIKE TO PURCHASE FOR $" << store1.getBulletPrice() << " EACH?" << endl;
                                    cin >> bulletChoice;

                                    if ((store1.getBulletPrice() * bulletChoice) > player1.getMoney()) // checks if they have enough money
                                        {
                                            cout << "THE COST OF THE QUANTITY OF BOXES OF BULLETS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }
                                } while (bulletChoice < 0 || (store1.getBulletPrice() * bulletChoice) > player1.getMoney());
                            
                                bill = bill + (store1.getBulletPrice() * bulletChoice);
                                availableMoney = availableMoney - (store1.getBulletPrice() * bulletChoice);
                                player1.setMoney(availableMoney);
                                bulletChoice = bulletChoice + player1.getBullets();
                                player1.setBullets(bulletChoice * 20);
                            
                                cout << "YOUR CURRENT BILL IS $" << bill << endl;
                                cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                                break;
                        case 4:
                            do
                                {
                                    if (player1.getMoney() < store1.getWagonPrice()) // checks if they have enough money
                                        {
                                            cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER WAGON PART." << endl;
                                            break;
                                        }

                                    cout << "HOW MANY WAGON PARTS WOULD YOU LIKE TO PURCHASE FOR $" << store1.getWagonPrice() << " EACH?" << endl;
                                    cin >> wagonChoice;

                                    if ((store1.getWagonPrice() * wagonChoice) > player1.getMoney()) // checks if they have enough money
                                        {
                                            cout << "THE COST OF THE QUANTITY OF WAGON PARTS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }
                                } while (wagonChoice < 0 || (store1.getWagonPrice() * wagonChoice) > player1.getMoney());
                            
                                bill = bill + (store1.getWagonPrice() * wagonChoice);
                                availableMoney = availableMoney - (store1.getWagonPrice() * wagonChoice);
                                player1.setMoney(availableMoney);
                                wagonChoice = wagonChoice + player1.getWagon();
                                player1.setWagon(wagonChoice);
                            
                                cout << "YOUR CURRENT BILL IS $" << bill << endl;
                                cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                                break;
                            
                        case 5:
                            do
                                {
                                    if (player1.getMoney() < store1.getMedicalPrice()) // checks if they have enough money
                                        {
                                            cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER MEDCIAL AID KIT." << endl;
                                            break;
                                        }
                                    cout << "HOW MANY MEDICAL AID KITS WOULD YOU LIKE TO PURCHASE FOR $" << store1.getMedicalPrice() << " EACH?" << endl;
                                    cin >> medicalChoice;

                                    if ((store1.getMedicalPrice() * medicalChoice) > player1.getMoney()) // checks if they have enough money
                                        {
                                            cout << "THE COST OF THE QUANTITY OF MEDICAL AID KITS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                        }
                                } while (wagonChoice < 0 || (store1.getMedicalPrice() * medicalChoice) > player1.getMoney());

                                bill = bill + (store1.getMedicalPrice() * medicalChoice);
                                availableMoney = availableMoney - (store1.getMedicalPrice() * medicalChoice);
                                player1.setMoney(availableMoney);
                                medicalChoice = medicalChoice + player1.getMedical();
                                player1.setMedical(medicalChoice );
                            
                                cout << "YOUR CURRENT BILL IS $" << bill << endl;
                                cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                                break;
                        
                        case 6:
                            break;
                        
                        default:
                            cout << "PLEASE ENTER ANOTHER SHOPPING CHOICE." << endl;
                            break;

                    }
                
            }
        
        cout << "THANKS FOR VISITING " << storeName << endl;
        return player1;
        }

/*
 * This function calculates the probability of raiders finding the player at their current location
 * parameters - the player object
 * returns - double probability of the raiders attacking out of 100
*/

double raiderProbability(Player player1)
    {
        int mileage = player1.getLocation();
        double middle = ((mileage / 100) - 4); // this is all a given probability function for the oregon trail game
        double top = (pow(middle,2) + 72);
        double bottom = (pow(middle,2) + 12);
        double probability = (((top / bottom) - 1) / 0.1);
        return probability;
    }

int main() {
    cout << "THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM" << endl << "INDEPENDENCE, MISSOURI TO OREGON CITY, OREGON IN 1847. YOUR" << endl << "FAMILY OF FIVE WILL COVER THE 2040 MILE OREGON TRAIL IN 5-6" << endl << "MONTHS --- IF YOU MAKE IT ALIVE." << endl << endl;

    Player player1;
    // initializing the character names
    cout << "PLEASE ENTER THE NAME OF YOUR CHARACTER:" << endl;
    string playerName1 = "";
    getline(cin,playerName1);
    player1.setPlayerName(playerName1);

    cout << "PLEASE ENTER THE NAME OF YOUR FIRST COMPANION:" << endl;
    string companion1 = "";
    getline(cin,companion1);
    player1.setCompanionAt(0, companion1);

    cout << "PLEASE ENTER THE NAME OF YOUR SECOND COMPANION:" << endl;
    string companion2 = "";
    getline(cin,companion2);
    player1.setCompanionAt(1, companion2);

    cout << "PLEASE ENTER THE NAME OF YOUR THIRD COMPANION:" << endl;
    string companion3 = "";
    getline(cin,companion3);
    player1.setCompanionAt(2, companion3);

    cout << "PLEASE ENTER THE NAME OF YOUR FOURTH COMPANION" << endl;
    string companion4 = "";
    getline(cin, companion4);
    player1.setCompanionAt(3, companion4);

    player1.setMoney(1600);

    Date date1;
    //initializing the start date
    cout << "WOULD YOU LIKE TO START ON THE DEFAULT DATE OF 03/28/1847 (YES/NO)?" << endl;
    string dateChoice = "";
    getline(cin,dateChoice);

    if (dateChoice == "YES" || dateChoice == "Yes" || dateChoice == "yes")
        {

        } 
    
    else if (dateChoice == "NO" || dateChoice == "No" || dateChoice == "no")
        {
             int monthChoice = 0;
            do
                {
                    cout << "PLEASE ENTER THE NUMBER OF THE MONTH THAT YOU WOULD LIKE TO BEGIN YOUR JOURNEY IN (03-05):" << endl;
                    cin >> monthChoice;
                } while (monthChoice < 03 || monthChoice > 05);

            int dayChoice = 0;
            string monthChoiceWord = "";

            if (monthChoice == 03)
                {
                    do
                        {
                            cout << "PLEASE ENTER THE NUMBER OF THE DAY YOU COULD LIKE TO BEGIN YOUR JOURNEY ON (01-31):" << endl;
                            cin >> dayChoice;
                        } while (dayChoice < 01 || dayChoice > 31);
                    monthChoiceWord = "March";
                }

            if (monthChoice == 04)
                {
                    do
                        {
                            cout << "PLEASE ENTER THE NUMBER OF THE DAY YOU COULD LIKE TO BEGIN YOUR JOURNEY ON (01-30):" << endl;
                            cin >> dayChoice;
                        } while (dayChoice < 01 || dayChoice > 30);
                    monthChoiceWord = "April";
                }
            
            if (monthChoice == 05)
                {
                    cout << "YOU MUST BEGIN ON THE FIRST DAY OF THE MONTH IN MAY (05)." << endl;
                    dayChoice = 01;
                    monthChoiceWord = "May";
                }
            
            cout << "YOUR JOURNEY MUST TAKE PLACE IN 1847." << endl;
            int yearChoice = 1847;

            date1.setMonth(monthChoiceWord);
            date1.setMonthNumber(monthChoice);
            date1.setDay(dayChoice);
            date1.setYear(yearChoice);
            
        }
    
    Store store1;
    const double store1Multiplier = 1.0;
    store1.setMultiplier(store1Multiplier);

    const double OxenPrice = 40.0;
    store1.setOxenPrice(OxenPrice);

    const double FoodPrice = 0.50;
    store1.setFoodPrice(FoodPrice);

    const double BulletPrice = 2.0;
    store1.setBulletPrice(BulletPrice);

    const double MedicalPrice = 25.0;
    store1.setMedicalPrice(MedicalPrice);

    const double WagonPrice = 20.0;
    store1.setWagonPrice(WagonPrice);

    cout << endl;
    ifstream in_file;
    in_file.open("store_info.txt"); // prints information on the store
    string line = "";
    while (getline(in_file,line))
        {
            cout << line << endl;
        }
    in_file.close();
    cout << endl;
    // buying initial items from store
    double bill = 0;
    double availableMoney = player1.getMoney();

    int oxenChoice = 0;
    do
        {
            cout << "HOW MANY YOKES OF OXEN WOULD YOU LIKE TO PURCHASE FOR $40 EACH (3-5)?" << endl;
            cin >> oxenChoice;
        } while (oxenChoice < 3 || oxenChoice > 5); // these are the only values that can be bought initially
    
    player1.setOxen(oxenChoice);
    bill = bill + (store1.getOxenPrice() * oxenChoice);
    availableMoney = availableMoney - (store1.getOxenPrice() * oxenChoice);
    player1.setMoney(availableMoney);
    
    cout << "YOUR CURRENT BILL IS $" << bill << endl;
    cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;

    int foodChoice = 0;
    do
        {
            cout << "HOW MANY POUNDS OF FOOD WOULD YOU LIKE TO PURCHASE FOR $0.5 EACH?" << endl;
            cin >> foodChoice;

            if ((store1.getFoodPrice() * foodChoice) > player1.getMoney()) // checks if they have enough money
                {
                    cout << "THE COST OF THE QUANTITY OF POUNDS OF FOOD CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                }
        } while (foodChoice < 0 || (store1.getFoodPrice() * foodChoice) > player1.getMoney());
    
    player1.setFood(foodChoice);
    bill = bill + (store1.getFoodPrice() * foodChoice);
    availableMoney = availableMoney - (store1.getFoodPrice() * foodChoice);
    player1.setMoney(availableMoney);

    cout << "YOUR CURRENT BILL IS $" << bill << endl;
    cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
    
    int bulletChoice = 0;
    do
        {
            cout << "HOW MANY BOXES OF 20 BULLETS WOULD YOU LIKE TO PURCHASE FOR $2 EACH?" << endl;
            cin >> bulletChoice;

            if ((store1.getBulletPrice() * bulletChoice) > player1.getMoney()) // checks if they have enough money
                {
                    cout << "THE COST OF THE QUANTITY OF BOXES OF BULLETS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                }
        } while (bulletChoice < 0 || (store1.getBulletPrice() * bulletChoice) > player1.getMoney());
    
    player1.setBullets(bulletChoice * 20);
    bill = bill + (store1.getBulletPrice() * bulletChoice);
    availableMoney = availableMoney - (store1.getBulletPrice() * bulletChoice);
    player1.setMoney(availableMoney);
    
    cout << "YOUR CURRENT BILL IS $" << bill << endl;
    cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;

    int wagonChoice = 0;
    do
        {
            cout << "HOW MANY WAGON PARTS WOULD YOU LIKE TO PURCHASE FOR $20 EACH?" << endl;
            cin >> wagonChoice;

            if ((store1.getWagonPrice() * wagonChoice) > player1.getMoney()) // checks if they have enough money
                {
                    cout << "THE COST OF THE QUANTITY OF WAGON PARTS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                }
        } while (wagonChoice < 0 || (store1.getWagonPrice() * wagonChoice) > player1.getMoney());
    
    player1.setWagon(wagonChoice);
    bill = bill + (store1.getWagonPrice() * wagonChoice);
    availableMoney = availableMoney - (store1.getWagonPrice() * wagonChoice);
    player1.setMoney(availableMoney);
    
    cout << "YOUR CURRENT BILL IS $" << bill << endl;
    cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;

    int medicalChoice = 0;
    do
        {
            cout << "HOW MANY MEDICAL AID KITS WOULD YOU LIKE TO PURCHASE FOR $25 EACH?" << endl;
            cin >> medicalChoice;

            if ((store1.getMedicalPrice() * medicalChoice) > player1.getMoney())  // checks if they have enough money
                {
                    cout << "THE COST OF THE QUANTITY OF MEDICAL AID KITS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                }
        } while (wagonChoice < 0 || (store1.getMedicalPrice() * medicalChoice) > player1.getMoney());
    
    player1.setMedical(medicalChoice);
    bill = bill + (store1.getMedicalPrice() * medicalChoice);
    availableMoney = availableMoney - (store1.getMedicalPrice() * medicalChoice);
    player1.setMoney(availableMoney);
    
    cout << "YOUR CURRENT BILL IS $" << bill << endl;
    cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;

    int choice = 0;
    cout << "YOU CAN PURCHASE ANYTHING ELSE YOU MIGHT NEED BEFORE YOU ENBARK ON YOUR TRAVELS." << endl;

    while (choice != 6)
        {
            cout << endl << "=== STORE ===" << endl; // prints menu for store
            cout << "1. OXEN" << endl;
            cout << "2. FOOD" << endl;
            cout << "3. BULLETS" << endl;
            cout << "4. WAGON PARTS" << endl;
            cout << "5. MEDICAL AID KITS" << endl;
            cout << "6. QUIT SHOPPING" << endl;
            cin >> choice;

            switch (choice)
                {
                    case 1:
                        do
                            {
                                if (player1.getMoney() < 40) // checks if they have enough money
                                    {
                                        cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER YOKE OF OXEN." << endl;
                                        break;
                                    }

                                cout << "HOW MANY YOKES OF OXEN WOULD YOU LIKE TO PURCHASE FOR $40 EACH (3-5)?" << endl;
                                cin >> oxenChoice;

                                if ((store1.getOxenPrice() * oxenChoice) > player1.getMoney()) // checks if they have enough money
                                    {
                                        cout << "THE COST OF THE QUANTITY OF YOKES OF OXEN CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }
                                else if (player1.getOxen() + oxenChoice > 5) // checks they dont have too many oxen
                                    {
                                        cout << "YOUR WAGON CAN ONLY HAVE 5 YOKES OF OXEN. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }

                            } while ((oxenChoice + player1.getOxen()) > 5 || (store1.getOxenPrice() * oxenChoice) > player1.getMoney() || oxenChoice < 0);
                            
                            bill = bill + (store1.getOxenPrice() * oxenChoice);
                            availableMoney = availableMoney - (store1.getOxenPrice() * oxenChoice);
                            player1.setMoney(availableMoney);
                            oxenChoice = oxenChoice + player1.getOxen();
                            player1.setOxen(oxenChoice);
    
                            cout << "YOUR CURRENT BILL IS $" << bill << endl;
                            cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                            break;
                            
                    case 2:
                        do
                            {
                                if (player1.getMoney() < 0.5) // checks if they have enough money
                                    {
                                        cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER POUND OF FOOD." << endl;
                                        break;
                                    }

                                cout << "HOW MANY POUNDS OF FOOD WOULD YOU LIKE TO PURCHASE FOR $0.5 EACH?" << endl;
                                cin >> foodChoice;

                                if ((store1.getFoodPrice() * foodChoice) > player1.getMoney()) // checks if they have enough money
                                    {
                                        cout << "THE COST OF THE QUANTITY OF POUNDS OF FOOD CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }
                            } while (foodChoice < 0 || (store1.getFoodPrice() * foodChoice) > player1.getMoney());
    
                            bill = bill + (store1.getFoodPrice() * foodChoice);
                            availableMoney = availableMoney - (store1.getFoodPrice() * foodChoice);
                            player1.setMoney(availableMoney);
                            foodChoice = foodChoice + player1.getFood();
                            player1.setFood(foodChoice);

                            cout << "YOUR CURRENT BILL IS $" << bill << endl;
                            cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                            break;

                    case 3:
                        do
                            {
                                if (player1.getMoney() < 2) // checks if they have enough money
                                    {
                                        cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER BOX OF BULLETS." << endl;
                                        break;
                                    }

                                cout << "HOW MANY BOXES OF 20 BULLETS WOULD YOU LIKE TO PURCHASE FOR $2 EACH?" << endl;
                                cin >> bulletChoice;

                                if ((store1.getBulletPrice() * bulletChoice) > player1.getMoney()) // checks if they have enough money
                                    {
                                        cout << "THE COST OF THE QUANTITY OF BOXES OF BULLETS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }
                            } while (bulletChoice < 0 || (store1.getBulletPrice() * bulletChoice) > player1.getMoney());
                        
                            bill = bill + (store1.getBulletPrice() * bulletChoice);
                            availableMoney = availableMoney - (store1.getBulletPrice() * bulletChoice);
                            player1.setMoney(availableMoney);
                            bulletChoice = bulletChoice + player1.getBullets();
                            player1.setBullets(bulletChoice * 20);
                        
                            cout << "YOUR CURRENT BILL IS $" << bill << endl;
                            cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                            break;
                    case 4:
                        do
                            {
                                if (player1.getMoney() < 20)  // checks if they have enough money
                                    {
                                        cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER WAGON PART." << endl;
                                        break;
                                    }

                                cout << "HOW MANY WAGON PARTS WOULD YOU LIKE TO PURCHASE FOR $20 EACH?" << endl;
                                cin >> wagonChoice;

                                if ((store1.getWagonPrice() * wagonChoice) > player1.getMoney()) // checks if they have enough money
                                    {
                                        cout << "THE COST OF THE QUANTITY OF WAGON PARTS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }
                            } while (wagonChoice < 0 || (store1.getWagonPrice() * wagonChoice) > player1.getMoney());
                        
                            bill = bill + (store1.getWagonPrice() * wagonChoice);
                            availableMoney = availableMoney - (store1.getWagonPrice() * wagonChoice);
                            player1.setMoney(availableMoney);
                            wagonChoice = wagonChoice + player1.getWagon();
                            player1.setWagon(wagonChoice);
                        
                            cout << "YOUR CURRENT BILL IS $" << bill << endl;
                            cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                            break;
                        
                    case 5:
                        do
                            {
                                if (player1.getMoney() < 25) // checks if they have enough money
                                    {
                                        cout << "YOU DO NOT HAVE ENOUGH MONEY FOR ANOTHER MEDCIAL AID KIT." << endl;
                                        break;
                                    }
                                cout << "HOW MANY MEDICAL AID KITS WOULD YOU LIKE TO PURCHASE FOR $25 EACH?" << endl;
                                cin >> medicalChoice;

                                if ((store1.getMedicalPrice() * medicalChoice) > player1.getMoney()) // checks if they have enough money
                                    {
                                        cout << "THE COST OF THE QUANTITY OF MEDICAL AID KITS CHOSEN EXCEEDS THE AMOUNT OF MONEY AVAILABLE. PLEASE CHOOSE A NEW QUANTITY." << endl;
                                    }
                            } while (wagonChoice < 0 || (store1.getMedicalPrice() * medicalChoice) > player1.getMoney());

                            bill = bill + (store1.getMedicalPrice() * medicalChoice);
                            availableMoney = availableMoney - (store1.getMedicalPrice() * medicalChoice);
                            player1.setMoney(availableMoney);
                            medicalChoice = medicalChoice + player1.getMedical();
                            player1.setMedical(medicalChoice );
                        
                            cout << "YOUR CURRENT BILL IS $" << bill << endl;
                            cout << "YOU CURRENTLY HAVE $" << availableMoney << endl;
                            break;
                    
                    case 6:
                        break;
                    
                    default:
                        cout << "PLEASE ENTER ANOTHER SHOPPING CHOICE." << endl;
                        break;

                }
            
        }
    cout << "YOUR PARTY NOW PREPARES TO LEAVE ON THEIR TRIP ALONG THE ORGEON TRAIL." << endl;
    // random variables
    int dailyChoice = 0;
    int currentFood = 0;
    int aliveFriends = 0;
    string blank = "";
    int randomMovement = 0;
    int randomTime = 0;

    // store objects
    string storeChoice = "";
    Store store2 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,1.25);
    Store store3 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,1.50);
    Store store4 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,1.75);
    Store store5 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,2.00);
    Store store6 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,2.25);
    Store store7 = Store(OxenPrice,FoodPrice,BulletPrice,WagonPrice,MedicalPrice,2.50);

    // store array
    Store stores[6];
    stores[0] = store2;
    stores[1] = store3;
    stores[2] = store4;
    stores[3] = store5;
    stores[4] = store6;
    stores[5] = store7;
    stores[0].setOxenPrice(2 * 2 * 10);

    //animal objects
    Animal rabbit("RABBIT", 5, 10, 0.5);
    Animal fox("FOX", 10, 8, 0.25);
    Animal deer("DEER", 60, 5, 0.15);
    Animal bear("BEAR", 200, 10, 0.07);
    Animal moose("MOOSE", 500, 12, 0.05);

    // huntung variables
    bool rabbitFound = false;
    bool foxFound = false;
    bool deerFound = false;
    bool bearFound = false;
    bool mooseFound = false;
    int huntingChoice= 0;
    int huntingFood = 0;
    int huntingBullets= 0;
    int foodEatingChoice = 0;

    // milestone variables
    Milestone milestones[15];
    int milestoneCounter = 0;
    createMilestones(milestones);
    bool milestoneCheck = false;

    // puzzle varaibles
    int puzzleRandom = 0;
    int puzzleCounter = 0;
    int puzzleGuess = 0;

    //misfortune objects
    Misfortune sickness = Misfortune(0.4, 0.7, 0.3, 0.0, 0, 0, 0, 0, 1);
    Misfortune oxenDeath =  Misfortune(0.4, 0.0, 0.0, 0.0, 1, 0, 0, 0, 0);
    Misfortune wagonBreaks = Misfortune(0.4, 0.0, 0.0, 0.0, 0, 0, 0, 1, 0);
    Misfortune foodSpoilage = Misfortune(0.4, 0.0, 0.0, 0.0, 0, 10, 0, 0, 0);
    Misfortune piratesGold = Misfortune(0.4, 0.0, 0.0, 500, 0, 0, 0, 0, 0);
    Misfortune helpingOthers = Misfortune(0.4, 0.0, 0.0, 0.0, 1, 100, 50, 1, 1);

    //misfortune variables
    const double misfortuneChance = 0.4;
    double misfortuneProbabilityGenerator = 0.0;
    double misfortuneChoice = 0.0;
    int oxenLeft = 0;
    int wagonLeft = 0;
    int foodLeft = 0;
    int bulletLeft = 0;
    double moneyLeft = 0.0;
    int medicalLeft = 0;
    int helpChoice = 0;
    bool sick = false;
    string sicknessName = "";
    double sickChoice = 0.0;
    string sickCompanion = "";
    int sickCompanionTracker = 0;
    double companionChoice = 0.0;
    double deathChance = 0.0;
    int currentDay = 0;

    // raiders variables
    Raiders raiders1 = Raiders();
    double randomRaider = 0.0;
    int raiderChoice = 0;


    do  // main gameplay loop
    {
        milestoneCounter = updateMilestone(milestones, player1);
        milestoneCheck = false;
        for (int i = 0; i < 15; i++) // tests ifthe player is at a milestone
            {
                if (player1.getLocation() == milestones[i].getMilestoneLength())
                    {
                        milestoneCheck = true;
                    }
            }

        turnUpdate(date1, player1, milestones, milestoneCounter); // prints players stats

        if (milestoneCheck == true)
            {
                cout << "YOU HAVE ARRIVED AT " << milestones[milestoneCounter - 1].getMilestoneName() << endl;

                if (player1.getLocation() == 304 || player1.getLocation() == 640 || player1.getLocation() == 989 || player1.getLocation() == 1395 || player1.getLocation() == 1648 || player1.getLocation() == 1863) // if player is at store
                    {
                        cout << "YOU HAVE ARRIVED AT A FORT ALONG THE TRAIL. WOULD YOU LIKE TO VISIT THE STORE IN THE FORT TO RESTOCK (YES/NO)?" << endl;
                        getline(cin,blank);
                        getline(cin,storeChoice);

                        if (storeChoice == "YES" || storeChoice == "Yes" || storeChoice == "yes")
                            {
                                if (player1.getLocation() == 304)
                                    {
                                        player1 = shopping(player1, store2, milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                                
                                if (player1.getLocation() == 640)
                                    {
                                        player1 = shopping(player1, stores[1], milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                                
                                if (player1.getLocation() == 989)
                                    {
                                        player1 = shopping(player1, stores[2], milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                                
                                if (player1.getLocation() == 1395)
                                    {
                                        player1 = shopping(player1, stores[3], milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                                
                                if (player1.getLocation() == 1648)
                                    {
                                        player1 = shopping(player1, stores[4], milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                                
                                if (player1.getLocation() == 1863)
                                    {
                                        player1 = shopping(player1, stores[5], milestones[milestoneCounter - 1].getMilestoneName());
                                    }
                            }
                    }
            }

        cout << " === WHAT WOULD YOU LIKE TO DO? ===" << endl;  //  player choice menu
        cout << "1. REST" << endl;
        cout << "2. CONTINUE ON THE TRAIL" << endl;
        cout << "3. HUNT" << endl;
        cout << "4. QUIT" << endl;
        cin >> dailyChoice;

        switch (dailyChoice)
            {
                case 1: //Rest
                    randomTime = 1 + (2 * ((double)rand() / (double)RAND_MAX));
                    date1.chooseRest(randomTime); // random 1-3 days
                    currentFood = player1.getFood();
                    aliveFriends = aliveCompanions(player1);
                    
                    player1.setFood(currentFood - (3 * randomTime * aliveFriends));
                    break;
                
                case 2: //Continue
                    date1.chooseContinue(); // 14 days
                    currentFood = player1.getFood();
                    aliveFriends = aliveCompanions(player1);
                    player1.setFood(currentFood - (42 * aliveFriends));

                    randomMovement = 70 + (70 * ((double)rand() / (double)RAND_MAX)); // random 70-140 miles

                    if (milestones[milestoneCounter].getMilestoneLength() - player1.getLocation() <= randomMovement) // sets players location at milestone if they reached one
                        {
                            player1.setLocation(milestones[milestoneCounter].getMilestoneLength());
                        }
                    else
                        {
                            player1.travelTrail(randomMovement);
                        }
                    break;
                
                case 3: //Hunting
                    date1.chooseHunting();

                    rabbitFound = false;
                    foxFound = false;
                    deerFound = false;
                    bearFound = false;
                    mooseFound = false;
                    // randomly determines if each animal was found
                    if (((double)rand() / (double)RAND_MAX) < rabbit.getChance())
                        {
                            rabbitFound = true;
                        }
                    
                    if (((double)rand() / (double)RAND_MAX) < fox.getChance())
                        {
                            foxFound = true;
                        }
                    
                    if (((double)rand() / (double)RAND_MAX) < deer.getChance())
                        {
                            deerFound = true;
                        }
                    
                    if (((double)rand() / (double)RAND_MAX) < bear.getChance())
                        {
                            bearFound = true;
                        }
                    
                    if (((double)rand() / (double)RAND_MAX) < moose.getChance())
                        {
                            mooseFound = true;
                        }
                    
                    
                    if (rabbitFound == true) // hunting rabbit
                        {
                            cout << "YOU GOT LUCKY AND ENCOUNTERED A RABBIT. WOULD YOU LIKE TO HUNT:" << endl;
                            cout << "(1) YES, (2) NO" << endl;
                            cin >> huntingChoice;

                            if (huntingChoice == 1)
                                {
                                    if (player1.getBullets() < 10)
                                        {
                                            cout << "YOU DID NOT KILL THE RABBIT." << endl;
                                        }
                                    else
                                        {
                                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);
                                           

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU KILLED THE RABBIT." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + rabbit.getMeat());
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets - rabbit.getBullet());
                                                }
                                            else
                                                {
                                                

                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU KILLED THE RABBIT." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + rabbit.getMeat());
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets - rabbit.getBullet());
                                                        }
                                                    else
                                                        {
                                                        

                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU KILLED THE RABBIT." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + rabbit.getMeat());
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - rabbit.getBullet());
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO KILL THE RABBIT." << endl;
                                                                }
                                                        }
                                        }
                                }


                        }
                        }
                    
                    if (foxFound == true) // hunting fox
                        {
                            cout << "YOU GOT LUCKY AND ENCOUNTERED A FOX. WOULD YOU LIKE TO HUNT:" << endl;
                            cout << "(1) YES, (2) NO" << endl;
                            cin >> huntingChoice;

                            if (huntingChoice == 1)
                                {
                                    if (player1.getBullets() < 10)
                                        {
                                            cout << "YOU DID NOT KILL THE FOX." << endl;
                                        }
                                    else
                                        {
                                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);

                                           

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU KILLED THE FOX." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + fox.getMeat());
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets - fox.getBullet());
                                                }
                                            else
                                                {
                                                   

                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU KILLED THE FOX." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + fox.getMeat());
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets - fox.getBullet());
                                                        }
                                                    else
                                                        {
                                                           

                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU KILLED THE FOX." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + fox.getMeat());
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - fox.getBullet());
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO KILL THE FOX."<< endl;
                                                                }
                                                        }
                                        }
                                }


                        }
                        }
                    if (deerFound == true) // hunting deer
                        {
                            cout << "YOU GOT LUCKY AND ENCOUNTERED A DEER. WOULD YOU LIKE TO HUNT:" << endl;
                            cout << "(1) YES, (2) NO" << endl;
                            cin >> huntingChoice;

                            if (huntingChoice == 1)
                                {
                                    if (player1.getBullets() < 10)
                                        {
                                            cout << "YOU DID NOT KILL THE DEER." << endl;
                                        }
                                    else
                                        {
                                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU KILLED THE DEER." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + deer.getMeat());
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets - deer.getBullet());
                                                }
                                            else
                                                {
                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU KILLED THE DEER." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + deer.getMeat());
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets - deer.getBullet());
                                                        }
                                                    else
                                                        {
                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU KILLED THE DEER." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + deer.getMeat());
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - deer.getBullet());
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO KILL THE DEER."<< endl;
                                                                }
                                                        }
                                        }
                                }


                        }
                        }
                    if (bearFound == true) //hunting bear
                        {
                            cout << "YOU GOT LUCKY AND ENCOUNTERED A BEAR. WOULD YOU LIKE TO HUNT:" << endl;
                            cout << "(1) YES, (2) NO" << endl;
                            cin >> huntingChoice;

                            if (huntingChoice == 1)
                                {
                                    if (player1.getBullets() < 10)
                                        {
                                            cout << "YOU DID NOT KILL THE BEAR." << endl;
                                        }
                                    else
                                        {
                                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU KILLED THE BEAR." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + bear.getMeat());
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets - bear.getBullet());
                                                }
                                            else
                                                {
                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU KILLED THE BEAR." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + bear.getMeat());
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets - bear.getBullet());
                                                        }
                                                    else
                                                        {
                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU KILLED THE BEAR." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + bear.getMeat());
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - bear.getBullet());
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO KILL THE BEAR."<< endl;
                                                                }
                                                        }
                                        }
                                }


                        }
                        }
                        
                    if (mooseFound == true) // huntung moose
                        {
                            cout << "YOU GOT LUCKY AND ENCOUNTERED A MOOSE. WOULD YOU LIKE TO HUNT:" << endl;
                            cout << "(1) YES, (2) NO" << endl;
                            cin >> huntingChoice;

                            if (huntingChoice == 1)
                                {
                                    if (player1.getBullets() < 12)
                                        {
                                            cout << "YOU DID NOT KILL THE FOX." << endl;
                                        }
                                    else
                                        {
                                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU KILLED THE MOOSE." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + moose.getMeat());
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets - moose.getBullet());
                                                }
                                            else
                                                {
                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU KILLED THE MOOSE." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + moose.getMeat());
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets - moose.getBullet());
                                                        }
                                                    else
                                                        {
                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU KILLED THE MOOSE." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + moose.getMeat());
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - moose.getBullet());
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO KILL THE MOOSE."<< endl;
                                                                }
                                                        }
                                        }
                                }


                        }
                    
                    

                    
            }
        
                    cout << "HOW WOULD YOU LIKE TO EAT AFTER YOUR HUNTING?" << endl;
                    cout << "(1) POORLY, (2) MODERATELY, (3) WELL" << endl;
                    cin >> foodEatingChoice;

                    switch (foodEatingChoice) // player chooses how much to eat after hunting
                        {
                            case 1:
                                aliveFriends = aliveCompanions(player1);
                                currentFood = player1.getFood();

                                player1.setFood(currentFood - (2 * aliveFriends));
                                break;

                            case 2:
                                aliveFriends = aliveCompanions(player1);
                                currentFood = player1.getFood();

                                player1.setFood(currentFood - (3 * aliveFriends));
                                break;
                            
                            case 3:
                                aliveFriends = aliveCompanions(player1);
                                currentFood = player1.getFood();

                                player1.setFood(currentFood - (5 * aliveFriends));
                                break;
                        }
                    
                    if (player1.getFood() > 1000)   // wagon can only hold 1000 pounds of food
                        {
                            cout << "YOUR WAGON CAN ONLY HOLD 1000 POUNDS OF FOOD. YOU HAVE TO LEAVE ALL FOOD OVER 1000 POUNDS." << endl;
                            player1.setFood(1000);
                        }
                    
                    break;
                
                case 4: // quit
                    {
                        cout << "YOUR PARTY DID NOT MAKE IT TO OREGON CITY." << endl;
                        player1.setWagonHealth(false);
                    }
            }
        
        sick = false;  // reverts sickness  after a whole turn

        misfortuneProbabilityGenerator = ((double)rand() / (double)RAND_MAX);
        if (misfortuneProbabilityGenerator < misfortuneChance)
            {
                misfortuneChoice = ((double)rand() / (double)RAND_MAX);
                companionChoice = ((double)rand() / (double)RAND_MAX);
                sickChoice = ((double)rand() / (double)RAND_MAX);

                if (misfortuneChoice >= 0 && misfortuneChoice <= 0.25) // sickness
                    {
                        sick = true;
                        if (aliveCompanions(player1) == 5)
                            {
                                // chance for each party member
                                if (companionChoice >= 0 && companionChoice <= 0.2)
                                    {
                                        sickCompanion = player1.getPlayerName();
                                        sickCompanionTracker = -1;
                                    }
                                
                                if (companionChoice > 0.2 && companionChoice <= 0.4)
                                    {
                                        sickCompanion = player1.getCompanionAt(0);
                                        sickCompanionTracker = 0;
                                    }
                                
                                if (companionChoice > 0.4 && companionChoice  <= 0.6)
                                    {
                                        sickCompanion = player1.getCompanionAt(1);
                                        sickCompanionTracker = 1;
                                    }
                                
                                if (companionChoice > 0.6 && companionChoice <= 0.8)
                                    {
                                        sickCompanion = player1.getCompanionAt(2);
                                        sickCompanionTracker = 2;
                                    }
                                
                                if (companionChoice > 0.8 && companionChoice <= 1)
                                    {
                                        sickCompanion = player1.getCompanionAt(3);
                                        sickCompanionTracker = 3;
                                    }
                            }
                        // chnace for each type of disease
                        if (sickChoice >= 0 && sickChoice <= (1 / 6))
                            {
                                sicknessName = "TYPHOID";
                            }
                        
                        if (sickChoice > (1 / 6) && sickChoice <= (2 / 6))
                            {
                                sicknessName = "CHOLERA";
                            }

                        if (sickChoice > (2 / 6) && sickChoice <= (3 / 6))
                            {
                                sicknessName = "DIARRHEA";
                            }
                        
                        if (sickChoice > (3 / 6) && sickChoice <= (4 / 6))
                            {
                                sicknessName = "MEASLES";
                            }
                        
                        if (sickChoice > (4 / 6) && sickChoice <= (5 / 6))
                            {
                                sicknessName = "DYSENTERY";
                            }
                        
                        if (sickChoice > (5 / 6) && sickChoice <= 1)
                            {
                                sicknessName = "FEVER";
                            }
                        
                        cout << sickCompanion << " HAS GOTTEN SICK WITH " << sicknessName << "." << endl;
                        deathChance = ((double)rand() / (double)RAND_MAX);
                    
                        if (player1.getMedical() > 0) // uses medical aid
                            {
                                medicalLeft = player1.getMedical();
                                player1.setMedical(medicalLeft - 1);
                                if (deathChance > 0.5)
                                    {
                                        cout << sickCompanion << " HAS DIED." << endl;
                                        
                                        if (sickCompanionTracker == -1)
                                            {
                                                player1.setLiving(false);
                                            }
                                        if (sickCompanionTracker > 0)
                                            {
                                                player1.setLivingAt(sickCompanionTracker, false);
                                            }
                                    }
                                else
                                    {
                                        cout << sickCompanion << " HAS RECOVERED" << endl;
                                    }
                            }
                        else // no medical aid
                            {
                                cout << "YOU CAN EITHER CHOOSE TO REST OR PRESS ON." << endl;
                                cout << "1. REST" << endl;
                                cout << "2. CONTINUE" << endl;
                                cin >> helpChoice;

                                switch (helpChoice)
                                    {
                                        case 1:
                                            currentDay = date1.getDay();
                                            date1.setDay(currentDay + 3);
                                            currentFood = player1.getFood();
                                            aliveFriends = aliveCompanions(player1);
                                            
                                            player1.setFood(currentFood - (3 * randomTime * aliveFriends));
                                            if (deathChance < 0.3)
                                                {
                                                    cout << sickCompanion << " HAS DIED." << endl;
                                        
                                                    if (sickCompanionTracker == -1)
                                                        {
                                                            player1.setLiving(false);
                                                        }
                                                    if (sickCompanionTracker > 0)
                                                        {
                                                            player1.setLivingAt(sickCompanionTracker, false);
                                                        }
                                                }
                                            else
                                                {
                                                    cout << sickCompanion << " HAS RECOVERED" << endl;
                                                }
                                            break;
                                        case 2:
                                            date1.chooseContinue();
                                            currentFood = player1.getFood();
                                            aliveFriends = aliveCompanions(player1);
                                            player1.setFood(currentFood - (42 * aliveFriends));

                                            randomMovement = 70 + (70 * ((double)rand() / (double)RAND_MAX));

                                            if (milestones[milestoneCounter].getMilestoneLength() - player1.getLocation() <= randomMovement)
                                                {
                                                    player1.setLocation(milestones[milestoneCounter].getMilestoneLength());
                                                }
                                            else
                                                {
                                                    player1.travelTrail(randomMovement);
                                                }
                                            
                                            if (deathChance < 0.7)
                                                {
                                                    cout << sickCompanion << " HAS DIED." << endl;
                                        
                                                    if (sickCompanionTracker == -1)
                                                        {
                                                            player1.setLiving(false);
                                                        }
                                                    if (sickCompanionTracker > 0)
                                                        {
                                                            player1.setLivingAt(sickCompanionTracker, false);
                                                        }
                                                }
                                            else
                                                {
                                                    cout << sickCompanion << " HAS RECOVERED" << endl;
                                                }
                                            
                                            break;

                                    }
                            }

                    }
                
                if (misfortuneChoice > 0.25 && misfortuneChoice <= 0.5) // oxen dies
                    {
                        oxenLeft = player1.getOxen();
                        player1.setOxen(oxenLeft - oxenDeath.getOxenEffect());
                        cout << "ONE OF YOUR OXEN HAS DIED. YOU HAVE " <<  player1.getOxen() << " OXEN LEFT." << endl;

                        if (player1.getOxen() == 0) // all oxen died
                            {
                                cout << "YOU HAVE NO MORE OXEN. YOUR TIME ON THE OREGON TRAIL HAS COME TO AN END." << endl;
                            }
                    }
                
                if (misfortuneChoice > 0.5 && misfortuneChoice <= 0.75)  // wagon breaks
                    {
                        wagonLeft = player1.getWagon();
                        cout << "ONE OF THE WHEELS ON YOUR WAGON HAS BROKEN." << endl;
                        
                        if (wagonLeft > 0)
                            {
                                cout << "YOU USED A SPARE WAGON PART TO FIX YOUR WHEEL." << endl;
                                player1.setWagon(wagonLeft - wagonBreaks.getWagonEffect());
                            }
                        
                        else
                            {
                                cout << "YOU DO NOT HAVE ANY SPARE WAGON PARTS AND YOUR WAGON REMAINS BROKEN. YOUR TIME ON THE OREGON TRAIL HAS COME TO AN END." << endl;
                                player1.setWagonHealth(false);
                            }
                    }
                
                if (misfortuneChoice > 0.75 && misfortuneChoice <= 0.85) // food  spoils
                    {
                        foodLeft = player1.getFood();
                        cout << "SOME OF YOUR FOOD HAS SPOILED AND CANNOT BE EATEN ANYMORE." << endl;
                        player1.setFood(foodLeft - foodSpoilage.getFoodEffect());

                        if (player1.getFood() <= 0)
                            {
                                cout << "YOU HAVE RUN OUT OF FOOD. YOUR TIME ON THE OREGON TRAIL HAS COME TO AN END." << endl;
                            }
                    }
                
                if (misfortuneChoice > 0.85 && misfortuneChoice <= 0.95) // pirate gold
                    {
                        moneyLeft =  player1.getMoney();
                        cout << "YOU HAVE FOUND PIRATE GOLD ALONG THE TRAIL SIDE." << endl;
                        player1.setMoney(moneyLeft + piratesGold.getMoneyEffect());
                    }
                
                if (misfortuneChoice > 0.95 && misfortuneChoice <= 1)  // helping others
                    {
                        cout << "YOU CHOSE TO HELP OTHER TRAVELERS STUCK IN THE MUD. CHOOSE ONE REWARD." << endl;
                        cout << "1. 1 OXEN" << endl;
                        cout << "2. 100 POUNDS OF FOOD" << endl;
                        cout << "3. 50 BULLETS" << endl;
                        cout << "4. 1 WAGON PART"<< endl;
                        cout << "5. 1 MEDICAL AID KIT" << endl;
                        cin >> helpChoice;

                        switch (helpChoice)
                            {
                                case 1:
                                    oxenLeft = player1.getOxen();
                                    player1.setOxen(oxenLeft + helpingOthers.getOxenEffect());
                                    break;
                                
                                case 2:
                                    foodLeft = player1.getFood();
                                    player1.setFood(foodLeft + helpingOthers.getFoodEffect());
                                    break;
                                
                                case 3:
                                    bulletLeft = player1.getBullets();
                                    player1.setBullets(bulletLeft + helpingOthers.getBulletEffect());
                                    break;
                                
                                case 4:
                                    wagonLeft = player1.getWagon();
                                    player1.setWagon(wagonLeft + helpingOthers.getWagonEffect());
                                    break;
                                
                                case 5:
                                    medicalLeft = player1.getMedical();
                                    player1.setMedical(medicalLeft + helpingOthers.getMedicalEffect());
                                    break;
                            }

                    }
            }
        
        raiders1.setRaiderProbability(raiderProbability(player1));
        randomRaider = 100 *  ((double)rand() / (double)RAND_MAX);

        if (randomRaider <= raiders1.getRaiderProbability()) //raiders attack
            {
                cout << "THE BAND OF RAIDERS HAS FOUND YOU. HOW WOULD YOU LIKE TO DEAL WITH THEM?" << endl;

                cout << endl << "1. RUN" << endl;
                cout << "2. ATTACK" << endl;
                cout << "3. SURRENDER" << endl;
                cin >> raiderChoice;

                switch (raiderChoice)
                    {
                        case 1:
                            cout << "YOUR PARTY HAS ESCAPED BUT LEFT SOME MATERIALS." << endl;
                            oxenLeft = player1.getOxen();
                            foodLeft = player1.getFood();
                            wagonLeft = player1.getWagon();
                            player1.setOxen(oxenLeft - 1);
                            player1.setFood(foodLeft - 10);
                            player1.setWagon(wagonLeft - 1);
                            break;
                        
                        case 2:
                            cout << "YOU MUST SOLVE A PUZZLE TO BEAT THE RAIDERS." << endl;
                            puzzleCounter = 3;
                                            puzzleRandom = 10 * ((double)rand() / (double)RAND_MAX);

                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE THREE GUESSES." << endl;
                                            cin >> puzzleGuess;
                                            
                                            if (puzzleRandom == puzzleGuess)
                                                {
                                                    cout << "YOU BEAT THE RAIDERS." << endl;
                                                    huntingFood = player1.getFood();
                                                    player1.setFood(huntingFood + 50);
                                                    huntingBullets = player1.getBullets();
                                                    player1.setBullets(huntingBullets + 50);
                                                }
                                            else
                                                {
                                                    cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE TWO GUESSES." << endl;
                                                    cin >> puzzleGuess;

                                                    if (puzzleRandom == puzzleGuess)
                                                        {
                                                            cout << "YOU BEAT THE RAIDERS." << endl;
                                                            huntingFood = player1.getFood();
                                                            player1.setFood(huntingFood + 50);
                                                            huntingBullets = player1.getBullets();
                                                            player1.setBullets(huntingBullets + 50);
                                                        }
                                                    else
                                                        {
                                                            cout << "TRY TO GUESS A NUMBER BETWEEN 0 AND 10. YOU HAVE ONE GUESS." << endl;
                                                            cin >> puzzleGuess;
                                                        
                                                            if (puzzleRandom == puzzleGuess)
                                                                {
                                                                    cout << "YOU BEAT THE RAIDERS." << endl;
                                                                    huntingFood = player1.getFood();
                                                                    player1.setFood(huntingFood + 50);
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets + 50);
                                                                }
                                                            else
                                                                {
                                                                    cout << "YOU FAILED TO BEAT THE RAIDERS." << endl;
                                                                    moneyLeft = player1.getMoney();
                                                                    player1.setMoney(moneyLeft * 0.75); // lose quarter of money
                                                                    huntingBullets = player1.getBullets();
                                                                    player1.setBullets(huntingBullets - 50); // lose 50 bullets
                                                                }
                                                        }
                                break;
                        case 3:
                            cout << "YOU SURRENDERED TO THE RAIDERS." << endl;
                            moneyLeft = player1.getMoney();
                            player1.setMoney(moneyLeft * 0.75);// lose quarter of money
                            break;
                    }
            }
        }
            
        


    } while (player1.getLocation() < 2040 && player1.getOxen() > 0 && player1.getFood() > 0 && player1.getLiving() == true && player1.getWagonHealth() == true);  // checks that aplyer  is alive and has more then 0 for all stats and wagon is not broken

    if (player1.getFood() < 0)
        {
            player1.setFood(0);
        }


    cout << "GAME OVER" << endl << endl;

    cout << "STATS:" << endl;
    cout << "* " << player1.getPlayerName() << endl;
    cout << "* " << player1.getLocation() << " MILES TRAVELED" << endl;
    cout << "* " << player1.getFood() << " POUNDS OF FOOD REMAINING" << endl;
    cout << "* " << player1.getMoney() << " DOLLARS REMAINING" << endl;

    
    ofstream out_file;
    out_file.open("results.txt"); // prints stats to txt file

    date1.switchOverMonth();
    date1.setDayOfWeek();
    out_file << date1.getDayOfWeek() << " " << date1.getMonth() << " " << date1.getDay() << " " << date1.getYear() << endl << endl;
    out_file << "TOTAL MILEAGE IS " << player1.getLocation() << endl;
    out_file << "MILEAGE UNTIL NEXT MILESTONE IS " << (milestones[milestoneCounter].getMilestoneLength() - player1.getLocation()) << endl;
    out_file << "OXEN      FOOD      BULLETS      WAGON PARTS      MEDICAL AID      MONEY"<< endl;
    out_file << player1.getOxen() << "          " << player1.getFood() << "         " << player1.getBullets() << "             " << player1.getWagon() << "            " << player1.getMedical() << "                " << player1.getMoney() << endl;

    out_file.close();
    return 0;
}