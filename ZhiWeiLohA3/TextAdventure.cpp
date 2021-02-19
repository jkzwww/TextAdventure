/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Main Application File

**********************************************************/

#include "TextAdventure.h"

int main()
{

	srand(unsigned(time(NULL)));

	initialiseGame();

	playGame();

	waitForUser();
	return 0;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Basic functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void waitForUser()
{
	system("pause");
	system("cls");
}


string askForString(string question)
{
	string answer;

	cout << "\n" << question;
	getline(cin, answer, '\n');

	return answer;
}


void createList(vector<string>& listName, string fileName, unsigned listSize)
{
	ifstream fileToRead(fileName);

	if (fileToRead.is_open())
	{
		string line = "";

		while (!fileToRead.eof() && listName.size() <= listSize)
		{
			getline(fileToRead, line, ';');
			listName.push_back(line);
		}
	}
	else
	{
		cout << "\n		File " << fileName << " not found.\n";
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Display functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void displayTitle()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t TEXT ADVENTURE \n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}


void displayText(string myFileName)
{
	ifstream fileToRead(myFileName);

	if (fileToRead.is_open())
	{
		string line = "";

		while (!fileToRead.eof())
		{
			getline(fileToRead, line, ';');
			cout << line << "\n";

		}
	}
	else
	{
		cout << "\n		File " << myFileName << " not found.\n";
	}

	waitForUser();
}


void displayArt(string myFileName)
{
	ifstream fileToRead(myFileName);

	if (fileToRead.is_open())
	{
		string line = "";

		while (!fileToRead.eof())
		{
			getline(fileToRead, line);
			cout << line << endl;

		}
	}
	else
	{
		cout << "\n		File " << myFileName << " not found.\n";
	}

}


void displayGameStats()
{
	displayTitle();

	displayMainMenu();

	cout << "\nYou are currently in the " << locationList[player->getLocIndex()]->getName() << ".\n";

	cout << locationList[player->getLocIndex()]->getDesc() << endl;

	string artFile = locationList[player->getLocIndex()]->getName() + ".txt";

	displayArt(artFile);

	cout << "\n\nSuspects present: " << locationList[player->getLocIndex()]->getLocSuspect() << endl;

}


void displayMainMenu()
{
	cout << "Turns left: " << player->getTurnsLeft() << "\t Action left: " << actionLeft << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << " Main commands: (enter the letter in [])" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "[S] show command menu	[M] show map	[N] open note	[I] show inventory	[H] help	[Q] quit game\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialise Variables~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void initialiseGame()
{

	displayTitle();
	displayText("story.txt");
	displayText("rules.txt");
	
	displayTitle();
	cout << "\nWe've been waiting for you!\n";


	//setup player details

	string name = askForString("What is your name?");
	int playerLevel;

	do
	{
		string level = askForString("Which level do you like to play?( [0] easy [1] tricky [2] hard ) ");

		playerLevel = stoi(level);

	} while (playerLevel > 2 || playerLevel < 0);

	player = new Player(name, playerLevel);


	//set up game variables according to difficulty
	int maxLocations;
	int maxSuspects;
	int maxItems;

	if (playerLevel == 0)
	{
		maxLocations = 10;
		maxSuspects = 7;
		maxItems = 10;

		cout << "\nWelcome, our rookie detective, " << player->getName() << "!\n"; 
		cout << "Now you'll start cracking your first case!\nBest of luck!\n\n\n";
	}
	else if (playerLevel == 1)
	{
		maxLocations = 12;
		maxSuspects = 9;
		maxItems = 20;

		cout << "\nWelcome, our experienced senior detective, " << player->getName() << "!\n";
		cout << "Now you'll start cracking the case that will challenge you like never before!\nBest of luck!\n\n\n";
	}
	else
	{
		maxLocations = 16; 
		maxSuspects = 11;
		maxItems = 30;

		cout << "\nWelcome, our detective inspector aka Shelock Holmes alive, " << player->getName() << "!\n";
		cout << "Now you'll start cracking the case that will reignite your passion and burn your brain!\nBest of luck!\n\n\n";
	}
	 

	//temp suspect info lists 
	vector <string> suspectNameList;
	createList(suspectNameList, "suspectNames.txt", maxSuspects);

	vector <string> suspectDescList;
	createList(suspectDescList, "suspectDesc.txt", maxSuspects);

	vector <string> suspectConvoList;
	createList(suspectConvoList, "suspectConvo.txt", maxSuspects);

	vector <string> suspectMotiveList;
	createList(suspectMotiveList, "suspectMotives.txt", maxSuspects);

	//initialise suspects
	for (int i = 0; i < maxSuspects;i++)
	{
		Suspect* suspect = new Suspect();
		suspectList.push_back(suspect);
		suspectList[i]->setName(suspectNameList[i]);
		suspectList[i]->setDesc(suspectDescList[i]);
		suspectList[i]->setConvo(suspectConvoList[i]);
	}


	//initialise victim
	int victimIndex = rand() % maxSuspects;
	victim = suspectList[victimIndex];
	maxSuspects-=1;
	suspectList.erase(suspectList.begin() + victimIndex);
	suspectMotiveList.erase(suspectMotiveList.begin() + victimIndex);

	//initialise murderer
	int murderIndex = rand() % maxSuspects;
	suspectList[murderIndex]->setStatus(true);
	murderMotive = suspectMotiveList[murderIndex];

	//initialise alibi
	//pairs
	int alibiPairs = (maxSuspects - 2)/2;
	vector <int> innocentIndex;

	for (int i = 0; i < maxSuspects; i++)
	{
		if (i != murderIndex)
		{
			innocentIndex.push_back(i);
		}
	}

	for (int i = 0; i < alibiPairs; i++)
	{
		int suspect1 = innocentIndex[(2 * i)];
		int suspect2 = innocentIndex[(2*i)+1];
		string alibi1 = "I was with " + suspectList[suspect2]->getName() + " that day!\n";
		string alibi2 = "I was with " + suspectList[suspect1]->getName() + " that day!\n";
		
		suspectList[suspect1]->setAlibi(alibi1);
		suspectList[suspect2]->setAlibi(alibi2);
	}

	//alone suspect alibi
	int aloneIndex = innocentIndex[innocentIndex.size() - 1];
	string aloneAlibi = "I have an urgend personal matter and left the gathering early.";

	suspectList[aloneIndex]->setAlibi(aloneAlibi); 

	//murderer alibi
	int randSuspIndex = rand() % (innocentIndex.size()-1);
	string fakeAlibi = "I was with " + suspectList[innocentIndex[randSuspIndex]]->getName() + " that day!\n";

	suspectList[murderIndex]->setAlibi(fakeAlibi);

	//temp location info list
	vector <string> locNameList;
	createList(locNameList, "locationNames.txt", maxLocations);

	vector <string> locDescList;
	createList(locDescList, "locationDesc.txt", maxLocations);

	//initialise locations
	for (int i = 0; i < maxLocations; i++)
	{
		Location* location = new Location();
		locationList.push_back(location);

		locationList[i]->setName(locNameList[i]);
		locationList[i]->setDesc(locDescList[i]);
	}

	//add suspects to location
	for (int i = 0; i < maxSuspects; i++)
	{
		int randLocIndex = rand() % maxLocations;

		while (locationList[randLocIndex]->getNumSusp() >= 2) 
		{ 
			randLocIndex++;

			if (randLocIndex > maxLocations - 1)
			{
				randLocIndex = 0;
			}
		}

		locationList[randLocIndex]->addLocSuspect(suspectList[i]);
		suspectList[i]->changeLocation(locationList[randLocIndex]->getName());

	}

	//initialise crime scene
	int randCrimeIndex = rand() % maxLocations;
	locationList[randCrimeIndex]->setStatus(true);


	//temp item info list

	int firstItems;

	if (playerLevel == 0)
	{
		firstItems = 10;
	}
	else if (playerLevel == 1)
	{
		firstItems = 12;
	}
	else
	{
		firstItems = 16;
	}

	vector <string> itemName1;
	createList(itemName1, "item1Names.txt", firstItems);

	vector <string> itemDesc1;
	createList(itemDesc1, "item1Desc.txt", firstItems);

	//initialise first batch item
	for (int i = 0; i < firstItems; i++)
	{
		Item* item = new Item();
		itemList.push_back(item);

		itemList[i]->setName(itemName1[i]);
		itemList[i]->setDesc(itemDesc1[i]);
		
		locationList[i]->addLocItem(itemList[i]);
		itemList[i]->setLocation(locationList[i]->getName());
	}


	//second batch

	if (playerLevel != 0)
	{
		int secondItems = maxItems - firstItems;
		
		vector <string> itemName2;
		createList(itemName2, "item2Names.txt", secondItems);

		vector <string> itemDesc2;
		createList(itemDesc2, "item2Desc.txt", secondItems);

		//initialise second batch items

		for (int i = 0; i < secondItems; i++)
		{
			Item* item = new Item();
			itemList.push_back(item);

			int j = firstItems + i;

			itemList[j]->setName(itemName2[i]);
			itemList[j]->setDesc(itemDesc2[i]);

			locationList[i]->addLocItem(itemList[j]);
			itemList[j]->setLocation(locationList[i]->getName());
		}

	}

	//initialise murder weapon
	int randWeaponIndex = rand() % maxItems;
	string weaponDesc = "Eww,this thing is bloodied!!!";
	itemList[randWeaponIndex]->setDesc(weaponDesc);
	itemList[randWeaponIndex]->setStatus(true);


	waitForUser();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Process Commands~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void askCommand()
{
	string commandString;
	string verb = "";
	noun = "";

	cout << "\n\nEnter command: ";

	getline(cin,commandString , '\n');

	if (commandString.length() < 2)
	{
		//main commands
		mainCommandprocessor(commandString);
	}
	else
	{
		bool nextWord = false;

		for (unsigned i = 0; i < commandString.length(); i++)
		{
			if (commandString[i] == ' ')
			{
				nextWord = true;
			}

			if (nextWord)
			{
				noun += commandString[i];
			}
			else
			{
				verb += commandString[i];
			}
		}

		noun = noun.erase(0,1);

		commandProcessor(verb, noun);
	}

}


void mainCommandprocessor(string charCommand)
{
	if (charCommand == "Q" || charCommand == "q")
	{
		endGame = true;
	}
	else if (charCommand == "S" || charCommand == "s")
	{
		displayText("commandMenu.txt");
	}
	else if (charCommand == "M" || charCommand == "m")
	{
		if (player->getLevel() == 0)
		{
			displayArt("map0.txt");
		}
		else if (player->getLevel() == 1)
		{
			displayArt("map1.txt");
		}
		else
		{
			displayArt("map2.txt");
		}
		waitForUser();
	}
	else if (charCommand == "N" || charCommand == "n")
	{
		noteProcessor();
	}
	else if (charCommand == "I" || charCommand == "i")
	{
		cout << "\nYour inventory: " << player->showInventory() << endl;
		waitForUser();
	}
	else if (charCommand == "H" || charCommand == "h")
	{
		displayText("rules.txt");
	}
	else if (charCommand == "G" || charCommand == "g")
	{
		suspectsGathered = true;

		string playerLocName = locationList[player->getLocIndex()]->getName();

		//remove all suspects from locations
		for (unsigned i = 0; i < locationList.size(); i++)
		{
			locationList[i]->removeLocSuspect();
		}

		//update suspect location and  move them to player location
		for (unsigned i = 0; i < suspectList.size(); i++)
		{
			suspectList[i]->changeLocation(playerLocName);
			locationList[player->getLocIndex()]->addLocSuspect(suspectList[i]);
		}

		waitForUser();

		crackCase();
	}
	else
	{
		cout << "\nInvalid input!!!\n";
		waitForUser();
	}
}


//iterator functions
bool isNameSuspect(Suspect* sp){ return (sp->getName() == noun); }
bool isNameLocation(Location* loc) { return (loc->getName() == noun); }
bool isNameItem(Item* item) { return (item->getName() == noun); }


void commandProcessor(string verb, string noun)
{
	bool invalidInput = false;

	if (verb == "go")
	{
		vector<Location*>::iterator itLoc = find_if(locationList.begin(), locationList.end(), isNameLocation);
		
		if (itLoc != locationList.end())
		{
			int locIndex = distance(locationList.begin(), itLoc);
			player->setLocation(locIndex);
		}
		else
		{
			cout << "\nInvalid Location!!\n";
			invalidInput = true;
		}

	}
	else if (verb == "search")
	{
		vector<Location*>::iterator itLoc = find_if(locationList.begin(), locationList.end(), isNameLocation);
		int locIndex = distance(locationList.begin(), itLoc);

		//check if player is in that location
		if (player->getLocIndex() == locIndex)
		{
			//check whether location is crime scene
			if (locationList[locIndex]->getStatus())
			{
				string crimeSceneDesc = "\nOh no, there is blood spattered all over this room!\n";
				cout << crimeSceneDesc;
			}

			
			cout << "Items found: " << locationList[locIndex]->getLocItem() << endl;
		}
		else
		{
			cout << "\nYou must go to that room in order to search! \n";
			invalidInput = true;
		}
	
	}
	else if (verb == "use")
	{
		vector<Item*>::iterator itItem = find_if(itemList.begin(), itemList.end(), isNameItem);
		if (itItem != itemList.end())
		{
			string itemName = (*itItem)->getName();

			if (player->checkInv(itemName))
			{
				accusedWeapon = itemName;
			}
			else
			{
				cout << itemName << " is not in your inventory! \n";
				invalidInput = true;
			}
		}
		else
		{
			cout << "\nInvalid Item!!\n";
			invalidInput = true;
		}
	}
	else if (verb == "drop")
	{
		vector<Item*>::iterator itItem = find_if(itemList.begin(), itemList.end(), isNameItem);
		if (itItem != itemList.end())
		{
			player->removeFromInv(*itItem);
			locationList[player->getLocIndex()]->addLocItem(*itItem);
			(*itItem)->setLocation(locationList[player->getLocIndex()]->getName());
		}
		else
		{
			cout << "\nInvalid Item!!\n";
			invalidInput = true;
		}
	}
	else if (verb == "get")
	{
		vector<Item*>::iterator itItem = find_if(itemList.begin(), itemList.end(), isNameItem);
		if (itItem != itemList.end())
		{
	
			int playerLoc = player->getLocIndex();

			if ((*itItem)->getLocation() == locationList[playerLoc]->getName())
			{

					player->addToInv((*itItem));
					if (player->checkInv((*itItem)->getName()))
					{
						locationList[playerLoc]->removeLocItem((*itItem));
					}
					(*itItem)->setLocation("Inventory");
				
			}
			else
			{
				cout << "\nItem is not present in your current location!\n\n";
				invalidInput = true;
			}
		}
		else
		{
			cout << "\nInvalid Item!!\n";
			invalidInput = true;
		}
	}
	else if (verb == "examine")
	{
		vector<Item*>::iterator itItem = find_if(itemList.begin(), itemList.end(), isNameItem);
		if (itItem != itemList.end())
		{
			int playerLoc = player->getLocIndex();

			if ((*itItem)->getLocation() == locationList[playerLoc]->getName() || (*itItem)->getLocation() == "Inventory")
			{
				cout << (*itItem)->getDesc() << "\n\n";
			}
			else
			{
				cout << "\nItem is not present in your current location!\n\n";
				invalidInput = true;
			}

		}
		else
		{
			cout << "\nInvalid Item!!\n";
			invalidInput = true;
		}

	}
	else if (verb == "question" || verb == "chat")
	{
		vector<Suspect*>::iterator itSusp = find_if(suspectList.begin(), suspectList.end(), isNameSuspect);

		if (itSusp != suspectList.end())
		{
			int playerLoc = player->getLocIndex();
			if ((*itSusp)->getLocation() == locationList[playerLoc]->getName())
			{
				if (verb == "question")
				{
					cout << (*itSusp)->getDesc() << endl;
					cout << (*itSusp)->getAlibi() << "\n\n";
				}
				else
				{
					cout << (*itSusp)->getConvo() << "\n\n";
				}
			}
			else
			{
				cout << "\nSuspect is not present in your current location!\n\n";
				invalidInput = true;
			}
		}
		else
		{
			cout << "\nInvalid Name!!\n";
			invalidInput = true;
		}
	}
	else if (verb == "accuse")
	{
		vector<Suspect*>::iterator itSusp = find_if(suspectList.begin(), suspectList.end(), isNameSuspect);

		if (itSusp != suspectList.end())
		{
			if (suspectsGathered)
			{
				accusedMurderer = (*itSusp)->getName();
			}
			else
			{
				cout << "\nYou must gather suspects to the crime scene first to accuse the murderer!\n";
				invalidInput = true;
			}
		}
		else
		{
			cout << "\nInvalid Name!!\n";
			invalidInput = true;
		}


    }
	else if (verb == "gather")
	{
		suspectsGathered = true;

		string playerLocName = locationList[player->getLocIndex()]->getName();

		//remove all suspects from locations
		for (unsigned i = 0; i < locationList.size(); i++)
		{
			locationList[i]->removeLocSuspect();
		}

		//update suspect location and  move them to player location
		for (unsigned i = 0; i < suspectList.size(); i++)
		{
			suspectList[i]->changeLocation(playerLocName);
			locationList[player->getLocIndex()]->addLocSuspect(suspectList[i]);
		}

		waitForUser();

		crackCase();

	}
	else
	{
		cout << "\nInvalid command input!\n";
		invalidInput = true;
    }


	if (!invalidInput) { actionLeft--; }

	if (actionLeft == 0)
	{
		player->decreaseTurn();
		gameTurn++;
		actionLeft = 5;
	}

	waitForUser();
}


void noteProcessor()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "[R] read notes			[W] write notes			[C] clear notes			[B] back\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	string noteCommand = "";

	cout << "Enter command: ";
	getline(cin, noteCommand, '\n');
	
	if (noteCommand == "R" || noteCommand == "r")
	{
		displayText("playerNote.txt");
	}
	else if (noteCommand == "W" || noteCommand == "w")
	{
		string noteWritten;
		cout << "\nWrite your note here, press enter when finish: ";
		getline(cin, noteWritten, '\n');

		ofstream fileToWrite;
		fileToWrite.open("playerNote.txt",ios::out | ios::app);

		if (fileToWrite.is_open()) 
		{
			fileToWrite << ";" << noteWritten;
			
			fileToWrite.close();
		}
		else { cout << "Unable to open file"; }
		
		waitForUser();
	}
	else if (noteCommand == "C" || noteCommand == "c")
	{
		clearNote();
		cout << "Note cleared.\n";
		waitForUser();
	}
	else if (noteCommand == "B" || noteCommand == "b")
	{
		waitForUser();
	}
	else
	{
		cout << "\n invalid input!! \n";
		waitForUser();
	}

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Game settings~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void playGame()
{
	actionLeft = 5;

	while (!endGame && player->getTurnsLeft() != 0)
	{
		displayGameStats();

		if (gameTurn % 7 == 0 && actionLeft == 5)
		{
			moveSuspects();

			cout << "\nThe suspects have moved around the mansion!\n\n";
		}

		askCommand();
	}

	if (player->getTurnsLeft() == 0)
	{
		cout << "\nOh no... You've run out of turns!\n";
		cout << "You've spent too much time cracking the case and the killer ran away!\n\n";
		displayArt("gameOverKnife.txt");
	}

	clearNote();

	cout << "\n" << player->getRank() << " " << player->getName() << ",\n";

	cout << "Thanks for playing with us!!!\n\n";

	clearMemory();
}


void crackCase()
{

	cout << "\nHere is your notes for last review,\n" << "please remember the weapon name,suspect name and suspect motive for later accusation. \n";

	displayText("playerNote.txt");

	cout << "\n\nYou have gathered everyone to " << locationList[player->getLocIndex()]->getName() << ".\n";
	
	cout << "This should be the location where you think " << victim->getName() << " is killed.\n";

	cout << "Now, show the bloodied weapon you've collected by typing \"use Itemname\".\n ";

	askCommand();

	cout << "Everyone is horrified and uneasy. Have you identified the killer?\n";

	cout << "Accuse him or her by typing in \"accuse Suspectname\".\n";

	askCommand();

	cout << accusedMurderer << " denied, please tell everyone what is the murderer's motive!\n";

	cout << "[1] Money   [2] Relationship issues   [3] Revenge   [4] Self Defense   [5]Hate \n";

	string motive = askForString("Please enter your guess: ");

	checkAccusation(motive);

}


void moveSuspects()
{
	for (unsigned i = 0; i < locationList.size(); i++)
	{
		locationList[i]->removeLocSuspect();
	}

	for (unsigned i = 0; i < suspectList.size(); i++)
	{
		unsigned randLocIndex = rand() % locationList.size();

		while (locationList[randLocIndex]->getNumSusp() >= 2)
		{
			randLocIndex++;

			if (randLocIndex > locationList.size() - 1)
			{
				randLocIndex = 0;
			}
		}

		locationList[randLocIndex]->addLocSuspect(suspectList[i]);
		suspectList[i]->changeLocation(locationList[randLocIndex]->getName());

	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Game~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void checkAccusation(string motive)
{
	string motiveName;

	switch (stoi(motive))
	{
		case 1:
			motiveName = " because of money.";
			break;
		case 2:
			motiveName = " because of relationship issues.";
			break;
		case 3:
			motiveName = " to revenge.";
			break;
		case 4:
			motiveName = " for self-defense.";
			break;
		case 5:
			motiveName =  " due to hatred.";
			break;
	default:
		motiveName = " ";
		break;
	}

	string playerLocName = locationList[player->getLocIndex()]->getName();
	
	cout << "\nYou have claimed that:\n\n";

	cout << accusedMurderer << " killed " << victim->getName() << motiveName << endl;

	cout << "The murder happened at the " << playerLocName << " of the rented mansion." << endl;

	cout << "The weapon " << accusedWeapon << " is collected as evidence.\n\n";

	string trueMotive;

	switch (stoi(murderMotive))
	{
	case 1:
		trueMotive = " because of money.";
		break;
	case 2:
		trueMotive = " because of relationship issues.";
		break;
	case 3:
		trueMotive = " to revenge.";
		break;
	case 4:
		trueMotive = " for self-defense.";
		break;
	case 5:
		trueMotive = " due to hatred.";
		break;
	default:
		trueMotive = " ";
		break;
	}

	vector<Suspect*>::iterator itSusp = find_if(suspectList.begin(), suspectList.end(), isMurderer);
	vector<Item*>::iterator itItem = find_if(itemList.begin(), itemList.end(), isWeapon);
	vector<Location*>::iterator itLoc = find_if(locationList.begin(), locationList.end(), isCrimeScene);


	cout << "\nThe truth is:\n\n";

	cout << (*itSusp)->getName() << " killed " << victim->getName() << trueMotive << endl;

	cout << "The murder happened at the " << (*itLoc)->getName() << " of the rented mansion." << endl;

	cout << "The weapon used was " << (*itItem)->getName() << ".\n\n";

	waitForUser();

	bool checkMurderer = ((*itSusp)->getName() == accusedMurderer);
	bool checkWeapon = ((*itItem)->getName() == accusedWeapon);
	bool checkLocation = ((*itLoc)->getName() == playerLocName);
	bool checkMotive = (murderMotive == motive);

	if (checkMurderer && checkWeapon && checkLocation && checkMotive)
	{
		isGameOver(true);
	}
	else
	{
		isGameOver(false);
	}


}


//iterator functions
bool isMurderer(Suspect* sp) { return sp->getStatus(); }
bool isCrimeScene(Location* loc) { return loc->getStatus(); }
bool isWeapon(Item* item) { return item->getStatus(); }


void isGameOver(bool win)
{
	displayTitle();

	if (win)
	{
		cout << "\n\nCongratulations, " << player->getName() << " !!You have cracked the case sucessfully!!!\n\n";
		displayArt("fireworks.txt");
	}
	else
	{
		cout << "\n\nToo bad...You did not solve the case and the killer ran away...\n\n";
		displayArt("gameOverKnife.txt");
	}

	endGame = true;
}


void clearNote()
{
	//clear note
	ofstream fileToWrite;
	fileToWrite.open("playerNote.txt", ios::out | ios::trunc);

	if (fileToWrite.is_open())
	{
		fileToWrite << ";";

		fileToWrite.close();
	}
	else { cout << "Unable to open file"; }
}


void clearMemory()
{
	for (unsigned i = 0; i < suspectList.size(); i++)
	{
		delete suspectList[i];
		suspectList[i] = nullptr;
	}

	for (unsigned i = 0; i < itemList.size(); i++)
	{
		delete itemList[i];
		itemList[i] = nullptr;
	}

	for (unsigned i = 0; i < locationList.size(); i++)
	{
		delete locationList[i];
		locationList[i] = nullptr;
	}

	delete player;
	player = nullptr;

	delete victim;
	victim = nullptr;
}