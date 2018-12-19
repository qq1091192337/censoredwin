#pragma once
#include "GUI\GUI.h"
#include <filesystem>

using namespace ui;
namespace fs = std::experimental::filesystem;

class Settings
{
public:
    void Initialize(MenuMain* pMenuObj);

    void SaveSettings(const std::string& strFileName, MenuMain* pMenuObj);
    void LoadSettings(const std::string& strFileName, MenuMain* pMenuObj);

private:
    void UpdateDirectoryContent(const fs::path& fsPath);
    inline fs::path GetFolderPath();

    fs::path                 fsPath{};
    std::vector<std::string> vecFileNames{};

public:
    /* All our settings variables will be here  *
    * The best would be if they'd get          *
    * initialized in the class itself.         */

    bool  bCheatActive = true;
    bool  bMenuOpened  = false;

	//rage aim
	bool  bRageEnabled = false;
	bool  bAimLock = true;
	bool  bAutoShoot = false;
	int   bAimBone = 0;
	float bAimFOV = 90.f;
	bool  bAimRCS = true;

	//rage antiaim
	bool  bAntiAimEnabled = false;

	//visuals
	bool  bVisualsEnabled = false;
	bool  bShowBoxes = true;
	bool  bShowNames = true;
	bool  bShowWeapons = true;
	bool  bShowHealth = true;
	bool  bShowArmor = true;
	bool  bPlayerChams = true;
	int   bChamsType = 0;
	float fChamsColT[3] = { 1.f, 0.f, 0.0f };
	float fChamsColCT[3] = { 0.f, 1.f, 0.f };

	//visuals misc
	bool  bCrosshair = true;
	bool  bShowInfo = true;

	//misc
    bool  bBhopEnabled = true;
	bool  bAutoStrafer = true;
};

extern Settings g_Settings;

