#include "Physics.h"



void Physics::SimpleNewtonMotion(PhysicsObject& object, const float deltaTime)
{
	// posFinal = posInit + velInit * deltaTime + 0.5 * accel * deltaTime * deitaTime
	object.SetPos(object.GetPos() + object.GetVel() * deltaTime + 0.5f * object.GetAccel() * deltaTime * deltaTime);	
	
	// velFinal = velInit + accel * deltaTime
	object.SetVel(object.GetVel() + object.GetAccel() * deltaTime);	
}

void Physics::RigidBodyRotation(PhysicsObject& object, const float deltaTime)
{
	// angPosFinal = angPosInit + angVelIinit * deltaTime + 0.5 * angAccel * deltaTime * deltaTime
	object.SetAngle(object.GetAngle() + object.GetAngularVel() * deltaTime + 0.5f * object.GetAngularAccel() * deltaTime * deltaTime);

	// angVelFinal = angVelInit + angAccel * deltaTime
	object.SetAngularVel(object.GetAngularVel() + object.GetAngularAccel() * deltaTime);	
}

Vec3 Physics::rotateZ(const Vec3 force, PhysicsObject& object) // This is to revise the Force into two components Fx and Fy -> it will update in every frame and will give precise output
{
	double rads = (object.GetAngle() * M_PI / 180);
	double ForceX, ForceY;
	ForceX = (cos(rads) * force.x) - (sin(rads) * force.y);
	ForceY = (sin(rads) * force.x) + (cos(rads) * force.y);
	return Vec3(ForceX, ForceY, 0.0f);
}

void Physics::ApplyTorque(const float torque, PhysicsObject& object)
{
	object.SetAngularAccel(torque / object.GetRotationalInertia());
}

void Physics::ApplyForce(const Vec3 force, PhysicsObject& object)
{
	object.SetAccel(force / object.GetMass());
}

//bool Physics::PlaneShphereCollision(const PhysicsObject& object, const Plane& p)
//{
//	return false;
//}
//
//void Physics::PlaneSphereCollisionResponse(PhysicsObject& object1, const PhysicsObject& object2)
//{
//}
//
//bool Physics::SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2)
//{
//	return false;
//}
//
//void Physics::SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2)
//{
//}

