#pragma once //BY MAZAHAKA
#ifndef RE_PLUGIN
#define RE_PLUGIN


#include "plugin.h"
#include "../core/common.h"
#include "../core/Frontend.h"
//#include "../utils/Utils.h"


#include "ClearExamplePlugin.hpp"
#include "SaveAnywhere.hpp"
#include "Helper.hpp"

#include "TimecycleDebuger.h"

#include "../utils/ConsoleTools.h"
//#include "Windows.h" // crash game in anim LOL WHAT??
//#include <iostream>

#define LOG_CALLS_


//------------------------------------------------------------------
//HANDLE InitConsole() // with proto
//{
//	AllocConsole();
//
//	//SetConsoleOutputCP(866);
//	setlocale(LC_ALL, "Russian");
//	SetConsoleOutputCP(1251);
//	SetConsoleCP(1251);
//
//
//	freopen("CONIN$", "r", stdin);
//	freopen("CONOUT$", "w", stdout);
//
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
//
//	return hConsole;
//}
//
////void LeaveConsole(HANDLE hConsole = nullptr)
//void LeaveConsole(HANDLE hConsole) // with proto
//{
//	if (hConsole != nullptr) { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); } // Reset to default color
//	FreeConsole();
//}




//--------------START-----------------
void PLG_Start()
{
#ifdef LOG_CALLS
	debug("PLG_Start();\n");
#endif
	//if(!gbIsConsoleOpened) { OpenConsole(); }
	//InNOUSEitConsole(); // green ------ crash LOL BLYAT!!!!!!!!!!!!!
	PLG_ClearExamplePlugin::PLG_OnStart();
	PLG_HelperPlugin::PLG_OnStart();
	PLG_SaveAnywhere::PLG_OnStart();
}

void PLG_Shutdown()
{
#ifdef LOG_CALLS
	debug("PLG_Shutdown();\n");
#endif
	PLG_ClearExamplePlugin::PLG_OnShutdown();
	PLG_HelperPlugin::PLG_OnShutdown();
	PLG_SaveAnywhere::PLG_OnShutdown();
}


//-------------INIT------------------
void PLG_OnInit_Before()
{
#ifdef LOG_CALLS
	debug("PLG_OnInit_Before();\n");
#endif

}
void PLG_OnInit_After()
{
#ifdef LOG_CALLS
	debug("PLG_OnInit_After();\n");
#endif
	PLG_ClearExamplePlugin::PLG_OnInit();
	PLG_HelperPlugin::PLG_OnInit();
	PLG_SaveAnywhere::PLG_OnInit();
}


//---------------INIT2-TEST-------------
void PLG_InitialiseOnceAfterRW_Before()
{
#ifdef LOG_CALLS
	debug("PLG_InitialiseOnceAfterRW_Before();\n");
#endif

}

void PLG_InitialiseOnceAfterRW_After()
{
#ifdef LOG_CALLS
	debug("PLG_InitialiseOnceAfterRW_After();\n");
#endif

}




//--------------RESTART-----------------
void PLG_OnRestart_Before()
{
#ifdef LOG_CALLS
	debug("PLG_OnRestart_Before();\n");
#endif

}

void PLG_OnRestart_After()
{
#ifdef LOG_CALLS
	debug("PLG_OnRestart_After();\n");
#endif

}



//-------------TICK------------------
void PLG_OnDraw_Before()
{
	//if(!FindPlayerPed()) { return; }
	if (FrontEndMenuManager.m_bMenuActive) { return; } // custom
#ifdef LOG_CALLS
	debug("PLG_OnDraw_Before();\n");
#endif
	//PLG_AddonParticles::PLG_AP_OnTick();
	//PLG_LiveRadioPlugin::PLG_OnDraw();
	//PLG_LiveRadioPlugin::PLG_OnDraw();
}

void PLG_OnDraw_After()
{
	//if(!FindPlayerPed()) { return; } // need?
	if (FrontEndMenuManager.m_bMenuActive) { return; } // custom
#ifdef LOG_CALLS
	debug("PLG_OnDraw_After();\n");
#endif
	PLG_ClearExamplePlugin::PLG_OnDraw();
	PLG_HelperPlugin::PLG_OnDraw();
	PLG_SaveAnywhere::PLG_OnDraw();

	PLG_TD::PLG_OnDraw();
}


#endif