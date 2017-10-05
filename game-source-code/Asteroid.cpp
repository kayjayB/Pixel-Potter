#include "Asteroid.h"

Asteroid::Asteroid(float angle):
movingEntity(50.0, 50.0, "quaffle.png", 1),
_theta{angle},
_radius{0.0},
_entityType{EntityList::AsteroidEntity} //,//manager(EntityList::AsteroidEntity, 50.0, 50.0, "quaffle.png")
{
	//_body.setRotation(_randomAngle);
	floatVector initialPosition=getPosition();
	setPosition(initialPosition);
}

floatVector Asteroid::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_radius +=factor;
	movement = getPosition();
	return movement;
}

void Asteroid::Update(int direction, float timeElapsed)
{
	floatVector movement;
	float factor = _speed*timeElapsed;

	if (_radius>= _MAX_RADIUS)
	{
		setLives(0);
	}
	
	movement=calculatePosition(true, factor);
	setPosition(movement);
	_body.setRotation(_theta*(180.0f/M_PI)+90);
}


float Asteroid::getAngle()
{
	return _theta;
}

floatVector Asteroid::getPosition()
{	
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float Asteroid::getRadius()
{
	return _radius;
}

EntityList Asteroid::getEntityType()
{
	return _entityType;
}