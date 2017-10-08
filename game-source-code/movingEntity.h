#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include <vector>
#include <memory>

#include "EntityList.h"

using floatVector = std::vector<float>;
using string = std::string;

/**
* movingEntity class - manages properties of all game entities.
* These entities can be categorised as any iteractive object in the game.
*/
class movingEntity
{
public:
    /**
    * Constructor.
	* @param entityWidth is a float containing the width of the entity
	* @param entityHeight is a float containing the height of the entity
	* @param lives in an int containing the number of lives of the entity
    */
    movingEntity(float entityWidth, float entityHeight, int lives);
    /**
    * Function to get the angle of the entity
	* The function is not implemented in this class and must be implemented
	* in the derived class
    */
    virtual float getAngle() = 0;
    /**
    * Function to get the current entity position
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @return vector of floats containing the current entity position
    */
    virtual floatVector getPosition() = 0;
    /**
    * Function to get the current entity radius
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @return float containing the current entity radius
    */
    virtual float getRadius() = 0;
    /**
    * Function to update the current position
	* The function is not implemented in this class and must be implemented
	* in the derived class
	* @param direction is an integer indicting the direction that the entity must move in
	* @param timeElapsed is a float containing the time since the last movement occurred
    */
    virtual void Update(int direction, float timeElapsed) = 0;
    /**
    * Static vector of all movingEntities
    */
    static std::vector<std::shared_ptr<movingEntity> > entityList;
    /**
    * Function to return the entityType
    * The function is not implemented in this class and must be implemented
    * in the derived class
    * @return an EntityList type containing the type of entity
    */
    virtual EntityList getEntityType() = 0;
    /**
    * Function to get the size of the entity
    * @return a vector of floats containing the height and width of the entity. The
    * height and width are scaled by the scaling factor
	*/
    floatVector getBodySize();
    /**
    * Function to get the number of lives remaining
    * @return an int containing the number of lives remaining
	*/
    int getLives();
    /**
    * Function to set the number of lives remaining
    * @param life is an integer containing the number of lives
	*/
    void setLives(int life);

protected:
    /**
    * Function to calculate the new entity position
    * The function is not implemented in this class and must be implemented
    * in the derived class
    * @param direction is unused for the enemy, but is required for the player class
    * @param factor is a float containing the amount by which the radius should be incremented.
    * factor is dependent on the elapsed time
    */
    virtual void calculatePosition(const bool& direction, float factor) = 0;

    float _scaleX;
    float _scaleY;

private:
    float _entityWidth;
    float _entityHeight;
    int _lives;
};

#endif
