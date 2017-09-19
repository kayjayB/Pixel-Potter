#include "Enemy.h"

Enemy::Enemy():
//movingEntity(30.0, 60.0, "HP.png"),
movingEntity(30.0, 60.0, "madeye.png"),
_radius{0}
{
	_randomAngle = rand()%360;
	_theta = _randomAngle*M_PI/180;
	_body.setFillColor(sf::Color::Blue);
	_body.setRotation(_randomAngle);
	floatVector initialPosition=getPosition();
	_body.setPosition(initialPosition[0], initialPosition[1]);
}

Enemy::~Enemy()
{	
}

floatVector Enemy::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_radius +=factor;
	movement = getPosition();
	return movement;
}

void Enemy::Update(bool direction, float timeElapsed)
{
	//floatVector movement= getPosition();
	floatVector movement;
	float factor = _speed*timeElapsed;
	
//		if(_radius < _MAX_RADIUS)
//	{
//		movement=calculatePosition(direction, factor);
//	}
//	else
//	{
//		_randomAngle = rand()%360;
//		_theta = _randomAngle*M_PI/180;
//		_radius = 0;
//		movement=calculatePosition(direction, factor);
//	}

	if (_radius>= _MAX_RADIUS)
	{
		_randomAngle = rand()%360;
		_theta = _randomAngle*M_PI/180;
		_radius = 0;
	}
	
	movement=calculatePosition(direction, factor);
	_body.setPosition(movement[0], movement[1]);
	_body.setRotation(_theta*(180.0f/M_PI)+90);
}


float Enemy::getAngle()
{
	return _theta;
}

floatVector Enemy::getPosition()
{	
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float Enemy::getRadius()
{
	return _radius;
}
//
//float Enemy::shoot(float bulletSpeed, float shootPositionX, float shootPositionY, float bulletAngle)
//{
//	bulletSpeed = 2.0f*bulletSpeed;
//	
//	return bulletSpeed;
//}
