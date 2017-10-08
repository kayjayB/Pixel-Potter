#include "PlayerBullet.h"

int PlayerBullet::_copies=0;

PlayerBullet::PlayerBullet(float currentPlayerAngle):
movingEntity(10.0,20.0, 1),
_minimumRadius{50.0},
_bulletRadius{480.0f},
_angle{currentPlayerAngle},
_entityType{EntityList::PlayerBulletEntity}
{
//	_body.setFillColor(sf::Color::Red);
	floatVector initialPosition= getPosition();
//	setPosition(initialPosition);
}

PlayerBullet::PlayerBullet(const PlayerBullet &bullet):
movingEntity(15.0, 20.0, 1)
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


//_angle=bullet._angle;
_entityType=bullet._entityType;

//_body.setFillColor(sf::Color::White);
floatVector initialPosition= getPosition();
	//_body.setPosition(initialPosition[0], initialPosition[1]);
//setPosition(initialPosition);

}

//PlayerBullet::~PlayerBullet()
//{
//}

//void PlayerBullet::Update(bool direction, float timeElapsed)
void PlayerBullet::Update(int direction, float timeElapsed)
{
	float factor = _speed*timeElapsed;
	floatVector movement= calculatePosition(true, factor);
	
		if (getPosition()[0] > 4000)
		{
		setLives(0);
		}
//		setPosition(movement);
//	_body.setRotation(_angle*(180.0f/M_PI)+90);
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
		setLives(0);
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

EntityList PlayerBullet::getEntityType()
{
	return _entityType;
}