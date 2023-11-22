// Gabriel DiFeo && Karissa Merrill 

// Headers 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include "ComplexPlane.h"

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

    ComplexPlane complexPlane(pixelWidth, pixelHeight);

    //adds music to the program
    Music music;
    if (!music.openFromFile("relaxing.wav"))
    {
        cerr << "Error! Could not load music file" << endl;
        return -1;
    }

    //change the volume here
    music.setVolume(5);

    // loops it after song is overv
    music.setLoop(true);

    //plays the music
    music.play();

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
    text.setCharacterSize(20); //Sets text size
    text.setFillColor(Color(253, 226, 167)); //Sets text color
    text.setPosition(10, 10); //Positions text

    //boolean for CALCULATING
    bool CALCULATING = true;

    // thread variable for the updateRender (not iterations yet)
    thread render_thread1;
    //thread render_thread2;
    //thread render_thread3;

    // thread for interations
    thread iterations_thread;

    while (window.isOpen()) 
    {
        Event event;

        window.clear();

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

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (event.mouseButton.button == Mouse::Right) 
                {
                    //right click to zoom out
                    //calls the setCenter on the ComplexPlane object from mouse clicked position
                    //sets CALCULATING to true
                    complexPlane.setCenter(Vector2i(mousePos.x, mousePos.y));
                    complexPlane.zoomOut();
                    CALCULATING = true;
                }
                else if (event.mouseButton.button == Mouse::Left)
                {
                    //left click to zoom in
                    //calls setCenter on the ComplexPlane object from mouse clicked postion
                    //sets CALCULATING to true
                    complexPlane.setCenter(Vector2i(mousePos.x, mousePos.y));
                    complexPlane.zoomIn();
                    CALCULATING = true;
                }
            }
            else if (event.type == Event::MouseMoved)
            {
                //mouse moved event here
                //calls setMouseLocation on the ComplexPlane object and stores mouse coords
                complexPlane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
            }

        }

        if (CALCULATING)
        {
            //complexPlane.updateRender(); // performs the mandlebrot set calculations
            // I am going to thread this as well, to help render it faster because the speed is crazy slow 
            //thread render_thread(&ComplexPlane::updateRender, &complexPlane);
            //The professors link is for SFML threading documentation, but take note this is a C++ library
            //joinable is basically like can they be threaded together? Like 1 + 1 = 2
            
            // join these threads together
            if (render_thread1.joinable())
            {
                render_thread1.join();
            }
            /*else if (render_thread2.joinable())
            {
                //render_thread2.join();
            }
            else if (render_thread3.joinable())
            {
                //render_thread3.join();
            }
                */
            // threading this to update and render a bit faster 
            render_thread1 = thread(&ComplexPlane::updateRender, &complexPlane);
            //render_thread2 = thread(&ComplexPlane::updateRender, &testY);
            //render_thread3 = thread(&ComplexPlane::updateRender, &testX);
            
            //render_thread.join();

            CALCULATING = false; // sets state back to DISPLAYING once calculations are done
        }
        complexPlane.loadText(text); // pulls up the text info
        complexPlane.draw(window, RenderStates::Default);
        //may need to be moved up a bracket to run
        window.draw(text);
        window.display();
    }

    return 0;
}