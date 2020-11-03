#include "class.h"
#include <fstream>

void upgradeMenu(sf::RenderWindow& window) {
	int healthSet[3], spiritSet[3], powerSet[3], minPowerSet[3];
	std::ifstream savedTeam("Save/TeamStat.save");
	if (!savedTeam) {
		exit(0);
	}
	for (int i = 0; i <= 2; i++) {
		savedTeam >> healthSet[i];
		savedTeam >> spiritSet[i];
		savedTeam >> powerSet[i];
		savedTeam >> minPowerSet[i];
	}
	savedTeam.close();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
	}
}