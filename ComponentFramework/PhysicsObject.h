#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "Vector.h"
#include "Sphere.h"
#include "Actor.h"

using namespace MATH;

class PhysicsObject : public Actor // inherited from Actor class
{
	friend class Physics; // shares the private variables with Physics class


private:
		Vec3 pos, vel, accel;
		float mass;
		float torque, rotationalInertia;
		float angle, angularVel, angularAccel;

public:

		PhysicsObject();
		PhysicsObject(float mass_, float rotationalInertia);
		virtual ~PhysicsObject();

		inline void Update(const float deltaTime);
		
		//csv print function
		void csv(float time, float torque);
	
		
		inline void SetPos(const Vec3 &pos_) { pos = pos_; }
		inline Vec3 GetPos() { return pos; }
		inline void SetMass(const float &mass_) { mass = mass_; }
		inline float GetMass() { return mass; }
		inline void SetRotationalInertia(const float& rotationalInertia_) { rotationalInertia = rotationalInertia_; }
		inline float GetRotationalInertia() { return rotationalInertia; }
		 
		inline void SetVel(const Vec3 &vel_) { vel = vel_; }
		inline Vec3 GetVel() { return vel; }
		inline void SetAccel(const Vec3& accel_) { accel = accel_; }
		inline Vec3 GetAccel() { return accel; }

		inline void SetAngle(const float& angle_) { angle = angle_; }
		inline float GetAngle() { return angle; };
		inline void SetAngularVel(const float &angularVel_) { angularVel = angularVel_; }
		inline float GetAngularVel() { return angularVel; }
		inline void SetAngularAccel(const float& angularAccel_) { angularAccel = angularAccel_; }
		inline float GetAngularAccel() { return angularAccel; }

		inline 
		inline Vec3 GetForce() { return mass * accel; }
		

};


#endif // !PHYSICSOBJECT_H