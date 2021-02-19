/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Suspect CLass Application File

**********************************************************/

#include "Suspect.h"

Suspect::Suspect()
{
	suspectName = new string;
	suspectDesc = new string;
	suspectStatus = new bool(false);
	alibi = new string;
	conversation = new string;
	location = new string;
}

Suspect::~Suspect()
{
	delete suspectName;
	suspectName = nullptr;

	delete suspectDesc;
	suspectStatus = nullptr;

	delete suspectStatus;
	suspectStatus = nullptr;

	delete alibi;
	alibi = nullptr;

	delete conversation;
	conversation = nullptr;

	delete location;
	location = nullptr;
}


string Suspect::getName() { return *suspectName; }
string Suspect::getDesc() { return *suspectDesc; }
bool Suspect::getStatus() { return *suspectStatus; }
string Suspect::getAlibi() { return *alibi; }
string Suspect::getConvo() { return *conversation; }
string Suspect::getLocation() { return *location; }

void Suspect::setName(string suspName) { *suspectName = suspName; }
void Suspect::setDesc(string suspDesc) { *suspectDesc = suspDesc; }
void Suspect::setAlibi(string suspAlibi) { *alibi = suspAlibi; }
void Suspect::setStatus(bool newStatus) { *suspectStatus = newStatus; }
void Suspect::setConvo(string convo) { *conversation = convo; }
void Suspect::changeLocation(string newLocation) { *location = newLocation; }







