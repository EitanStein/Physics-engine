#pragma once

#include "scenario_base.hpp"


struct ScenarioCircleOfCircles : public Scenario{
    ScenarioCircleOfCircles(int num_circles, double rad){
        objects.reserve(num_circles);
        renderers.reserve(num_circles);

        int main_circle_rad = 100;
        Point center(400,300);
        double deg = 360/num_circles;

        Point prev_circle(-1, 0);

        BodyConfig circle_body_config;
    
        for(int i = 0; i < num_circles ; ++i){

            circle_body_config.position = prev_circle*main_circle_rad + center;
            circle_body_config.velocity = center-circle_body_config.position;
            objects.push_back(createCircle(rad, circle_body_config));

            double color = (i+1)*255/num_circles;
            renderers.emplace_back(objects.back(), sf::Color(color, color, color));


            // find next circle by rotating the circle center
            double new_x = prev_circle.x * cos(3.14*deg/180) - prev_circle.y * sin(3.14*deg/180);
            double new_y = prev_circle.x * sin(3.14*deg/180) + prev_circle.y * cos(3.14*deg/180);

            prev_circle.x = new_x;
            prev_circle.y = new_y;
        }

    }
};