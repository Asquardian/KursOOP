#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class obj {
public:
	int health[3]{};
	int power[3]{};
	int minPower[3]{};
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			window.draw(teamCharacter[i]);
	}
	sf::Sprite teamCharacter[3];
	sf::Texture character;
};
class team : public obj{
private:
	int inventory[10]{};
	int spirit[3]{};
public:	
	sf::Font font;
	sf::Text hp[3]{}, sp[3]{};
	team(int* healthSet, int* spiritSet, int* powerSet, int* minPowerSet) {		
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
	int skillPower(int characterNum) {
		srand(time(NULL));
		int skill = rand() % power[characterNum];
		if (skill < minPower[characterNum])
			skill = minPower[characterNum];
		spirit[characterNum] = spirit[characterNum] - 10;
		return skill;
	}
	int onMouse(sf::RenderWindow& window) {
		if (sf::IntRect(200, 372, 100, 100).contains(sf::Mouse::getPosition(window))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 0;
		}
		if (sf::IntRect(240, 462, 100, 100).contains(sf::Mouse::getPosition(window))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 1;
		}
		if (sf::IntRect(200, 600, 100, 100).contains(sf::Mouse::getPosition(window))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 2;
		}
		return 3;
	}
	int chooseSkill(int characterNum, sf::RenderWindow &window) {
		int skill, characterEffect;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && spirit[characterNum] - 10 > 0) {
			return skillPower(characterNum);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && spirit[characterNum] - 5 > 0) {
			switch (characterNum) {
			case 0:
				spirit[characterNum] -= 5;
				power[characterNum] += 10;
				return 1;
				break;
			case 1:
				spirit[characterNum] -= 5;
				characterEffect = onMouse(window);
				health[characterEffect] += 20;
				return 1;
				break;
			case 2:
				health[characterNum] -= 100;
				spirit[characterNum] -= 5;
				power[characterNum] += 100;
				return 1;
				break;
			default:
				return 0;
			}
		}
		return 0;
	}
	void setFont() {
		font.loadFromFile("Asset/FontC.TTF");
		hp[0].setPosition(190, 370);
		hp[1].setPosition(230, 462);
		hp[2].setPosition(190, 598);
		sp[0].setPosition(190, 348);
		sp[1].setPosition(230, 440);
		sp[2].setPosition(190, 576);
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
			hp[i].setString(hpString[i].str());
			sp[i].setString(spString[i].str());
			window.draw(hp[i]);
			window.draw(sp[i]);
		}
	}
};

class enemy : public obj {
public:
	enemy(int* healthSet, int* powerSet, int* minPowerSet) {
		character.loadFromFile("Asset/Char.png");
		teamCharacter[0].setPosition(1100, 372);
		teamCharacter[1].setPosition(1060, 464);
		teamCharacter[2].setPosition(1100, 600);
		for (int i = 0; i < 3; i++) {
			teamCharacter[i].setTexture(character);
			teamCharacter[i].setTextureRect(sf::IntRect(i * 100, 0, 100, 100));
		}
		for (int i = 0; i < 3; i++) {
			health[i] = healthSet[i];
			power[i] = powerSet[i];
			minPower[i] = minPowerSet[i];
		}
	}
};

team fight(sf::RenderWindow &window);