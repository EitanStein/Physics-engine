#include "scenario_custom.hpp"
#include "scenario_circle_of_circles.hpp"
#include "PhysicsEngine/logging/log_macros.h"
#include <memory>

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "debug visualizer");


    double time_step = 0.001;
    // std::unique_ptr<Scenario> circle_tester = std::make_unique<ScenarioCircleOfCircles>(8, 10);
    std::unique_ptr<Scenario> circle_tester = std::make_unique<CustomScenario>();


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        
        circle_tester->Draw(window);
        circle_tester->Update(time_step);


        window.display();
    }
}