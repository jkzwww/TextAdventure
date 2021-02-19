/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Location CLass Header File

**********************************************************/

#ifndef LOCATION_H
#define LOCATION_H

#include "Suspect.h"
#include "Item.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Location {

private:
	string* locName;
	string* locDesc;
	vector <Suspect*> locSuspect;
	vector <Item*> locItem;
	bool* status;

public:
	Location();
	~Location();

	string getName();
	string getDesc();
	string getLocSuspect();
	int getNumSusp();
	string getLocItem();
	bool getStatus();

	void setName(string newName);
	void setDesc(string newDesc);
	void setStatus(bool newStatus);
	void addLocSuspect(Suspect* newSuspect);
	void removeLocSuspect();
	void addLocItem(Item* newItem);
	void removeLocItem(Item* oldItem);
};


#endif
