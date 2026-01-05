#pragma once

#include "scenario_base.hpp"


struct ScenarioCircleOfCircles : public Scenario{
    std::vector<PhysicsObject> circles;
    std::vector<CircleRenderer> circles_drawers;

    ScenarioCircleOfCircles(int num_circles, double rad){
        circles.reserve(num_circles);
        circles_drawers.reserve(num_circles);
        int main_circle_rad = 100;
        Point center(400,300);
        double deg = 360/num_circles;

        Point prev_circle(-1, 0);
    
        for(int i = 0; i < num_circles ; ++i){

            Point new_circle_center = prev_circle*main_circle_rad + center;
            circles.push_back(createCircle(rad, new_circle_center, center-new_circle_center));

            double color = (i+1)*255/num_circles;
            circles_drawers.emplace_back(circles.back(), sf::Color(color, color, color));


            // find next circle by rotating the circle center
            double new_x = prev_circle.x * cos(3.14*deg/180) - prev_circle.y * sin(3.14*deg/180);
            double new_y = prev_circle.x * sin(3.14*deg/180) + prev_circle.y * cos(3.14*deg/180);

            prev_circle.x = new_x;
            prev_circle.y = new_y;
        }

    }

    void Update(double time_step) override{
        for(auto& circle: circles)
            circle.update(time_step);
        
        for(auto& circle: circles){
            for(auto& other_circle: circles){
                // is same circle
                if(circle.getPos() == other_circle.getPos() && circle.getVelocity() == other_circle.getVelocity())
                    continue;

                if(areCirclesOverlapping(circle, other_circle))
                    resolveCirclesOverlap(circle, other_circle);
            }
        }
    }

    void Draw(sf::RenderWindow& window) override { 
        for(auto& circle_drawer: circles_drawers)
            circle_drawer.Draw(window);
    }
};