#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

class obj {
public:
	sf::Font font;
	int health[3]{};
	bool animPlay = NULL;
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			if (health[i] > 0)
				window.draw(teamCharacter[i]);
	}
	bool alive() {
		int j = 0;
		for (int i = 0; i < 3; i++) {
			if (health[i] <= 0)
				j++;
		}
		if (j == 3)
			return false;
		return true;
	}
	int onMouse(sf::RenderWindow& window, float X, float forMid) {
		if (sf::IntRect(X, 372, 100, 100).contains(sf::Mouse::getPosition(window)) && health[0] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 0; //1100 enem and 200
		}
		if (sf::IntRect(X - forMid, 464, 100, 100).contains(sf::Mouse::getPosition(window)) && health[1] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 1;
		}
		if (sf::IntRect(X, 600, 100, 100).contains(sf::Mouse::getPosition(window)) && health[2] > 0) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return 2;
		}
		return 3;
	}
	sf::Sprite teamCharacter[3];
	sf::Texture character;
};
class team : public obj{
private:
	sf::Sprite buff[3]{};
	sf::Texture buffTexture;
	int isBuffed[3]{};
public:
	int power[3]{};
	int minPower[3]{};
	int spirit[3]{};
	bool step = NULL;
	sf::Text hp[3]{}, sp[3]{}, pw[3]{}, minpw[3]{};
	team() {	
		std::ifstream savedTeam("Save/TeamStat.save");
		for (int i = 0; i <= 2; i++) {
			animPlay = false;
			step = true;
			savedTeam >> health[i];
			savedTeam >> spirit[i];
			savedTeam >> power[i];
			savedTeam >> minPower[i];
		}
		savedTeam.close();
		buffTexture.loadFromFile("Asset/Effect.png");
		for (int i = 0; i < 3; i++) {
			buff[i].setTexture(buffTexture);
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
	}
	void drawBuff(sf::RenderWindow &window) {
		for (int i = 0; i < 3; i++) {
			if (isBuffed[i] == 1 && health[i] > 0)
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
					characterEffect = onMouse(window, 200, -40);
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
		pw[0].setPosition(150, 392);
		pw[1].setPosition(190, 484);
		pw[2].setPosition(150, 620);
		minpw[0].setPosition(150, 414);
		minpw[1].setPosition(190, 506);
		minpw[2].setPosition(150, 642);
		for (int i = 0; i < 3; i++) {
			hp[i].setFont(font);
			sp[i].setFont(font);
			pw[i].setFont(font);
			minpw[i].setFont(font);
			hp[i].setCharacterSize(20);
			sp[i].setCharacterSize(20);
			pw[i].setCharacterSize(20);
			minpw[i].setCharacterSize(20);
		}
	}
	void playPrepareToAttack(int charNum) {
		teamCharacter[charNum].setTextureRect(sf::IntRect(charNum * 100, 100, 100, 100));
	}
	void playIdle() {
		for (int i = 0; i < 3; i++)
			teamCharacter[i].setTextureRect(sf::IntRect(i * 100, 0, 100, 100));
		animPlay = false;
	}
	void playGetDamage(int charNum) {
		animPlay = true;
		teamCharacter[charNum].setTextureRect(sf::IntRect(charNum * 100, 200, 100, 100));
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
	void fullStat(sf::RenderWindow& window){
		stat(window);
		std::ostringstream pwString[3], minpwString[3];
		for (int i = 0; i < 3; i++) {
			pwString[i] << power[i];
			minpwString[i] << minPower[i];
		}
		for (int i = 0; i < 3; i++) {
			if (health[i] > 0) {
				pw[i].setString("PW: " + pwString[i].str());
				minpw[i].setString("MP: " + minpwString[i].str());
				window.draw(pw[i]);
				window.draw(minpw[i]);
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
		animPlay = false;
		healTime = 0;
		teamCharacter[0].setPosition(1100, 372);
		teamCharacter[1].setPosition(1060, 464);
		teamCharacter[2].setPosition(1100, 600);
		for (int i = 0; i < 3; i++) {
			teamCharacter[i].setTexture(character);
			teamCharacter[i].setTextureRect(sf::IntRect(0, 0, 100, 100));
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
			if (healthPlayer[i] <= minHealth && healthPlayer[i] > 0) {
				minHealth = healthPlayer[i];
				charToAttack = i;
			}
		}
		return charToAttack;
	}
	void playIdle() {
		for (int i = 0; i < 3; i++) {
			teamCharacter[i].setTextureRect(sf::IntRect(0, 0, 100, 100));
		}
		animPlay = false;
	}
	void playAttack(int enemNum) {
		teamCharacter[enemNum].setTextureRect(sf::IntRect(100, 0, 100, 100));
		animPlay = true;
	}
	void playGetDamage(int enemNum) {
		teamCharacter[enemNum].setTextureRect(sf::IntRect(200, 0, 100, 100));
		animPlay = true;
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
class Button {
private:
	sf::Text buttonText;
	sf::Font font;
public:
	float posX, posY, endX, endY;
	Button(float x, float y, float xend, float yend) {
		posX = x;
		posY = y;
		endX = xend;
		endY = yend;
	};
	Button(float x, float y, float xend, float yend, std::string text) {
		posX = x;
		posY = y;
		endX = xend;
		endY = yend;
		font.loadFromFile("Asset/FontC.ttf");
		buttonText.setString(text);
		buttonText.setPosition(x, y);
		buttonText.setFont(font);
		buttonText.setCharacterSize(20);
	};
	void draw(sf::RenderWindow& window) {
		window.draw(buttonText);
	}
	bool click(sf::RenderWindow& window) {
		if (sf::IntRect(posX, posY, endX, endY).contains(sf::Mouse::getPosition(window))) {
			buttonText.setFillColor(sf::Color(148, 148, 148));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return true;
		}
		else
			buttonText.setFillColor(sf::Color(255, 255, 255));
		return false;
	}
};
class inventory {
private:
	float x, y;
	std::string nameId[3]{};
	sf::Text item[3]{};
	sf::Font font;
	sf::Text win;
public:
	int id[3]{};
	inventory() {
		std::ifstream savedInventory("Save/inventory.save");
		font.loadFromFile("Asset/FontC.TTF");
		for (int i = 0; i < 3; i++) {
			savedInventory >> id[i];
			item[i].setFont(font);
			item[i].setCharacterSize(20);
		}
		nameId[0] = "Life";
		nameId[1] = "Power";
		nameId[2] = "Spirit";
		x = 520, y = 200;
	}
	void get(sf::RenderWindow& window, int num) {
		id[num] = id[num] + 1;
		win.setCharacterSize(30);
		win.setFont(font);
		win.setPosition(380, 384);
		win.setString("You've got Essension of " + nameId[num]);
		window.draw(win);
		std::ofstream inv("Save/inventory.save");
		for (int i = 0; i < 3; i++) {
			inv << id[i] << " ";
		}
		inv.close();
	}
	void set() {
		for (int i = 0; i < 3; i++) {
			std::ostringstream idStr[3];
			for (int i = 0; i < 3; i++) {
				idStr[i] << id[i];
			}
			item[i].setString("Essension of " + nameId[i] + ": " + idStr[i].str());
		}
	}
	void setPosition() {
		for (int i = 0; i < 3; i++){
			item[i].setPosition(x, y);
			y -= 22;
		}
	}
	void show(sf::RenderWindow& window) {
		for(int i = 0; i < 3; i++)
			window.draw(item[i]);
	}
};