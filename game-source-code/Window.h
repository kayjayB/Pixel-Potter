#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "userInput.h"
#include "Enemy.h"
#include "movingEntity.h"
#include "gameState.h"
#include "EntityList.h"

/**
* FileNotFound class
* Throws an exception if a file to be opened cannot be found
*/
class FileNotFound
{
};

/**
* Window class
* Interface class - creates a window, draws the entities, displays the splashscreens
*/
class Window
{

public:
	/**
	* Default Constructor. 
	* Creates a new window 
	*/
    Window();
	/**
	* Function to close the window
	*/
    void closeWindow();
	/**
	* Function to clear the window prior to drawing
	*/
    void BeginDraw();
	/**
	* Function to display the window
	*/
    void EndDraw();
	/**
	* Function to clear the window prior to drawing and set the background 
	* for the main game
	*/
    void BeginDrawMain();
	/**
	* Function that converts the keyboard input to a userInput type
	* The function is used to seperate the logic and interface layers
	* @return userInput 
	*/
    userInput Update();
	/**
	* Function that checks the status of the window (open or closed)
	* @return bool indicating whether the window should be closed or not 
	*/
    bool IsDone();
	/**
	* Function that displays the splashscreen at the start of the game
	*/
    void SplashScreen();
	/**
	* Function that displays the win or lose screen
	*/
    void DisplayGameState(sf::Sprite& texture);
	/**
	* Function that draws the entity to the screen
	* @param entity is a shared pointer to a movingEntity object
	*/
    void show(std::shared_ptr<movingEntity> entity);
	/**
	* Function that gets the current state of the game
	*/		
    void setGameState(gameState state);
	/**
	* Function that gets the current state of the game and calls the win/lose screen
	* @param state is a gameState variable that indicates the state of the game
	*/	
    void getGameState();
	/**
	* Function that sets the number of player lives remaining
	*/		
    void setLivesRemaining(int lives);
	/**
	* Function that sets the maximum number of enemies
	*/		
    void setMaximumEnemies(int maxEnemies);
	
	sf::RenderWindow _window;
	bool reset;
	userInput keyBoard;

private:
	/**
	* Function that loads the required images
	*/		
    void fileLoader();
	/**
	* Function that draws the reqired text to the screen
	*/		
    void drawText();
	/**
	* Function that ends the splashscreen by either starting the game or closing the window
	* @param bool that indicates whether the window should be closed or not
	*/		
    bool End();
	/**
	* Function that sets up the text to be drawn on the screen
	* @param xPos is a float indicating the x position of the text
	* @param yPos is a float indicating the y position of the text
	* @param text is a reference to an sf::Text containing the text to be altered
	*/	
    void textSetup(float xPos, float yPos, sf::Text& text);
	
    sf::Texture _splashTexture;
    sf::Texture _loseTexture;
    sf::Texture _winTexture;
    sf::Texture _backgroundTexture;
    sf::Texture _playerTexture;
    sf::Texture _enemyTexture;
    sf::Texture _satelliteTexture;
    sf::Texture _asteroidTexture;
    sf::Texture _arcTexture;
    sf::Font font;
    bool _isDone;
    bool _isShooting;
    bool disableShooting;
    gameState _state;
    int _playerLives;
    int _enemies;
};
#endif 