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
* Player class - represents the harry potter player
* Inherits from the MovingShootingEntity class
*/
class Player : public MovingShootingEntity
{
public:
	/**
	* Default Constructor. Calls the MovingShootingEntity constructor explicitly.
	* Creates a player entity on the perimeter of the circle at 270 degrees
	*/
    Player();
	/**
     * Inherited from MovingShootingEntity.
     * @return vector of floats containing the current Player position
     */
    virtual floatVector getPosition() override;
	/**
     * Inherited from MovingShootingEntity.
     * @return current Player angle
     */
    virtual float getAngle() override;
	/**
     * Inherited from MovingShootingEntity.
     * @return float containing the current Player radius
     */
    virtual float getRadius() override;
	/**
	* Function returning an integer based on the required movement of the player
	* @param event takes in a userInput type indicating the user's interaction with the keyboard
	* @return int relating to the type of movement required based on the userInput 
	*/
    int MovementDirection(userInput event);
	/**
	* Inherited from MovingShootingEntity.
	* Updates the current position of the enemy 
	* @param direction indicates the direction that the player needs to travel in based on
	* the user input
	* @param timeElapsed is a float containing the time since the last movement occurred
	*/
    virtual void Update(int direction, float timeElapsed) override;
	/**
	* Inherited from MovingShootingEntity.
	* @return an EntityList type containing the type of entity
	*/
    virtual EntityList getEntityType() override;

    void reset();

private:
	/**
	* Inherited from MovingShootingEntity.
	* Increments the enemy radius and calculates the position of the enemy 
	* @param direction is a bool indicating twhether the angle must be incremented or
	* decremented
	* @param factor is a float containing the amount by which the angle should be incremented
	* or decremented. factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	/**
     * Inherited from MovingShootingEntity.
	 * Generates Player bullets
     */
	virtual void createBullets() override;
	
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
