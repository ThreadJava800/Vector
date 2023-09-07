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

inline double Vector::len() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

void Vector::setColor(sf::Color color) {
    this->color = color;
}

void Vector::drawArrowheads(sf::RenderWindow* window, CoordinatePlane* coordPlane) {
    ON_ERROR(!window || !coordPlane, "Null pointer exception",);

    // question
    Vector leftArrow = !(*this) * 0.1 - (*this) * 0.1;  // TODO: move to constants
    leftArrow = leftArrow + Vector(this->x, this->y); // parallel move of vector

    Vector rightArrow = !(*this) * -0.1 - (*this) * 0.1;  // TODO: move to constants
    rightArrow = rightArrow + Vector(this->x, this->y);

    leftArrow.setColor(sf::Color::Red);
    rightArrow.setColor(sf::Color::Red);
    leftArrow.drawLine(window, coordPlane, this->x, this->y);
    rightArrow.drawLine(window, coordPlane, this->x, this->y);
}

void Vector::drawLine(sf::RenderWindow* window, CoordinatePlane* coordPlane, double xStart, double yStart) {
    ON_ERROR(!window || !coordPlane, "Null pointer exception",);

    sf::VertexArray lineObject(sf::LinesStrip, 2);

    lineObject[0].position = sf::Vector2f(WINDOW_LENGTH / 2 + xStart * coordPlane->getXUnit(), 
                                          WINDOW_HEIGHT / 2 - yStart * coordPlane->getYUnit());
    lineObject[1].position = sf::Vector2f(WINDOW_LENGTH / 2 + this->x * coordPlane->getXUnit(), 
                                          WINDOW_HEIGHT / 2 - this->y * coordPlane->getYUnit());

    lineObject[0].color = this->color;
    lineObject[1].color = this->color;

    window->draw(lineObject);
}

void Vector::draw(sf::RenderWindow* window, CoordinatePlane* coordPlane, double xStart, double yStart) {
    drawLine(window, coordPlane, xStart, yStart);
    drawArrowheads(window, coordPlane);
}

Vector operator+(const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y);
}

Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a.x - b.x, a.y - b.y);
}

Vector operator-(const Vector& a) {
    return Vector(-1 * a.x, -1 * a.y, a.color);
}

Vector operator*(const Vector& a, double scalar) {
    return Vector(scalar * a.x, scalar * a.y, a.color);
}

// normal vector
Vector operator!(const Vector& a) {
    return Vector((-1 * a.y) / a.len(), a.x / a.len(), a.color);
}

// scalar mul
double operator,(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y;
}