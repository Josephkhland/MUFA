#pragma once
#include "happening.h"
class tableOfEvents
{
	vector<happening*> eventsList;
	int totalEvents;
public:
	tableOfEvents();
	~tableOfEvents();

	happening* getEvent(int progressVar);
};

