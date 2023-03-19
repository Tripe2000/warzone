#pragma once
#include <vector>
#include <string>
using namespace std;

class territory
{
public:
	territory(int id, string n, int c);
	string getName();
	int getID();
	void setContinent(int c);
	void addBorders(territory* t);
	int getNumOfBorders();
	int getBorderID(int pos);
	
	//By Nicolas
	string getTerritoryOwner() const;
	void setTerritoryOwner(string);
	
	void addArmies(int numberOfArmies) { numOfArmies += numberOfArmies; }
	void removeArmies(int numberOfArmies) { numOfArmies -= numberOfArmies; }
	void setArmies(int numberOfArmies) { numOfArmies = numberOfArmies; }
	int getArmies() { return numOfArmies; }
	bool isAdjacentTerritory(territory* target);
private:
	int numOfArmies;
	//vector of pointers for neigbor territories
	vector<territory*> borders;
	int continent;
	string name; 
	//territoryID 1 more than its index in the <vector>
	int ID; 
	//By Nicolas
	string territoryOwner;
};
class continent
{
public:
	int getID();
	string getName();
	continent(string n, int id, int bonus);
	int getLength();
	int getTerrID(int index);
	void addTerrID(int id);
	int getBonus();
private:
	int Bonus;
	string name;
	int ID;
	vector<int> terrIDs;
};

class Map
{
public:
	Map();
	Map(string name);
	void addTerritory(int id,string n, int c);
	void addContinent(string n, int id, int bonus);
	continent* getContinent(int id);
	territory* getTerritory(int id);
	vector<territory> getTerritories() { return land; }
	void addBorders(int territory, int border);
	int getNumOfTerr();
	int getNumOfCont();
	void addToContinent(int c, int t);
	string getName() { return name; }
private:
	string name;
	vector<territory> land;
	vector<continent> continents;
};


bool validate(Map m);

void validateMap(Map m, vector<int>& memory, int reference);

void validateContinent(Map m, int c, vector<int>& memory, int reference);
