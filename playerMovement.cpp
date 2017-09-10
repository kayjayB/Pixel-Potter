#include "playerMovement.h"

playerMovement::playerMovement(double radius, double x_center, double y_center, double theta):
_radius{radius},
_x_center{x_center},
_y_center{y_center},
_theta{theta}
{
//	_movement.push_back(_radius*std::cos(_theta) + _x_center);
//	_movement.push_back(_radius*std::sin(_theta) + _y_center);
}

playerMovement::~playerMovement()
{
}

floatVector playerMovement::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	if (direction)
	{
	_theta+=factor;
	movement.push_back(_radius*cos(_theta)+_x_center);
	movement.push_back(_radius*sin(_theta) +_y_center);
	return movement;
	}
	
	_theta-=factor;
	movement.push_back(_radius*cos(_theta)+_x_center);
	movement.push_back(_radius*sin(_theta) +_y_center);
	return movement;
	
}

floatVector playerMovement::getPostition()
{
	floatVector currentPosition;
	currentPosition.push_back(_radius*cos(_theta) + _x_center);
	currentPosition.push_back(_radius*sin(_theta) + _y_center);
	return currentPosition;
	
}

float playerMovement::getRotation()
{

	return _theta;	
}