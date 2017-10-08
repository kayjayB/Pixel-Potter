#include "LaserArc.h"

LaserArc::LaserArc(float LaserAngle,
    std::shared_ptr<LaserGenerator> laserGen1,
    std::shared_ptr<LaserGenerator> laserGen2)
    : movingEntity(14.0, 4.0, "arcMedium.png", 1)
    , _radius{ 0 }
    , _entityType{ EntityList::ArcEntity }
    , _laser1{ laserGen1 }
    , _laser2{ laserGen2 }
{
    _theta = LaserAngle - 25 * M_PI / 180;
    _body.setScale(1.0, 1.0);
    _scale = 1.0;
    floatVector initialPosition = getPosition();
    setPosition(initialPosition);
    _body.setRotation(_theta * 180 / M_PI + 90);
}

LaserArc::~LaserArc()
{
}

floatVector LaserArc::calculatePosition(const bool& direction, float factor)
{
    floatVector movement;
    _radius += factor;
    movement = getPosition();
    return movement;
}

void LaserArc::Update(int direction, float timeElapsed)
{
    floatVector movement;
    float factor = _speed * timeElapsed;
    if(_laser1->getLives() == 0 || _laser2->getLives() == 0){
	setLives(0);
	}

    if(_radius >= _MAX_RADIUS) {
	setLives(0);
    }

    movement = calculatePosition(true, factor);
    setPosition(movement);

    _body.setScale(_scale, _scale / 2);
    _scale += 0.087 * factor;
    _body.setOrigin(_body.getSize().x / 2, _body.getSize().y / 2);
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