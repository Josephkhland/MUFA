#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
class item
{
private:
	string name;
	string description;
	string USED_Name;
	int Price;
	int progressVariable; // 0 if none, determines which progress variable to change.

	map<string, vector<int>> itemStats; // statname [effect, prerequisite]
	//Main Stats: sanity, vitality, agility, strength,
	//More Stats: literature, science, medicine, esoteric, fame, art, martial, karma.
	
	bool isUsed;
	bool consumedOnUse;

	int stageRequirement;


public:
	item(string Name, string desc, string usedName,int stageReq, int price,int progressVar,bool consumable, vector<int> stats, bool used=false);
	~item();

	item(item& i);
	string getName();
	string getUsedName();
	string getDesc();
	
	int getStage();
	int getPrice();
	void setUsed();
	int getStat(string statName);
	int getPreq(string statName);
	int getProgressVar();

	bool getIsUsed();
	bool isConsumable();
	bool canBuy(int money);
	bool canUse(int uSanity, int uVitality, int uAgility, int uStrength, int uLiterature, int uScience, int uMedicine, int uEsoteric, int uFame, int uArt, int uMartial, int uKarma);
};

