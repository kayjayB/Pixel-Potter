#ifndef MOVINGSHOOTINGENTITY_H
#define MOVINGSHOOTINGENTITY_H

#include <vector>
#include <memory>

#include "movingEntity.h"

/**
* \brief MovingShootingEntity class - represents any entities that can both move and shoot.
* Inherits from the movingEntity class
*/
class MovingShootingEntity : public movingEntity
{
public:
    /**
    * \brief Constructor. Calls the movingEntity constructor explicitly.
	* @param entityWidth is a float containing the width of the entity
	* @param entityHeight is a float containing the height of the entity
	* @param lives in an int containing the number of lives of the entity
	* @param red is an integer between 0 and 255 containing the amount of red in the colour of the entity
	* @param blue is an integer between 0 and 255 containing the amount of blue in the colour of the entity
	* @param green is an integer between 0 and 255 containing the amount of green in the colour of the entity
	* @param texture is the name of the file to be loaded as the texture for the entity
    */
    MovingShootingEntity(float entityWidth, float entityHeight, int lives, int red, int blue, int green, string texture);
   /**
    * \brief Function to get the angle of the entity
	* The function is not implemented in this class and must be implemented
	* in the derived class
    */
    virtual float getAngle() override = 0;
    /**
    * \brief Function to get the current entity position.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @return vector of floats containing the current entity position
    */
    virtual floatVector getPosition() override = 0;
    /**
    * \brief Function to get the current entity radius.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @return float containing the current entity radius
    */
    virtual float getRadius() override = 0;
    /**
    * \brief Function to update the current position.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @param direction is an integer indicting the direction that the entity must move in
	* @param timeElapsed is a float containing the time since the last movement occurred
    */
    virtual void Update(int direction, float timeElapsed) override = 0;
    /**
    * \brief Function to create bullets.
    * The function is not implemented in this class and must be implemented
    * in the derived class.
    */
    virtual void createBullets() = 0;

protected:
    /**
    * \brief Calculates the new entity position
    * The function is not implemented in this class and must be implemented
    * in the derived class
    * @param direction is a bool containing informaton about the direction that the entity is required to travel in
    * @param factor is a float containing the amount by which the radius or angle should be incremented or decremented.
    * factor is dependent on the elapsed time
    */
    virtual void calculatePosition(const bool& direction, float factor) override = 0;
};

#endif 
