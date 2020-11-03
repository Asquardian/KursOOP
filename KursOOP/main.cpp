#include "function.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Battle of 2 Opponents");
	window.setVerticalSyncEnabled(true);
	upgradeMenu(window);
	fight(window);
}