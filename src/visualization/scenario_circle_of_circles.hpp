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

        BodyConfig circle_body_config;
    
        for(int i = 0; i < num_circles ; ++i){

            circle_body_config.position = prev_circle*main_circle_rad + center;
            circle_body_config.velocity = center-circle_body_config.position;
            circles.push_back(createCircle(rad, circle_body_config));

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
            circle.getBody().update(time_step);
        
        for(int i=0; i< circles.size()-1 ; ++i){
            PhysicsObject& circle = circles[i];
            for(int j=i+1 ; j < circles.size() ; ++j){
                PhysicsObject& other_circle = circles[j];


                if(areOverlapping(circle, other_circle))
                    resolveOverlap(circle, other_circle);
            }
        }
    }

    void Draw(sf::RenderWindow& window) override { 
        for(auto& circle_drawer: circles_drawers)
            circle_drawer.Draw(window);
    }
};