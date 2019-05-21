#pragma once
#include "item.h"
#include <string>
#include <vector>
class itemDataBase
{
private:
	vector<item*> itemsList;
	int totalItems;

public:
	itemDataBase();
	~itemDataBase();

	item * getItem(string name);
	item * getItem(int index);
	int getSize();
};

