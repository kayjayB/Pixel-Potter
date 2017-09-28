#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "userInput.h"
#include <vector>
#include "Enemy.h"
#include "movingEntity.h"
#include "gameState.h"


class Window{

public:

	Window();
	~Window();
	void closeWindow();
	void BeginDraw();
	void EndDraw();
	void BeginDrawMain();
	userInput Update();
	//std::vector<userInput> Update();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	sf::RenderWindow _window;
	bool IsDone();
	void SplashScreen();
	bool EndSplashScreen();
	
	void Lose();
	bool EndLose();
	
	void Win();
	bool EndWin();
	userInput keyBoard;
	//std::vector <userInput> keyBoard;
	bool isShooting();
	void show(movingEntity &entity);
	void showPointer(std::shared_ptr<movingEntity> entity);
	void setGameState(gameState state);
	void getGameState();
	bool reset;

private:
//	sf::Sprite backgroundLose;
	sf::Texture _splashTexture;
	sf::Texture _loseTexture;
	sf::Texture _winTexture;
	sf::Texture _backgroundTexture;
	void Destroy();
	bool _isDone; 
	bool _isShooting;
	bool disableShooting;
	gameState _state;
	

};

#endif // WINDOW_H