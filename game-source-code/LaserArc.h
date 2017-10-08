#ifndef LASERARC_H
#define LASERARC_H

#include <vector>
#include <cmath>
#include "movingEntity.h"
#include "EntityList.h"
#include "LaserGenerator.h"

using floatVector = std::vector<float>;

/**
* LaserArc class - represents the arc of the laser generator
* Inherits from the movingEntity class
*/
class LaserArc : public movingEntity
{
public:
    /**
    * Constructor. Calls the movingEntity constructor explicitly. Creates a LaserArc
    * entity at the centre of the circle with an angle that lies half way between the angles
    * of the laser generators
    * @param LaserAngle is a float containing the angle of one of the generators
    * @param laserGen1 is a shared pointer to the first LaserGenerator object
    * @param laserGen2 is a shared pointer to the second LaserGenerator object
    */
    LaserArc(float LaserAngle, std::shared_ptr<LaserGenerator> laserGen1, std::shared_ptr<LaserGenerator> laserGen2);
    /**
     * Inherited from movingEntity.
     * @return current LaserArc angle
     */
    virtual float getAngle() override;
    /**
     * Inherited from movingEntity.
     * @return vector of floats containing the current LaserArc position
     */
    virtual floatVector getPosition() override;
   /**
     * Inherited from movingEntity.
     * @return float containing the current LaserArc radius
     */
    virtual float getRadius() override;
    /**
     * Inherited from movingEntity.
	 * Updates the current position of the LaserArc 
	 * @param direction is unused for the LaserArc, but is required for the player class
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
	 * Increments the LaserArc radius and calculates the position of the LaserArc 
	 * @param direction is unused for the LaserArc, but is required for the player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	
    float _theta;
    float _radius;
    const float _MAX_RADIUS = 470.0;
    float _x_center = 1920.0 / 2.0;
    float _y_center = 1080.0 / 2.0;
    const float _speed = 43.5;
    EntityList _entityType;
    std::shared_ptr<LaserGenerator> _laser1;
    std::shared_ptr<LaserGenerator> _laser2;
};

#endif // LASERARC_H
