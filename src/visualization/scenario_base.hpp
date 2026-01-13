#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsEngine/core/PhysicsObject.hpp"


struct CircleRenderer{
    PhysicsObject& circle;
    sf::CircleShape draw_cricle;

    CircleRenderer(PhysicsObject& circle, sf::Color color) : circle(circle), draw_cricle(circle.getRadius()) {
        draw_cricle.setFillColor(color);
    }

    void Draw(sf::RenderWindow& window){
        draw_cricle.setPosition(sf::Vector2f(circle.getPos().x, circle.getPos().y));
        window.draw(draw_cricle);
    }
};

PhysicsObject createCircle(double rad, Point pos, DirVector spd){
    PhysicsObject circle(rad, pos);
    circle.resetSpeed(spd);
    circle.applyForce(DirVector(0, 10));
    return circle;
}



struct Scenario{
    virtual void Update(double time_step) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};