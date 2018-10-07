//#include "cardtest.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Region.h"
#include "Maploader.h"


using namespace std;

int main() {
	//cards::main();

	ifstream inFile("test.map");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1);
	}

	string line;
	string city;
	vector<Region*> allRegions;

	getline(inFile, line);

	// Check for [Map]
	if (line != "[City]") {
		inFile.close();
		throw invalid_argument("Map file is invalid, missing [City] section.");
	}

	// City name
	//getline(inFile, city);

	// Skip to Regions section
	while (line != "[Regions]" && !inFile.eof()) {
		getline(inFile, line);
	}

	int n = 1;

	// Add all regions
	while (inFile >> line) {

		if (line == "[Neighbours]") {
			break;
		}

		//remove commas between words
		stringstream ss(line);
		vector<string> words;
		
		while (ss.good()) {
			string word;
			getline(ss, word, ',');
			words.push_back(word);
		}

		string* regionName = &words[0];
		int id = stoi(words[1]);
		Region* region(regionName, id);
		allRegions.push_back(region);

		n++;

	}

	// Add neighbours to each region
	while (inFile >> line) {

		//remove commas between words
		stringstream ss(line);
		vector<string> words;

		while (ss.good()) {
			string word;
			getline(ss, word, ',');
			words.push_back(word);
		}

		string currentRegion = words[0];

		int position = NULL;
		vector<Region*> neighbours;

		for(int i = 0; i < allRegions.size(); i++){
			if (allRegions[i]->getName() == currentRegion) {
				position = i;
			}
		}

		for (int i = 0; i < allRegions.size(); i++) {
			for (int j = 1; j < words.size(); j++) {
				if (allRegions[i]->getName() == words[j]) {
					neighbours.push_back(allRegions[i]);

				}
			}
		}

		allRegions[position]->addNearbyRegions(neighbours);

		if (inFile.eof()) {
			break;
		}

	}

	/*
	for (int i = 0; i < allRegions.size(); i++) {
		cout << allRegions[i].getName() << endl;

		vector<Region> neighbours = allRegions[i].getNearbyRegions();
		for (int j = 0; j < neighbours.size(); j++) {
			cout << "	" + neighbours[j].getName() << endl;
		}
	}
	*/

	Map map1(allRegions);

	map1.checkConnection();

	return 0;
}