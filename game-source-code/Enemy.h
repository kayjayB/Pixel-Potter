#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "MovingShootingEntity.h"
#include "EnemyBullet.h"

using floatVector =std::vector<float>;

/**
* \brief Enemy class - represents the voldemort enemies
* Inherits from the MovingShootingEntity class
*/
class Enemy: public MovingShootingEntity
{
public:
	/**
	* \brief Default Constructor. Calls the MovingShootingEntity constructor explicitly.
	* Creates an enemy entity at the centre of the circle with a random starting angle
	*/
	Enemy();
	/**
	* \brief Destructor. Decrements the number of enemies alive and increments the number 
	* of enemies that have been killed
	*/	
	~Enemy();
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return vector of floats containing the current Enemy position
     */
	virtual floatVector getPosition() override;
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return current enemy angle
     */
	virtual float getAngle() override;
	/**
     * \brief Inherited from MovingShootingEntity.
     * @return float containing the current Enemy radius
     */
	virtual float getRadius() override;
	/**
     * \brief Inherited from MovingShootingEntity.
	 * Updates the current position of the Enemy 
	 * @param direction is unused for the Enemy, but is required for the Player class
	 * @param timeElapsed is a float containing the time since the last movement occurred
     */
	virtual void Update(int direction, float timeElapsed) override;	
	/**
     * \brief Inherited from MovingShootingEntity.
	 * @return an EntityList type containing the type of entity
     */
	virtual EntityList getEntityType() override;
	/**
     * \brief Static function
	 * @return int containing the number of enemies alive
     */
	static int getNumberofEnemiesAlive();
	/**
     * \brief Static function
	 * @return int containing the total number of enemies
     */	
	static int getTotalNumberofEnemies();
	/**
     * \brief Static function
	 * @return int containing the number of enemies that have been killed
     */
	static int getNumberofEnemiesKilled();
	/**
     * \brief Static function
	 * Resets the number of enemies alive and killed, and the total number of enemies
     */
	static void ResetEnemies();
	/**
     * \brief Inherited from MovingShootingEntity.
	 * Generates EnemyBullet
     */
	virtual void createBullets() override;
	
private:
	/**
     * \brief Inherited from MovingShootingEntity.
	 * Increments the enemy radius and calculates the position of the Enemy 
	 * @param direction is unused for the Enemy, but is required for the Player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
	virtual void calculatePosition(const bool& direction, float factor) override;
	
	static int _NumberEnemiesAlive;
	static int _TotalNumberOfEnemies;
	static int 	_NumberEnemiesKilled;
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0;
	float _x_center = 1920.0/2.0;
	float _y_center = 1080.0/2.0;
	const float _speed = 90.0;
	float _randomAngle;
	EntityList _entityType;
	float _time;
	float _spawnBullet;
	float _tolerance;

};

#endif

