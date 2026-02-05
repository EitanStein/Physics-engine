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
        const Point& pos = body.getPosition();
        draw_cricle.setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(draw_cricle);
    }
};

PhysicsObject createCircle(double rad, const BodyConfig& body_config){
    PhysicsObject circle(rad, body_config);
    Body& body = circle.getBody();
    return circle;
}



struct Scenario{
    virtual void Update(double time_step) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};