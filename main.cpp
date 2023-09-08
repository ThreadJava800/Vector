#include "graphLib.h"        

int main() {
    sf::RenderWindow window(sf::VideoMode(), "Chemical simulator", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    SubWindow subWindow1 = SubWindow(50, 50, 500, 500);
    CoordinatePlane coordPlane1 = CoordinatePlane(100, 100, 50, 50);

    SubWindow subWindow2 = SubWindow(1000, 0, 920, 920);
    CoordinatePlane coordPlane2 = CoordinatePlane(460, 460, 100, 100);

    Vector  rotatingVec = Vector(1, 2, sf::Color::Blue);
    Vector* mouseVec1   = nullptr;
    Vector* mouseVec2   = nullptr;

    Vector test1 = Vector(1, 2, sf::Color::Yellow);
    Vector test2 = Vector(2, 1, sf::Color::Yellow);
    // test2 += test1;
    Vector test3 = test1 + test2;

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
                    sf::Vector2i mouseGraphCoords = sf::Mouse::getPosition();

                    if (subWindow1.pointInside(mouseGraphCoords.x, mouseGraphCoords.y)) {
                        sf::Vector2f mouseVecCoords   = vecGraphToCoord(subWindow1,
                                                                        coordPlane1, 
                                                                        mouseGraphCoords.x, 
                                                                        mouseGraphCoords.y);

                        if (mouseVec1) delete mouseVec1;
                        mouseVec1 = new Vector(mouseVecCoords.x, mouseVecCoords.y, sf::Color::Cyan);
                    }
                    if (subWindow2.pointInside(mouseGraphCoords.x, mouseGraphCoords.y)) {
                        sf::Vector2f mouseVecCoords   = vecGraphToCoord(subWindow2,
                                                                        coordPlane2, 
                                                                        mouseGraphCoords.x, 
                                                                        mouseGraphCoords.y);

                        if (mouseVec2) delete mouseVec2;
                        mouseVec2 = new Vector(mouseVecCoords.x, mouseVecCoords.y, sf::Color::Cyan);
                    }
                }
            }
            default:
                break;
            }
        }

        window.clear();

        subWindow1.clear();
        subWindow2.clear();
        coordPlane1.draw(subWindow1);
        coordPlane2.draw(subWindow2);
        
        rotatingVec.rotate(0.01);
        rotatingVec.draw(subWindow1, coordPlane1);
        rotatingVec.draw(subWindow2, coordPlane2);

        if (mouseVec1) mouseVec1->draw(subWindow1, coordPlane1);
        if (mouseVec2) mouseVec2->draw(subWindow2, coordPlane2);

        test1.draw(subWindow2, coordPlane2, -1, 0);    
        test2.draw(subWindow2, coordPlane2);
        test3.draw(subWindow2, coordPlane2);

        // staticVec1.draw(window, coordPlane);
        // staticVec2.draw(window, coordPlane);
        // result.draw(window, coordPlane);

        subWindow1.displayOnWindow(window);
        subWindow2.displayOnWindow(window);

        window.display();
    }

    if (mouseVec1) delete mouseVec1;
    if (mouseVec2) delete mouseVec2;

    return 0;
}