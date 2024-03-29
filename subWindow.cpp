#include "graphLib.h"

SubWindow::SubWindow(double x0, double y0, double sizeX, double sizeY) : sf::RenderTexture() {
    this->x0 = x0;
    this->y0 = y0;
    this->create(sizeX, sizeY);
}

SubWindow::~SubWindow() {
    this->x0 = NAN;
    this->y0 = NAN;
}

double SubWindow::getX0() {
    return this->x0;
}

double SubWindow::getY0() {
    return this->y0;
}

void SubWindow::displayOnWindow(sf::RenderWindow& window) {
    this->display();

    sf::Sprite sprite(this->getTexture());
    sprite.setPosition(this->x0, this->y0);
    window.draw(sprite);
}

bool SubWindow::pointInside(double x, double y) {
    return (this->getX0() <= x && x <= this->getX0() + this->getSize().x) &&
           (this->getY0() <= y && y <= this->getY0() + this->getSize().y);
}
