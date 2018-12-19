#include "../Features/Features.h"

namespace MATH
{
	void VectorAngles( const Vector& forward, Vector &angles )
	{
		float tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0)
		{
			yaw = 0;
			if (forward[2] > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = (atan2( forward[1], forward[0] ) * 180 / M_PI);
			if (yaw < 0)
				yaw += 360;

			tmp = sqrt( forward[0] * forward[0] + forward[1] * forward[1] );
			pitch = (atan2( -forward[2], tmp ) * 180 / M_PI);
			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	Vector NormalizeAngle( Vector angle )
	{
		while (angle.x > 89.f)
		{
			angle.x -= 180.f;
		}
		while (angle.x < -89.f)
		{
			angle.x += 180.f;
		}
		if (angle.y > 180)
		{
			angle.y -= (round( angle.y / 360 ) * 360.f);
		}
		else if (angle.y < -180)
		{
			angle.y += (round( angle.y / 360 ) * -360.f);
		}
		if ((angle.z > 50) || (angle.z < 50))
		{
			angle.z = 0;
		}
		return angle;
	}
	
	/*Vector ClampAngles( Vector& angles )
	{
		if (angles.y > 89.0f) angles.y = 89.0f;
		else if (angles.y < -89.0f) angles.y = -89.0f;

		if (angles.x > 180.0f) angles.x = 180.0f;
		else if (angles.x < -180.0f) angles.x = -180.0f;

		angles.z = 0;

		return angles;
	}*/

	/*void NormalizeAngles( QAngle& angles )
	{
		for (auto i = 0; i < 3; i++) {
			while (angles[i] < -180.0f) angles[i] += 360.0f;
			while (angles[i] > 180.0f) angles[i] -= 360.0f;
		}
	}*/

	Vector CalcAngle( Vector src, Vector dst )
	{
		Vector ret;
		MATH::VectorAngles( dst - src, ret );
		return ret;
	}
}