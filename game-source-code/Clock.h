#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>

class Clock
{
public:
Clock();
~Clock();

float GetTime();

float getAsteroidTime();

float getSatelliteTime();

void RestartClock();

void RestartAsteroidClock();

void RestartSatelliteClock();
	
private:
sf::Clock _clock;
sf::Clock _clockEnemy;
sf::Clock _clockAsteroid;
sf::Clock _clockSatellite;
float _elapsedTime;
float _timeAsteroid;
float _timeSatellite;
};

#endif // CLOCK_H
