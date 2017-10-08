#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <memory>

#include "math.h"
#include "movingEntity.h"

using floatVector = std::vector<float>;

/**
* Asteroid class - represents the quaffle asteroids.
* Inherits from movingEntity class.
*/
class Asteroid : public movingEntity
{
public:
	/**
	* Constructor. Calls the movingEntity constructor explicitly. Creates an asteroid 
	* entity at the centre of the circle with an angle equal to the player's current 
	* angle
	* @param angle is a float containing the current player angle
	*/
    Asteroid(float angle);
    /**
     * Inherited from movingEntity.
     * @return current asteroid angle
     */
	virtual float getAngle() override;
    /**
     * Inherited from movingEntity.
     * @return vector of floats containing the current asteroid position
     */
    virtual floatVector getPosition() override;
    /**
     * Inherited from movingEntity.
     * @return float containing the current asteroid radius
     */
    virtual float getRadius() override;
    /**
     * Inherited from movingEntity.
	 * Updates the current position of the asteroid 
	 * @param direction is unused for the asteroid, but is required for the player class
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
	 * Increments the asteroid radius and calculates the position of the asteroid 
	 * @param direction is unused for the asteroid, but is required for the player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	
    float _theta;
    float _radius;
    const float _MAX_RADIUS = 480.0f;
    float _x_center = 1920.0f / 2.0f;
    float _y_center = 1080.0f / 2.0f;
    const float _speed = 100.9f;
    EntityList _entityType;
};

#endif
