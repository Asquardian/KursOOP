#include "class.h"
#include "function.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Battle of 2 Opponents");
	window.setVerticalSyncEnabled(true);
	inventory Inventory;
	sf::Sprite Escape;
	sf::Texture escTexture;
	escTexture.loadFromFile("Asset/Escape.png");
	int positionMenu = NULL;
	while (positionMenu != 2) {
		positionMenu = menu(window);
		if (positionMenu == 0) {
			int idItem = fight(window);
			if (idItem != 10)
				Inventory.get(idItem);
			if (idItem == 10) {
				window.draw(Escape);
				window.display();
			}
		}
		if (positionMenu == 1)
			upgradeMenu(window);
	}
}