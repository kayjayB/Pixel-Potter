#include "Window.h"

Window::Window()
    : _window(sf::VideoMode(1920, 1080), "Pixel Potter", sf::Style::Titlebar | sf::Style::Close)
{
    _isDone = false;
	_isShooting=false;
	disableShooting=false;
	reset=false;
	if (!_splashTexture.loadFromFile("Slide1.png", sf::IntRect(0, 0, 1920, 1080)))
		throw FileNotFound();
	if (!_loseTexture.loadFromFile("lose.png", sf::IntRect(0, 0, 1920, 1080)))
			throw FileNotFound();
	if(!_winTexture.loadFromFile("win.png", sf::IntRect(0, 0, 1920, 1080)))
			throw FileNotFound();
	if(!_backgroundTexture.loadFromFile("vortex.png", sf::IntRect(0, 0, 1920, 1080)))
			throw FileNotFound();
}

Window::~Window()
{
    _window.close();
}

void Window::closeWindow()
{
	_window.close();
}

void Window::BeginDrawMain()
{
    _window.clear(sf::Color::White);
	sf::Sprite background(_backgroundTexture);
	_window.draw(background);
	sf::Font font;
	font.loadFromFile("HARRYP__.TTF");
	sf::Text text("Enemies remaining:" + std::to_string(_enemies- Enemy::getNumberofEnemiesKilled()), font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color(255,1,1,255));
	text.setPosition(1500, 1);
	text.setStyle(sf::Text::Bold);
	_window.draw(text);

	sf::Text lives("Lives remaining:" + std::to_string(_playerLives), font);
	lives.setCharacterSize(50);
	lives.setStyle(sf::Text::Bold);
	lives.setColor(sf::Color(255,0,0,255));
	lives.setStyle(sf::Text::Bold);
	_window.draw(lives);
	
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
	reset=false;
    sf::Event event;
    // sf::Event keyPress;
    while(_window.pollEvent(event)) 
	{
		if(event.type == sf::Event::Closed) 
		{
			_isDone = true;
		}
//		if (event.type==sf::Event::KeyPressed)
//		{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{
			//keyBoard.push_back(userInput::PressLeft);
			keyBoard=userInput::PressLeft;
			_isShooting=false;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			//keyBoard.push_back(userInput::PressRight);
			keyBoard=userInput::PressRight;
			_isShooting=false;
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{
			//keyBoard.push_back(userInput::NoButtonPress);
			keyBoard=userInput::NoButtonPress;
			_isShooting=false;
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // && !disableShooting)
		{
			keyBoard=userInput::PressSpace;
			_isShooting=true;
		//	keyBoard.push_back(userInput::PressSpace);
		}
	//	disableShooting=!disableShooting;
		}
//		else if (event.type==sf::Event::KeyReleased)
//		{
//			disableShooting=false;	
//		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
//		&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
//		{
//			//keyBoard.push_back(userInput::NoButtonPress);
//			keyBoard=userInput::NoButtonPress;
//			_isShooting=false;
//		}
//		}
	return keyBoard;
}

void Window::SplashScreen()
{
    sf::Sprite background(_splashTexture);
    while(_window.isOpen()) {
		
	BeginDraw();
	
	_window.draw(background);
	
	_window.display();
	
	if(EndSplashScreen())
	    return ;
    }
}

bool Window::EndSplashScreen()
{
    sf::Event endSplash;

    while(_window.pollEvent(endSplash)) {
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
	    _isDone = false;
	    return true;
	}
	
	if(endSplash.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}
    }
}

void Window::Lose()
{
   sf::Sprite backgroundLose(_loseTexture);
   movingEntity::entityList.clear();
    while(_window.isOpen()) {
		
	BeginDraw();
	
	_window.draw(backgroundLose);
	
	_window.display();

	if(EndLose())
	{
	    return;
	}
    }
}

bool Window::EndLose()
{
    sf::Event endSplash;

    while(_window.pollEvent(endSplash)) {
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
	    _isDone = false;
	    return true;
		}
	if(endSplash.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}
    }
}

void Window::Win()
{

   sf::Sprite backgroundWin(_winTexture);
   BeginDraw();
   movingEntity::entityList.clear();
    while(_window.isOpen()) {

	BeginDraw();
	_window.draw(backgroundWin);
	
	_window.display();
	if(EndWin())
	{
	    return;
	}
    }
}

bool Window::EndWin()
{
    sf::Event endSplash;

    while(_window.pollEvent(endSplash)) {
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
	    _isDone = false;
	    return true;
	}
	if(endSplash.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}
	
    }
}

bool Window::isShooting()
{
	return _isShooting;
}

void Window::show(std::shared_ptr<movingEntity> entity)
{
	_window.draw(entity->getBody());
}

void Window::getGameState()
{
		switch (_state)
		{
		case gameState::lose:
		reset=true;
		Enemy::ResetEnemies();
		Lose();
		break;
		case gameState::win:
		reset=true;
		Enemy::ResetEnemies();
		Win();
		break;
		case gameState::playing:
		reset=false;
		break;
		}
}

void Window::setGameState(gameState state)
{
	_state=state;
}

void Window::setLivesRemaining(int lives)
{
		_playerLives= lives;
}
	
void Window::setMaximumEnemies(int maxEnemies)
{
	_enemies= maxEnemies;
}