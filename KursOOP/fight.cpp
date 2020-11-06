#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <windows.h>
#include "class.h"

int fight(sf::RenderWindow &window) {
	int healthEnemy[3];
	team Player;
	for (int i = 0; i < 3; i++)
		healthEnemy[i] = Player.health[i];
	enemy Shadow(healthEnemy);
	sf::Music battleTheme;
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Asset/videoplayback.ogg");
	sf::SoundBuffer hitbuffer;
	sf::Sound special(buffer);
	hitbuffer.loadFromFile("Asset/hit.ogg");
	sf::Sound hit(hitbuffer);
	battleTheme.openFromFile("Asset/MassDestruction.ogg");
	battleTheme.setLoop(true);
	battleTheme.play();
	sf::Sprite Background;
	sf::Texture BackgroundTexture;
	BackgroundTexture.loadFromFile("Asset/Background.png");
	Background.setTexture(BackgroundTexture);
	Player.setFont();
	Shadow.setFont();
	int characterNum = 3, enemyChoose = 3, charAttack, enemyToAttack = 0;
	int skill = 0, frame = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(Background);
		if (Player.step == true && Player.animPlay == false && Shadow.animPlay == false) {
			if (characterNum == 3) {
				characterNum = Player.onMouse(window, 200, -40);
			}
			if (enemyChoose == 3) {
				enemyChoose = Shadow.onMouse(window, 1100, 40);
			}
			if (enemyChoose != 3 && characterNum != 3) {
				Player.playPrepareToAttack(characterNum);
				skill = Player.chooseSkill(characterNum, window);
				if (skill == 1)
					special.play();
				if (skill > 2)
					hit.play();
				Shadow.health[enemyChoose] = Shadow.health[enemyChoose] - skill;
			}
		}
		if (Player.step == false && Player.animPlay == false && Shadow.animPlay == false && Shadow.alive() == true) {
			if (skill > 0)
				Shadow.playGetDamage(enemyChoose);
			Player.playIdle();
			while (Shadow.health[enemyToAttack] <= 0) {
				enemyToAttack++;
				if (enemyToAttack > 2)
					enemyToAttack = 0;
			}
			Shadow.playAttack(enemyToAttack);
			charAttack = Shadow.AI(Player.health, enemyToAttack);
			Player.playGetDamage(charAttack);
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
		window.display();
		if (Player.animPlay == true || Shadow.animPlay == true) {
			Sleep(200);
			Player.playIdle();
			Shadow.playIdle();
		}
		if (Player.alive() == false) {
			return 10;
		}
		if (Shadow.alive() == false) {
			return rand() % 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 10;
	}
	return 10;
}