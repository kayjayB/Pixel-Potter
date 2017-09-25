#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float currentEnemyAngle, float currentEnemyRadius, float x_center, float y_center,
int red, int green, int blue):
movingEntity(10.0,20.0,"", 1),
_bulletRadius{currentEnemyRadius},
_angle{currentEnemyAngle},
_x_center{x_center},
_y_center{y_center},
_entityType{EntityList::EnemyBulletEntity}
{
	_body.setFillColor(sf::Color(red,green,blue,255));
//	_body.setFillColor(sf::Color::Green);
	floatVector initialPosition= getPosition();
	setPosition(initialPosition);
}
//
// EnemyBullet::EnemyBullet(const EnemyBullet& bullet):
// movingEntity(20.0,40.0,"", 1),
// {
//	 
// }

void EnemyBullet::Update(int direction, float timeElapsed)
{
	float factor = _speed*timeElapsed;
	floatVector movement= calculatePosition(true, factor);
	
		if (getPosition()[0] > 4000)
		{
		setLives(0);
		}
		setPosition(movement);
	_body.setRotation(_angle*(180.0f/M_PI)+90);
}

floatVector EnemyBullet::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_bulletRadius*cosf(_angle) + _x_center);
	currentPosition.push_back(_bulletRadius*sinf(_angle) + _y_center);
	return currentPosition;
}

floatVector EnemyBullet::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_bulletRadius+=factor;
	if (_bulletRadius>=_MAXIMUM_RADIUS)
	{
		_body.setFillColor(sf::Color::Black);
		movement.push_back(4000); // set the bullet off the screen
		movement.push_back(4000);
		return movement;
	}
	movement = getPosition();
	return movement;
}

float EnemyBullet::getAngle()
{
	return _angle;
}

float EnemyBullet::getRadius()
{
	return _bulletRadius;
}

EntityList EnemyBullet::getEntityType()
{
	return _entityType;
}