#include "Satellite.h"

int Satellite::_NumberSatellitesAlive=0;
int Satellite::_TotalNumberOfSatellites=0;
int Satellite::_NumberSatellitesKilled=0;
bool Satellite::_copies=false;

Satellite::Satellite(floatVector position, float playerAngle):
MovingShootingEntity(40.0, 40.0, 1),
_theta{0},
_radius{80},
_entityType{EntityList::SatelliteEntity},
_time{0.0},
thetaBullet{0}
{

if (position[0] < _x_centerPlayer && position[1] < _y_centerPlayer)
{
	_x_center=position[0]+changeRadius;
	_y_center=position[1]+changeRadius;
}
else if (position[0] < _x_centerPlayer && position[1] > _y_centerPlayer)
{
	_x_center=position[0]+changeRadius;
	_y_center=position[1]-changeRadius;
}
else if (position[0] > _x_centerPlayer && position[1] > _y_centerPlayer)
{
	_x_center=position[0]-changeRadius;
	_y_center=position[1]-changeRadius;
}
else if (position[0] > _x_centerPlayer && position[1] < _y_centerPlayer)
{
	_x_center=position[0]-changeRadius;
	_y_center=position[1]+changeRadius;
}
else if (position[0]== _x_centerPlayer && position[1] < _y_centerPlayer)
{
	_x_center=position[0];
	_y_center=position[1]+changeRadius;
}
else if (position[0]== _x_centerPlayer && position[1] > _y_centerPlayer)
{
	_x_center=position[0];
	_y_center=position[1]-changeRadius;
}
else if (position[1]== _y_centerPlayer && position[0] > _x_centerPlayer)
{
	_x_center=position[0]-changeRadius;
	_y_center=position[1];
}
else if (position[1]== _y_centerPlayer && position[0] < _x_centerPlayer)
{
	_x_center=position[0]+changeRadius;
	_y_center=position[1];
}
	
	_playerPos=position;
	floatVector initialPosition=getPosition();
	_NumberSatellitesAlive++;
	_TotalNumberOfSatellites++;
	
	_spawnBullet=rand()%5+1;
	
}

Satellite::~Satellite()
{
	_NumberSatellitesAlive--;
	_NumberSatellitesKilled++;
}
Satellite::Satellite(const Satellite &satellite):
MovingShootingEntity(40.0, 40.0, 1)
{
	_radius = satellite._radius;
	
	_copies=!_copies;
	
	if (_copies)
	{
	_theta=120*M_PI/180;
	}
	else
	{
		_theta = 240*M_PI/180;
	}
	_x_center=satellite._x_center;
	_y_center=satellite._y_center;
	_entityType=satellite._entityType;
	floatVector initialPosition=getPosition();
	_NumberSatellitesAlive++;
	_TotalNumberOfSatellites++;
	
	_spawnBullet=rand()%5+1;
}

floatVector Satellite::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	//_radius -=factor;
	_theta-=factor;
	movement = getPosition();
	return movement;
}

void Satellite::Update(int direction, float timeElapsed)
{
	floatVector movement;
	float factor = _speed*timeElapsed;
	_time+=timeElapsed;
	
	if (_time > (_spawnBullet-1) && _time < (_spawnBullet+1) )
	{
		createBullets();
		_spawnBullet=fmod(rand(),5);
		_time=0.0;
	}
	
	movement=calculatePosition(true, factor);
//	setPosition(movement);
}


float Satellite::getAngle()
{
	return _theta;
}

floatVector Satellite::getPosition()
{	
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float Satellite::getRadius()
{
	return _radius;
}

EntityList Satellite::getEntityType()
{
	return _entityType;
}

int Satellite::getNumberofSatellitesAlive()
{
		return _NumberSatellitesAlive;
}

int Satellite::getTotalNumberofSatellites()
{
		return _TotalNumberOfSatellites;
}

int Satellite::getNumberofSatellitesKilled()
{
	return _NumberSatellitesKilled;
}

void Satellite::ResetSatellites()
{
		_TotalNumberOfSatellites=0;
		_NumberSatellitesAlive=0;
		_NumberSatellitesKilled=0;
		_copies=false;
}

void Satellite::createBullets()
{
satellitePosition=getPosition();
	
if (satellitePosition[0] < _x_centerPlayer && satellitePosition[1] < _y_centerPlayer)
{
	thetaBullet=M_PI;
}
if (satellitePosition[0] <= _x_centerPlayer && satellitePosition[1] >= _y_centerPlayer)
{
	thetaBullet=M_PI/2;
}
if (satellitePosition[0] > _x_centerPlayer && satellitePosition[1] <= _y_centerPlayer)
{
	thetaBullet=3*M_PI/2;
}
if (satellitePosition[0] >= _x_centerPlayer && satellitePosition[1] > _y_centerPlayer)
{
	thetaBullet=0;
}
	std::shared_ptr <EnemyBullet> bulletPtr{ new EnemyBullet(thetaBullet, _radius, _x_center, _y_center)};
	movingEntity::entityList.push_back(bulletPtr);
	return;
}