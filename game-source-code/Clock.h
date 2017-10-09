#ifndef CLOCK_H
#define CLOCK_H

#include <SFML/Graphics.hpp>

/**
* \brief Clock class - used to seperate the interface and logic layers.
* The class manages all time based events.
* Time is used to update the movement of the entities and to
* randomly generate new entities
*/
class Clock
{
public:
    /**
    * \brief Default constructor. Creates a Clock object
    */
    Clock();
    /**
    * \brief Default destructor
    */
    ~Clock();
    /**
    * \brief Function to get the time elapsed since the last reset
    * @return float containing the elapsed time
    */
    float GetTime();
    /**
    * \brief Function to get the total elapsed time used to randomly generate Asteroid entities
    * @return float containing the total elapsed time
    */
    float getAsteroidTime();
    /**
    * \brief Function to get the total elapsed time used to randomly generate Satellite entities
    * @return float containing the total elapsed time
    */
    float getSatelliteTime();
    /**
    * \brief Function to restart the elapsed time, as well as update the Asteroid and Satellite time
    */
    void RestartClock();
    /**
    * \brief Function to restart the Asteroid clock
    */
    void RestartAsteroidClock();
    /**
    * \brief Function to restart the Satellite clock
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

#endif 
