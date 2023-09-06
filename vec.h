#ifndef _VEC_h_
#define _VEC_h_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int WINDOW_HEIGHT = 720;
const int WINDOW_LENGTH = 480;
const int X_CENTER      = 200;
const int Y_CENTER      = 200;

enum SHAPE_TYPE {
    LINE    // default vector
};

class Shape {
private:
    double x, y;
    SHAPE_TYPE type;

public:
    Shape(double x, double y, SHAPE_TYPE type);

    virtual void drawShape(sf::RenderWindow* window) = 0;
};

class Vector : public Shape {
private:
    double x,    y;
    double xEnd, yEnd;

public:   
    Vector(double x, double y);

    Vector* add(Vector a, Vector b);
    void drawShape(sf::RenderWindow* window) override;
};

class CoordinatePlane {
private:
    double  x, y;
    double  singleSegment;
    Shape** shapes;
    size_t  shapeCount;


public:
    CoordinatePlane(double x, double y, double singleSegment);
    CoordinatePlane(double x, double y, double singleSegment, Shape** shapes, size_t shapeCount);

    void drawAxis(sf::RenderWindow* window, int windowHeight, int windowLength);
    void drawAll (sf::RenderWindow* window, int windowHeight, int windowLength);
};

#endif