#ifndef ENTITYLIST_H
#define ENTITYLIST_H

/**
* EntityList is strongly typed enum class 
* It is used to classify the type of the enemy entities
*/
enum class EntityList
{
	PlayerEntity=0,
	PlayerBulletEntity,
	EnemyEntity,
	EnemyBulletEntity,
	AsteroidEntity,
	SatelliteEntity,
	LaserEntity,
	ArcEntity,
};

#endif