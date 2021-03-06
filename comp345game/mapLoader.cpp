#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Maploader.h"
#include "Map.h"

using namespace std;

//removes commas from the line to read in the words
vector<string> removeCommas(string line) {
	stringstream ss(line);
	vector<string> words;

	while (ss.good()) {
		string word;
		getline(ss, word, ',');
		words.push_back(word); //push words after the comma
	}

	return words;
}

//Maploader constructor
Maploader::Maploader() {
}

//Maploader constructor that takes a file name
Maploader::Maploader(string textFileName) {
	ifstream inFile(textFileName);
	if (!inFile) { //exit if can't find file
		cout << "Unable to open file";
		system("pause");
		exit(1);
	}

	string line;
	string city;
	vector<Region*> allRegions;

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

	Tiles tiles;

	// Add all regions
	while (inFile >> line) {

		if (line == "[Neighbours]") {
			break;
		}

		//remove commas between words
		vector<string> words = removeCommas(line);

		string regionName = words[0];
		int id = stoi(words[1]); //convert string number to int
		allRegions.push_back(new Region(regionName, id, tiles));
	}

	// Add neighbours to each region
	while (inFile >> line) {

		//remove commas between words
		vector<string> words = removeCommas(line);

		string currentRegion = words[0];
		int position = NULL;
		
		//assign position to each region
		for (int i = 0; i < allRegions.size(); i++) {
			if ((*allRegions[i]).getName() == currentRegion) {
				position = i;
			}
		}
		//for all region names, add their respective neighbours
		for (int i = 0; i < allRegions.size(); i++) {
			for (int j = 1; j < words.size(); j++) {
				if ((*allRegions[i]).getName() == words[j]) {
					allRegions[position]->addNeighbour((*allRegions[i]));
				}
			}
		}

		if (inFile.eof()) {
			break;
		}

	}

	Map map(allRegions);
	mapInPlay = map;
	map.checkConnection();
}

Maploader::~Maploader() {
	
}