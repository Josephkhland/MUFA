#pragma once
#include "person.h"
#include "itemDataBase.h"
#include "nameGenerator.h"
class society
{
	vector<person*> contacts;
	int level;
	nameGenerator names;
	
public:
	society();
	~society();

	void performDaily();
	int getNumberOfContacts();
	person* generateRandomPerson(); 
	person* generatePerson(string Name);
	void showContacts(bool longmode =false);
	void showContact(int index);
	void setLevel(int amount);
	person* getPerson(int index);
	person* exportPerson(int index);
	person* exportPerson(string Name);

	string generateItemName();
	

};

