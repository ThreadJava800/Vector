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

void CoordinatePlane::drawPoints(SubWindow& window) {
    // unit points on x axis
    for (int i = xOrigin; i >= 0; i -= xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, yOrigin - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
    for (int i = xOrigin; i <= window.getSize().x + window.getX0(); i += xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, yOrigin - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }

    // unit points on y axis
    for (int i = yOrigin; i >= 0; i -= yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(xOrigin - UNIT_POINT_RAD / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
    for (int i = yOrigin; i < window.getSize().y + window.getY0(); i += yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(xOrigin - UNIT_POINT_RAD / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window.draw(point);
    }
}

void CoordinatePlane::drawFrame (SubWindow& window) {
    sf::RectangleShape frame(sf::Vector2f(window.getSize().x - 2 * FRAME_WIDTH, window.getSize().y - 2 * FRAME_WIDTH));
    frame.setFillColor   (sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::White);
    frame.setOutlineThickness(FRAME_WIDTH);
    frame.setPosition(FRAME_WIDTH, FRAME_WIDTH);
    window.draw(frame);
}

void CoordinatePlane::draw(SubWindow& window) {
    sf::Vector2f oxStart = vecGraphToCoord(window, *this, window.getX0(), this->yOrigin + window.getY0());
    sf::Vector2f oxEnd   = vecGraphToCoord(window, *this, window.getX0() + window.getSize().x, this->yOrigin + window.getY0());
    Vector       ox      = Vector(oxEnd.x, oxEnd.y, sf::Color::White);

    sf::Vector2f oyStart = vecGraphToCoord(window, *this, this->xOrigin + window.getX0(), window.getY0() + window.getSize().y);
    sf::Vector2f oyEnd   = vecGraphToCoord(window, *this, this->xOrigin + window.getX0(), window.getY0());
    Vector       oy      = Vector(oyEnd.x, oyEnd.y, sf::Color::White);

    ox.draw(window, *this, oxStart.x, oxStart.y);
    oy.draw(window, *this, oyStart.x, oyStart.y);

    drawPoints(window);
    drawFrame (window);
}