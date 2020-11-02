#include <iostream>
#include <fstream>
#include "head.h"

team fight(sf::RenderWindow &window) {
	int healthSet[3], spiritSet[3], powerSet[3], minPowerSet[3], healthEnemy[3], powerEnemy[3], minPowerEnemy[3];
	std::ifstream savedTeam("Save/TeamStat.save");
	srand(time(NULL));
	if (!savedTeam) {
		exit(0);
	}
	for (int i = 0; i <= 2; i++) {
		savedTeam >> healthSet[i];
		healthEnemy[i] = rand()%healthSet[i];
		if (healthEnemy[i] < 60)
			healthEnemy[i] = 60;
		savedTeam >> spiritSet[i];
		savedTeam >> powerSet[i];
		powerEnemy[i] = rand() % powerSet[i];
		if (powerEnemy[i] < 50)
			powerEnemy[i] = 50;
		savedTeam >> minPowerSet[i];
		minPowerEnemy[i] = rand() % minPowerSet[i];
		if (minPowerEnemy[i] < 30)
			minPowerEnemy[i] = 30;
	}
	team Player(healthSet, spiritSet, powerSet, minPowerSet);
	enemy Shadow(healthEnemy, powerEnemy, minPowerEnemy);
	sf::Sprite Background;
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("Asset/Background.png");
	Background.setTexture(BackgroundTexture);
	Player.setFont();
	Shadow.setFont();
	sf::Text turn("Your turn!", Player.font, 20);
	turn.setPosition(200, 200);
	Player.step = true;
	int characterNum = 3;
	int skill = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(Background);
		if (Player.step == true) {
			if (characterNum == 3)
				characterNum = Player.onMouse(window);
			skill = Player.chooseSkill(characterNum, window);
			Shadow.health[0] -= skill;
			window.draw(turn);
		}
		Player.draw(window);
		Player.stat(window);
		Shadow.draw(window);
		Shadow.stat(window);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return Player;
	}
	return Player;
}