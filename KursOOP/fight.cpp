#include <iostream>
#include <fstream>
#include "head.h"

team fight(sf::RenderWindow &window) {
	int healthSet[2], spiritSet[2], powerSet[2], minPowerSet[2];
	std::ifstream savedTeam("Save/TeamStat.save");
	if (!savedTeam) {
		exit(0);
	}
	for (int i = 0; i < 2; i++) {
		savedTeam >> healthSet[i];
		savedTeam >> spiritSet[i];
		savedTeam >> powerSet[i];
		savedTeam >> minPowerSet[i];
	}
	team Player(healthSet, spiritSet, powerSet, minPowerSet);
	Player.setTeam();
	while (window.isOpen()) {
		return Player;
	}
	return Player;
}