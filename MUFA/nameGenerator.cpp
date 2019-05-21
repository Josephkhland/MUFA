#pragma once
#include "pch.h"
#include "nameGenerator.h"




nameGenerator::nameGenerator()
{
	srand(time(NULL));
	for (char i = 'A'; i <= 'Z'; i++)
	{
		int k = 10;
		if (i == 'Q') k = 1;
		charTable.push_back(pair<char, int>(i, k));
		
	}
	charTable.push_back(pair<char, int>('\0', 0));
}

bool nameGenerator::isVowel(char ch)
{
	return (ch == 'A') || (ch == 'E') || (ch == 'I') || (ch == 'O') || (ch == 'U');
}

string nameGenerator::nGenerate()
{
	vector<pair<char, int>> temp(charTable);
	int size = temp.size();
	temp[size - 1].second = 0;
	int counter = 0;
	bool finish = false;
	string name;
	int sum = 0;
	for (int i = 0; i < size; i++) sum += temp[i].second;
	while (finish == false)
	{
		int picker = rand() % (sum);
		sum = 0;
		char toAdd = ' ';
		for (int i = 0; i < size; i++)
		{
			sum += temp[i].second;
			if (picker <= sum)
			{
				toAdd = temp[i].first;
				temp[i].second = 1;
				if (toAdd == '\0') return name;
				name.push_back(toAdd);
				break;
			}

		}

		if (counter >= 3) temp[size-1].second += 3 * counter;
		if (isVowel(toAdd))
		{
			for (int i = 0; i < size - 1; i++)
			{
				if (isVowel(temp[i].first) && temp[i].first != toAdd) temp[i].second = 5;
				else if (!isVowel(temp[i].first))
				{
					if (temp[i].first != 'Q') temp[i].second = 10;
					else temp[i].second = 1;
				}
			}
		}
		else
		{
			for (int i = 0; i < size - 1; i++)
			{
				if (!isVowel(temp[i].first) && temp[i].first != toAdd) temp[i].second = 1;
				else if (isVowel(temp[i].first)) temp[i].second = 15;
			}
		}
		sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += temp[i].second;
		}

		
		if (++counter > 10) return name;

		


	}
}

