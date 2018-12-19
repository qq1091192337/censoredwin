#pragma once
#include "..\Utils\GlobalVars.h"
#include "..\Settings.h"

template<typename t> t lerp( t a, t b, float percent ) {
	return ((b - a) * percent) + a;
}

class Misc
{
public:
    void OnCreateMove()
    {
        this->pCmd   = g::pCmd;
        this->pLocal = g::pLocalEntity;

        if (g_Settings.bBhopEnabled)
            this->DoBhop();
        // sum future shit
		if (g_Settings.bAutoStrafer)
			this->DoAutoStrafer();

		if (g_Settings.bAimLock)
			this->DoAimLock();

		if (g_Settings.bAimRCS)
			this->DoAimRCS();
    };
private:
    CUserCmd*     pCmd;
    C_BaseEntity* pLocal;

    void DoBhop() const
    {
        if (this->pLocal->GetMoveType() == MoveType_t::MOVETYPE_LADDER)
            return;

        static bool bLastJumped = false;
        static bool bShouldFake = false;

        if (!bLastJumped && bShouldFake)
        {
            bShouldFake = false;
            pCmd->buttons |= IN_JUMP;
        }
        else if (pCmd->buttons & IN_JUMP)
        {
            if (pLocal->GetFlags() & FL_ONGROUND)
                bShouldFake = bLastJumped = true;
            else 
            {
                pCmd->buttons &= ~IN_JUMP;
                bLastJumped = false;
            }
        }
        else
            bShouldFake = bLastJumped = false;
    }

	void DoAutoStrafer() const
	{
		//to do
	}

	void DoAimLock() const
	{
		//float best_magnitude = 99999999999999;
		float best_fov = g_Settings.bAimFOV; //99999999999999;
		Vector view_angles;
		Vector engine_angles;

		for (int it = 1; it <= g_pEngine->GetMaxClients(); ++it)
		{
			C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity( it );

			if (!pPlayerEntity || pPlayerEntity->IsDormant() || !pPlayerEntity->IsAlive() || pPlayerEntity == pLocal || pPlayerEntity->GetTeam() == pLocal->GetTeam() || !GetAsyncKeyState( VK_MENU ) )
				continue;

			//float magnitude = (pLocal->GetOrigin() - pPlayerEntity->GetOrigin()).Length2D();

			g_pEngine->GetViewAngles( engine_angles );

			Vector angles;

			//close ur eyez
			switch (g_Settings.bAimBone)
			{
			case 0: angles = MATH::NormalizeAngle( MATH::CalcAngle( pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition( 8 ) ) ); break;
			case 1: angles = MATH::NormalizeAngle( MATH::CalcAngle( pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition( 6 ) ) ); break;
			case 2: angles = MATH::NormalizeAngle( MATH::CalcAngle( pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition( 8 ) ) ); break; //ha best hitscan ever, always hit head
			}

			//angles = MATH::NormalizeAngle( MATH::CalcAngle( pLocal->GetEyePosition(), pPlayerEntity->GetBonePosition(8) ) );

			float fov = (engine_angles - angles).Length2D();

			/*if (magnitude < best_magnitude) 
			{
				best_magnitude = magnitude;
				view_angles = angles;
			}*/

			if (fov < best_fov)
			{
				best_fov = fov;
				view_angles = angles;
			}
		}

		/*if (best_magnitude != 99999999999999)
		{
			g_pEngine->SetViewAngles( view_angles );
		}*/
		
		if (best_fov != g_Settings.bAimFOV)
		{
			g_pEngine->SetViewAngles( view_angles );

			//if (g_Settings.bAutoShoot)
			//{
			//	pCmd->buttons |= IN_ATTACK; //meme
			//}
		}
	}

	void DoAimRCS() const
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			Vector recoil = pLocal->GetPunchAngles();
			pCmd->viewangles -= recoil * 2.f;
		}
	}
};

extern Misc g_Misc;
