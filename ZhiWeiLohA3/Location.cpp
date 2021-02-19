/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Location CLass Application File

**********************************************************/

#include "Location.h"

Location::Location()
{
	locName = new string;
	locDesc = new string;
	status = new bool(false);
}

Location::~Location()
{
	delete locName;
	locName = nullptr;

	delete locDesc;
	locDesc = nullptr;

	delete status;
	status = nullptr;


}


string Location::getName() { return *locName; }
string Location::getDesc() { return *locDesc; }
int Location::getNumSusp() { return locSuspect.size(); }
bool Location::getStatus() { return *status; }

string Location::getLocSuspect()
{
	string locSuspectInfo = " ";

	for (int i = 0; i < locSuspect.size(); i++)
	{
		locSuspectInfo += locSuspect[i]->getName() + " ,";
	}

	locSuspectInfo.pop_back();

	if (locSuspect.size() == 0)
	{
		locSuspectInfo += "NONE";
	}

	return locSuspectInfo;
}



string Location::getLocItem()
{
	string locItemInfo = " ";

	for(int i = 0; i < locItem.size(); i++)
	{
		locItemInfo += locItem[i]->getName() + " ,";
	}

	locItemInfo.pop_back();

	return locItemInfo;
}


void Location::setName(string newName) { *locName = newName; }
void Location::setDesc(string newDesc) { *locDesc = newDesc; }
void Location::setStatus(bool newStatus) { *status = newStatus; }

void Location::addLocSuspect(Suspect* newSuspect)
{
	locSuspect.push_back(newSuspect);
}

void Location::removeLocSuspect()
{
	locSuspect.erase(locSuspect.begin(), locSuspect.end());
}


void Location::addLocItem(Item* newItem)
{
	locItem.push_back(newItem);
}


void Location::removeLocItem(Item* oldItem)
{
	for (int i = 0; i < locItem.size(); i++)
	{
		if (locItem[i] == oldItem)
		{
			locItem.erase(locItem.begin() + i);
		}

	}
}