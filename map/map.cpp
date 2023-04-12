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

Map readfile(string filename)
{
	string fileLine, temp;
	ifstream input;
	int orderOperation = 0;
	bool check = false;
	//mode of construction on map: 0 default, 1 continents, 2 countries, 3 borders 
	int mode = 0; 
	int counter = 0;
	string country;
	string delim = " ";
	int int1, int2, int3;
	size_t pos;
	input.open(filename);
	input >> fileLine;
	Map map(filename);
	//read file
	while (getline(input, fileLine))
	{

		//check for correct order
		if (orderOperation == 4)
		{
			break;
		}
		//create continents
		if (fileLine == "[continents]")
		{
			orderOperation = 1;
			counter = 0;

			while (getline(input, fileLine))
			{
				counter++;
				//end of continents we break
				if (fileLine == "[countries]")
				{
					break;
				}
				while ((pos = fileLine.find(delim)) != string::npos) 
				{
					temp = fileLine.substr(0, pos);
					//map.addContinent((fileLine.substr(0, pos)), counter);
					fileLine.erase(0, pos + delim.length());
					pos = fileLine.find(delim);
					map.addContinent(temp, counter, stoi((fileLine.substr(0, pos))));
					break;
				}

			}
		}
		check = false;
		//make countries/territories
		if (fileLine == "[countries]")
		{
			int1 = 0;
			int2 = 0;
			int3 = 0;

			//check for correct order
			if (orderOperation != 1)
			{
				throw invalid_argument("Map is invalid");
				orderOperation = 4;
				break;
			}
			orderOperation = 2;
			while (getline(input, fileLine))
			{
				counter = 0;
				//end of country and start of borders we break
				if (fileLine == "[borders]")
				{
					break;
				}
				while ((pos = fileLine.find(delim)) != string::npos && !check)
				{
					//skip anything prior introduction of 1st map element this will start with 1
					if ((fileLine.substr(0, pos)) == "1")
					{
						check = true;
						break;
					}
					fileLine.erase(0, pos + delim.length());
					
				}
				
				while ((pos = fileLine.find(delim)) != string::npos && check)
				{
					if (counter == 0)
					{
						int1 = stoi(fileLine.substr(0, pos));
					}
					if (counter == 1)
					{
						country = (fileLine.substr(0, pos));
					}
					if (counter == 2)
					{
						int3 = stoi(fileLine.substr(0, pos));
					}
					fileLine.erase(0, pos + delim.length());
					counter++;
					if (counter == 3)
					{
						//make territory and adding it to the map
						map.addTerritory(int1 -1, country, int3 -1);
						/* adding the territory to the appropriate continent
						it only holds the index of the territory and not a pointer as the vector changes with every addition */
						map.addToContinent(int3 -1, int1 -1);
						break;
					}
				}

			}
		}
		check = false;
		//making borders
		if (fileLine == "[borders]")
		{
			int1 = 0;
			int2 = 0;
			int3 = 0;
			//check correct order 
			if (orderOperation != 2)
			{
				throw invalid_argument("Map is invalid");
				orderOperation = 4;
				break;
			}
			orderOperation = 3;
			while (getline(input, fileLine))
			{
				counter = 0;
				while ((pos = fileLine.find(delim)) != string::npos && !check)
				{
					//skip anything prior introduction of 1st map element this will start with 1
					if ((fileLine.substr(0, pos)) == "1")
					{
						check = true;
						break;
					}
					fileLine.erase(0, pos + delim.length());
				}
				//reading bordering territories
				while ((pos = fileLine.find(delim)) != string::npos && check)
				{
					//counter for getting 1st element of line
					counter++;
					int1 = stoi(fileLine.substr(0, pos));
					if (counter == 1)
					{
						//gets ID of the territory which share borders
						int2 = int1;
					}
					else
					{
						map.addBorders(int2, int1);
					}
					fileLine.erase(0, pos + delim.length());
				}
			
				if(check && fileLine.length()>0)
				{
					int1 = stoi(fileLine);
					//add borders to the territory
					map.addBorders(int2, int1);
				}
				//end of border and eof
			}
		}
	}
	if (orderOperation !=3)
		throw invalid_argument("Map is invalid");
	input.close();
	return map;
}

//By Nicolas
string Territory::getTerritoryOwner() const {
	return this->territoryOwner;
}

void Territory::setTerritoryOwner(string owner) {
	this->territoryOwner = owner;
}

void Territory::setName(string name) {
	this->name = name;
}
