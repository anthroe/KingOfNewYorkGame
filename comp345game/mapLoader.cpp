#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Maploader.h"
#include "Map.h"

using namespace std;

vector<string> removeCommas(string line) {
	stringstream ss(line);
	vector<string> words;

	while (ss.good()) {
		string word;
		getline(ss, word, ',');
		words.push_back(word);
	}

	return words;
}

Maploader::Maploader() {
	mapInPlay = new Map();
}

Maploader::Maploader(string textFileName) {
	ifstream inFile(textFileName);
	if (!inFile) {
		cout << "Unable to open file";
		exit(1);
	}

	string line;
	string city;
	vector<Region> allRegions;

	// First line
	getline(inFile, line);

	// Check for [Map]
	if (line != "[City]") {
		inFile.close();
		throw invalid_argument("Map file is invalid, missing [City] section.");
	}

	// City name
	getline(inFile, city);

	// Skip to Regions section
	while (line != "[Regions]" && !inFile.eof()) {
		getline(inFile, line);
	}

	// Add all regions
	while (inFile >> line) {

		if (line == "[Neighbours]") {
			break;
		}

		//remove commas between words
		vector<string> words = removeCommas(line);

		string regionName = words[0];
		int id = stoi(words[1]);
		allRegions.push_back(Region(regionName, id));
	}

	// Add neighbours to each region
	while (inFile >> line) {

		//remove commas between words
		vector<string> words = removeCommas(line);

		vector<Region> neighbours;
		string currentRegion = words[0];
		int position = NULL;

		for (int i = 0; i < allRegions.size(); i++) {
			if (allRegions[i].getName() == currentRegion) {
				position = i;
			}
		}

		for (int i = 0; i < allRegions.size(); i++) {
			for (int j = 1; j < words.size(); j++) {
				if (allRegions[i].getName() == words[j]) {
					neighbours.push_back(allRegions[i]);

				}
			}
		}

		allRegions[position].addNearbyRegions(neighbours);

		if (inFile.eof()) {
			break;
		}

	}

	/*for (int i = 0; i < allRegions.size(); i++) {
		cout << allRegions[i].getName() << endl;

		vector<Region> neighbours = allRegions[i].getNearbyRegions();
		for (int j = 0; j < neighbours.size(); j++) {
			cout << "	" + neighbours[j].getName() << endl;
		}
	}*/

	Map mapInPlay(allRegions);
	mapInPlay.checkConnection();
}

Maploader::~Maploader() {
	delete mapInPlay;
}