#pragma once

namespace MATH
{
	void VectorAngles( const Vector& forward, Vector &angles );
	//void VectorAngles( const Vector& forward, QAngle& angles );
	Vector NormalizeAngle( Vector angle );
	Vector ClampAngles( Vector& angle );
	//void NormalizeAngles( QAngle& angles );
	Vector CalcAngle( Vector src, Vector dst );
};