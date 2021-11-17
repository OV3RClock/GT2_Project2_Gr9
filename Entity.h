#pragma once

class Entity
{
	public:
		Entity(float entityHP, sf::Vector2f pos);
		~Entity();

		int getEntityHP();
		bool isAlive();
	protected:
		sf::Sprite sprite;
		sf::Vector2f position = { 0,0 };
		float entityHP = 0;

};


