#pragma once
#include <SFML/Graphics.hpp>

class team {
private:
	int inventory[10]{};
	int health[3]{};
	int power[3]{};
	int minPower[3]{};
	int spirit[3]{};
	void setPlayer() {
		character.loadFromFile("Asset/Char.png");
		for (int i = 0; i < 2; i++) {
			teamCharacter[i].setTexture(character);
			teamCharacter[i].setTextureRect(sf::IntRect(i * 100, 0, 100, 100));
		}
	}
public:	
	sf::Sprite teamCharacter[3];
	sf::Texture character;
	team(int* healthSet, int* spiritSet, int* powerSet, int* minPowerSet) {
		teamCharacter[0].setPosition(100, 192);
		teamCharacter[1].setPosition(120, 384);
		teamCharacter[2].setPosition(100, 576);
		for (int i = 0; i < 2; i++) {
			health[i] = healthSet[i];
			spirit[i] = spiritSet[i];
			power[i] = powerSet[i];
			minPower[i] = minPowerSet[i];
		}
	};
	void setTeam() {
		setPlayer();
	}
	int skillPower(int characterNum) {
		srand(time(NULL));
		int skill = rand() % power[characterNum];
		if (skill < minPower[characterNum])
			skill = minPower[characterNum];
		return skill;
	}
};

team fight(sf::RenderWindow &window);