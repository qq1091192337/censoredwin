#include "GUI\GUI.h"
#include "Settings.h"


void Detach() { g_Settings.bCheatActive = false; }


void MenuMain::Initialize()
{
    /* Create our main window (Could have multiple if you'd create vec. for it) */
    auto mainWindow = std::make_shared<Window>("", SSize(800, 575), g_Fonts.pFontTahoma8, g_Fonts.pFontTahoma10);
    {
        ///TODO: window->AddTab()
        auto tab1 = std::make_shared<Tab>("rage", 2, mainWindow);
        {
            /* Create sections for it */
            auto sectMain = tab1->AddSection("aim", 1.f);
            {
                /* Add controls within section */
                //sectMain->AddCheckBox("rage enabled", &g_Settings.bRageEnabled );
				sectMain->AddCheckBox( "aimlock enabled", &g_Settings.bAimLock );
				sectMain->AddCheckBox( "autoshoot enabled", &g_Settings.bAimLock );
				sectMain->AddCombo( "aimlock bone", &g_Settings.bAimBone, std::vector<std::string>{ "head", "body", "hitscan" } );
				sectMain->AddSlider( "aimlock fov", &g_Settings.bAimFOV, 0, 360 );
				sectMain->AddCheckBox( "aimRCS enabled", &g_Settings.bAimRCS );
                //sectMain->AddCombo("TestCombo", std::vector<std::string>{ "Value1", "Value2", "Value3" }, &testint);
            }

            auto sectMain2 = tab1->AddSection("antiaim", 1.f);
            {
                //sectMain2->AddCombo("TestCombo2", std::vector<std::string>{ "ttest", "ttest2", "ttest3" }, &testint2);
                //sectMain2->AddCheckBox("antiaim enabled", &g_Settings.bAntiAimEnabled );
            }
        } mainWindow->AddChild(tab1);   /* For now */

        auto tab2 = std::make_shared<Tab>("visuals", 2, mainWindow);
        {
			/* Create sections for it */
			auto sectMain = tab2->AddSection( "TestSect", 1.f );
			{
				/* Add controls within section */
				//sectMain->AddCheckBox( "visuals enabled", &g_Settings.bRageEnabled );
				sectMain->AddCheckBox( "show player names", &g_Settings.bShowNames );
				sectMain->AddCheckBox( "show player boxes", &g_Settings.bShowBoxes );
				sectMain->AddCheckBox( "show player health", &g_Settings.bShowHealth );
				sectMain->AddCheckBox( "show player weapons", &g_Settings.bShowWeapons );
				sectMain->AddCheckBox( "show player armor", &g_Settings.bShowArmor );
				sectMain->AddCheckBox( "show player chams", &g_Settings.bPlayerChams );
				sectMain->AddCombo( "chams type", &g_Settings.bChamsType, std::vector<std::string>{ "flat", "platinum", "glass", "crystal", "gold", "dark chrome", "plastic/glass", "wildfire gold", "crystal blue" } );
			}

			auto sectMain2 = tab2->AddSection( "TestSect2", 1.f );
			{
				sectMain2->AddCheckBox( "show crosshair", &g_Settings.bCrosshair );
				sectMain2->AddCheckBox( "show info", &g_Settings.bShowInfo );
			}
        } mainWindow->AddChild(tab2);

		auto tab3 = std::make_shared<Tab>( "misc", 2, mainWindow );
		{
			/* Create sections for it */
			auto sectMain = tab3->AddSection( "TestSect", 1.f );
			{
				/* Add controls within section */
				sectMain->AddCheckBox( "bunnyhop enabled", &g_Settings.bBhopEnabled );
				//sectMain->AddCheckBox( "autostrafer enabled", &g_Settings.bAutoStrafer );
			}

			auto sectMain2 = tab3->AddSection( "TestSect2", 1.f );
			{
				// todo
			}
		} mainWindow->AddChild( tab3 );

		auto tab4 = std::make_shared<Tab>( "other", 2, mainWindow );
		{
			/* Create sections for it */
			auto sectMain = tab4->AddSection( "TestSect", 1.f );
			{
				/* Add controls within section */
				//sectMain->AddSlider( "test slider", &float123, 0, 20 );
				//sectMain->AddSlider( "int slider", &testint3, 0, 10 );
			}

			auto sectMain2 = tab4->AddSection( "TestSect2", 1.f );
			{
				sectMain2->AddButton( "shutdown", Detach );
			}
		} mainWindow->AddChild( tab4 );
    }
    this->vecChildren.push_back(mainWindow);

    /* Create our mouse cursor (one instance only) */
    mouseCursor = std::make_unique<MouseCursor>();

    /* Do the first init run through all of the objects */
    for (auto& it : vecChildren)
        it->Initialize();
}
