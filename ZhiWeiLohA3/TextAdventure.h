/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Main Header File

**********************************************************/

#ifndef TEXTADVENTURE_H
#define TEXTADVENTURE_H

#include "Player.h"
#include "Suspect.h"
#include "Location.h"
#include "Item.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
using namespace std;

//basic functions
void waitForUser();
string askForString(string question);
void createList(vector<string>& listName, string fileName, unsigned listSize);

//display functions
void displayTitle();
void displayText(string myFileName);
void displayGameStats();
void displayMainMenu();
void displayArt(string myFileName);

//command processors
void askCommand();
void mainCommandprocessor(string charCommand);
void commandProcessor(string verb, string noun);
void noteProcessor();

//game setup
void initialiseGame();
void playGame();
void crackCase();
void moveSuspects();

//iterator bool functions
bool isNameSuspect(Suspect* sp);
bool isNameLocation(Location* loc);
bool isNameItem(Item* item);
bool isMurderer(Suspect* sp);
bool isCrimeScene(Location* loc);
bool isWeapon(Item* item);

//end game functions
void checkAccusation(string motive);
void isGameOver(bool win);
void clearNote();
void clearMemory();

//main game object pointers
Player* player = nullptr;
Suspect* victim = nullptr;
string murderMotive;


//game variables
int actionLeft;
int gameTurn = 1;

bool endGame = false;
bool suspectsGathered;

string noun;

string accusedWeapon;
string accusedMurderer;


//game object pointer lists
vector <Suspect*> suspectList;
vector <Location*> locationList;
vector <Item*> itemList;

#endif