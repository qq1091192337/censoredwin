#pragma once
#include "..\Utils\DrawManager.h"
#include "..\Utils\GlobalVars.h"
#include "..\Settings.h"


class ESP
{
public:
    void Render();
private:
    void RenderBox(C_BaseEntity* pEnt);
    void RenderName(C_BaseEntity* pEnt, int iterator);
    void RenderWeaponName(C_BaseEntity* pEnt);
	void RenderHealth( C_BaseEntity* pEnt );
	void RenderArmor( C_BaseEntity* pEnt );
	void RenderCrosshair();
	void RenderInfo();

    int localTeam{};
    Color teamColor{ 195, 240, 100, 255 };
    Color enemyColor{ 255, 255, 255, 255 };
};
extern ESP g_ESP;