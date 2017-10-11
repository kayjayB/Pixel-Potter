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
* \brief FileNotFound class
* Throws an exception if a file to be opened cannot be found
*/
class FileNotFound
{
};

/**
* \brief Window class.
* Acts as an Interface - creates a window, draws the entities, displays the splashscreens
*/
class Window
{

public:
	/**
	* \brief Default Constructor. 
	* Creates a new Window 
	*/
    Window();
	/**
	* \brief Function to close the SFML window
	*/
    void closeWindow();
	/**
	* \brief Function to clear the SFML window prior to drawing
	*/
    void BeginDraw();
	/**
	* \brief Function to display the SFML window
	*/
    void EndDraw();
	/**
	* \brief Function to clear the SFML window prior to drawing and set the background 
	* for the main game
	*/
    void BeginDrawMain();
	/**
	* \brief Function that converts the keyboard input to a userInput type
	* The function is used to seperate the logic and interface layers
	* @return userInput 
	*/
    userInput Update();
	/**
	* \brief Function that checks the status of the SFML window (open or closed)
	* @return bool indicating whether the SFML window should be closed or not 
	*/
    bool IsDone();
	/**
	* \brief Function that displays the splashscreen at the start of the game
	*/
    void SplashScreen();
	/**
	* \brief Function that displays the win or lose screen
	*/
    void DisplayGameState(sf::Sprite& texture);
	/**
	* \brief Function that draws the entity to the screen
	* @param entity is a shared pointer to a movingEntity object
	*/
    void show(std::shared_ptr<movingEntity> entity);
	/**
	* \brief Function that gets the current state of the game
	*/		
    void setGameState(gameState state);
	/**
	* \brief Function that gets the current state of the game and calls the win/lose screen
	* @param state is a gameState variable that indicates the state of the game
	*/	
    void getGameState();
	/**
	* \brief Function that sets the number of Player lives remaining
	*/		
    void setLivesRemaining(int lives);
	/**
	* \brief Function that sets the maximum number of Enemy entities
	*/		
    void setMaximumEnemies(int maxEnemies);
	
	bool reset;

private:
	/**
	* \brief Function that loads the required images
	*/		
    void fileLoader();
	/**
	* \brief Function that draws the reqired text to the screen
	*/		
    void drawText();
	/**
	* \brief Function that ends the splashscreen by either starting the game or closing the window
	* @param bool that indicates whether the window should be closed or not
	*/		
    bool End();
	/**
	* \brief Function that sets up the text to be drawn on the screen
	* @param xPos is a float indicating the x position of the text
	* @param yPos is a float indicating the y position of the text
	* @param text is a reference to an sf::Text containing the text to be altered
	*/	
    void textSetup(float xPos, float yPos, sf::Text& text);
	userInput keyBoard;
	sf::RenderWindow _window;
    sf::Texture _splashTexture;
    sf::Texture _loseTexture;
    sf::Texture _winTexture;
    sf::Texture _backgroundTexture;
    sf::Font font;
    bool _isDone;
    bool disableShooting;
    gameState _state;
    int _playerLives;
    int _enemies;
};
#endif 