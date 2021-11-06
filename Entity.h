#pragma once

class Entity
{
	public:
		Entity(int entityHP);
		~Entity();

		int getEntityHP();

		void setEntityHP(int i);

	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		int entityHP = 0;
};

