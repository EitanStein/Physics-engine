#include "PhysicsEngine/core/collision/resolve.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"
#include <cmath>

namespace Collision{
    // TODO merge normal and penetretaion into collision info during detection
    namespace Normal{
        DirVector circleCircle(const Point& pos1, const Point& pos2){
            DirVector diff = pos2 - pos1;
            return diff/dist(diff, Point(0,0));
        }

        DirVector circleRect(const Circle& circle, const Point& pos1, const Rectangle& rect, const Point& pos2){
            
            double x_diff = circle.getRadius() + rect.getWidth()/2 - std::abs(pos2.x - pos1.x);
            double y_diff = circle.getRadius() + rect.getHeight()/2 - std::abs(pos2.y - pos1.y);
            // TODO need to also do (-1, 0) (0, -1) normals?
            if(x_diff > y_diff)
                return DirVector(0,1);
            else if(x_diff < y_diff)
                return DirVector(1,0);
            
            Point diff = pos2 - pos1;
            // TODO does this work proerply with a non-square rectangle of different proportions?
            return diff/dist(diff, Point(0,0));
        }

        DirVector rectRect(const Rectangle& rect1, const Point& pos1, const Rectangle& rect2, const Point& pos2){
            double x_diff = rect1.getWidth() + rect2.getWidth() - std::abs(pos2.x - pos1.x)*2;
            double y_diff = rect1.getHeight() + rect2.getHeight() - std::abs(pos2.y - pos1.y)*2;

            if(x_diff > y_diff){
                if(pos2.y > pos1.y)
                    return DirVector(0,1);
                return DirVector(0,-1);
            }
            else if(x_diff < y_diff)
            {
                if(pos2.x > pos1.x)
                    return DirVector(1,0);
                return DirVector(-1,0);
            }
            
            Point diff = pos2 - pos1;
            // TODO does this work proerply with non-square rectangles?
            return diff/dist(diff, Point(0,0));
        }
    }

    namespace Penetration{
        double circleCircle(const Circle& circle1, const Point& pos1, const Circle& circle2, const Point& pos2){
            return circle1.getRadius() + circle2.getRadius() - dist(pos1, pos2);
        }

        double circleRect(const Circle& circle, const Point& pos1, const Rectangle& rect, const Point& pos2){
            double x_diff = circle.getRadius() + rect.getWidth()/2 - std::abs(pos2.x - pos1.x);
            double y_diff = circle.getRadius() + rect.getHeight()/2 - std::abs(pos2.y - pos1.y);
            
            if(x_diff > y_diff)
                return y_diff;
            else if(x_diff < y_diff)
                return x_diff;

            double rect_cornser_dist = std::sqrt(std::pow(rect.getWidth(), 2) + std::pow(rect.getHeight(), 2)) / 2; 
            return circle.getRadius() + rect_cornser_dist - dist(pos1, pos2);
        }

        double rectRect(const Rectangle& rect1, const Point& pos1, const Rectangle& rect2, const Point& pos2){
            double x_diff = rect1.getWidth() + rect2.getWidth() - std::abs(pos2.x - pos1.x)*2;
            double y_diff = rect1.getHeight() + rect2.getHeight() - std::abs(pos2.y - pos1.y)*2;
            
            if(x_diff > y_diff)
                return y_diff;
            else if(x_diff < y_diff)
                return x_diff;

            double rect1_cornser_dist = std::sqrt(std::pow(rect1.getWidth(), 2) + std::pow(rect1.getHeight(), 2)) / 2; 
            double rect2_cornser_dist = std::sqrt(std::pow(rect2.getWidth(), 2) + std::pow(rect2.getHeight(), 2)) / 2; 
            return rect1_cornser_dist + rect2_cornser_dist - dist(pos1, pos2);
        }
    }

    namespace Resolve{
        void updateImpulseSpeed(Body& body1, Body& body2, const DirVector& normal){
            DirVector relative_velocity = body2.getVelocity() - body1.getVelocity();

            double normal_of_rel_velocity = dotProduct(relative_velocity, normal);

            if(normal_of_rel_velocity >= 0){
                LOG_INFO("In collision resolution but normalized rel velocity sugests they do not collide");
                return;
            }

            // TODO  need to handle very low coefficient? if coeff is 0~ the 2 objects will be in permanent collision 
            double restitution_coeff = calcRestitutionCoefficient(body1, body2);

            double impulse = -(1 + restitution_coeff) * normal_of_rel_velocity / (1/body1.getMass() + 1/body2.getMass());

            body1.resetSpeed(body1.getVelocity() - normal*(impulse/body1.getMass()));
            body2.resetSpeed(body2.getVelocity() + normal*(impulse/body2.getMass()));
        }

        // TODO change penetration name (a float that represents how much the ob jects overlap)
        void correctPosition(Body& body1, Body& body2, const DirVector& normal, double penetration){
            double body1_inv_mass = body1.getInverseMass();
            double body2_inv_mass = body2.getInverseMass();

            DirVector partial_correction = normal * penetration / (body1_inv_mass + body2_inv_mass);

            body1.movePos(partial_correction * (-body1_inv_mass));
            body2.movePos(partial_correction * body2_inv_mass);

        }

        // circle collisions
        void circleCircle(const Shape& shape1, Body& body1, const Shape& shape2, Body& body2){
            const Circle& circle1 = static_cast<const Circle&>(shape1);
            const Circle& circle2 = static_cast<const Circle&>(shape2);


            DirVector normal = Collision::Normal::circleCircle(body1.getPosition(), body2.getPosition());
            double penetration = Collision::Penetration::circleCircle(circle1, body1.getPosition(), 
                                                                        circle2, body2.getPosition());

            

            correctPosition(body1, body2, normal, penetration);
            updateImpulseSpeed(body1, body2, normal);
        }

        void circleRect(const Shape& shape1, Body& body1, const Shape& shape2, Body& body2){
            const Circle& circle = static_cast<const Circle&>(shape1);
            const Rectangle& rect = static_cast<const Rectangle&>(shape2);

            DirVector normal = Collision::Normal::circleRect(circle, body1.getPosition(), rect, body2.getPosition());
            double penetration = Collision::Penetration::circleRect(circle, body1.getPosition(), 
                                                                    rect, body2.getPosition());

            

            correctPosition(body1, body2, normal, penetration);
            updateImpulseSpeed(body1, body2, normal);
        }

        // rectangle collisions
        void rectCircle(const Shape& shape1, Body& body1, const Shape& shape2, Body& body2){
            circleRect(shape2, body2, shape1, body1);
        }

        void rectRect(const Shape& shape1, Body& body1, const Shape& shape2, Body& body2){
            const Rectangle& rect1 = static_cast<const Rectangle&>(shape1);
            const Rectangle& rect2 = static_cast<const Rectangle&>(shape2);

            DirVector normal = Collision::Normal::rectRect(rect1, body1.getPosition(), rect2, body2.getPosition());
            double penetration = Collision::Penetration::rectRect(rect1, body1.getPosition(), 
                                                                    rect2, body2.getPosition());

            

            correctPosition(body1, body2, normal, penetration);
            updateImpulseSpeed(body1, body2, normal);
        }


    }
}