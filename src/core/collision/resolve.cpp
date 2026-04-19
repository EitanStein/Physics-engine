#include "PhysicsEngine/core/collision/resolve.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"
#include <cmath>

namespace Collision{
    namespace Resolve{
        void updateImpulseSpeed(Body& body1, Body& body2, const Info& info){
            DirVector relative_a = info.contact_point - body1.getPosition();
            DirVector relative_b = info.contact_point - body2.getPosition();

            DirVector velocity_a = body1.getVelocity() + cross(body1.getAngularVel(), relative_a);
            DirVector velocity_b = body2.getVelocity() + cross(body2.getAngularVel(), relative_b);

            DirVector relative_velocity = velocity_b - velocity_a;

            double normal_of_rel_velocity = dotProduct(relative_velocity, info.normal);

            if(normal_of_rel_velocity >= 0){
                LOG_INFO("In collision resolution but normalized rel velocity sugests they do not collide");
                return;
            }

            // TODO  need to handle very low coefficient? if coeff is 0~ the 2 objects will be in permanent collision 
            double restitution_coeff = calcRestitutionCoefficient(body1, body2);
            
            double rel_a_cross_n = cross(relative_a, info.normal);
            double rel_b_cross_n = cross(relative_b, info.normal);

            double denom =
                body1.getInverseMass() + body2.getInverseMass() +
                (rel_a_cross_n * rel_a_cross_n) * body1.getInverseInertia() +
                (rel_b_cross_n * rel_b_cross_n) * body2.getInverseInertia();
            
            double J = -(1 + restitution_coeff) * normal_of_rel_velocity / denom;

            DirVector impulse = info.normal * J;

            body1.resetSpeed(body1.getVelocity() - (impulse/body1.getMass()));
            body2.resetSpeed(body2.getVelocity() + (impulse/body2.getMass()));

            body1.resetAngularSpeed(
                body1.getAngularVel() - body1.getInverseInertia() * cross(relative_a, impulse)
            );
            body2.resetAngularSpeed(
                body2.getAngularVel() + body2.getInverseInertia() * cross(relative_b, impulse)
            );
        }

        // TODO change penetration name (a float that represents how much the ob jects overlap)
        void correctPosition(Body& body1, Body& body2, const Info& info){
            double body1_inv_mass = body1.getInverseMass();
            double body2_inv_mass = body2.getInverseMass();

            DirVector partial_correction = info.normal * info.penetration / (body1_inv_mass + body2_inv_mass);

            body1.movePos(partial_correction * (-body1_inv_mass));
            body2.movePos(partial_correction * body2_inv_mass);

        }

        
        void resolve(Body& body1, Body& body2, const Info& info){
            correctPosition(body1, body2, info);
            updateImpulseSpeed(body1, body2, info);
        }
    }
}