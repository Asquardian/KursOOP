#include <SFML/Audio.hpp>
#include "class.h"
#include "function.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Battle of 2 Opponents");
	window.setVerticalSyncEnabled(true);
	inventory Inventory;
	sf::Sprite Escape;
	sf::Texture escTexture;
	sf::Music beneathTheMask;
	beneathTheMask.openFromFile("Asset/BeneathTheMask.ogg");
	beneathTheMask.setLoop(true);
	beneathTheMask.play();
	escTexture.loadFromFile("Asset/Escape.png");
	int positionMenu = NULL;
	while (positionMenu != 2) {
		positionMenu = menu(window);
		if (positionMenu == 0) {
			beneathTheMask.stop();
			int idItem = fight(window);
			if (idItem != 10) {
				beneathTheMask.play();
				Inventory.get(idItem);
			}
			if (idItem == 10) {
				beneathTheMask.play();
				window.draw(Escape);
				window.display();
			}
		}
		if (positionMenu == 1)
			upgradeMenu(window);
	}
}