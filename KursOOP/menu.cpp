#include "class.h"

int menu(sf::RenderWindow& window) {
	Button startGame(1246, 600, 100, 20, "Start");
	Button upgrade(1246, 642, 140, 20, "Upgrade");
	Button exit(1246, 684, 80, 20, "Exit");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		if (startGame.click(window) == true) 
			return 0;
		if (upgrade.click(window) == true)
			return 1;
		if (exit.click(window) == true) 
			return 2;
		startGame.draw(window);
		upgrade.draw(window);
		exit.draw(window);
		window.display();
	}
	return 2;
}