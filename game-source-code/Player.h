#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <algorithm>
#include <memory>
#include "userInput.h"
#include "PlayerBullet.h"
#include "MovingShootingEntity.h"
#include "Satellite.h"
#include "movingEntity.h"

using floatVector = std::vector<float>;

/**
* \brief Player class - represents the harry potter player
* Inherits from the MovingShootingEntity class
*/
class Player : public MovingShootingEntity
{
public:
	/**
	* \brief Default Constructor. Calls the MovingShootingEntity constructor explicitly.
	* Creates a Player entity on the perimeter of the circle at 270 degrees
	*/
    Player();
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return vector of floats containing the current Player position
     */
    virtual floatVector getPosition() override;
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return current Player angle
     */
    virtual float getAngle() override;
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return float containing the current Player radius
     */
    virtual float getRadius() override;
	/**
	* \brief Function returning an integer based on the required movement of the player
	* @param event takes in a userInput type indicating the user's interaction with the keyboard
	* @return int relating to the type of movement required based on the userInput 
	*/
    int MovementDirection(userInput event);
	/**
	*\brief Inherited from MovingShootingEntity.
	* Updates the current position of the Player
	* @param direction indicates the direction that the Player needs to travel in based on
	* the user input
	* @param timeElapsed is a float containing the time since the last movement occurred
	*/
    virtual void Update(int direction, float timeElapsed) override;
	/**
	* \brief Inherited from MovingShootingEntity.
	* @return an EntityList type containing the type of entity
	*/
    virtual EntityList getEntityType() override;
	/**
     * \brief Function to reset all the variables required for the player class
     */
    void reset();
	/**
     * \brief Inherited from MovingShootingEntity.
	 * Generates PlayerBullet entities
     */
	virtual void createBullets() override;

private:
	/**
	* \brief Inherited from MovingShootingEntity.
	* Increments or decrements the Player angle and calculates the position of the Player
	* @param direction is a bool indicating whether the angle must be incremented or
	* decremented
	* @param factor is a float containing the amount by which the angle should be incremented
	* or decremented. factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	
    const int _numberLives = 5;
    float _speed = 0.9f;
    double _theta;
    const double _x_center = 1920.0f / 2.0f;
    const double _y_center = 1080.0f / 2.0f;
    const double _radius = 480.0f;
    EntityList _entityType;
    int _checkShoot;
    std::vector<int> _upgradeBullets;
};

#endif
