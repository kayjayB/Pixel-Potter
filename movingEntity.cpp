#include "movingEntity.h"

movingEntity::movingEntity(float entityWidth, float entityHeight, string texture)
{
		_body.setSize(sf::Vector2f(entityWidth,entityHeight));
		setTexture(texture);
		_body.setOrigin(entityWidth/2,entityHeight/2);
}

floatVector movingEntity::getPosition()
{
	floatVector position;
	position.push_back(0.0);
	position.push_back(0.0);
	
	return position;
}

void movingEntity::setTexture(string texture)
{
	_Texture.loadFromFile(texture, sf::IntRect(0, 0, 150, 150));
	_body.setTexture(&_Texture);
}

sf::RectangleShape movingEntity::getBody() const
{
	return _body;
}