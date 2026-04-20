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
            case ShapeT::Type::Circle:{
                double radius = static_cast<const Circle&>(obj.getShape()).getRadius();
                p_drawer = std::make_unique<sf::CircleShape>(radius);
                p_drawer->setOrigin(sf::Vector2f(radius, radius));
                break;
            }
                
            case ShapeT::Type::Rectangle:{
                const Rectangle& rect = static_cast<const Rectangle&>(obj.getShape());
                p_drawer = std::make_unique<sf::RectangleShape>
                                    (sf::Vector2f(rect.getWidth(), rect.getHeight()));
                p_drawer->setOrigin(sf::Vector2f(rect.getWidth()/2, rect.getHeight()/2));
                break;
            }
            
        }


        p_drawer->setFillColor(color);
    }

    void draw(sf::RenderWindow& window){
        const Body& body = obj.getBody();
        const Point& pos = body.getPosition();
        p_drawer->setPosition(sf::Vector2f(pos.x, pos.y));
        p_drawer->setRotation(sf::radians(body.getAngle()));
        window.draw(*p_drawer);
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
    std::vector<PhysicsObject> objects;
    std::vector<Renderer> renderers;


    void update(double time_step){
        for(auto& obj: objects)
            obj.getBody().update(time_step);
        
        Collision::Info info;

        for(int i=0; i< objects.size()-1 ; ++i){
            PhysicsObject& obj = objects[i];
            for(int j=i+1 ; j < objects.size() ; ++j){
                PhysicsObject& other_obj = objects[j];


                if(areOverlapping(obj, other_obj, info))
                    resolveOverlap(obj, other_obj, info);
            }
        }
    }

    void draw(sf::RenderWindow& window){
        for(auto& renderer : renderers)
            renderer.draw(window);
    }
};