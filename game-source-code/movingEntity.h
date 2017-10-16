#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include <vector>
#include <memory>
#include <string>

#include "EntityList.h"

using floatVector = std::vector<float>;
using string = std::string;

/**
* \brief movingEntity class - manages properties of all game entities.
* These entities can be categorised as any iteractive object in the game.
*/
class movingEntity
{
public:
    /**
    * \brief Constructor.
	* @param entityWidth is a float containing the width of the entity
	* @param entityHeight is a float containing the height of the entity
	* @param lives in an int containing the number of lives of the entity
	* @param red is an integer between 0 and 255 containing the amount of red in the colour of the entity
	* @param blue is an integer between 0 and 255 containing the amount of blue in the colour of the entity
	* @param green is an integer between 0 and 255 containing the amount of green in the colour of the entity
	* @param texture is the name of the file to be loaded as the texture for the entity
    */
    movingEntity(float entityWidth, float entityHeight, int lives, int red, int blue, int green, const string &texture);
    /**
    * \brief Function to get the angle of the entity.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
    */
    virtual float getAngle() = 0;
    /**
    * \brief Function to get the current entity position.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @return vector of floats containing the current entity position
    */
    virtual floatVector getPosition() = 0;
    /**
    * \brief Function to get the current entity radius.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @return float containing the current entity radius
    */
    virtual float getRadius() = 0;
    /**
    * \brief Function to update the current position.
	* The function is not implemented in this class and must be implemented
	* in the derived class.
	* @param direction is an integer indicting the direction that the entity must move in
	* @param timeElapsed is a float containing the time since the last movement occurred
    */
    virtual void Update(int direction, float timeElapsed) = 0;
    /**
    * \brief Static vector of all movingEntities
    */
    static std::vector<std::shared_ptr<movingEntity> > entityList;
    /**
    * \brief Function to return the entityType.
    * The function is not implemented in this class and must be implemented
    * in the derived class.
    * @return an EntityList type containing the type of entity
    */
    virtual EntityList getEntityType() = 0;
    /**
    * \brief Function to get the size of the entity.
    * @return a vector of floats containing the height and width of the entity. The
    * height and width are scaled by the scaling factor
	*/
    floatVector getBodySize();
    /**
    * \brief Function to get the number of lives remaining.
    * @return an int containing the number of lives remaining
	*/
    int getLives();
    /**
    * \brief Function to indicate that a collision has occurred. The function decreases the number of lives of the entity
	*/
    void collide();
	/**
	* \brief  Function to get the required colour of the entity
     * @return vector of integers containing the RGB values of the entity colour
 	*/	
	virtual std::vector<int> getColour();
	/**
	* \brief  Function to get the name of the texture to be loaded
     * @return string containing the 
 	*/		
	string getTextureName();

protected:
    /**
    * \brief Function to calculate the new entity position.
    * The function is not implemented in this class and must be implemented
    * in the derived class.
    * @param direction is a bool containing informaton about the direction that the entity is required to travel in
    * @param factor is a float containing the amount by which the radius or angle should be incremented or decremented.
    * factor is dependent on the elapsed time
    */
    virtual void calculatePosition(const bool& direction, float factor) = 0;
	/**
	* \brief  Function to set the number of lives remaining
     * @param life is an integer containing the number of lives
 	*/
	void setLives(int life);

    float _scaleX;
    float _scaleY;
	int _red;
	int _blue;
	int _green;

private:
    float _entityWidth;
    float _entityHeight;
    int _lives;
	string _texture;
};

#endif
