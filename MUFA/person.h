#pragma once

#include "pch.h"
#include <iostream>
#include "item.h"
#include <string>
#include <vector>

class person
{
	string name;
	//STAT VARIABLES
	int sanity;
	int vitality;
	int agility;
	int strength;
	int money;


	//AI VARIABLES
	int karmaLevel; //Determines luck and ethical level.
	int relationshipLevel; //Determines how close he is to player
	int generosity;
	int willTOLive;


	//POSSESSIONS
	vector<pair<string,bool>> itemsOwned; // string Item name, bool Possession is known?
	pair<int, string> proficiency;

	
	

public:
	person(string nameee,int sanityL, int vitalityL, int agilityL, int strengthL, int moneyL, int karma, int relation, int generosityL,int willToLive, vector<pair<string, bool>> itemss, pair<int, string> prof);
	person(person& p);
	~person();

	int dailyCheck(); //Returns about what the person should do. 0- Nothing, 1-Person should die, 2-Person should give you a random item, 3-Person should try to do mischief on you.
	
	string getName();
	int getSanity();
	void setSanity(int amount);
	void increaseSanity(int value);
	int getVitality();
	void setVitality(int amount);
	void increaseVitality(int value);
	int getAgility();
	void setAgility(int amount);
	void increaseAgility(int value);
	int getStrength();
	void setStrength(int amount);
	void increaseStrength(int value);
	int getMoney();
	void setMoney(int amount);
	void increaseMoney(int value);

	int getKarma();
	void increaseKarma(int value);
	int getRelation();
	void increaseRelation(int value);
	int getGenerosity();
	int getWill();
	void increaseWill(int value);
	void showKnownItems();
	string revealItem(int index);
	pair<int,string> getProficiency();

	int getItemsNumber();
	void giveItem(string nameItem);
	string getItem(int index);
	bool getItem(string nameItem);

	void printPerson();
};

