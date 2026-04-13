#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsEngine/core/PhysicsObject.hpp"
#include <memory>


struct Renderer{
    PhysicsObject& obj;
    std::unique_ptr<sf::Shape> p_drawer;
    
    Renderer(PhysicsObject& obj, sf::Color color) : obj(obj) {
        ShapeT::Type shape = obj.getShape().type();

        switch(shape){
            case ShapeT::Type::Circle:
                p_drawer = std::make_unique<sf::CircleShape>
                                    (static_cast<const Circle&>(obj.getShape()).getRadius());
                break;
            case ShapeT::Type::Rectangle:
            const Rectangle& rect = static_cast<const Rectangle&>(obj.getShape());
                p_drawer = std::make_unique<sf::RectangleShape>
                                    (sf::Vector2f(rect.getWidth(), rect.getHeight()));
                break;
        }


        p_drawer->setFillColor(color);
    }

    void draw(sf::RenderWindow& window){
        const Body& body = obj.getBody();
        const Point& pos = body.getPosition();
        p_drawer->setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(*p_drawer);
    }
};

struct CircleRenderer{
    PhysicsObject& circle;
    sf::CircleShape draw_cricle;

    CircleRenderer(PhysicsObject& circle, sf::Color color) : circle(circle), draw_cricle(static_cast<const Circle&>(circle.getShape()).getRadius()) {
        draw_cricle.setFillColor(color);
    }

    void Draw(sf::RenderWindow& window){
        const Body& body = circle.getBody();
        const Point& pos = body.getPosition();
        draw_cricle.setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(draw_cricle);
    }
};

// TODO make generic renderer class
struct RectRenderer{
    PhysicsObject& rect;
    sf::RectangleShape draw_rect;

    RectRenderer(PhysicsObject& rect, sf::Color color) : rect(rect), draw_rect(sf::Vector2f(static_cast<const Rectangle&>(rect.getShape()).getWidth(),
                                                                                            static_cast<const Rectangle&>(rect.getShape()).getHeight())) {
        draw_rect.setFillColor(color);
    }

    void Draw(sf::RenderWindow& window){
        const Body& body = rect.getBody();
        const Point& pos = body.getPosition();
        draw_rect.setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(draw_rect);
    }
};

PhysicsObject createRect(double width, double height, const BodyConfig& body_config){
    PhysicsObject rect(std::move(ShapeFactory::createRect(width, height)), body_config);
    return rect;
}


PhysicsObject createCircle(double rad, const BodyConfig& body_config){
    PhysicsObject circle(std::move(ShapeFactory::createCircle(rad)), body_config);
    return circle;
}



struct Scenario{
    virtual void Update(double time_step) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};