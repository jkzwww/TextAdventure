/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Player CLass Header File

**********************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player
{
public:
	//constructor
	Player();
	Player(string name,int level);
	~Player();

	//acessor
	string getName();
	int getLevel();
	string getRank();
	int getLocIndex();
	int getTurnsLeft();


	//mutator
	void changeName(string newName);
	string showInventory();
	void addToInv(Item* newItem);
	void removeFromInv(Item* oldItem);
	void setLocation(int newLocation);
	void decreaseTurn();
	bool checkInv(string itemName);

private:
	string* playerName;
	int* playerLevel;
	int* turnsLeft;
	int* playerLocIndex;

	vector <Item*> inventory;
	
};

#endif