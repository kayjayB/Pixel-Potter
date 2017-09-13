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

void Window::Update()
{
    sf::Event event;

    while(_window.pollEvent(event)) 
	{
		if(event.type == sf::Event::Closed) 
		{
	    _isDone = true;
	    //_window.close();
		}
    }
}

void Window::SplashScreen()
{

//    sf::Font font;
//    font.loadFromFile("/Users/KJ/Documents/SoftwareProject/SFMLTest/HARRYP__.TTF");
//    sf::Text pauseMessage;
//    pauseMessage.setFont(font);
//    pauseMessage.setCharacterSize(150);
//    pauseMessage.setPosition(0.0f, 150.f);
//    pauseMessage.setColor(sf::Color::Yellow);
//    pauseMessage.setString("Pixel Potter\nand Voldemort's Vortex\nPress left arrow to move \ncounterclockwise\nPress "
//                           "right arrow to move \nclockwise");

	_splashTexture.loadFromFile("/Users/KJ/Documents/SoftwareProject/ProjectWithClasses/Slide1.png", sf::IntRect(0, 0, 1920, 1080));
	sf::Sprite background(_splashTexture);
    while(_window.isOpen()) 
	{

	if (EndSplashScreen(background))
		return;
    }
}

bool Window::EndSplashScreen(const sf::Sprite &background)
{
    sf::Event endSplash;

    while(_window.pollEvent(endSplash)) 
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		{
	    //_window.close();
		_isDone=false;
	    return true;
		}
		if(endSplash.type == sf::Event::Closed) 
		{
			_isDone = true;
			_window.close();
			return false;
		}

		_window.draw(background);
		_window.display();
    }

}
