#include "Inventory.h"

using namespace sf;
using namespace std;


Inventory::Inventory(Player p, float dim)
{
	texture.loadFromFile("assets/inventory.png");
}

Inventory::~Inventory()
{
}

void Inventory::loadVector(Player p, float dim, RenderWindow& rw, float width, float height, float zoom)
{
	inventoryBar.clear();
	int posX = width / 4;
	int posY = height - dim*(zoom+1);
	Vector2f pos = rw.mapPixelToCoords({ posX,posY });
	IntRect emptyRect(0, 0, dim, dim);
	IntRect potionRect(dim, 0, dim, dim);
	int j = 0;
	for (int i = 0; i < p.getInventory().size(); i++) 
	{
		Sprite s;
		s = Sprite(texture);

		if (p.getInventory()[i] != nullptr) 
		{ s.setTextureRect(potionRect); }
		else { s.setTextureRect(emptyRect); }
		s.setPosition(pos.x + j*dim, pos.y);
		inventoryBar.push_back(s);
		j++;
	}
}

void Inventory::update(Player p, float dim, RenderWindow& rw, float width, float height, float zoom)
{
	loadVector(p,dim,rw,width,height,zoom);
}

void Inventory::drawInventory(sf::RenderWindow& rw)
{
	for (int i = 0; i < inventoryBar.size(); i++)
	{
		rw.draw(inventoryBar[i]);
	}
}
