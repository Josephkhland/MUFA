#include "pch.h"
#include "happening.h"


happening::happening(int id0, string message0, int maxStage0, bool stageToIncrease0, vector<pair<int, string>>choicesList, vector<vector<string>>itemsPerChoice0, vector<pair<string, int>>statEffects,vector<pair<int,string>>prof)
{
	id = id0;
	message = message0;
	maxStage = maxStage0;
	stageToIncrease = stageToIncrease0;
	int choicesSize = choicesList.size();
	for (int i = 0; i < choicesSize; i++) choices.push_back(choicesList[i]);
	int size0 = itemsPerChoice0.size();
	for (int j = 0; j < size0; j++)
	{
		int size1 =itemsPerChoice0[j].size();
		vector<string> itemListRandomNameBecauseIcan;
		for (int k = 0; k < size1; k++)
		{
			itemListRandomNameBecauseIcan.push_back(itemsPerChoice0[j][k]);
		}
		itemsPerChoice.push_back(itemListRandomNameBecauseIcan);
		
	}
	int statSize = statEffects.size();
	for (int i = 0; i < statSize; i++)
	{
		statsIncrease.push_back(statEffects[i]);
	}
	for (int i = 0; i < prof.size(); i++)
	{
		proficiencyToUnlock.push_back(prof[i]);
	}
}

happening::happening(happening & someRandomName)
{
	id = someRandomName.getID();
	message = someRandomName.getMessage();
	maxStage = someRandomName.getMaxStage();;
	stageToIncrease = someRandomName.doesStageUP();

	int choicesSize = someRandomName.numberOfChoices();
	for (int i = 0; i < choicesSize; i++) choices.push_back(someRandomName.getChoice(i));
	int size0 = someRandomName.numberOfItemLists();
	for (int j = 0; j < size0; j++)
	{
		int size1 = someRandomName.numberOfItems(j);
		vector<string> itemListRandomNameBecauseIcan;
		for (int k = 0; k < size1; k++)
		{
			itemListRandomNameBecauseIcan.push_back(someRandomName.getItemName(j,k));
		}
		itemsPerChoice.push_back(itemListRandomNameBecauseIcan);

	}
	int statSize =someRandomName.statsIncrease.size();
	for (int i = 0; i < statSize; i++)
	{
		statsIncrease.push_back(someRandomName.statsIncrease[i]);
	}
	statSize = someRandomName.numberProf();
	for (int i = 0; i < statSize; i++)
	{
		proficiencyToUnlock.push_back(someRandomName.getProf(i));
	}
}


happening::~happening()
{
	/*
	statsIncrease.clear();
	statsIncrease.shrink_to_fit();
	choices.clear();
	choices.shrink_to_fit();
	for (int i = 0; i < itemsPerChoice.size(); i++)
	{
		itemsPerChoice[i].clear();
		itemsPerChoice[i].shrink_to_fit();
	}
	itemsPerChoice.clear();
	itemsPerChoice.shrink_to_fit();
	*/
}

int happening::numberProf()
{
	return proficiencyToUnlock.size();
}

pair<int, string> happening::getProf(int index)
{
	return proficiencyToUnlock[index];
}

int happening::getID()
{
	return id;
}

vector<string> happening::itemsToGive(int choiceCode)
{
	

	return itemsPerChoice[choiceCode];
}

int happening::choiceEvent()
{
	// Write Message
	cout << message << endl;

	//Show choices
	for (int i = 0; i < choices.size(); i++)
	{
		cout << choices[i].first << ". " << choices[i].second << endl;
	}

	//Pick choice
	string input;
	cout << "-Type an index to choose-" << endl;
	cin >> input;
	int choiceSelected = stoi(input);

	//Return choice selected.
	return choiceSelected;
}

string happening::getMessage()
{
	return message;
}

bool happening::doesStageUP()
{
	return stageToIncrease ;
}

int happening::getMaxStage()
{
	return maxStage;
}

pair<int, string> happening::getChoice(int index)
{
	return choices[index];
}

int happening::numberOfChoices()
{
	return choices.size();
}

string happening::getItemName(int choiceIndex, int itemIndex)
{
	return itemsPerChoice[choiceIndex][itemIndex];
}

int happening::numberOfItemLists()
{
	return itemsPerChoice.size();
}

int happening::numberOfItems(int choiceIndex)
{
	return itemsPerChoice[choiceIndex].size();
}
