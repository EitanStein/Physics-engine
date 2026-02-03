#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsEngine/core/PhysicsObject.hpp"


struct CircleRenderer{
    PhysicsObject& circle;
    sf::CircleShape draw_cricle;

    CircleRenderer(PhysicsObject& circle, sf::Color color) : circle(circle), draw_cricle(static_cast<Circle*>(circle.getShape())->getRadius()) {
        draw_cricle.setFillColor(color);
    }

    void Draw(sf::RenderWindow& window){
        const Body& body = circle.getBody();
        draw_cricle.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y));
        window.draw(draw_cricle);
    }
};

PhysicsObject createCircle(double rad, Point pos, DirVector spd, double mass=DEFAULT_MASS, double restitution=DEFAULT_RESTITUTION){
    PhysicsObject circle(rad, pos, mass, restitution);
    Body& body = circle.getBody();
    body.resetSpeed(spd);
    body.applyForce(DirVector(0, 10));
    return circle;
}



struct Scenario{
    virtual void Update(double time_step) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};