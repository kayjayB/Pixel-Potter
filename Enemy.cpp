#include "Enemy.h"

int Enemy::_NumberEnemies=0;

Enemy::Enemy():
//movingEntity(30.0, 60.0, "HP.png"),
movingEntity(40.0, 80.0, "voldy.png", 1),
_radius{0.5},
_entityType{EntityList::EnemyEntity}
{
	_randomAngle = rand()%360;
	_theta = _randomAngle*M_PI/180;
//	Enemy::angles.push_back(_theta);
//	while (angleCompare())
//	{
//		_randomAngle = rand()%360;
//		_theta = _randomAngle*M_PI/180;
//	}
//	_body.setFillColor(sf::Color::Blue);
	_body.setRotation(_randomAngle);
	floatVector initialPosition=getPosition();
	setPosition(initialPosition);
	_NumberEnemies++;
}

Enemy::~Enemy()
{	
	_NumberEnemies--;
}

floatVector Enemy::angles;

//bool Enemy::angleCompare()
//{
//	//for (auto i=begin(Enemy::angles);i!=(end(Enemy::angles)-1); i++)
//	for (int i=0; i!=angles.size()-1; i++)
//	{
//		if ( std::fabs(angles[i]-angles[i+1])<=(20*M_PI/180))
//		{
//			return true;
//		}
//	}
//	return false;
//}

floatVector Enemy::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_radius +=factor;
	movement = getPosition();
	return movement;
}

void Enemy::Update(int direction, float timeElapsed)
{
	floatVector movement;
	float factor = _speed*timeElapsed;

	if (_radius>= _MAX_RADIUS)
	{
		_randomAngle = rand()%360;
		_theta = _randomAngle*M_PI/180;
		_radius = 0;
	}
	
	movement=calculatePosition(true, factor);
	setPosition(movement);
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

EntityList Enemy::getEntityType()
{
	return _entityType;
}

int Enemy::getNumberofEnemies()
{
	return _NumberEnemies;
}