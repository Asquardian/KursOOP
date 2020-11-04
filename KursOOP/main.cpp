#include "function.h"
#include "class.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Battle of 2 Opponents");
	window.setVerticalSyncEnabled(true);
	inventory Inventory;
	int idItem = fight(window);
	if (idItem != 10)
		Inventory.get(idItem);
	upgradeMenu(window);
}