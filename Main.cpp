#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>



int main()
{	//---------------------------
	//Setup
	//--------------------------

	// Make a variable called gameWindow of the type RenderWindow
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Critter Whack",
		sf::Style::Titlebar | sf::Style::Close);




	// Timer Functionality
	sf::Clock gameClock;

	//------------------------------
	//End Game Setup
	//------------------------------




	//-------------------------------
	// Game Loop
	//-------------------------------
	while (gameWindow.isOpen())
	{
		//-----------------------------------
		//Input
		//-----------------------------------


		sf::Event Event;
		while (gameWindow.pollEvent(Event))

		{
			if (Event.type == sf::Event::Closed)
			{
				gameWindow.close();
			}
		}// end event polling loop

		//end input


		//----------------------------
		//Upate
		//----------------------------
		sf::Time frameTime = gameClock.restart();
			


		//end update

		//Draw Everything

		gameWindow.clear();








		gameWindow.display();
			
		//End Draw
	}

	return 0;
}