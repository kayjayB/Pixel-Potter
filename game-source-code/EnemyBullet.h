#ifndef ENEMYBULLETS_H
#define ENEMYBULLETS_H

#include "movingEntity.h"
#include "EntityList.h"
#include <cmath>
#include <vector>

using floatVector = std::vector<float>;

/**
* \brief EnemyBullet class - represents the Enemy entities' bullets
* Inherits from movingEntity class.
*/
class EnemyBullet : public movingEntity
{
public:
    /**
    * \brief Constructor. Calls the movingEntity constructor explicitly.
    * Creates an EnemyBullet at the current position
	* @param currentEnemyAngle is a float containing the Enemy angle
	* @param currentEnemyRadius is a float containing the Enemy radius
	* @param x_center is a float containing the x coordinate of the center of the circle
	* @param y_center is a float containing the y coordinate of the center of the circle
    */
    EnemyBullet(float currentEnemyAngle, float currentEnemyRadius, float x_center, float y_center);
    /**
     * \brief Inherited from movingEntity.
     * @return vector of floats containing the current EnemyBullet position
     */
    virtual floatVector getPosition() override;
    /**
     * \brief Inherited from movingEntity.
     * @return current EnemyBullet angle
     */
    virtual float getAngle() override;
    /**
     * \brief Inherited from movingEntity.
     * @return float containing the current EnemyBullet radius
     */
    virtual float getRadius() override;
    /**
     * \brief Inherited from movingEntity.
	 * Updates the current position of the EnemyBullet 
	 * @param direction is unused for the EnemyBullet, but is required for the Player class
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
	 * Increments the EnemyBullet radius and calculates the position of the EnemyBullet 
	 * @param direction is unused for the EnemyBullet, but is required for the Player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
    virtual void calculatePosition(const bool& direction, float factor) override;
	
    const float _MAXIMUM_RADIUS = 480.0;
    float _bulletRadius;
    float _angle;
    float _speed = 200;
    double _x_center;
    double _y_center;
    EntityList _entityType;
};

#endif
