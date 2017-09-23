#include "Enemy.h"

int Enemy::_NumberEnemiesAlive=0;
int Enemy::_TotalNumberOfEnemies=0;

Enemy::Enemy():
//movingEntity(30.0, 60.0, "HP.png"),
MovingShootingEntity(40.0, 80.0, "voldy.png", 1),
_radius{0.0},
_entityType{EntityList::EnemyEntity},
_time{0.0}
{
	_randomAngle = rand()%360;
	_theta = _randomAngle*M_PI/180;
	_body.setRotation(_randomAngle);
	floatVector initialPosition=getPosition();
	setPosition(initialPosition);
	_NumberEnemiesAlive++;
	_TotalNumberOfEnemies++;
	
	_spawnBullet=rand()%5+1;
}

Enemy::~Enemy()
{	
	_NumberEnemiesAlive--;
}

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
	_time+=timeElapsed;
	if (_radius>= _MAX_RADIUS)
	{
		_randomAngle = rand()%360;
		_theta = _randomAngle*M_PI/180;
		_radius = 0.0;
		return;
	}
	
	if (_time > (_spawnBullet-1) && _time < (_spawnBullet+1) )
	{
		createBullets();
		_spawnBullet=fmod(rand(),_time)+5;
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

EntityList Enemy::getEntityType()
{
	return _entityType;
}

int Enemy::getNumberofEnemiesAlive()
{
		return _NumberEnemiesAlive;
}

int Enemy::getTotalNumberofEnemies()
{
		return _TotalNumberOfEnemies;
}

void Enemy::ResetEnemies()
{
		_TotalNumberOfEnemies=0;
}

void Enemy::createBullets()
{
		std::shared_ptr <EnemyBullet> bulletPtr{ new EnemyBullet(_theta, _radius)};
		movingEntity::entityList.push_back(bulletPtr);
		return;
}