#include "pch.h"
#include "item.h"


using namespace std;
item::item(string Name, string desc, string usedName,int stageReq, int price, int progressVar,bool consumable,vector<int> stats, bool used)
{
	name = Name;
	description = desc;
	USED_Name = usedName;
	Price = price;
	progressVariable = progressVar;
	stageRequirement = stageReq;
	consumedOnUse = consumable;
	string statNames[12] = { "sanity", "vitality", "agility", "strength", "literature", "science", "medicine", "esoteric", "fame", "art", "martial", "karma" };
	for (int i = 0; i < 24; i = i + 2)
	{
		vector<int> vect0{ stats[i],stats[i+1] };
		
		//itemStats[statNames[i / 2]] = array0;
		//cout << itemStats[statNames[i / 2]] << endl;
		//cout << itemStats[statNames[i / 2]][0] << ", " << itemStats[statNames[i/2]][1];
		//cout << array0[0] << endl;
		itemStats.insert(pair<string, vector<int>>(statNames[i / 2], vect0));
	}
	isUsed = used;
}

item::~item()
{
}

item::item(item& i)
{
	name = i.getName();
	description = i.getDesc();
	USED_Name = i.getUsedName();
	Price = i.getPrice();
	progressVariable = i.getProgressVar();
	stageRequirement = i.getStage();
	consumedOnUse = i.isConsumable();
	isUsed = i.getIsUsed();
	string statNames[12] = { "sanity", "vitality", "agility", "strength", "literature", "science", "medicine", "esoteric", "fame", "art", "martial", "karma" };
	for (int j = 0; j < 12; j++)
	{
		vector<int> vect0{ i.getStat(statNames[j]),i.getPreq(statNames[j])};
		//cout << vect0[0] <<" "<< vect0[1]<< endl;
		//itemStats[statNames[j]] = array0;
		itemStats.insert(pair<string, vector<int>>(statNames[j],vect0));
		//cout<< itemStats.at(statNames[j]);
	}
}

string item::getName()
{
	return name;
}

string item::getUsedName()
{
	return USED_Name;
}

string item::getDesc()
{
	return description;
}

int item::getStage()
{
	return stageRequirement;
}

int item::getPrice()
{
	return Price;
}

void item::setUsed()
{
	name = USED_Name;
	Price = 1;
	isUsed = true;
}

int item::getStat(string statName)
{
	//cout << statName << endl;
	//cout<<itemStats.find(statName)
	//cout << itemStats[statName]<<endl;
	return itemStats[statName][0];
	//for (auto const&x : itemStats)
		//if (x.first == statName)  
		//{
		//	cout << x.second << endl; return x.second[0];
		//}
	//return 0;
}

int item::getPreq(string statName)
{
	//cout << itemStats["sanity"][1] << endl;
	return itemStats[statName][1];
	//for (auto const&x : itemStats)
	//	if (x.first == statName) return x.second[1];
	//return 0;
	//return 0;
}

int item::getProgressVar()
{
	return progressVariable;
}

bool item::getIsUsed()
{
	return isUsed;
}

bool item::isConsumable()
{
	return consumedOnUse;
}

bool item::canBuy(int money)
{
	if (money < Price)
		return false;
	else return true;
}

bool item::canUse(int uSanity, int uVitality, int uAgility, int uStrength, int uLiterature, int uScience, int uMedicine, int uEsoteric, int uFame, int uArt, int uMartial, int uKarma)
{
	if (isUsed == true) return false;
	string statNames[12] = { "sanity", "vitality", "agility", "strength", "literature", "science", "medicine", "esoteric", "fame", "art", "martial", "karma" };
	if(uSanity < getPreq(statNames[0])) return false;
	if (uVitality < getPreq(statNames[1])) return false;
	if (uAgility < getPreq(statNames[2])) return false;
	if (uStrength < getPreq(statNames[3]))return false;
	if (uLiterature < getPreq(statNames[4]))return false;
	if (uScience < getPreq(statNames[5])) return false;
	if (uMedicine < getPreq(statNames[6])) return false;
	if (uEsoteric < getPreq(statNames[7])) return false;
	if (uFame < getPreq(statNames[8])) return false;
	if (uArt < getPreq(statNames[9])) return false;
	if (uMartial < getPreq(statNames[10])) return false;
	if (uKarma < getPreq(statNames[11])) return false;
	return true;
}
