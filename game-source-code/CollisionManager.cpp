#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::checkCollision()
{

    for(int i = 0; i < movingEntity::entityList.size(); i++)

    {
	for(int j = 0; j < movingEntity::entityList.size(); j++) {
	    if(i != j) {
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyEntity) {

		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives() - 1);
			movingEntity::entityList[j]->setLives(0);
		    }
		}
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::AsteroidEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives() - 1);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyBulletEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives() - 1);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::ArcEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives() - 1);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::LaserEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives() - 1);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::LaserEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::ArcEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyBulletEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
			movingEntity::entityList[j]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::AsteroidEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::SatelliteEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->setLives(0);
			movingEntity::entityList[j]->setLives(0);
		    }
		}
	    }
	}
    }
}

bool CollisionManager::Collision(int i, int j)
{
    floatVector position1 = movingEntity::entityList[i]->getPosition();
    floatVector position2 = movingEntity::entityList[j]->getPosition();
    floatVector halfSize1 = movingEntity::entityList[i]->getBodySize();
    floatVector halfSize2 = movingEntity::entityList[j]->getBodySize();

    float deltaX = position1[0] - position2[0];
    float deltaY = position1[1] - position2[1];
    float intersectX = fabs(deltaX) - (halfSize1[0] / 2 + halfSize2[0] / 2);
    float intersectY = fabs(deltaY) - (halfSize1[1] / 2 + halfSize2[1] / 2);

    if(intersectX < 0.0 && intersectY < 0.0) {
	return true;
    }

    return false;
}

void CollisionManager::entityCleanUp(std::shared_ptr<Player> playerPtr, Window& window)
{
    if(playerPtr->getLives() <= 0) {
	window.setGameState(gameState::lose);
	return;
    }
    for(auto i = begin(movingEntity::entityList); i != end(movingEntity::entityList);) {
	if((*i)->getLives() == 0) {
	    movingEntity::entityList.erase(i);
	} else {
	    i++;
	}
    }
}