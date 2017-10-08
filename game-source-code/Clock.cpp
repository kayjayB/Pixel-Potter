#include "Clock.h"

Clock::Clock()
{
}

Clock::~Clock()
{
}

float Clock::GetTime()
{
    return _elapsedTime;
}

float Clock::getAsteroidTime()
{
    return _timeAsteroid;
}

float Clock::getSatelliteTime()
{
    return _timeSatellite;
}

void Clock::RestartClock()
{
    _elapsedTime = _clock.restart().asSeconds();
    _timeAsteroid = _clockAsteroid.getElapsedTime().asSeconds();
    _timeSatellite = _clockSatellite.getElapsedTime().asSeconds();
}

void Clock::RestartAsteroidClock()
{
    _clockAsteroid.restart();
}

void Clock::RestartSatelliteClock()
{
    _clockSatellite.restart();
}