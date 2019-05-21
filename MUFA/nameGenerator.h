#pragma once
#include "time.h"
#include <vector>
#include <string>

using namespace std;
class nameGenerator
{
	vector<pair<char, int>> charTable;
public:
	nameGenerator();
	bool isVowel(char ch);
	string nGenerate();
	
};