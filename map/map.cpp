#include "map.h"
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

territory::territory(int id, string n, int c) :ID(id), name(n), continent(c)
{
	numOfArmies = 0;
}
continent::continent(string n, int id, int bonus) :name(n), ID(id), Bonus(bonus)
{
	terrIDs;
}

Map::Map()
{
	land; 
	continents;
}
Map::Map(string fileName) : Map() {
	name = fileName;
}
//the territory object is generated within the Map object for mainting scope within stack
void Map::addTerritory(int id, string n, int c)
{
	land.push_back(territory(id, n, c));
};

void Map::addToContinent(int c, int t)
{
	getContinent(c)->addTerrID(t);
}

void continent::addTerrID(int t)
{
	terrIDs.push_back(t);
}

territory* Map::getTerritory(int id)
{
	return &land[id];
}

continent* Map::getContinent(int id)
{
	return &continents[id];
}

int territory::getNumOfBorders()
{
	return borders.size();
}

int continent::getLength()
{
	return terrIDs.size();
}

int continent::getBonus()
{
	return Bonus;
}

void Map::addBorders(int territory, int border)
{
	land[territory - 1].addBorders(&land[border - 1]);
}

void territory::addBorders(territory* t)
{
	borders.push_back(t);
}
//need to add somehting here as well about the bonus
void Map::addContinent(string name, int id, int bonus)
{
	continents.push_back(continent(name, id, bonus));
};



int Map::getNumOfTerr()
{
	return land.size();
}

string territory::getName()
{
	return name;
};

string continent::getName()
{
	return name;
}



int territory::getID()
{
	return ID;
}

int continent::getID()
{
	return ID;
}

void territory::setContinent(int c)
{
	continent = c;	
}

int territory::getBorderID(int pos)
{
	return borders[pos]->getID();
}

bool territory::isAdjacentTerritory(territory* target)
{
	std::vector<territory*>::iterator it = std::find(borders.begin(), borders.end(), target);
	if (it != borders.end())
	{
		return true;
	}
	return false;
}

int Map::getNumOfCont()
{
	return continents.size();
}

int continent::getTerrID(int index)
{
	return terrIDs[index];
}

bool validate(Map m)
{
	vector<int> memory;
	//test map starting from every possible territory on map
	for ( int i =0; i < m.getNumOfTerr(); i++)
	{
		memory.clear();
		validateMap(m, memory, i);
		if (memory.size() != m.getNumOfTerr())
		{
			cout << memory.size() << " mem vs actual " << m.getNumOfTerr() << endl;
			cout << "invalid map" << endl;
			return false;
		}
	}
	//testing for each continent
	for (int i = 0; i < m.getNumOfCont(); i++)
	{
		//start from every territory in continent
		for (int j = 0; j < m.getContinent(i)->getLength(); j++)
		{
			memory.clear();
			validateContinent(m, i, memory, m.getContinent(i)->getTerrID(j));
			if (memory.size() != m.getContinent(i)->getLength())
			{
				cout << memory.size() << " mem vs actual " << m.getContinent(i)->getLength() << endl;
				cout << "invalid map" << endl;
				return false;
			}
		}
		
	}
	return true;
}
void validateMap(Map m, vector<int>& memory, int reference)
{
	//add curr ID to the memory
	memory.push_back(reference);
	bool been;
	for (int i = 0; i < m.getTerritory(reference)->getNumOfBorders(); i++)
	{
		been = false;
		// for loop for checking if the country ID is already in the memory vector
		for (int j = 0; j < memory.size(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == memory[j])
			{
				been = true;
				break;
			}
		}
		//if the country ID isn't in memory vector, then that country is used as the new start point
		if (been)
		{
			continue;
		}
		validateMap(m, memory, m.getTerritory(reference)->getBorderID(i));
	}
}

void validateContinent(Map m, int c, vector<int>& memory, int reference)
{
	//insert curr location into memory
	memory.push_back(reference);
	bool been;;
	bool inContinent;
	for (int i = 0; i < m.getTerritory(reference)->getNumOfBorders(); i++)
	{
		been = false;
		inContinent = false;
		//ensure not to call the function again on territory that code has already been in
		for (int j = 0; j < memory.size(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == memory[j])
			{
				been = true;
				break;
			}
		}
		//ensures that only territories called are within continent
		for (int j = 0; j < m.getContinent(c)->getLength(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == m.getContinent(c)->getTerrID(j))
			{
				inContinent = true;
				break;
			}
		}
		if (!been && inContinent)
		{
			validateContinent(m, c, memory, m.getTerritory(reference)->getBorderID(i));
		}

	}
}
