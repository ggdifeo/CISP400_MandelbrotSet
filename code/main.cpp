// Gabriel DiFeo && Karissa Merrill 

// Headers 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "ComplexPlane.h"

//Namespace Declarations
using namespace sf;
using namespace std;


int main() {
    //grabs the desktop resolution
    VideoMode desktop = VideoMode::getDesktopMode();

    //Divides the screen's resolution by 2 to scale down the screen
    unsigned int screenWidth = desktop.width / 2;
    unsigned int screenHeight = desktop.height / 2;

    //Creates the window 
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Mandlebrot Set", Style::Default);

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
        }
    }
    window.display();

}