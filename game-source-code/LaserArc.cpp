#include "LaserArc.h"

LaserArc::LaserArc(float LaserAngle,
    std::shared_ptr<LaserGenerator> laserGen1,
    std::shared_ptr<LaserGenerator> laserGen2)
    : movingEntity(14.0, 4.0, 1, 255,255,255, "arcMedium.png")
    , _radius{ 0 }
    , _entityType{ EntityList::ArcEntity }
    , _laser1{ laserGen1 }
    , _laser2{ laserGen2 }
{
    _theta = LaserAngle - 25 * M_PI / 180;
}

void LaserArc::calculatePosition(const bool& direction, float factor)
{
    floatVector movement;
    _radius += factor;
    getPosition();
	return;
}

void LaserArc::Update(int direction, float timeElapsed)
{
    floatVector movement;
    float factor = _speed * timeElapsed;
    if(_laser1->getLives() == 0 || _laser2->getLives() == 0){
	setLives(0);
	}

	calculatePosition(true, factor);

    _scaleX += 0.087 * factor;
	_scaleY += 0.087 * factor/2;
}

float LaserArc::getAngle()
{
    return _theta;
}

floatVector LaserArc::getPosition()
{
    floatVector currentPosition;
    currentPosition.push_back(_radius * cosf(_theta) + _x_center);
    currentPosition.push_back(_radius * sinf(_theta) + _y_center);
    return currentPosition;
}

float LaserArc::getRadius()
{
    return _radius;
}

EntityList LaserArc::getEntityType()
{
    return _entityType;
}