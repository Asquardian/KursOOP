#include <SFML/Audio.hpp>
#include <windows.h>
#include "class.h"
#include "function.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Battle of 2 Opponents", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	inventory Inventory;
	sf::Sprite Escape;
	Escape.setPosition(227, 300);
	sf::Texture escTexture;
	sf::Music beneathTheMask;
	int positionMenu = NULL;
	bool musicPlay = true, delay = false;
	beneathTheMask.openFromFile("Asset/BeneathTheMask.ogg");
	beneathTheMask.setLoop(true);
	beneathTheMask.play();
	escTexture.loadFromFile("Asset/Escape.png");
	Escape.setTexture(escTexture);
	while (positionMenu != 2) {
		positionMenu = menu(window);
		if (positionMenu == 3 && musicPlay == true && delay == false) {
			beneathTheMask.stop();
			musicPlay = false;
			delay = true;
		}
		if (positionMenu == 3 && musicPlay == false && delay == false) {
			beneathTheMask.play();
			musicPlay = true;
			delay = true;
		}
		if (positionMenu == 0) {
			beneathTheMask.stop();
			int idItem = fight(window, musicPlay);
			if (idItem != 10) {
				beneathTheMask.play();
				window.clear();
				Inventory.get(window, idItem);
				window.display();
				Sleep(5000);
			}
			if (idItem == 10) {
				beneathTheMask.play();
				window.clear();
				window.draw(Escape);
				window.display();
				Sleep(1000);
			}
		}
		if (positionMenu == 1)
			upgradeMenu(window);
	}
}