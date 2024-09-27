#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "AnimBlendAssociation.h"
#include "AudioManager.h"
#include "Boat.h"
#include "Camera.h"
#include "CarCtrl.h"
#include "CivilianPed.h"
#include "Clock.h"
#include "CopPed.h"
#include "Coronas.h"
#include "Debug.h"
#include "DMAudio.h"
#include "EmergencyPed.h"
#include "FileMgr.h"
#include "Frontend.h"
#include "General.h"
#include "GenericGameStorage.h"
#include "HandlingMgr.h"
#include "Heli.h"
#include "Hud.h"
#include "Lines.h"
#include "Messages.h"
#include "Pad.h"
#include "Pickups.h"
#include "Pools.h"
#include "Population.h"
#include "Remote.h"
#include "Replay.h"
#include "Stats.h"
#include "Streaming.h"
#include "User.h"
#include "Wanted.h"
#include "Weather.h"
#include "Zones.h"
#include "main.h"
#include "Ropes.h"
#include "ColStore.h"
#include "Fluff.h"
#include "GameLogic.h"
#include "MBlur.h"
#include "PedRoutes.h"
#include "RoadBlocks.h"
#include "SpecialFX.h"
#include "Timecycle.h"
#include "TxdStore.h"
#include "Bike.h"
#include "smallHeap.h"
// new
#include "Radar.h"
#include "Garages.h"
#include "CarGen.h"
#include "Restart.h"
#pragma optimize("", off) // tmp 4 dbg

#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
#include <stdarg.h>
#endif

//--LCS: file done except TODOs and command table
uint8* CTheScripts::ScriptSpace;
CRunningScript CTheScripts::ScriptsArray[MAX_NUM_SCRIPTS];
intro_text_line CTheScripts::IntroTextLines[MAX_NUM_INTRO_TEXT_LINES];
intro_script_rectangle CTheScripts::IntroRectangles[MAX_NUM_INTRO_RECTANGLES];
CSprite2d CTheScripts::ScriptSprites[MAX_NUM_SCRIPT_SRPITES];
script_sphere_struct CTheScripts::ScriptSphereArray[MAX_NUM_SCRIPT_SPHERES];
tCollectiveData CTheScripts::CollectiveArray[MAX_NUM_COLLECTIVES];
tUsedObject CTheScripts::UsedObjectArray[MAX_NUM_USED_OBJECTS];
int32 CTheScripts::MultiScriptArray[MAX_NUM_MISSION_SCRIPTS];
tBuildingSwap CTheScripts::BuildingSwapArray[MAX_NUM_BUILDING_SWAPS];
CEntity* CTheScripts::InvisibilitySettingArray[MAX_NUM_INVISIBILITY_SETTINGS];
CStoredLine CTheScripts::aStoredLines[MAX_NUM_STORED_LINES];
bool CTheScripts::DbgFlag;
uint32 CTheScripts::OnAMissionFlag;
int32 CTheScripts::StoreVehicleIndex;
bool CTheScripts::StoreVehicleWasRandom;
CRunningScript *CTheScripts::pIdleScripts;
CRunningScript *CTheScripts::pActiveScripts;
int32 CTheScripts::NextFreeCollectiveIndex;
int32 CTheScripts::LastRandomPedId;
uint16 CTheScripts::NumberOfUsedObjects;
bool CTheScripts::bAlreadyRunningAMissionScript;
bool CTheScripts::bUsingAMultiScriptFile;
uint16 CTheScripts::NumberOfMissionScripts;
uint32 CTheScripts::LargestMissionScriptSize;
uint32 CTheScripts::MainScriptSize;
uint8 CTheScripts::FailCurrentMission;
uint16 CTheScripts::NumScriptDebugLines;
uint16 CTheScripts::NumberOfIntroRectanglesThisFrame;
uint16 CTheScripts::NumberOfIntroTextLinesThisFrame;
uint8 CTheScripts::UseTextCommands;
CMissionCleanup CTheScripts::MissionCleanUp;
CUpsideDownCarCheck CTheScripts::UpsideDownCars;
CStuckCarCheck CTheScripts::StuckCars;
uint16 CTheScripts::CommandsExecuted;
uint16 CTheScripts::ScriptsUpdated;
int32 ScriptParams[32];
uint8 CTheScripts::RiotIntensity;
uint32 CTheScripts::LastMissionPassedTime;
uint16 CTheScripts::NumberOfExclusiveMissionScripts;
bool CTheScripts::bPlayerHasMetDebbieHarry;
bool CTheScripts::bPlayerIsInTheStatium;
int CTheScripts::AllowedCollision[MAX_ALLOWED_COLLISIONS];
int CTheScripts::FSDestroyedFlag;
uint16* CTheScripts::SavedVarIndices;
int CTheScripts::NumSaveVars;
int gScriptsFile = -1;
int CTheScripts::NextProcessId = 1;
bool CTheScripts::InTheScripts;
CRunningScript* pCurrent;
uint16 CTheScripts::NumTrueGlobals;
uint16 CTheScripts::MostGlobals;
CVector gVectorSetInLua;
int CTheScripts::NextScriptCoronaID;
base::cSList<script_corona> CTheScripts::mCoronas;

#ifdef MISSION_REPLAY

static const char* MissionScripts[] = { // vcs todo
	"VIC2",
	"VIC3",
	"VIC4",
	"VIC5",
	"VIC6",
	"VIC7",
	"SAL1",
	"SAL2",
	"SAL3",
	"SAL4",
	"SAL5",
	"SAL6",
	"SAL7",
	"SAL8",
	"JDT1",
	"JDT2",
	"JDT3",
	"JDT4",
	"JDT5",
	"JDT6",
	"JDT7",
	"JDT8",
	"MAC1",
	"MAC2",
	"MAC3",
	"MAC4",
	"MAC5",
	"SALS1",
	"SALS2",
	"SALS3",
	"SALS4",
	"SALS5",
	"SALS6",
	"RAYS1",
	"RAYS2",
	"RAYS3",
	"RAYS4",
	"RAYS5",
	"DONS1",
	"DONS2",
	"DONS3",
	"DONS4",
	"DONS5",
	"DONS6",
	"DONS7",
	"NEDS1",
	"NEDS2",
	"NEDS3",
	"NEDS4",
	"SALH1",
	"SALH2",
	"SALH3",
	"SALH4",
	"SALH5",
	"DONH1",
	"DONH2",
	"DONH3",
	"DONH4",
	"DONH5",
	"DONH6",
	"TOSH1",
	"TOSH2",
	"TOSH3",
	"TOSH4"
};

int AllowMissionReplay;
uint32 NextMissionDelay;
uint32 MissionStartTime;
uint32 WaitForMissionActivate;
uint32 WaitForSave;
float oldTargetX;
float oldTargetY;
int missionRetryScriptIndex;
bool doingMissionRetry;
bool gbTryingPorn4Again;
int IsInAmmunation;
int MissionSkipLevel;

#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
bool AlreadySavedGame;
#endif

#endif

const uint32 CRunningScript::nSaveStructSize =
#ifdef COMPATIBLE_SAVES
	536;
#else
	sizeof(CRunningScript);
#endif

CMissionCleanup::CMissionCleanup()
{
	Init();
}

void CMissionCleanup::Init()
{
	m_nCount = 0;
	for (int i = 0; i < MAX_CLEANUP; i++){
		m_sEntities[i].type = CLEANUP_UNUSED;
		m_sEntities[i].id = 0;
	}
}

cleanup_entity_struct* CMissionCleanup::FindFree()
{
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == CLEANUP_UNUSED)
			return &m_sEntities[i];
	}
	script_assert(0);
	return nil;
}

void SleepThisPed(cleanup_entity_struct* pCleanup, CPed* pPed)
{
	printf("*** SLEEPING PED %i %i\n", pCleanup->id, pPed->GetModelIndex());
	if (!pPed->GetIsStatic())
		pPed->RemoveFromMovingList();
	pPed->bIsStaticWaitingForCollision = true;
}

void WakeThisPed(cleanup_entity_struct* pCleanup, CPed* pPed)
{
	printf("*** WAKING UP PED %i %i\n", pCleanup->id, pPed->GetModelIndex());
	pPed->bIsStaticWaitingForCollision = false;
	if (!pPed->bIsStatic)
		pPed->AddToMovingList();

}

void CMissionCleanup::AddEntityToList(int32 id, uint8 type)
{
	cleanup_entity_struct* pNew = FindFree();
	if (!pNew)
		return;
	pNew->id = id;
	pNew->type = type;
	m_nCount++;
}

void CMissionCleanup::RemoveEntityFromList(int32 id, uint8 type)
{
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == type && m_sEntities[i].id == id){
			switch (m_sEntities[i].type) {
			case CLEANUP_CAR:
			{
				CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(m_sEntities[i].id);
				if (pVehicle) {
					if (pVehicle->bIsStaticWaitingForCollision) {
						pVehicle->bIsStaticWaitingForCollision = false;
						if (!pVehicle->GetIsStatic())
							pVehicle->AddToMovingList();
					}
				}
				break;
			}
			case CLEANUP_CHAR:
			{
				CPed* pPed = CPools::GetPedPool()->GetAt(m_sEntities[i].id);
				if (pPed) {
					if (pPed->bIsStaticWaitingForCollision) {
						pPed->bIsStaticWaitingForCollision = false;
						if (!pPed->GetIsStatic())
							pPed->AddToMovingList();
					}
				}
				break;
			}
			case CLEANUP_OBJECT:
			{
				CObject* pObject = CPools::GetObjectPool()->GetAt(m_sEntities[i].id);
				if (pObject) {
					if (pObject->bIsStaticWaitingForCollision) {
						pObject->bIsStaticWaitingForCollision = false;
						if (!pObject->GetIsStatic())
							pObject->AddToMovingList();
					}
				}
				break;
			}
			default:
				break;
			}
			m_sEntities[i].id = 0;
			m_sEntities[i].type = CLEANUP_UNUSED;
			m_nCount--;
		}
	}
}

// relcs todo MAZAHAKA_MAPZONE_VC??
/*void CMissionCleanup::CheckIfCollisionHasLoadedForMissionObjects()
{
	for (int i = 0; i < MAX_CLEANUP; i++) {
		switch (m_sEntities[i].type) {
		case CLEANUP_CAR:
		{
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(m_sEntities[i].id);
			if (pVehicle) {
				eLevelName level = CTheZones::GetLevelFromPosition(&pVehicle->GetPosition());
				if (level == LEVEL_GENERIC)
					level = CGame::currLevel;
				if (!CColStore::HasCollisionLoaded(level)) {
					if (!pVehicle->bIsStaticWaitingForCollision) {
						if (!pVehicle->IsHeli() && !pVehicle->IsPlane() && pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI &&
							pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT && pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_PLANE) {
							printf("*** SLEEPING VEHICLE %i %i\n", m_sEntities[i].id, pVehicle->GetModelIndex());
							if (!pVehicle->GetIsStatic())
								pVehicle->RemoveFromMovingList();
							pVehicle->bIsStaticWaitingForCollision = true;
						}
					}
				}
				else {
					if (pVehicle->bIsStaticWaitingForCollision) {
						printf("*** WAKING UP VEHICLE %i %i\n", m_sEntities[i].id, pVehicle->GetModelIndex());
						pVehicle->bIsStaticWaitingForCollision = false;
						if (!pVehicle->bIsStatic)
							pVehicle->AddToMovingList();
					}
				}
			}
		}
		break;
		case CLEANUP_OBJECT:
			CObject* pObject = CPools::GetObjectPool()->GetAt(m_sEntities[i].id);
			if (pObject) {
				eLevelName level = CTheZones::GetLevelFromPosition(&pObject->GetPosition());
				if (level == LEVEL_GENERIC)
					level = CGame::currLevel;
				if (!CColStore::HasCollisionLoaded(level)) {
					if (!pObject->bIsStaticWaitingForCollision) {
						if (!pObject->GetIsStatic())
							pObject->RemoveFromMovingList();
						pObject->bIsStaticWaitingForCollision = true;
					}
				}
				else {
					if (pObject->bIsStaticWaitingForCollision) {
						pObject->bIsStaticWaitingForCollision = false;
						if (!pObject->bIsStatic)
							pObject->AddToMovingList();
					}
				}
			}
		}
	}
	for (int i = 0; i < MAX_CLEANUP; i++) {
		switch (m_sEntities[i].type) {
		case CLEANUP_CHAR:
		{
			CPed* pPed = CPools::GetPedPool()->GetAt(m_sEntities[i].id);
			if (pPed) {
				eLevelName level = CTheZones::GetLevelFromPosition(&pPed->GetPosition());
				if (level == LEVEL_GENERIC)
					level = CGame::currLevel;
				if (!pPed->bIsStaticWaitingForCollision) {
					if (pPed->bInVehicle) {
						if (pPed->m_pMyVehicle->GetIsStatic()) {
							SleepThisPed(&m_sEntities[i], pPed);
							continue;
						}
					}
					if (!CColStore::HasCollisionLoaded(level)) {
						if (pPed->bInVehicle && pPed->m_pMyVehicle->GetIsStatic() ||
							pPed->m_attachedTo && pPed->m_attachedTo->GetIsStatic())
							SleepThisPed(&m_sEntities[i], pPed);
					}
				}
				else {
					if (!pPed->bInVehicle) {
						if (CColStore::HasCollisionLoaded(level)) {
							if (!(pPed->bInVehicle && pPed->m_pMyVehicle->GetIsStatic() ||
								pPed->m_attachedTo && pPed->m_attachedTo->GetIsStatic()))
								WakeThisPed(&m_sEntities[i], pPed);
						}
					}
					else {
						if (!pPed->m_pMyVehicle->GetIsStatic()) {
							WakeThisPed(&m_sEntities[i], pPed);
							continue;
						}
						if (CColStore::HasCollisionLoaded(level)) {
							if (!(pPed->bInVehicle && pPed->m_pMyVehicle->GetIsStatic() ||
								pPed->m_attachedTo && pPed->m_attachedTo->GetIsStatic()))
								WakeThisPed(&m_sEntities[i], pPed);
						}
					}
				}

			}
		}
		break;
		}
	}
}*/

//revc
void CMissionCleanup::CheckIfCollisionHasLoadedForMissionObjects()
{
	for (int i = 0; i < MAX_CLEANUP; i++) {
		switch (m_sEntities[i].type) {
		case CLEANUP_CAR:
		{
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(m_sEntities[i].id);
			if (pVehicle) {
				if (pVehicle->bIsStaticWaitingForCollision) {
					if (CColStore::HasCollisionLoaded(pVehicle->GetPosition())) {
						pVehicle->bIsStaticWaitingForCollision = false;
							if (!pVehicle->GetIsStatic())
								pVehicle->AddToMovingList();
					}
				}
			}
			break;
		}
		case CLEANUP_CHAR:
		{
			CPed* pPed = CPools::GetPedPool()->GetAt(m_sEntities[i].id);
			if (pPed) {
				if (pPed->bIsStaticWaitingForCollision) {
					if (CColStore::HasCollisionLoaded(pPed->GetPosition())) {
						pPed->bIsStaticWaitingForCollision = false;
						if (!pPed->GetIsStatic())
							pPed->AddToMovingList();
					}
				}
			}
			break;
		}
		case CLEANUP_OBJECT:
		{
			CObject* pObject = CPools::GetObjectPool()->GetAt(m_sEntities[i].id);
			if (pObject) {
				if (pObject->bIsStaticWaitingForCollision) {
					if (CColStore::HasCollisionLoaded(pObject->GetPosition())) {
						pObject->bIsStaticWaitingForCollision = false;
						if (!pObject->GetIsStatic())
							pObject->AddToMovingList();
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

void CMissionCleanup::Process()
{
	CPopulation::m_AllRandomPedsThisType = -1;
	CPopulation::PedDensityMultiplier = 1.0f;
	CCarCtrl::CarDensityMultiplier = 1.0f;
	CPed::nThreatReactionRangeMultiplier = 1;
	CPed::nEnterCarRangeMultiplier = 1;
	for (int i = 0; i < MAX_ALLOWED_COLLISIONS; i++)
		CTheScripts::AllowedCollision[i] = 0;
	FindPlayerPed()->m_pWanted->m_fCrimeSensitivity = 1.0f;
	CRoadBlocks::ClearScriptRoadBlocks();
	CRouteNode::Initialise();
	if (!CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		TheCamera.Restore();
	TheCamera.SetWideScreenOff();
	CSpecialFX::bLiftCam = false;
	// TODO(LCS): CHud::m_ClockEventWarningMinutes = 0;
	// TODO(LCS): CHud::m_ClockEventFlashTimer = 0;
	CTimeCycle::StopExtraColour(0); // TODO: thiscall
	for (int i = 0; i < MISSION_AUDIO_SLOTS; i++)
		DMAudio.ClearMissionAudio(i);
	CWeather::ReleaseWeather();
	for (int i = 0; i < NUM_OF_SPECIAL_CHARS; i++)
		CStreaming::SetMissionDoesntRequireSpecialChar(i);
#ifdef GTA_NETWORK
	if (!gIsMultiplayerGame)
#endif
		CStreaming::ms_disableStreaming = false;
	if (CHud::m_ItemToFlash != ITEM_ARMOUR && CHud::m_ItemToFlash != ITEM_HEALTH)
		CHud::m_ItemToFlash = ITEM_NONE;
	CHud::SetHelpMessage(nil, false); // nil, false, false, true TODO(LCS)
	CUserDisplay::OnscnTimer.m_bDisabled = false;
	CWorld::Players[0].m_pPed->m_pWanted->m_bIgnoredByCops = false;
	CWorld::Players[0].m_pPed->m_pWanted->m_bIgnoredByEveryone = false;
	CWorld::Players[0].MakePlayerSafe(false);
	CWorld::Players[0].m_pPed->m_nFadeDrunkenness = 1;
	CWorld::Players[0].m_pPed->m_nDrunkCountdown = 0;
	CPad::GetPad(0)->SetDrunkInputDelay(0);
	CWorld::Players[0].m_bDriveByAllowed = true;
	CPad::GetPad(0)->unk_B4 = 1.0f;
	CPad::GetPad(0)->unk_B8 = 0.5f;
	DMAudio.ShutUpPlayerTalking(FALSE);
	CVehicle::bDisableRemoteDetonation = false;
	CVehicle::bDisableRemoteDetonationOnContact = false;
	CTheScripts::RiotIntensity = 0;
	CTheScripts::StoreVehicleIndex = -1;
	CTheScripts::StoreVehicleWasRandom = true;
	CTheScripts::UpsideDownCars.Init();
	CTheScripts::StuckCars.Init();
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == CLEANUP_UNUSED)
			continue;
		switch (m_sEntities[i].type) {
		case CLEANUP_CAR:
		{
			CVehicle* v = CPools::GetVehiclePool()->GetAt(m_sEntities[i].id);
			if (v)
				CTheScripts::CleanUpThisVehicle(v);
			break;
		}
		case CLEANUP_CHAR:
		{
			CPed* p = CPools::GetPedPool()->GetAt(m_sEntities[i].id);
			if (p)
				CTheScripts::CleanUpThisPed(p);
			break;
		}
		case CLEANUP_OBJECT:
		{
			CObject* o = CPools::GetObjectPool()->GetAt(m_sEntities[i].id);
			if (o)
				CTheScripts::CleanUpThisObject(o);
			break;
		}
		default:
			break;
		}
		RemoveEntityFromList(m_sEntities[i].id, m_sEntities[i].type);
	}
	for (int i = 1; i < MODELINFOSIZE; i++) {
		if (CStreaming::IsScriptOwnedModel(i))
			CStreaming::SetMissionDoesntRequireModel(i);
	}
#ifdef SECUROM
	if ((myrand() & 3) == 2){
		// if pirated game
		CWeather::ForceHurricaneWeather();
	}
#endif
}

/* NB: CUpsideDownCarCheck is not used by actual script at all
 * It has a weird usage: AreAnyCarsUpsideDown would fail any mission
 * just like death or arrest. */

void CUpsideDownCarCheck::Init()
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		m_sCars[i].m_nVehicleIndex = -1;
		m_sCars[i].m_nUpsideDownTimer = 0;
	}
}

bool CUpsideDownCarCheck::IsCarUpsideDown(int32 id)
{
	CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(id);
	return IsCarUpsideDown(pVehicle);
}

bool CUpsideDownCarCheck::IsCarUpsideDown(CVehicle* pVehicle)
{
	script_assert(pVehicle);
	return pVehicle->GetUp().z <= UPSIDEDOWN_UP_THRESHOLD &&
		pVehicle->GetMoveSpeed().Magnitude() < UPSIDEDOWN_MOVE_SPEED_THRESHOLD &&
		pVehicle->GetTurnSpeed().Magnitude() < UPSIDEDOWN_TURN_SPEED_THRESHOLD;
}

void CUpsideDownCarCheck::UpdateTimers()
{
	uint32 timeStep = CTimer::GetTimeStepInMilliseconds();
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		CVehicle* v = CPools::GetVehiclePool()->GetAt(m_sCars[i].m_nVehicleIndex);
		if (v){
			if (IsCarUpsideDown(m_sCars[i].m_nVehicleIndex))
				m_sCars[i].m_nUpsideDownTimer += timeStep;
			else
				m_sCars[i].m_nUpsideDownTimer = 0;
		}else{
			m_sCars[i].m_nVehicleIndex = -1;
			m_sCars[i].m_nUpsideDownTimer = 0;
		}
	}
}

bool CUpsideDownCarCheck::AreAnyCarsUpsideDown()
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex >= 0 && m_sCars[i].m_nUpsideDownTimer > UPSIDEDOWN_TIMER_THRESHOLD)
			return true;
	}
	return false;
}

void CUpsideDownCarCheck::AddCarToCheck(int32 id)
{
	uint16 index = 0;
	while (index < MAX_UPSIDEDOWN_CAR_CHECKS && m_sCars[index].m_nVehicleIndex >= 0)
		index++;
#ifdef FIX_BUGS
	if (index >= MAX_UPSIDEDOWN_CAR_CHECKS)
		return;
#endif
	m_sCars[index].m_nVehicleIndex = id;
	m_sCars[index].m_nUpsideDownTimer = 0;
}

void CUpsideDownCarCheck::RemoveCarFromCheck(int32 id)
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id){
			m_sCars[i].m_nVehicleIndex = -1;
			m_sCars[i].m_nUpsideDownTimer = 0;
		}
	}
}

bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int32 id)
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id)
			return m_sCars[i].m_nUpsideDownTimer > UPSIDEDOWN_TIMER_THRESHOLD;
	}
	return false;
}

void stuck_car_data::Reset()
{
	m_nVehicleIndex = -1;
	m_vecPos = CVector(-5000.0f, -5000.0f, -5000.0f);
	m_nLastCheck = -1;
	m_fRadius = 0.0f;
	m_nStuckTime = 0;
	m_bStuck = false;
}

void CStuckCarCheck::Init()
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++) {
		m_sCars[i].Reset();
	}
}

void CStuckCarCheck::Process()
{
	uint32 timer = CTimer::GetTimeInMilliseconds();
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex < 0)
			continue;
		if (timer <= m_sCars[i].m_nStuckTime + m_sCars[i].m_nLastCheck)
			continue;
		CVehicle* pv = CPools::GetVehiclePool()->GetAt(m_sCars[i].m_nVehicleIndex);
		if (!pv){
			m_sCars[i].Reset();
			continue;
		}
		float distance = (pv->GetPosition() - m_sCars[i].m_vecPos).Magnitude();
		m_sCars[i].m_bStuck = distance < m_sCars[i].m_fRadius;
		m_sCars[i].m_vecPos = pv->GetPosition();
		m_sCars[i].m_nLastCheck = timer;
	}
}

void CStuckCarCheck::AddCarToCheck(int32 id, float radius, uint32 time)
{
	CVehicle* pv = CPools::GetVehiclePool()->GetAt(id);
	if (!pv)
		return;
	int index = 0;
	while (index < MAX_STUCK_CAR_CHECKS && m_sCars[index].m_nVehicleIndex >= 0)
		index++;
#ifdef FIX_BUGS
	if (index >= MAX_STUCK_CAR_CHECKS)
		return;
#endif
	m_sCars[index].m_nVehicleIndex = id;
	m_sCars[index].m_vecPos = pv->GetPosition();
	m_sCars[index].m_nLastCheck = CTimer::GetTimeInMilliseconds();
	m_sCars[index].m_fRadius = radius;
	m_sCars[index].m_nStuckTime = time;
	m_sCars[index].m_bStuck = false;
}

void CStuckCarCheck::RemoveCarFromCheck(int32 id)
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id){
			m_sCars[i].Reset();
		}
	}
}

bool CStuckCarCheck::HasCarBeenStuckForAWhile(int32 id)
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id)
			return m_sCars[i].m_bStuck;
	}
	return false;
}

void CRunningScript::CollectParameters(uint32* pIp, int16 total, int* pParameters)
{
	while (total--){
		//int type = (uint32_t)CTheScripts::Read1ByteFromScript(pIp);
		//debug("com: %d\n", type);
		//switch (type)
		switch (CTheScripts::Read1ByteFromScript(pIp))
		{
		case ARGUMENT_END:
			return;
		case ARGUMENT_INT_ZERO:
			*pParameters = 0;
			break;
		case ARGUMENT_FLOAT_ZERO:
			*pParameters = 0;
			break;
		case ARGUMENT_FLOAT_1BYTE:
			*pParameters = (uint32)(uint8)CTheScripts::Read1ByteFromScript(pIp) << 24;
			break;
		case ARGUMENT_FLOAT_2BYTES:
			*pParameters = (uint32)(uint16)CTheScripts::Read2BytesFromScript(pIp) << 16;
			break;
		case ARGUMENT_FLOAT_3BYTES:
			*pParameters = (uint32)(uint8)CTheScripts::Read1ByteFromScript(pIp) << 8;
			*pParameters |= (uint32)(uint16)CTheScripts::Read2BytesFromScript(pIp) << 16;
			break;
		case ARGUMENT_INT32:
		case ARGUMENT_FLOAT:
			*pParameters = CTheScripts::Read4BytesFromScript(pIp);
			break;
		case ARGUMENT_INT8:
			*pParameters = CTheScripts::Read1ByteFromScript(pIp);
			break;
		case ARGUMENT_INT16:
			*pParameters = CTheScripts::Read2BytesFromScript(pIp);
			break;
		case ARGUMENT_STRING:
			*pParameters = *pIp;
			*pIp += strlen((char *)(CTheScripts::ScriptSpace + *pIp)) + 1;
			break;
		default:
			*pIp -= 1;
			*pParameters = *GetPointerToScriptVariable(pIp);
			break;
		}
		pParameters++;
	}
}


int32 CRunningScript::CollectNextParameterWithoutIncreasingPC(uint32 ip)
{
	uint32* pIp = &ip;
	int tmp;
	switch (CTheScripts::Read1ByteFromScript(pIp))
	{
	case ARGUMENT_END:
		return 0; // TODO(LCS)
	case ARGUMENT_INT_ZERO:
		return 0;
	case ARGUMENT_FLOAT_ZERO:
		return 0;
	case ARGUMENT_FLOAT_1BYTE:
		return (uint32)(uint8)CTheScripts::Read1ByteFromScript(pIp) << 24;
	case ARGUMENT_FLOAT_2BYTES:
		return (uint32)(uint16)CTheScripts::Read2BytesFromScript(pIp) << 16;
	case ARGUMENT_FLOAT_3BYTES:
		tmp = (uint32)(uint8)CTheScripts::Read1ByteFromScript(pIp) << 8;
		tmp |= (uint32)(uint16)CTheScripts::Read2BytesFromScript(pIp) << 16;
		return tmp;
	case ARGUMENT_INT32:
	case ARGUMENT_FLOAT: // vcs
		return CTheScripts::Read4BytesFromScript(pIp);
	case ARGUMENT_INT8:
		return CTheScripts::Read1ByteFromScript(pIp);
	case ARGUMENT_INT16:
		return CTheScripts::Read2BytesFromScript(pIp);
	//case ARGUMENT_FLOAT:
	//	return CTheScripts::Read4BytesFromScript(pIp);
	// vcs string arg ida ??? i not found str arg
	default:
		(*pIp)--;
		return *GetPointerToScriptVariable(pIp);
	}
	return -1;
}

void CRunningScript::StoreParameters(uint32* pIp, int16 number)
{
	for (int16 i = 0; i < number; i++){
		*GetPointerToScriptVariable(pIp) = ScriptParams[i];
	}
}



// vcs todo inline
const char* CRunningScript::GetKeyFromScript(uint32* pIp) // lcs, vcs hardcoded or inlined
{
	CollectParameters(pIp, 1); // 0x0A type string include here, GET_INTEGER_PARAM(0) store ip string in collect
	const char *key = GET_INTEGER_PARAM(0) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)] : nil;
	return key;
}

wchar* CRunningScript::GetTextByKeyFromScript(uint32* pIp)
{
	CollectParameters(pIp, 1);
	wchar *text = GET_INTEGER_PARAM(0) ? TheText.Get((const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)]) : nil;
	return text;
}


//__declspec(noinline) 
//#pragma optimize("", off) // dbg stuff
#ifdef THIS_IS_STUPID
int32* GetPointerToScriptVariable(CRunningScript* pScript, uint32* pIp)
{
	uint8 type = CTheScripts::Read1ByteFromScript(pIp);
	if (type >= ARGUMENT_GLOBAL_ARRAY) {
		uint8 index_in_block = CTheScripts::Read1ByteFromScript(pIp);
		uint8 index_id = CTheScripts::Read1ByteFromScript(pIp);
		uint8 size = CTheScripts::Read1ByteFromScript(pIp);
		script_assert(size > 0);
		script_assert(pScript->m_anLocalVariables[pScript->m_nLocalsPointer + index_id] < size);
		uint8 index = Min(pScript->m_anLocalVariables[pScript->m_nLocalsPointer + index_id], size - 1);
		return (int32*)&CTheScripts::ScriptSpace[4 * (((int)(type - ARGUMENT_GLOBAL_ARRAY) << 8) + index + index_in_block)];
	}
	else if (type >= ARGUMENT_GLOBAL) {
		uint8 index_in_block = CTheScripts::Read1ByteFromScript(pIp);
		return (int32*)&CTheScripts::ScriptSpace[4 * (((int)(type - ARGUMENT_GLOBAL) << 8) + index_in_block)];
	}
	else if (type >= ARGUMENT_LOCAL_ARRAY) {
		uint8 index_id = CTheScripts::Read1ByteFromScript(pIp);
		uint8 size = CTheScripts::Read1ByteFromScript(pIp);
		script_assert(size > 0);
		script_assert(pScript->m_anLocalVariables[pScript->m_nLocalsPointer + index_id] < size);
		uint8 index = Min(pScript->m_anLocalVariables[pScript->m_nLocalsPointer + index_id], size - 1);
		return &pScript->m_anLocalVariables[pScript->m_nLocalsPointer + (type - ARGUMENT_LOCAL_ARRAY) + index];
	}
	else if (type >= ARGUMENT_LOCAL) {
		return &pScript->m_anLocalVariables[pScript->m_nLocalsPointer + (type - ARGUMENT_LOCAL)];
	}
	else if (type >= ARGUMENT_TIMER) {
		return &pScript->m_anLocalVariables[NUM_LOCAL_VARS + 8 + (type - ARGUMENT_TIMER)];
	}
	script_assert(false && "wrong type for variable");
	return &pScript->m_anLocalVariables[pScript->m_nLocalsPointer + (type - ARGUMENT_LOCAL)];
}

int32 *CRunningScript::GetPointerToScriptVariable(uint32* pIp/*, int16 type*/)
{
	return ::GetPointerToScriptVariable(this, pIp);
}
#else
int32 *CRunningScript::GetPointerToScriptVariable(uint32* pIp)
{
	uint8 type = CTheScripts::Read1ByteFromScript(pIp);
	if (type >= ARGUMENT_GLOBAL_ARRAY) {
		uint8 index_in_block = CTheScripts::Read1ByteFromScript(pIp);
		uint8 index_id = CTheScripts::Read1ByteFromScript(pIp);
		uint8 size = CTheScripts::Read1ByteFromScript(pIp);
		script_assert(size > 0);
		script_assert(m_anLocalVariables[m_nLocalsPointer + index_id] < size);
		uint8 index = Min(m_anLocalVariables[m_nLocalsPointer + index_id], size - 1);
		return (int32*)&CTheScripts::ScriptSpace[4 * (((int)(type - ARGUMENT_GLOBAL_ARRAY) << 8) + index + index_in_block)];
	}
	else if (type >= ARGUMENT_GLOBAL) {
		uint8 index_in_block = CTheScripts::Read1ByteFromScript(pIp);
		return (int32*)&CTheScripts::ScriptSpace[4 * (((int)(type - ARGUMENT_GLOBAL) << 8) + index_in_block)];
	}
	else if (type >= ARGUMENT_LOCAL_ARRAY) {
		uint8 index_id = CTheScripts::Read1ByteFromScript(pIp);
		uint8 size = CTheScripts::Read1ByteFromScript(pIp);
		script_assert(size > 0);
		script_assert(m_anLocalVariables[m_nLocalsPointer + index_id] < size);
		uint8 index = Min(m_anLocalVariables[m_nLocalsPointer + index_id], size - 1);
		return &m_anLocalVariables[m_nLocalsPointer + (type - ARGUMENT_LOCAL_ARRAY) + index];
	}
	else if (type >= ARGUMENT_LOCAL) {
		return &m_anLocalVariables[m_nLocalsPointer + (type - ARGUMENT_LOCAL)];
	}
	else if (type >= ARGUMENT_TIMER) {
		return &m_anLocalVariables[NUM_LOCAL_VARS + 8 + (type - ARGUMENT_TIMER)];
	}
	debug("wrong type for variable");
	script_assert(false && "wrong type for variable");
	return &m_anLocalVariables[m_nLocalsPointer + (type - ARGUMENT_LOCAL)];
}
#endif


int CTheScripts::GetSaveVarIndex(int var)
{
	for (int i = 0; i < NumSaveVars; i++) {
		if (SavedVarIndices[i] == var)
			return i;
	}
	return -1;
}

void CRunningScript::Init()
{
	sprintf(m_abScriptName, "id%02i", m_nId);
	next = prev = nil;
	SetIP(0);
	for (int i = 0; i < MAX_STACK_DEPTH; i++)
		m_anStack[i] = 0;
	m_nStackPointer = 0;
	m_nWakeTime = 0;
	m_bIsActive = false;
	m_bCondResult = false;
	m_bIsMissionScript = false;
	m_bSkipWakeTime = false;
	for (int i = 0; i < NUM_LOCAL_VARS + 8 + NUM_TIMERS; i++)
		m_anLocalVariables[i] = 0;
	m_nAndOrState = 0;
	m_bNotFlag = false;
	m_bDeatharrestEnabled = true;
	m_bDeatharrestExecuted = false;
	m_bMissionFlag = false;
	m_nLocalsPointer = 0;
}

void CTheScripts::Shutdown()
{
	if (gScriptsFile != -1) {
		CFileMgr::CloseFile(gScriptsFile);
		gScriptsFile = -1;
	}
	if (ScriptSpace) {
		base::cMainMemoryManager::Instance()->Free(ScriptSpace);
		ScriptSpace = nil;
		FSDestroyedFlag = false;
		OnAMissionFlag = 0;
	}
}

#ifdef USE_DEBUG_SCRIPT_LOADER
int CTheScripts::ScriptToLoad = 0;

int CTheScripts::OpenScript()
{
	CFileMgr::ChangeDir("\\");
	switch (ScriptToLoad) {
	case 0: return CFileMgr::OpenFile("DATA\\main.scm", "rb");
	case 1: return CFileMgr::OpenFile("DATA\\freeroam_vcs.scm", "rb");
	case 2: return CFileMgr::OpenFile("DATA\\main_d.scm", "rb");
	}
	return CFileMgr::OpenFile("DATA\\main.scm", "rb");
}
#endif

bool CTheScripts::Init(bool loaddata)
{
	bool retval = false;
	printf("CTheScripts::Init\n");
	pActiveScripts = pIdleScripts = nil;
	for (int i = 0; i < MAX_NUM_SCRIPTS; i++){
		ScriptsArray[i].Init();
		ScriptsArray[i].AddScriptToList(&pIdleScripts);
	}
	MissionCleanUp.Init();
	UpsideDownCars.Init();
	StuckCars.Init();
	StoreVehicleIndex = -1;
	StoreVehicleWasRandom = true;
	OnAMissionFlag = 0;
	LastMissionPassedTime = (uint32)-1;
	for (int i = 0; i < MAX_NUM_COLLECTIVES; i++) {
		CollectiveArray[i].colIndex = -1;
		CollectiveArray[i].pedIndex = 0;
	}
	NextFreeCollectiveIndex = 0;
	LastRandomPedId = -1;
	for (int i = 0; i < MAX_NUM_USED_OBJECTS; i++){
		memset(&UsedObjectArray[i].name, 0, sizeof(UsedObjectArray[i].name));
		UsedObjectArray[i].index = 0;
	}
#if defined FIX_BUGS || (!defined GTA_PS2 && !defined GTA_PSP)
	for (base::cSList<script_corona>::tSItem* i = CTheScripts::mCoronas.first; i;) {
		base::cSList<script_corona>::tSItem* next = i->next;
		delete i;
		i = next;
	}
	CTheScripts::mCoronas.first = nil;
#endif
	NumberOfUsedObjects = 0;
	if (ScriptSpace)
		Shutdown();
#ifdef USE_DEBUG_SCRIPT_LOADER
	// glfwGetKey doesn't work because of CGame::Initialise is blocking
	CPad::UpdatePads();
	if (CPad::GetPad(0)->GetChar('G')) ScriptToLoad = 0;
	if (CPad::GetPad(0)->GetChar('R')) ScriptToLoad = 1;
	if (CPad::GetPad(0)->GetChar('D')) ScriptToLoad = 2;
	int mainf = OpenScript();
#else
	CFileMgr::SetDir("DATA");
	int mainf = CFileMgr::OpenFile("main.scm", "rb");
#endif
	CFileMgr::Read(mainf, (char*)&MainScriptSize, sizeof(MainScriptSize));
	int nLargestMissionSize = 0;
	CFileMgr::Read(mainf, (char*)&nLargestMissionSize, sizeof(nLargestMissionSize));
	if (!cSmallHeap::msInstance.IsLocked())
		cSmallHeap::msInstance.Lock();
	ScriptSpace = (uint8*)base::cMainMemoryManager::Instance()->Allocate(MainScriptSize + nLargestMissionSize);
	memset(ScriptSpace, 0, MainScriptSize + nLargestMissionSize);
	CFileMgr::Read(mainf, (char*)ScriptSpace, MainScriptSize);
	gScriptsFile = mainf;
	CFileMgr::SetDir("");
	ReadObjectNamesFromScript();
	UpdateObjectIndices();
	bAlreadyRunningAMissionScript = false;
	bUsingAMultiScriptFile = true;
	for (int i = 0; i < MAX_NUM_MISSION_SCRIPTS; i++)
		MultiScriptArray[i] = 0;
	NumberOfExclusiveMissionScripts = 0;
	NumberOfMissionScripts = 0;
	LargestMissionScriptSize = 0;
	ReadMultiScriptFileOffsetsFromScript();
	FailCurrentMission = 0;
	DbgFlag = false;
	//NumScriptDebugLines = 0;
	RiotIntensity = 0;
	bPlayerHasMetDebbieHarry = false;
	bPlayerIsInTheStatium = false;
	for (int i = 0; i < MAX_NUM_SCRIPT_SPHERES; i++){
		ScriptSphereArray[i].m_bInUse = false;
		ScriptSphereArray[i].m_Index = 1;
		ScriptSphereArray[i].m_Id = 0;
		ScriptSphereArray[i].m_vecCenter = CVector(0.0f, 0.0f, 0.0f);
		ScriptSphereArray[i].m_fRadius = 0.0f;
	}
	for (int i = 0; i < MAX_NUM_INTRO_TEXT_LINES; i++){
		IntroTextLines[i].Reset();
	}
	NumberOfIntroTextLinesThisFrame = 0;
	UseTextCommands = 0;
	for (int i = 0; i < MAX_NUM_INTRO_RECTANGLES; i++){
		IntroRectangles[i].m_bIsUsed = false;
		IntroRectangles[i].m_bBeforeFade = false;
		IntroRectangles[i].m_nTextureId = -1;
		IntroRectangles[i].m_sRect = CRect(0.0f, 0.0f, 0.0f, 0.0f);
		IntroRectangles[i].m_sColor = CRGBA(255, 255, 255, 255);
	}
	NumberOfIntroRectanglesThisFrame = 0;
	//RemoveScriptTextureDictionary(); // TODO(LCS) - probably not needed
	for (int i = 0; i < MAX_NUM_BUILDING_SWAPS; i++){
		BuildingSwapArray[i].m_pBuilding = nil;
		BuildingSwapArray[i].m_nNewModel = -1;
		BuildingSwapArray[i].m_nOldModel = -1;
	}
	for (int i = 0; i < MAX_NUM_INVISIBILITY_SETTINGS; i++)
		InvisibilitySettingArray[i] = nil;
	if (loaddata) {
		printf("loaddata = true\n");
		retval = GenericLoad();
	}
	for (int i = 0; i < MAX_ALLOWED_COLLISIONS; i++)
		AllowedCollision[i] = 0;

#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LogAfterScriptInitializing();
#endif
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
	AlreadySavedGame = false;
#endif
	return retval;
}

/*
void CTheScripts::RemoveScriptTextureDictionary()
{
	for (int i = 0; i < ARRAY_SIZE(CTheScripts::ScriptSprites); i++)
		CTheScripts::ScriptSprites[i].Delete();
	int slot = CTxdStore::FindTxdSlot("script");
	if (slot != -1)
		CTxdStore::RemoveTxd(slot);
}
*/

void CRunningScript::RemoveScriptFromList(CRunningScript** ppScript)
{
	if (prev)
		prev->next = next;
	else
		*ppScript = next;
	if (next)
		next->prev = prev;
}

void CRunningScript::AddScriptToList(CRunningScript** ppScript)
{
	next = *ppScript;
	prev = nil;
	if (*ppScript)
		(*ppScript)->prev = this;
	*ppScript = this;
}

CRunningScript* CTheScripts::StartNewScript(uint32 ip)
{
	CRunningScript* pNew = pIdleScripts;
	script_assert(pNew);
	pNew->RemoveScriptFromList(&pIdleScripts);
	pNew->m_nId = NextProcessId++;
	pNew->Init();
	pNew->SetIP(ip);
	pNew->AddScriptToList(&pActiveScripts);
	pNew->m_bIsActive = true;
	return pNew;
}

void CTheScripts::Process()
{
	if (CReplay::IsPlayingBack())
		return;
	if (!ScriptSpace)
		return;
	CommandsExecuted = 0;
	ScriptsUpdated = 0;
	float timeStep = CTimer::GetTimeStepInMilliseconds();
	UpsideDownCars.UpdateTimers();
	StuckCars.Process();
	MissionCleanUp.CheckIfCollisionHasLoadedForMissionObjects();
	DrawScriptSpheres();
	if (FailCurrentMission)
		--FailCurrentMission;
	if (UseTextCommands){
		for (int i = 0; i < MAX_NUM_INTRO_TEXT_LINES; i++)
			IntroTextLines[i].Reset();
		NumberOfIntroTextLinesThisFrame = 0;
		for (int i = 0; i < MAX_NUM_INTRO_RECTANGLES; i++){
			IntroRectangles[i].m_bIsUsed = false;
			IntroRectangles[i].m_bBeforeFade = false;
		}
		NumberOfIntroRectanglesThisFrame = 0;
		if (UseTextCommands == 1)
			UseTextCommands = 0;
	}

#ifdef MISSION_REPLAY
	static uint32 TimeToWaitTill;
	static bool AlreadyResetHealth;
	switch (AllowMissionReplay) {
	case MISSION_RETRY_STAGE_START_PROCESSING:
		AllowMissionReplay = MISSION_RETRY_STAGE_WAIT_FOR_DELAY;
		TimeToWaitTill = CTimer::GetTimeInMilliseconds() + (AddExtraDeathDelay() > 1000 ? 4000 : 2500);
		break;
	case MISSION_RETRY_STAGE_WAIT_FOR_DELAY:
		if (TimeToWaitTill < CTimer::GetTimeInMilliseconds())
			AllowMissionReplay = MISSION_RETRY_STAGE_WAIT_FOR_MENU;
		break;
	case MISSION_RETRY_STAGE_WAIT_FOR_MENU:
		AllowMissionReplay = MISSION_RETRY_STAGE_WAIT_FOR_USER;
		RetryMission(MISSION_RETRY_TYPE_SUGGEST_TO_PLAYER);
		break;
	case MISSION_RETRY_STAGE_START_RESTARTING:
		AllowMissionReplay = MISSION_RETRY_STAGE_WAIT_FOR_TIMER_AFTER_RESTART;
		AlreadyResetHealth = false;
		TimeToWaitTill = CTimer::GetTimeInMilliseconds() + 500;
		break;
	case MISSION_RETRY_STAGE_WAIT_FOR_TIMER_AFTER_RESTART:
		if (!AlreadyResetHealth) {
			AlreadyResetHealth = true;
			CPlayerPed* pPlayerPed = FindPlayerPed();
			if (pPlayerPed) {
				CPlayerInfo* pPlayerInfo = pPlayerPed->GetPlayerInfoForThisPlayerPed();
				if (pPlayerInfo)
					pPlayerPed->m_fHealth = pPlayerInfo->m_nMaxHealth;
			}
		}
		if (TimeToWaitTill < CTimer::GetTimeInMilliseconds()) {
			AllowMissionReplay = MISSION_RETRY_STAGE_NORMAL;
			return;
		}
		break;
	}
	if (WaitForMissionActivate) {
		if (WaitForMissionActivate > CTimer::GetTimeInMilliseconds())
			return;
		WaitForMissionActivate = 0;
		WaitForSave = CTimer::GetTimeInMilliseconds() + 3000;
	}
	if (WaitForSave && WaitForSave > CTimer::GetTimeInMilliseconds())
		WaitForSave = 0;
#endif

#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LogBeforeScriptProcessing();
#endif

	CRunningScript* script = pActiveScripts;
	InTheScripts = true;
	while (script != nil){
		CRunningScript* next = script->GetNext();
		++ScriptsUpdated;
		script->UpdateTimers(timeStep);
		script->Process();
		script = next;
		if (script && !script->m_bIsActive)
			script = nil;
	}
	InTheScripts = false;
	for (base::cSList<script_corona>::tSItem* i = CTheScripts::mCoronas.first; i; i = i->next) {
		CCoronas::RegisterCorona((uint32)(uintptr)i, i->item.r, i->item.g, i->item.b, 255, CVector(i->item.x, i->item.y, i->item.z),
			-i->item.size, 450.0f, i->item.type, i->item.flareType, 1, 0, 0, 0.0f);
	}
	DbgFlag = false;

#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LogAfterScriptProcessing();
#endif
}

CRunningScript* CTheScripts::StartTestScript()
{
	return StartNewScript(0);
}

bool CTheScripts::IsPlayerOnAMission()
{
	return OnAMissionFlag && *(int32*)&ScriptSpace[OnAMissionFlag] == 1;
}

void CRunningScript::Process()
{
#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LogOnStartProcessing();
#endif
	pCurrent = this;
	if (m_bIsMissionScript)
		DoDeatharrestCheck();
	if (m_bMissionFlag && CTheScripts::FailCurrentMission == 1 && m_nStackPointer == 1)
		SetIP(m_anStack[--m_nStackPointer]);
	if (CTimer::GetTimeInMilliseconds() >= m_nWakeTime){
		while (!ProcessOneCommand())
			;
		return;
	}
	if (!m_bSkipWakeTime)
		return;
	if (!CPad::GetPad(0)->GetCrossJustDown())
		return;
	m_nWakeTime = 0;
	for (int i = 0; i < NUMBIGMESSAGES; i++){
		if (CMessages::BIGMessages[i].m_Stack[0].m_pText != nil)
			CMessages::BIGMessages[i].m_Stack[0].m_nStartTime = 0;
	}
	if (CMessages::BriefMessages[0].m_pText != nil)
		CMessages::BriefMessages[0].m_nStartTime = 0;
}

int8 CRunningScript::ProcessOneCommand()
{
	int8 retval = -1;
	++CTheScripts::CommandsExecuted;
	int32 command = (uint16)CTheScripts::Read2BytesFromScript(&m_nIp);
	m_bNotFlag = (command & 0x8000);
	command &= 0x7FFF;
#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LogBeforeProcessingCommand(command);
#endif

	//dbgstuff code
	//if(!strcmp(m_abScriptName, "initpla")) 
	//{
	//	debug("dbg scr\n");
	//	int t = command;
	//}

	// дублированные кейсы вручную через ProcessCommandsNToN(comm)
	// vcs todo? aCommandsHandlersPointers[command] need?? comm enum simplify but aHandlers faster

	if (command < 100)
		retval = ProcessCommands0To99(command);
	else if (command < 200)
		retval = ProcessCommands100To199(command);
	else if (command < 300)
		retval = ProcessCommands200To299(command);
	else if (command < 400)
		retval = ProcessCommands300To399(command);
	else if (command < 500)
		retval = ProcessCommands400To499(command);
	else if (command < 600)
		retval = ProcessCommands500To599(command);
	else if (command < 700)
		retval = ProcessCommands600To699(command);
	else if (command < 800)
		retval = ProcessCommands700To799(command);
	else if (command < 900)
		retval = ProcessCommands800To899(command);
	else if (command < 1000)
		retval = ProcessCommands900To999(command);
	else if (command < 1100)
		retval = ProcessCommands1000To1099(command);
	else if (command < 1200)
		retval = ProcessCommands1100To1199(command);
	else if (command < 1300)
		retval = ProcessCommands1200To1299(command);
	else if (command < 1400)
		retval = ProcessCommands1300To1399(command);
	else
		script_assert(false && "NOT FOUND COMM HANDLER");

#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
	if (!AlreadySavedGame)
#endif
	{
#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
		LogAfterProcessingCommand(command);
#elif defined USE_BASIC_SCRIPT_DEBUG_OUTPUT
		if (m_bMissionFlag) {
			char tmp[128];
			sprintf(tmp, "Comm %d Cmp %d", command, m_bCondResult);
			CDebug::DebugAddText(tmp);
		}
#endif
	}
	return retval;
}



int8 CRunningScript::ProcessCommands0To99(int32 command)
{
	float *fScriptVar1;
	//int *nScriptVar1;
	//int buff[4];
	switch(command) {
	//case COMMAND_NOP:
	//	return 0;
	case COMMAND_WAIT:
		CollectParameters(&m_nIp, 1);
		m_nWakeTime = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(0);
		m_bSkipWakeTime = false;
		return 1;
	case COMMAND_GOTO:
		CollectParameters(&m_nIp, 1);
		SetIP(GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0));
		/* Known issue: GOTO to 0. It might have been "better" to use > instead of >= */
		/* simply because it never makes sense to jump to start of the script */
		/* but jumping to start of a custom mission is an issue for simple mission-like scripts */
		/* However, it's not an issue for actual mission scripts, because they follow a structure */
		/* and never start with a loop. */
		return 0;
	case COMMAND_SHAKE_CAM:
		CollectParameters(&m_nIp, 1);
		CamShakeNoPos(&TheCamera, GET_INTEGER_PARAM(0) / 1000.0f);
		return 0;
	case COMMAND_SET_VAR_INT:
	//{ // vcs 4 5 one handler
	//	int32* ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	*ptr = GET_INTEGER_PARAM(0);
	//	return 0;
	//}
	case COMMAND_SET_VAR_FLOAT:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		//*(float *)ptr = GET_FLOAT_PARAM(0); // lcs
		*ptr = GET_INTEGER_PARAM(0); // like vcs
		return 0;
	}
	case COMMAND_SET_VAR_STRING: // it is possible to link with COMMAND_SET_VAR_INT TODO CHECK!!!!
	{
		//debug("STRING ARG!!!!!!!!!!!!!!!\n");
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*ptr = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_ADD_VAL_TO_INT_LVAR:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*ptr += GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_ADD_VAL_TO_FLOAT_LVAR:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*(float *)ptr += GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_SUB_VAL_FROM_INT_VAR:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*ptr -= GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SUB_VAL_FROM_FLOAT_VAR: // upped checked
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*(float *)ptr -= GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_MULT_INT_LVAR_BY_VAL:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*ptr *= GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_MULT_FLOAT_LVAR_BY_VAL:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*(float *)ptr *= GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_DIV_INT_LVAR_BY_VAL:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		// vcs if(!GET_INTEGER_PARAM(0)) { break(); }
		*ptr /= GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_DIV_FLOAT_LVAR_BY_VAL:
	{
		int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*(float *)ptr /= GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*ptr > GET_INTEGER_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR:
	//{
	//	CollectParameters(&m_nIp, 1);
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	UpdateCompareFlag(GET_INTEGER_PARAM(0) > *ptr);
	//	return 0;
	//}
	case COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR: // tested
	{
		// lcs [prob its equal]
		//int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
		//int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
		//UpdateCompareFlag(*ptr1 > *ptr2);

		// vcs
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(GET_INTEGER_PARAM(0) > GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*(float *)ptr > GET_FLOAT_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR:
	//{
	//	CollectParameters(&m_nIp, 1);
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	UpdateCompareFlag(GET_FLOAT_PARAM(0) > *(float *)ptr);
	//	return 0;
	//}
	case COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR: // tested
	{
		// lcs
		//int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
		//int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
		//UpdateCompareFlag(*(float *)ptr1 > *(float *)ptr2);

		// vcs
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(GET_FLOAT_PARAM(0) > GET_FLOAT_PARAM(1));
		return 0;
	}
	case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*ptr >= GET_INTEGER_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR:
	//{
	//	CollectParameters(&m_nIp, 1);
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	UpdateCompareFlag(GET_INTEGER_PARAM(0) >= *ptr);
	//	return 0;
	//}
	case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR: // tested
	{
		//int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
		//int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
		//UpdateCompareFlag(*ptr1 >= *ptr2);

		// vcs
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(GET_INTEGER_PARAM(0) >= GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*(float *)ptr >= GET_FLOAT_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR:
	//{
	//	CollectParameters(&m_nIp, 1);
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	UpdateCompareFlag(GET_FLOAT_PARAM(0) >= *(float *)ptr);
	//	return 0;
	//}
	case COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR: // tested
	{
		//int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
		//int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
		//UpdateCompareFlag(*(float *)ptr1 >= *(float *)ptr2);

		// vcs
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(GET_FLOAT_PARAM(0) >= GET_FLOAT_PARAM(1));
		return 0;
	}
	case COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*ptr == GET_INTEGER_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR:
	//{
	//	int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
	//	int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
	//	UpdateCompareFlag(*ptr1 == *ptr2);
	//	return 0;
	//}
	case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER:
	//{
	//	int32 *ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	UpdateCompareFlag(*(float *)ptr == GET_FLOAT_PARAM(0));
	//	return 0;
	//}
	case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR:
	{
		//int32 *ptr1 = GetPointerToScriptVariable(&m_nIp);
		//int32 *ptr2 = GetPointerToScriptVariable(&m_nIp);
		//UpdateCompareFlag(*(float *)ptr1 == *(float *)ptr2);

		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(!(GET_INTEGER_PARAM(0) ^ GET_INTEGER_PARAM(1))); // like strcmp
		return 0;
	}
	case COMMAND_IS_STRING_VAR_EQUAL_TO_STRING_VAR_31:
	case COMMAND_IS_STRING_VAR_EQUAL_TO_STRING_VAR_32: // tested
	{
		//script_assert(false && "TODO_OR_CHECK_todo__comm_31_32");
		//debug("STRING CMP COMM!!!!!!!!!!!!!!!\n");
		//CollectParameters(&m_nIp, 1);
		//const char *str1 = GET_INTEGER_PARAM(0) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)] : nil;
		//CollectParameters(&m_nIp, 1);
		//const char *str2 = GET_INTEGER_PARAM(0) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)] : nil;
		//bool bIsEqual = !strcmp(str1, str2);
		//UpdateCompareFlag(bIsEqual);

		CollectParameters(&m_nIp, 2);
		const char *str1 = GET_INTEGER_PARAM(0) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)] : nil;
		const char *str2 = GET_INTEGER_PARAM(1) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(1)] : nil;
		UpdateCompareFlag(!strcmp(str1, str2)); // !strcmp is equal
		return 0;
	}
	case COMMAND_GOTO_IF_TRUE:
		CollectParameters(&m_nIp, 1);
		if(m_bCondResult) SetIP(GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_GOTO_IF_FALSE:
		CollectParameters(&m_nIp, 1);
		if(!m_bCondResult) SetIP(GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0));
		/* Check COMMAND_GOTO note. */
		return 0;
	case COMMAND_TERMINATE_THIS_SCRIPT:
		if(m_bMissionFlag) CTheScripts::bAlreadyRunningAMissionScript = false;
		RemoveScriptFromList(&CTheScripts::pActiveScripts);
		AddScriptToList(&CTheScripts::pIdleScripts);
		m_bIsActive = false;
#ifdef MISSION_REPLAY // lcs, vcs todo
		if(m_bMissionFlag) {
			CPlayerInfo *pPlayerInfo = &CWorld::Players[CWorld::PlayerInFocus];
#if 0 // makeing autosave is pointless and is a bit buggy
			if (pPlayerInfo->m_pPed->GetPedState() != PED_DEAD && pPlayerInfo->m_WBState == WBSTATE_PLAYING && !m_bDeatharrestExecuted)
				SaveGameForPause(SAVE_TYPE_QUICKSAVE);
#endif
			oldTargetX = oldTargetY = 0.0f;
			if(AllowMissionReplay == MISSION_RETRY_STAGE_WAIT_FOR_SCRIPT_TO_TERMINATE) AllowMissionReplay = MISSION_RETRY_STAGE_START_PROCESSING;
			// I am fairly sure they forgot to set return value here
		}
#endif
		return 1;
	case COMMAND_START_NEW_SCRIPT:
	{
		CollectParameters(&m_nIp, 1);
		script_assert(GET_INTEGER_PARAM(0) >= 0);
		CRunningScript *pNew = CTheScripts::StartNewScript(GET_INTEGER_PARAM(0));
		CollectParameters(&m_nIp, NUM_LOCAL_VARS, pNew->m_anLocalVariables);
		return 0;
	}
	case COMMAND_GOSUB:
		CollectParameters(&m_nIp, 1);
		script_assert(m_nStackPointer < MAX_STACK_DEPTH);
		m_anStack[m_nStackPointer++] = m_nIp;
		SetIP(GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_RETURN: ReturnFromGosubOrFunction(); return 0;
	case COMMAND_LINE:
		CollectParameters(&m_nIp, 6);
		/* Something must have been here */
		return 0;
	case COMMAND_CREATE_PLAYER:
	{
		CollectParameters(&m_nIp, 4);
		int32 index = GET_INTEGER_PARAM(0);
		script_assert(index < NUMPLAYERS);
		// vcs stuff todo
		int mi = 0;
		CModelInfo::GetModelInfo(CGameLogic::mStoredPlayerOutfit, &mi); // plr3
		//for(size_t i = 0; i < 8; i++) { CGameLogic::mStoredPlayerOutfit[i]; } // todo vcs copy str outfit

		printf("&&&&&&&&&&&&&Creating player: %d\n", index);
		if(!CStreaming::HasModelLoaded(MI_PLAYER)) {
			CStreaming::RequestSpecialModel(MI_PLAYER, "player", STREAMFLAGS_DONT_REMOVE | STREAMFLAGS_DEPENDENCY);
		// vcs
		//if(!CStreaming::HasModelLoaded(mi)) {
		//	CStreaming::RequestSpecialModel(mi, "player", STREAMFLAGS_DONT_REMOVE | STREAMFLAGS_DEPENDENCY);
			CStreaming::LoadAllRequestedModels(false);
		}
		CPlayerPed::SetupPlayerPed(index);
		CWorld::Players[index].m_pPed->CharCreatedBy = MISSION_CHAR;
		CPlayerPed::DeactivatePlayerPed(index);
		CVector pos = GET_VECTOR_PARAM(1);
		if(pos.z <= MAP_Z_LOW_LIMIT) pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += CWorld::Players[index].m_pPed->GetDistanceFromCentreOfMassToBaseOfModel();
		CWorld::Players[index].m_pPed->SetPosition(pos);
		CTheScripts::ClearSpaceForMissionEntity(pos, CWorld::Players[index].m_pPed);
		CPlayerPed::ReactivatePlayerPed(index);
		index = CPools::GetPedPool()->GetIndex(CWorld::Players[index].m_pPed); // vcs
		SET_INTEGER_PARAM(0, index);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_INT_LVAR_TO_INT_LVAR:
	{
		//nScriptVar1 = GetPointerToScriptVariable(&m_nIp);
		//*nScriptVar1 += *GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(7); // header duplicate
	}
	case COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR:
	{
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 += *(float*)GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(8); // header duplicate
	}
	case COMMAND_SUB_INT_LVAR_FROM_INT_LVAR:
	{
		//nScriptVar1 = GetPointerToScriptVariable(&m_nIp);
		//*nScriptVar1 -= *GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(9); // header duplicate
	}
	case COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR:
	{
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 -= *(float*)GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(10); // header duplicate
	}
	case COMMAND_MULT_INT_LVAR_BY_INT_LVAR:
	{
		//nScriptVar1 = GetPointerToScriptVariable(&m_nIp);
		//*nScriptVar1 *= *GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(11); // header duplicate
	}
	case COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR:
	{
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 *= *(float*)GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(12); // header duplicate
	}
	case COMMAND_DIV_INT_LVAR_BY_INT_LVAR:
	{
		//nScriptVar1 = GetPointerToScriptVariable(&m_nIp);
		//*nScriptVar1 /= *GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(13); // header duplicate
	}
	case COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR:
	{
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 /= *(float*)GetPointerToScriptVariable(&m_nIp);
		//return 0;
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(14); // header duplicate
	}
	case COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR:
	//{
	//	int32* ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	*(float*)ptr += CTimer::GetTimeStep() * GET_FLOAT_PARAM(0);
	//	return 0;
	//}
	case COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR:
	{
		// lcs
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 += CTimer::GetTimeStep() * *(float*)GetPointerToScriptVariable(&m_nIp);
		
		//vcs
		debug("need test COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR\n");
		fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*fScriptVar1 += CTimer::GetTimeStep() * GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR:
	//{
	//	int32* ptr = GetPointerToScriptVariable(&m_nIp);
	//	CollectParameters(&m_nIp, 1);
	//	*(float*)ptr -= CTimer::GetTimeStep() * GET_FLOAT_PARAM(0);
	//	return 0;
	//}
	case COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR:
	{
		// lcs
		//fScriptVar1 = (float*)GetPointerToScriptVariable(&m_nIp);
		//*fScriptVar1 -= CTimer::GetTimeStep() * *(float*)GetPointerToScriptVariable(&m_nIp);

		// vcs
		debug("need test COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR\n");
		fScriptVar1 = (float *)GetPointerToScriptVariable(&m_nIp);
		CollectParameters(&m_nIp, 1);
		*fScriptVar1 -= CTimer::GetTimeStep() * GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_SET_VAR_INT_TO_LVAR_INT:
	//{
	//	int32* ptr = GetPointerToScriptVariable(&m_nIp);
	//	*ptr = *GetPointerToScriptVariable(&m_nIp);
	//	return 0;
	//}
	case COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT:
	{
		//float* ptr = (float*)GetPointerToScriptVariable(&m_nIp);
		//*ptr = *(float*)GetPointerToScriptVariable(&m_nIp);
		//return 0;
		//script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(4); // header duplicate, tmp no use COMMAND_SET_VAR_INT, if change only in ScriptCommands there will be a bug here
	}
	case DUPLICATE_COMMAND_55:
	{
		//script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(6); // header duplicate
	}
	case COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp);
		*ptr = *(float*)GetPointerToScriptVariable(&m_nIp);
		return 0;
	}
	case COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT:
	{
		float* ptr = (float*)GetPointerToScriptVariable(&m_nIp);
		*ptr = *GetPointerToScriptVariable(&m_nIp);
		return 0;
	}
	case COMMAND_ABS_VAR_INT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp);
		*ptr = ABS(*ptr);
		return 0;
	}
	case COMMAND_ABS_VAR_FLOAT:
	{
		float* ptr = (float*)GetPointerToScriptVariable(&m_nIp);
		*ptr = ABS(*ptr); // fabsf?
		return 0;
	}
	case COMMAND_GENERATE_RANDOM_FLOAT:
	{
		float* ptr = (float*)GetPointerToScriptVariable(&m_nIp);
		CGeneral::GetRandomNumber();
		CGeneral::GetRandomNumber();
		CGeneral::GetRandomNumber(); /* To make it EXTRA random! */
#ifdef FIX_BUGS
		*ptr = CGeneral::GetRandomNumberInRange(0.0f, 1.0f);
#else
		*ptr = CGeneral::GetRandomNumber() / 65536.0f;
		/* Between 0 and 0.5 on PC (oh well...), never used in original script. */
#endif

		return 0;
	}
	case COMMAND_GENERATE_RANDOM_INT:
		*GetPointerToScriptVariable(&m_nIp) = CGeneral::GetRandomNumber();
		return 0;
	case COMMAND_CREATE_CHAR:
	{
		CollectParameters(&m_nIp, 5);
		switch (GET_INTEGER_PARAM(1)) {
		case MI_COP:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_COP)
				SET_INTEGER_PARAM(1, COP_STREET);
			break;
		case MI_SWAT:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_COP)
				SET_INTEGER_PARAM(1, COP_SWAT);
			break;
		case MI_FBI:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_COP)
				SET_INTEGER_PARAM(1, COP_FBI);
			break;
		case MI_ARMY:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_COP)
				SET_INTEGER_PARAM(1, COP_ARMY);
			break;
		case MI_MEDIC:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_EMERGENCY)
				SET_INTEGER_PARAM(1, PEDTYPE_EMERGENCY);
			break;
		case MI_FIREMAN:
			if (GET_INTEGER_PARAM(0) == PEDTYPE_FIREMAN)
				SET_INTEGER_PARAM(1, PEDTYPE_FIREMAN);
			break;
		default:
			break;
		}
		CPed* ped;
		if (GET_INTEGER_PARAM(0) == PEDTYPE_COP)
			ped = new CCopPed((eCopType)GET_INTEGER_PARAM(1));
		else if (GET_INTEGER_PARAM(0) == PEDTYPE_EMERGENCY || GET_INTEGER_PARAM(0) == PEDTYPE_FIREMAN)
			ped = new CEmergencyPed(GET_INTEGER_PARAM(1));
		else
			ped = new CCivilianPed((ePedType)GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		ped->CharCreatedBy = MISSION_CHAR;
		ped->bRespondsToThreats = false;
		ped->bAllowMedicsToReviveMe = false;
		ped->bIsPlayerFriend = false;
		CVector pos = GET_VECTOR_PARAM(2);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += 1.0f;
		ped->SetPosition(pos);
		ped->SetOrientation(0.0f, 0.0f, 0.0f);
		CTheScripts::ClearSpaceForMissionEntity(pos, ped);
		if (m_bIsMissionScript)
			ped->bIsStaticWaitingForCollision = true;
		CWorld::Add(ped);
		ped->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pos);
		// VCS TODO: FUNC PED WITH SOME FLAGS NEED RE------------------------------------------------------------------------------------
		CPopulation::ms_nTotalMissionPeds++;
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(ped));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_DELETE_CHAR:
	{
		CollectParameters(&m_nIp, 1);

		// lcs
		//CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		//CTheScripts::RemoveThisPed(ped);

		// vcs
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if(ped)
		{
			if(!ped->IsPlayer())
			{
				CTheScripts::RemoveThisPed(ped);
				if (m_bIsMissionScript)
					CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
			}
		}
		return 0;
	}
	case COMMAND_CHAR_WANDER_DIR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		ped->ClearAll();
		int8 path = GET_INTEGER_PARAM(1);
		if (GET_INTEGER_PARAM(1) < 0 || GET_INTEGER_PARAM(1) > 7)
			// Max number GetRandomNumberInRange returns is max-1
#ifdef FIX_BUGS
			path = CGeneral::GetRandomNumberInRange(0, 8);
#else
			path = CGeneral::GetRandomNumberInRange(0, 7);
#endif

		ped->SetWanderPath(path);
		return 0;
	}
	case COMMAND_CHAR_FOLLOW_PATH:
	{
		CollectParameters(&m_nIp, 6);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		if (ped->GetPedState() == PED_ATTACK || ped->GetPedState() == PED_FIGHT || !ped->IsPedInControl())
			return 0;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = GET_FLOAT_PARAM(4);
		eMoveState state;
		switch (GET_INTEGER_PARAM(5)) {
		case 0: state = PEDMOVE_WALK; break;
		case 1: state = PEDMOVE_RUN; break;
		default: state = PEDMOVE_WALK; break;
		}
		ped->ClearAll();
		ped->m_pathNodeTimer = 0;
		ped->SetFollowPath(pos, radius, state, nil, nil, 999999);
		return 0;
	}
	case COMMAND_CHAR_SET_IDLE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		ped->bScriptObjectiveCompleted = false;
		ped->SetObjective(OBJECTIVE_WAIT_ON_FOOT);
		return 0;
	}
	case COMMAND_GET_CHAR_COORDINATES:
	{
		CollectParameters(&m_nIp, 1);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		CVehicle* vehicle;
		CVector pos;
		/* Seems a bit clumsy but I'll leave original flow */
		if (ped->bInVehicle)
			vehicle = ped->m_pMyVehicle;
		else
			vehicle = nil;
		if (vehicle)
			pos = vehicle->GetPosition();
		else
			pos = ped->GetPosition();
		SET_VECTOR_PARAM(0, pos);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_CHAR_COORDINATES:
	{
		CollectParameters(&m_nIp, 4);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		CVehicle* vehicle;
		if (ped->bInVehicle)
			vehicle = ped->m_pMyVehicle;
		else
			vehicle = nil;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT) // -250.0 ?
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		// removed dumb stuff again
		if (!vehicle) {
			pos.z += ped->GetDistanceFromCentreOfMassToBaseOfModel();
			ped->Teleport(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, ped);
			for (int i = 0; i < ped->m_numNearPeds; i++) {
				CPed* pNearPed = ped->m_nearPeds[i];
				if (pNearPed->m_leader == ped) {
					pNearPed->Teleport(pos);
					pNearPed->PositionAnyPedOutOfCollision();
				}
			}
		}
		else {
			pos.z += vehicle->GetDistanceFromCentreOfMassToBaseOfModel();
			vehicle->Teleport(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, vehicle);
		}
		return 0;
	}
	case COMMAND_IS_CHAR_STILL_ALIVE: // vcs probably done, need testing
	{
		// lcs COMMAND_IS_CHAR_STILL_ALIVE+COMMAND_IS_PLAYER_STILL_ALIVE/
		CollectParameters(&m_nIp, 1);
		//lcs
		//CPed *ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		//UpdateCompareFlag(ped && !ped->DyingOrDead());

		//script_assert(false && "TODO COMMAND_IS_CHAR_STILL_ALIVE CPLAYERINFO FLAG");
		//GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		//script_assert(ped); // can not found
		// or this, but need RECODE TO PLINFO
		//UpdateCompareFlag(ped && ((ped->IsPlayer() && (CWorld::Players[GET_INT_RECODE_TO_PLINFO_ARAM(0)].m_WBState != WBSTATE_WASTED)) || ((!ped->IsPlayer()) && (!ped->DyingOrDead()))));
		bool cmp = false; // ida style
		if(ped) {
			if(ped->IsPlayer()) 
			{
				CPlayerInfo *pPlayerInfo = ((CPlayerPed *)ped)->GetPlayerInfoForThisPlayerPed();
				script_assert(pPlayerInfo);
				//cmp = (CWorld::Players[GET_INTEGER_PARAM(0)].m_WBState != WBSTATE_WASTED); // wrong, in vcs h is no player in focus, its pool index !!
				cmp = (pPlayerInfo->m_WBState != WBSTATE_WASTED);
			} // COMMAND_IS_PLAYER_STILL_ALIVE
			else { cmp = (!ped->DyingOrDead()); } // COMMAND_IS_CHAR_STILL_ALIVE
		}
		UpdateCompareFlag(cmp);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_AREA_2D:
	{
		CollectParameters(&m_nIp, 6);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		CVehicle* vehicle;
		if (ped->bInVehicle)
			vehicle = ped->m_pMyVehicle;
		else
			vehicle = nil;
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		if (vehicle)
			UpdateCompareFlag(ped->m_pMyVehicle->IsWithinArea(x1, y1, x2, y2));
		else
			UpdateCompareFlag(ped->IsWithinArea(x1, y1, x2, y2));
		if (GET_INTEGER_PARAM(5))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, MAP_Z_LOW_LIMIT);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugSquare(x1, y1, x2, y2);
		*/
		return 0;
	}
	case COMMAND_IS_CHAR_IN_AREA_3D:
	{
		CollectParameters(&m_nIp, 8);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		CVehicle* vehicle;
		if (ped->bInVehicle)
			vehicle = ped->m_pMyVehicle;
		else
			vehicle = nil;
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float z1 = GET_FLOAT_PARAM(3);
		float x2 = GET_FLOAT_PARAM(4);
		float y2 = GET_FLOAT_PARAM(5);
		float z2 = GET_FLOAT_PARAM(6);
		if (vehicle)
			UpdateCompareFlag(ped->m_pMyVehicle->IsWithinArea(x1, y1, z1, x2, y2, z2));
		else
			UpdateCompareFlag(ped->IsWithinArea(x1, y1, z1, x2, y2, z2));
		if (GET_INTEGER_PARAM(7))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, (z1 + z2) / 2);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugCube(x1, y1, z1, x2, y2, z2);
		*/
		return 0;
	}
	case COMMAND_CREATE_CAR:
	{
		debug("!!!!!!!!!! create car need re some subs\n");
		CollectParameters(&m_nIp, 4);
		int32 handle;
		if (CModelInfo::IsBoatModel(GET_INTEGER_PARAM(0))) {
/*#ifdef MAZAHAKA_TMP_FIX_MAIN_SCM_ERRORS_IN_CODE
			// mazahaka tmp main.scm fixes
			if(CTheScripts::pActiveScripts && CTheScripts::pActiveScripts->m_abScriptName && (!strcmp(CTheScripts::pActiveScripts->m_abScriptName, "salh5")))
			{
				CStreaming::RequestModel(GET_INTEGER_PARAM(0), 0); // StreamFlags::STREAMFLAGS_DONT_REMOVE
				CStreaming::LoadAllRequestedModels(false);
			}
#endif*/
			CBoat* boat = new CBoat(GET_INTEGER_PARAM(0), MISSION_VEHICLE);
			CVector pos = GET_VECTOR_PARAM(1);
			if (pos.z <= MAP_Z_LOW_LIMIT)
				pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
			pos.z += boat->GetDistanceFromCentreOfMassToBaseOfModel();
			boat->SetPosition(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, boat);
			boat->SetStatus(STATUS_ABANDONED);
			boat->bIsLocked = true;
			boat->AutoPilot.m_nCarMission = MISSION_NONE;
			boat->AutoPilot.m_nTempAction = TEMPACT_NONE;
			boat->AutoPilot.m_nCruiseSpeed = boat->AutoPilot.m_fMaxTrafficSpeed = 20.0f;
			if (m_bIsMissionScript)
				boat->bIsStaticWaitingForCollision = true;
			CWorld::Add(boat);
			handle = CPools::GetVehiclePool()->GetIndex(boat);
/*#ifdef MAZAHAKA_TMP_FIX_MAIN_SCM_ERRORS_IN_CODE
			// mazahaka tmp main.scm fixes
			if(CTheScripts::pActiveScripts && CTheScripts::pActiveScripts->m_abScriptName && (!strcmp(CTheScripts::pActiveScripts->m_abScriptName, "salh5")))
			{ // bug explosion
				//exit(0); // test
				//boat->bExplosionProof = 1; // all boats in this mission exproof
				//CStreaming::RequestModel(GET_INTEGER_PARAM(0), 0); // StreamFlags::STREAMFLAGS_DONT_REMOVE
				//CStreaming::LoadAllRequestedModels(false);
#ifdef MAZAHAKA_MISC
				//if(1) { boat->m_bIsBlowProof = 1; } // if its our car
#endif
			}
#endif*/
		}
		else {
			CVehicle* car;

			if (!CModelInfo::IsBikeModel(GET_INTEGER_PARAM(0)))
				car = new CAutomobile(GET_INTEGER_PARAM(0), MISSION_VEHICLE);
			else {
				car = new CBike(GET_INTEGER_PARAM(0), MISSION_VEHICLE);
				((CBike*)(car))->bIsStanding = true;
			}
			CVector pos = GET_VECTOR_PARAM(1);
			if (pos.z <= MAP_Z_LOW_LIMIT)
				pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
			pos.z += car->GetDistanceFromCentreOfMassToBaseOfModel();
			car->SetPosition(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, car);
			car->SetStatus(STATUS_ABANDONED);
			car->bIsLocked = true;
			CCarCtrl::JoinCarWithRoadSystem(car);
			car->AutoPilot.m_nCarMission = MISSION_NONE;
			car->AutoPilot.m_nTempAction = TEMPACT_NONE;
			car->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_STOP_FOR_CARS;
			car->AutoPilot.m_nCruiseSpeed = car->AutoPilot.m_fMaxTrafficSpeed = 9.0f;
			car->AutoPilot.m_nCurrentLane = car->AutoPilot.m_nNextLane = 0;
			car->bEngineOn = false;
			car->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pos); // TODO: gpTheZones
			car->bHasBeenOwnedByPlayer = true;
			if (m_bIsMissionScript)
				car->bIsStaticWaitingForCollision = true;
			CWorld::Add(car);
			handle = CPools::GetVehiclePool()->GetIndex(car);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
#ifdef GTA_NETWORK
		// TODO(LCS): register car
#endif
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(handle, CLEANUP_CAR);
		return 0;
	}
	case COMMAND_DELETE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (car) {
			CWorld::Remove(car);
			CWorld::RemoveReferencesToDeletedObject(car);
			delete car;
		}
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CAR);
		return 0;
	}
	case COMMAND_CAR_GOTO_COORDINATES:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += car->GetDistanceFromCentreOfMassToBaseOfModel();
		uint8 nOldMission = car->AutoPilot.m_nCarMission;
		if (CCarCtrl::JoinCarWithRoadSystemGotoCoors(car, pos, false))
			car->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_STRAIGHT;
		else
			car->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS;
		car->SetStatus(STATUS_PHYSICS);
		car->bEngineOn = true;
		car->AutoPilot.m_nCruiseSpeed = Max(1, car->AutoPilot.m_nCruiseSpeed);
		if (nOldMission != car->AutoPilot.m_nCarMission)
			car->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	case COMMAND_CAR_WANDER_RANDOMLY:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		CCarCtrl::JoinCarWithRoadSystem(car);
		car->AutoPilot.m_nCarMission = MISSION_CRUISE;
		car->bEngineOn = true;
		car->AutoPilot.m_nCruiseSpeed = Max(1, car->AutoPilot.m_nCruiseSpeed);
		car->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	case COMMAND_CAR_SET_IDLE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		car->AutoPilot.m_nCarMission = MISSION_NONE;
		return 0;
	}
	case COMMAND_GET_CAR_COORDINATES:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		SET_VECTOR_PARAM(0, car->GetPosition());
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_CAR_COORDINATES:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += car->GetDistanceFromCentreOfMassToBaseOfModel();
		car->SetIsStatic(false);
		/* Again weird usage of virtual functions. */
		if (car->IsBoat()) {
			car->Teleport(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, car);
		}
		else {
			car->Teleport(pos);
			CTheScripts::ClearSpaceForMissionEntity(pos, car);
			/* May the following be inlined CCarCtrl function? */
			switch (car->AutoPilot.m_nCarMission) {
			case MISSION_CRUISE:
				CCarCtrl::JoinCarWithRoadSystem(car);
				break;
			case MISSION_RAMPLAYER_FARAWAY:
			case MISSION_RAMPLAYER_CLOSE:
			case MISSION_BLOCKPLAYER_FARAWAY:
			case MISSION_BLOCKPLAYER_CLOSE:
			case MISSION_BLOCKPLAYER_HANDBRAKESTOP:
				CCarCtrl::JoinCarWithRoadSystemGotoCoors(car, FindPlayerCoors(), false);
				break;
			case MISSION_GOTOCOORDS:
			case MISSION_GOTOCOORDS_STRAIGHT:
				CCarCtrl::JoinCarWithRoadSystemGotoCoors(car, car->AutoPilot.m_vecDestinationCoors, false);
				break;
			case MISSION_GOTOCOORDS_ACCURATE:
			case MISSION_GOTO_COORDS_STRAIGHT_ACCURATE:
				CCarCtrl::JoinCarWithRoadSystemGotoCoors(car, car->AutoPilot.m_vecDestinationCoors, false);
				break;
			case MISSION_RAMCAR_FARAWAY:
			case MISSION_RAMCAR_CLOSE:
			case MISSION_BLOCKCAR_FARAWAY:
			case MISSION_BLOCKCAR_CLOSE:
			case MISSION_BLOCKCAR_HANDBRAKESTOP:
				CCarCtrl::JoinCarWithRoadSystemGotoCoors(car, car->AutoPilot.m_pTargetCar->GetPosition(), false);
				break;
			default:
				break;
			}
		}
		return 0;
	}
	case COMMAND_IS_CAR_STILL_ALIVE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(car && car->GetStatus() != STATUS_WRECKED && (car->IsBoat() || !car->bIsInWater));
		return 0;
	}
	case COMMAND_SET_CAR_CRUISE_SPEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		car->AutoPilot.m_nCruiseSpeed = Min(GET_FLOAT_PARAM(1), 60.0f * car->pHandling->Transmission.fMaxCruiseVelocity);
		return 0;
	}
	case COMMAND_SET_CAR_DRIVING_STYLE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		car->AutoPilot.m_nDrivingStyle = (uint8)GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CAR_MISSION:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* car = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(car);
		if ((uint8)GET_INTEGER_PARAM(1) != car->AutoPilot.m_nCarMission) {
			car->AutoPilot.m_nCarMission = (uint8)GET_INTEGER_PARAM(1);
			car->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		}
		// vcs CCarCtrl::JoinCarWithRoadSystem ??
		car->bEngineOn = true;
		return 0;
	}
	case COMMAND_IS_CAR_IN_AREA_2D:
	{
		CollectParameters(&m_nIp, 6);
		CVehicle* vehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(vehicle);
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		UpdateCompareFlag(vehicle->IsWithinArea(x1, y1, x2, y2));
		if (GET_INTEGER_PARAM(5))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, MAP_Z_LOW_LIMIT);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugSquare(x1, y1, x2, y2);
		*/
		return 0;
	}
	case COMMAND_IS_CAR_IN_AREA_3D:
	{
		CollectParameters(&m_nIp, 8);
		CVehicle* vehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(vehicle);
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float z1 = GET_FLOAT_PARAM(3);
		float x2 = GET_FLOAT_PARAM(4);
		float y2 = GET_FLOAT_PARAM(5);
		float z2 = GET_FLOAT_PARAM(6);
		UpdateCompareFlag(vehicle->IsWithinArea(x1, y1, z1, x2, y2, z2));
		if (GET_INTEGER_PARAM(7))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, (z1 + z2) / 2);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugCube(x1, y1, z1, x2, y2, z2);
		*/
		return 0;
	}
	case COMMAND_PRINT_BIG:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
#ifdef MISSION_REPLAY
		if (strcmp((char*)&CTheScripts::ScriptSpace[m_nIp - KEY_LENGTH_IN_SCRIPT], "M_FAIL") == 0) {
			if (AllowMissionReplay == MISSION_RETRY_STAGE_WAIT_FOR_TIMER_AFTER_RESTART)
				AllowMissionReplay = MISSION_RETRY_STAGE_NORMAL;
			if (CanAllowMissionReplay())
				AllowMissionReplay = MISSION_RETRY_STAGE_WAIT_FOR_SCRIPT_TO_TERMINATE;
		}
#endif
		CollectParameters(&m_nIp, 2);
		CMessages::AddBigMessage(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1) - 1);
		return 0;
	}
	case COMMAND_PRINT:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddMessage(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_PRINT_NOW:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddMessageJumpQ(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_PRINT_SOON:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddMessageSoon(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_CLEAR_PRINTS:
		CMessages::ClearMessages();
		return 0;
	case COMMAND_GET_TIME_OF_DAY:
		SET_INTEGER_PARAM(0, CClock::GetHours());
		SET_INTEGER_PARAM(1, CClock::GetMinutes());
		StoreParameters(&m_nIp, 2);
		return 0;
	case COMMAND_SET_TIME_OF_DAY:
		CollectParameters(&m_nIp, 2);
		CClock::SetGameClock(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_GET_MINUTES_TO_TIME_OF_DAY:
		CollectParameters(&m_nIp, 2);
		SET_INTEGER_PARAM(0, CClock::GetGameClockMinutesUntil(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_IS_POINT_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= -100)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pos, GET_FLOAT_PARAM(3)));
		return 0;
	}
	case COMMAND_RETURN_TRUE:
		UpdateCompareFlag(true);
		ReturnFromGosubOrFunction();
		return 0;
	case COMMAND_RETURN_FALSE:
		UpdateCompareFlag(false);
		ReturnFromGosubOrFunction();
		return 0;
	case COMMAND_NULL_96:
	case COMMAND_NULL_97:
	case COMMAND_NULL_98:
	case COMMAND_NULL_99:
	{
		script_assert(false && "COMMAND NULL");
		return 0;
	}

	default:
		script_assert(0);
		break;
	}
	return -1;
}

int8 CRunningScript::ProcessCommands100To199(int32 command)
{
	float *fScriptVar1;
	int *nScriptVar1;
	switch (command) {
	case COMMAND_NULL_100:
	case COMMAND_NULL_101:
	case COMMAND_NULL_102:
	case COMMAND_NULL_103:
	case COMMAND_NULL_104:
	case COMMAND_NULL_105:
	case COMMAND_NULL_106:
	case COMMAND_NULL_107:
	case COMMAND_NULL_108:
	case COMMAND_NULL_109:
	case COMMAND_NULL_110:
	case COMMAND_NULL_111:
	case COMMAND_NULL_112:
	case COMMAND_NULL_113:
	case COMMAND_NULL_114:
	case COMMAND_NULL_115:
	case COMMAND_NULL_116:
	case COMMAND_NULL_117:
	case COMMAND_NULL_118:
	case COMMAND_NULL_119:
	{
		script_assert(false && "COMMAND NULL");
		return 0;
	}
	case COMMAND_ANDOR:
		CollectParameters(&m_nIp, 1);
		m_nAndOrState = GET_INTEGER_PARAM(0);
		if (m_nAndOrState == ANDOR_NONE){
			m_bCondResult = false; // pointless
		}else if (m_nAndOrState >= ANDS_1 && m_nAndOrState <= ANDS_8){
			m_bCondResult = true;
		}else if (m_nAndOrState >= ORS_1 && m_nAndOrState <= ORS_8){
			m_bCondResult = false;
		}else{
			script_assert(0 && "COMMAND_ANDOR: invalid ANDOR state");
		}
		return 0;
	case COMMAND_LAUNCH_MISSION:
	{
		CollectParameters(&m_nIp, 1);
		CRunningScript* pNew = CTheScripts::StartNewScript(GET_INTEGER_PARAM(0));
		pNew->m_bIsMissionScript = true;
		return 0;
	}
	case COMMAND_MISSION_HAS_FINISHED:
	{
		//lcs
		//if (!m_bIsMissionScript)
		//	return 0;
		//CTheScripts::MissionCleanUp.Process();

		if(m_bIsMissionScript) { CTheScripts::MissionCleanUp.Process(); }
		return 0;
	}
	case COMMAND_STORE_CAR_CHAR_IS_IN:
	{
		CollectParameters(&m_nIp, 1);
		CPed* ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(ped);
		CVehicle* pCurrent = nil;
		if (ped->bInVehicle) {
			pCurrent = ped->m_pMyVehicle;
		}
		script_assert(pCurrent); // GetIndex(0) doesn't look good
		int handle = CPools::GetVehiclePool()->GetIndex(pCurrent);
		if (handle != CTheScripts::StoreVehicleIndex && m_bIsMissionScript){
			CVehicle* pOld = CPools::GetVehiclePool()->GetAt(CTheScripts::StoreVehicleIndex);
			if (pOld){
				CCarCtrl::RemoveFromInterestingVehicleList(pOld);
				if (pOld->VehicleCreatedBy == MISSION_VEHICLE && CTheScripts::StoreVehicleWasRandom){
					pOld->VehicleCreatedBy = RANDOM_VEHICLE;
					pOld->bIsLocked = false;
					CCarCtrl::NumRandomCars++;
					CCarCtrl::NumMissionCars--;
					CTheScripts::MissionCleanUp.RemoveEntityFromList(CTheScripts::StoreVehicleIndex, CLEANUP_CAR);
				}
			}

			CTheScripts::StoreVehicleIndex = handle;
			switch (pCurrent->VehicleCreatedBy){
			case RANDOM_VEHICLE:
				pCurrent->VehicleCreatedBy = MISSION_VEHICLE;
				CCarCtrl::NumMissionCars++;
				CCarCtrl::NumRandomCars--;
				CTheScripts::StoreVehicleWasRandom = true;
				CTheScripts::MissionCleanUp.AddEntityToList(CTheScripts::StoreVehicleIndex, CLEANUP_CAR);
				break;
			case PARKED_VEHICLE:
				pCurrent->VehicleCreatedBy = MISSION_VEHICLE;
				CCarCtrl::NumMissionCars++;
				CCarCtrl::NumParkedCars--;
				CTheScripts::StoreVehicleWasRandom = true;
				CTheScripts::MissionCleanUp.AddEntityToList(CTheScripts::StoreVehicleIndex, CLEANUP_CAR);
				break;
			case MISSION_VEHICLE:
			case PERMANENT_VEHICLE:
				CTheScripts::StoreVehicleWasRandom = false;
				break;
			default:
				break;
			}
		}
		SET_INTEGER_PARAM(0, CTheScripts::StoreVehicleIndex);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pCheckedVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CVehicle* pActualVehicle = pPed->bInVehicle ? pPed->m_pMyVehicle : nil;
		UpdateCompareFlag(pActualVehicle && pActualVehicle == pCheckedVehicle);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_MODEL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pActualVehicle = pPed->bInVehicle ? pPed->m_pMyVehicle : nil;
		UpdateCompareFlag(pActualVehicle && pActualVehicle->GetModelIndex() == GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_CHAR_IN_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle);
		return 0;
	}
	case COMMAND_IS_BUTTON_PRESSED:
	{
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(GetPadState(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)) != 0);
		return 0;
	}
	case COMMAND_LOCATE_CHAR_ANY_MEANS_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_2D:
	case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D:
	case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D:
	case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D:
		LocateCharCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D:
		LocateCharCharCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_CHAR_ANY_MEANS_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_3D:
	case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D:
	case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D:
	case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D:
		LocateCharCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D:
		LocateCharCharCommand(command, &m_nIp);
		return 0;
	case COMMAND_CREATE_OBJECT:
	{
		CollectParameters(&m_nIp, 4);
		int mi = GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::UsedObjectArray[-GET_INTEGER_PARAM(0)].index;
		CObject* pObj = new CObject(mi, false);
		pObj->ObjectCreatedBy = MISSION_OBJECT;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += pObj->GetDistanceFromCentreOfMassToBaseOfModel();
		pObj->SetPosition(pos);
		pObj->SetOrientation(0.0f, 0.0f, 0.0f);
		pObj->GetMatrix().UpdateRW();
		pObj->UpdateRwFrame();
		CTheScripts::ClearSpaceForMissionEntity(pos, pObj);
		CWorld::Add(pObj);
		SET_INTEGER_PARAM(0, CPools::GetObjectPool()->GetIndex(pObj));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_DELETE_OBJECT:
	{
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0) > (NUMOBJECTS + 2) << 8)
			return 0;
		CObject* pObj = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pObj){
			CWorld::Remove(pObj);
			CWorld::RemoveReferencesToDeletedObject(pObj);
			delete pObj;
		}
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_ADD_SCORE:
	{
		CollectParameters(&m_nIp, 2);

		// lcs
		//CWorld::Players[GET_INTEGER_PARAM(0)].m_nMoney += GET_INTEGER_PARAM(1);
		//if (CWorld::Players[GET_INTEGER_PARAM(0)].m_nMoney < 0)
		//	CWorld::Players[GET_INTEGER_PARAM(0)].m_nMoney = 0;

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));

		pPlayerInfo->m_nMoney += GET_INTEGER_PARAM(1);
		if(pPlayerInfo->m_nMoney < 0) { pPlayerInfo->m_nMoney = 0; }
		return 0;
	}
	case COMMAND_IS_SCORE_GREATER:
	{
		CollectParameters(&m_nIp, 2);
		// lcs
		//UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].m_nMoney > GET_INTEGER_PARAM(1));

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPlayerInfo->m_nMoney > GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_STORE_SCORE:
	{
		CollectParameters(&m_nIp, 1);
		// lcs
		//SET_INTEGER_PARAM(0, CWorld::Players[GET_INTEGER_PARAM(0)].m_nMoney);

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, pPlayerInfo->m_nMoney);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GIVE_REMOTE_CONTROLLED_CAR_TO_PLAYER:
	{
		CollectParameters(&m_nIp, 5);
		// vcs playerinfo macro??
		//GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CVehicle* pVehicle = CRemote::GivePlayerRemoteControlledCar(pos.x, pos.y, pos.z, DEGTORAD(GET_FLOAT_PARAM(4)), MI_RCBANDIT);
		SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex(pVehicle));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ALTER_WANTED_LEVEL:
	{
		CollectParameters(&m_nIp, 2);
		// lcs
		//CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed->SetWantedLevel(GET_INTEGER_PARAM(1));

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		pPlayerInfo->m_pPed->SetWantedLevel(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_ALTER_WANTED_LEVEL_NO_DROP:
	{
		CollectParameters(&m_nIp, 2);
		// lcs
		//CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed->SetWantedLevelNoDrop(GET_INTEGER_PARAM(1));

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		pPlayerInfo->m_pPed->SetWantedLevelNoDrop(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_WANTED_LEVEL_GREATER:
	{
		CollectParameters(&m_nIp, 2);
		// lcs
		//UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed->m_pWanted->GetWantedLevel() > GET_INTEGER_PARAM(1));

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPlayerInfo->m_pPed->m_pWanted->GetWantedLevel() > GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_CLEAR_WANTED_LEVEL:
	{
		CollectParameters(&m_nIp, 1);
		// lcs
		//CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed->SetWantedLevel(0);

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		pPlayerInfo->m_pPed->SetWantedLevel(0);
		return 0;
	}
	case COMMAND_SET_DEATHARREST_STATE:
		CollectParameters(&m_nIp, 1);
		m_bDeatharrestEnabled = (GET_INTEGER_PARAM(0) == 1);
		return 0;
	case COMMAND_HAS_DEATHARREST_BEEN_EXECUTED:
		UpdateCompareFlag(m_bDeatharrestExecuted);
		return 0;
	case COMMAND_ADD_AMMO_TO_CHAR:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->GrantAmmo((eWeaponType)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_IS_CHAR_DEAD:
	{
		CollectParameters(&m_nIp, 1);
		// lcs
		//CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		//UpdateCompareFlag(!pPed || pPed->DyingOrDead() || pPed->m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE);

		// vcs
		//script_assert(false && "TEST THIS COMMAND_IS_CHAR_DEAD");
		CPed *ped = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		bool cmp = false; // ida style
		if(ped) {
			if(ped->IsPlayer()) {
				CPlayerInfo *pPlayerInfo = ((CPlayerPed *)ped)->GetPlayerInfoForThisPlayerPed();
				script_assert(pPlayerInfo);
				cmp = pPlayerInfo && (pPlayerInfo->m_WBState == WBSTATE_WASTED);
			}
			else { cmp = (ped->DyingOrDead() || (ped->m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE)); } 
		}
		//debug("dead? : %d\n", cmp);
		UpdateCompareFlag(ped ? cmp : true); // !pPed is dead
		return 0;
	}
	case COMMAND_IS_CAR_DEAD:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(!pVehicle || pVehicle->GetStatus() == STATUS_WRECKED || pVehicle->bIsDrowning);
		return 0;
	}
	case COMMAND_SET_CHAR_THREAT_SEARCH:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_fearFlags |= GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_NO_OBJ:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->ClearObjective();
		return 0;
	}
	case COMMAND_IS_CHAR_OBJECTIVE_PASSED:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bScriptObjectiveCompleted);
		return 0;
	}
	case COMMAND_CREATE_CHAR_INSIDE_CAR:
	{
		CollectParameters(&m_nIp, 3);
		debug("ida COMMAND_CREATE_CHAR_INSIDE_CAR re some funcs\n");
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		switch (GET_INTEGER_PARAM(2)) {
		case MI_COP:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_STREET);
			break;
		case MI_SWAT:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_SWAT);
			break;
		case MI_FBI:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_FBI);
			break;
		case MI_ARMY:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_ARMY);
			break;
		case MI_MEDIC:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_EMERGENCY)
				SET_INTEGER_PARAM(2, PEDTYPE_EMERGENCY);
			break;
		case MI_FIREMAN:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_FIREMAN)
				SET_INTEGER_PARAM(2, PEDTYPE_FIREMAN);
			break;
		default:
			break;
		}
		CPed* pPed;
		if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
			pPed = new CCopPed((eCopType)GET_INTEGER_PARAM(2));
		else if (GET_INTEGER_PARAM(1) == PEDTYPE_EMERGENCY || GET_INTEGER_PARAM(1) == PEDTYPE_FIREMAN)
			pPed = new CEmergencyPed(GET_INTEGER_PARAM(2));
		else
			pPed = new CCivilianPed((ePedType)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		pPed->CharCreatedBy = MISSION_CHAR;
		pPed->bRespondsToThreats = false;
		pPed->bAllowMedicsToReviveMe = false;
		pPed->bIsPlayerFriend = false;
		if (pVehicle->bIsBus)
			pPed->bRenderPedInCar = false;
		pPed->SetPosition(pVehicle->GetPosition());
		pPed->SetOrientation(0.0f, 0.0f, 0.0f);
		pPed->SetPedState(PED_DRIVING);
		script_assert(!pVehicle->pDriver);
		pVehicle->pDriver = pPed;
		pVehicle->pDriver->RegisterReference((CEntity**)&pVehicle->pDriver);
		pPed->m_pMyVehicle = pVehicle;
		pPed->m_pMyVehicle->RegisterReference((CEntity**)&pPed->m_pMyVehicle);
		pPed->bInVehicle = true;
		pVehicle->SetStatus(STATUS_PHYSICS);
		if (!pVehicle->IsBoat())
			pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
		pVehicle->bEngineOn = true;
		pPed->bUsesCollision = false;
		pPed->AddInCarAnims(pVehicle, true);
		pPed->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pPed->GetPosition());
		CWorld::Add(pPed);
		CPopulation::ms_nTotalMissionPeds++;
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPed));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_HAS_PLAYER_BEEN_ARRESTED:
	{
		CollectParameters(&m_nIp, 1);
		// lcs
		//UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].m_WBState == WBSTATE_BUSTED);

		// vcs
		GetPlayerInfoByPoolHandler(pPlayerInfo, GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPlayerInfo->m_WBState == WBSTATE_BUSTED);
		return 0;
	}
	case COMMAND_IS_CAR_MODEL:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() == GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_GIVE_CAR_ALARM:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_nAlarmState = -1;
		return 0;
	}
	case COMMAND_IS_CAR_CRUSHED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::HasCarBeenCrushed(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_CREATE_CAR_GENERATOR:
	{
		CollectParameters(&m_nIp, 12);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z > MAP_Z_LOW_LIMIT)
			pos.z += 0.015f;
		SET_INTEGER_PARAM(0, CTheCarGenerators::CreateCarGenerator(
			pos.x, pos.y, pos.z, GET_FLOAT_PARAM(3),
			GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7),
			GET_INTEGER_PARAM(8), GET_INTEGER_PARAM(9), GET_INTEGER_PARAM(10), GET_INTEGER_PARAM(11)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SWITCH_CAR_GENERATOR:
	{
		CollectParameters(&m_nIp, 2);
		CCarGenerator* pCarGen = &CTheCarGenerators::CarGeneratorArray[GET_INTEGER_PARAM(0)];
		if (GET_INTEGER_PARAM(1) == 0) {
			pCarGen->SwitchOff();
		}
		else if (GET_INTEGER_PARAM(1) <= 100) {
			pCarGen->SwitchOn();
			pCarGen->SetUsesRemaining(GET_INTEGER_PARAM(1));
		}
		else {
			pCarGen->SwitchOn();
		}
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER:
	{
		uint16 offset = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.AddClock(offset, nil, GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_CLEAR_ONSCREEN_TIMER:
	{
		uint16 offset = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CUserDisplay::OnscnTimer.ClearClock(offset);
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_COUNTER:
	{
		uint16 counter = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.AddCounter(counter, GET_INTEGER_PARAM(0), nil, 0, -1, nil, 0);
		return 0;
	}
	case COMMAND_CLEAR_ONSCREEN_COUNTER:
	{
		uint16 counter = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CUserDisplay::OnscnTimer.ClearCounter(counter);
		return 0;
	}
	case COMMAND_SET_ZONE_CAR_INFO:
	{
		int16 gangDensities[NUM_GANGS] = { 0 };
		int i;

		// lcs
		//char label[12];
		//CTheScripts::ReadTextLabelFromScript(&m_nIp, label);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;

		//vcs
		const char *label = GetKeyFromScript(&m_nIp);
		//script_assert(false && "NEED TEST");

		CollectParameters(&m_nIp, 12);
		for (i = 0; i < NUM_GANGS; i++)
			gangDensities[i] = ScriptParams[i + 2];
		int zone = CTheZones::FindZoneByLabelAndReturnIndex((char*)label, ZONE_INFO);
		for (int i = 0; i < NUM_GANGS; i++) {
			if (gangDensities[i] != 0 && CGangs::GetGangInfo(i)->m_nVehicleMI == -1)
				debug("SET_ZONE_CAR_INFO - Gang %d car ratio should be 0 in %s zone\n", i + 1, label);
		}
		if (zone < 0) {
			debug("Couldn't find zone - %s\n", label);
			return 0;
		}
		while (zone >= 0) {
			CTheZones::SetZoneCarInfo(zone, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(11), gangDensities);
			zone = CTheZones::FindNextZoneByLabelAndReturnIndex((char*)label, ZONE_INFO);
		}
		return 0;
	}
	case COMMAND_IS_CHAR_IN_ZONE: // navig.zon ??
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);

		// lcs
		//char label[12];
		//CTheScripts::ReadTextLabelFromScript(&m_nIp, label);
		//int zone = CTheZones::FindZoneByLabelAndReturnIndex(label, ZONE_DEFAULT);
		//if (zone != -1)
		//	m_nIp += KEY_LENGTH_IN_SCRIPT;

		//vcs
		const char *label = GetKeyFromScript(&m_nIp);
		//const char *label = (const char*)GetPointerToScriptVariable(&m_nIp);
		int zone = CTheZones::FindZoneByLabelAndReturnIndex((char*)label, ZONE_DEFAULT);
		script_assert(zone != -1);
		//script_assert(false && "NEED TEST");
		debug("NEED TEST  COMMAND_IS_CHAR_IN_ZONE\n");

		CVector pos = pPed->bInVehicle ? pPed->m_pMyVehicle->GetPosition() : pPed->GetPosition();
		UpdateCompareFlag(CTheZones::PointLiesWithinZone(&pos, CTheZones::GetNavigationZone(zone)));
		return 0;
	}
	case COMMAND_SET_CAR_DENSITY:
	{
		char label[12];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, label);
		int16 zone = CTheZones::FindZoneByLabelAndReturnIndex(label, ZONE_INFO);
		m_nIp += 8;
		CollectParameters(&m_nIp, 2);
		if (zone < 0) {
			debug("Couldn't find zone - %s\n", label);
			return 0;
		}
		while (zone >= 0) {
			CTheZones::SetCarDensity(zone, ScriptParams[0], ScriptParams[1]);
			zone = CTheZones::FindNextZoneByLabelAndReturnIndex(label, ZONE_INFO);
		}
		return 0;
	}
	case COMMAND_SET_PED_DENSITY:
	{
		char label[12];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, label);
		int16 zone = CTheZones::FindZoneByLabelAndReturnIndex(label, ZONE_INFO);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CollectParameters(&m_nIp, 2);
		if (zone < 0) {
			debug("Couldn't find zone - %s\n", label);
			return 0;
		}
		while (zone >= 0) {
			CTheZones::SetPedDensity(zone, ScriptParams[0], ScriptParams[1]);
			zone = CTheZones::FindNextZoneByLabelAndReturnIndex(label, ZONE_INFO);
		}
		return 0;
	}
	case COMMAND_POINT_CAMERA_AT_PLAYER:
	{
		CollectParameters(&m_nIp, 3);
		TheCamera.TakeControl(nil, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), CAMCONTROL_SCRIPT);
		return 0;
	}
	case COMMAND_POINT_CAMERA_AT_CAR:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle)
			TheCamera.TakeControl(pVehicle, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), CAMCONTROL_SCRIPT);
		return 0;
	}
	case COMMAND_POINT_CAMERA_AT_CHAR:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			TheCamera.TakeControl(pPed, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), CAMCONTROL_SCRIPT);
		return 0;
	}
	case COMMAND_RESTORE_CAMERA:
		TheCamera.Restore();
		return 0;
	case COMMAND_SET_ZONE_PED_INFO:
	{
		// lcs
		//char label[12];
		//CTheScripts::ReadTextLabelFromScript(&m_nIp, label);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;

		//vcs
		const char *label = GetKeyFromScript(&m_nIp);

		CollectParameters(&m_nIp, 12);
		int16 zone = CTheZones::FindZoneByLabelAndReturnIndex((char*)label, ZONE_INFO);
		if (zone < 0) {
			debug("Couldn't find zone - %s\n", label);
			return 0;
		}
		while (zone >= 0) {
			CTheZones::SetZonePedInfo(zone, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3),
				GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8), GET_INTEGER_PARAM(9), GET_INTEGER_PARAM(10), GET_INTEGER_PARAM(11));
			zone = CTheZones::FindNextZoneByLabelAndReturnIndex((char*)label, ZONE_INFO);
		}
		return 0;
	}
	case COMMAND_SET_TIME_SCALE:
		CollectParameters(&m_nIp, 1);
		CTimer::SetTimeScale(GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_SET_FIXED_CAMERA_POSITION:
	{
		CollectParameters(&m_nIp, 6);
		TheCamera.SetCamPositionForFixedMode(
			CVector(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)),
			CVector(GET_FLOAT_PARAM(3), GET_FLOAT_PARAM(4), GET_FLOAT_PARAM(5)));
		return 0;
	}
	case COMMAND_POINT_CAMERA_AT_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		TheCamera.TakeControlNoEntity(pos, GET_INTEGER_PARAM(3), CAMCONTROL_SCRIPT);
		return 0;
	}
	case COMMAND_REMOVE_BLIP:
		CollectParameters(&m_nIp, 1);
		CRadar::ClearBlip(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CHANGE_BLIP_COLOUR:
		CollectParameters(&m_nIp, 2);
		CRadar::ChangeBlipColour(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_DIM_BLIP:
		CollectParameters(&m_nIp, 2);
		CRadar::ChangeBlipBrightness(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_ADD_BLIP_FOR_COORD_OLD:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CRadar::SetCoordBlip(BLIP_COORD, pos, GET_INTEGER_PARAM(3), (eBlipDisplay)GET_INTEGER_PARAM(4)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_CHANGE_BLIP_SCALE:
		CollectParameters(&m_nIp, 2);
		CRadar::ChangeBlipScale(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_ADD_BLIP_FOR_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int handle = CRadar::SetEntityBlip(BLIP_CAR, GET_INTEGER_PARAM(0), 0, BLIP_DISPLAY_BOTH);
		CRadar::ChangeBlipScale(handle, 3);
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_BLIP_FOR_CHAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int handle = CRadar::SetEntityBlip(BLIP_CHAR, GET_INTEGER_PARAM(0), 1, BLIP_DISPLAY_BOTH);
		CRadar::ChangeBlipScale(handle, 3);
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_BLIP_FOR_OBJECT:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int handle = CRadar::SetEntityBlip(BLIP_OBJECT, GET_INTEGER_PARAM(0), 6, BLIP_DISPLAY_BOTH);
		CRadar::ChangeBlipScale(handle, 3);
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_BLIP_FOR_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int handle = CRadar::SetCoordBlip(BLIP_COORD, pos, 5, BLIP_DISPLAY_BOTH);
		CRadar::ChangeBlipScale(handle, 3);
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_CHANGE_BLIP_DISPLAY:
		CollectParameters(&m_nIp, 2);
		CRadar::ChangeBlipDisplay(GET_INTEGER_PARAM(0), (eBlipDisplay)GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_ADD_SPRITE_BLIP_FOR_CONTACT_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetCoordBlip(BLIP_CONTACT_POINT, pos, 2, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_SPRITE_BLIP_FOR_COORD:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetCoordBlip(BLIP_COORD, pos, 4, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_COORD:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetShortRangeCoordBlip(BLIP_COORD, pos, 5, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}

	default:
		script_assert(0);
		break;
	}
	return -1;
}

int8 CRunningScript::ProcessCommands200To299(int32 command)
{
	switch (command) {
	case COMMAND_SET_FADING_COLOUR:
		CollectParameters(&m_nIp, 3);
		TheCamera.SetFadeColour(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_DO_FADE:
	{
		// unknown empty call on PS2, not mobile
		CollectParameters(&m_nIp, 2);
		float fFadeTime = GET_INTEGER_PARAM(0);
		TheCamera.Fade(fFadeTime > 2 ? fFadeTime / 1000.0f : 0.0f, GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_GET_FADING_STATUS:
		UpdateCompareFlag(TheCamera.GetFading());
		return 0;
	case COMMAND_ADD_HOSPITAL_RESTART:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		float angle = GET_FLOAT_PARAM(3);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRestart::AddHospitalRestartPoint(pos, angle);
		return 0;
	}
	case COMMAND_ADD_POLICE_RESTART:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		float angle = GET_FLOAT_PARAM(3);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRestart::AddPoliceRestartPoint(pos, angle);
		return 0;
	}
	case COMMAND_OVERRIDE_NEXT_RESTART:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		float angle = GET_FLOAT_PARAM(3);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRestart::OverrideNextRestart(pos, angle);
		return 0;
	}
	case COMMAND_GET_CHAR_HEADING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float angle = pPed->bInVehicle ? pPed->m_pMyVehicle->GetForward().Heading() : pPed->GetForward().Heading();
		angle = RADTODEG(angle);
		if (angle < 0.0f)
			angle += 360.0f;
		if (angle > 360.0f)
			angle -= 360.0f;
		SET_FLOAT_PARAM(0, angle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_HEADING:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (pPed->bInVehicle)
			return 0;
		pPed->m_fRotationDest = pPed->m_fRotationCur = DEGTORAD(GET_FLOAT_PARAM(1));
		pPed->SetHeading(DEGTORAD(GET_FLOAT_PARAM(1)));
		return 0;
	}
	case COMMAND_GET_CAR_HEADING:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		float angle = pVehicle->GetForward().Heading();
		angle = RADTODEG(angle);
		if (angle < 0.0f)
			angle += 360.0f;
		if (angle > 360.0f)
			angle -= 360.0f;
		SET_FLOAT_PARAM(0, angle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CAR_HEADING:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->SetHeading(DEGTORAD(GET_FLOAT_PARAM(1)));
		return 0;
	}
	case COMMAND_GET_OBJECT_HEADING:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		float angle = pObject->GetForward().Heading();
		angle = RADTODEG(angle);
		if (angle < 0.0f)
			angle += 360.0f;
		if (angle > 360.0f)
			angle -= 360.0f;
		SET_FLOAT_PARAM(0, angle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_OBJECT_HEADING:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CWorld::Remove(pObject);
		pObject->SetHeading(DEGTORAD(GET_FLOAT_PARAM(1)));
		pObject->GetMatrix().UpdateRW();
		pObject->UpdateRwFrame();
		CWorld::Add(pObject);
		return 0;
	}
	case COMMAND_IS_CHAR_TOUCHING_OBJECT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[1]);
		script_assert(pObject);
		CPhysical* pEntityToTest = pPed->bInVehicle ? (CPhysical*)pPed->m_pMyVehicle : pPed;
		UpdateCompareFlag(pEntityToTest->GetHasCollidedWith(pObject));
		return 0;
	}
	case COMMAND_SET_CHAR_AMMO:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		pPed->SetAmmo((eWeaponType)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_DECLARE_MISSION_FLAG:
		CTheScripts::OnAMissionFlag = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		return 0;
	case COMMAND_IS_CHAR_HEALTH_GREATER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->m_fHealth > GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_CAR_HEALTH_GREATER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->m_fHealth > GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_ADD_ONE_OFF_SOUND:
	{
		CollectParameters(&m_nIp, 4);
		debug("TODO: COMMAND_ADD_ONE_OFF_SOUND\n");
		switch (GET_INTEGER_PARAM(3)) {
		case SCRIPT_SOUND_PART_MISSION_COMPLETE:
			DMAudio.PlayFrontEndSound(SOUND_PART_MISSION_COMPLETE, 0);
			return 0;
		case SCRIPT_SOUND_RACE_START_3:
			DMAudio.PlayFrontEndSound(SOUND_RACE_START_3, 0);
			return 0;
		case SCRIPT_SOUND_RACE_START_2:
			DMAudio.PlayFrontEndSound(SOUND_RACE_START_2, 0);
			return 0;
		case SCRIPT_SOUND_RACE_START_1:
			DMAudio.PlayFrontEndSound(SOUND_RACE_START_1, 0);
			return 0;
		case SCRIPT_SOUND_RACE_START_GO:
			DMAudio.PlayFrontEndSound(SOUND_RACE_START_GO, 0);
			return 0;
		case SCRIPT_SOUND_AMMUNATION_BUY_WEAPON:
			DMAudio.PlayFrontEndSound(SOUND_PICKUP_WEAPON_BOUGHT, 0);
			return 0;
		case SCRIPT_SOUND_AMMUNATION_BUY_WEAPON_DENIED:
			DMAudio.PlayFrontEndSound(SOUND_GARAGE_NO_MONEY, 0);
			return 0;
		case SCRIPT_SOUND_IMRAN_ARM_BOMB:
			DMAudio.PlayFrontEndSound(SOUND_AMMUNATION_IMRAN_ARM_BOMB, 0);
			return 0;
		case 0x46: // TODO
			DMAudio.PlayFrontEndSound(0xC4, 0);
			return 0;
		case 0x47: // TODO
			DMAudio.PlayFrontEndSound(0xCD, 0);
			return 0;
		default:
			break;
		}
		if (!DMAudio.IsAudioInitialised()) // LCS doesn't have it. Why?
			return 0;
		cAudioScriptObject* obj = new cAudioScriptObject();
		obj->Posn = GET_VECTOR_PARAM(0);
		obj->AudioId = GET_INTEGER_PARAM(3);
		obj->AudioEntity = AEHANDLE_NONE;
		DMAudio.CreateOneShotScriptObject(obj);
		return 0;
	}
	case COMMAND_ADD_CONTINUOUS_SOUND:
	{
		CollectParameters(&m_nIp, 4);
		if (DMAudio.IsAudioInitialised()) {  // LCS doesn't have it. Why?
			cAudioScriptObject* obj = new cAudioScriptObject();
			obj->Posn = GET_VECTOR_PARAM(0);
			obj->AudioId = GET_INTEGER_PARAM(3);
			obj->AudioEntity = DMAudio.CreateLoopingScriptObject(obj);
			SET_INTEGER_PARAM(0, CPools::GetAudioScriptObjectPool()->GetIndex(obj));
		}
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_REMOVE_SOUND:
	{
		CollectParameters(&m_nIp, 1);
		cAudioScriptObject* obj = CPools::GetAudioScriptObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		if (!obj) {
			debug("REMOVE_SOUND - Sound doesn't exist\n");
			return 0;
		}
		DMAudio.DestroyLoopingScriptObject(obj->AudioEntity);
		delete obj;
		return 0;
	}
	case COMMAND_IS_CAR_STUCK_ON_ROOF:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(CTheScripts::UpsideDownCars.HasCarBeenUpsideDownForAWhile(GET_INTEGER_PARAM(0)));
		return 0;
	}
	case COMMAND_ADD_UPSIDEDOWN_CAR_CHECK:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CTheScripts::UpsideDownCars.AddCarToCheck(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_REMOVE_UPSIDEDOWN_CAR_CHECK:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CTheScripts::UpsideDownCars.RemoveCarFromCheck(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_WAIT_ON_FOOT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_WAIT_ON_FOOT);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_FLEE_ON_FOOT_TILL_SAFE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GUARD_SPOT:
	{
		CollectParameters(&m_nIp, 4);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GUARD_SPOT, pos);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GUARD_AREA:
	{
		CollectParameters(&m_nIp, 5);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float infX = GET_FLOAT_PARAM(1);
		float infY = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GUARD_SPOT, pos, radius);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_WAIT_IN_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_WAIT_IN_CAR);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, pTarget);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_KILL_CHAR_ANY_MEANS, pTarget);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS, pTarget);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GOTO_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_CHAR_ON_FOOT, pTarget);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_LEAVE_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_LEAVE_CAR, pVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, pVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_DRIVER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, pVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_DESTROY_OBJECT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_DESTROY_OBJECT, pObject);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_DESTROY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_DESTROY_CAR, pVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ON_FOOT:
	{
		CollectParameters(&m_nIp, 5);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float infX = GET_FLOAT_PARAM(1);
		float infY = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_AREA_ON_FOOT, pos, radius);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector target;
		target.x = GET_FLOAT_PARAM(1);
		target.y = GET_FLOAT_PARAM(2);
		target.z = CWorld::FindGroundZForCoord(target.x, target.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_AREA_ON_FOOT, target);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FOLLOW_CHAR_IN_FORMATION, pTargetPed);
		pPed->SetFormation((eFormation)GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_STEAL_ANY_CAR);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_LEAVE_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_LEAVE_CAR, pPed->m_pMyVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_FLEE_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FLEE_CAR, pVehicle);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_WALK_TO_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTargetPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING, pTargetPed);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_AIM_GUN_AT_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTargetPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_AIM_GUN_AT, pTargetPed);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_SPRINT_TO_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector pos;
		pos.x = GET_FLOAT_PARAM(1);
		pos.y = GET_FLOAT_PARAM(2);
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_SPRINT_TO_AREA, pos);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_2D:
	case COMMAND_IS_CHAR_IN_AREA_IN_CAR_2D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_2D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_2D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_2D:
	case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_3D:
	case COMMAND_IS_CHAR_IN_AREA_IN_CAR_3D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_3D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_3D:
	case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_3D:
		CharInAreaCheckCommand(command, &m_nIp);
		return 0;
	case COMMAND_IS_CAR_STOPPED_IN_AREA_2D:
	case COMMAND_IS_CAR_STOPPED_IN_AREA_3D:
		CarInAreaCheckCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_CAR_2D:
	case COMMAND_LOCATE_STOPPED_CAR_2D:
	case COMMAND_LOCATE_CAR_3D:
	case COMMAND_LOCATE_STOPPED_CAR_3D:
		LocateCarCommand(command, &m_nIp);
		return 0;
	case COMMAND_GIVE_WEAPON_TO_CHAR:
	{
		CollectParameters(&m_nIp, 3);
		debug("TODO: VCS COMMAND_GIVE_WEAPON_TO_CHAR other anims code\n");
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->SetCurrentWeapon(pPed->GiveWeapon((eWeaponType)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2)));
		if (pPed->bInVehicle && pPed->m_pMyVehicle)
			pPed->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(pPed->m_weapons[pPed->m_currentWeapon].m_eWeaponType)->m_nModelId);
		// todo vcs: some anims logic
		return 0;
	}
	case COMMAND_SET_PLAYER_CONTROL:
	{
		CollectParameters(&m_nIp, 2);
		//CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		//return 0;
		// lcs
		//CPlayerInfo* pPlayer = &CWorld::Players[GET_INTEGER_PARAM(0)];

		// vcs
		GetPlayerInfoByPoolHandler(pPlayer, GET_INTEGER_PARAM(0));

		if (FindPlayerPed()) {
			if (FindPlayerPed()->GetPedState() != PED_JUMP) {
				FindPlayerPed()->bIsLanding = false;
				FindPlayerPed()->bIsInTheAir = false;
			}
			FindPlayerPed()->RestoreHeadingRate();
		}
		if (GET_INTEGER_PARAM(1)) {
			pPlayer->MakePlayerSafe(false);
			if (FindPlayerPed()->GetStatus() != PED_DRIVING && !FindPlayerPed()->m_attachedTo) {
				// FindPlayerPed()->SetIdleAndResetAnim(); // TODO!
			}
		}
		else {
			pPlayer->MakePlayerSafe(true);
			if (FindPlayerPed()->GetPedState() > PED_STATES_NO_AI && FindPlayerPed()->GetPedState() != PED_DRIVING && TheCamera.GetScreenFadeStatus() == FADE_2) {
				// FindPlayerPed()->SetIdleAndResetAnim(); // TODO!
			}
		}
		return 0;
	}
	case COMMAND_FORCE_WEATHER:
		CollectParameters(&m_nIp, 1);
		CWeather::ForceWeather(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_FORCE_WEATHER_NOW:
		CollectParameters(&m_nIp, 1);
		CWeather::ForceWeatherNow(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_RELEASE_WEATHER:
		CWeather::ReleaseWeather();
		return 0;
	case COMMAND_SET_CURRENT_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		debug("TODO VCS: COMMAND_SET_CURRENT_CHAR_WEAPON else code block anims check\n");
		for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
			if (pPed->m_weapons[i].m_eWeaponType == GET_INTEGER_PARAM(1))
				pPed->SetCurrentWeapon(i);
		}
		return 0;
	}
	case COMMAND_GET_OBJECT_COORDINATES:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		SET_VECTOR_PARAM(0, pObject->GetPosition());
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_OBJECT_COORDINATES:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pObject->Teleport(pos);
		CTheScripts::ClearSpaceForMissionEntity(pos, pObject);
		return 0;
	}
	case COMMAND_GET_GAME_TIMER:
		SET_INTEGER_PARAM(0, CTimer::GetTimeInMilliseconds());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_TURN_CHAR_TO_FACE_COORD:
	{
		CollectParameters(&m_nIp, 4);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle;
		CVector pos;
		if (pPed->bInVehicle)
			pVehicle = pPed->m_pMyVehicle;
		else
			pVehicle = nil;
		if (pVehicle)
			pos = pVehicle->GetPosition();
		else
			pos = pPed->GetPosition();
		float heading = CGeneral::GetATanOfXY(pos.x - GET_FLOAT_PARAM(1), pos.y - GET_FLOAT_PARAM(2));
		heading += HALFPI;
		if (heading > TWOPI)
			heading -= TWOPI;
		if (!pVehicle) {
			pPed->m_fRotationCur = heading;
			pPed->m_fRotationDest = heading;
			pPed->SetHeading(heading);
		}
		return 0;
	}
	case COMMAND_STORE_WANTED_LEVEL:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_pWanted->GetWantedLevel());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CAR_STOPPED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(CTheScripts::IsVehicleStopped(pVehicle));
		return 0;
	}
	case COMMAND_MARK_CHAR_AS_NO_LONGER_NEEDED:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CTheScripts::CleanUpThisPed(pPed);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_MARK_CAR_AS_NO_LONGER_NEEDED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CTheScripts::CleanUpThisVehicle(pVehicle);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CAR);
		return 0;
	}
	case COMMAND_MARK_OBJECT_AS_NO_LONGER_NEEDED:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		CTheScripts::CleanUpThisObject(pObject);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_DONT_REMOVE_CHAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		// vcs CreatedBy 2
		pPed->CharCreatedBy = MISSION_CHAR; // vcs
		CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_DONT_REMOVE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CAR);
		return 0;
	}
	case COMMAND_DONT_REMOVE_OBJECT:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_CREATE_CHAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		switch (GET_INTEGER_PARAM(2)) {
		case MI_COP:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_STREET);
			break;
		case MI_SWAT:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_SWAT);
			break;
		case MI_FBI:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_FBI);
			break;
		case MI_ARMY:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
				SET_INTEGER_PARAM(2, COP_ARMY);
			break;
		case MI_MEDIC:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_EMERGENCY)
				SET_INTEGER_PARAM(2, PEDTYPE_EMERGENCY);
			break;
		case MI_FIREMAN:
			if (GET_INTEGER_PARAM(1) == PEDTYPE_FIREMAN)
				SET_INTEGER_PARAM(2, PEDTYPE_FIREMAN);
			break;
		default:
			break;
		}
		CPed* pPed;
		if (GET_INTEGER_PARAM(1) == PEDTYPE_COP)
			pPed = new CCopPed((eCopType)GET_INTEGER_PARAM(2));
		else if (GET_INTEGER_PARAM(1) == PEDTYPE_EMERGENCY || GET_INTEGER_PARAM(1) == PEDTYPE_FIREMAN)
			pPed = new CEmergencyPed(GET_INTEGER_PARAM(2));
		else
			pPed = new CCivilianPed((ePedType)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		pPed->CharCreatedBy = MISSION_CHAR;
		pPed->bRespondsToThreats = false;
		pPed->bAllowMedicsToReviveMe = false;
		pPed->bIsPlayerFriend = false;
		if (pVehicle->bIsBus)
			pPed->bRenderPedInCar = false;
		pPed->SetPosition(pVehicle->GetPosition());
		pPed->SetOrientation(0.0f, 0.0f, 0.0f);
		CPopulation::ms_nTotalMissionPeds++;
		CWorld::Add(pPed);
		if (GET_INTEGER_PARAM(3) >= 0)
			pVehicle->AddPassenger(pPed, GET_INTEGER_PARAM(3));
		else
			pVehicle->AddPassenger(pPed);
		pPed->m_pMyVehicle = pVehicle;
		pPed->m_pMyVehicle->RegisterReference((CEntity**)&pPed->m_pMyVehicle);
		pPed->bInVehicle = true;
		pPed->SetPedState(PED_DRIVING);
		pPed->bUsesCollision = false;
		pPed->AddInCarAnims(pVehicle, false);
		pPed->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pPed->GetPosition());
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPed));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_SET_CHAR_AS_LEADER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->SetObjective(OBJECTIVE_SET_LEADER, pTarget);
		return 0;
	}
	case COMMAND_LEAVE_GROUP:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->ClearLeader();
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_FOLLOW_ROUTE:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FOLLOW_ROUTE, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_ADD_ROUTE_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CRouteNode::AddRoutePoint(GET_INTEGER_PARAM(0), GET_VECTOR_PARAM(1));
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_BIG:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddBigMessageWithNumber(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) - 1, GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_NOW:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1); // 1
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_SOON:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_SWITCH_ROADS_ON:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(0);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(1);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(5);
			supZ = GET_FLOAT_PARAM(2);
		}
		ThePaths.SwitchRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, false);
		return 0;
	}
	case COMMAND_SWITCH_ROADS_OFF:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(0);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(1);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(5);
			supZ = GET_FLOAT_PARAM(2);
		}
		ThePaths.SwitchRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, true);
		return 0;
	}
	case COMMAND_GET_NUMBER_OF_PASSENGERS:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_nNumPassengers);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_MAXIMUM_NUMBER_OF_PASSENGERS:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_nNumMaxPassengers);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CAR_DENSITY_MULTIPLIER:
	{
		CollectParameters(&m_nIp, 1);
		CCarCtrl::CarDensityMultiplier = GET_FLOAT_PARAM(0);
		return 0;
	}
	case COMMAND_SET_CAR_HEAVY:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1) != 0) {
			pVehicle->bIsHeavy = true;
			pVehicle->m_fMass = 3.0f * pVehicle->pHandling->fMass; // TODO: tHandlingData::GetMass()
			pVehicle->m_fTurnMass = 5.0f * pVehicle->pHandling->fTurnMass; // TODO: tHandlingData::GetTurnMass()
		}
		else {
			pVehicle->bIsHeavy = false;
			pVehicle->m_fMass = pVehicle->pHandling->fMass; // TODO: tHandlingData::GetMass()
			pVehicle->m_fTurnMass = pVehicle->pHandling->fTurnMass; // TODO: tHandlingData::GetTurnMass()
		}
		return 0;
	}
	case COMMAND_CLEAR_CHAR_THREAT_SEARCH:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_fearFlags = 0;
		script_assert(false && "TODO VCS COMMAND_CLEAR_CHAR_THREAT_SEARCH some func call check");
		return 0;
	}
	case COMMAND_SET_MAX_WANTED_LEVEL:
	{
		CollectParameters(&m_nIp, 1);
		CWanted::SetMaximumWantedLevel(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_NULL_297:
	case COMMAND_NULL_298:
	case COMMAND_NULL_299:
	{
		script_assert(false && "COMMAND NULL");
		return 0;
	}
	default:
		script_assert(0);
		break;
	}
	return -1;
}



void CRunningScript::ReturnFromGosubOrFunction()
{
	uint32 val = m_nIp = m_anStack[--m_nStackPointer];
	if (!(m_nIp & BIT(STACKVALUE_IS_FUNCTION_CALL_BIT)))
		return;
	if (m_nIp & BIT(STACKVALUE_INVERT_RETURN_BIT))
		m_bCondResult = !m_bCondResult;
	m_nIp = m_nIp & STACKVALUE_IP_MASK;
	uint8 nInputParameters = CTheScripts::Read1ByteFromScript(&m_nIp);
	uint8 nOutputParameters = CTheScripts::Read1ByteFromScript(&m_nIp);
	uint8 nLocalsOffset = CTheScripts::Read1ByteFromScript(&m_nIp);
	for (int i = 0; i < nOutputParameters; i++)
		ScriptParams[i] = m_anLocalVariables[m_nLocalsPointer + nInputParameters + i];
	m_nIp += val >> STACKVALUE_IP_PARAMS_OFFSET;
	m_nLocalsPointer -= nLocalsOffset;
	StoreParameters(&m_nIp, nOutputParameters);
}

#ifdef MISSION_REPLAY

bool CRunningScript::CanAllowMissionReplay()
{
	if (AllowMissionReplay != MISSION_RETRY_STAGE_NORMAL)
		return false;
	for (int i = 0; i < ARRAY_SIZE(MissionScripts); i++) {
		if (!CGeneral::faststricmp(m_abScriptName, MissionScripts[i]))
			return true;
	}
	return false;
}

uint32 AddExtraDeathDelay()
{
	return 1000;
}

void RetryMission(int type, int unk)
{
	if (type == MISSION_RETRY_TYPE_SUGGEST_TO_PLAYER) {
		doingMissionRetry = true;
		FrontEndMenuManager.m_nCurrScreen = MENUPAGE_MISSION_RETRY;
		FrontEndMenuManager.m_bAttemptingMissionRetry = true;
		FrontEndMenuManager.RequestFrontEndStartUp();
	}
	else if (type == MISSION_RETRY_TYPE_BEGIN_RESTARTING) {
		doingMissionRetry = false;
		AllowMissionReplay = MISSION_RETRY_STAGE_START_RESTARTING;
		CTheScripts::MissionCleanUp.Process();
	}
}

#endif
