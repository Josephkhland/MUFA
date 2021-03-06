// MUFA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "item.h"
#include "itemDataBase.h"
#include <vector>
#include <time.h>
#include "tableOfEvents.h"
#include "happening.h"
#include "person.h"
#include "society.h"
using namespace std;



string easytolower(string in) {
	for (int i = 0; in[i] != '\0'; i++)
	{
		if (in[i] <= 'Z' && in[i] >= 'A')
			in[i] = in[i] - ('Z' - 'z');

	}
	return in;

}
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
const int TOTAL_GAME_EVENTS = 50;

//commands variables
string input = "code 0: Initialising component";
int day = 0;
int stage = 0;

//Stats
int sanity = 1;
int vitality = 1;
int agility = 1;
int strength = 1;
int money = 10;

//Stat Gain Variables:
int sanityGain = 1;
int vitalityGain = 1;
int agilityGain = 1;
int strengthGain = 1;

//Stat Loss Variables:
int sanityLoss = 1;
int vitalityLoss = 1;
int agilityLoss = 1;
int strengthLoss = 1;

//Secondary Stats:
int literature = 0;
int science = 0;
int medicine =0;
int esoteric =0;
int fame =0;
int art =0;
int martial=0;
int karma=0;

//Progress Variables
int lastDayAte=0;
bool progress[TOTAL_GAME_EVENTS];
bool completed[TOTAL_GAME_EVENTS];
tableOfEvents story;
vector<pair<int, string>> unlockedProficiencies;

//Items
itemDataBase items;
vector<item*> shop;
vector<item*> inventory;
pair<int, string> proficiency;

//Social
society mySociety;


void increaseStat(pair<string, int> input)
{
	if (input.first == "sanity") sanity += input.second;
	if (input.first == "vitality") vitality += input.second;
	if (input.first == "agility") agility += input.second;
	if (input.first == "strength") strength += input.second;
	if (input.first == "literature") literature += input.second;
	if (input.first == "science") science += input.second;
	if (input.first == "medicine") medicine += input.second;
	if (input.first == "esoteric") esoteric += input.second;
	if (input.first == "fame") fame += input.second;
	if (input.first == "art") art += input.second;
	if (input.first == "martial") martial += input.second;
	if (input.first == "karma") karma += input.second;

}

void useItem(item* object)
{
	if (object->canUse(sanity, vitality, agility, strength, literature, science, medicine, esoteric, fame, art, martial, karma) == true)
	{
		string statNames[12] = { "sanity", "vitality", "agility", "strength", "literature", "science", "medicine", "esoteric", "fame", "art", "martial", "karma" };
		int i = 0;
		sanity += object->getStat(statNames[i++]);
		vitality += object->getStat(statNames[i++]);
		agility += object->getStat(statNames[i++]);
		int strengthBonus = object->getStat(statNames[i++]);
		if (strengthBonus > 0)
		{
			lastDayAte = day;
			strength += strengthBonus;
		}
		literature += object->getStat(statNames[i++]);
		science += object->getStat(statNames[i++]);
		medicine += object->getStat(statNames[i++]);
		esoteric += object->getStat(statNames[i++]);
		fame  += object->getStat(statNames[i++]);
		art += object->getStat(statNames[i++]);
		martial += object->getStat(statNames[i++]);
		karma += object->getStat(statNames[i++]);
		progress[object->getProgressVar()] = true;
		cout << "You have used item: " << object->getName() << endl;
		object->setUsed();
		
	}
	else
	{
		cout << "You can't use this item yet." << endl;
	}
	
	
}

void shopRefill(int stage0)
{
	const int TOTAL_ITEMS = items.getSize();
	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		if (items.getItem(i)->getStage() <= stage0) shop.push_back(items.getItem(i));
	}
}

void initialize()
{
	int tmpMax = shop.size();
	for (int i = 0; i < tmpMax; i++)
	{
		shop.pop_back();
	}
	tmpMax = inventory.size();
	for (int i = 0; i < tmpMax; i++)
	{
		inventory.pop_back();
	}
	shopRefill(stage);
	day = 0;
	stage = 0;
	sanity = 1;
	vitality = 1;
	agility = 1;
	strength = 1;
	money = 10;
	sanityGain = 1;
	vitalityGain = 1;
	agilityGain = 1;
	strengthGain = 1;
	sanityLoss = 1;
	vitalityLoss = 1;
	agilityLoss = 1;
	strengthLoss = 1;
	literature = 0;
	science = 0;
	medicine = 0;
	esoteric = 0;
	fame = 0;
	art = 0;
	martial = 0;
	karma = 0;
	lastDayAte = 0;
	for (int i = 0; i < 50; i++)
	{
		progress[i] = false;
		completed[i] = false;
	}
	proficiency = make_pair(10, "Student");
	return;
}

void progressEvaluation()
{
	for (int i = 1; i < TOTAL_GAME_EVENTS; i++)
	{
		if (progress[i] && !completed[i])
		{
			completed[i] = true;
			happening * episode = story.getEvent(i);
			//Shows Message
			cout << episode->getMessage() << endl;

			//Shows Choices
			int numSize = episode->numberOfChoices();
			for (int j = 0; j < numSize; j++)
			{
				cout << j << ". " << episode->getChoice(j).second << endl;
			}

			//User Picks Choice
			int choice;
			cin >> choice;
			cout << endl;

			//Adds items based on choice
			int itemsTag = episode->getChoice(choice).first;
			int itemsNum = episode->numberOfItems(itemsTag);
			for (int j = 0; j < itemsNum; j++)
			{
				string currentItem = episode->getItemName(itemsTag, j);
				cout << currentItem << " has been added to your inventory" << endl;
				inventory.push_back(items.getItem(currentItem));
			}

			//Changes Stats
			for (int j = 0; j < episode->statsIncrease.size(); j++)
			{
				increaseStat(episode->statsIncrease[j]);
			}

			//Checks if stage should be changed and increase by one
			if (stage < episode->getMaxStage() && episode->doesStageUP() == true)
			{
				stage += 1;
				shopRefill(stage);
			}

			//Unlock new proficiencies;
			pair<int, string> profToUnlock = episode->getProf(choice);

			for (int j = 0; j < unlockedProficiencies.size(); j++)
			{
				if (profToUnlock.second == unlockedProficiencies[j].second)return;
			}
			unlockedProficiencies.push_back(profToUnlock);
		}
	}
}

int main()
{
	initialize();
	srand(time(NULL));
	//Intro Text & Game Loop
	cout << "Welcome to MUFA, the Multiple Unidentified Futures Anthology" << endl;
	cout << endl;
	cout << "Think, to start playing!" << endl;
	cout << endl;
	while (input != "exit")
	{
		cout << "Day: " << day << endl << "Stage: " << stage << endl;
		cout << "Sanity: " << sanity << endl;
		cout << "Vitality: " << vitality << endl;
		cout << "Agility: " << agility << endl;
		cout << "Strength: " << strength <<" -Last Meal: "<<day -lastDayAte <<" days ago." << endl;
		cout << "Money: " << money <<" -Next Payroll in: "<<30-day%30<< " days." <<endl;
		cout << endl << "Picking your action... ";
		cin >> input;
		input = easytolower(input);
		cout << endl;

		//Actions:
		if (input == "think")
		{
			sanity += sanityGain;
		}
		else if (input == "rest")
		{
			vitality += vitalityGain;
			sanity -= sanityLoss;

		}
		else if (input == "run")
		{
			agility += agilityGain;
			vitality -= vitalityLoss;
		}
		else if (input == "eat")
		{
			strength += strengthGain;
			agility -= agilityLoss;
			lastDayAte = day;
		}
		else if (input == "cheat")
		{
			sanity += 100;
			vitality += 100;
			agility += 100;
			strength += 100;
			karma -= 100;
		}
		else if (input == "suicide")
		{
			initialize();
			cout << "You were murdered in cold blood... by yourself!" << endl << endl;;
			continue;
		}
		else if (input == "shop")
		{
			input = string();
			cout << "Welcome to the shop!" << endl;
			//cout << "ID - ITEM - PRICE - DESCRIPTION" << endl;
			int count = 0;
			for (auto &const i : shop)
			{
				cout << count++ << ". \"" << i->getName() << "\" PRICE: " << i->getPrice() << " DESCRIPTION: " << i->getDesc() << endl;
			}
			cin >> input;
			input = easytolower(input);
			cout << endl;
			if (input == "buy")
			{
				cout << "Which item do you wish to purchase? -Type shop index- " << endl;
				cin >> input;
				cout << endl;
				int id0 = stoi(input);
				if (id0 < shop.size() && id0 >= 0)
				{
					if (shop[id0]->canBuy(money))
					{
						money -= shop[id0]->getPrice();
						cout << "You've just purchased " << shop[id0]->getName() << " and your new balance is " << money << "$" << endl;
						inventory.push_back(shop[id0]);
						vector<item*>::iterator itr;
						itr = shop.begin() + id0;
						shop.erase(itr);


					}
					else
					{
						cout << "You don't have enough money to buy this!" << endl;
					}
				}
				else cout << "No such item in the shop." << endl;
			}
			else if (input == "back") continue;
			else if (input == "steal")
			{
				cout << "Which item do you wish to steal? -Type shop index- " << endl;
				cin >> input;
				cout << endl;
				int id0 = stoi(input);
				if (id0 < shop.size() && id0 >= 0)
				{
					karma -= shop[id0]->getPrice();
					//Random check of 1d100 + agility + karma
					int randomCheck = rand() % 100 + 1 + agility + karma;
					// if success
					if (randomCheck > 50)
					{
						cout << "You just stole: " << shop[id0]->getName() << endl;
						inventory.push_back(shop[id0]);
						vector<item*>::iterator itr;
						itr = shop.begin() + id0;
						shop.erase(itr);
					}
					// if failure
					else
					{
						cout << "You failed to steal from the shop, the owner caught you and killed you." << endl << endl;
						initialize();
						continue;
					}


					
				}
			}

		}
		else if (input == "inventory")
		{
			input = string();
			cout << "INVENTORY" << endl;
			int count = 0;
			for (auto &const i : inventory)
			{
				cout << count++ << ". \"" << i->getName() << "\" - DESCRIPTION: " << i->getDesc() << endl;
			}
			cin >> input;
			input = easytolower(input);
			cout << endl;
			if (input == "use")
			{
				cout << "Which item would you like to use? -Type item index-" << endl;
				cin >> input;
				cout << endl;
				int id0 = stoi(input);
				if (id0 < inventory.size() && id0 >= 0)
				{
					useItem(inventory[id0]);
					if (inventory[id0]->isConsumable())
					{
						vector<item*>::iterator itr;
						itr = inventory.begin() + id0;
						inventory.erase(itr);
					}
				}
				else {
					cout << "Invalid index" << endl;
					continue;
				}
			

			}
			else if (input == "sell")
			{
				cout << "Which item would you like to sell? -Type item index-" << endl;
				cin >> input;
				cout << endl;
				int id0 = stoi(input);
				if (id0 < inventory.size() && id0 >= 0)
				{
					money+= inventory[id0]->getPrice();
					vector<item*>::iterator itr;
					itr = inventory.begin() + id0;
					inventory.erase(itr);
					
				}
				else {
					cout << "Invalid index" << endl;
					continue;
				}
			}
			else if (input == "gift")
			{
				cout << "Which item would you like to gift? -Type item index-" << endl;
				cin >> input;
				cout << endl;
				int id0 = stoi(input);
				if (id0 < inventory.size() && id0 >= 0)
				{
					karma += inventory[id0]->getPrice();
					vector<item*>::iterator itr;
					itr = inventory.begin() + id0;
					inventory.erase(itr);

				}
				else {
					cout << "Invalid index" << endl;
					continue;
				}
			}
			else continue;
		}
		else if (input == "profile")
		{
			if (stage = 0)
			{
				cout << "Proficiency: " << proficiency.second << " - Salary: " << proficiency.first << endl;
				cout << "Make sure to study!" << endl;
			}
			else
			{
				cout << "Proficiency: " << proficiency.second << " - Salary: " << proficiency.first << endl;
				cout << endl;
				cout << "Literature: " << literature << endl;
				cout << "Science: " << science << endl;
				cout << "Medicine: " << medicine << endl;
				cout << "Esoteric: " << esoteric << endl;
				cout << "Fame: " << fame << endl; 
				cout <<"Art: " << art << endl;
				cout << "Martial: " << martial << endl;
				cout <<"Karma: " << karma << endl;
				
			}
			cout << endl;
			continue;

		}
		else if (input == "friends")
		{
		mySociety.showContacts();
		cout << endl;
		cout << "To check details -Type contact index-" << endl;
		cin >> input;
		cout << endl;
		int id0 = stoi(input);
		if (id0 >= 0 && id0 < mySociety.getNumberOfContacts())
		{
			mySociety.showContact(id0);
			cout << endl;
			cout << "What would you like to do with this contact?" << endl;
			cin >> input;
			cout << endl;
			if (input == "visit")
			{
			
				mySociety.getPerson(id0)->increaseSanity(1);
				mySociety.getPerson(id0)->increaseVitality(1);
				mySociety.getPerson(id0)->increaseAgility(1);
				mySociety.getPerson(id0)->increaseStrength(1);
				mySociety.getPerson(id0)->increaseRelation(10);
				mySociety.getPerson(id0)->increaseWill(10);
				fame += 1;
				karma += 1;
				int incr = 1;
				if (mySociety.getPerson(id0)->getKarma() < 0) incr *= -1;
				int picker = rand() % 11;
				switch (picker)
				{
				case 0://Sanity
					sanity += incr;
					break;
				case 1: // Vitality
					vitality += incr;
					break;
				case 2: //Agility
					agility += incr;
					break;
				case 3: //Strength
					strength += incr;
					break;
				case 4: // Literature
					if (incr < 0 && literature == 0) break;
					else literature += incr;
					break;
				case 5: // Science
					if (incr < 0 && science == 0) break;
					else science += incr;
					break;
				case 6: // Esoteric
					if (incr < 0 && esoteric == 0) break;
					else esoteric += incr;
					break;
				case 7: // Medicine
					if (incr < 0 && medicine == 0) break;
					else medicine += incr;
					break;
				case 8: //Fame
					if (incr < 0 && fame == 0) break;
					else fame += incr;
					break;
				case 9: // Art
					if (incr < 0 && art == 0) break;
					else art += incr;
					break;
				case 10: //Martial
					if (incr < 0 && martial == 0) break;
					else martial += incr;
					break;
				}
			}
			else
			{
				continue;
			}
		}
		cout << endl;
		
		}
		else if (input != "exit")
		{
			cout << "You can't do that!" << endl << endl;
			input = string();
			continue;
		}
		
		//Difficulty Factors
		day++;
		if (day % 5 == 0) vitality -= vitalityLoss;
		if (day - lastDayAte >= 7 ) strength -= strengthLoss;
		if (day % 30 == 0) money += proficiency.first;
		progressEvaluation();
		mySociety.performDaily();

		//LOSS CONDITIONS
		if (sanity <= 0)
		{
			initialize();
			cout << "It was a foggy moonlit night, when your body was found scattered upon the surface of a frozen lake." << endl;
		}
		else if (vitality <= 0)
		{
			initialize();
			cout << "Driving yourself beyond your physical capabilities, you ended up drained and fatigued. Eventually died off Sickness." << endl ;
		}
		else if (agility <= 0)
		{
			initialize();
			cout << "You were chased through the streets... being too slow, you've been murdered." << endl;
		}
		else if (strength <= 0)
		{
			initialize();
			cout << "You've died of malnutrition." << endl;
		}

		
		
		cout << endl;
	}
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
