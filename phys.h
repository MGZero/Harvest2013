#ifndef PHYS_H
#define PHYS_H

#include "Vector2D.h"
#include "Vector3D.h"

namespace phys
{
	//forward declerations
	class velocity;
	class displacement;
	class acceleration;
	class force;
	class momentum;
	class energy;

	
	const float G = 6.67f * pow(10.0,-11.0);
	const float K = 8.987551787f * pow(10.0,9.0);

	class velocity : public vector3D
	{
	public:
		velocity(){}
		velocity(float x, float y, float z) : vector3D(x,y,z){}

		static velocity calcVelocity(displacement distance, float time);
		static velocity calcVelocityF1(float m1, float m2, velocity v1); //conservation of momentum after collision
		static velocity calcVelocityF2(float m1, float m2, velocity v1); //conservation of momentum after collision, V2f
	};

	class acceleration : public vector3D
	{
	public:
		acceleration(){}
		acceleration(float x, float y, float z) : vector3D(x,y,z){}

		static acceleration calcAcceleration(velocity v, float time);
		static acceleration calcAcceleration(force f, float m);

	};

	const acceleration gravity = acceleration(0, 9.81, 0);

	class force : public vector3D
	{
	public:
		force(){}
		force(float x, float y, float z) : vector3D(x,y,z){}

		static force calcForce(acceleration a, float m);
	};

	class momentum : public vector3D
	{
	public:
		momentum(){}
		momentum(float x, float y, float z) : vector3D(x, y, z) {}

		static momentum calcMomentum(velocity v, float m);
	};

	class displacement : public vector3D
	{
	public:
		displacement(){}
		displacement(float x, float y, float z) : vector3D(x,y,z){}
	};

	class energy : public vector3D
	{
	public:
		energy(){}
		energy(float x, float y, float z) : vector3D(x,y,z){}

		static energy calcEnergy(force f, displacement d);
		static energy calcKineticEnergy(velocity v, float m);
	};


};

#endif