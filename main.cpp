#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Player.h"
#include "Enemy.h"

int main()
{
	// render the screen
	sf::RenderWindow window(sf::VideoMode(1400,1400), "Pixel Potter",  sf::Style::Titlebar | sf::Style::Close);
	sf::Texture texture;
if (!texture.loadFromFile("/Users/KJ/Documents/SoftwareProject/SFMLTest/harry_potter_sprite.png", sf::IntRect(0, 0, 150, 150)))
	return EXIT_FAILURE;
	
	sf::Texture volde;
if (!volde.loadFromFile("/Users/KJ/Documents/SoftwareProject/SFMLTest/gallery_10492_49_5214.png", sf::IntRect(0, 0, 150, 150)))
	return EXIT_FAILURE;	
	
// Load the text font
sf::Font font;
if (!font.loadFromFile("/Users/KJ/Documents/SoftwareProject/SFMLTest/HARRYP__.TTF"))
	return EXIT_FAILURE;


double size_of_x=window.getSize().x;
double size_of_y=window.getSize().y;

sf::CircleShape circle(size_of_x/2-50.0f);
circle.setFillColor(sf::Color::White);
circle.setOrigin(size_of_x/2,size_of_y/2);
Player harryPotter(&texture, sf::Vector2u(4,4),0.3f, 0.90f, size_of_x, size_of_y);
Enemy voldemort(&volde, sf::Vector2u(1,1), 0.3f, 100.0f, size_of_x, size_of_y);
Enemy voldemort2(&volde, sf::Vector2u(1,1), 0.3f, 100.0f, size_of_x, size_of_y);
Enemy voldemort3(&volde, sf::Vector2u(1,1), 0.3f, 100.0f, size_of_x, size_of_y);
Enemy voldemort4(&volde, sf::Vector2u(1,1), 0.3f, 100.0f, size_of_x, size_of_y);
float deltaTime =0.0f;
sf::Clock clock;

	    // Initialize the pause message
sf::Text pauseMessage;
pauseMessage.setFont(font);
pauseMessage.setCharacterSize(150);
pauseMessage.setPosition(170.f, 150.f);
pauseMessage.setColor(sf::Color::Yellow);
pauseMessage.setString("Pixel Potter\n and Voldemort's Vortex \n Coming soon to a laptop near you");
//while(window.isOpen())
//{
//	window.draw(pauseMessage);
//	window.display();
//	sf::Event startGame;
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	{
//		break;
//	}
//}

	// to be able to see the screen we need to create a while loop
	while(window.isOpen())
	{
		deltaTime =  clock.restart().asSeconds();
		
		sf::Event evnt;
		while(window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
				window.close();
				break;
			}
		
		}
		
//		while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//		{
//			window.draw(pauseMessage);
//			window.display();
//		}
//		window.clear(sf::Color::White);
		circle.setPosition(size_of_x/2, size_of_y/2);
		harryPotter.Update(deltaTime);
		voldemort.Update(deltaTime, window);
		voldemort2.Update(deltaTime, window);
		voldemort3.Update(deltaTime, window);
		voldemort4.Update(deltaTime, window);
		window.clear(sf::Color::Black); //must call before you draw
		window.draw(circle);
		harryPotter.Draw(window);
		voldemort.Draw(window);
		voldemort2.Draw(window);
		voldemort3.Draw(window);
		voldemort4.Draw(window);
		window.display(); 
	}
	
	return 0;
}