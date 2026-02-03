#pragma once

#include "scenario_base.hpp"


struct CustomScenario : public Scenario{
    PhysicsObject circle1;
    PhysicsObject circle2;

    CircleRenderer c1;
    CircleRenderer c2;
    CustomScenario() : circle1(createCircle(10, Point(300, 300), DirVector(50, -10))),
                    circle2(createCircle(10, Point(500, 300), DirVector(-50, -10))),
                    c1(circle1, sf::Color::Blue),
                    c2(circle2, sf::Color::Green) {
    }

    void Update(double time_step) override{
        circle1.getBody().update(time_step);
        circle2.getBody().update(time_step);

        if(areCirclesOverlapping(circle1, circle2))
            resolveCirclesOverlap(circle1, circle2);
    }

    void Draw(sf::RenderWindow& window) override {
        c1.Draw(window);
        c2.Draw(window);
    }
    
};