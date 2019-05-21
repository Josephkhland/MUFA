#include "pch.h"
#include "itemDataBase.h"




itemDataBase::itemDataBase()
{
	//Book
	item* no1 = new item("Book", "Read it if you dare", "Completed Book", 0,5,1,false ,
			vector<int>{ //Effect on Stat, Stat Prerequisite
				-10,10,		//Sanity
				0,0,		//Vitality
				0,0,		//Agility
				0,0,		//Strength
				0,0,		//literature
				0,0,		//Science
				0,0,		//Medicine
				0,0,		//Esoteric
				0,0,		//Fame
				0,0,		//Art
				0,0,		//Martial
				0,-1000		//Karma
	}    //(string Name, string desc, string usedName,int stageReq, int price,int progressVar ,vector<int> stats [24], bool used)
	);
	itemsList.push_back(no1);

	item* no2 = new item("Snack", "Eat for +2 Vitality, +2 Strength, -1 Agility", "CONSUMED",0,3,0,true,
		vector<int>{//Effect on Stat, Stat Prerequisite
		 0, 0,		//Sanity
			2, 0,		//Vitality
			-1, 0,		//Agility
			2, 0,		//Strength
			0, 0,		//literature
			0, 0,		//Science
			0, 0,		//Medicine
			0, 0,		//Esoteric
			0, 0,		//Fame
			0, 0,		//Art
			0, 0,		//Martial
			0, -1000		//Karma
	}
	);
	itemsList.push_back(no2);

	
}


itemDataBase::~itemDataBase()
{
}

item * itemDataBase::getItem(string name)
{
	for (auto &const i : itemsList)
	{
		if (i->getName() == name) return new item(*i) ;
	}
}

item * itemDataBase::getItem(int index)
{
	return new item(*itemsList[index]);
}

int itemDataBase::getSize()
{
	return itemsList.size();
}
