#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "userInput.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("The enemy spawns at the center of the circle screen")
{
	Enemy testEnemy;
	testEnemy.movement(0.0f);
	sf::Vector2f centerCircle(1920.0f/2.0f,1080.0f/2.0f);
	sf::Vector2f intialPosition = testEnemy.getPosition();
	CHECK(intialPosition==centerCircle);
}

TEST_CASE("The enemy maintains a constant angle")
{
	Enemy testEnemy;
	testEnemy.movement(0.0f);
	float angleAtPosition1 = testEnemy.getAngle();
	testEnemy.movement(5.0f);
	float angleAtPosition2 = testEnemy.getAngle();
	CHECK(doctest::Approx(angleAtPosition1) == angleAtPosition2);
}
