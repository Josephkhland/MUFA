#pragma once
#include "pch.h"
#include "person.h"
#include <string>
#include <vector>


person::person(string namee,int sanityL, int vitalityL, int agilityL, int strengthL, int moneyL, int karma, int relation, int generosityL, int will, vector<pair<string,bool>> itemss,pair<int,string> prof)
{
	name = namee;
	sanity = sanityL;
	vitality = vitalityL;
	agility = agilityL;
	strength = strengthL;
	money = moneyL;

	karmaLevel = karma;
	relationshipLevel = relation;
	generosity = generosityL;
	willTOLive = will;
	for (int i=0; i < itemss.size(); i++) itemsOwned.push_back(itemss[i]);
	proficiency = prof;

}

person::person(person & p)
{
	name = p.getName();
	sanity = p.getSanity();
	vitality = p.getVitality();
	agility = p.getAgility();
	strength = p.getStrength();
	money = p.getMoney();

	karmaLevel = p.getKarma();
	relationshipLevel = p.getRelation();
	generosity = p.getGenerosity();
	willTOLive = p.getWill();

	for (int i = 0; i < p.getItemsNumber(); i++)
	{
		itemsOwned.push_back(pair<string, bool>(p.getItem(i), false));
	}
	proficiency = p.getProficiency();
}


person::~person()
{
}

int person::dailyCheck()
{
	int randChangePLUS = rand() % 4;
	int randChangeMINUS = rand() % 4;
	if (rand() + 1 > willTOLive)
	{
		if (willTOLive != 0)
		
{
			willTOLive -= 1;
			if (sanity <= vitality)
			{
				if (sanity <= strength)
				{
					if (sanity <= agility)
					{
						randChangePLUS = 0;
					}
					else
					{
						randChangePLUS = 2;
					}
				}
				else
				{
					if (strength <= agility)
					{
						randChangePLUS = 3;
					}
					else
					{
						randChangePLUS = 2;
					}
				}
			}
			else
			{
				if (vitality <= strength)
				{
					if (vitality <= agility)
					{
						randChangePLUS = 1;
					}
					else
					{
						randChangePLUS = 2;
					}
				}
				else
				{
					if (strength <= agility)
					{
						randChangePLUS = 3;
					}
					else
					{
						randChangePLUS = 2;
					}
				}
			}
		}
	}
	else
	{
		if (sanity <= vitality)
		{
			if (sanity <= strength)
			{
				if (sanity <= agility)
				{
					randChangePLUS = 0;
				}
				else
				{
					randChangePLUS = 2;
				}
			}
			else
			{
				if (strength <= agility)
				{
					randChangePLUS = 3;
				}
				else
				{
					randChangePLUS = 2;
				}
			}
		}
		else
		{
			if (vitality <= strength)
			{
				if (vitality <= agility)
				{
					randChangePLUS = 1;
				}
				else
				{
					randChangePLUS = 2;
				}
			}
			else
			{
				if (strength <= agility)
				{
					randChangePLUS = 3;
				}
				else
				{
					randChangePLUS = 2;
				}
			}
		}
	}
	switch (randChangePLUS) {
		case 0:
			sanity += 1;
			break;
		case 1:
			vitality += 1;
			break;
		case 2:
			agility += 1;
			break;
		case 3:
			strength += 1;
	}
	switch (randChangeMINUS) {
	case 0:
		sanity -= 1;
		break;
	case 1:
		vitality -= 1;
		break;
	case 2:
		agility -= 1;
		break;
	case 3:
		strength -= 1;
	}
	if (sanity <= 0 || vitality <= 0 || agility <= 0 || strength <= 0)
	{
		return 1;
	}

	if (relationshipLevel + rand() % 20 >= generosity)
	{
		return 2;
	}
	return 0;
}

string person::getName()
{
	return name;
}

int person::getSanity()
{
	return sanity;
}

void person::setSanity(int amount)
{
	sanity = amount;
}

void person::increaseSanity(int value)
{
	sanity += value;
}



int person::getVitality()
{
	return vitality;
}

void person::setVitality(int amount)
{
	vitality = amount;
}

void person::increaseVitality(int value)
{
	vitality += value;
}

int person::getAgility()
{
	return agility;
}

void person::setAgility(int amount)
{
	agility = amount;
}

void person::increaseAgility(int value)
{
	agility += value;
}

int person::getStrength()
{
	return strength;
}

void person::setStrength(int amount)
{
	strength = amount;
}

void person::increaseStrength(int value)
{
	strength += value;
}

int person::getMoney()
{
	return money;
}

void person::setMoney(int amount)
{
	money = amount;
}

void person::increaseMoney(int value)
{
	if (money + value < 0) money = 0;
	else money += value;
}

int person::getKarma()
{
	return karmaLevel;
}

void person::increaseKarma(int value)
{
	karmaLevel += value;
}

int person::getRelation()
{
	return relationshipLevel;
}

void person::increaseRelation(int value)
{
	relationshipLevel += value;
}

int person::getGenerosity()
{
	return generosity;
}

int person::getWill()
{
	return willTOLive;
}

void person::increaseWill(int value)
{
	willTOLive += value;
}

void person::showKnownItems()
{
	int counter = 0;
	for (int i = 0; i < itemsOwned.size(); i++)
	{
		
		if (itemsOwned[i].second == true)
		{
			cout << counter << ". " << itemsOwned[i].first << endl;
		}
		counter++;
	}
}

string person::revealItem(int index)
{
	itemsOwned[index].second = true;
	return itemsOwned[index].first;
}

pair<int, string> person::getProficiency()
{
	return proficiency;
}

int person::getItemsNumber()
{
	return itemsOwned.size();
}

void person::giveItem(string nameItem)
{
	itemsOwned.push_back(pair<string,int>(nameItem,true));
}

string person::getItem(int index)
{
	return itemsOwned[index].first;
}

bool person::getItem(string nameItem)
{
	int extremelyEpicLocalVariableWithAnUnnecessarilyLongAssName = itemsOwned.size();
	for (int i = 0; i < extremelyEpicLocalVariableWithAnUnnecessarilyLongAssName; i++)
	{
		if (itemsOwned[i].first == nameItem)
		{
			itemsOwned.erase(itemsOwned.begin() + i);
			return true;

		}
	}
	return false;
}

void person::printPerson()
{
	cout << "##################" << endl;
	cout << name << ", the " << proficiency.second << endl;
	cout << endl;
	cout << "Sanity: " << sanity << endl;
	cout << "Vitality: " << vitality << endl;
	cout << "Agility: " << agility << endl;
	cout << "Strength: " << strength << endl;
	cout << endl;
	cout << "Possessions: " << endl;
	cout << "Money: " << money << endl;
	cout << endl;
	showKnownItems();
	cout << endl;
	cout << "##################" << endl;
}
