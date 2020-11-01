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
	sf::Sprite Background;
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("Asset/Background.png");
	Background.setTexture(BackgroundTexture);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(Background);
		Player.draw(window);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return Player;
	}
	return Player;
}