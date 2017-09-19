#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float currentPlayerAngle)
{
	_minimumRadius=0.0;
	_bulletRadius=480.0f;
	_angle=currentPlayerAngle;
	_body.setSize(sf::Vector2f(10.0f,20.0f));
	_body.setOrigin(5.0f,10.0f);
	_body.setFillColor(sf::Color::Red);
	floatVector initialPosition= getPosition();
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update(float timeElapsed)
{
	float factor = 100*timeElapsed;
	floatVector movement= calculatePosition(factor);
	//_body.setPosition(movement[x], movement[y]);
	setPos(movement);
	_body.setRotation(_angle*(180.0f/pi)+90);
}

floatVector PlayerBullet::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_bulletRadius*cosf(_angle) + _x_center);
	currentPosition.push_back(_bulletRadius*sinf(_angle) + _y_center);
	return currentPosition;
}

void PlayerBullet::setPos(floatVector position)
{
	_body.setPosition(position[0], position[1]);
}


floatVector PlayerBullet::calculatePosition(float factor)
{
	floatVector movement;
	_bulletRadius-=factor;
	if (_bulletRadius<=_minimumRadius)
	{
		_body.setFillColor(sf::Color::Black);
		movement.push_back(4000); // set the bullet off the screen
		movement.push_back(4000);
		return movement;
	}
	movement = getPosition();
	return movement;
}

void PlayerBullet::show(sf::RenderWindow& window)
{
	window.draw(_body);
}