#include "LaserGenerator.h"

int LaserGenerator::_NumberLasersAlive=0;

LaserGenerator::LaserGenerator():
movingEntity(10.0, 10.0, "", 1),
_radius{5.0},
_entityType{EntityList::LaserEntity}
{
		_randomAngle = rand()%360;
		_theta = _randomAngle*M_PI/180;
		floatVector initialPosition=getPosition();
		setPosition(initialPosition);
		_body.setFillColor(sf::Color::Cyan);
		_body.setScale(1.0, 1.0);
		_scale=1.0;
		_NumberLasersAlive++;
		_body.setRotation(_randomAngle-90);
}

LaserGenerator::LaserGenerator(const LaserGenerator &generator):
movingEntity(10.0, 10.0, "", 1)
{
	_theta=generator._theta-50*M_PI/180;
	_scale=generator._scale;
	_body=generator._body;
	_radius=generator._radius;
	floatVector initialPosition=getPosition();
	setPosition(initialPosition);
	_entityType=generator._entityType;
	_NumberLasersAlive++;
	_body.setRotation(_theta*180/M_PI-90);
}

LaserGenerator::~LaserGenerator()
{
	_NumberLasersAlive--;
}

int LaserGenerator::getNumberofLasersAlive()
{
		return _NumberLasersAlive;
}

floatVector LaserGenerator::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_radius +=factor;
	movement = getPosition();
	return movement;
}

void LaserGenerator::Update(int direction, float timeElapsed)
{
	floatVector movement;
	float factor = _speed*timeElapsed;

	if (_radius>= _MAX_RADIUS)
	{
		setLives(0);
	}
	
	movement=calculatePosition(true, factor);
	setPosition(movement);
	
	_body.setScale(_scale,_scale);
        // increase scale...
        _scale+=0.022*factor;
	_body.setOrigin(_body.getSize().x/2,_body.getSize().y/2);
	
//	std::cout << _body.getSize().x << " ";
}


float LaserGenerator::getAngle()
{
	return _theta;
}

floatVector LaserGenerator::getPosition()
{	
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float LaserGenerator::getRadius()
{
	return _radius;
}

EntityList LaserGenerator::getEntityType()
{
	return _entityType;
}