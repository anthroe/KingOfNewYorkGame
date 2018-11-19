#include "GameStatsObserver.h"

void GameStatsObserver::update() {
	TextTable::TextTable regionStatsTable('-', '|', '+');
	regionStatsTable.add("Region Name");
	regionStatsTable.add("# Players");
	regionStatsTable.add("# Buildings");
	regionStatsTable.add("# Units");
	regionStatsTable.endOfRow();

	vector<Region> regions = gameStart::mapRegions;
	vector<player> players = gameStart::playersInGame;
	for (int i = 0; i < regions.size(); i++) {
		for (int j = 0; j < players.size(); j++) {
			if (regions[i] == players[j].getRegion()) {
				regions[i].increasePlayerCount();
			}
		}
	}

	for (Region region : regions) {
		regionStatsTable.add(region.getName());
		regionStatsTable.add(to_string(region.getPlayerCount()));

		int numOfBuildingsInRegion = 0;
		for (vector<int> unit : region.getBuildings()) {
			if (!unit.empty())
				numOfBuildingsInRegion++;
		}
		regionStatsTable.add(to_string(numOfBuildingsInRegion));

		int numOfUnitsInRegion = 0;
		for (vector<int> unit : region.getUnits()) {
			if (!unit.empty())
				numOfUnitsInRegion++;
		}
		regionStatsTable.add(to_string(numOfUnitsInRegion));
		regionStatsTable.endOfRow();
	}

	regionStatsTable.setAlignment(1, TextTable::TextTable::Alignment::RIGHT);
	regionStatsTable.setAlignment(2, TextTable::TextTable::Alignment::RIGHT);
	regionStatsTable.setAlignment(3, TextTable::TextTable::Alignment::RIGHT);

	TextTable::TextTable playerStatsTable('-', '|', '+');
	playerStatsTable.add("Player Name");
	playerStatsTable.add("Energy");
	playerStatsTable.add("HP");
	playerStatsTable.add("VP");
	playerStatsTable.endOfRow();

	for (player plr : gameStart::playersInGame) {
		playerStatsTable.add(plr.getName());
		playerStatsTable.add(to_string(plr.getEnergy()));
		playerStatsTable.add(to_string(plr.getMonsterCard()->getHP()));
		playerStatsTable.add(to_string(plr.getMonsterCard()->getVP()));
		playerStatsTable.endOfRow();
	}

	playerStatsTable.setAlignment(1, TextTable::TextTable::Alignment::RIGHT);
	playerStatsTable.setAlignment(2, TextTable::TextTable::Alignment::RIGHT);
	playerStatsTable.setAlignment(3, TextTable::TextTable::Alignment::RIGHT);

	displayStats(regionStatsTable, playerStatsTable);
}

void GameStatsObserver::displayStats(TextTable::TextTable region, TextTable::TextTable player) {
	cout << "REGION STATS" << endl;
	cout << region << endl;

	cout << "PLAYER STATS" << endl;
	cout << player << endl;
}