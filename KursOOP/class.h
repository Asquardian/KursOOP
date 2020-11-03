#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class obj {
public:
	sf::Font font;
	int health[3]{};
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			if (health[i] >= 0)
				window.draw(teamCharacter[i]);
	}
	bool alive() {
		int j = 0;
		for (int i = 0; i < 3; i++) {
			if (health[i] < 0)
				j++;
		}
		if (j == 3)
			return false;
		return true;
	}
	sf::Sprite teamCharacter[3];
	sf::Texture character;
};
class team : public obj{
private:
	int power[3]{};
	int minPower[3]{};
	sf::Sprite buff[3]{};
	sf::Texture buffTexture;
	int isBuffed[3]{};
	int inventory[10]{};
	int spirit[3]{};
public:	
	bool step;
	sf::Text hp[3]{}, sp[3]{};
	team(int* healthSet, int* spiritSet, int* powerSet, int* minPowerSet) {		
		buffTexture.loadFromFile("Asset/Effect.png");
		for (int i = 0; i < 3; i++) {
			buff[i].setTexture(buffTexture);
			buff[i].setScale(2, 2);
		}
		buff[0].setPosition(150, 392);
		buff[1].setPosition(190, 484);
		buff[2].setPosition(150, 622);
		for (int i = 0; i < 3; i++)
			isBuffed[i] = 0;
		character.loadFromFile("Asset/Char.png");
		teamCharacter[0].setPosition(200, 372);
		teamCharacter[1].setPosition(240, 464);
		teamCharacter[2].setPosition(200, 600);
		for (int i = 0; i < 3; i++) {
			teamCharacter[i].setTexture(character);
			teamCharacter[i].setTextureRect(sf::IntRect(i * 100, 0, 100, 100));
		}
		for (int i = 0; i < 3; i++) {
			health[i] = healthSet[i];
			spirit[i] = spiritSet[i];
			power[i] = powerSet[i];
			minPower[i] = minPowerSet[i];
		}
	}
	void drawBuff(sf::RenderWindow &window) {
		for (int i = 0; i < 3; i++) {
			if (isBuffed[i] == 1 && health[i] >= 0)
				window.draw(buff[i]);
		}
	}
	int skillPower(int characterNum) {
		srand(time(NULL));
		int skill = rand() % power[characterNum];
		if (skill < minPower[characterNum])
			skill = minPower[characterNum];
		spirit[characterNum] = spirit[characterNum] - 10;
		return skill;
	}
	int onMouse(sf::RenderWindow& window) {
		if (sf::IntRect(200, 372, 100, 100).contains(sf::Mouse::getPosition(window)) && health[0] >= 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 0;
		}
		if (sf::IntRect(240, 462, 100, 100).contains(sf::Mouse::getPosition(window)) && health[1] >= 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 1;
		}
		if (sf::IntRect(200, 600, 100, 100).contains(sf::Mouse::getPosition(window)) && health[2] >= 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 2;
		}
		return 3;
	}
	int chooseSkill(int characterNum, sf::RenderWindow &window) {
		int characterEffect = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && spirit[characterNum] - 10 > 0) {
			step = false;
			return skillPower(characterNum);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && spirit[characterNum] - 5 > 0) {
			switch (characterNum) {
			case 0:
				spirit[characterNum] -= 5;
				power[characterNum] += 20;
				step = false;
				isBuffed[0] = 1;
				return 1;
				break;
			case 1:
				spirit[characterNum] -= 5;
				while (characterEffect == 3) {
					characterEffect = onMouse(window);
				}
				health[characterEffect] += 45;
				power[1] += 5;
				step = false;
				isBuffed[1] = 1;
				return 1;
				break;
			case 2:
				health[characterNum] -= 90;
				spirit[characterNum] -= 5;
				power[characterNum] += 100;
				isBuffed[2] = 1;
				step = false;
				return 1;
				break;
			default:
				return 0; 
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			step = false;
		return 0;
	}
	void setFont() {
		font.loadFromFile("Asset/FontC.TTF");
		hp[0].setPosition(150, 370);
		hp[1].setPosition(190, 462);
		hp[2].setPosition(150, 598);
		sp[0].setPosition(150, 348);
		sp[1].setPosition(190, 440);
		sp[2].setPosition(150, 576);
		for (int i = 0; i < 3; i++) {
			hp[i].setFont(font);
			sp[i].setFont(font);
			hp[i].setCharacterSize(20);
			sp[i].setCharacterSize(20);
		}
	}
	void stat(sf::RenderWindow &window) {
		std::ostringstream hpString[3], spString[3];
		for (int i = 0; i < 3; i++) {
			hpString[i] << health[i];
			spString[i] << spirit[i];
		}
		for (int i = 0; i < 3; i++) {
			if (health[i] > 0) {
				hp[i].setString("HP: " + hpString[i].str());
				sp[i].setString("SP: " + spString[i].str());
				window.draw(hp[i]);
				window.draw(sp[i]);
			}
		}
	}
};
class enemy : public obj {
private:
	sf::Text hp[3]{};
public:
	int healTime;
	enemy(int* healthSet) {
		character.loadFromFile("Asset/Shadow.png");
		healTime = 0;
		teamCharacter[0].setPosition(1100, 372);
		teamCharacter[1].setPosition(1060, 464);
		teamCharacter[2].setPosition(1100, 600);
		for (int i = 0; i < 3; i++) {
			teamCharacter[i].setTexture(character);
		}
		for (int i = 0; i < 3; i++) {
			health[i] = healthSet[i];
		}
	}
	int AI(int* healthPlayer, int enemyToAttack) {
		int i, charToAttack = 0;
		int minHealth = healthPlayer[0];
		for (int j = 0; j < 3; j++) {
			if (healthPlayer[j] > minHealth)
				minHealth = healthPlayer[j];
		}
		if (health[enemyToAttack] < 50 && healTime < 3) {
			healTime++;
			health[enemyToAttack] += 40;
			return 5;
		}
		for (i = 0; i < 3; i++) {
			if (healthPlayer[i] <= minHealth && healthPlayer[i] >= 0) {
				minHealth = healthPlayer[i];
				charToAttack = i;
			}
		}
		return charToAttack;
	}
	int onMouse(sf::RenderWindow& window) {
		if (sf::IntRect(1100, 372, 100, 100).contains(sf::Mouse::getPosition(window)) && health[0] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 0;
		}
		if (sf::IntRect(1060, 464, 100, 100).contains(sf::Mouse::getPosition(window)) && health[1] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 1;
		}
		if (sf::IntRect(1100, 600, 100, 100).contains(sf::Mouse::getPosition(window)) && health[2] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 2;
		}
		return 3;
	}
	void setFont() {
		font.loadFromFile("Asset/FontC.TTF");
		hp[0].setPosition(1200, 370);
		hp[1].setPosition(1160, 462);
		hp[2].setPosition(1200, 598);
		for (int i = 0; i < 3; i++) {
			hp[i].setFont(font);
			hp[i].setCharacterSize(20);
		}
	}
	void stat(sf::RenderWindow& window) {
		std::ostringstream hpString[3];
		for (int i = 0; i < 3; i++) {
			hpString[i] << health[i];
		}
		for (int i = 0; i < 3; i++) {
			if (health[i] > 0) {
				hp[i].setString("HP: "+ hpString[i].str());
				window.draw(hp[i]);
			}
		}
	}
};
