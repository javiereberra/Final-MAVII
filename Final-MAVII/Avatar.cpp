#include "Avatar.h"

Avatar::Avatar(b2Body* body, sf::Sprite* sprite) : m_Body(body), m_Sprite(sprite)
{

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	for (b2Fixture* f = m_Body->GetFixtureList(); f; f = f->GetNext())
		aabb.Combine(f->GetAABB(0));

	float sizeX = aabb.GetExtents().x * 2.0 / m_Sprite->getTexture()->getSize().x;
	float sizeY = aabb.GetExtents().y * 2.0 / m_Sprite->getTexture()->getSize().y;
	m_Sprite->setScale(sizeX, sizeY);
	m_Sprite->setOrigin(sf::Vector2f(m_Sprite->getTexture()->getSize().x / 2.0f, m_Sprite->getTexture()->getSize().y / 2.0f));
	b2Vec2 pos = m_Body->GetPosition();
	m_Sprite->setPosition(sf::Vector2f(pos.x, pos.y));

}

void Avatar::Actualizar()
{
	b2Vec2 pos = m_Body->GetPosition();
	m_Sprite->setPosition(sf::Vector2f(pos.x, pos.y));

	float ang = m_Body->GetAngle();

	m_Sprite->setRotation(ang * 180 / 3.1415f);


}

void Avatar::Dibujar(sf::RenderWindow& wnd)
{

	wnd.draw(*m_Sprite);
}
