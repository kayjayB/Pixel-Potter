#include "PlayerBullet.h"

int PlayerBullet::_copies=0;

PlayerBullet::PlayerBullet(float currentPlayerAngle):
movingEntity(10.0,20.0, 1,255,0,0, ""),
_minimumRadius{50.0},
_bulletRadius{480.0f},
_angle{currentPlayerAngle},
_entityType{EntityList::PlayerBulletEntity}
{
	_scaleX=1;
	_scaleY=1;
}

PlayerBullet::PlayerBullet(const PlayerBullet &bullet):
movingEntity(15.0, 25.0, 1, 255,255,255, "")
{
_copies++;	
_minimumRadius=bullet._minimumRadius;
_bulletRadius=bullet._bulletRadius;

switch (_copies%2 )
{
	case 0:
	_angle=bullet._angle-3*M_PI/180;
	break;
	case 1:
	_angle=bullet._angle+3*M_PI/180;
	break;
}

_entityType=bullet._entityType;

}

void PlayerBullet::Update(int direction, float timeElapsed)
{
	float factor = _speed*timeElapsed;
	calculatePosition(true, factor);
	
	_scaleX-=0.0011*factor;
	_scaleY-=0.0011*factor;
}

floatVector PlayerBullet::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_bulletRadius*cosf(_angle) + _x_center);
	currentPosition.push_back(_bulletRadius*sinf(_angle) + _y_center);
	return currentPosition;
}

void PlayerBullet::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_bulletRadius-=factor;
	if (_bulletRadius<=_minimumRadius)
	{
		setLives(0);
	}
	getPosition();
	return;
}

float PlayerBullet::getAngle()
{
	return _angle;
}

float PlayerBullet::getRadius()
{
	return _bulletRadius;
}

EntityList PlayerBullet::getEntityType()
{
	return _entityType;
}