#include "phys.h"

phys::velocity phys::velocity::calcVelocity(displacement distance, float time)
{
	vector3D out = distance/time;

	return velocity(out.x, out.y, out.z);
}

phys::velocity phys::velocity::calcVelocityF1(float m1, float m2, velocity v1)
{
	vector3D out = v1 * (m1 - m2);
	out /= (m1 + m2);

	return velocity(out.x, out.y, out.z);
}

phys::velocity phys::velocity::calcVelocityF2(float m1, float m2, velocity v1)
{
	vector3D out = v1 * (2.0f * (m1 - m2));
	out /= (m1 + m2);

	return velocity(out.x, out.y, out.z);
}


phys::acceleration phys::acceleration::calcAcceleration(velocity v, float time)
{
	vector3D out = v/time;

	return acceleration(out.x,out.y,out.z);
}

phys::acceleration phys::acceleration::calcAcceleration(force f, float m)
{
	vector3D out = f/m;

	return acceleration(out.x,out.y,out.z);
}

phys::force phys::force::calcForce(acceleration a, float m)
{
	vector3D out = a * m;

	return force(out.x,out.y,out.z);
}

phys::momentum phys::momentum::calcMomentum(velocity v, float m)
{
	vector3D out = v * m;

	return momentum(out.x,out.y,out.z);
}

phys::energy phys::energy::calcEnergy(force f, displacement d)
{
	vector3D out = f * d;

	return energy(out.x,out.y,out.z);
}

phys::energy phys::energy::calcKineticEnergy(velocity v, float m)
{
	vector3D out = (v * v) * (.5 * m);

	return energy(out.x, out.y, out.z);
}