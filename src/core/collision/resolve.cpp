#include "PhysicsEngine/core/collision/resolve.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"
#include <cmath>

namespace Collision{
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

        
        void resolve(Body& body1, Body& body2, const Info& info){
            correctPosition(body1, body2, info.normal, info.penetration);
            updateImpulseSpeed(body1, body2, info.normal);
        }
    }
}