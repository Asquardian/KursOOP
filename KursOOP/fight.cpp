#include <iostream>
#include <fstream>
#include "class.h"

int fight(sf::RenderWindow &window) {
	int healthEnemy[3];
	team Player;
	for (int i = 0; i < 3; i++)
		healthEnemy[i] = Player.health[i];
	enemy Shadow(healthEnemy);
	sf::Sprite Background;
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("Asset/Background.png");
	Background.setTexture(BackgroundTexture);
	Player.setFont();
	Shadow.setFont();
	sf::Text turn("Your turn!", Player.font, 20);
	turn.setPosition(200, 200);
	sf::Text win("You win!", Player.font, 40);
	win.setPosition(683, 384);
	sf::Text lose("You lose!", Player.font, 40);
	win.setPosition(683, 384);
	Player.step = true;
	int characterNum = 3, enemyChoose = 3, charAttack, enemyToAttack = 0;
	int skill = 0, wait;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(Background);
		if (Player.step == true) {
			if (characterNum == 3) {
				characterNum = Player.onMouse(window);
			}
			if (enemyChoose == 3) {
				enemyChoose = Shadow.onMouse(window);
			}
			if (enemyChoose != 3 && characterNum != 3) {
				skill = Player.chooseSkill(characterNum, window);
				Shadow.health[enemyChoose] = Shadow.health[enemyChoose] - skill;
			}
			window.draw(turn);
		}
		else {
			while (Shadow.health[enemyToAttack] < 0) {
				enemyToAttack++;
				if (enemyToAttack > 2)
					enemyToAttack = 0;
			}
			charAttack = Shadow.AI(Player.health, enemyToAttack);
			if (charAttack != 5) {
				Player.health[charAttack] = Player.health[charAttack] - 40;
			}
			enemyToAttack++;
			characterNum = 3;
			enemyChoose = 3;
			Player.step = true;
		}
		Player.draw(window);
		Player.stat(window);
		Player.drawBuff(window);
		Shadow.draw(window);
		Shadow.stat(window);
		if (Player.alive() == false) {
			return 10;
		}
		if (Shadow.alive() == false) {
			return rand() % 8;
		}
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 11;
	}
	return 10;
}