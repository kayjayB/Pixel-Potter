#ifndef MOVINGSHOOTINGENTITY_H
#define MOVINGSHOOTINGENTITY_H

#include <vector>
#include <memory>

#include "movingEntity.h"

/**
* MovingShootingEntity class - represents any entities that can both move and shoot
* Inherits from the movingEntity class
*/
class MovingShootingEntity : public movingEntity
{
public:
    /**
    * Constructor. Calls the movingEntity constructor explicitly.
	* @param entityWidth is a float containing the width of the entity
	* @param entityHeight is a float containing the height of the entity
	* @param lives in an int containing the number of lives of the entity
    */
    MovingShootingEntity(float entityWidth, float entityHeight, int lives);
   /**
    * Function to get the angle of the entity
	* The function is not implemented in this class and must be implemented
	* in the derived class
    */
    virtual float getAngle() override = 0;
    /**
    * Function to get the current entity position
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @return vector of floats containing the current entity position
    */
    virtual floatVector getPosition() override = 0;
    /**
    * Function to get the current entity radius
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @return float containing the current entity radius
    */
    virtual float getRadius() override = 0;
    /**
    * Function to update the current position
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @param direction is an integer indicting the direction that the entity must move in
	* @param timeElapsed is a float containing the time since the last movement occurred
    */
    virtual void Update(int direction, float timeElapsed) override = 0;
    /**
    * Function to create bullets
    * The function is not implemented in this class and must be implemented
    * in the derived class
    */
    virtual void createBullets() = 0;

protected:
    /**
    * Calculates the new entity position
    * The function is not implemented in this class and must be implemented
    * in the derived class
    * @param direction is unused for the enemy, but is required for the player class
    * @param factor is a float containing the amount by which the radius should be incremented.
    * factor is dependent on the elapsed time
    */
    virtual void calculatePosition(const bool& direction, float factor) override = 0;
};

#endif 
