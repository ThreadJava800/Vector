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

void Vector::rotate(double degree) {
    double radians = degree * M_PI / 180;

    double oldX   = this->x,      oldY   = this->y;
    double degCos = cos(radians), degSin = sin(radians);

    // (sin(a) + cos(a)i)*(x+yi) = (sin(a)*x - cos(a)*y)+(sin(a)*y + cos(a)*x)i
    this->x = degCos * oldX - degSin * oldY;
    this->y = degCos * oldY + degSin * oldX;
}

inline sf::Vector2f vecCoordToGraph(CoordinatePlane& coordPlane, double x, double y) {
    return sf::Vector2f(WINDOW_LENGTH / 2 + x * coordPlane.getXUnit(),
                        WINDOW_HEIGHT / 2 - y * coordPlane.getYUnit());
}

void Vector::setColor(sf::Color color) {
    this->color = color;
}

void Vector::drawArrowheads(sf::RenderWindow& window, CoordinatePlane& coordPlane) {
    sf::VertexArray vecHead = sf::VertexArray(sf::Triangles, 3);

    // question
    Vector leftArrow = !(*this) * 0.1 - (*this) * 0.1;  // TODO: move to constants
    leftArrow = leftArrow + Vector(this->x, this->y); // parallel move of vector

    Vector rightArrow = !(*this) * -0.1 - (*this) * 0.1;  // TODO: move to constants
    rightArrow = rightArrow + Vector(this->x, this->y);

    vecHead[0].position = vecCoordToGraph(coordPlane, leftArrow.x, leftArrow.y);
    vecHead[1].position = vecCoordToGraph(coordPlane, rightArrow.x, rightArrow.y);
    vecHead[2].position = vecCoordToGraph(coordPlane, this->x, this->y);

    vecHead[0].color    = this->color;
    vecHead[1].color    = this->color;
    vecHead[2].color    = this->color;

    window.draw(vecHead);
}

void Vector::drawLine(sf::RenderWindow& window, CoordinatePlane& coordPlane, double xStart, double yStart) {
    sf::VertexArray lineObject(sf::LinesStrip, 2);

    lineObject[0].position = vecCoordToGraph(coordPlane, xStart, yStart);
    lineObject[1].position = vecCoordToGraph(coordPlane, this->x, this->y);;

    lineObject[0].color = this->color;
    lineObject[1].color = this->color;

    window.draw(lineObject);
}

void Vector::draw(sf::RenderWindow& window, CoordinatePlane& coordPlane, double xStart, double yStart) {
    drawLine(window, coordPlane, xStart, yStart);
    drawArrowheads(window, coordPlane);
}

Vector operator+(const Vector& a, const Vector& b) {
    sf::Color resColor = (a.color == b.color) ? a.color : DEFAULT_LINE_COLOR;
    return Vector(a.x + b.x, a.y + b.y, resColor);
}

Vector operator-(const Vector& a, const Vector& b) {
    sf::Color resColor = (a.color == b.color) ? a.color : DEFAULT_LINE_COLOR;
    return Vector(a.x - b.x, a.y - b.y, resColor);
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