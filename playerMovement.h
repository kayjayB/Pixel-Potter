#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include <vector>
#include <cmath>

using floatVector =std::vector <float> ;
//using floatVector = std::vector< std::vector< float > > ;
class playerMovement
{
public:
	playerMovement(double radius, double x_center, double y_center, double theta);
	~playerMovement();
	floatVector calculatePosition(const bool &direction, float factor);
	floatVector getPostition();
	float getRotation();
	
private:
double _radius;
double _x_center;
double _y_center;
double _theta;
floatVector _movement;
};

#endif // PLAYERMOVEMENT_H
