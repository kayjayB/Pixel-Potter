#include "Window.h"

Window::Window()
    : _window(sf::VideoMode(1920, 1080), "Pixel Potter", sf::Style::Titlebar | sf::Style::Close)
{
    _isDone = false;
}

Window::~Window()
{
    _window.close();
}

void Window::BeginDraw()
{
    _window.clear(sf::Color::White);
}

void Window::EndDraw()
{
    _window.display();
}

bool Window::IsDone()
{
    return _isDone;
}

userInput Window::Update()
{
    sf::Event event;
    // sf::Event keyPress;
    while(_window.pollEvent(event)) 
	{
		if(event.type == sf::Event::Closed) 
		{
			_isDone = true;
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{
			//keyBoardInput.push_back(userInput::PressLeft);
			keyBoard=userInput::PressLeft;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			//keyBoardInput.push_back(userInput::PressRight);
			keyBoard=userInput::PressRight;
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			//keyBoardInput.push_back(userInput::NoButtonPress);
			keyBoard=userInput::NoButtonPress;
		}
    }
	return keyBoard;
}

void Window::SplashScreen()
{

	_splashTexture.loadFromFile(
       "Slide1.png", sf::IntRect(0, 0, 1920, 1080));
    sf::Sprite background(_splashTexture);
    while(_window.isOpen()) {

	if(EndSplashScreen(background))
	    return;
    }
}

bool Window::EndSplashScreen(const sf::Sprite& background)
{
    sf::Event endSplash;

    while(_window.pollEvent(endSplash)) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	    _isDone = false;
	    return true;
	}
	if(endSplash.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}

	_window.draw(background);
	_window.display();
    }
}
