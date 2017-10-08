#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>

/**
* Clock class - used to seperate the interface and logic layers
* The class manages all time based events
* Time is used to update the movement of the entities and to
* randomly generate new entities
*/
class Clock
{
public:
    /**
    * Default constructor. Creates a Clock object
    */
    Clock();
    /**
    * Default destructor
    */
    ~Clock();
    /**
    * Function to get the time elapsed since the last reset
    * @return float containing the elapsed time
    */
    float GetTime();
    /**
    * Function to get the total elapsed time used to randomly generate asteroid entities
    * @return float containing the total elapsed time
    */
    float getAsteroidTime();
    /**
    * Function to get the total elapsed time used to randomly generate satellite entities
    * @return float containing the total elapsed time
    */
    float getSatelliteTime();
    /**
    * Function to restart the elapsed time, as well as update the asteroid and satellite time
    */
    void RestartClock();
    /**
    * Function to restart the asteroid clock
    */
    void RestartAsteroidClock();
    /**
    * Function to restart the satellite clock
    */
    void RestartSatelliteClock();

private:
    sf::Clock _clock;
    sf::Clock _clockAsteroid;
    sf::Clock _clockSatellite;
    float _elapsedTime;
    float _timeAsteroid;
    float _timeSatellite;
};

#endif // CLOCK_H
