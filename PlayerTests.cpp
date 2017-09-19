#include "Player.h"
#include <SFML/Graphics.hpp>
#include "userInput.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Player is not initilised in the center of the screen")
{
	Player testPlayer;
	std::vector<float> position =testPlayer.getPostition();
	std::vector <float> origin(1920/2, 1080/2);
	CHECK_FALSE( position== origin);
}

TEST_CASE("Player is initialised at cartesian 270 degrees")
{
	Player testPlayer;
	auto angle =testPlayer.getAngle();
	auto expectedAngle= 90*pi/180;
	
	CHECK(doctest::Approx(angle) == expectedAngle);
}

TEST_CASE("Player moves anticlockwise when the left arrow is pressed")
{
	Player testPlayer;
	std::vector<float> initialPosition= testPlayer.getPostition();
	userInput left = userInput::PressLeft;
	bool direction = testPlayer.MovementDirection(left);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPostition();
	double factor = 0.9 * time;
	auto expectedAngle= 90*pi/180-factor;
	double x_center = 1920.0f / 2.0f;
	double y_center = 1080.0f / 2.0f;
	float radius = 480.0f;
	float calculatedpositionX=radius*cos(expectedAngle) + x_center;
	float calculatedpositionY=radius*sin(expectedAngle) + y_center;
	CHECK(doctest::Approx(calculatedpositionX)==finalPosition[0]);
	CHECK(doctest::Approx(calculatedpositionY)==finalPosition[1]);
}


TEST_CASE("Player moves clockwise when the left arrow is pressed")
{
	Player testPlayer;
	std::vector<float> initialPosition= testPlayer.getPostition();
	userInput right = userInput::PressRight;
	bool direction = testPlayer.MovementDirection(right);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPostition();
	double factor = 0.9 * time;
	auto expectedAngle= 90*pi/180+factor;
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
	std::vector<float> initialPosition= testPlayer.getPostition();
	userInput noInput = userInput::NoButtonPress;
	bool direction = testPlayer.MovementDirection(noInput);
	float time = 0.1f;
	testPlayer.Update(direction, time);
	std::vector<float> finalPosition= testPlayer.getPostition();
	CHECK(initialPosition==finalPosition);

}