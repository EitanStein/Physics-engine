#include "scenario_custom.hpp"
#include "scenario_circle_of_circles.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"
#include <memory>

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "debug visualizer");
    window.setFramerateLimit(60);


    const double time_step = 0.016;

    std::unique_ptr<Scenario> tester = std::make_unique<ScenarioCircleOfCircles>(8, 10);
    // std::unique_ptr<Scenario> tester = std::make_unique<CustomScenario>();


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        
        tester->draw(window);
        tester->update(time_step);


        window.display();
    }
}