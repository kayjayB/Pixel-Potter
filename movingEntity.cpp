#include "movingEntity.h"

movingEntity::movingEntity(float entityWidth, float entityHeight, string texture, int lives):
_entityWidth{entityWidth},
_entityHeight{entityHeight},
_lives{lives}
{
		_body.setSize(sf::Vector2f(_entityWidth,_entityHeight));
		if (texture.size()!=0)
		setTexture(texture);
		_body.setOrigin(_entityHeight/2,_entityHeight/2);
}

//movingEntity::~movingEntity() {}

std::vector<std::shared_ptr<movingEntity>> movingEntity::entityList;

floatVector movingEntity::getPosition()
{
	floatVector position;
	position.push_back(0.0);
	position.push_back(0.0);
	
	return position;
}

void movingEntity::setTexture(string texture)
{
	if (texture.size()!=0)
	{
	_Texture.loadFromFile(texture, sf::IntRect(0, 0, 150, 150));
	_body.setTexture(&_Texture);
	}
	
}

sf::RectangleShape movingEntity::getBody() const
{
	return _body;
}

void movingEntity::setPosition(floatVector position)
{
		_body.setPosition(position[0], position[1]);
}

floatVector movingEntity::getBodySize()
{
	floatVector bodySize;
	bodySize.push_back(_entityWidth);
	bodySize.push_back(_entityHeight);
	
	return bodySize;
}

int movingEntity::getLives()
{
	return _lives;
	
}

void movingEntity::setLives(int life)
{
	_lives=life;
//	_body.setFillColor(sf::Color(255,0,0,255));
	
}