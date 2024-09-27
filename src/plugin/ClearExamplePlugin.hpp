// MIT лицензия By MaZaHaKa
#pragma once
#include "../core/Camera.h"
#include "../core/Clock.h"
#include "../core/FileLoader.h"
#include "../core/FileMgr.h"
#include "../core/Frontend.h"
#include "../core/Pad.h"
#include "../core/World.h"
#include "../core/common.h"
#include "../entities/Entity.h"
#include "../extras/custompipes.h"
#include "../peds/CivilianPed.h"
#include "../peds/Ped.h"
#include "../peds/PlayerPed.h"
#include "../core/PlayerInfo.h"
#include "../renderer/Font.h"
#include "../audio/DMAudio.h"
#include "../audio/MusicManager.h"
#include "../audio/AudioManager.h"
#include "../audio/sampman.h"
#include "../rw/TxdStore.h"
#include "../utils/Utils.h"
#include "../vehicles/Vehicle.h"
#include "../vehicles/CarGen.h"
#include "../weapons/WeaponInfo.h"

//#include "../utils/Utils.h"
#include "../utils/ConsoleTools.h"

#include "Windows.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>

namespace PLG_ClearExamplePlugin
{

//std::vector<HANDLE> g_threads;

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
PLG_OnDraw()
{

}

void
PLG_OnShutdown()
{
}

} // namespace PLG_ClearExamplePlugin