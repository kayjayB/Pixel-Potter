#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float currentPlayerAngle):
movingEntity(10.0,20.0,""),
_minimumRadius{0.0},
_bulletRadius{480.0f},
_angle{currentPlayerAngle}
{
	_body.setFillColor(sf::Color::Red);
	floatVector initialPosition= getPosition();
	//_body.setPosition(initialPosition[0], initialPosition[1]);
	setPosition(initialPosition);
}

PlayerBullet::~PlayerBullet()
{
}

//void PlayerBullet::Update(bool direction, float timeElapsed)
void PlayerBullet::Update(int direction, float timeElapsed)
{
	float factor = _speed*timeElapsed;
	floatVector movement= calculatePosition(true, factor);
	setPosition(movement);
	_body.setRotation(_angle*(180.0f/M_PI)+90);
}

floatVector PlayerBullet::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_bulletRadius*cosf(_angle) + _x_center);
	currentPosition.push_back(_bulletRadius*sinf(_angle) + _y_center);
	return currentPosition;
}

floatVector PlayerBullet::calculatePosition(const bool &direction, float factor)
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

float PlayerBullet::getAngle()
{
	return _angle;
}

float PlayerBullet::getRadius()
{
	return _bulletRadius;
}