// Gabriel DiFeo && Karissa Merrill 

// Headers 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <sstream>
#include <vector>
//#include "ComplexPlane.h"

//Namespace Declarations
using namespace sf;
using namespace std;


int main() {
    //grabs the desktop resolution
    VideoMode desktop = VideoMode::getDesktopMode();

 
    //Divides the screen's resolution by 2 to scale down the screen
    unsigned int pixelWidth = desktop.width / 2;
    unsigned int pixelHeight = desktop.height / 2;

    //Creates the window 
    RenderWindow window(VideoMode(pixelWidth, pixelHeight), "Mandlebrot Set", Style::Default);

    //ComplexPlane complexPlane(pixelWidth, pixelHeight);

    // Font for Chaos Game
    Font font;
    if (!font.loadFromFile("YatraOne.ttf")) 
    {
        // Displays message to user if font doesn't load
        cout << "Error loading font!" << endl;
        // returns error and exits program
        return -1;
    }

    Text text;

    text.setFont(font);
    text.setCharacterSize(60); //Sets text size
    text.setFillColor(Color::White); //Sets text color
    text.setPosition(10, 10); //Positions text

    while (window.isOpen()) 
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) 
            {
                window.close();
            }

            //closes window if esc key is pressed
            if (Keyboard::isKeyPressed(Keyboard::Escape))
		    {
			    window.close();
		    }

            text.setString("Hello World!");
            window.draw(text);
        }
    }
    window.display();

}