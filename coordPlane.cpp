#include "graphLib.h"

CoordinatePlane::CoordinatePlane(double xOrigin, double yOrigin, double xUnit, double yUnit) :
    xOrigin(xOrigin),
    yOrigin(yOrigin),
    xUnit  (xUnit),
    yUnit  (yUnit)              {}

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

    sf::VertexArray axis(sf::Lines, 2);

    // x axis
    axis.append(sf::Vertex(sf::Vector2f(0  , height / 2)));
    axis.append(sf::Vertex(sf::Vector2f(len, height / 2)));

    axis.append(sf::Vertex(sf::Vector2f(len / 2, 0)));
    axis.append(sf::Vertex(sf::Vector2f(len / 2, height)));

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

    window.draw(axis);
}