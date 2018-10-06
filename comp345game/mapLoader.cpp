#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "Maploader.h"
#include "Map.h"

using namespace std;

Maploader::Maploader() {
	mapInPlay = new Map();
}

Maploader::Maploader(string textFileName) {
	mapInPlay = new Map();
	//parseMap(textFileName);
}

Maploader::~Maploader() {
	delete mapInPlay;
}

/*
// Helper function for getting whole lines without carriage returns
string MapLoader::readLine(ifstream &fileReader) {
	string line;
	if (getline(fileReader, line)) {
		return this->strip(line);
	}
	else {
		return "";
	}
}

// Helper function to strip \r or \n at the right end of the string
string MapLoader::strip(string s) {
	while (s[s.length() - 1] == '\r' || s[s.length() - 1] == '\n') {
		s.pop_back();
	}

	return s;
}

// Helper function to split strings
vector<string> MapLoader::split(string s, char delim) {
	stringstream ss(s);
	string input;
	vector<string> result;

	while (getline(ss, input, delim)) {
		result.push_back(input);
	}

	return result;
}

Map* MapLoader::getMap() {
	return loadedMap;
}

void MapLoader::parseMap(string textFileName) {
	string line;
	ifstream fileReader(textFileName);
	if (loadedMap != nullptr) {
		delete loadedMap;
		loadedMap = new Map();
	}

	// Verify that [Map] exists but skip over it to continents
	if ((line = this->readLine(fileReader)) != "[Map]") {
		fileReader.close();
		throw invalid_argument("Map file is invalid, missing [Map] section.");
	}

	while ((line = this->readLine(fileReader)) != "[Continents]" && !fileReader.eof()) {}

	// Parse the continents until we reach territories
	if (line != "[Continents]") {
		fileReader.close();
		throw invalid_argument("Map file is invalid, missing [Continents] section.");
	}

	while ((line = this->readLine(fileReader)) != "[Territories]" && !fileReader.eof()) {
		vector<string> continentInfo = this->split(line, '=');

		// Only parse valid lines with format [continent]=[value]
		if (continentInfo.size() == 2) {
			Continent* continent;
			try {
				continent = new Continent(stoi(continentInfo[1]), continentInfo[0]);
			}
			catch (invalid_argument e) {
				fileReader.close();
				throw invalid_argument("Expected integer value for continent but got something else.");
			}
			loadedMap->addContinent(continent);
		}
	}

	// Parse the territories until the end of the map file
	if (line != "[Territories]") {
		fileReader.close();
		throw invalid_argument("Map file is invalid, missing [Territories] section.");
	}

	// Add bordering country names to a 2d vector so we can add them once all countries are initialized
	vector<vector<string> > borderingCountries;
	map<string, bool> countryNames;

	line = this->readLine(fileReader);
	while (!fileReader.eof()) {
		if (line != "") {
			vector<string> countryInfo = this->split(line, ',');

			// Make sure there are at least 4 fields and the country name did not already show up
			if (countryInfo.size() > 4 && countryNames.count(countryInfo[0]) == 0) {
				Country* country = new Country(countryInfo[0], countryInfo[3]);
				countryNames[country->getName()] = true;

				// Add country to it's respective continent
				bool addedToContinent = false;
				for (int i = 0; i < loadedMap->getContinents().size(); i++) {
					if (loadedMap->getContinents()[i]->getName() == countryInfo[3]) {
						addedToContinent = true;
						loadedMap->getContinents()[i]->addCountry(country);
						break;
					}
				}

				if (!addedToContinent) {
					fileReader.close();
					throw invalid_argument("Map file is invalid, continent for country '" + countryInfo[0] + "' does not exist.");
				}

				loadedMap->addCountry(country);

				// Add bordering countries for later processing
				vector<string> bordering;
				for (int i = 4; i < countryInfo.size(); i++) {
					bordering.push_back(countryInfo[i]);
				}
				borderingCountries.push_back(bordering);
			}
			else if (countryInfo.size() <= 4) {
				fileReader.close();
				throw invalid_argument("Map file is invalid, missing properties for a territory.");
			}
			else {
				fileReader.close();
				throw invalid_argument("Same country cannot show up multiple times in map file.");
			}
		}

		line = this->readLine(fileReader);
	}

	// Go over every country and add the proper bordering countries
	for (int countryIndex = 0; countryIndex < borderingCountries.size(); countryIndex++) {
		for (int borderingCountryIndex = 0; borderingCountryIndex < borderingCountries[countryIndex].size(); borderingCountryIndex++) {
			string borderingCountryName = borderingCountries[countryIndex][borderingCountryIndex];

			bool addedBorderingCountry = false;
			for (int allCountriesIndex = 0; allCountriesIndex < loadedMap->getCountries().size(); allCountriesIndex++) {
				if (loadedMap->getCountries()[allCountriesIndex]->getName() == borderingCountryName) {
					addedBorderingCountry = true;
					loadedMap->getCountries()[countryIndex]->addBorderingCountry(loadedMap->getCountries()[allCountriesIndex]);
					break;
				}
			}

			if (!addedBorderingCountry) {
				fileReader.close();
				throw invalid_argument("Map file is invalid, bordering country '" + borderingCountryName + "' "
					"for country '" + loadedMap->getCountries()[countryIndex]->getName() + "' does not exist");
			}
		}
	}

	if (!loadedMap->isMapValid()) {
		if (!loadedMap->verifyCountriesBelongToOneContinent()) {
			fileReader.close();
			throw invalid_argument("Some continents own multiple countries.");
		}
		else if (!loadedMap->verifyContinentsAreConnected()) {
			fileReader.close();
			throw invalid_argument("Some of the continents are not subgraphs, verify that every continent is connected.");
		}
		else {
			fileReader.close();
			throw invalid_argument("Some of the countries are not connected, this means the map is disjoint when it should not be.");
		}
	}
	
fileReader.close();
}
*/