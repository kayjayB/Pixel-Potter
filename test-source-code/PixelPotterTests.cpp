#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Asteroid.h"
#include "Satellite.h"
#include "userInput.h"
#include "movingEntity.h"
#include "MovingShootingEntity.h"
#include "CollisionManager.h"
#include "LaserGenerator.h"
#include "LaserArc.h"
#include "gameState.h"
#include <cmath>
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

//********************************************************************************************************************************************************************************
//Testing the movement and spawning of the player
//********************************************************************************************************************************************************************************

TEST_SUITE("Player_movement_and_spawning"){
TEST_CASE("Player is not initilised in the center of the screen")
{
	Player testPlayer;
	std::vector<float> position =testPlayer.getPosition();
	std::vector <float> origin(1920/2, 1080/2);
	CHECK_FALSE( position[0]== origin[0]);
	CHECK_FALSE( position[1]== origin[1]);
}

TEST_CASE("Player is initialised at cartesian 270 degrees")
{
	Player testPlayer;
	auto angle =testPlayer.getAngle();
	auto expectedAngle= 90*M_PI/180;
	
	CHECK(doctest::Approx(angle) == expectedAngle);
}

TEST_CASE("Player moves anticlockwise when the left arrow is pressed")
{
	Player testPlayer;
	std::vector<float> initialPosition= testPlayer.getPosition();
	userInput left = userInput::PressLeft;
	int direction = testPlayer.MovementDirection(left);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPosition();
	double factor = 0.9 * time;
	auto expectedAngle= 90*M_PI/180-factor;
	double x_center = 1920.0f / 2.0f;
	double y_center = 1080.0f / 2.0f;
	float radius = 480.0f;
	float calculatedpositionX=radius*cos(expectedAngle) + x_center;
	float calculatedpositionY=radius*sin(expectedAngle) + y_center;
	CHECK(doctest::Approx(calculatedpositionX)==finalPosition[0]);
	CHECK(doctest::Approx(calculatedpositionY)==finalPosition[1]);
}


TEST_CASE("Player moves clockwise when the right arrow is pressed")
{
	Player testPlayer;
	std::vector<float> initialPosition= testPlayer.getPosition();
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPosition();
	double factor = 0.9 * time;
	auto expectedAngle= 90*M_PI/180+factor;
	double x_center = 1920.0f / 2.0f;
	double y_center = 1080.0f / 2.0f;
	float radius = 480.0f;
	float calculatedpositionX=radius*cos(expectedAngle) + x_center;
	float calculatedpositionY=radius*sin(expectedAngle) + y_center;
	CHECK(doctest::Approx(calculatedpositionX)==finalPosition[0]);
	CHECK(doctest::Approx(calculatedpositionY)==finalPosition[1]);

}

TEST_CASE("Player does not move when there is no user input")
{
	Player testPlayer;
	std::vector<float> initialPosition= testPlayer.getPosition();
	userInput noInput = userInput::NoButtonPress;
	int direction = testPlayer.MovementDirection(noInput);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPosition();
	CHECK(initialPosition==finalPosition);

}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of the player's bullets
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Player_bullet_movement_and_spawning"){
TEST_CASE("No bullet is created if no button is pressed (no spacebar is pressed)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float time = 0.1f;
	userInput noInput = userInput::NoButtonPress;
	int shoot = testPlayer.MovementDirection(noInput);
	testPlayer.Update(shoot,time);
	int numberOfBulletsMade =0;
	
	for (unsigned int i =0 ; i< movingEntity::entityList.size() ;i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity)
		{
			numberOfBulletsMade++;
		}
	}
	int numberOfExpectedBullets = 0;
	CHECK(numberOfBulletsMade == numberOfExpectedBullets);
}

TEST_CASE("Bullet is created when spacebar is pressed")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float time = 0.1f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int numberOfBulletsMade =0;
	
	for (unsigned int i =0 ; i< movingEntity::entityList.size() ;i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity)
		{
			numberOfBulletsMade++;
			
		}
	}
	int numberOfExpectedBullets = 1;
	CHECK(numberOfBulletsMade == numberOfExpectedBullets);
}

TEST_CASE("More than one bullet can be created")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float time = 0.1f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	testPlayer.Update(shoot,time);
	int numberOfBulletsMade =0;
	
	for (unsigned int i =0 ; i< movingEntity::entityList.size() ;i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity)
		{
			numberOfBulletsMade++;
		}
	}
	int numberOfExpectedBullets = 2;
	CHECK(numberOfBulletsMade == numberOfExpectedBullets);
}

TEST_CASE("Bullet has a starting position which is the same as the player's when shot from players starting position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> initialPlayerPosition= testPlayer.getPosition();
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	std::vector<float> initialBulletPosition = movingEntity::entityList[0]->getPosition();
	
	CHECK(doctest::Approx(initialPlayerPosition[0])==initialBulletPosition[0]);
	CHECK(doctest::Approx(initialPlayerPosition[1])==initialBulletPosition[1]);
}

TEST_CASE("Bullet has a starting position that is the same as the player's, regardless of player's position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime1 = 0.3f;
	int direction1 = testPlayer.MovementDirection(right);
	testPlayer.Update(direction1,movementTime1);
	std::vector<float> PlayerPosition1 = testPlayer.getPosition();
	float shootTime = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	
	std::vector<float> bulletPosition1 = movingEntity::entityList[0]->getPosition();
	CHECK(doctest::Approx(PlayerPosition1[0])==bulletPosition1[0]);
	CHECK(doctest::Approx(PlayerPosition1[1])==bulletPosition1[1]);
	
	
	userInput left = userInput::PressLeft;
	float movementTime2 = 0.8f;
	int direction2 = testPlayer.MovementDirection(left);
	testPlayer.Update(direction2,movementTime2);
	std::vector<float> PlayerPosition2 = testPlayer.getPosition();
	shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	std::vector<float> bulletPosition2 = movingEntity::entityList[1]->getPosition();
	CHECK(doctest::Approx(PlayerPosition2[0])==bulletPosition2[0]);
	CHECK(doctest::Approx(PlayerPosition2[1])==bulletPosition2[1]);
}

TEST_CASE("Bullet has the same angle as the player when it is shot")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	float bulletAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(playerAngle)==bulletAngle);
}

TEST_CASE("Bullet has the same start angle as the player's angle when it is shot, regardless of players current angle")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime1 = 0.3f;
	int direction1 = testPlayer.MovementDirection(right);
	testPlayer.Update(direction1,movementTime1);
	float playerAngle1 = testPlayer.getAngle();
	float shootTime = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	float bulletAngle1 = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(playerAngle1)==bulletAngle1);
	
	userInput left = userInput::PressLeft;
	float movementTime2 = 0.8f;
	int direction2 = testPlayer.MovementDirection(left);
	testPlayer.Update(direction2,movementTime2);
	float playerAngle2 = testPlayer.getAngle();
	shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	float bulletAngle2 = movingEntity::entityList[1]->getAngle();
	CHECK(doctest::Approx(playerAngle2)==bulletAngle2);
}

TEST_CASE("The angle of the bullet remains constant during flight, regardless of shooting position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.8f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	float originalDistanceToCenter1 = movingEntity::entityList[0]->getRadius();
	float originalAngle1 = movingEntity::entityList[0]->getAngle();
	movingEntity::entityList[0]->Update(1,shootTime);
	float finalDistanceToCenter1 = movingEntity::entityList[0]->getRadius();
	float finalAngle1 = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(originalDistanceToCenter1) > finalDistanceToCenter1);
	CHECK(doctest::Approx(originalAngle1) == finalAngle1);
	
	userInput left = userInput::PressLeft;
	float movementTime = 0.8f;
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	testPlayer.Update(shoot,shootTime);
	float originalDistanceToCenter2 = movingEntity::entityList[1]->getRadius();
	float originalAngle2 = movingEntity::entityList[1]->getAngle();
	movingEntity::entityList[1]->Update(1,shootTime);
	float finalDistanceToCenter2 = movingEntity::entityList[1]->getRadius();
	float finalAngle2 = movingEntity::entityList[1]->getAngle();
	CHECK(doctest::Approx(originalDistanceToCenter2) > finalDistanceToCenter2);
	CHECK(doctest::Approx(originalAngle2) == finalAngle2);
}

TEST_CASE("The bullet angle remains constant during flight while the player moves")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition1 = testPlayer.getPosition();
	float shootTime1 = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime1);
	float originalAngle = movingEntity::entityList[0]->getAngle();
	float originalDistanceToCenter = movingEntity::entityList[0]->getRadius();
	
	userInput right = userInput::PressRight;
	float moveTime = 0.5f;
	float shootTime2 = 0.8f;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,moveTime);
	std::vector<float> playerPosition2 = testPlayer.getPosition();
	movingEntity::entityList[0]->Update(1,shootTime2);
	float finalAngle = movingEntity::entityList[0]->getAngle();
	float finalDistanceToCenter = movingEntity::entityList[0]->getRadius();
	
	CHECK_FALSE(doctest::Approx(playerPosition1[0])==playerPosition2[0]);
	CHECK_FALSE(doctest::Approx(playerPosition1[1])==playerPosition2[1]);
	CHECK(doctest::Approx(originalDistanceToCenter) > finalDistanceToCenter);
	CHECK(doctest::Approx(originalAngle) == finalAngle);
}

TEST_CASE("Multiple bullet positions can be tracked during bullet flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.0f;
	float moveTime = 0.9f;
	float bulletFlightTime = 0.1f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,moveTime);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	testPlayer.Update(direction,moveTime);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	movingEntity::entityList[2]->Update(1,bulletFlightTime);
	
	std::vector<float> bullet1Position = movingEntity::entityList[0]->getPosition();
	std::vector<float> bullet2Position = movingEntity::entityList[1]->getPosition();
	std::vector<float> bullet3Position = movingEntity::entityList[2]->getPosition();
	
	CHECK_FALSE(doctest::Approx(bullet1Position[0])==bullet2Position[0]);
	CHECK_FALSE(doctest::Approx(bullet1Position[1])==bullet2Position[1]);
	CHECK_FALSE(doctest::Approx(bullet2Position[0])==bullet3Position[0]);
	CHECK_FALSE(doctest::Approx(bullet2Position[1])==bullet3Position[1]);
	CHECK_FALSE(doctest::Approx(bullet1Position[0])==bullet3Position[0]);
	CHECK_FALSE(doctest::Approx(bullet1Position[1])==bullet3Position[1]);
}

TEST_CASE("Multiple bullets have different flight angles if they are fired from different positions")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.0f;
	float moveTime = 0.9f;
	float bulletFlightTime = 0.1f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,moveTime);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	
	testPlayer.Update(direction,moveTime);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	movingEntity::entityList[2]->Update(1,bulletFlightTime);
	float bullet1Angle = movingEntity::entityList[0]->getAngle();
	float bullet2Angle = movingEntity::entityList[1]->getAngle();
	float bullet3Angle = movingEntity::entityList[2]->getAngle();
	
	CHECK_FALSE(doctest::Approx(bullet1Angle)==bullet2Angle);
	CHECK_FALSE(doctest::Approx(bullet2Angle)==bullet3Angle);
	CHECK_FALSE(doctest::Approx(bullet3Angle)==bullet1Angle);
}

TEST_CASE("Two bullets shot from same position at different times, have the same angle but different position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.0f;
	float moveTime = 0.9f;
	float bulletFlightTime = 0.1f;
	
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,moveTime);
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	float bullet1Angle = movingEntity::entityList[0]->getAngle();
	std::vector<float> bullet1Position = movingEntity::entityList[0]->getPosition();
	float bullet2Angle = movingEntity::entityList[1]->getAngle();
	std::vector<float> bullet2Position = movingEntity::entityList[1]->getPosition();
	CHECK(doctest::Approx(bullet1Angle)==bullet2Angle);
	CHECK_FALSE(doctest::Approx(bullet1Position[0])==bullet2Position[0]);
	CHECK_FALSE(doctest::Approx(bullet1Position[1])==bullet2Position[1]);
}

TEST_CASE("Bullets fired at different positions travel at the same speed")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.0f;
	float moveTime = 0.9f;
	float bulletFlightTime = 0.1f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[0]->Update(1,bulletFlightTime);
	float bullet1DistanceToCenter = movingEntity::entityList[0]->getRadius();
	
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,moveTime);
	testPlayer.Update(shoot,shootTime);
	movingEntity::entityList[1]->Update(1,bulletFlightTime);
	float bullet2DistanceToCenter = movingEntity::entityList[1]->getRadius();
	CHECK(doctest::Approx(bullet1DistanceToCenter)==bullet2DistanceToCenter);
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of the enemy
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Enemy_movement_and_spawning"){
TEST_CASE("Created enemies start at the center of the circular screen")
{
	Enemy testEnemy;
	float circleScreenCenterX = 1920.0f/2.0f;
	float circleScreenCenterY = 1080.0f/2.0f;
	std::vector<float> initialEnemyPosition = testEnemy.getPosition();
	CHECK(doctest::Approx(circleScreenCenterX)==initialEnemyPosition[0]);
	CHECK(doctest::Approx(circleScreenCenterY)==initialEnemyPosition[1]);
}

TEST_CASE("A single enemy can move")
{
	Enemy testEnemy;
	std::vector<float> initialEnemyPosition = testEnemy.getPosition();
	float initialEnemyRadius = testEnemy.getRadius();
	float moveTime = 0.5f;
	int noUserInput = 0;
	testEnemy.Update(noUserInput,moveTime);
	std::vector<float> continuousEnemyPosition = testEnemy.getPosition();
	float continuousEnemyRadius = testEnemy.getRadius();
	CHECK_FALSE(doctest::Approx(initialEnemyPosition[0])==continuousEnemyPosition[0]);
	CHECK_FALSE(doctest::Approx(initialEnemyPosition[1])==continuousEnemyPosition[1]);
	CHECK(doctest::Approx(initialEnemyRadius) < continuousEnemyRadius);
}

TEST_CASE("A single enemy maintains a constant angle throughout flight")
{
	Enemy testEnemy;
	float initialEnemyAngle = testEnemy.getAngle();
	float moveTime = 0.5f;
	int noUserInput = 0;
	testEnemy.Update(noUserInput,moveTime);
	float continuousEnemyAngle = testEnemy.getAngle();
	CHECK(initialEnemyAngle == continuousEnemyAngle);
}

TEST_CASE("More than one enemy travels radially (constant angle and increasing radius)")
{
	Enemy testEnemy1;
	float initialEnemy1Angle = testEnemy1.getAngle();
	float initialEnemy1Radius = testEnemy1.getRadius();
	Enemy testEnemy2;
	float initialEnemy2Angle = testEnemy2.getAngle();
	float initialEnemy2Radius = testEnemy2.getRadius();
	float moveTime = 0.5f;
	int noUserInput = 0;
	testEnemy1.Update(noUserInput,moveTime);
	testEnemy2.Update(noUserInput,moveTime);
	float finalEnemy1Angle = testEnemy1.getAngle();
	float finalEnemy1Radius = testEnemy1.getRadius();
	float finalEnemy2Angle = testEnemy2.getAngle();
	float finalEnemy2Radius = testEnemy2.getRadius();
	CHECK(doctest::Approx(initialEnemy1Angle)==finalEnemy1Angle);
	CHECK(doctest::Approx(initialEnemy2Angle)==finalEnemy2Angle);
	CHECK(doctest::Approx(initialEnemy1Radius) < finalEnemy1Radius);
	CHECK(doctest::Approx(initialEnemy2Radius) < finalEnemy2Radius);
}

TEST_CASE("A single enemy is respawned to center once distance travelled is greater than radius of circular screen")
{
	Enemy testEnemy;
	float moveTime = 0.1f;
	float respawnTime = 0.0f;
	int noUserInput = 0;
	float maxRadius = 480.0f;
	while(testEnemy.getRadius() < maxRadius)
	{
		testEnemy.Update(noUserInput,moveTime);
	}
	testEnemy.Update(noUserInput,respawnTime);
	float expectedRadius = 0.0f;
	float actualRadius = testEnemy.getRadius();
	CHECK(doctest::Approx(actualRadius) == expectedRadius);
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of enemy bullets
// Enemy bullets are randomly generated when a random number generator is equal to a specific number. For the sake of the basic movement
// tests of the enemy bullets, the random generation/creation of the enemy bullets is bypassed and the tests are peformed on manually generated
// enemy bullets.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Enemy_bullet_movement_and_spawning"){
TEST_CASE("An enemy bullet can be created")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	testEnemy.createBullets();
	int numberOfBulletsCreated = 0;
	for(unsigned int i=0; i< movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::EnemyBulletEntity)
		{
			numberOfBulletsCreated++;
		}
	}
	int numberOfBulletsExpected = 1;
	CHECK(numberOfBulletsCreated==numberOfBulletsExpected);
}

TEST_CASE("More than one enemybullet can be created")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	testEnemy.createBullets();
	testEnemy.createBullets();
	testEnemy.createBullets();
	int numberOfBulletsCreated = 0;
	for(unsigned int i=0; i< movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::EnemyBulletEntity)
		{
			numberOfBulletsCreated++;
		}
	}
	int numberOfBulletsExpected = 3;
	CHECK(numberOfBulletsCreated==numberOfBulletsExpected);
}

TEST_CASE("The enemey bullet's position is the same as the enemy's position when the enemy shoots from spawning position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	std::vector<float> initialEnemyPosition = testEnemy.getPosition();
	testEnemy.createBullets();
	std::vector<float> initialBulletPosition = movingEntity::entityList[0]->getPosition();
	CHECK(doctest::Approx(initialEnemyPosition[0])==initialBulletPosition[0]);
	CHECK(doctest::Approx(initialEnemyPosition[1])==initialBulletPosition[1]);
}

TEST_CASE("The enemey bullet's position is the same as the enemy's position when the enemy shoots from any position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float enemyFlightTime = 0.7f;
	testEnemy.Update(noUserInput,enemyFlightTime);
	std::vector<float> enemyPosition = testEnemy.getPosition();
	testEnemy.createBullets();
	std::vector<float> bulletPosition = movingEntity::entityList[0]->getPosition();
	CHECK(doctest::Approx(enemyPosition[0])==bulletPosition[0]);
	CHECK(doctest::Approx(enemyPosition[1])==bulletPosition[1]);
}

TEST_CASE("The enemey bullet's angle is the same as the enemy's angle when the enemy shoots from spawning position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	float initialEnemyAngle = testEnemy.getAngle();
	testEnemy.createBullets();
	float initialBulletAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(initialEnemyAngle)==initialBulletAngle);
}

TEST_CASE("The enemey bullet's angle is the same as the enemy's angle when the enemy shoots from any position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float enemyFlightTime = 0.7f;
	testEnemy.Update(noUserInput,enemyFlightTime);
	float enemyAngle = testEnemy.getAngle();
	testEnemy.createBullets();
	float bulletAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(enemyAngle)==bulletAngle);
}
TEST_CASE("The enemy bullet travels with a constant angle when shot from spawning position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float bulletFlightTime = 0.4f;
	testEnemy.createBullets();
	float initialBulletAngle = movingEntity::entityList[0]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	float finalBulletAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(initialBulletAngle)==finalBulletAngle);
}

TEST_CASE("The enemy bullet travels with a constant angle when shot from any position")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float enemyFlightTime = 0.4f;
	float bulletFlightTime = 0.4f;
	testEnemy.Update(noUserInput,enemyFlightTime);
	testEnemy.createBullets();
	float initialBulletAngle = movingEntity::entityList[0]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	float finalBulletAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(initialBulletAngle)==finalBulletAngle);
}

TEST_CASE("The enemy bullet travels such that its distance from the center of the screen increases as game time increases")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float enemyFlightTime = 0.4f;
	float bulletFlightTime = 0.4f;
	testEnemy.Update(noUserInput,enemyFlightTime);
	testEnemy.createBullets();
	float initialDistanceToCenter = movingEntity::entityList[0]->getRadius();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	float finalDistanceToCenter = movingEntity::entityList[0]->getRadius();
	CHECK(doctest::Approx(finalDistanceToCenter) > initialDistanceToCenter);
}

TEST_CASE("The enemy bullet travels at a faster speed than that of the enemy")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	int noUserInput = 0;
	float enemyFlightTime = 0.4f;
	float bulletFlightTime = 0.4f;
	float initialEnemyDistanceToCenter = testEnemy.getRadius();
	testEnemy.createBullets();
	float initialBulletDistanceToCenter = movingEntity::entityList[0]->getRadius();
	CHECK(doctest::Approx(initialEnemyDistanceToCenter)==initialBulletDistanceToCenter);
	testEnemy.Update(noUserInput,enemyFlightTime);
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	float finalEnemyDistanceToCenter = testEnemy.getRadius();
	float finalBulletDistanceToCenter = movingEntity::entityList[0]->getRadius();
	CHECK(doctest::Approx(finalBulletDistanceToCenter) > finalEnemyDistanceToCenter);
}

TEST_CASE("The positions of more than one enemy bullet can be tracked from different enemies")
{
	movingEntity::entityList.clear();
	Enemy testEnemy1;
	Enemy testEnemy2;
	testEnemy1.createBullets();
	testEnemy2.createBullets();
	int noUserInput = 0;
	float bullet1FlightTime = 0.4f;
	float bullet2FlightTime = 0.6f;
	movingEntity::entityList[0]->Update(noUserInput,bullet1FlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bullet2FlightTime);
	std::vector<float> bullet1Position = movingEntity::entityList[0]->getPosition();
	std::vector<float> bullet2Position = movingEntity::entityList[1]->getPosition();
	CHECK_FALSE(doctest::Approx(bullet1Position[0])==bullet2Position[0]);
	CHECK_FALSE(doctest::Approx(bullet1Position[1])==bullet2Position[1]);
}

TEST_CASE("The angles of more than one enemy bullet can be tracked from different enemies")
{
	movingEntity::entityList.clear();
	Enemy testEnemy1;
	Enemy testEnemy2;
	testEnemy1.createBullets();
	testEnemy2.createBullets();
	float initialBullet1Angle = movingEntity::entityList[0]->getAngle();
	float initialBullet2Angle = movingEntity::entityList[1]->getAngle();
	int noUserInput = 0;
	float bullet1FlightTime = 0.4f;
	float bullet2FlightTime = 0.6f;
	movingEntity::entityList[0]->Update(noUserInput,bullet1FlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bullet2FlightTime);
	float finalBullet1Angle = movingEntity::entityList[0]->getAngle();
	float finalBullet2Angle = movingEntity::entityList[1]->getAngle();
	CHECK(doctest::Approx(initialBullet1Angle)==finalBullet1Angle);
	CHECK(doctest::Approx(initialBullet2Angle)==finalBullet2Angle);
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of the Asteroid
// Asteroids are randomly generated when a random number generator is equal to a specific number. For the sake of the basic movement
// tests of the asteroids, the random generation/creation of the asteroids is bypassed and the tests are peformed on manually generated
// asteroids.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Asteroid_movement_and_spawning"){
TEST_CASE("A single asteroid can be created")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	int numberOfAsteroidsCreated = 0;
	
	for(unsigned int i = 0; i<movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::AsteroidEntity)
		{
			numberOfAsteroidsCreated++;
		}
	}
	int numberOfAsteroidsExpected = 1;
	CHECK(numberOfAsteroidsCreated == numberOfAsteroidsExpected);
}
TEST_CASE("More than one asteroid can be created")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	movingEntity::entityList.push_back(asteroidPtr);
	int numberOfAsteroidsCreated = 0;
	for(unsigned int i = 0; i<movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::AsteroidEntity)
		{
			numberOfAsteroidsCreated++;
		}
	}
	int numberOfAsteroidsExpected = 2;
	CHECK(numberOfAsteroidsCreated == numberOfAsteroidsExpected);
}

TEST_CASE("Asteroids have a starting/spawning position at the center of the circular screen when player is at starting position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	std::vector<float> initialAsteroidPosition = movingEntity::entityList[0]->getPosition();
	float circleScreenCenterX = 1920.0f/2.0f;
	float circleScreenCenterY = 1080.0f/2.0f;
	CHECK(doctest::Approx(circleScreenCenterX)==initialAsteroidPosition[0]);
	CHECK(doctest::Approx(circleScreenCenterY)==initialAsteroidPosition[1]);
}

TEST_CASE("Asteroids have a starting/spawning position at the center of the circular screen when player is at arbitrary position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerMoveTime = 0.5f;
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,playerMoveTime);
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	std::vector<float> initialAsteroidPosition = movingEntity::entityList[0]->getPosition();
	float circleScreenCenterX = 1920.0f/2.0f;
	float circleScreenCenterY = 1080.0f/2.0f;
	CHECK(doctest::Approx(circleScreenCenterX)==initialAsteroidPosition[0]);
	CHECK(doctest::Approx(circleScreenCenterY)==initialAsteroidPosition[1]);
}

TEST_CASE("Asteroids have a starting/spawning angle that is the same as the player's current angle")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle1 = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr1{ new Asteroid{playerAngle1}};
	movingEntity::entityList.push_back(asteroidPtr1);
	float initialAsteroid1Angle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(playerAngle1)==initialAsteroid1Angle);
	
	float playerMoveTime = 0.5f;
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,playerMoveTime);
	float playerAngle2 = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr2{ new Asteroid{playerAngle2}};
	movingEntity::entityList.push_back(asteroidPtr2);
	float initialAsteroid2Angle = movingEntity::entityList[1]->getAngle();
	CHECK(doctest::Approx(playerAngle2)==initialAsteroid2Angle);
	CHECK_FALSE(doctest::Approx(initialAsteroid1Angle)==initialAsteroid2Angle);
}

TEST_CASE("Asteroids maintain a constant angle throughout flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerMoveTime = 0.5f;
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,playerMoveTime);
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	float initialAsteroidAngle = movingEntity::entityList[0]->getAngle();
	int noUserInput = 0;
	float asteroidFlightTime = 0.7f;
	movingEntity::entityList[0]->Update(noUserInput,asteroidFlightTime);
	float finalAsteroidAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(initialAsteroidAngle)==finalAsteroidAngle);
}

TEST_CASE("Asteroids maintain a constant angle throughout flight while player moves")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float initialPlayerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{initialPlayerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	float initialAsteroidAngle = movingEntity::entityList[0]->getAngle();
	float playerMoveTime = 0.5f;
	userInput right = userInput::PressRight;
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,playerMoveTime);
	float finalPlayerAngle = testPlayer.getAngle();
	CHECK_FALSE(doctest::Approx(initialPlayerAngle) == finalPlayerAngle);
	int noUserInput = 0;
	float asteroidFlightTime = 0.6f;
	movingEntity::entityList[0]->Update(noUserInput,asteroidFlightTime);
	float finalAsteroidAngle = movingEntity::entityList[0]->getAngle();
	CHECK(doctest::Approx(initialAsteroidAngle)==finalAsteroidAngle);
}

TEST_CASE("The asteroid's distance to the center of the screen increases as game time increases")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	float initialAsteroidRadius = movingEntity::entityList[0]->getRadius();
	int noUserInput = 0;
	float asteroidFlightTime = 0.5f;
	movingEntity::entityList[0]->Update(noUserInput,asteroidFlightTime);
	float finalAsteroidRadius = movingEntity::entityList[0]->getRadius();
	CHECK(doctest::Approx(finalAsteroidRadius) > initialAsteroidRadius);
}
}

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of the Satelites
// Satelites are randomly generated when a random number generator is equal to a specific number. For the sake of the basic movement
// tests of the satelites, the random generation/creation of the satelites is bypassed and the tests are peformed on manually generated
// satelites.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Satellite_movement_and_spawning"){
TEST_CASE("More than one satelite can exist at a time")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	int numberSatellitesMade = 0;
	
	for(unsigned int i=0; i<movingEntity::entityList.size();i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::SatelliteEntity)
		{
			numberSatellitesMade++;
		}
	}
	int numberSatellitesExpected = 3;
	CHECK(numberSatellitesMade == numberSatellitesExpected);
}

TEST_CASE("All satelites have the same initial radius")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	float satellite1Radius = movingEntity::entityList[0]->getRadius();
	float satellite2Radius = movingEntity::entityList[1]->getRadius();
	float satellite3Radius = movingEntity::entityList[2]->getRadius();
	CHECK(doctest::Approx(satellite1Radius)==satellite2Radius);
	CHECK(doctest::Approx(satellite2Radius)==satellite3Radius);
	CHECK(doctest::Approx(satellite3Radius)==satellite1Radius);
}

TEST_CASE("All satellites maintain the initial radius while moving/gyrating")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	float initialSatellite1Radius = movingEntity::entityList[0]->getRadius();
	float initialSatellite2Radius = movingEntity::entityList[1]->getRadius();
	float initialSatellite3Radius = movingEntity::entityList[2]->getRadius();
	int noUserInput = 0;
	float moveTime = 1.0f;
	movingEntity::entityList[0]->Update(noUserInput,moveTime);
	movingEntity::entityList[1]->Update(noUserInput,moveTime);
	movingEntity::entityList[2]->Update(noUserInput,moveTime);
	float finalSatellite1Radius = movingEntity::entityList[0]->getRadius();
	float finalSatellite2Radius = movingEntity::entityList[1]->getRadius();
	float finalSatellite3Radius = movingEntity::entityList[2]->getRadius();
	
	CHECK(doctest::Approx(initialSatellite1Radius)==finalSatellite1Radius);
	CHECK(doctest::Approx(initialSatellite2Radius)==finalSatellite2Radius);
	CHECK(doctest::Approx(initialSatellite3Radius)==finalSatellite3Radius);
}

TEST_CASE("All satellites move/gyrate in an anti-clockwise direction")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	float initialSatellite1Angle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2Angle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3Angle = movingEntity::entityList[2]->getAngle();
	int noUserInput = 0;
	float moveTime = 1.0f;
	movingEntity::entityList[0]->Update(noUserInput,moveTime);
	movingEntity::entityList[1]->Update(noUserInput,moveTime);
	movingEntity::entityList[2]->Update(noUserInput,moveTime);
	float finalSatellite1Angle = movingEntity::entityList[0]->getAngle();
	float finalSatellite2Angle = movingEntity::entityList[1]->getAngle();
	float finalSatellite3Angle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialSatellite1Angle) > finalSatellite1Angle);
	CHECK(doctest::Approx(initialSatellite2Angle) > finalSatellite2Angle);
	CHECK(doctest::Approx(initialSatellite3Angle) > finalSatellite3Angle);
	
}

TEST_CASE("Angle between each gyrating satellite is initially 120 degrees (2*pi/3 rad)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	float initialSatellite1Angle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2Angle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3Angle = movingEntity::entityList[2]->getAngle();
	const float expectedAngleDifference = 2.0f*M_PI/3.0f;
	CHECK(doctest::Approx(abs(initialSatellite1Angle-initialSatellite2Angle))==expectedAngleDifference);
	CHECK(doctest::Approx(abs(initialSatellite2Angle-initialSatellite3Angle))==expectedAngleDifference);
	CHECK(doctest::Approx(abs(initialSatellite3Angle-initialSatellite1Angle))==2.0f*expectedAngleDifference);
}

TEST_CASE("Angle between each satellite is 120 degrees (2*pi/3 rad) while satelites are gyrating")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	int noUserInput = 0;
	float moveTime = 1.0f;
	movingEntity::entityList[0]->Update(noUserInput,moveTime);
	movingEntity::entityList[1]->Update(noUserInput,moveTime);
	movingEntity::entityList[2]->Update(noUserInput,moveTime);
	float satellite1Angle = movingEntity::entityList[0]->getAngle();
	float satellite2Angle = movingEntity::entityList[1]->getAngle();
	float satellite3Angle = movingEntity::entityList[2]->getAngle();
	const float expectedAngleDifference = 2.0f*M_PI/3.0f;
	CHECK(doctest::Approx(abs(satellite1Angle-satellite2Angle))==expectedAngleDifference);
	CHECK(doctest::Approx(abs(satellite2Angle-satellite3Angle))==expectedAngleDifference);
	CHECK(doctest::Approx(abs(satellite3Angle-satellite1Angle))==2.0f*expectedAngleDifference);
}

TEST_CASE("All the satellites gyrate aound the same center point")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	std::vector<float> satellite1Position = movingEntity::entityList[0]->getPosition();
	float satellite1Angle = movingEntity::entityList[0]->getAngle();
	float satellite1Radius = movingEntity::entityList[0]->getRadius();
	std::vector<float> satellite2Position = movingEntity::entityList[1]->getPosition();
	float satellite2Angle = movingEntity::entityList[1]->getAngle();
	float satellite2Radius = movingEntity::entityList[1]->getRadius();
	std::vector<float> satellite3Position = movingEntity::entityList[2]->getPosition();
	float satellite3Angle = movingEntity::entityList[2]->getAngle();
	float satellite3Radius = movingEntity::entityList[2]->getRadius();
	float satellite1CenterX = satellite1Position[0] - satellite1Radius*cosf(satellite1Angle);
	float satellite1CenterY = satellite1Position[1] - satellite1Radius*sinf(satellite1Angle);
	float satellite2CenterX = satellite2Position[0] - satellite2Radius*cosf(satellite2Angle);
	float satellite2CenterY = satellite2Position[1] - satellite2Radius*sinf(satellite2Angle);
	float satellite3CenterX = satellite3Position[0] - satellite3Radius*cosf(satellite3Angle);
	float satellite3CenterY = satellite3Position[1] - satellite3Radius*sinf(satellite3Angle);
	
	CHECK(doctest::Approx(satellite1CenterX)==satellite2CenterX);
	CHECK(doctest::Approx(satellite2CenterX)==satellite3CenterX);
	CHECK(doctest::Approx(satellite3CenterX)==satellite1CenterX);
	CHECK(doctest::Approx(satellite1CenterY)==satellite2CenterY);
	CHECK(doctest::Approx(satellite2CenterY)==satellite3CenterY);
	CHECK(doctest::Approx(satellite3CenterY)==satellite1CenterY);
}
}

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of Satellite bullets (of type EnemyBullets)
// Satelite bullets are randomly generated when a random number generator is equal to a specific number. For the sake of the basic movement
// tests of the satelite bullets, the random generation/creation of the satelite bullets is bypassed and the tests are peformed on manually generated
// satelite bullets.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Satellite_bullet_movement_and_spawning"){
TEST_CASE("Satellite bullets can be created")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int numberSatelliteBulletsMade = 0;
	for(unsigned int i=0; i<movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::EnemyBulletEntity)
		{
			numberSatelliteBulletsMade++;
		}
	}
	int numberEnemyBulletsExpected = 3;
	CHECK(numberSatelliteBulletsMade==numberEnemyBulletsExpected);
}

TEST_CASE("Satellite bullet initially has the same position as the satellite it was shot from ")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	std::vector<float> satellite1Position = satellite1.getPosition();
	satellite1.createBullets();
	std::vector<float> satellite1BulletPosition = movingEntity::entityList[0]->getPosition();
	
	CHECK(doctest::Approx(satellite1Position[0])==satellite1BulletPosition[0]);
	CHECK(doctest::Approx(satellite1Position[1])==satellite1BulletPosition[1]);
}

TEST_CASE("All satellite bullets have a starting angle of 270 degrees (3*pi/2 radians) clockwise from positive x-axis if they are spawned in top right quadrant")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 4.0f; //time needed to get player to top right quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	float satellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float satellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float satellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	float expectedBulletAngle = 3.0f*M_PI/2.0f;
	
	CHECK(doctest::Approx(satellite1BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite2BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite3BulletAngle)==expectedBulletAngle);
}

TEST_CASE("All satellite bullets have a starting angle of 180 degrees (pi radians) clockwise from positive x-axis if they are spawned in top left quadrant")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 2.8f; //time needed to get player to top left quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	float satellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float satellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float satellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	float expectedBulletAngle = M_PI;
	
	CHECK(doctest::Approx(satellite1BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite2BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite3BulletAngle)==expectedBulletAngle);
}

TEST_CASE("All satellite bullets have a starting angle of 90 degrees (pi/2 radians) clockwise from positive x-axis if they are spawned in bottom left quadrant")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 0.8f; //time needed to get player to bottom left quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	float satellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float satellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float satellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	float expectedBulletAngle = M_PI/2.0f;
	
	CHECK(doctest::Approx(satellite1BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite2BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite3BulletAngle)==expectedBulletAngle);
}

TEST_CASE("All satellite bullets have a starting angle of 0 degrees (0 radians) clockwise from positive x-axis if they are spawned in bottom right quadrant")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput left = userInput::PressLeft;
	float movementTime = 0.8f; //time needed to get player to bottom left quadrant
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	float satellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float satellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float satellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	float expectedBulletAngle = 0.0f;
	
	CHECK(doctest::Approx(satellite1BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite2BulletAngle)==expectedBulletAngle);
	CHECK(doctest::Approx(satellite3BulletAngle)==expectedBulletAngle);
}

TEST_CASE("Satellite bullets shot from top right quadrant maintain a constant angle throughout flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 4.0f; //time needed to get player to top right quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int noUserInput = 0;
	float bulletFlightTime = 0.2f;
	float initialSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[2]->Update(noUserInput,bulletFlightTime);
	float finalSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float finalSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float finalSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialSatellite1BulletAngle)==finalSatellite1BulletAngle);
	CHECK(doctest::Approx(initialSatellite2BulletAngle)==finalSatellite2BulletAngle);
	CHECK(doctest::Approx(initialSatellite3BulletAngle)==finalSatellite3BulletAngle);
	
}

TEST_CASE("Satellite bullets shot from top left quadrant maintain a constant angle throughout flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 2.8f; //time needed to get player to top left quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int noUserInput = 0;
	float bulletFlightTime = 0.2f;
	float initialSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[2]->Update(noUserInput,bulletFlightTime);
	float finalSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float finalSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float finalSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialSatellite1BulletAngle)==finalSatellite1BulletAngle);
	CHECK(doctest::Approx(initialSatellite2BulletAngle)==finalSatellite2BulletAngle);
	CHECK(doctest::Approx(initialSatellite3BulletAngle)==finalSatellite3BulletAngle);
}

TEST_CASE("Satellite bullets shot from bottom left quadrant maintain a constant angle throughout flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput right = userInput::PressRight;
	float movementTime = 0.8f; //time needed to get player to bottom left quadrant
	int direction = testPlayer.MovementDirection(right);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int noUserInput = 0;
	float bulletFlightTime = 0.2f;
	float initialSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[2]->Update(noUserInput,bulletFlightTime);
	float finalSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float finalSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float finalSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialSatellite1BulletAngle)==finalSatellite1BulletAngle);
	CHECK(doctest::Approx(initialSatellite2BulletAngle)==finalSatellite2BulletAngle);
	CHECK(doctest::Approx(initialSatellite3BulletAngle)==finalSatellite3BulletAngle);
	
}

TEST_CASE("Satellite bullets shot from bottom right quadrant maintain a constant angle throughout flight")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	userInput left = userInput::PressLeft;
	float movementTime = 0.8f; //time needed to get player to bottom right quadrant
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int noUserInput = 0;
	float bulletFlightTime = 0.2f;
	float initialSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float initialSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float initialSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	movingEntity::entityList[2]->Update(noUserInput,bulletFlightTime);
	float finalSatellite1BulletAngle = movingEntity::entityList[0]->getAngle();
	float finalSatellite2BulletAngle = movingEntity::entityList[1]->getAngle();
	float finalSatellite3BulletAngle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialSatellite1BulletAngle)==finalSatellite1BulletAngle);
	CHECK(doctest::Approx(initialSatellite2BulletAngle)==finalSatellite2BulletAngle);
	CHECK(doctest::Approx(initialSatellite3BulletAngle)==finalSatellite3BulletAngle);
	
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the movement and spawning of Laser Arc and generators
// Laser genrators and laser arcs are randomly generated when a random number generator is equal to a specific number. For the sake of the basic movement
// tests of the laser genrators and laser arcs, the random generation/creation of the laser genrators and laser arcs is bypassed and the tests are peformed on manually generated
// laser genrators and laser arcs.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Laser_generator_and_arc_movement_and_spawning"){
TEST_CASE("A laser arc and its generators can be created")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int numberOfLaserGeneratorsMade = 0;
	for(unsigned int i=0; i<movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::LaserEntity)
		{
			numberOfLaserGeneratorsMade++;
		}
	}
	
	int numberOfLaserArcsMade = 0;
	for(unsigned int i=0; i<movingEntity::entityList.size(); i++)
	{
		if(movingEntity::entityList[i]->getEntityType() == EntityList::ArcEntity)
		{
			numberOfLaserArcsMade++;
		}
	}
	int numberOfExpectedGenerators = 2;
	int numberOfExpectedLaserArcs = 1;
	
	CHECK(numberOfLaserGeneratorsMade == numberOfExpectedGenerators);
	CHECK(numberOfLaserArcsMade == numberOfExpectedLaserArcs);
}

TEST_CASE("The laser generators are spawned at the center of the screen")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::vector<float> generator1Position = movingEntity::entityList[0]->getPosition();
	std::vector<float> generator2Position = movingEntity::entityList[1]->getPosition();
	float expectedXposition = 1920.0/2.0;
	float expectedYposition = 1080.0/2.0;
	
	CHECK(doctest::Approx(generator1Position[0]) == expectedXposition);
	CHECK(doctest::Approx(generator1Position[1]) == expectedYposition);
	CHECK(doctest::Approx(generator2Position[0]) == expectedXposition);
	CHECK(doctest::Approx(generator2Position[1]) == expectedYposition);
}

TEST_CASE("The laser arc is spawned at the center of the screen")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	
	float laserArcDistanceToCenter = movingEntity::entityList[2]->getRadius();
	float expectedArcDistanceToCenter = 0.0f;
	std::vector<float> laserArcPosition = movingEntity::entityList[2]->getPosition();
	float expectedXposition = 1920.0/2.0;
	float expectedYposition = 1080.0/2.0;
	
	CHECK(doctest::Approx(laserArcDistanceToCenter) == expectedArcDistanceToCenter);
	CHECK(doctest::Approx(laserArcPosition[0]) == expectedXposition);
	CHECK(doctest::Approx(laserArcPosition[1]) == expectedYposition);
}

TEST_CASE("The laser generators travel with a constant angle")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	float initialGenerator1Angle = movingEntity::entityList[0]->getAngle();
	float initialGenerator2Angle = movingEntity::entityList[1]->getAngle();
	
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[0]->Update(noUserInput,flightTime);
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	float finalGenerator1Angle = movingEntity::entityList[0]->getAngle();
	float finalGenerator2Angle = movingEntity::entityList[1]->getAngle();
	
	CHECK(doctest::Approx(initialGenerator1Angle) == finalGenerator1Angle);
	CHECK(doctest::Approx(initialGenerator2Angle) == finalGenerator2Angle);
}

TEST_CASE("The angle between the generators is always 50 degrees (0.872664 radians)")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	float initialGenerator1Angle = movingEntity::entityList[0]->getAngle();
	float initialGenerator2Angle = movingEntity::entityList[1]->getAngle();
	float angleDifference = initialGenerator1Angle - initialGenerator2Angle;
	float angleDifferenceExpected = 0.872664f; //calculated
	
	CHECK(doctest::Approx(angleDifference) == angleDifferenceExpected);
}

TEST_CASE("The angle of the laser arc remains constant during flight")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	float initialLaserArcAngle = movingEntity::entityList[2]->getAngle();
	
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[0]->Update(noUserInput,flightTime);
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	float finalLaserArcAngle = movingEntity::entityList[2]->getAngle();
	
	CHECK(doctest::Approx(initialLaserArcAngle) == finalLaserArcAngle);
}
TEST_CASE("The angle of the laser arc is always a midpoint value between the angles of the generators")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	float initialGenerator1Angle = movingEntity::entityList[0]->getAngle();
	float initialGenerator2Angle = movingEntity::entityList[1]->getAngle();
	float initialLaserArcAngle = movingEntity::entityList[2]->getAngle();
	float expectedInitialLaserArcAngle = (initialGenerator1Angle + initialGenerator2Angle)/2.0f;
	
	CHECK(doctest::Approx(initialLaserArcAngle) == expectedInitialLaserArcAngle);
}

TEST_CASE("The laser generators and the laser arc travel such that their distances from the center always increase")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	float initialGenerator1Radius = movingEntity::entityList[0]->getRadius();
	float initialGenerator2Radius = movingEntity::entityList[1]->getRadius();
	float initialLaserArcRadius = movingEntity::entityList[2]->getRadius();
	
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[0]->Update(noUserInput,flightTime);
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	float finalGenerator1Radius = movingEntity::entityList[0]->getRadius();
	float finalGenerator2Radius = movingEntity::entityList[1]->getRadius();
	float finalLaserArcRadius = movingEntity::entityList[2]->getRadius();
	
	CHECK(doctest::Approx(initialGenerator1Radius) < finalGenerator1Radius);
	CHECK(doctest::Approx(initialGenerator2Radius) < finalGenerator2Radius);
	CHECK(doctest::Approx(initialLaserArcRadius) < finalLaserArcRadius);
}
}

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//  Testing the lives and relations of entity lives
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Lives"){
TEST_CASE("The player has 5 lives at the start of the game")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	int startingNumberOfPlayerLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 5;
	
	CHECK(startingNumberOfPlayerLives == expectedNumberOfLives);
}

TEST_CASE("The enemy has one life at the start of the game")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	movingEntity::entityList.push_back(enemyPtr);
	int startingNumberOfEnemyLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfEnemyLives == expectedNumberOfLives);
}

TEST_CASE("The player bullets have one life")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int startingNumberOfPlayerBulletLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfPlayerBulletLives == expectedNumberOfLives);
}

TEST_CASE("The enemy bullets have one life")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	testEnemy.createBullets();
	int startingNumberOfEnemyBulletLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfEnemyBulletLives == expectedNumberOfLives);
}

TEST_CASE("The asteroids have one life")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	int startingNumberOfAsteroidLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfAsteroidLives == expectedNumberOfLives);
}

TEST_CASE("Each of the satelites have one life")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	int startingNumberOfSatellite1Lives = movingEntity::entityList[0]->getLives();
	int startingNumberOfSatellite2Lives = movingEntity::entityList[1]->getLives();
	int startingNumberOfSatellite3Lives = movingEntity::entityList[2]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfSatellite1Lives == expectedNumberOfLives);
	CHECK(startingNumberOfSatellite2Lives == expectedNumberOfLives);
	CHECK(startingNumberOfSatellite3Lives == expectedNumberOfLives);
}

TEST_CASE("Satellite bullets have one life")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	int startingNumberOfSatellite1BulletLives = movingEntity::entityList[0]->getLives();
	int startingNumberOfSatellite2BulletLives = movingEntity::entityList[1]->getLives();
	int startingNumberOfSatellite3BulletLives = movingEntity::entityList[2]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfSatellite1BulletLives == expectedNumberOfLives);
	CHECK(startingNumberOfSatellite2BulletLives == expectedNumberOfLives);
	CHECK(startingNumberOfSatellite3BulletLives == expectedNumberOfLives);
}

TEST_CASE("The laser generators have one life")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	int startingNumberOfLaserGenerator1Lives = movingEntity::entityList[0]->getLives();
	int startingNumberOfLaserGenerator2Lives = movingEntity::entityList[1]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfLaserGenerator1Lives == expectedNumberOfLives);
	CHECK(startingNumberOfLaserGenerator2Lives == expectedNumberOfLives);
}

TEST_CASE("The laser arc has one life")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int startingNumberOfLaserArcLives = movingEntity::entityList[2]->getLives();
	int expectedNumberOfLives = 1;
	
	CHECK(startingNumberOfLaserArcLives == expectedNumberOfLives);
}

TEST_CASE("Player bullet loses a life when it reaches the center of the screen (less than minimum radius)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float shootTime = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,shootTime);
	int noUserInput =0;
	float bulletFlightTime = 4.8f;//time for player bullet to get to center of screen
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	
	bulletFlightTime = 0.0f;//time for updating bullet while not making it move further
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	int numberOfBulletLives = movingEntity::entityList[0]->getLives();
	int numberOfExpectedLives = 0;
	
	CHECK(numberOfBulletLives == numberOfExpectedLives);
}

TEST_CASE("The enemy bullet loses a life when it exceeds a maximum radius")
{
	movingEntity::entityList.clear();
	Enemy testEnemy;
	testEnemy.createBullets();
	
	int noUserInput = 0;
	float bulletFlightTime = 2.4f;//time taken for bullet to get to max radius (480)
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	bulletFlightTime = 0.0f;
	movingEntity::entityList[0]->Update(noUserInput,bulletFlightTime);
	int numberOfEnemyBulletLives = movingEntity::entityList[0]->getLives();
	int numberOfExpectedLives = 0;
	
	CHECK(numberOfEnemyBulletLives == numberOfExpectedLives);
}

TEST_CASE("The asteroid loses a life when it exceeds a maximum radius")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	
	int noUserInput = 0;
	float asteroidFlightTime = 4.8f;//time for asteroid to pass max radius
	movingEntity::entityList[0]->Update(noUserInput,asteroidFlightTime);
	asteroidFlightTime = 0.0f; //time so that asteroid does not move further but still updates
	movingEntity::entityList[0]->Update(noUserInput,asteroidFlightTime);
	int numberOfAsteroidLives = movingEntity::entityList[0]->getLives();
	int numberOfExpectedAsteroidLives = 0;
	
	CHECK(numberOfAsteroidLives == numberOfExpectedAsteroidLives);
}

TEST_CASE("If the first laser generator has zero lives, the laser arc loses a life")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	
	movingEntity::entityList[1]->collide();
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	movingEntity::entityList[3]->Update(noUserInput,flightTime);
	
	int laserArcLives = movingEntity::entityList[3]->getLives();
	int secondLaserGeneratorLives = movingEntity::entityList[2]->getLives();
	CHECK(laserArcLives == 0);
	CHECK(secondLaserGeneratorLives == 1);
}

TEST_CASE("If the second laser generator has zero lives, the laser arc loses a life")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	
	movingEntity::entityList[2]->collide();
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	movingEntity::entityList[3]->Update(noUserInput,flightTime);
	int laserArcLives = movingEntity::entityList[3]->getLives();
	int firstLaserGeneratorLives = movingEntity::entityList[1]->getLives();
	
	CHECK(laserArcLives == 0);
	CHECK(firstLaserGeneratorLives == 1);
}

TEST_CASE("The laser arc loses a life when it exceeds a maximum radius (470 pixels)")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int noUserInput = 0;
	float flightTime =10.9f;//time needed for arc to exceed max radius
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	movingEntity::entityList[3]->Update(noUserInput,flightTime);
	flightTime = 0.0f;
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	movingEntity::entityList[3]->Update(noUserInput,flightTime);

	int numberOfArcLives = movingEntity::entityList[3]->getLives();
	int expectedNumberOfLives = 0;
	
	CHECK(numberOfArcLives == expectedNumberOfLives);
}

TEST_CASE("The generators lose a life when they exceed a maximum radius (520 pixels)")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	
	int noUserInput = 0;
	float flightTime = 1.1f;
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	movingEntity::entityList[3]->Update(noUserInput,flightTime);
	
	float maxRadius = 520.0f;
	float laserGenerator1Radius = movingEntity::entityList[1]->getRadius();
	float laserGenerator2Radius = movingEntity::entityList[2]->getRadius();
	while(laserGenerator1Radius <= maxRadius && laserGenerator2Radius <= maxRadius)
	{
		movingEntity::entityList[1]->Update(noUserInput,flightTime);
		movingEntity::entityList[2]->Update(noUserInput,flightTime);
		movingEntity::entityList[3]->Update(noUserInput,flightTime);
		laserGenerator1Radius = movingEntity::entityList[1]->getRadius();
		laserGenerator2Radius = movingEntity::entityList[2]->getRadius();
	}
	movingEntity::entityList[1]->Update(noUserInput,flightTime);
	movingEntity::entityList[2]->Update(noUserInput,flightTime);
	int numberOfLaserGenerator1Lives = movingEntity::entityList[1]->getLives();
	int numberOfLaserGenerator2Lives = movingEntity::entityList[2]->getLives();
	
	CHECK(numberOfLaserGenerator1Lives == 0);
	CHECK(numberOfLaserGenerator2Lives == 0);
}
}

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the collision detection
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Collision_detection"){
TEST_CASE("The player bullet loses a life when it is at the same position as the enemy")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	movingEntity::entityList.push_back(enemyPtr);
	
	Player testPlayer;
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	int finalPlayerBulletLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalPlayerBulletLives == 0);
}

TEST_CASE("The enemy loses a life when it is at the same position as the player bullet")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	movingEntity::entityList.push_back(enemyPtr);
	
	Player testPlayer;
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	CollisionManager detection;
	detection.checkCollision();
	int finalEnemyLives = movingEntity::entityList[0]->getLives();
	
	CHECK(finalEnemyLives == 0);
}

TEST_CASE("The asteroid does not lose a life when the player bullet has the same position as the asteroid (player bullet loses a life)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalAsteroidLives = movingEntity::entityList[0]->getLives();
	
	CHECK(finalAsteroidLives == 1);
}

TEST_CASE("The player bullet loses a life when it has the same position as the asteroid")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	int finalPlayerBulletLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalPlayerBulletLives == 0);
}

TEST_CASE("The satellite and the player bullet lose a life when in the same position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	
	userInput left = userInput::PressLeft;
	float movementTime = 0.2642f; //time needed to get player to same sangle as a satelite
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	
	int noUserInput = 0;
	float bulletFlightTime = 1.4f; //time for player bullet to travel to satellite
	movingEntity::entityList[3]->Update(noUserInput,bulletFlightTime);
	std::vector<float> bulletPos = movingEntity::entityList[3]->getPosition();
	
	CollisionManager detection;
	detection.checkCollision();
	int finalSatelliteLives = movingEntity::entityList[0]->getLives();
	int finalPlayerBulletLives = movingEntity::entityList[3]->getLives();
	
	CHECK(finalSatelliteLives == 0);
	CHECK(finalPlayerBulletLives == 0);
}

TEST_CASE("The player loses a life when an asteroid has the same position as the player (asteroid loses a life)")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	float playerAngle = movingEntity::entityList[0]->getAngle();
	
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	int noUserInput = 0;
	float travelTime = 4.75f; //time for asteroid to get to player's position
	movingEntity::entityList[1]->Update(noUserInput, travelTime);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalPlayerLives = movingEntity::entityList[0]->getLives();
	int finalAsteroidLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalPlayerLives == 4);
	CHECK(finalAsteroidLives == 0);
}
TEST_CASE("No lives are lost (from the enemies or asteroids) when they are in the same position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	float playerAngle = testPlayer.getAngle();
	
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	
	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	movingEntity::entityList.push_back(enemyPtr);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalAsteroidLives = movingEntity::entityList[0]->getLives();
	int finalEnemyLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalAsteroidLives == 1);
	CHECK(finalEnemyLives == 1);
}

TEST_CASE("No lives are lost (from the satellites or asteroids) when they are in the same position ")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	
	userInput left = userInput::PressLeft;
	float movementTime = 0.2642f; //time needed to get player to same sangle as a satelite
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	playerAngle = testPlayer.getAngle();
	
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	
	int noUserInput = 0;
	float travelTime = 3.37f; //time for asteroid to get to satellite's position
	movingEntity::entityList[3]->Update(noUserInput,travelTime);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalAsteroidLives = movingEntity::entityList[3]->getLives();
	int finalSatelliteLives = movingEntity::entityList[0]->getLives();
	
	CHECK(finalAsteroidLives == 1);
	CHECK(finalSatelliteLives == 1);
}

TEST_CASE("Satellite bullets (which are of same type as enemy bullets) and the player lose a life when in the same position")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	float playerAngle = movingEntity::entityList[0]->getAngle();
	std::vector<float> playerPosition =  movingEntity::entityList[0]->getPosition();
	
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	satellite2.createBullets();
	satellite3.createBullets();
	
	int noUserInput = 0;
	float bulletTravelTime = 1.338f; //time for satellite bullet in get to perimeter of circle
	movingEntity::entityList[1]->Update(noUserInput,bulletTravelTime);
	
	float movementTime = 0.9f; //time needed to get player to same position as satellite bullet
	int direction = 1; //this will simulate the anticlockwise movement of the player
	movingEntity::entityList[0]->Update(direction,movementTime);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalPlayerLives = movingEntity::entityList[0]->getLives();
	int finalSatelliteBulletLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalPlayerLives == 4);
	CHECK(finalSatelliteBulletLives == 0);
}

TEST_CASE("The satellite bullet (enemy bullet) and the player bullet lose a life when they are in the same position")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	
	userInput left = userInput::PressLeft;
	//float movementTime = 0.2642f; //time needed to get player to same angle as a satelite bullet will be
	float movementTime = 0.29f; //time needed to get player to same angle as a satelite bullet will be
	int direction = testPlayer.MovementDirection(left);
	testPlayer.Update(direction,movementTime);
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	
	int noUserInput = 0;
	float bulletFlightTime = 1.4f; //time for player bullet to travel to where satellite will be
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	
	CollisionManager detection;
	detection.checkCollision();
	
	int finalPlayerBulletLives = movingEntity::entityList[0]->getLives();
	int finalSatelliteBulletLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalSatelliteBulletLives == 0);
	CHECK(finalPlayerBulletLives == 0);
	
}

TEST_CASE("The player bullet loses a life when it has the same posistion as the laser arc (laser does not lose a life)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[3]->Update(noUserInput,bulletFlightTime);
	int finalNumberOfLaserArcLives = movingEntity::entityList[2]->getLives();
	int finalNumberOfPlayerBulletLives = movingEntity::entityList[3]->getLives();
	
	CHECK(finalNumberOfLaserArcLives == 1);
	CHECK(finalNumberOfPlayerBulletLives == 0);
}

TEST_CASE("The player bullet loses a life when it is in the same position as the laser generator")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	movingEntity::entityList.push_back(laserPtr);
	
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	int finalNumberOfPlayerBulletLives = movingEntity::entityList[1]->getLives();
	
	CHECK(finalNumberOfPlayerBulletLives == 0);
}

TEST_CASE("The laser generator loses a life when it is in the same position as the player bullet")
{
	movingEntity::entityList.clear();
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	movingEntity::entityList.push_back(laserPtr);
	
	Player testPlayer;
	float time = 0.0f;
	userInput spacebar = userInput::PressSpace;
	int shoot = testPlayer.MovementDirection(spacebar);
	testPlayer.Update(shoot,time);
	int noUserInput = 0;
	float bulletFlightTime = 4.8f;
	movingEntity::entityList[1]->Update(noUserInput,bulletFlightTime);
	
	CollisionManager detection;
	detection.checkCollision();
	int finalNumberOfLaserGeneratorLives = movingEntity::entityList[0]->getLives();
	int expectedNumberOfLives = 0;
	
	CHECK(finalNumberOfLaserGeneratorLives == expectedNumberOfLives);
}
}

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the deletion of enities
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Entity_deletion"){
TEST_CASE("The enemy is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	movingEntity::entityList.push_back(enemyPtr);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 2);
	CHECK(finalNumberOfMovingEntities == 1);
}

TEST_CASE("The enemy bullet is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	Enemy testEnemy;
	testEnemy.createBullets();
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 2);
	CHECK(finalNumberOfMovingEntities == 1);
}

TEST_CASE("Player bullet is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	int simulatedShoot = 0;
	float time = 0.0f;
	movingEntity::entityList[0]->Update(simulatedShoot,time);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 2);
	CHECK(finalNumberOfMovingEntities == 1);
}

TEST_CASE("The asteroid is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	float playerAngle = movingEntity::entityList[0]->getAngle();
	std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerAngle}};
	movingEntity::entityList.push_back(asteroidPtr);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 2);
	CHECK(finalNumberOfMovingEntities == 1);
}

TEST_CASE("A satellite is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	float playerAngle = movingEntity::entityList[0]->getAngle();
	std::vector<float> playerPosition = movingEntity::entityList[0]->getPosition();
	
	std::shared_ptr <Satellite> satellitePtr{ new Satellite{playerPosition,playerAngle}};
	std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
	std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr);
	movingEntity::entityList.push_back(satellitePtr2);
	movingEntity::entityList.push_back(satellitePtr3);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	movingEntity::entityList[2]->collide();
	movingEntity::entityList[3]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 4);
	CHECK(finalNumberOfMovingEntities == 1);
	
}
TEST_CASE("Satellite bullet is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	float playerAngle = movingEntity::entityList[0]->getAngle();
	std::vector<float> playerPosition = movingEntity::entityList[0]->getPosition();
	Satellite satellite1(playerPosition,playerAngle);
	Satellite satellite2(satellite1);
	Satellite satellite3(satellite2);
	satellite1.createBullets();
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 2);
	CHECK(finalNumberOfMovingEntities == 1);
}

TEST_CASE("First laser generator is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[1]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 4);
	CHECK(finalNumberOfMovingEntities == 3);
}

TEST_CASE("Second laser generator is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[2]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 4);
	CHECK(finalNumberOfMovingEntities == 3);
}

TEST_CASE("The laser arc is erased when it has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
	std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
	movingEntity::entityList.push_back(laserPtr);
	movingEntity::entityList.push_back(laserPtr2);
	std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
	movingEntity::entityList.push_back(arcPtr);
	int initialNumberOfMovingEntities = movingEntity::entityList.size();
	
	movingEntity::entityList[3]->collide();
	CollisionManager detection;
	detection.entityCleanUp(playerPtr);
	int finalNumberOfMovingEntities = movingEntity::entityList.size();
	CHECK(initialNumberOfMovingEntities == 4);
	CHECK(finalNumberOfMovingEntities == 3);
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the upgrade in player bullets
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Player_bullet_upgrade"){
TEST_CASE("Player bullets are upgraded when 3 satellites are destroyed (2 bullets spawned per shot)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satelliteMonitor(playerPosition,playerAngle);
	satelliteMonitor.ResetSatellites();
	
	Satellite sat1(playerPosition,playerAngle);
	Satellite sat2(sat1);
	Satellite sat3(sat2);
	sat1.~Satellite(); //simulating killing of 3 satellites
	sat2.~Satellite();
	sat3.~Satellite();
	
	int numberOfBulletsBeforeShootingOnce = movingEntity::entityList.size();
	int shoot = 0; //to simulate a spacebar press 
	float time = 0.1f;
	testPlayer.Update(shoot,time);
	int numberOfBulletsAfterShootingOnce = movingEntity::entityList.size();
	CHECK(numberOfBulletsBeforeShootingOnce == 0);
	CHECK(numberOfBulletsAfterShootingOnce == 2);
}

TEST_CASE("The difference in angle between the two upgraded bullets is 3 degrees (0.0523598)")
{
	movingEntity::entityList.clear();
	Player testPlayer;
	std::vector<float> playerPosition = testPlayer.getPosition();
	float playerAngle = testPlayer.getAngle();
	Satellite satelliteMonitor(playerPosition,playerAngle);
	satelliteMonitor.ResetSatellites();
	
	Satellite sat1(playerPosition,playerAngle);
	Satellite sat2(sat1);
	Satellite sat3(sat2);
	sat1.~Satellite(); //simulating killing of 3 satellites
	sat2.~Satellite();
	sat3.~Satellite();
	
	int shoot = 0; //to simulate a spacebar press 
	float time = 0.1f;
	testPlayer.Update(shoot,time);
	
	float upgradedBullet1Angle = movingEntity::entityList[0]->getAngle();
	float upgradedBullet2Angle = movingEntity::entityList[1]->getAngle();
	float angleDifference = upgradedBullet1Angle - upgradedBullet2Angle;
	float expectedAngleDifference = 0.0523598f;
	CHECK(doctest::Approx(angleDifference) == expectedAngleDifference);
}
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
//Testing the changes in game state (win, lose, playing)
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Game_state"){
TEST_CASE("The game remains in the playing state when the player has more than zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	
	movingEntity::entityList[0]->collide();
	gameState expectedState = gameState::playing;
	
	CollisionManager detection;
	gameState actualState = detection.entityCleanUp(playerPtr);
	
	CHECK(expectedState == actualState);
}

TEST_CASE("The game enters a losing state when the player has zero lives left")
{
	movingEntity::entityList.clear();
	std::shared_ptr <Player> playerPtr{ new Player{}};
	movingEntity::entityList.push_back(playerPtr);
	
	movingEntity::entityList[0]->collide();
	movingEntity::entityList[0]->collide();
	movingEntity::entityList[0]->collide();
	movingEntity::entityList[0]->collide();
	movingEntity::entityList[0]->collide();
	gameState expectedState = gameState::lose;
	
	CollisionManager detection;
	gameState actualState = detection.entityCleanUp(playerPtr);
	
	CHECK(expectedState == actualState);
}
}

// The transition into a winning state could not be tested because the function required for this transition was found in the Game class and
// the required function was also a private member of the class. This is discussed further in the report.
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
