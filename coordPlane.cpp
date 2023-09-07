#include "vector.h"

CoordinatePlane::CoordinatePlane() :
    xOrigin(WINDOW_LENGTH / 2),
    yOrigin(WINDOW_HEIGHT / 2),
    xUnit  (DEFAULT_UNIT),
    yUnit  (DEFAULT_UNIT)       {}

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

void CoordinatePlane::draw(sf::RenderWindow* window) {
    ON_ERROR(!window, "Window was null!",);

    int unitPointCount = (WINDOW_HEIGHT / this->xUnit) + (WINDOW_LENGTH / this->yUnit);

    sf::VertexArray axis(sf::Lines, 2);

    // x axis
    axis.append(sf::Vertex(sf::Vector2f(0                , WINDOW_HEIGHT / 2)));
    axis.append(sf::Vertex(sf::Vector2f(WINDOW_LENGTH    , WINDOW_HEIGHT / 2)));

    axis.append(sf::Vertex(sf::Vector2f(WINDOW_LENGTH / 2, 0)));
    axis.append(sf::Vertex(sf::Vector2f(WINDOW_LENGTH / 2, WINDOW_HEIGHT)));

    // unit points on x axis
    for (int i = WINDOW_LENGTH / 2; i >= 0; i -= xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));
        
        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, (WINDOW_HEIGHT - UNIT_POINT_RAD) / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window->draw(point);
    }
    for (int i = WINDOW_LENGTH / 2; i <= WINDOW_LENGTH; i += xUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f(i - UNIT_POINT_RAD / 2, (WINDOW_HEIGHT - UNIT_POINT_RAD) / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window->draw(point);
    }

    for (int i = WINDOW_HEIGHT / 2; i >= 0; i -= yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f((WINDOW_LENGTH - UNIT_POINT_RAD) / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window->draw(point);
    }
    for (int i = WINDOW_HEIGHT / 2; i < WINDOW_HEIGHT; i += yUnit) {
        sf::RectangleShape point(sf::Vector2f(UNIT_POINT_RAD, UNIT_POINT_RAD));

        point.setPosition(sf::Vector2f((WINDOW_LENGTH - UNIT_POINT_RAD) / 2, i - UNIT_POINT_RAD / 2));
        point.setFillColor(DEFAULT_UNIT_POINT_COL);

        window->draw(point);
    }

    window->draw(axis);
}