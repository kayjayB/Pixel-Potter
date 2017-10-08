#ifndef BULLET_H
#define BULLET_H

#include <cmath>

#include "movingEntity.h"

/**
* PlayerBullet class - represents the player entities' bullets
* Inherits from movingEntity class.
*/
class PlayerBullet : public movingEntity
{
public:
    /**
    * Constructor. Calls the movingEntity constructor explicitly.
    * Creates an enemy bullet at the current position
	* @param currentPlayerAngle is a float containing the current player angle
    */
    PlayerBullet(float currentPlayerAngle);
	/**
	* Copy constructor. Calls the movingEntity constructor explicitly.
	* Creates a copy of the initial PlayerBullet with an angle that is either the 
	* original PlayerBullet minus 3 degrees or the original PlayerBullet plus 3 degrees
	*/
    PlayerBullet(const PlayerBullet& bullet);
	/**
	* Inherited from movingEntity.
	* @return vector of floats containing the current bullet position
	*/
    virtual floatVector getPosition() override;
	/**
	* Inherited from movingEntity.
	* @return current bullet angle
	*/
    virtual float getAngle() override;
	/**
	* Inherited from movingEntity.
	* @return float containing the current bullet radius
	*/
    virtual float getRadius() override;
	/**
	* Inherited from movingEntity.
	* Updates the current position of the bullet 
	* @param direction is unused for the bullet, but is required for the player class
	* @param timeElapsed is a float containing the time since the last movement occurred
	*/
    virtual void Update(int direction, float timeElapsed) override;
	/**
	* Inherited from movingEntity.
	* @return an EntityList type containing the type of entity
	*/
    virtual EntityList getEntityType() override;

private:
	/**
	* Inherited from movingEntity.
	* Increments the bullet radius and calculates the position of the bullet 
	* @param direction is unused for the bullet, but is required for the player class
	* @param factor is a float containing the amount by which the radius should be incremented.
	* factor is dependent on the elapsed time
	*/
    virtual void calculatePosition(const bool& direction, float factor) override;
	
    float _minimumRadius;
    float _bulletRadius;
    float _angle;
    float _speed = 100;
    double _x_center = 1920.0 / 2.0;
    double _y_center = 1080.0 / 2.0;
    EntityList _entityType;
    static int _copies;
};

#endif
