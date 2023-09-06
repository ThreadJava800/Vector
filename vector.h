#ifndef _VEC_h_
#define _VEC_h_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int       WINDOW_LENGTH          = 720;
const int       WINDOW_HEIGHT          = 480;
const double    DEFAULT_UNIT           = 100;
const float     UNIT_POINT_RAD         = 4;
const sf::Color DEFAULT_LINE_COLOR     = sf::Color::White;
const sf::Color DEFAULT_UNIT_POINT_COL = sf::Color::Red;

class Vector {
private:
    double    x, y;
    sf::Color color;

public:
    Vector();
    Vector(double x, double y, sf::Color color);

    double    getX();
    double    getY();
    sf::Color getColor();

    void draw(sf::RenderWindow* window, double xEnd, double yEnd);
};

class CoordinatePlane {
private:
    double    xOrigin, yOrigin;
    double    xUnit  , yUnit;

public:
    CoordinatePlane();
    CoordinatePlane(double xOrigin, double yOrigin, double xUnit, double yUnit);

    double getXOrigin();
    double getYOrigin();
    double getXUnit  ();
    double getYUnit  ();

    void draw(sf::RenderWindow* window);
};

#if _DEBUG
#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}                                                             \


#else
#define ON_ERROR(expr, errStr, retVal) {}
#endif

#endif