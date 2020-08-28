#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "PlaceHolder");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::RectangleShape rec(sf::Vector2f(2000.f, 100.f));
	rec.setPosition(0.f, 1020.f);

	// set a 10-pixel wide orange outline
	shape.setOutlineThickness(10.f);
	shape.setOutlineColor(sf::Color(250,150,100));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				//update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "Position of mouse: (" << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << ")\n\n";
			}
		}

		window.clear();
		window.draw(shape);
		window.draw(rec);
		window.display();

		//debug position data
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.move(1.f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.move(-1.f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shape.move(0.f, -1.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.move(0.f, 1.f);
		}
	}

	return 0;
}
