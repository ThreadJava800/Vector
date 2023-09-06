#include "vector.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "");
    window.setPosition(sf::Vector2i(0, 0));

    CoordinatePlane* coordPlane = new CoordinatePlane();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close if escape clicked
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
               
            }
        }

        window.clear();

        coordPlane->draw(&window);

        window.display();
    }

    return 0;
}