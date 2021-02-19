/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Item CLass Application File

**********************************************************/

#include "Item.h"

Item::Item()
{
	itemName = new string;
	itemDesc = new string;
	itemStatus = new bool(false);
	itemLocation = new string;
}

Item::~Item()
{
	delete itemName;
	itemName = nullptr;

	delete itemDesc;
	itemDesc = nullptr;

	delete itemStatus;
	itemStatus = nullptr;

	delete itemLocation;
	itemLocation = nullptr;
}

string Item::getName() { return *itemName; }
string Item::getDesc() { return *itemDesc; }
bool Item::getStatus() { return *itemStatus; }
string Item::getLocation() { return *itemLocation; }

void Item::setName(string name)
{
	*itemName = name;
}

void Item::setDesc(string desc)
{
	*itemDesc = desc;
}

void Item::setStatus(bool newStatus)
{
	*itemStatus = newStatus;
}

void Item::setLocation(string newLocation)
{
	*itemLocation = newLocation;
}