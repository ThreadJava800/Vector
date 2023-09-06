#include "vec.h"
  
Shape::Shape(double x, double y, SHAPE_TYPE type) :
        x(x), y(y), type(type) {}

Vector::Vector(double x, double y) : Shape(x, y, LINE) {
    this->x    = x;
    this->y    = y;
    this->xEnd = 0;
    this->yEnd = 0;
}

Vector::Vector(double x, double y, double xEnd, double yEnd) : Shape(x, y, LINE) {
    this->x    = x;
    this->y    = y;
    this->xEnd = xEnd;
    this->yEnd = yEnd;
}

Vector* Vector::add(Vector* a, Vector* b) {
    return new Vector(a->x + b->x, a->y + b->y);
}

void Vector::drawShape(sf::RenderWindow* window) {
    if (!window) return;

    sf::VertexArray lineObject(sf::LinesStrip, 2);

    lineObject[0].position = sf::Vector2f(X_CENTER, Y_CENTER);
    lineObject[1].position = sf::Vector2f(this->xEnd, this->yEnd);

    window->draw(lineObject);
}

CoordinatePlane::CoordinatePlane(double x, double y, double singleSegment) :
                x(x), y(y), singleSegment(singleSegment), shapes(nullptr), shapeCount(0) {}

CoordinatePlane::CoordinatePlane(double x, double y, double singleSegment, Shape** shapes, size_t shapeCount) :
                x(x), y(y), singleSegment(singleSegment), shapes(shapes), shapeCount(shapeCount) {}

void CoordinatePlane::drawAxis(sf::RenderWindow* window, int windowHeight, int windowLength) {
    if (!window) return;

    sf::VertexArray coordAxisY(sf::LinesStrip, 2);
    sf::VertexArray coordAxisX(sf::LinesStrip, 2);

    coordAxisY[0].position = sf::Vector2f(this->x, windowHeight);
    coordAxisY[1].position = sf::Vector2f(this->x, 0);

    coordAxisX[0].position = sf::Vector2f(0,            this->y);
    coordAxisX[1].position = sf::Vector2f(windowLength, this->y);

    window->draw(coordAxisX);
    window->draw(coordAxisY);
}

void CoordinatePlane::drawAll (sf::RenderWindow* window, int windowHeight, int windowLength) {
    if (!window) return;

    window->clear();
    drawAxis(window, windowHeight, windowLength);
    
    if (this->shapes) {
        for (size_t i = 0; i < this->shapeCount; i++) {
            if (this->shapes[i])
                this->shapes[i]->drawShape(window);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_LENGTH), "");
    window.setPosition(sf::Vector2i(0, 0));

    Vector* vec = new Vector(X_CENTER, Y_CENTER, 20, 20);
    CoordinatePlane* plane = new CoordinatePlane(X_CENTER, Y_CENTER, 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close if escape clicked
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition();
                vec->drawShape(&window, vectorLine, &mousePos);
            }
        }

        window.clear();
        window.draw(vectorLine);
        window.draw(coordAxisX);
        window.draw(coordAxisY);
        window.display();
    }

    return 0;
}