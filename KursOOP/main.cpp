#include "head.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1768, 768), "Battle of 2 Opponents");
	window.setVerticalSyncEnabled(true);
	fight(window);
	system("PAUSE");
}