#include "graphLib.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(), "Chemical simulator", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    SubWindow subWindow = SubWindow(20, 20, 300, 300);
    CoordinatePlane coordPlane = CoordinatePlane(150, 150, 50, 50);

    SubWindow subWindow2 = SubWindow(500, 500, 500, 500);
    CoordinatePlane coordPlane2 = CoordinatePlane(500, 500, 100, 100);

    Vector  rotatingVec = Vector(1, 2, sf::Color::Blue);
    Vector* mouseVec1   = nullptr;

    Vector test = Vector(1, 2, sf::Color::Yellow);

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
                    if (mouseVec1) delete mouseVec1;

                    sf::Vector2i mouseGraphCoords = sf::Mouse::getPosition();
                    sf::Vector2f mouseVecCoords   = vecGraphToCoord(subWindow2,
                                                                    coordPlane2, 
                                                                    mouseGraphCoords.x, 
                                                                    mouseGraphCoords.y);

                    mouseVec1 = new Vector(mouseVecCoords.x, mouseVecCoords.y, sf::Color::Cyan);
                }
            }
            default:
                break;
            }
        }

        window.clear();

        subWindow.clear();
        subWindow2.clear();
        coordPlane.draw(subWindow);
        coordPlane2.draw(subWindow2);
        
        rotatingVec.rotate(0.01);
        rotatingVec.draw(subWindow, coordPlane);
        rotatingVec.draw(subWindow2, coordPlane2);

        if (mouseVec1) mouseVec1->draw(subWindow2, coordPlane2);

        test.draw(subWindow2, coordPlane2, -1, 0);

        // staticVec1.draw(window, coordPlane);
        // staticVec2.draw(window, coordPlane);
        // result.draw(window, coordPlane);

        subWindow.displayOnWindow(window);
        subWindow2.displayOnWindow(window);

        window.display();
    }

    if (mouseVec1) delete mouseVec1;
    return 0;
}