#pragma once

#include "scenario_base.hpp"


struct CustomScenario : public Scenario{
    CustomScenario() {
        objects.emplace_back(createCircle(10, BodyConfig(Point(300, 300), DirVector(50, -10), DirVector(0, 0), 10 , 0.5)));
        objects.emplace_back(createCircle(10, BodyConfig(Point(500, 300), DirVector(-50, -10), DirVector(0, 0), 1, 0.2)));

        renderers.emplace_back(objects[0], sf::Color::Blue);
        renderers.emplace_back(objects[1], sf::Color::Green);
    }
};