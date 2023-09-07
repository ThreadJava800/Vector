#ifndef _VEC_h_
#define _VEC_h_

#include <unistd.h>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int       WINDOW_LENGTH          = 1920;
const int       WINDOW_HEIGHT          = 1080;
const double    DEFAULT_UNIT           = 100;
const float     UNIT_POINT_RAD         = 4;
const sf::Color DEFAULT_LINE_COLOR     = sf::Color::White;
const sf::Color DEFAULT_UNIT_POINT_COL = sf::Color::Red;

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

    void draw(sf::RenderWindow& window);
};

class Vector {
private:
    double    x, y;
    sf::Color color;

    void drawArrowheads(sf::RenderWindow& window, CoordinatePlane& coordPlane);
    void drawLine      (sf::RenderWindow& window, CoordinatePlane& coordPlane,
                        double xStart, double yStart);

public:
    Vector();
    Vector(double x, double y);
    Vector(double x, double y, sf::Color color);

    double    getX();
    double    getY();
    sf::Color getColor();

    void setX(double x);
    void setY(double y);
    void setColor(sf::Color color);

    inline double len() const;

    void rotate(double degree);  // not radians
    void draw(sf::RenderWindow& window, CoordinatePlane& coordPlane, 
              double xStart = 0, double yStart = 0);

    friend Vector operator+  (const Vector& a, const Vector& b);
    friend void   operator+= (      Vector& a, const Vector& b);
    friend Vector operator-  (const Vector& a, const Vector& b);
    friend void   operator-= (      Vector& a, const Vector& b);
    friend Vector operator-  (const Vector& a);
    friend Vector operator*  (const Vector& a, double scalar);
    friend Vector operator*  (double scalar, const Vector& a);
    friend void   operator*= (      Vector& a, double scalar);
    friend Vector operator/  (const Vector& a, double scalar);
    friend void   operator/= (      Vector& a, double scalar);
    friend Vector operator&  (const Vector& a);                   // projection on ox
    friend Vector operator~  (const Vector& a);                   // projection on oy
    friend bool   operator== (const Vector& a, const Vector& b);
    friend bool   operator!= (const Vector& a, const Vector& b);
    friend Vector operator>> (const Vector& a, double scalar);    // rotate right on scalar degs
    friend Vector operator<< (const Vector& a, double scalar);    // rotate left on scalar degs
    friend void   operator>>=(      Vector& a, double scalar);    // rotate right on scalar degs
    friend void   operator<<=(      Vector& a, double scalar);    // rotate left on scalar degs
    friend Vector operator!  (const Vector& a);                   // normal vector
    friend double operator,  (const Vector& a, const Vector& b);  // scalar mul
};

sf::Vector2f vecGraphToCoord(CoordinatePlane& coordPlane, double x, double y);
sf::Vector2f vecCoordToGraph(CoordinatePlane& coordPlane, double x, double y);

#endif