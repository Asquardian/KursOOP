#pragma once
#include <SFML/Graphics.hpp>

class team {
private:
	int inventory[10]{};
	int health[3]{};
	int power[3]{};
	int minPower[3]{};
	int spirit[3]{};
public:	
	sf::Sprite teamCharacter[3];
	sf::Texture character;
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
		return skill;
	}
	void draw(sf::RenderWindow &window) {
		for (int i = 0; i < 3; i++)
			window.draw(teamCharacter[i]);
	}
};

team fight(sf::RenderWindow &window);