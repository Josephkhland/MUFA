#include "pch.h"
#include "society.h"



society::society()
{
	
	level = 10;
	for (int i = 0; i < 20; i++) contacts.push_back(generateRandomPerson());
}


society::~society()
{
	contacts.clear();
}

void society::performDaily()
{
	int firstSize = contacts.size();
	for (int i = firstSize-1; i >=0; i--)
	{
		if (contacts[i]->dailyCheck() == 1)
		{
			cout << contacts[i]->getName() << " has departed from this world.";
			contacts.erase(contacts.begin() + i);
		}
	}
}

int society::getNumberOfContacts()
{
	return contacts.size();
}

person* society::generateRandomPerson()
{
	
	return generatePerson(names.nGenerate());
	
	return 0;
}

person * society::generatePerson(string Name)
{
	int sanityL = rand() % level + 1;
	int vitalityL = rand() % level + 1;
	int agilityL = rand() % level + 1;
	int strengthL = rand() % level + 1;
	int moneyL = rand() % (level*10) + 1;

	int karmaL = rand() % (level * 20) - level * 10;
	int relation = 0;
	int generosity = rand() % 20 + 1;
	int will = rand() % 20 + 1;

	int numberOfItems = 1;
	int exponSeed = rand() % 100 + 1;
	while (exponSeed > 50)
	{
		numberOfItems++;
		exponSeed = rand() % 100 + 1 -5*numberOfItems;
	}
	vector<pair<string, bool>> itemss;
	for (int i = 0; i < numberOfItems; i++)
	{
		itemss.push_back(pair<string, bool>(generateItemName(), false));
	}
	pair<int, string> prof = make_pair(rand() % (level * 10) + 1, "MYSTERIOUS PROFFESIONAL");
	return new person(Name,sanityL,vitalityL,agilityL,strengthL,moneyL,karmaL,relation,generosity,will,itemss,prof);
}

void society::showContacts(bool longmode)
{
	cout << "Your list of contacts: " << endl;
	if (longmode == false)
	{
		for (int i=0; i < contacts.size(); i++)
		{
			cout << i << ". ";
			cout << contacts[i]->getName() << ", the " << contacts[i]->getProficiency().second << endl;
			//cout << endl;
		}
	}
	else
	{
		for (int i=0; i < contacts.size(); i++)
		{
			cout << i << ". " << endl;
			contacts[i]->printPerson();
			cout << endl;
		}
	}
}

void society::showContact(int index)
{
	contacts[index]->printPerson();
}

void society::setLevel(int amount)
{
	level = amount;
}

person * society::getPerson(int index)
{
	return contacts[index];
}

person * society::exportPerson(int index)
{
	return new person(*contacts[index]);
}

person * society::exportPerson(string Name)
{
	for (int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i]->getName() == Name) return new person(*contacts[i]);
		
	}
	return new person(*generatePerson(Name));
	return nullptr;
}

string society::generateItemName()
{
	itemDataBase tempItems;
	int cap = tempItems.getSize();
	int id = rand() % cap;
	return tempItems.getItem(id)->getName();
}
