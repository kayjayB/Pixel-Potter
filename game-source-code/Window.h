#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "userInput.h"
#include <vector>
#include "Enemy.h"
#include "movingEntity.h"
#include "gameState.h"

class FileNotFound
{
};

class Window
{

public:
    Window();
    ~Window();
    void closeWindow();
    void BeginDraw();
    void EndDraw();
    void BeginDrawMain();
    userInput Update();
    // std::vector<userInput> Update();
    sf::Vector2u GetWindowSize();
    sf::RenderWindow _window;
    bool IsDone();
    void SplashScreen();

    //void Lose();
	void DisplayGameState(sf::Sprite &texture);
	
	bool isShooting();
    userInput keyBoard;
    // std::vector <userInput> keyBoard;
    void show(std::shared_ptr<movingEntity> entity);
	//void show(sf::RectangleShape entity);
    void setGameState(gameState state);
    void getGameState();
	
	void setLivesRemaining(int lives);
	
	void setMaximumEnemies(int maxEnemies);
	
    bool reset;

private:
    void fileLoader();
	void drawText();
	 bool End();
	 void textSetup(float xPos, float yPos, sf::Text &text);
    sf::Texture _splashTexture;
    sf::Texture _loseTexture;
    sf::Texture _winTexture;
    sf::Texture _backgroundTexture;
	sf::Font font;
    void Destroy();
    bool _isDone;
    bool _isShooting;
    bool disableShooting;
    gameState _state;
	
	int _playerLives;
	int _enemies;
	
};
#endif // WINDOW_H