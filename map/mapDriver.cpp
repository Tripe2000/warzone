#include "map.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

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
		
int main()
{
	string filename;
	cout << "Enter file name of map to be generated" << endl;
	cin >> filename;
	Map map = readfile(filename);
	cout << "generating map..." << endl;
	cout << "checking if the map file is valid" << endl;
	if (validate(map))
	{
		cout << "the map is valid!!" << endl;
	}
	else
	{
		cout << "the map is not valid!!" << endl;
	}
	return 0;
}
