#include "vector.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    CoordinatePlane coordPlane = CoordinatePlane();

    Vector rotatingVec = Vector(1, 0, sf::Color::Blue);

    Vector* mouseVec = nullptr;

    Vector staticVec1 = Vector(1, 2, sf::Color::Red);
    Vector staticVec2 = Vector(2, 1, sf::Color::Green);
    Vector result = staticVec1 >> 30;

    std::cout << (staticVec1, staticVec2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close if escape clicked
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mouseVec) delete mouseVec;

                    sf::Vector2i mouseGraphCoords = sf::Mouse::getPosition();
                    sf::Vector2f mouseVecCoords   = vecGraphToCoord(coordPlane, 
                                                                    mouseGraphCoords.x, 
                                                                    mouseGraphCoords.y);

                    mouseVec = new Vector(mouseVecCoords.x, mouseVecCoords.y, sf::Color::Cyan);
                }
            }
            default:
                break;
            }
        }

        window.clear();

        coordPlane.draw(window);
        
        rotatingVec.rotate(0.01);
        rotatingVec.draw(window, coordPlane);

        if (mouseVec) mouseVec->draw(window, coordPlane);

        staticVec1.draw(window, coordPlane);
        staticVec2.draw(window, coordPlane);
        result.draw(window, coordPlane);

        window.display();
    }

    if (mouseVec) delete mouseVec;
    return 0;
}