#include "graphLib.h"

CoordinatePlane::CoordinatePlane(double xOrigin, double yOrigin, double xUnit, double yUnit) :
    xOrigin(xOrigin),
    yOrigin(yOrigin),
    xUnit  (xUnit),
    yUnit  (yUnit)              {}

CoordinatePlane::~CoordinatePlane() {
    this->xOrigin = NAN;
    this->yOrigin = NAN;
    this->xUnit   = NAN;
    this->yUnit   = NAN;
}

double CoordinatePlane::getXOrigin() {
    return this->xOrigin;
}
double CoordinatePlane::getYOrigin() {
    return this->yOrigin;
}
double CoordinatePlane::getXUnit() {
    return this->xUnit;
}
double CoordinatePlane::getYUnit() {
    return this->yUnit;
}

void CoordinatePlane::draw(SubWindow& window) {
    double len = window.getSize().x, height = window.getSize().y;

    int unitPointCount = (len / this->xUnit) + (height / this->yUnit);

    sf::Vector2f oxStart = vecGraphToCoord(window, *this, window.getX0(),   height / 2 + window.getY0());
    sf::Vector2f oxEnd   = vecGraphToCoord(window, *this, len + window.getX0(), height / 2 + window.getY0());
    Vector       ox      = Vector(oxEnd.x, oxEnd.y, sf::Color::White);

    sf::Vector2f oyStart = vecGraphToCoord(window, *this, len / 2 + window.getX0(), height + window.getY0());
    sf::Vector2f oyEnd   = vecGraphToCoord(window, *this, len / 2 + window.getX0(), window.getY0());
    Vector       oy      = Vector(oyEnd.x, oyEnd.y, sf::Color::White);

    ox.draw(window, *this, oxStart.x, oxStart.y);
    oy.draw(window, *this, oyStart.x, oyStart.y);

    // unit points on x axis
    for (int i = len / 2; i >= 0; i -= xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, (height - UNIT_POINT_RAD) / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
    for (int i = len / 2; i <= len; i += xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, (height - UNIT_POINT_RAD) / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }

    // unit points on y axis
    for (int i = height / 2; i >= 0; i -= yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f((len - UNIT_POINT_RAD) / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
    for (int i = height / 2; i < height; i += yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f((len - UNIT_POINT_RAD) / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
}