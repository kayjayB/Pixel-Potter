#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "userInput.h"
#include <vector>
#include "Enemy.h"

class Window{

public:

	Window();
	~Window();
	void BeginDraw();
	void EndDraw();
	userInput Update();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	sf::RenderWindow _window;
	bool IsDone();
	void SplashScreen();
	bool EndSplashScreen(const sf::Sprite &background);
	userInput keyBoard;

private:
sf::Texture _splashTexture;
	void Destroy();
	bool _isDone; 
	

};

#endif // WINDOW_H