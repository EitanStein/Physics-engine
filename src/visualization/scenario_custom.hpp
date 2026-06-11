#pragma once

#include "scenario_base.hpp"


struct CustomScenario : public Scenario{
    CustomScenario() {
        objects.emplace_back(createRect(10, 20, BodyConfig(Point{300, 290}, DirVector{50, -10}, DirVector{0, 0}, 1 , 0.5)));
        objects.emplace_back(createRect(10, 30, BodyConfig(Point{500, 300}, DirVector{-50, -10}, DirVector{0, 0}, 1, 0.2)));
        objects.emplace_back(createRect(10, 10, BodyConfig(Point{700, 310}, DirVector{-50, -10}, DirVector{0, 0}, 1 , 0.5)));
        
        renderers.emplace_back(objects[0], sf::Color::Blue);
        renderers.emplace_back(objects[1], sf::Color::Green);
        renderers.emplace_back(objects[2], sf::Color::Red);
    }
};