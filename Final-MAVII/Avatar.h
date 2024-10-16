#pragma once
#include <Box2d/Box2D.h>

#include "SFML//Graphics.hpp"
#include "SFML//System.hpp"
#include "SFML//Window.hpp"
#include "SFML//Config.hpp"

class Avatar
{
private:
	
	sf::Sprite* m_Sprite;

	b2Body* m_Body;

public:

	Avatar(b2Body* body, sf::Sprite* sprite);

	void Actualizar();

	void Dibujar(sf::RenderWindow& wnd);

};
