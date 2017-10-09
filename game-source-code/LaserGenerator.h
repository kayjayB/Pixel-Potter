#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H

#include <vector>
#include <cmath>

#include "movingEntity.h"
#include "EntityList.h"

using floatVector = std::vector<float>;

/**
* \brief LaserGenerator class - represents the generators of the laser generator
* Inherits from the movingEntity class
*/
class LaserGenerator : public movingEntity
{
public:
    /**
    * \brief Constructor. Calls the movingEntity constructor explicitly. Creates a LaserGenerator
    * entity at the centre of the circle with a random starting angle
    */
    LaserGenerator();
    /**
	* \brief Copy constructor. Calls the movingEntity constructor explicitly.
	* Creates a copy of the initial LaserGenerator with an angle that is the angle of the
	* initial LaserGenerator minus 50 degrees
	*/
    LaserGenerator(const LaserGenerator& generator);
	/**
	* \brief Destructor. Decrements the number of LaserGenerators alive
	*/
    ~LaserGenerator();
    /**
     * \brief Inherited from movingEntity.
     * @return current LaserGenerator angle
     */
    virtual float getAngle() override;
    /**
     * \brief Inherited from movingEntity.
     * @return vector of floats containing the current LaserGenerator position
     */
    virtual floatVector getPosition() override;
   /**
     * \brief Inherited from movingEntity.
     * @return float containing the current LaserGenerator radius
     */
    virtual float getRadius() override;
    /**
     * \brief Inherited from movingEntity.
	 * Updates the current position of the LaserGenerator 
	 * @param direction is unused for the LaserGenerator, but is required for the Player class
	 * @param timeElapsed is a float containing the time since the last movement occurred
     */
    virtual void Update(int direction, float timeElapsed) override;
    /**
     * \brief Inherited from movingEntity.
	 * @return an EntityList type containing the type of entity
     */
    virtual EntityList getEntityType() override;
    /**
     * \brief Static function 
	 * @return int containing the number of LaserGenerators alive
     */
    static int getNumberofLasersAlive();

private:
	/**
     * \brief Inherited from movingEntity.
	 * Increments the LaserArc radius and calculates the position of the LaserArc 
	 * @param direction is unused for the LaserArc, but is required for the Player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	
	static int _NumberLasersAlive;
    float _theta;
    float _radius;
    const float _MAX_RADIUS = 520.0;
    float _x_center = 1920.0 / 2.0;
    float _y_center = 1080.0 / 2.0;
    const float _speed = 50.0;
    float _randomAngle;
    EntityList _entityType;
};

#endif
