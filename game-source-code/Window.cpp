#include "Window.h"

Window::Window()
    : _window(sf::VideoMode(1920, 1080), "Pixel Potter", sf::Style::Titlebar | sf::Style::Close)
    , reset{ false }
    , _isDone{ false }
    , disableShooting{ false }
{
    fileLoader();
}

void Window::fileLoader()
{
    if(!_splashTexture.loadFromFile("Slide1.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_loseTexture.loadFromFile("lose.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_winTexture.loadFromFile("win.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_backgroundTexture.loadFromFile("vortex.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!font.loadFromFile("HARRYP__.TTF"))
	throw FileNotFound();

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
    drawText();
}

void Window::drawText()
{

    sf::Text text("Enemies remaining:" + std::to_string(_enemies - Enemy::getNumberofEnemiesKilled()), font);
    textSetup(1500, 1, text);
    _window.draw(text);

    sf::Text lives("Lives remaining:" + std::to_string(_playerLives), font);
    textSetup(0, 0, lives);
    _window.draw(lives);
}

void Window::textSetup(float xPos, float yPos, sf::Text& text)
{
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color(255, 255, 255, 255));
    text.setPosition(xPos, yPos);
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
    reset = false;
    sf::Event event;
    while(_window.pollEvent(event)) {
	if(event.type == sf::Event::Closed) {
	    _isDone = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !disableShooting) {
	    keyBoard = userInput::PressSpace;
	    disableShooting = true;
	    return keyBoard;
	}
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && disableShooting) {
	    disableShooting = false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	    keyBoard = userInput::PressLeft;
	    return keyBoard;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	    keyBoard = userInput::PressRight;
	    return keyBoard;
	}
	
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	    keyBoard = userInput::NoButtonPress;
	    return keyBoard;
	}
    }
    return keyBoard;
}

void Window::SplashScreen()
{
    sf::Sprite background(_splashTexture);
    while(_window.isOpen()) {

	BeginDraw();

	_window.draw(background);

	_window.display();

	if(End())
	    return;
    }
}

bool Window::End()
{
    sf::Event end;

    while(_window.pollEvent(end)) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
	    _isDone = false;
	    return true;
	}

	if(end.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}
    }
}

void Window::DisplayGameState(sf::Sprite& texture)
{
    movingEntity::entityList.clear();
    while(_window.isOpen()) {

	BeginDraw();

	_window.draw(texture);

	_window.display();

	if(End()) {
	    return;
	}
    }
}

void Window::show(std::shared_ptr<movingEntity> entity)
{	
	sf::RectangleShape _body;
	
    _body.setSize(sf::Vector2f(entity->getBodySize()[0], entity->getBodySize()[1]));
	
    _body.setOrigin(entity->getBodySize()[0] / 2, entity->getBodySize()[1] / 2);
	
    _body.setPosition(entity->getPosition()[0], entity->getPosition()[1]);
	
    _body.setRotation(entity->getAngle() * (180.0f / M_PI) + 90);
	
	sf::Texture _bodyTexture;
		
	if (!entity->getTextureName().empty())
	{
		if(!_bodyTexture.loadFromFile(entity->getTextureName(), sf::IntRect(0, 0, 150, 150)))
		{
			std::cerr<< "File not found" << std::endl;
		}
	}
	
	_body.setTexture(&_bodyTexture);
	
    _body.setFillColor(sf::Color(entity->getColour()[0], entity->getColour()[1], entity->getColour()[2], 255));
	
    _window.draw(_body);
}

void Window::getGameState()
{
    switch(_state) {
    case gameState::lose: {
	reset = true;
	sf::Sprite background(_loseTexture);
	DisplayGameState(background);
	break;
    }
    case gameState::win: {
	reset = true;
	sf::Sprite background2(_winTexture);
	DisplayGameState(background2);
	break;
    }
    case gameState::playing:
	reset = false;
	break;
    }
}

void Window::setGameState(gameState state)
{
    _state = state;
}

void Window::setLivesRemaining(int lives)
{
    _playerLives = lives;
}

void Window::setMaximumEnemies(int maxEnemies)
{
    _enemies = maxEnemies;
}