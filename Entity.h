#pragma once

class Entity
{
	public:
		Entity(int entityHP, sf::Vector2f pos);
		~Entity();

		int getEntityHP();

	protected:
		sf::Sprite sprite;
		sf::Vector2f position = { 0,0 };
		int entityHP = 0;
};

