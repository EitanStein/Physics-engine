#include "PhysicsEngine/core/collision/resolve.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"

namespace Collision{
    namespace Normal{
        DirVector circleCircle(const Point& pos1, const Point& pos2){
            DirVector diff = pos2 - pos1;
            return diff/dist(diff, Point(0,0));
        }
    }

    namespace Penetration{
        double circleCircle(const Circle& circle1, const Body& body1, const Circle& circle2, const Body& body2){
            return circle1.getRadius() + circle2.getRadius() - dist(body1.getPosition(), body2.getPosition());
        }
    }

    namespace Resolve{
        void circleCircle(const Shape& circle1, Body& body1, const Shape& circle2, Body& body2){
            // calculate speed impulse change
            DirVector relative_velocity = body2.getVelocity() - body1.getVelocity();
            DirVector normal = Collision::Normal::circleCircle(body1.getPosition(), body2.getPosition());

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
    }
}