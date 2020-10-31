#pragma once
#include <SFML/Graphics.hpp>

class team {
private:
	int inventory[10];
	int spirit[2];
public:
	int health[2];
	int power[2];
	int minPower[2];
	sf::Sprite teamCharacter[2];
	sf::Texture character;
	void setTeam() {
		character.loadFromFile("Asset/Char.png");
		for (int i = 0; i < 2; i++) {
			teamCharacter[i].setTexture(character);
			teamCharacter[i].setTextureRect(sf::IntRect(i * 100, 0, 100, 100));
		}
	}
	int skillPower(int characterNum) {
		srand(time(NULL));
		int skill = rand() % power[characterNum];
		if (skill < minPower[characterNum])
			skill = minPower[characterNum];
		return skill;
	}
	team(int* healthSet, int* spiritSet, int* powerSet, int* minPowerSet) {
		for (int i = 0; i < 2; i++) {
			health[i] = healthSet[i];
			spirit[i] = spiritSet[i];
			power[i] = powerSet[i];
			minPower[i] = minPowerSet[i];
		}
	};
};

team fight(sf::RenderWindow &window);