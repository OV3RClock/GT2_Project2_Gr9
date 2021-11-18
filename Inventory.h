#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Player.h"

class Inventory
{
	public:
		Inventory(Player p, float dim);
		~Inventory();

		void loadVector(Player p, float dim, sf::RenderWindow& rw, float width, float height, float zoom);

		void update(Player p, float dim, sf::RenderWindow& rw, float width, float height, float zoom);

		void drawInventory(sf::RenderWindow& rw);

	protected:
		sf::Texture texture;
		sf::Vector2f position = { 0,0 };
		float size = 8;
		std::vector<sf::Sprite> inventoryBar;
};