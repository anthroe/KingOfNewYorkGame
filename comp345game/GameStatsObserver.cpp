#include "GameStatsObserver.h"

void GameStatsObserver::update() {
	TextTable regionStatsTable('-', '|', '+');
	regionStatsTable.add("Region Name");
	regionStatsTable.add("# Players");
	regionStatsTable.add("# Buildings");
	regionStatsTable.add("# Units");
	regionStatsTable.endOfRow();

	for (Region region : gameStart::mapRegions) {
		regionStatsTable.add(region.getName());
		regionStatsTable.add(region.getPlayerCount() + "");

		int numOfBuildingsInRegion = 0;
		for (vector<int> unit : region.getBuildings()) {
			if (!unit.empty())
				numOfBuildingsInRegion++;
		}
		regionStatsTable.add(numOfBuildingsInRegion + "");

		int numOfUnitsInRegion = 0;
		for (vector<int> unit : region.getUnits()) {
			if (!unit.empty())
				numOfUnitsInRegion++;
		}
		regionStatsTable.add(numOfUnitsInRegion + "");
		regionStatsTable.endOfRow();
	}

	regionStatsTable.setAlignment(1, TextTable::Alignment::RIGHT);
	regionStatsTable.setAlignment(2, TextTable::Alignment::RIGHT);
	regionStatsTable.setAlignment(3, TextTable::Alignment::RIGHT);

	TextTable playerStatsTable('-', '|', '+');
	playerStatsTable.add("Player Name");
	playerStatsTable.add("Energy");
	playerStatsTable.add("HP");
	playerStatsTable.add("VP");
	playerStatsTable.endOfRow();

	for (player plr : gameStart::playersInGame) {
		playerStatsTable.add(plr.getName() + "");
		playerStatsTable.add(plr.getEnergy() + "");
		playerStatsTable.add(plr.getMonsterCard()->getHP() + "");
		playerStatsTable.add(plr.getMonsterCard()->getVP() + "");
		playerStatsTable.endOfRow();
	}

	playerStatsTable.setAlignment(1, TextTable::Alignment::RIGHT);
	playerStatsTable.setAlignment(2, TextTable::Alignment::RIGHT);
	playerStatsTable.setAlignment(3, TextTable::Alignment::RIGHT);

	displayStats(regionStatsTable, playerStatsTable);
}

void GameStatsObserver::displayStats(TextTable region, TextTable player) {
	cout << "REGION STATS" << endl;
	cout << region << endl;

	cout << "PLAYER STATS" << endl;
	cout << player << endl;
}