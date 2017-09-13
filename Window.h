#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>

class Window{

public:

	Window();
	~Window();
	void BeginDraw();
	void EndDraw();
	void Update();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	sf::RenderWindow _window;
	bool IsDone();
	void SplashScreen();
	bool EndSplashScreen(const sf::Sprite &background);

private:
sf::Texture _splashTexture;
	void Destroy();
	bool _isDone; 

};

#endif // WINDOW_H