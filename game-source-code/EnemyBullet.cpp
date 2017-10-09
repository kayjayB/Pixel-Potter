#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float currentEnemyAngle, float currentEnemyRadius, float x_center, float y_center):
movingEntity(10.0,20.0, 1),
_bulletRadius{currentEnemyRadius},
_angle{currentEnemyAngle},
_x_center{x_center},
_y_center{y_center},
_entityType{EntityList::EnemyBulletEntity}
{
	_scaleX=1.0;
	_scaleY=1.0;
}

void EnemyBullet::Update(int direction, float timeElapsed)
{
	float factor = _speed*timeElapsed;
	calculatePosition(true, factor);
	
		if (getPosition()[0] > 4000)
		{
		collide();
		}
}

floatVector EnemyBullet::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_bulletRadius*cosf(_angle) + _x_center);
	currentPosition.push_back(_bulletRadius*sinf(_angle) + _y_center);
	return currentPosition;
}

void EnemyBullet::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_bulletRadius+=factor;
	if (_bulletRadius>=_MAXIMUM_RADIUS)
	{
		collide();
	}
	getPosition();
	_scaleX+=0.001*factor;
	_scaleY+=0.001*factor;
	return;
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