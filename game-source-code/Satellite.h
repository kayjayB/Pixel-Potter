#ifndef SATELLITE_H
#define SATELLITE_H

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "MovingShootingEntity.h"
#include "EnemyBullet.h"

using floatVector = std::vector<float>;

/**
* Satellite class - represents the dementor Satellites.
* Inherits from MovingShootingEntity class.
*/
class Satellite: public MovingShootingEntity
{
public:
	/**
	* Constructor. Calls the MovingShootingEntity constructor explicitly. Creates a Satellite
	* entity directly below the player 
	* @param angle is a vector of floats containing the current player position
	* @param angle is a float containing the current player angle
	*/
	Satellite(floatVector position, float playerAngle);
	/**
	* Destructor. Decrements the number of Satellites alive and increments the number 
	* of Satellites that have been killed
	*/
	~Satellite();
	/**
	* Copy constructor. Calls the MovingShootingEntity constructor explicitly.
	* Creates a copy of the initial Satellites with an angle that is either the 
	* original Satellite plus 120 degrees or the original Satellite plus 240 degrees
	*/
    Satellite(const Satellite &satellite);
	/**
	* Inherited from MovingShootingEntity.
	* @return vector of floats containing the current Satellite position
	*/
	virtual floatVector getPosition() override;
	/**
	* Inherited from MovingShootingEntity.
	* @return current Satellite angle
	*/
	virtual float getAngle() override;
	/**
	* Inherited from MovingShootingEntity.
	* @return float containing the current Satellite radius
	*/
	virtual float getRadius() override;
	/**
	* Inherited from MovingShootingEntity.
	* Updates the current position of the Satellite 
	* @param direction is unused for the Satellite, but is required for the player class
	* @param timeElapsed is a float containing the time since the last movement occurred
	*/
	virtual void Update(int direction, float timeElapsed) override;	
	/**
	* Inherited from MovingShootingEntity.
	* @return an EntityList type containing the type of entity
	*/
	virtual EntityList getEntityType() override;
	/**
	* Static function
	* @return int containing the number of Satellites alive
	*/
	static int getNumberofSatellitesAlive();
	/**
	* Static function
	* @return int containing the total number of Satellites
	*/	
	static int getTotalNumberofSatellites();
	/**
	* Static function
	* @return int containing the number of Satellites that have been killed
	*/
	static int getNumberofSatellitesKilled();
	/**
	* Static function
	* Resets the number of Satellites alive and killed, and the total number of Satellites
	*/
	static void ResetSatellites();
	
private:
	/**
     * Inherited from MovingShootingEntity.
	* Increments the Satellite angle and calculates the position of the Satellite 
	* @param direction is unused for the Satellite, but is required for the player class
	* @param factor is a float containing the amount by which the angle should be decremented.
	* factor is dependent on the elapsed time
	*/
	virtual void calculatePosition(const bool& direction, float factor) override;
	/**
	* Inherited from MovingShootingEntity.
	* Generates enemy bullets
	*/
	virtual void createBullets() override;
	
	float _theta;
	float _radius;
	float _x_center;
	float _y_center;
	const float _x_centerPlayer=1920.0/2.0;
	const float _y_centerPlayer=1080.0/2.0;
	const float _speed = 1.0;
	EntityList _entityType;
	static int _NumberSatellitesAlive;
	static int _TotalNumberOfSatellites;
	static int 	_NumberSatellitesKilled;
	float _time;
	float _spawnBullet;
	static bool _copies;
	const int changeRadius=150;
	floatVector satellitePosition;
	float thetaBullet;

};

#endif 
