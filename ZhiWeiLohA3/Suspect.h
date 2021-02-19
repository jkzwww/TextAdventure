/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Suspect CLass Header File

**********************************************************/

#ifndef SUSPECT_H
#define SUSPECT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Suspect
{
public:
	Suspect();
	~Suspect();

	string getName();
	string getDesc();
	bool getStatus();
	string getAlibi();
	string getConvo();
	string getLocation();
	
	void setName(string suspName);
	void setDesc(string suspDesc);
	void setAlibi(string suspAlibi);
	void setStatus(bool newStatus);
	void setConvo(string convo);
	void changeLocation(string newLocation);

private:

	string* suspectName;
	string* suspectDesc;
	bool* suspectStatus;
	string* alibi;
	string* conversation;
	string* location;

};

#endif
