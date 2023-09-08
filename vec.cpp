#include "graphLib.h"

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

sf::Vector2f vecCoordToGraph(SubWindow& subWindow, CoordinatePlane& coordPlane, double x, double y) {
    return sf::Vector2f(subWindow.getSize().x / 2 + x * coordPlane.getXUnit(),
                        subWindow.getSize().y / 2 - y * coordPlane.getYUnit());
}

sf::Vector2f vecGraphToCoord(SubWindow& subWindow, CoordinatePlane& coordPlane, double x, double y) {
    return sf::Vector2f((x - subWindow.getSize().x / 2) / coordPlane.getXUnit(), 
                        (subWindow.getSize().y / 2 - y) / coordPlane.getYUnit());
}

void Vector::setX(double x) {
    if (x != NAN) this->x = x;
    else std::cerr << "Value was NAN\n";
}

void Vector::setY(double y) {
    if (y != NAN) this->y = y;
    else std::cerr << "Value was NAN\n";
}

void Vector::setColor(sf::Color color) {
    this->color = color;
}

void Vector::drawArrowheads(SubWindow& window, CoordinatePlane& coordPlane, double xStart, double yStart) {
    sf::VertexArray vecHead = sf::VertexArray(sf::Triangles, 3);
    Vector startVec = Vector(xStart, yStart, this->color);

    // question
    Vector leftArrow = (*this) - startVec;
    leftArrow = !(leftArrow) * ARROW_SIZE_COEF - (leftArrow) * ARROW_SIZE_COEF;
    leftArrow = leftArrow + Vector(this->x, this->y); // parallel move of vector

    Vector rightArrow = (*this) - startVec;
    rightArrow = !(rightArrow) * -ARROW_SIZE_COEF - (rightArrow) * ARROW_SIZE_COEF;
    rightArrow = rightArrow + Vector(this->x, this->y);

    vecHead[0].position = vecCoordToGraph(window, coordPlane, leftArrow.x, leftArrow.y);
    vecHead[1].position = vecCoordToGraph(window, coordPlane, rightArrow.x, rightArrow.y);
    vecHead[2].position = vecCoordToGraph(window, coordPlane, this->x, this->y);

    vecHead[0].color    = this->color;
    vecHead[1].color    = this->color;
    vecHead[2].color    = this->color;

    window.draw(vecHead);
}

void Vector::drawLine(SubWindow& window, CoordinatePlane& coordPlane, double xStart, double yStart) {
    sf::VertexArray lineObject(sf::LinesStrip, 2);

    lineObject[0].position = vecCoordToGraph(window, coordPlane, xStart, yStart);
    lineObject[1].position = vecCoordToGraph(window, coordPlane, this->x, this->y);;

    lineObject[0].color = this->color;
    lineObject[1].color = this->color;

    window.draw(lineObject);
}

void Vector::draw(SubWindow& window, CoordinatePlane& coordPlane, double xStart, double yStart) {
    drawLine(window, coordPlane, xStart, yStart);
    drawArrowheads(window, coordPlane, xStart, yStart);
}

Vector operator+(const Vector& a, const Vector& b) {
    sf::Color resColor = (a.color == b.color) ? a.color : DEFAULT_LINE_COLOR;
    return Vector(a.x + b.x, a.y + b.y, resColor);
}

void operator+= (Vector& a, const Vector& b) {
    a = a + b;
}

Vector operator-(const Vector& a, const Vector& b) {
    sf::Color resColor = (a.color == b.color) ? a.color : DEFAULT_LINE_COLOR;
    return Vector(a.x - b.x, a.y - b.y, resColor);
}

void operator-= (Vector& a, const Vector& b) {
    a = a - b;
}

Vector operator-(const Vector& a) {
    return Vector(-1 * a.x, -1 * a.y, a.color);
}

Vector operator*(const Vector& a, double scalar) {
    return Vector(scalar * a.x, scalar * a.y, a.color);
}

Vector operator*(double scalar, const Vector& a) {
    return Vector(scalar * a.x, scalar * a.y, a.color);
}

void operator*= (Vector& a, double scalar) {
    a = a * scalar;
}

Vector operator/ (const Vector& a, double scalar) {
    return Vector(a.x / scalar, a.y / scalar, a.color);
}

void operator/= (Vector& a, double scalar) {
    a = a / scalar;
}

// projection on ox
Vector operator&(const Vector& a) {
    return Vector(a.x, 0, a.color);
}

// projection on oy
Vector operator~(const Vector& a) {
    return Vector(0, a.y, a.color);
}

Vector operator>> (const Vector& a, double scalar) {
    Vector result = a;
    result >>= scalar;
    return result;
}

Vector operator<< (const Vector& a, double scalar) {
    Vector result = a;
    result <<= scalar;
    return result;
}

void operator>>=(Vector& a, double scalar) {
    a.rotate(-1 * scalar);
}

void operator<<=(Vector& a, double scalar) {
    a.rotate(scalar);
}

bool operator==(const Vector& a, const Vector& b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const Vector& a, const Vector& b) {
    return (a.x != b.x) || (a.y != b.y);
}

// normal vector
Vector operator!(const Vector& a) {
    return Vector((-1 * a.y) / a.len(), a.x / a.len(), a.color);
}

// scalar mul
double operator,(const Vector& a, const Vector& b) {
    return a.x * b.x + a.y * b.y;
}