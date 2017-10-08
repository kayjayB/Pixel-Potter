#include "LaserGenerator.h"

int LaserGenerator::_NumberLasersAlive=0;

LaserGenerator::LaserGenerator():
movingEntity(10.0, 10.0, 1),
_radius{5.0},
_entityType{EntityList::LaserEntity}
{
		_randomAngle = rand()%360;
		_theta = _randomAngle*M_PI/180;
		_scale=1.0;
		_NumberLasersAlive++;
}

LaserGenerator::LaserGenerator(const LaserGenerator &generator):
movingEntity(10.0, 10.0, 1)
{
	_theta=generator._theta-50*M_PI/180;
	_scale=generator._scale;
	//_body=generator._body;
	_radius=generator._radius;
	floatVector initialPosition=getPosition();
	_entityType=generator._entityType;
	_NumberLasersAlive++;
}

LaserGenerator::~LaserGenerator()
{
	_NumberLasersAlive--;
}

int LaserGenerator::getNumberofLasersAlive()
{
		return _NumberLasersAlive;
}

void LaserGenerator::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	_radius +=factor;
	getPosition();
	return;
}

void LaserGenerator::Update(int direction, float timeElapsed)
{
	floatVector movement;
	float factor = _speed*timeElapsed;

	if (_radius>= _MAX_RADIUS)
	{
		setLives(0);
	}
	
	//movement=calculatePosition(true, factor);
	calculatePosition(true, factor);

        _scale+=0.022*factor;
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