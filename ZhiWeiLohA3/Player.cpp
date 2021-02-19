/********************************************************
Project: Text Adventure
 Author: Loh Zhi Wei
Purpose: Player CLass Application File

**********************************************************/

#include "Player.h"

Player::Player()
{
	playerName = new string;
	playerLevel = new int;
	turnsLeft = new int;
	playerLocIndex = new int;

}


Player::Player(string name = "", int level = 0)
{
	playerName = new string(name);
	playerLevel = new int(level);
	turnsLeft = new int;
	

	if (*playerLevel == 0)
	{
		*turnsLeft = 12;
	}
	else if (*playerLevel == 1)
	{
		*turnsLeft = 15;
	}
	else
	{
		*turnsLeft = 20;
	}

	playerLocIndex = new int(2); //start at lounge
}

Player::~Player()
{
	delete playerName;
	playerName = nullptr;

	delete playerLevel;
	playerLevel = nullptr;

	delete turnsLeft;
	turnsLeft = nullptr;

	delete playerLocIndex;
	playerLocIndex = nullptr;


}


string Player::getName() { return *playerName; }
int Player::getLevel() { return *playerLevel; }
int Player::getLocIndex() { return *playerLocIndex; }
int Player::getTurnsLeft() { return *turnsLeft; }


string Player::getRank()
{
	if (*playerLevel == 0)
	{
		return "Rookie Detective";
	}
	else if (*playerLevel == 1)
	{
		return "Senior Detective";
	}
	else
	{
		return "Detective Inspector";
	}

}



void Player::changeName(string newName)
{
	*playerName = newName;
}

void Player::setLocation(int newLocation)
{
	*playerLocIndex = newLocation;
}


void Player::decreaseTurn()
{
	*turnsLeft -= 1;
}


void Player::addToInv(Item* newItem)
{
	if (inventory.size() == 5)
	{
		cout << "Your inventory is FULL!\n";
	}
	else
	{
		inventory.push_back(newItem);
		cout << newItem->getName() << " added to your inventory! \n";
	}
}

void Player::removeFromInv(Item* oldItem)
{
	bool itemFound = false;

	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == oldItem)
		{
			inventory.erase(inventory.begin() + i);
			cout << oldItem->getName() << " removed from your inventory! \n";
			itemFound = true;
		}

	 }

	if (!itemFound)
	{
		cout << oldItem->getName() << " is not in your inventory! \n";
	}


	if (inventory.size() == 0)
	{
		cout << "\nYour inventory is empty!\n";
	}
}



string Player::showInventory()
{
	string invList = "";

	if (inventory.size() == 0)
	{
		invList = "EMPTY";
		return invList;
	}


	for (int i = 0; i < inventory.size(); i++)
	{
		invList += inventory[i]->getName() + " ,";
	}

	invList.pop_back();

	return invList;

}

bool Player::checkInv(string itemName)
{
	bool itemFound = false;

	if (inventory.size() == 0)
	{
		return false;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->getName() == itemName)
		{
			return true;
		}

	}

	if (!itemFound)
	{
		return false;
	}

}