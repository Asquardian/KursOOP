#include "class.h"

int menu(sf::RenderWindow& window) {
	Button startGame(1246, 600, 100, 20, "Start");
	Button upgrade(1246, 642, 140, 20, "Upgrade");
	Button exit(1246, 684, 80, 20, "Exit");
	sf::Sprite background, cloud;
	cloud.setScale(0.5, 0.5);
	sf::Texture backTexture, cloudTexture;
	backTexture.loadFromFile("Asset/Menu.png");
	cloudTexture.loadFromFile("Asset/cloud.png");
	cloud.setTexture(cloudTexture);
	float x = 0;
	background.setTexture(backTexture);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		cloud.setPosition(x, 0);
		x += 0.9;
		if (x > 2000) 
			x = -2200;
		if (startGame.click(window) == true) 
			return 0;
		if (upgrade.click(window) == true)
			return 1;
		if (exit.click(window) == true) 
			return 2;
		window.draw(background);
		window.draw(cloud);
		startGame.draw(window);
		upgrade.draw(window);
		exit.draw(window);
		window.display();
	}
	return 2;
}