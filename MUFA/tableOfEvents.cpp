#include "pch.h"
#include "tableOfEvents.h"


tableOfEvents::tableOfEvents()
{
	happening* no1 = new happening(0, "Message", 0, false,
		vector<pair<int, string>>{
			pair<int,string>(0,"Choice 0"),
			pair<int,string>(1,"Choice 1"),
			pair<int,string>(2,"Choice 2")
		},
		vector<vector<string>>{
			vector<string>{"Item1","Item2","Item3"},
			vector<string>{"Item1","Item2"},
			vector<string>{"Item1","Item3","Item11"}
		},
		vector<pair<string, int>>{
			pair<string,int>("sanity",0),
			pair<string,int>("vitality",0),
			pair<string,int>("agility",0),
			pair<string,int>("strength",0),
			pair<string,int>("literature",0),
			pair<string,int>("science",0),
			pair<string,int>("medicine",0),
			pair<string,int>("esoteric",0),
			pair<string,int>("fame",0),
			pair<string,int>("art",0),
			pair<string,int>("martial",0),
			pair<string,int>("karma",0)
		},
			vector<pair<int, string>>{
				pair<int,string>(10,"Student"),
				pair<int,string>(20, "Donut Boy")
			}
		);
	eventsList.push_back(no1);

	happening* no2 = new happening(1, "After long hours of study, you finally graduated elementary school.\n Choose your career: ", 1, true,
		vector<pair<int, string>>{
		pair<int, string>(0, "Student"),
			pair<int, string>(1, "Donut Boy")
	},
		vector<vector<string>>{
			vector<string>{"Book", "Book", "Book"},
				vector<string>{"Snack", "Snack","Snack","Snack","Snack"}
		},
			vector<pair<string, int>>{
			pair<string, int>("sanity", 0),
				pair<string, int>("vitality", 0),
				pair<string, int>("agility", 0),
				pair<string, int>("strength", 0),
				pair<string, int>("literature", 0),
				pair<string, int>("science", 0),
				pair<string, int>("medicine", 0),
				pair<string, int>("esoteric", 0),
				pair<string, int>("fame", 0),
				pair<string, int>("art", 0),
				pair<string, int>("martial", 0),
				pair<string, int>("karma", 0)
		},
			vector<pair<int, string>>{
				pair<int, string>(10, "Student"),
					pair<int, string>(20, "Donut Boy")
			}
			);
	eventsList.push_back(no2);

}


tableOfEvents::~tableOfEvents()
{
}

happening * tableOfEvents::getEvent(int progressVar)
{
	for (auto &const i : eventsList)
	{
		if (i->getID() == progressVar) return new happening(*i);
	}
}
