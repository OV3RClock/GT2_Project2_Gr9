#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Item 
{
	public:
		Item();
		Item(float healAmount);
		~Item();

		float getHealAmount();
		sf::Sprite getSprite();

		void setHealAmount(float f);
		void setPosition(sf::Vector2f v);

		void drawItem(sf::RenderWindow& rw);

	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		float healAmount = 50;
};