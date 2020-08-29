#include <SFML/Graphics.hpp>
#include <iostream>

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}


//bool collision(sf::FloatRect r1, sf::FloatRect r2)
//{
//	sf::FloatRect intersection;
//	return r1.intersects(r2, intersection);
//}


int main(int argc, char ** argv)
{
	//Make Window
	int resX = 640;
	int resY = 480;
	sf::RenderWindow window(sf::VideoMode(resX, resY), "PlaceHolder", (sf::Style::Resize + sf::Style::Close));
	
	// Set Objects and Sprits
	// 	BOXES
	sf::RectangleShape rect1(sf::Vector2f(100.f,100.f));
	sf::RectangleShape rect2(sf::Vector2f(2000.f, 100.f));
	rect2.setPosition(0.f, 1020.f);	
	//	SPRITES
	sf::Texture textureUp;
	textureUp.loadFromFile("Assets/Character/Character Move.png");
	sf::Sprite spriteUp(textureUp, sf::IntRect(0,0,50,50));
	sf::Sprite spriteRight(textureUp, sf::IntRect(0,0,150,150));
	sf::Sprite spriteDown(textureUp, sf::IntRect(0,0,150,150));
	sf::Sprite spriteLeft(textureUp, sf::IntRect(0,0,200,200));

	// set Views
	sf::View playerView;
	playerView.setSize( resX, resY);
	playerView.setCenter(playerView.getSize().x / 2, playerView.getSize().y /2);
	playerView = getLetterboxView(playerView, resX, resY);


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
				playerView = getLetterboxView(playerView, event.size.width, event.size.height);	
			}

			
			}
			
			//DEBUG
			if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "Position of mouse: (" << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << ")\n\n";
			}
		

			if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{

				std::cout << "Player Position: (" << rect1.getPosition().x << ", " << rect1.getPosition().y << ")\n\n";
			//
			}
			
		//Drawing and View stuff here for loop	
		playerView.setCenter(spriteUp.getPosition().x, spriteUp.getPosition().y);
		window.clear();
		window.draw(rect1);
		window.draw(rect2);
		window.draw(spriteUp);
		window.setView(playerView);

		//Key Controls
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //&& collision(rect1,rect2) == false) 
		{
			spriteUp.move(1.f, 0.f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			spriteUp.move(-1.f, 0.f);
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			spriteUp.move(0.f, -1.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			spriteUp.move(0.f, 1.f);
		}
		window.display();
	}

	return 0;
}
