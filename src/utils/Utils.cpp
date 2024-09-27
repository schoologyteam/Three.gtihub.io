#pragma once
#include "Utils.h"
//#include "../core/config.h"
#include "../core/common.h"
#include "../core/General.h"
#include "../weapons/WeaponType.h"
#include "../weapons/WeaponInfo.h"
#include "../rw/TxdStore.h"
#include "../fakerw/rpworld.h"
#include "../entities/Entity.h"
#include "../peds/Ped.h"
#include "../vehicles/Vehicle.h"
#include "../core/PlayerInfo.h"
#include "../peds/Ped.h"
#include "../peds/PlayerPed.h"
#include "../peds/CivilianPed.h"
#include "../core/Wanted.h"
#include "../control/PathFind.h"
#include "../core/Camera.h"
#include "../control/Replay.h"
#include "../renderer/Hud.h"
#include "../renderer/Font.h"
#include "../text/Text.h"
#include "../core/World.h"
#include "../control/Script.h"
#include "../core/Frontend.h"
#ifdef MAZAHAKA_FIX_BACKGROUND_APP_NO_HOLD_MOUSE
#include "../skel/win/win.h"
#endif

//class CEntity;
//class CPed;
//class CVehicle;
//class CPlayerPed;
//class CCivilianPed;

#include "Windows.h"
#include <iostream>


////------------------------------------------------------------------
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




void Mbox(const char* msg, const char* title)
{
	MessageBoxA(HWND_DESKTOP, msg, title, MB_SYSTEMMODAL | MB_ICONWARNING);
}
//void MboxSTD(const std::string& msg, const std::string& title = "title")
void MboxSTD(std::string msg, std::string title)
{
	MessageBoxA(HWND_DESKTOP, msg.c_str(), title.c_str(), MB_SYSTEMMODAL | MB_ICONWARNING);
}
void EXIT_F()
{
	ExitProcess(EXIT_FAILURE);
}
void EXIT_S()
{
	ExitProcess(EXIT_SUCCESS);
}
void RaiseError(const char* fmt, ...)
{
	char buf[2048];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buf, fmt, args);
	va_end(args);

	MessageBoxA(HWND_DESKTOP, buf, "Fatal Error", MB_SYSTEMMODAL | MB_ICONWARNING);
	ExitProcess(EXIT_FAILURE);
}




void DumpTexturesNames(RpAtomic* pRpAtomic, CEntity* pEntity, bool dump_error)
{
	if (pEntity) { pRpAtomic = pEntity->GetAtomic(); }
	if (!pRpAtomic) { if (dump_error) { std::cout << "!rpAtomic\n"; } return; }
	if (dump_error) { printf("Atomic: 0x%p\n", pRpAtomic); }
	RpGeometry* geo = pRpAtomic->geometry;
	if (!geo) { if (dump_error) { std::cout << "!geo\n"; } return; }
	rw::MaterialList matList = geo->matList;
	//if (!matList) { return; }
	//std::cout << "\n\n";
	for (int i = 0; i < matList.numMaterials; ++i)
	{
		RpMaterial* mat = matList.materials[i];
		if (mat && mat->texture) {
			const char* textureName = mat->texture->name;
			if (dump_error) { printf("%d: %s \t 0x%p\n", i, textureName, mat->texture); }
			else { printf("%d: %s\n", i, textureName); }
		}
		//else { debug("!Material %d .", i); }
	}
	std::cout << "\n\n";
}



int GetModelIndex(CEntity* pEntity) // lol
{
	if (!pEntity) { return -1; }
	return (pEntity->GetModelIndex());
}

std::string GetModelName(CEntity* pEntity)
{
	if (!pEntity) { return ""; }
	//return (CModelInfo::ms_modelInfoPtrs[pEntity->GetModelIndex()]->m_name); // +".txd" ?
	return (CModelInfo::GetModelInfo(pEntity->GetModelIndex())->GetModelName()); // +".txd" ?
}

std::string GetModelTxdSlotName(CEntity* pEntity)
{
	if (!pEntity) { return ""; }
	//return (CTxdStore::GetTxdName(CModelInfo::ms_modelInfoPtrs[pEntity->GetModelIndex()]->GetTxdSlot())); // +".txd" ?
	return (CTxdStore::GetTxdName(CModelInfo::GetModelInfo(pEntity->GetModelIndex())->GetTxdSlot())); // +".txd" ?
}

// crash if entity is ped
void DumpEntityData(CEntity* pEntity, bool clear_console)
{
	if (!pEntity) { std::cout << "!pEntity" << "\n"; return; }
	if(clear_console) { system("cls"); }
	else {std::cout << "\n\n"; }
	std::cout << "MI: " << GetModelIndex(pEntity) << " Entity: 0x" << pEntity << "  Name:  " << GetModelName(pEntity) << "\t TXD: " << GetModelTxdSlotName(pEntity) << "\n";
	std::cout << "\n" << "Tex List" << "\n";
	DumpTexturesNames(nullptr, pEntity, false);
	std::cout << "\n\n";
}


CWeaponInfo* GetPlayerCurrentWeaponInfo()
{
	if (!FindPlayerPed()) { return nullptr; }
	CWeaponInfo* info = CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType);
	return info;
}

int32_t GetPlayerCurrentWeaponType()
{
	//if (!FindPlayerPed()) { return eWeaponType::WEAPONTYPE_UNARMED; }
	if (!FindPlayerPed()) { return eWeaponType::WEAPONTYPE_UNARMED; }
	//int32_t WeaponType = FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nCurrentWeapon].m_eWeaponType;
	return FindPlayerPed()->GetWeapon()->m_eWeaponType;
}


//-----
bool IsWeaponPistol()
{
	if (!FindPlayerPed()) { return false; }
	return (GetPlayerCurrentWeaponType() == WEAPONTYPE_COLT45);
}

bool IsWeaponUziPlayer()
{
	if (!FindPlayerPed()) { return false; }
	return (GetPlayerCurrentWeaponType() == WEAPONTYPE_UZI);
}

/*bool IsWeaponAK47Player()
{
	if (!FindPlayerPed()) { return false; }
	return (GetPlayerCurrentWeaponType() == WEAPONTYPE_AK47);
}

bool IsWeaponM16Player()
{
	if (!FindPlayerPed()) { return false; }
	return (GetPlayerCurrentWeaponType() == WEAPONTYPE_M16);
}*/

bool IsUnArmedPlayer()
{
	if (!FindPlayerPed()) { return false; }
	return (GetPlayerCurrentWeaponType() == WEAPONTYPE_UNARMED);
}
//-----


RpClump* GetPlayerClump()
{
	if(!FindPlayerPed()) { return nullptr; }
	// CWeaponInfo::GetWeaponInfo(FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nCurrentWeapon]
	return (RpClump*)FindPlayerPed()->GetClump();
}

bool IsPlayerDriveVehicle()
{
	if(!FindPlayerPed()) { return false; }
	// return FindPlayerPed()->m_pVehicle != nullptr; // NOT WORK. тачка педа остаёться если он вышел
	return FindPlayerPed()->InVehicle(); // work
}

//	if (!DKSleep(deltaTime.count(), gfMemingTimer, gfTimerBuffer)) { return; } // задержка прокрута
bool DKSleep(float deltaTime, float wait_time, float& sleepBuffer)
{
	sleepBuffer += deltaTime; // Накапливаем время
	// Если накопленное время больше или равно времени ожидания
	if (sleepBuffer >= wait_time) {
		sleepBuffer = 0.0f; // Сбрасываем накопленное время
		return true; // Время ожидания истекло, возвращаем true
	}
	return false; // Время ожидания не истекло, возвращаем false
}


bool
IsWindowActive(HWND hwnd)
{
	HWND activeWindow = GetForegroundWindow();
	return (hwnd == activeWindow);
}

bool
IsWindowMinimized(HWND hwnd)
{
	return IsIconic(hwnd) != 0;
}


/*wchar strW[200];
// char strA[250];
// sprintf(strA, "TTS DAT Reloaded!");
AsciiToUnicode(str, strW);
if(play_beep) { CHud::SetHelpMessage(strW, true); }*/

std::wstring
Utf8ToWide(const std::string &utf8Str)
{
	int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
	wchar_t *wideStr = new wchar_t[wideStrLen];
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wideStr, wideStrLen);
	std::wstring result(wideStr);
	delete[] wideStr;
	return result;
}

//inline
int
GetFrontendAudioPercentVolume(bool bSFX, bool crt_vol)
{ // FrontEndMenuManager MAX VOL 128
#define FRONTEND_AUDIO_MAX 127
  // InitConsole();
	// std::cout << "FrontEndMenuManager.m_nPrefsSfxVolume: " << FrontEndMenuManager.m_nPrefsSfxVolume << "\n";
	// std::cout << "FrontEndMenuManager.m_nPrefsMusicVolume: " << FrontEndMenuManager.m_nPrefsMusicVolume << "\n\n";
	// return 20;
	int res = bSFX ? (FrontEndMenuManager.m_PrefsSfxVolume * 100) / FRONTEND_AUDIO_MAX : (FrontEndMenuManager.m_PrefsMusicVolume * 100) / FRONTEND_AUDIO_MAX;
	// std::cout << "bSFX:" << bSFX << " vol:" << res << "\n";
	return res;
#undef FRONTEND_AUDIO_MAX
}


void
UAsciiToUnicode(const char *src, wchar *dst) // font?cpp
{
	while((*dst++ = (unsigned char)*src++) != '\0')
		;
}


void
UUnicodeToAscii(wchar *src, char *dst)
{
	while((*dst++ = (char)*src++) != '\0')
		;
}

bool
IsPlayerAsPassangerNow()
{
	CPlayerPed *pPlayer = FindPlayerPed();
	if(!pPlayer) { return false; }
	if(pPlayer->InVehicle() && pPlayer->m_pMyVehicle->pDriver != pPlayer) { return true; } // passanger?
	return false;
}

bool
CheckWastedBustedPlayer() // return true if wasted/busted
{
	CPlayerInfo *pPlayerInfo = &CWorld::Players[CWorld::PlayerInFocus];
	if(!pPlayerInfo) { return false; }
	//CPlayerInfo::IsRestartingAfterDeath
	//CPlayerInfo::IsRestartingAfterArres
	return (pPlayerInfo->m_WBState != WBSTATE_PLAYING);
	//return ((pPlayerInfo->m_WBState == WBSTATE_WASTED) || (pPlayerInfo->m_WBState == WBSTATE_BUSTED));
}

bool
IsPlayerPlaying()
{ // CPlayerInfo::MakePlayerSafe(bool toggle)
	CPlayerInfo *pPlayerInfo = &CWorld::Players[CWorld::PlayerInFocus];
	CPlayerPed *pPlayer = FindPlayerPed();

	if(!pPlayerInfo) { return false; }
	if(!pPlayer) { return false; }

	// if (CCutsceneMgr::ms_running) { return false; }
	// if (IsPlayerOnMission()) { return false; } // desp rando wanted
#ifdef MAZAHAKA_FIX_BACKGROUND_APP_NO_HOLD_MOUSE 
	if(!CheckWindowStateIsOpenedMaZaHaKa()) { return false; }
#endif
	if(FrontEndMenuManager.m_bMenuActive) { return false; }
	if(TheCamera.m_bFading) { return false; }
	if(FrontEndMenuManager.m_bGameNotLoaded) { return false; }
	if(CheckWastedBustedPlayer()) { return false; }
	if(FindPlayerVehicle() && (FindPlayerVehicle()->m_vehType == VEHICLE_TYPE_TRAIN)) { return false; }

	//if(pPlayer->InVehicle() && pPlayer->m_pMyVehicle->pDriver != pPlayer) { return false; } // passanger?
	if(IsPlayerAsPassangerNow()) { return false; } // passanger?
	if(CReplay::IsPlayingBack()) { return false; }


	bool defaultgamesafeped =
	    (true
			&& pPlayer->m_pWanted->m_bIgnoredByEveryone
			&& pPlayer->bBulletProof
			&& pPlayer->bFireProof
			&& pPlayer->bCollisionProof
			&& pPlayer->bMeleeProof
			&& pPlayer->bOnlyDamagedByPlayer
			&& pPlayer->bExplosionProof
			&& !(pPlayer->m_bCanBeDamaged));
	if(defaultgamesafeped) { return false; }
	// on true safe
	// m_pPed->bBulletProof = true;
	// m_pPed->bFireProof = true;
	// m_pPed->bCollisionProof = true;
	// m_pPed->bMeleeProof = true;
	// m_pPed->bOnlyDamagedByPlayer = true;
	// m_pPed->bExplosionProof = true;
	// m_pPed->m_bCanBeDamaged = false;
	return true;
}


CVector
Transform3DPoint2NearPathNode(CVector target)
{
	int node = ThePaths.FindNodeClosestToCoors(target, 0, 150.0f, true, true);
	if(node < 0) { return target; }
	CVector output = ThePaths.m_pathNodes[node].GetPosition();
	return output;
}

int
GetRandomNumInclude(int start, int end)
{
	// Добавляем 1 к `end` в выражении, чтобы включить верхнюю границу
	return start + CGeneral::GetRandomNumberInRange(0, end - start + 1);
}

int
GetRandomNumUnInclude(int start, int end)
{
	// Здесь верхняя граница уже исключена, поэтому никакие изменения не требуются
	return start + CGeneral::GetRandomNumberInRange(0, end - start);
}


bool
IsWithinRadius(const CVector &point1, const CVector &point2, float radius) // есть реализация в игре готовая?
{
	CVector diff = point1 - point2;
	float distSquared = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
	float radiusSquared = radius * radius;
	return distSquared <= radiusSquared;
}


void
Message(const char *str, bool play_beep)
{
	/*std::wstring wideStr = Utf8ToWide(str);
#ifdef MAZAHAKA_SILENT_CHUD_MESSAGE
	if(play_beep) { CHud::SetHelpMessage((wchar *)wideStr.c_str(), true); }
	else { CHud::SetHelpMessageNoSound((wchar *)wideStr.c_str(), true); }
#else
	CHud::SetHelpMessage((wchar *)wideStr.c_str(), true);
#endif*/

	wchar strW[200];
	// char strA[250];
	// sprintf(strA, "TTS DAT Reloaded!");
	AsciiToUnicode(str, strW);

#ifdef MAZAHAKA_SILENT_CHUD_MESSAGE
	if(play_beep) {
		CHud::SetHelpMessage(strW, true);
	} else {
		CHud::SetHelpMessageNoSound(strW, true);
	}
#else
	CHud::SetHelpMessage(strW, true);
#endif
}

//__declspec(noinline)
CVehicle *
GetRandomPoolVehicle(bool nodriver, bool all)
{
	CPlayerPed *pPlayer = FindPlayerPed();
	int j = CPools::GetVehiclePool()->GetSize();
	while(j-- > 0) {
		//if(CVehicle *veh = CPools::GetVehiclePool()->GetSlot(j)) veh->BlowUpCar(nil);
		CVehicle *veh = CPools::GetVehiclePool()->GetSlot(j);
		if(!veh) {continue; }
		if(pPlayer && pPlayer->InVehicle() && pPlayer->m_pMyVehicle == veh) { continue; }
		if(all) { if(veh->IsCar()) { return veh; }  }
		else {
			if(nodriver && (!veh->pDriver) && veh->IsCar()) { return veh; }
			else if(!nodriver && veh->pDriver && veh->IsCar()) { return veh; }
		}

	}

	/*while(1)
	{
		int i = _RandVUKL(0, CPools::GetVehiclePool()->GetSize());
		CVehicle *veh = CPools::GetVehiclePool()->GetSlot(i);
		if(veh && veh->IsCar()) { return veh; }
		Sleep(0);
	}*/
	return nil;
}

CVehicle*
GetVehicleNearPlayer()
{
	//CVehicle *veh = nil;
	CPlayerPed *pPlayer = FindPlayerPed();
	CPlayerInfo *pPlayerInfo = &CWorld::Players[CWorld::PlayerInFocus];
	if(!pPlayer || !pPlayerInfo) { return false; }
	//veh = pPlayer->m_pMyVehicle; // tmp dummy

	bool weAreOnBoat = false;
	float lastCloseness = 0.0f;
	CVehicle *carBelow = nil;
	CEntity *surfaceBelow = pPlayer->m_pCurrentPhysSurface;
	if(surfaceBelow && surfaceBelow->IsVehicle()) {
		carBelow = (CVehicle *)surfaceBelow;
		if(carBelow->IsBoat()) {
			weAreOnBoat = true;
			pPlayer->bOnBoat = true;
#ifdef VC_PED_PORTS
			if(carBelow->GetStatus() != STATUS_WRECKED && carBelow->GetUp().z > 0.3f)
#else
			if(carBelow->GetStatus() != STATUS_WRECKED)
#endif
				pPlayer->SetSeekBoatPosition(carBelow);
		}
	}
	// Find closest car
	if(!weAreOnBoat) {
		float minX = pPlayer->GetPosition().x - 10.0f;
		float maxX = 10.0f + pPlayer->GetPosition().x;
		float minY = pPlayer->GetPosition().y - 10.0f;
		float maxY = 10.0f + pPlayer->GetPosition().y;

		int minXSector = CWorld::GetSectorIndexX(minX);
		if(minXSector < 0) minXSector = 0;
		int minYSector = CWorld::GetSectorIndexY(minY);
		if(minYSector < 0) minYSector = 0;
		int maxXSector = CWorld::GetSectorIndexX(maxX);
		if(maxXSector > NUMSECTORS_X - 1) maxXSector = NUMSECTORS_X - 1;
		int maxYSector = CWorld::GetSectorIndexY(maxY);
		if(maxYSector > NUMSECTORS_Y - 1) maxYSector = NUMSECTORS_Y - 1;

		CWorld::AdvanceCurrentScanCode();

		for(int curY = minYSector; curY <= maxYSector; curY++) {
			for(int curX = minXSector; curX <= maxXSector; curX++) {
				CSector *sector = CWorld::GetSector(curX, curY);
				pPlayerInfo->FindClosestCarSectorList(sector->m_lists[ENTITYLIST_VEHICLES], pPlayer, minX, minY, maxX, maxY, &lastCloseness,
				                                      &carBelow);
				pPlayerInfo->CPlayerInfo::FindClosestCarSectorList(sector->m_lists[ENTITYLIST_VEHICLES_OVERLAP], pPlayer, minX, minY, maxX,
				                                                   maxY, &lastCloseness, &carBelow);
			}
		}
	}


	return carBelow;
}

void
DumpAllScriptsOffsets()
{
	// re3.cpp (no have re3.h)
	static const char* missions[] = {
	"initial: objects", "initial: hidden packages", "initial: car generators", "initial: pickups", "initial: unique stunt jumps",
	"initial: player", "initial: general info", "initial: lods", "initial: weapons", "Home Sweet Home", "Taxi-Driver Sub-Mission",
	"Paramedic Sub-Mission", "Vigilante Sub-Mission", "Karmageddon", "Firefighter Sub-Mission", "Trash Dash", "RC Triad Take-Down",
	"Thrashin' RC", "Ragin' RC", "Chasin' RC", "GO GO Faggio", "Noodleboy", "Pizzaboy", "Wong Side Of The Tracks", "Bumps and Grinds: Course 1",
	"Bumps and Grinds: Course 2", "Bumps and Grinds: Course 3", "Bumps and Grinds: Course 4", "Bumps and Grinds: Course 5", "Bumps and Grinds: Course 6",
	"Bumps and Grinds: Course 7", "Bumps and Grinds: Course 8", "Bumps and Grinds: Course 9", "Bumps and Grinds: Course 10", "Car Salesman", "Bike Salesman",
	"RACE: Low-Rider Rumble", "RACE: Deimos Dash", "RACE: Wi-Cheetah Run", "RACE: Red Light Racing", "RACE: Torrington TT", "RACE: Gangsta GP",
	"Scooter Shooter", "AWOL Angel", "9mm Mayhem", "Scrapyard Challenge", "See the Sight Before your Flight", "SlashTV", "Slacker (Vincenzo)",
	"Dealing Revenge (Vincenzo)", "Snuff (Vincenzo)", "Smash and Grab (Vincenzo)", "Hot Wheels (Vincenzo)", "The Portland Chainsaw Masquerade (Vincenzo)",
	"The Offer (Salvatore)", "Ho Selecta! (Salvatore)", "Frighteners (Salvatore)", "Rollercoaster Ride (Salvatore)", "Contra-Banned (Salvatore)",
	"Sindacco Sabotage (Salvatore)", "The Trouble with Triads (Salvatore)", "Driving Mr Leone (Salvatore)", "conversation (JD)", "Bone Voyeur! (JD)",
	"Don in 60 Seconds (JD)", "A Volatile Situation (JD)", "Blow up 'Dolls' (JD)", "Salvatore's Salvation (JD)", "The Guns of Leone (JD)",
	"Calm before the Storm (JD)", "The Made Man (JD)", "Snappy Dresser (Ma Cipriani)", "Big Rumble in Little China (Ma Cipriani)", "Grease Sucho (Ma Cipriani)",
	"Dead Meat (Ma Cipriani)", "No Son of Mine (Ma Cipriani)", "Shop 'til you Strop (Maria)", "Taken for a Ride (Maria)", "Booby Prize (Maria)",
	"Biker Heat (Maria)", "Overdose of Trouble (Maria)", "Making Toni (Salvatore)", "A Walk In The Park (Salvatore)", "Caught In The Act (Salvatore)",
	"Search And Rescue (Salvatore)", "Taking The Peace (Salvatore)", "Shoot The Messenger (Salvatore)", "Sayonara Sindaccos (Leon McAffrey)",
	"The Whole 9 Yardies (Leon McAffrey)", "Crazy '69' (Leon McAffrey)", "Night Of The Livid Dreads (Leon McAffrey)", "Munitions Dump (Leon McAffrey)",
	"The Morgue Party Candidate (Donald Love)", "Steering The Vote (Donald Love)", "Cam-Pain (Donald Love)", "Friggin' The Riggin' (Donald Love)",
	"Love & Bullets (Donald Love)", "Counterfeit Count (Donald Love)", "Love On The Rocks (Donald Love)", "L.C. Confidential (Church Confessional)",
	"The Passion Of The Heist (Church Confessional)", "Karmageddon (Church Confessional)", "False Idols (Church Confessional)", "Rough Justice (Salvatore)",
	"Dead Reckoning (Salvatore)", "Shogun Showdown (Salvatore)", "The Shoreside Redemption (Salvatore)", "The Sicilian Gambit (Salvatore)",
	"Panlantic Land Grab (Donald Love)", "Stop the Press (Donald Love)", "Morgue Party Resurrection (Donald Love)", "No Money, Mo' Problems (Donald Love)",
	"Bringing the House Down (Donald Love)", "Love on the Run (Donald Love)", "More Deadly than the Male (Toshiko Kasen)", "Cash Clash (Toshiko Kasen)",
	"A Date with Death (Toshiko Kasen)", "Cash in Kazuki's Chips (Toshiko Kasen)"
	};

	CPlayerPed *pPlayer = FindPlayerPed();
	if(!pPlayer || FrontEndMenuManager.m_bGameNotLoaded) { return; } // if not loaded, scm offsets not inited, only in game
	//void CTheScripts::ReadMultiScriptFileOffsetsFromScript() Script5.cpp
	int NumberOfMissionScripts = CTheScripts::NumberOfMissionScripts;
	for(int i = 0; i < NumberOfMissionScripts; i++)
	{ // todo refw auto labels?
		std::cout << i << ": " << "0x" << std::hex << CTheScripts::MultiScriptArray[i] << std::dec << "   " << missions[i] << "\n";
	}
}