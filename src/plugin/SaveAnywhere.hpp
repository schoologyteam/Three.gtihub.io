#pragma once
#include "../core/common.h"
#include "../core/Frontend.h"
#include "../entities/Entity.h"
#include "../weapons/WeaponType.h"
#include "../weapons/WeaponInfo.h"
#include "../rw/TxdStore.h"
#include "../peds/Ped.h"
#include "../vehicles/Vehicle.h"
#include "../peds/PlayerPed.h"
#include "../peds/CivilianPed.h"
#include "../core/PlayerInfo.h"
#include "../core/World.h"
#include "../core/Camera.h"
#include "../control/Script.h"
#include "../utils/Utils.h"
#include "../plugin/HotKeys.h"

#include "Windows.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace PLG_SaveAnywhere {

	std::vector<HANDLE> g_threads;

	std::string ToUpper(std::string strToConvert)
	{
		std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), std::toupper); //::toupper
		return strToConvert;
	}
	std::string ToLower(std::string strToConvert)
	{
		std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), std::tolower);
		return strToConvert;
	}


bool IsPlayerOnMission(bool onlyonactive_script = true) // active = buying home !!
{
	bool on_mission = false;
	if (onlyonactive_script) // only active
	{
		if (CTheScripts::IsPlayerOnAMission()) // mission
		{
			for (auto i = CTheScripts::pActiveScripts; i; i = i->next) // 
			{
				//if (i->m_bIsMission && i->m_bIsMissionScript && !i->m_bIsExternal) { on_mission = true; break; }
				if (i->m_bMissionFlag && i->m_bIsMissionScript) { on_mission = true; break; }
				//if (i->m_bIsMission) { return true; }
			}
		}
		//return on_mission;
	}
	//else // fw other names
	//{
	//	// search on list our scripts?
	//	std::string snames[] = { /*"INTRO", "HEALTH",	"WANTED", "RC1", "RC2", "RC3", "RC4", "T4X4_1", "T4X4_2", "T4X4_3", "MAYHEM",
	//		"AMBULAN", "FIRETRU", "COPCAR", "TAXI",*/ "MEAT1", "MEAT2", "MEAT3", "MEAT4", "EIGHT", "LUIGI2", "LUIGI3", "LUIGI4",
	//		"LUIGI5", "JOEY1", "JOEY2", "JOEY3", "JOEY4", "JOEY5", "JOEY6", "TONI1", "TONI2", "TONI3", "TONI4", "TONI5", "FRANK1",
	//		"FRANK2", "FRANK21", "FRANK3", "FRANK4", "DIABLO1", "DIABLO2", "DIABLO3", "DIABLO4", "ASUKA1", "ASUKA2", "ASUKA3",
	//		"ASUKA4", "ASUKA5", "KENJI1", "KENJI2", "KENJI3", "KENJI4", "KENJI5", "RAY1", "RAY2", "RAY3",	"RAY4", "RAY5", "RAY6",
	//		"LOVE1", "LOVE2", "LOVE3", "YARD1", "YARD2", "YARD3", "YARD4", "LOVE4", "LOVE5", "LOVE6", "LOVE7", "ASUSB1", "ASUSB2",
	//		"ASUSB3", "HOOD1", "HOOD2", "HOOD3", "HOOD4", "HOOD5", "CAT1", };

	//	if (CTheScripts::IsPlayerOnAMission()) // mission
	//	{
	//		for (auto i = CTheScripts::pActiveScripts; i; i = i->next)
	//		{
	//			if(i->m_bMissionFlag /* && i->m_bIsMissionScript*/) // ??? m_bIsActive false
	//			{
	//				for (const std::string& name : snames) { if (i->m_abScriptName && std::strcmp(i->m_abScriptName, ToLower(name).c_str()) == 0) { on_mission = true; break; } }
	//				if (on_mission) break;
	//			}
	//		}
	//	}
	//}
	return on_mission;
}


	void PLG_SAEntry()
	{
		while (true)
		{
			Sleep(90);

			CPlayerPed* pPlayer = FindPlayerPed();
		        if((GetAsyncKeyState(HotKeyStore_GetSaveAnywhereHotkey()) & 0x8000)
		        // TODO Splash -> Fade timing
		        && (pPlayer)
		        && ((!TheCamera.m_bFading))
				&& ((!FrontEndMenuManager.m_bMenuActive))
				&& ((!pPlayer->InVehicle()))
		        && ((!IsPlayerOnMission()))

				&& (!FrontEndMenuManager.m_bActivateSaveMenu)
				)
			{
				Sleep(150);
				//std::cout << "PLG_SAEntry() PRESS!" << "\n";
			        FrontEndMenuManager.m_bActivateSaveMenu = true; // 984 COMMAND_ACTIVATE_SAVE_MENU  show_save_screen
			}
		}
	}


	DWORD CALLBACK DebugEntry(LPVOID)
	{
		PLG_SAEntry();
		return TRUE;
	}

	void StartThread()
	{
		HANDLE threadHandle = CreateThread(NULL, 0, DebugEntry, NULL, 0, NULL);
		g_threads.push_back(threadHandle);
	}

	void StopAllThreads()
	{
		for (HANDLE handle : g_threads)
		{
			try {
				TerminateThread(handle, 0);
			    CloseHandle(handle);
		    } catch(...) {}
		}
	}


	void
	PLG_OnStart()
	{
		// if(!gbIsConsoleOpened) { OpenConsole(); }
		// std::cout << "PLG_OnStart()" << "\n";
	}


	void
	PLG_OnInit()
	{
		StartThread();
	}

	void
	PLG_OnDraw()
	{

	}

	void
	PLG_OnShutdown()
    {
		StopAllThreads();
	}

} // NS