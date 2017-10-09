#ifndef BULLET_H
#define BULLET_H

#include <cmath>

#include "movingEntity.h"

/**
* \brief PlayerBullet class - represents the Player entities' bullets
* Inherits from movingEntity class.
*/
class PlayerBullet : public movingEntity
{
public:
    /**
    * \brief Constructor. Calls the movingEntity constructor explicitly.
    * Creates a PlayerBullet at the current position
	* @param currentPlayerAngle is a float containing the current Player angle
    */
    PlayerBullet(float currentPlayerAngle);
	/**
	* \brief Copy constructor. Calls the movingEntity constructor explicitly.
	* Creates a copy of the initial PlayerBullet with an angle that is either the 
	* original PlayerBullet minus 3 degrees or the original PlayerBullet plus 3 degrees
	*/
    PlayerBullet(const PlayerBullet& bullet);
	/**
	* \brief Inherited from movingEntity.
	* @return vector of floats containing the current PlayerBullet position
	*/
    virtual floatVector getPosition() override;
	/**
	* \brief Inherited from movingEntity.
	* @return current PlayerBullet angle
	*/
    virtual float getAngle() override;
	/**
	* \brief Inherited from movingEntity.
	* @return float containing the current PlayerBullet radius
	*/
    virtual float getRadius() override;
	/**
	* \brief Inherited from movingEntity.
	* Updates the current position of the PlayerBullet 
	* @param direction is unused for the PlayerBullet, but is required for the Player class
	* @param timeElapsed is a float containing the time since the last movement occurred
	*/
    virtual void Update(int direction, float timeElapsed) override;
	/**
	* \brief Inherited from movingEntity.
	* @return an EntityList type containing the type of entity
	*/
    virtual EntityList getEntityType() override;

private:
	/**
	* \brief Inherited from movingEntity.
	* Decrements the PlayerBullet radius and calculates the position of the PlayerBullet 
	* @param direction is unused for the PlayerBullet, but is required for the Player class
	* @param factor is a float containing the amount by which the radius should be decremented.
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
