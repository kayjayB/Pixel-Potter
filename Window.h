#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "userInput.h"
#include <vector>
#include "Enemy.h"
#include "movingEntity.h"

class Window{

public:

	Window();
	~Window();
	void closeWindow();
	void BeginDraw();
	void EndDraw();
	userInput Update();
	//std::vector<userInput> Update();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	sf::RenderWindow _window;
	bool IsDone();
	void SplashScreen();
	//bool SplashScreen();
	bool EndSplashScreen(const sf::Sprite &background);
	
	void Lose();
	//bool SplashScreen();
	bool EndLose(const sf::Sprite &background);
	//bool EndLose();
	userInput keyBoard;
	//std::vector <userInput> keyBoard;
	bool isShooting();
	void show(movingEntity &entity);
	void showPointer(std::shared_ptr<movingEntity> entity);
	
	bool reset;

private:
//	sf::Sprite backgroundLose;
	sf::Texture _splashTexture;
	sf::Texture _loseTexture;
	void Destroy();
	bool _isDone; 
	bool _isShooting;
	

};

#endif // WINDOW_H