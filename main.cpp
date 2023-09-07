#include "vector.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "");
    window.setPosition(sf::Vector2i(0, 0));

    CoordinatePlane coordPlane = CoordinatePlane();

    Vector staticVec1 = Vector(1, -2);
    Vector staticVec2 = Vector(1, 1);

    Vector sumVec    = staticVec1 + staticVec2;
    sumVec.setColor(sf::Color::Red);

    Vector normalVec = Vector(2, 2, sf::Color::Blue);
    normalVec.setColor(sf::Color::Blue);

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
        // staticVec1.draw(&window, &coordPlane);
        // staticVec2.draw(&window, &coordPlane);
        // sumVec.draw(&window, &coordPlane);
        normalVec.draw(&window, &coordPlane);

        window.display();
    }

    return 0;
}