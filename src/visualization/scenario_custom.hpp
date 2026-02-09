#pragma once

#include "scenario_base.hpp"


struct CustomScenario : public Scenario{
    PhysicsObject circle1;
    PhysicsObject circle2;

    CircleRenderer c1;
    CircleRenderer c2;
    CustomScenario() : circle1(createCircle(10, BodyConfig(Point(300, 300), DirVector(50, -10), DirVector(0, 0), 10 , 0.5))),
                    circle2(createCircle(10, BodyConfig(Point(500, 300), DirVector(-50, -10), DirVector(0, 0), 1, 0.2))),
                    c1(circle1, sf::Color::Blue),
                    c2(circle2, sf::Color::Green) {
    }

    void Update(double time_step) override{
        circle1.getBody().update(time_step);
        circle2.getBody().update(time_step);

        if(areOverlapping(circle1, circle2))
            resolveOverlap(circle1, circle2);
    }

    void Draw(sf::RenderWindow& window) override {
        c1.Draw(window);
        c2.Draw(window);
    }
    
};