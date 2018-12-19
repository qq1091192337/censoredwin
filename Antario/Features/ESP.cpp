#include "ESP.h"
#include "..\Utils\Utils.h"
#include "..\SDK\IVEngineClient.h"
#include "..\SDK\PlayerInfo.h"
#include "../SDK/CGlobalVarsBase.h"

ESP g_ESP;

void ESP::RenderBox(C_BaseEntity* pEnt)
{
    Vector vecScreenOrigin, vecOrigin = pEnt->GetRenderOrigin();
    if (!Utils::WorldToScreen(vecOrigin, vecScreenOrigin))
        return;

    Vector vecScreenBottom, vecBottom = vecOrigin;
    vecBottom.z += (pEnt->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
    if (!Utils::WorldToScreen(vecBottom, vecScreenBottom))
        return;

    const auto sx = int(std::roundf(vecScreenOrigin.x)),
               sy = int(std::roundf(vecScreenOrigin.y)),
               h  = int(std::roundf(vecScreenBottom.y - vecScreenOrigin.y)),
               w  = int(std::roundf(h * 0.25f));

    /* Draw rect around the entity */
    g_Render.Rect(sx - w, sy, sx + w, sy + h, (pEnt->GetTeam() == localTeam) ? teamColor : enemyColor);

    /* Draw rect outline */
    g_Render.Rect(sx - w - 1, sy - 1, sx + w + 1, sy + h + 1, Color( 0, 0, 0, 155 ) );
    g_Render.Rect(sx - w + 1, sy + 1, sx + w - 1, sy + h - 1, Color( 0, 0, 0, 155 ) );
}

void ESP::RenderName(C_BaseEntity* pEnt, int iterator)
{
    Vector vecScreenOrigin, vecOrigin = pEnt->GetRenderOrigin();
    if (!Utils::WorldToScreen(vecOrigin, vecScreenOrigin))
        return;

    Vector vecScreenBottom, vecBottom = vecOrigin;
    vecBottom.z += (pEnt->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
    if (!Utils::WorldToScreen(vecBottom, vecScreenBottom))
        return;

    PlayerInfo_t pInfo;
    g_pEngine->GetPlayerInfo(iterator, &pInfo);

    int sx = std::roundf(vecScreenOrigin.x);
    int sy = std::roundf(vecScreenOrigin.y);
    int h = std::roundf(vecScreenBottom.y - vecScreenOrigin.y);

    g_Render.String(sx, sy + h - 5, CD3DFONT_CENTERED_Y | CD3DFONT_CENTERED_X | CD3DFONT_DROPSHADOW,
                    (localTeam == pEnt->GetTeam()) ? teamColor : enemyColor,
                    g_Fonts.pFontTahoma8.get(), pInfo.szName);
}

void ESP::RenderWeaponName(C_BaseEntity* pEnt)
{
    Vector vecScreenPos;
    if (!Utils::WorldToScreen(pEnt->GetRenderOrigin(), vecScreenPos))
        return;

    auto weapon = pEnt->GetActiveWeapon();

    if (!weapon)
        return;

    auto strWeaponName = weapon->GetName();

    strWeaponName.erase(0, 7);
    std::transform(strWeaponName.begin(), strWeaponName.end(), strWeaponName.begin(), ::toupper);

    g_Render.String(vecScreenPos.x, vecScreenPos.y + 7, CD3DFONT_CENTERED_Y | CD3DFONT_CENTERED_X | CD3DFONT_DROPSHADOW,
                    (localTeam == pEnt->GetTeam()) ? teamColor : enemyColor,
                    g_Fonts.pFontTahoma8.get(), strWeaponName.c_str());
}

void ESP::RenderHealth( C_BaseEntity* pEnt )
{
	Vector vecScreenOrigin, vecOrigin = pEnt->GetRenderOrigin();
	if (!Utils::WorldToScreen( vecOrigin, vecScreenOrigin ))
		return;

	Vector vecScreenBottom, vecBottom = vecOrigin;
	vecBottom.z += (pEnt->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
	if (!Utils::WorldToScreen( vecBottom, vecScreenBottom ))
		return;

	const auto sx = int( std::roundf( vecScreenOrigin.x ) ),
			   sy = int( std::roundf( vecScreenOrigin.y ) ),
	           h = int( std::roundf( vecScreenBottom.y - vecScreenOrigin.y ) ),
			   w = int( std::roundf( h * 0.25f ) );

	int enemyHp = pEnt->GetHealth(),
		hpRed = 255 - (enemyHp * 2.55),
		hpGreen = enemyHp * 2.55;

	UINT hp = h - (UINT)((h * enemyHp) / 100);

	/* Draw rect outline */
	g_Render.Rect( sx + w - 4, sy + 1, sx + w - 5, sy + h - 1, Color( 0, 0, 0, 155 ) );

	/* Draw rect */
	g_Render.Line( sx + w - 5, sy, sx + w - 5, sy + h - 1 - hp, Color( hpRed, hpGreen, 1, 255 ) );

	std::string s = std::to_string( enemyHp );
	char const *pchar = s.c_str();

	if ( pEnt->GetHealth() < 100 )
	{
		g_Render.String( sx + w - 5, sy + h - hp, CD3DFONT_CENTERED_Y | CD3DFONT_CENTERED_X | CD3DFONT_DROPSHADOW, Color(255, 255, 255, 255), g_Fonts.pFontTahoma8.get(), pchar );
	}
}

void ESP::RenderArmor( C_BaseEntity* pEnt )
{
	Vector vecScreenOrigin, vecOrigin = pEnt->GetRenderOrigin();
	if (!Utils::WorldToScreen( vecOrigin, vecScreenOrigin ))
		return;

	Vector vecScreenBottom, vecBottom = vecOrigin;
	vecBottom.z += (pEnt->GetFlags() & FL_DUCKING) ? 54.f : 72.f;
	if (!Utils::WorldToScreen( vecBottom, vecScreenBottom ))
		return;

	const auto sx = int( std::roundf( vecScreenOrigin.x ) ),
		sy = int( std::roundf( vecScreenOrigin.y ) ),
		h = int( std::roundf( vecScreenBottom.y - vecScreenOrigin.y ) ),
		w = int( std::roundf( h * 0.25f ) );

	g_Render.String( sx - w + 10, sy + h - 2, CD3DFONT_CENTERED_X | CD3DFONT_DROPSHADOW, Color( 255, 255, 255, 255 ), g_Fonts.pFontTahoma8.get(), pEnt->GetArmorName() );
}

void ESP::RenderCrosshair()
{
	g_Render.Line( g_Render.GetScreenCenter().x - 5, g_Render.GetScreenCenter().y, g_Render.GetScreenCenter().x + 5, g_Render.GetScreenCenter().y, Color( 255, 0, 0, 255 ) );
	g_Render.Line( g_Render.GetScreenCenter().x, g_Render.GetScreenCenter().y - 5, g_Render.GetScreenCenter().x, g_Render.GetScreenCenter().y + 5, Color( 255, 0, 0, 255 ) );
}

void ESP::RenderInfo()
{
	auto nci = g_pEngine->GetNetChannelInfo();
	std::string ping = std::to_string( (int)(nci->GetAvgLatency( FLOW_INCOMING ) + nci->GetAvgLatency( FLOW_OUTGOING ) * 1000) ) + " ms";
	g_Render.String( 8, 15, CD3DFONT_DROPSHADOW, Color( 250, 150, 200, 180 ), g_Fonts.pFontTahoma8.get(), ("PING: " + ping).c_str() );

	std::string fps = std::to_string( static_cast<int>( 1.f / g_pGlobalVars->frametime ) );
	g_Render.String( 8, 22, CD3DFONT_DROPSHADOW, Color( 250, 150, 200, 180 ), g_Fonts.pFontTahoma8.get(), ("FPS: " + fps).c_str() );
}

void ESP::Render()
{
    if (!g::pLocalEntity || !g_pEngine->IsInGame())
        return;

    localTeam = g::pLocalEntity->GetTeam();

	if (g_Settings.bCrosshair)
		this->RenderCrosshair();

	if (g_Settings.bShowInfo)
		this->RenderInfo();

    for (int it = 1; it <= g_pEngine->GetMaxClients(); ++it)
    {

        C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(it);

        if (!pPlayerEntity
            || !pPlayerEntity->IsAlive()
            || pPlayerEntity->IsDormant()
            || pPlayerEntity == g::pLocalEntity
			|| pPlayerEntity->GetTeam() == g::pLocalEntity->GetTeam())
            continue;

        if (g_Settings.bShowBoxes)
            this->RenderBox(pPlayerEntity);

        if (g_Settings.bShowNames)
            this->RenderName(pPlayerEntity, it);

        if (g_Settings.bShowWeapons)
            this->RenderWeaponName(pPlayerEntity);

		if (g_Settings.bShowHealth)
			this->RenderHealth( pPlayerEntity );

		if (g_Settings.bShowHealth)
			this->RenderArmor( pPlayerEntity );
    }
}
