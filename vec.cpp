#include "vector.h"

Vector::Vector() :
    x    (0),
    y    (0),
    color(DEFAULT_LINE_COLOR) {}

Vector::Vector(double x, double y) :
    x    (x),
    y    (y),
    color(DEFAULT_LINE_COLOR) {}

Vector::Vector(double x, double y, sf::Color color) :
    x    (x),
    y    (y),
    color(color)              {}

double Vector::getX() {
    return this->x;
}

double Vector::getY() {
    return this->y;
}

sf::Color Vector::getColor() {
    return this->color;
}

void Vector::draw(sf::RenderWindow* window, CoordinatePlane* coordPlane) {
    ON_ERROR(!window, "Window was null!",);

    sf::VertexArray lineObject(sf::LinesStrip, 2);

    lineObject[0].position = sf::Vector2f(WINDOW_LENGTH / 2, WINDOW_HEIGHT / 2);
    lineObject[1].position = sf::Vector2f(WINDOW_LENGTH / 2 + this->x * coordPlane->getXUnit(), 
                                          WINDOW_HEIGHT / 2 - this->y * coordPlane->getYUnit());

    window->draw(lineObject);
}

Vector Vector::operator+(Vector const& toSum) {
    return Vector(this->x + toSum.x, this->y + toSum.y);
}