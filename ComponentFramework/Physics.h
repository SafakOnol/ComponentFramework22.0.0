#ifndef PHYSICS_H
#define PHYSICS_H

#include "PhysicsObject.h"
#include "Plane.h"
#include "Vmath.h"

class Physics
{
public:

	static Vec3 rotateZ(const Vec3 force, PhysicsObject& object);

	static void SimpleNewtonMotion(PhysicsObject& object, const float deltaTime);
	static void RigidBodyRotation(PhysicsObject& object, const float deltaTime);

	static void ApplyTorque(const float torque, PhysicsObject& object);
	static void ApplyForce(const Vec3 force, PhysicsObject& object);

	/*static bool PlaneShphereCollision(const PhysicsObject& object, const Plane& p);
	static void PlaneSphereCollisionResponse(PhysicsObject& object1, const PhysicsObject& object2);
	static bool SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2);
	static void SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);*/

};

#endif