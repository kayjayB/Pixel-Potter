#include "Asteroid.h"

Asteroid::Asteroid(float angle)
    : movingEntity(50.0, 50.0, 1)
    , _theta{ angle }
    , _radius{ 0.0 }
    , _entityType{ EntityList::AsteroidEntity }
{
		_scaleX=1.0;
		_scaleY=1.0;
}

void Asteroid::calculatePosition(const bool& direction, float factor)
{
    floatVector movement;
    _radius += factor;
    getPosition();
	return;
}

void Asteroid::Update(int direction, float timeElapsed)
{
    floatVector movement;
    float factor = _speed * timeElapsed;

    if(_radius >= _MAX_RADIUS) {
	setLives(0);
    }

	calculatePosition(true, factor);
	_scaleX+=0.0012*factor;
	_scaleY+=0.0012*factor;
}

float Asteroid::getAngle()
{
    return _theta;
}

floatVector Asteroid::getPosition()
{
    floatVector currentPosition;
    currentPosition.push_back(_radius * cosf(_theta) + _x_center);
    currentPosition.push_back(_radius * sinf(_theta) + _y_center);
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