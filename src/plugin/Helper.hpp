// MIT лицензи€ By MaZaHaKa
#pragma once
#include "../audio/AudioManager.h"
#include "../audio/DMAudio.h"
#include "../audio/MusicManager.h"
#include "../audio/sampman.h"
#include "../core/Camera.h"
#include "../core/Clock.h"
#include "../core/FileLoader.h"
#include "../core/FileMgr.h"
#include "../core/Frontend.h"
#include "../core/Pad.h"
#include "../core/PlayerInfo.h"
#include "../core/Stats.h"
#include "../core/World.h"
#include "../core/common.h"
#include "../entities/Entity.h"
#include "../extras/custompipes.h"
#include "../peds/CivilianPed.h"
#include "../peds/Ped.h"
#include "../peds/PlayerPed.h"
#include "../renderer/Font.h"
#include "../renderer/Timecycle.h"
#include "../rw/TxdStore.h"
#include "../utils/Utils.h"
#include "../vehicles/CarGen.h"
#include "../control/Script.h"
#include "../vehicles/Vehicle.h"
#include "../weapons/WeaponInfo.h"

//#include "../utils/Utils.h"
#include "../utils/ConsoleTools.h"

#include "Windows.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace PLG_HelperPlugin
{

// std::vector<HANDLE> g_threads;

void
PLG_OnStart()
{
	// if(!gbIsConsoleOpened) { OpenConsole(); }
	// std::cout << "PLG_OnStart()" << "\n";
}

void
PLG_OnInit()
{
}

void
DecryptCheatString(char *encryptedStr, char *decryptedStr)
{
#define decmp(n) decryptedStr[i] = encryptedStr[i] - n;
	int i = 0;
	while(encryptedStr[i]) {
		switch(i) {
		case 0: decmp(3); break;
		case 1: decmp(5); break;
		case 2: decmp(7); break;
		case 3: decmp(1); break;
		case 4: decmp(13); break;
		case 5: decmp(27); break;
		case 6: decmp(3); break;
		case 7: decmp(7); break;
		case 8: decmp(1); break;
		case 9: decmp(11); break;
		case 10: decmp(13); break;
		case 11: decmp(8); break;
		case 12: decmp(7); break;
		case 13: decmp(32); break;
		case 14: decmp(13); break;
		case 15: decmp(6); break;
		case 16: decmp(28); break;
		case 17: decmp(19); break;
		case 18: decmp(10); break;
		case 19: decmp(3); break;
		case 20: decmp(3); break;
		case 21: decmp(5); break;
		case 22: decmp(7); break;
		case 23: decmp(1); break;
		case 24: decmp(13); break;
		case 25: decmp(27); break;
		case 26: decmp(3); break;
		case 27: decmp(7); break;
		default: return;
		}
		i++;
	}
#undef decmp
}



void
ProcessMaterialsFromClump(RpClump *clump)
{
	// ѕредположим, что RpClump имеет список атомиков (например, linked list)
	// заменим _list на поле из структуры, в котором хран€тс€ атомики.
	if(!clump) { return; }
	FORLIST(lnk, clump->atomics)
	{
		RpAtomic *atomic = (RpAtomic *)lnk; // ѕолучаем атомик из текущей ссылки
		if(!atomic) { continue; }
		RpGeometry *geometry = RpAtomicGetGeometry(atomic);
		if(geometry) {
			//int numMaterials = RpGeometryGetNumMaterials(geometry);
			int numMaterials = geometry->matList.numMaterials;
			for(int i = 0; i < numMaterials; ++i) {
				RpMaterial *material = RpGeometryGetMaterial(geometry, i);
				// «десь можно извлекать и использовать данные материала
				printf("Material: %s\n", material->texture->name);
			}
		}
	}
}

__declspec(noinline)
void
dbg()
{
	ProcessMaterialsFromClump(FindPlayerPed()->GetClump());
}



bool once = false;
bool draw = false;
bool hold = false;
int hlp = 0;
bool allow_hold = false;
void
PLG_OnDraw()
{
	// if(!gbIsInitedExternalCargen)
	{
		// once = true;
		// PLG_ExternalCargens::InitExternalCargens(); // twice
	}
	if(draw) {
		// DrawRadioName("L Radio");
		// TestDraw();
	}

	// bool ispress = CPad::GetPad(0)->GetChar(HotKeyStore_GetLiveRadioHotkey());
	bool ispress = (GetAsyncKeyState('R') & 0x8000);
	if(ispress && ((!hold && !allow_hold) || (allow_hold))) {
		// DrawRadioName("AHAHAHHA");
		// TestDraw();
		// std::cout << "PrintText" << "\n";
		if(!once) {
			/*const char *ffmpeglib = "bass\\x64\\bass.dll";
			HMODULE hBass = GetModuleHandleA(ffmpeglib);
			if(!hBass) { hBass = LoadLibraryA(ffmpeglib); }
			std::cout << "Loaded 0x" << hBass << "\n";*/

			// setStation("https://online.kissfm.ua/KissFM_Deep_HD");
			// setStation("C:\\Users\\Zver\\Desktop\\Any Act - Gypsy Man.mp3");
			// setStation("https://air.unmixed.ru/lradio256");
			// setVolume(10);
			draw = true;
			once = true;
			// PLG_ExternalCargens::InitExternalCargens(); // twice
		}
		// std::cout << CTheScripts::pActiveScripts->m_abScriptName << "\n";
		// std::cout << "cnt cargen: " << CTheCarGenerators::NumOfCarGenerators << "\n"; // 209
		// std::cout << "CurrentActiveCount: " << (int)CTheCarGenerators::CurrentActiveCount << "\n"; // 193
		// std::cout << "ProcessCounter: " << (int)CTheCarGenerators::ProcessCounter << "\n";
		// CTheCarGenerators::CurrentActiveCount = 209;
		// DMAudio.ResetTimers(CTimer::GetTimeInMilliseconds() - 5000);

		// TryMuteVehRadio();
		// CPlayerInfo *pPlayer = &CWorld::Players[CWorld::PlayerInFocus];
		// pPlayer->m_nMoney = 0;
		// std::cout << "rand: " << GetRandomNumInclude(0, 5) << "\n";
		// std::cout << "randUn: " << GetRandomNumUnInclude(0, 5) << "\n";

		// std::cout << "m_fMapSize: " << FrontEndMenuManager.m_fMapSize << "\n";
		// std::cout << "m_fMapCenterX: " << FrontEndMenuManager.m_fMapCenterX << "\n";
		// std::cout << "m_fMapCenterY: " << FrontEndMenuManager.m_fMapCenterY << "\n";

		/*wchar *lastMissionPassed;
		lastMissionPassed = TheText.Get(CStats::LastMissionPassedName[0] ? CStats::LastMissionPassedName : "ITBEG");
		char* str = UnicodeToAscii(lastMissionPassed);
		//debug("stats last: %s\n", *CStats::LastMissionPassedName); // vic1
		debug("stats last: %s\n\n", str); // vic1
		std::cout << "\n";*/

		/*char encryptedStr[] = "SZUSb]";
		char decryptedStr[sizeof(encryptedStr)] = {0};
		DecryptCheatString(encryptedStr, decryptedStr);
		std::cout << "Decrypted string: " << decryptedStr << std::endl;*/

		std::string name = CModelInfo::GetModelInfo(FindPlayerPed()->GetModelIndex())->GetModelName();
		std::cout << name << "\n";
		return;
		std::cout << "mission: " << CTheScripts::pActiveScripts[0].m_abScriptName << "\n";
		std::cout << "player in veh: " << FindPlayerPed()->InVehicle() << "\n";
		DumpAllScriptsOffsets();
		dbg();
		//std::cout << &([]() {});

		// ReadDataFromBufferPointer(buf, CTimeCycle::m_ExtraColour);
		// ReadDataFromBufferPointer(buf, CTimeCycle::m_bExtraColourOn);
		// ReadDataFromBufferPointer(buf, CTimeCycle::m_ExtraColourInter);
		////std::cout << "m_ExtraColour: " << (unsigned int)CTimeCycle::m_ExtraColour << "\n";
		////std::cout << "m_bExtraColourOn: " << (unsigned int)CTimeCycle::m_bExtraColourOn << "\n";
		////std::cout << "m_ExtraColourInter: " << (unsigned int)CTimeCycle::m_ExtraColourInter << "\n";

		//std::cout << "pad: " << CPad::GetPad(0)->GetWeapon() << "\n";
		/*CVehicle *pRandVehicle = GetRandomPoolVehicle();
		CPlayerPed *pPlayer = FindPlayerPed();
		if(pRandVehicle && pPlayer) { 
			pPlayer->SetCarJack(pRandVehicle);
		}*/

		hlp = hlp == 0 ? 1 : 0;
		// CTimeCycle::m_bExtraColourOn = CTimeCycle::m_ExtraColourInter = hlp;
		// CTimeCycle::m_ExtraColour = hlp;
		// CTimeCycle::m_bExtraColourOn = hlp; // плавно переключает
		// CTimeCycle::m_ExtraColourInter = hlp;

		//CTimeCycle::m_nCurrentSkyTopRed = 0;
		//CTimeCycle::m_nCurrentSkyTopGreen = 0;
		//CTimeCycle::m_nCurrentSkyTopBlue = 0;
		//test();

		hold = true;
	} else if(!ispress) {
		hold = false;
	}
	// std::cout << "prefs: " << FrontEndMenuManager.m_PrefsLanguage << "\n";
	// DebugVehPipe();
}




void
PLG_OnShutdown()
{
}

} // namespace PLG_HelperPlugin