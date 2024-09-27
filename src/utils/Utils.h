#pragma once
#include "../core/common.h"

class CEntity;
class CPed;
class CVehicle;
class CPlayerPed;
class CCivilianPed;
class CWeaponInfo;

//struct RpAtomic;

#include "Windows.h"
#include <iostream>

//HANDLE InitConsole();
//void LeaveConsole(HANDLE hConsole);




void Mbox(const char* msg, const char* title);
//void MboxSTD(const std::string& msg, const std::string& title = "title")
void MboxSTD(std::string msg, std::string title = "");
void EXIT_F();
void EXIT_S();
void RaiseError(const char* fmt, ...);



void DumpTexturesNames(RpAtomic* pRpAtomic, CEntity* pEntity = nullptr, bool dump_error = true);



int GetModelIndex(CEntity* pEntity);

std::string GetModelName(CEntity* pEntity);

std::string GetModelTxdSlotName(CEntity* pEntity);

// crash if entity is ped
void DumpEntityData(CEntity* pEntity, bool clear_console = true);

CWeaponInfo* GetPlayerCurrentWeaponInfo();

int32_t GetPlayerCurrentWeaponType();


//-----
bool IsWeaponPistol();
bool IsWeaponUziPlayer();
bool IsWeaponAK47Player();
bool IsWeaponM16Player();
bool IsUnArmedPlayer();
//-----

RpClump* GetPlayerClump();
bool IsPlayerDriveVehicle();

// if(!DKSleep(deltaTime.count(), gfMemingTimer, gfTimerBuffer)) { return; } // задержка прокрута
bool DKSleep(float deltaTime, float wait_time, float& sleepBuffer);

bool
IsWindowActive(HWND hwnd);

bool
IsWindowMinimized(HWND hwnd);

// example in cpp
//std::wstring
//Utf8ToWide(const std::string &utf8Str);

//inline
int
GetFrontendAudioPercentVolume(bool bSFX, bool crt_vol = true);

void
UAsciiToUnicode(const char *src, wchar *dst); // font.cpp

void
UUnicodeToAscii(wchar *src, char *dst);


bool
IsPlayerAsPassangerNow();

bool
CheckWastedBustedPlayer(); // return true if wasted/busted

bool
IsPlayerPlaying();

CVector
Transform3DPoint2NearPathNode(CVector target);

int
GetRandomNumInclude(int start, int end);

int
GetRandomNumUnInclude(int start, int end);

bool
IsWithinRadius(const CVector &point1, const CVector &point2, float radius);

void
Message(const char *str, bool play_beep = true);

CVehicle *
GetRandomPoolVehicle(bool nodriver = false, bool all = false);

CVehicle *
GetVehicleNearPlayer();

void
DumpAllScriptsOffsets();