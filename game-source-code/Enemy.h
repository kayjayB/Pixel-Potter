#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "MovingShootingEntity.h"
#include "EnemyBullet.h"

using floatVector =std::vector<float>;

/**
* Enemy class - represents the voldemort enemies
* Inherits from the MovingShootingEntity class
*/
class Enemy: public MovingShootingEntity
{
public:
	/**
	* Default Constructor. Calls the MovingShootingEntity constructor explicitly.
	* Creates an enemy entity at the centre of the circle with a random starting angle
	*/
	Enemy();
	/**
	* Destructor. Decrements the number of enemies alive and increments the number 
	* of enemies that have been killed
	*/	
	~Enemy();
	/**
     * Inherited from MovingShootingEntity.
     * @return vector of floats containing the current enemy position
     */
	virtual floatVector getPosition() override;
	/**
     * Inherited from MovingShootingEntity.
     * @return current enemy angle
     */
	virtual float getAngle() override;
	/**
     * Inherited from MovingShootingEntity.
     * @return float containing the current enemy radius
     */
	virtual float getRadius() override;
	/**
     * Inherited from MovingShootingEntity.
	 * Updates the current position of the enemy 
	 * @param direction is unused for the enemy, but is required for the player class
	 * @param timeElapsed is a float containing the time since the last movement occurred
     */
	virtual void Update(int direction, float timeElapsed) override;	
	/**
     * Inherited from MovingShootingEntity.
	 * @return an EntityList type containing the type of entity
     */
	virtual EntityList getEntityType() override;
	/**
     * Static function
	 * @return int containing the number of enemies alive
     */
	static int getNumberofEnemiesAlive();
	/**
     * Static function
	 * @return int containing the total number of enemies
     */	
	static int getTotalNumberofEnemies();
	/**
     * Static function
	 * @return int containing the number of enemies that have been killed
     */
	static int getNumberofEnemiesKilled();
	/**
     * Static function
	 * Resets the number of enemies alive and killed, and the total number of enemies
     */
	static void ResetEnemies();
	
private:
	/**
     * Inherited from MovingShootingEntity.
	 * Increments the enemy radius and calculates the position of the enemy 
	 * @param direction is unused for the enemy, but is required for the player class
	 * @param factor is a float containing the amount by which the radius should be incremented.
	 * factor is dependent on the elapsed time
     */
	virtual void calculatePosition(const bool& direction, float factor) override;
	/**
     * Inherited from MovingShootingEntity.
	 * Generates enemy bullets
     */
	virtual void createBullets() override;
	
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

