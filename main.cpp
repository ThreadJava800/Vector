#include "vector.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "");
    window.setPosition(sf::Vector2i(0, 0));

    CoordinatePlane coordPlane = CoordinatePlane();

    Vector staticVec1 = Vector(1, -2);
    Vector staticVec2 = Vector(380, 20);

    Vector sumVec = staticVec1 + staticVec2;

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

            // if (event.type == sf::Event::MouseMoved) {
               
            // }
        }

        window.clear();

        coordPlane.draw(&window);
        staticVec1.draw(&window, &coordPlane);
        // staticVec2.draw(&window);
        // sumVec.draw(&window);

        window.display();
    }

    return 0;
}