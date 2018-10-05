//#include "cardtest.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Region.h"
#include "Maploader.h"


using namespace std;

int main() {
	//cards::main();

	//ifstream inFile("test.map");
	//if (!inFile) {
	//	cout << "Unable to open file";
	//	//exit(1); // terminate with error
	//}

	//string line;
	//string city;
	//string id;
	//vector<Region> allRegions;

	//getline(inFile, line);
	//// Verify that [Map] exists but skip over it to continents
	//if (line != "[City]") {
	//	inFile.close();
	//	throw invalid_argument("Map file is invalid, missing [City] section.");
	//}

	////Register all regions
	//getline(inFile, city);

	//while (line != "[Regions]" && !inFile.eof()) {
	//	getline(inFile, line);
	//}

	//while (inFile >> line) {
	//	Region temp(line);
	//	getline(inFile, id);
	//	cout << id;
	//	allRegions.push_back(temp);
	//}

	//for (int i = 0; i < allRegions.size(); i++) {
	//	cout << allRegions[i].getName() << endl;
	//}
	/*
	try {
		Maploader loader("./Map/maps/World(small).map");
		Map* currentMap = loader.getMap();
		cout << "The map is completely connected, and the continents are subgraphs." << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}*/

	Region canada("canada");
	Region usa("usa");
	Region mexico("mexico");

	canada.addNearbyRegions({usa, mexico});
	usa.addNearbyRegions({canada, mexico});
	mexico.addNearbyRegions({ canada, usa });

	vector<Region> randomRegions{canada, usa, mexico};
	Map map1(randomRegions);

	map1.checkConnection();

	return 0;
}