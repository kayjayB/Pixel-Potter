#include "Asteroid.h"

Asteroid::Asteroid(float angle)
    : movingEntity(50.0, 50.0, 1)
    , _theta{ angle }
    , _radius{ 0.0 }
    , _entityType{ EntityList::AsteroidEntity }
{
}

floatVector Asteroid::calculatePosition(const bool& direction, float factor)
{
    floatVector movement;
    _radius += factor;
    movement = getPosition();
    return movement;
}

void Asteroid::Update(int direction, float timeElapsed)
{
    floatVector movement;
    float factor = _speed * timeElapsed;

    if(_radius >= _MAX_RADIUS) {
	setLives(0);
    }

    movement = calculatePosition(true, factor);
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