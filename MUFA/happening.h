#pragma once
#include "item.h"


class happening
{
private:
	int id;
	vector<pair<int, string>> proficiencyToUnlock;
	vector<pair<int,string>> choices;
	vector<vector<string>> itemsPerChoice;
	
	string message;
	bool stageToIncrease;
	int maxStage;

public:
	happening(int id0, string message, int maxStage,bool stageToIncrease, vector<pair<int,string>>choicesList,vector<vector<string>>itemsPerChoice,vector<pair<string,int>>statEffects,vector<pair<int,string>>prof);
	happening(happening& someRandomName);
	~happening();

	vector < pair<string, int>> statsIncrease;

	int numberProf();
	pair<int, string> getProf(int index);
	int getID();
	vector<string> itemsToGive(int choiceCode);
	int choiceEvent();
	string getMessage();
	bool doesStageUP();
	int getMaxStage();
	pair<int, string> getChoice(int index);
	int numberOfChoices();
	string getItemName(int choiceIndex, int itemIndex);
	int numberOfItemLists();
	int numberOfItems(int choiceIndex);

};

