/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Item CLass Header File

**********************************************************/

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item
{
private:
	string* itemName;
	string* itemDesc;
	bool* itemStatus;
	string* itemLocation;

public:
	Item();
	~Item();

	string getName();
	string getDesc();
	bool getStatus();
	string getLocation();

	void setName(string name);
	void setDesc(string desc);
	void setStatus(bool newStatus);
	void setLocation(string newLocation);

};

#endif 
