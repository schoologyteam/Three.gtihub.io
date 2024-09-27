#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "AnimBlendAssociation.h"
#include "BulletInfo.h"
#include "CarAI.h"
#include "CarCtrl.h"
#include "CivilianPed.h"
#include "Cranes.h"
#include "DMAudio.h"
#include "Darkel.h"
#include "Explosion.h"
#include "Fire.h"
#include "Frontend.h"
#include "Garages.h"
#include "General.h"
#include "Heli.h"
#include "Hud.h"
#include "Messages.h"
#include "ParticleObject.h"
#include "PedRoutes.h"
#include "Phones.h"
#include "Pickups.h"
#include "Plane.h"
#include "Pools.h"
#include "Population.h"
#include "Radar.h"
#include "Record.h"
#include "RpAnimBlend.h"
#include "Rubbish.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "TxdStore.h"
#include "User.h"
#include "WaterLevel.h"
#include "World.h"
#include "Zones.h"
#include "Bike.h"
#include "Wanted.h"
//new
#include "GameLogic.h"
#include "Glass.h"
#include "MBlur.h"
#include "PedAttractor.h"
#include "VisibilityPlugins.h"
#include "Pad.h"
#include "CutsceneMgr.h"
#include "Remote.h"

bool gDeveloperFlag;

// LCS: file done except TODOs

int8 CRunningScript::ProcessCommands800To899(int32 command)
{
	CMatrix tmp_matrix;
	switch (command) {
	case COMMAND_IS_CHAR_LEAVING_VEHICLE_TO_DIE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE);
		return 0;
	}
	case COMMAND_SORT_OUT_OBJECT_COLLISION_WITH_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->m_pCollidingEntity = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_CHAR_WANDER_PATH_CLEAR:
	{
		CollectParameters(&m_nIp, 5);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(CWorld::IsWanderPathClear(pPed->GetPosition(), GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3), 4));
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + true
		if (text != CHud::gLastPrintForeverString) {
			CHud::gLastPrintForeverString = text;
			DMAudio.PlayFrontEndSound(SOUND_HUD, 0);
		}
		return 0;
	}
	case COMMAND_SET_CHAR_CAN_BE_DAMAGED_BY_MEMBERS_OF_GANG:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pTarget);
		uint8 flag = 1 << (uint8)GET_INTEGER_PARAM(1);
		if (GET_INTEGER_PARAM(2))
			pTarget->m_gangFlags |= flag;
		else
			pTarget->m_gangFlags &= ~flag;

		return 0;
	}
	case COMMAND_FREEZE_CAR_POSITION:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bIsFrozen = GET_INTEGER_PARAM(1);
		pVehicle->bInfiniteMass = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pTestedPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		bool result = false;
		if (pPed) {
			if (pPed->m_lastDamEntity) {
				if (pPed->m_lastDamEntity == pTestedPed)
					result = true;
				if (pTestedPed->bInVehicle && pPed->m_lastDamEntity == pTestedPed->m_pMyVehicle)
					result = true;
			}
		}else
			debug("HAS_CHAR_BEEN_DAMAGED_BY_CHAR - First character doesn't exist\n");
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pTestedVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		bool result = false;
		if (pPed) {
			if (pPed->m_lastDamEntity) {
				if (pPed->m_lastDamEntity == pTestedVehicle)
					result = true;
			}
		}
		else
			debug("HAS_CHAR_BEEN_DAMAGED_BY_CAR - Character doesn't exist\n");
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pTestedPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		bool result = false;
		if (pVehicle) {
			if (pVehicle->m_pLastDamageEntity) {
				if (pVehicle->m_pLastDamageEntity == pTestedPed)
					result = true;
				if (pTestedPed->bInVehicle && pVehicle->m_pLastDamageEntity == pTestedPed->m_pMyVehicle)
					result = true;
			}
		}
		else
			debug("HAS_CAR_BEEN_DAMAGED_BY_CHAR - Car doesn't exist\n");
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pTestedVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		bool result = false;
		if (pVehicle) {
			if (pVehicle->m_pLastDamageEntity) {
				if (pVehicle->m_pLastDamageEntity == pTestedVehicle)
					result = true;
			}
		}
		else
			debug("HAS_CAR_BEEN_DAMAGED_BY_CAR - First car doesn't exist\n");
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_GET_RADIO_CHANNEL:
	{
		uint8 radio = DMAudio.GetRadioInCar();
		if (radio < NUM_RADIOS || radio == STREAMED_SOUND_MISSION_COMPLETED)
			SET_INTEGER_PARAM(0, radio);
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CHAR_DROWNING_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed && pPed->bIsDrowning);
		return 0;
	}
	case COMMAND_HAS_GLASS_BEEN_SHATTERED_NEARBY:
	{
		CollectParameters(&m_nIp, 3);
		
		bool shattered = false;
		if ( CGlass::HasGlassBeenShatteredAtCoors(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)) )
			shattered = true;
		
		UpdateCompareFlag(shattered);
		return 0;
	}
	case COMMAND_SET_CHAR_STAY_IN_CAR_WHEN_JACKED:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bStayInCarOnJack = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_ADD_MONEY_SPENT_ON_WEAPONS:
		CollectParameters(&m_nIp, 1);
		CStats::MoneySpentOnWeapons(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_SET_CHAR_ANSWERING_MOBILE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (GET_INTEGER_PARAM(1))
			pPed->SetAnswerMobile();
		else
			pPed->ClearAnswerMobile();
		return 0;
	}
	case COMMAND_SET_PLAYER_DRUNKENNESS:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayerInfo->m_pPed->m_nDrunkenness = GET_INTEGER_PARAM(1);
		pPlayerInfo->m_pPed->m_nFadeDrunkenness = 0;
		if (pPlayerInfo->m_pPed->m_nDrunkenness == 0)
			CMBlur::ClearDrunkBlur();
		return 0;
	}
	case COMMAND_SET_CHAR_IN_PLAYERS_GROUP_CAN_FIGHT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bDontFight = !GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_CLEAR_CHAR_WAIT_STATE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->ClearWaitState();
		return 0;
	}
	case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE:
	{
		CollectParameters(&m_nIp, 5);
		int handle = -1;
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
		while (i--) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (pVehicle->GetVehicleAppearance() != VEHICLE_APPEARANCE_CAR && pVehicle->GetVehicleAppearance() != VEHICLE_APPEARANCE_BIKE)
				continue;
			if (GET_INTEGER_PARAM(4) != pVehicle->GetModelIndex() && GET_INTEGER_PARAM(4) >= 0)
				continue;
			if (pVehicle->VehicleCreatedBy != RANDOM_VEHICLE)
				continue;
			if (!pVehicle->IsWithinArea(infX, infY, supX, supY))
				continue;
			handle = CPools::GetVehiclePool()->GetIndex(pVehicle);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CAN_BURST_CAR_TYRES:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bTyresDontBurst = !GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_FIRE_HUNTER_GUN:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle *pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (CTimer::GetTimeInMilliseconds() > pVehicle->m_nGunFiringTime + 150) {
			CWeapon gun(WEAPONTYPE_HELICANNON, 5000);
			CVector worldGunPos = (pVehicle->GetMatrix() * vecHunterGunPos) + (CTimer::GetTimeStep() * pVehicle->m_vecMoveSpeed);
			gun.FireInstantHit(pVehicle, &worldGunPos);
			gun.AddGunshell(pVehicle, worldGunPos, CVector2D(0.f, 0.1f), 0.025f);
			DMAudio.PlayOneShot(pVehicle->m_audioEntityId, SOUND_WEAPON_SHOT_FIRED, 0.f);
			pVehicle->m_nGunFiringTime = CTimer::GetTimeInMilliseconds();
		}
		return 0;
	}
	case todo__comm_822:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_822");
		return 0;
	}
	case COMMAND_CHECK_FOR_PED_MODEL_AROUND_PLAYER:
	{
		CollectParameters(&m_nIp, 6);
		CVector d1 = CWorld::Players[GET_INTEGER_PARAM(0)].GetPos() - GET_VECTOR_PARAM(1);
		CVector d2 = CWorld::Players[GET_INTEGER_PARAM(0)].GetPos() + GET_VECTOR_PARAM(1);
		int i = CPools::GetPedPool()->GetSize();
		bool result = false;
		while (i--) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (GET_INTEGER_PARAM(4) != pPed->GetModelIndex() && GET_INTEGER_PARAM(5) != pPed->GetModelIndex())
				continue;
			if (pPed->IsWithinArea(d1.x, d1.y, d1.z, d2.x, d2.y, d2.z))
				result = true;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_CLEAR_CHAR_FOLLOW_PATH:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (pPed->GetPedState() == PED_FOLLOW_PATH) {
			pPed->RestorePreviousState();
			pPed->ClearFollowPath();
		}
		return 0;
	}
	case COMMAND_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bCanBeShotInVehicle = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_LOAD_MISSION_TEXT:
	{
		char key[8];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		TheText.LoadMissionText(key);
		return 0;
	}
	case COMMAND_CLEAR_CHAR_LAST_DAMAGE_ENTITY:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->m_lastDamEntity = nil;
		else
			debug("CLEAR_CHAR_LAST_DAMAGE_ENTITY - Character doesn't exist\n");
		return 0;
	}
	case COMMAND_CLEAR_CAR_LAST_DAMAGE_ENTITY:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle)
			pVehicle->m_pLastDamageEntity = nil;
		else
			debug("CLEAR_CAR_LAST_DAMAGE_ENTITY - Car doesn't exist\n");
		return 0;
	}
	case COMMAND_FREEZE_OBJECT_POSITION:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bIsFrozen = GET_INTEGER_PARAM(1);
		pObject->bInfiniteMass = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_UP_TAXI_SHORTCUT:
	{
		CollectParameters(&m_nIp, 8);
		CGameLogic::SetUpShortCut(
			GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3),
			GET_VECTOR_PARAM(4), GET_FLOAT_PARAM(7));
		return 0;
	}
	case COMMAND_CLEAR_TAXI_SHORTCUT:
		CGameLogic::ClearShortCut();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	case COMMAND_INCREASE_PLAYER_MAX_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayerInfo->m_nMaxHealth += GET_INTEGER_PARAM(1);
		pPlayerInfo->m_pPed->m_fHealth = pPlayerInfo->m_nMaxHealth;
		CHud::m_ItemToFlash = ITEM_HEALTH;
		return 0;
	}
	case COMMAND_INCREASE_PLAYER_MAX_ARMOUR:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayerInfo->m_nMaxArmour += GET_INTEGER_PARAM(1);
		pPlayerInfo->m_pPed->m_fArmour = pPlayerInfo->m_nMaxArmour;
		CHud::m_ItemToFlash = ITEM_ARMOUR;
		return 0;
	}
	case COMMAND_CREATE_RANDOM_CHAR_AS_DRIVER:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed = CPopulation::AddPedInCar(pVehicle, true);
		pPed->CharCreatedBy = MISSION_CHAR;
		pPed->bRespondsToThreats = false;
		pPed->bAllowMedicsToReviveMe = false;
		pPed->bIsPlayerFriend = false;
		if (pVehicle->bIsBus)
			pPed->bRenderPedInCar = false;
		pPed->SetPosition(pVehicle->GetPosition());
		pPed->SetOrientation(0.0f, 0.0f, 0.0f);
		pPed->SetPedState(PED_DRIVING);
		pPed->m_pMyVehicle = pVehicle;
		pPed->m_pMyVehicle->RegisterReference((CEntity**)&pPed->m_pMyVehicle);
		pVehicle->pDriver = pPed;
		pVehicle->pDriver->RegisterReference((CEntity**)&pVehicle->pDriver);
		pPed->bInVehicle = true;
		pVehicle->SetStatus(STATUS_PHYSICS);
		if (pVehicle->m_vehType == VEHICLE_TYPE_BOAT)
			pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
		pVehicle->bEngineOn = true;
		pVehicle->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pVehicle->GetPosition());
		CPopulation::ms_nTotalMissionPeds++;
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPed));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_CREATE_RANDOM_CHAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed = CPopulation::AddPedInCar(pVehicle, false);
		pPed->CharCreatedBy = MISSION_CHAR;
		pPed->bRespondsToThreats = false;
		pPed->bAllowMedicsToReviveMe = false;
		pPed->bIsPlayerFriend = false;
		if (pVehicle->bIsBus)
			pPed->bRenderPedInCar = false;
		pPed->SetPosition(pVehicle->GetPosition());
		pPed->SetOrientation(0.0f, 0.0f, 0.0f);
		CPopulation::ms_nTotalMissionPeds++;
		pVehicle->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pVehicle->GetPosition());
		if (GET_INTEGER_PARAM(1) >= 0)
			pVehicle->AddPassenger(pPed, GET_INTEGER_PARAM(1));
		else
			pVehicle->AddPassenger(pPed);

		pPed->m_pMyVehicle = pVehicle;
		pPed->m_pMyVehicle->RegisterReference((CEntity**)&pPed->m_pMyVehicle);
		pPed->bInVehicle = true;
		pPed->SetPedState(PED_DRIVING);
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPed));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_SET_CHAR_IGNORE_THREATS_BEHIND_OBJECTS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIgnoreThreatsBehindObjects = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_MAKE_HELI_COME_CRASHING_DOWN:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pHeli = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pHeli && pHeli->IsCar() && pHeli->IsRealHeli());
		pHeli->bHeliDestroyed = true;
		return 0;
	}
	case COMMAND_SET_OBJECT_AREA_VISIBLE:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->m_area = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_NEVER_TARGETTED:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bNeverEverTargetThisPed = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_CROUCH_WHEN_THREATENED:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bCrouchWhenScared = true;
		return 0;
	}
	case COMMAND_IS_CHAR_IN_ANY_POLICE_VEHICLE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle &&
			pPed->m_pMyVehicle->IsLawEnforcementVehicle() &&
			pPed->m_pMyVehicle->GetModelIndex() != MI_PREDATOR);
		return 0;
	}
	case COMMAND_DOES_CHAR_EXIST:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0)) != 0);
		return 0;
	case COMMAND_DOES_VEHICLE_EXIST:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		bool bExist = false;
		if (pVehicle) {
			int index = GET_INTEGER_PARAM(0) >> 8;
#ifdef FIX_BUGS
			bExist = (index >= 0 && index < NUMVEHICLES); // epic fail
#else
			bExist = (index > 0 && index < NUMVEHICLES);
#endif
		}
		UpdateCompareFlag(bExist);
		return 0;
	}
	case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_CONTACT_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetShortRangeCoordBlip(BLIP_COORD, pos, 2, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CHAR_STUCK:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->m_nWaitState == WAITSTATE_STUCK);
		return 0;
	}
	case COMMAND_SET_ALL_TAXIS_HAVE_NITRO:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle::bAllTaxisHaveNitro = GET_INTEGER_PARAM(0) != 0;
		return 0;
	}
	case COMMAND_SET_CHAR_STOP_SHOOT_DONT_SEEK_ENTITY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->bKindaStayInSamePlace = true;
			pPed->bStopAndShoot = true;
		}
		else {
			pPed->bKindaStayInSamePlace = false;
			pPed->bStopAndShoot = false;
		}
		pPed->m_nLastPedState = PED_NONE;
		return 0;
	}
	case COMMAND_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1)) {
			pVehicle->bIsFrozen = true;
			pVehicle->bInfiniteMass = true;
			if (m_bIsMissionScript) {
				CWorld::Remove(pVehicle);
				pVehicle->bIsStaticWaitingForCollision = true;
				CWorld::Add(pVehicle);
			}
		}
		else {
			pVehicle->bIsFrozen = false;
			pVehicle->bInfiniteMass = false;
		}
		return 0;
	}
	case COMMAND_REGISTER_VIGILANTE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelVigilanteMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CLEAR_ALL_CHAR_ANIMS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed && pPed->GetPedState() != PED_DRIVING && pPed->GetPedState() != PED_AIM_GUN) {
			pPed->m_pVehicleAnim = nil;
			pPed->RestartNonPartialAnims();
			RpAnimBlendClumpRemoveAllAssociations(pPed->GetClump());
			pPed->SetPedState(PED_IDLE);
			pPed->SetMoveState(PEDMOVE_STILL);
			pPed->m_nLastPedState = PED_NONE;
			pPed->ClearAimFlag();
			pPed->ClearLookFlag();
			pPed->bIsPointingGunAt = false;
			if (pPed->IsPlayer())
				((CPlayerPed*)pPed)->m_fMoveSpeed = 0.0f;
			else
				pPed->m_nStoredMoveState = PEDMOVE_STILL;
			CAnimManager::AddAnimation(pPed->GetClump(), pPed->m_animGroup, ANIM_STD_IDLE);
			pPed->bIsPedDieAnimPlaying = false;
		}
		return 0;
	}
	case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::SetMaxNumStoredCarsForGarage(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_WANTED_STARS_ARE_FLASHING:
	{
		CWanted* pWanted = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted;
		UpdateCompareFlag(pWanted->m_nMinWantedLevel - pWanted->GetWantedLevel() > 0);
		return 0;
	}
	case COMMAND_SET_ALLOW_HURRICANES:
		CollectParameters(&m_nIp, 1);
		CStats::NoMoreHurricanes = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_PLAY_ANNOUNCEMENT:
	{
		CollectParameters(&m_nIp, 1);
		DMAudio.PlayRadioAnnouncement(GET_INTEGER_PARAM(0) + STREAMED_SOUND_NEWS_A);
		return 0;
	}
	case COMMAND_SET_PLAYER_IS_IN_STADIUM:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::bPlayerIsInTheStatium = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		SET_INTEGER_PARAM(0, pPlayerInfo->m_pPed->m_nLastBusFareCollected);
		pPlayerInfo->m_pPed->m_nLastBusFareCollected = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, 0);
		if (pPed->m_objective == OBJECTIVE_NONE && !pPed->bHasAlreadyUsedAttractor) {
			C2dEffect* pEffect = (C2dEffect*)GetPedAttractorManager()->GetEffectForIceCreamVan(pVehicle, pPed->GetPosition()); // has to be casted, because inner methods are const
			if (pEffect) {
				CVector pos;
				CPedAttractorManager::ComputeEffectPos(pEffect, pVehicle->GetMatrix(), pos);
				if ((pPed->GetPosition() - pos).MagnitudeSqr() < SQR(20.0f)) {
					if (GetPedAttractorManager()->HasEmptySlot(pEffect) && GetPedAttractorManager()->IsApproachable(pEffect, pVehicle->GetMatrix(), 0, pPed)) {
						if (GetPedAttractorManager()->RegisterPedWithAttractor(pPed, pEffect, pVehicle->GetMatrix()))
							SET_INTEGER_PARAM(0, 1);
					}
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISPLAY_RADAR:
		CollectParameters(&m_nIp, 1);
		CHud::m_HideRadar = GET_INTEGER_PARAM(0) == 0;
		// on PS2 two flags are set, on mobile none
		return 0;
	case COMMAND_IS_PLAYER_IN_INFO_ZONE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		char key[KEY_LENGTH_IN_SCRIPT];
		memset(key, 0, KEY_LENGTH_IN_SCRIPT);
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CVector pos = pPlayerInfo->GetPos();
		CZone* infoZone = CTheZones::FindInformationZoneForPosition(&pos);
		UpdateCompareFlag(strncmp(key, infoZone->name, 8) == 0); // original code doesn't seem to be using strncmp in here and compare 2 ints instead
		return 0;
	}
	case COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (pPed->m_attractor)
			GetPedAttractorManager()->DeRegisterPed(pPed, pPed->m_attractor);
		return 0;
	}
	case COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bHasAlreadyUsedAttractor);
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1)) {
			pVehicle->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pVehicle);
				pVehicle->bIsStaticWaitingForCollision = true;
				CWorld::Add(pVehicle);
			}
		}
		else {
			pVehicle->bDontLoadCollision = true;
			if (pVehicle->bIsStaticWaitingForCollision) {
				pVehicle->bIsStaticWaitingForCollision = false;
				if (!pVehicle->GetIsStatic())
					pVehicle->AddToMovingList();
			}
		}
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pPed);
				pPed->bIsStaticWaitingForCollision = true;
				CWorld::Add(pPed);
			}
		}
		else {
			pPed->bDontLoadCollision = true;
			if (pPed->bIsStaticWaitingForCollision) {
				pPed->bIsStaticWaitingForCollision = false;
				if (!pPed->GetIsStatic())
					pPed->AddToMovingList();
			}
		}
		return 0;
	}
	case COMMAND_ADD_BIG_GUN_FLASH:
	{
		CollectParameters(&m_nIp, 6);
		CWeapon::AddGunFlashBigGuns(GET_VECTOR_PARAM(0), GET_VECTOR_PARAM(3));
		return 0;
	}
	case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bBoughtIceCream);
		return 0;
	}
	case COMMAND_GET_PROGRESS_PERCENTAGE:
		SET_FLOAT_PARAM(0, CStats::GetPercentageProgress());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_SHORTCUT_PICKUP_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutPointAfterDeath(GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3));
		return 0;
	}
	case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutDropOffPointForMission(GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3));
		return 0;
	}
	case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float x2 = GET_FLOAT_PARAM(2);
		float y2 = GET_FLOAT_PARAM(3);
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (CTheScripts::LastRandomPedId == CPools::GetPedPool()->GetIndex(pPed))
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl())
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->m_nWaitState != WAITSTATE_FALSE)
				continue;
			if (pPed->bHasAlreadyUsedAttractor)
				continue;
			if (pPed->m_attractor)
				continue;
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6)))
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
		while (i--) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (pVehicle->IsWithinArea(infX, infY, supX, supY))
				pVehicle->m_nDoorLock = CARLOCK_UNLOCKED;
		}
		return 0;
	}
	case COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS:
		CollectParameters(&m_nIp, 2);
		CGangs::SetWillAttackPlayerWithCops((ePedType)((int)PEDTYPE_GANG1 + GET_INTEGER_PARAM(0)), !!GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bHeldHostageInCar = GET_INTEGER_PARAM(1);
		pPed->b1A4_2 = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_VEHICLE_TO_FADE_IN:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVisibilityPlugins::SetClumpAlpha(pVehicle->GetClump(), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_REGISTER_ODDJOB_MISSION_PASSED:
		++CStats::MissionsPassed;
		CStats::CheckPointReachedSuccessfully();
		CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMilliseconds();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	case COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle && pPed->m_pMyVehicle == CGameLogic::pShortCutTaxi);
		return 0;
	}
	case COMMAND_IS_CHAR_DUCKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(RpAnimBlendClumpGetAssociation(pPed->GetClump(), ANIM_STD_DUCK_DOWN) != nil);
		return 0;
	}
	case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI:
	{
		CollectParameters(&m_nIp, 3);
		CObject* pHeli = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		bool found = false;
		float waterLevel = -1000.0f;
		CVector pos = pHeli->GetPosition();
		float radius = GET_FLOAT_PARAM(1);
		float ground = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &found);
		if (!CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &waterLevel, false))
			waterLevel = 0.0f;
		if (waterLevel > ground)
			ground = waterLevel;
		if (GET_INTEGER_PARAM(2) > 8)
			SET_INTEGER_PARAM(2, 8);
		CVehicle::HeliDustGenerate(pHeli, (pos.z - ground - 1.0f - radius) * 0.3 + radius, ground, GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_REGISTER_FIRE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelFireMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_IS_AUSTRALIAN_GAME:
		UpdateCompareFlag(false); // should we make some check?
		return 0;
	case COMMAND_DISARM_CAR_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle->IsCar()) {
			if (((CAutomobile*)pVehicle)->m_bombType != CARBOMB_NONE) {
				((CAutomobile*)pVehicle)->m_bombType = CARBOMB_NONE;
				((CAutomobile*)pVehicle)->m_pBombRigger = nil;
			}
		}
#ifdef FIX_BUGS
		else if (pVehicle->IsBike()) {
			if (((CBike*)pVehicle)->m_bombType != CARBOMB_NONE) {
				((CBike*)pVehicle)->m_bombType = CARBOMB_NONE;
				((CBike*)pVehicle)->m_pBombRigger = nil;
			}
		}
#endif
		return 0;
	}
	case COMMAND_IS_JAPANESE_GAME:
#ifdef MORE_LANGUAGES
		UpdateCompareFlag(FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_JAPANESE);
#elif (defined GTAVC_JP_PATCH)
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_DOT_PRODUCT_2D:
	{
		CollectParameters(&m_nIp, 4);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float X2 = GET_FLOAT_PARAM(2);
		float Y2 = GET_FLOAT_PARAM(3);
		float fDistance = X1 * X2 + Y1 * Y2;
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DOT_PRODUCT_3D:
	{
		CollectParameters(&m_nIp, 6);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float Z1 = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float Z2 = GET_FLOAT_PARAM(5);
		float fDistance = X1 * X2 + Y1 * Y2 + Z1 * Z2;
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DEBUG_PRINT_WITH_1_FLOAT:
		return 0;
	case COMMAND_DEBUG_PRINT_WITH_2_FLOATS:
		return 0;
	case COMMAND_DEBUG_PRINT_WITH_3_FLOATS:
		return 0;
	case COMMAND_GET_PAD_BUTTON_STATE:
	{
		CollectParameters(&m_nIp, 1);
		switch (GET_INTEGER_PARAM(0)) {
		case 0: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetOddJobTrigger()); break;
		case 1: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetBrake()); break;
		case 2: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSteeringLeftRight()); break;
		case 3: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSteeringUpDown()); break;
		case 4: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunLeftRight()); break;
		case 5: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunUpDown()); break;
		case 6: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetPedWalkLeftRight()); break;
		case 7: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetPedWalkUpDown()); break;
		case 8: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookLeft()); break;
		case 9: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookRight()); break;
		case 10: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookBehindForCar()); break;
		case 11: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookBehindForPed()); break;
		case 12: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetHorn()); break;
		case 13: SET_INTEGER_PARAM(0, CPad::GetPad(0)->HornJustDown()); break;
		case 14: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunFired()); break;
		case 15: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CarGunJustDown()); break;
		case 16: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetHandBrake()); break;
		case 17: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetBrake()); break;
		case 18: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetExitVehicle()); break;
		case 19: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ExitVehicleJustDown()); break;
		case 20: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetWeapon()); break;
		case 21: SET_INTEGER_PARAM(0, CPad::GetPad(0)->WeaponJustDown()); break;
		case 22: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetAccelerate()); break;
		case 23: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleCameraModeUpJustDown()); break;
		case 24: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleWeaponLeftJustDown()); break;
		case 25: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleWeaponRightJustDown()); break;
		case 26: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetTarget()); break;
		case 27: SET_INTEGER_PARAM(0, CPad::GetPad(0)->TargetJustDown()); break;
		case 28: SET_INTEGER_PARAM(0, CPad::GetPad(0)->JumpJustDown()); break;
		case 29: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSprint()); break;
		case 30: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ShiftTargetLeftJustDown()); break;
		case 31: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ForceCameraBehindPlayer()); break;
		case 32: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperZoomIn()); break;
		case 33: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperZoomOut()); break;
		case 34: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperModeLookLeftRight()); break;
		case 35: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperModeLookUpDown()); break;
		case 36: SET_INTEGER_PARAM(0, CPad::GetPad(0)->LookAroundLeftRight()); break;
		case 37: SET_INTEGER_PARAM(0, CPad::GetPad(0)->LookAroundUpDown()); break;
		case 38: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiLeft()); break;
		case 39: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiRight()); break;
		case 40: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiUp()); break;
		case 41: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiDown()); break;
		case 42: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiSelect()); break;
		case 43: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiBack()); break;
		case 44: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSkipCutscene()); if (GET_INTEGER_PARAM(0)) TheCamera.m_bIgnoreFadingStuffForMusic = false; break; // spectacular hack
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_NAVIGATION_ARROW:
	{
		CollectParameters(&m_nIp, 3);
		// cNavArrow::SetTarget(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(0)); // TODO, although it's unused
		return 0;
	}
	case COMMAND_CLEAR_NAVIGATION_ARROW:
	{
		// cNavArrow::ClearTarget(); // TODO, although it's unused
		return 0;
	}
	case COMMAND_CALLNOT:
	case COMMAND_CALL:
	{
		m_anStack[m_nStackPointer++] = m_nIp | BIT(STACKVALUE_IS_FUNCTION_CALL_BIT) | ((command == COMMAND_CALLNOT) ? BIT(STACKVALUE_INVERT_RETURN_BIT) : 0);
		uint8 nInputParams = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nOutputParameters = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nLocalsOffset = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint32 nIPBeforeParameters = m_nIp;
		CollectParameters(&m_nIp, 1);
		if (nInputParams)
			CollectParameters(&m_nIp, nInputParams, &m_anLocalVariables[m_nLocalsPointer + nLocalsOffset]);
		m_nLocalsPointer += nLocalsOffset;
		m_anStack[m_nStackPointer - 1] |= (m_nIp - nIPBeforeParameters) << STACKVALUE_IP_PARAMS_OFFSET;
		if (GET_INTEGER_PARAM(0) < 0)
			m_nIp = CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0);
		else
			m_nIp = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_IS_CAR_AUTOMOBILE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_FIRST_VEHICLE && pVehicle->GetModelIndex() < MI_FERRY);
		return 0;
	}
	case COMMAND_IS_CAR_BIKE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_ANGEL && pVehicle->GetModelIndex() <= MI_SANCHEZ);
		return 0;
	}
		return 0;
	case COMMAND_IS_CAR_PLANE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_AIRTRAIN && pVehicle->GetModelIndex() <= MI_DEADDODO);
		return 0;
	}
	case COMMAND_IS_CAR_HELI:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_ESCAPE && pVehicle->GetModelIndex() <= MI_CHOPPER);
		return 0;
	}
	case COMMAND_NULL_896:
	case COMMAND_NULL_897:
	case COMMAND_NULL_898:
	case COMMAND_NULL_899:
	{
		script_assert(false && "COMMAND NULL");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands900To999(int32 command)
{
	char str[52];
	char onscreen_str[KEY_LENGTH_IN_SCRIPT];
	switch (command) {
	case COMMAND_NULL_900:
	case COMMAND_NULL_901:
	case COMMAND_NULL_902:
	case COMMAND_NULL_903:
	case COMMAND_NULL_904:
	case COMMAND_NULL_905:
	case COMMAND_NULL_906:
	case COMMAND_NULL_907:
	case COMMAND_NULL_908:
	case COMMAND_NULL_909:
	case COMMAND_NULL_910:
	case COMMAND_NULL_911:
	{
		script_assert(false && "COMMAND NULL");
		return 0;
	}
	case LCSWRONG_COMMAND_1476: // they DO have it in script
		return 0;
	case COMMAND_RETURN_IF_TRUE:
		if (m_bCondResult) {
			ReturnFromGosubOrFunction();
		}
		return 0;
	case COMMAND_RETURN_TRUE_IF_TRUE:
		if (m_bCondResult) {
			UpdateCompareFlag(false);
			ReturnFromGosubOrFunction();
		}
		return 0;
	case COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_BEHIND:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyAllowedToSitBehind = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_RC_HELI_HEIGHT_LIMIT:
		CollectParameters(&m_nIp, 1);
		CVehicle::rcHeliHeightLimit = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_CREATE_SCRIPT_CORONA:
	{
		CollectParameters(&m_nIp, 9);
		base::cSList<script_corona>::tSItem* pCorona = new base::cSList<script_corona>::tSItem();
		pCorona->item.x = GET_FLOAT_PARAM(0);
		pCorona->item.y = GET_FLOAT_PARAM(1);
		pCorona->item.z = GET_FLOAT_PARAM(2);
		pCorona->item.id = CTheScripts::NextScriptCoronaID++;
		if (pCorona->item.z <= MAP_Z_LOW_LIMIT)
			pCorona->item.z = CWorld::FindGroundZForCoord(pCorona->item.x, pCorona->item.y);
		pCorona->item.size = GET_FLOAT_PARAM(3);
		pCorona->item.r = GET_INTEGER_PARAM(6);
		pCorona->item.g = GET_INTEGER_PARAM(7);
		pCorona->item.b = GET_INTEGER_PARAM(8);
		pCorona->item.type = GET_INTEGER_PARAM(4);
		pCorona->item.flareType = GET_INTEGER_PARAM(5);
		SET_INTEGER_PARAM(0, pCorona->item.id);
		CTheScripts::mCoronas.Insert(pCorona);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_REMOVE_SCRIPT_CORONA:
	{
		CollectParameters(&m_nIp, 1);
		for (base::cSList<script_corona>::tSItem* i = CTheScripts::mCoronas.first; i; i = i->next) {
			if (i->item.id == GET_INTEGER_PARAM(0)) {
				CTheScripts::mCoronas.Remove(i);
				delete i;
				break;
			}
		}
		return 0;
	}
	case COMMAND_IS_BOAT_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CBoat* pVehicle = (CBoat*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->IsBoat());
		UpdateCompareFlag(pVehicle->bBoatInWater);
		return 0;
	}
	case COMMAND_IS_CAR_DRIVER_BEING_JACKED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->bIsBeingCarJacked);
		return 0;
	}
	case COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_IN_FRONT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyAllowedToSitInFront = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CAR_TILTED_BY_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		pVehicle->ApplyTurnForce(0.0f, 0.0f, CGeneral::GetRandomNumberInRange(-0.8f, -1.2f)* pPed->m_fMass,
			pPed->GetPosition().x - pVehicle->GetPosition().x, pPed->GetPosition().y - pVehicle->GetPosition().y, 0.0f);
		DMAudio.PlayOneShot(pVehicle->m_audioEntityId, SOUND_CAR_JERK, 0.0f);
		return 0;
	}
	case COMMAND_GET_WEAPON_TYPE_FOR_PICKUP_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		float X = GET_FLOAT_PARAM(0);
		float Y = GET_FLOAT_PARAM(1);
		float Z = GET_FLOAT_PARAM(2);
		float radius = GET_FLOAT_PARAM(3);
		int model = -1;
		bool found = false;
		for (uint32 i = 0; i < NUMPICKUPS; i++) {
			CPickup* pPickup = &CPickups::aPickUps[i];
			if (pPickup->m_eType != PICKUP_NONE) {
				CVector fDist = pPickup->m_vecPos - CVector(X, Y, Z);
#ifndef FIX_BUGS // this breaks ALL pickups!
				pPickup->m_eModelIndex = 4;
#endif
				if (fDist.Magnitude() < radius && pPickup->m_pObject) {
					found = true;
					model = CPickups::WeaponForModel(pPickup->m_pObject->GetModelIndex());
				}
			}
		}
		SET_INTEGER_PARAM(0, model);
		StoreParameters(&m_nIp, 1);
	}
	case todo__comm_924:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_924");
		return 0;
	}
	case LCSWRONG_COMMAND_1489:
	{
		script_assert(false && "TODO_OR_CHECK_COMMAND_1489");
		return 0;
	}
	case LCSWRONG_COMMAND_1490:
	{
		script_assert(false && "TODO_OR_CHECK_COMMAND_1490");
		return 0;
	}
	case todo__comm_927:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_927");
		return 0;
	}
	case COMMAND_SET_DEBUG_MENU_ACTIVE:
		CollectParameters(&m_nIp, 1);
		// this sets two values on PS2 and PSP, but not on mobile - TODO?
		return 0;
	case COMMAND_SET_DRAW_HUD:
		CollectParameters(&m_nIp, 1);
		CHud::m_Wants_To_Draw_Hud = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_GET_RANDOM_CHAR_IN_AREA_NO_CHECKS:
	{
		CollectParameters(&m_nIp, 4);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float x2 = GET_FLOAT_PARAM(2);
		float y2 = GET_FLOAT_PARAM(3);
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->m_nWaitState != WAITSTATE_FALSE)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_RANDOM_CAR_IN_AREA_NO_CHECKS_NO_SAVE:
	{
		CollectParameters(&m_nIp, 4);
		int handle = -1;
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
		while (i-- && handle == -1) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (!pVehicle->IsWithinArea(infX, infY, supX, supY))
				continue;
			handle = CPools::GetVehiclePool()->GetIndex(pVehicle);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_STORE_CAR_COLLIDED_WITH_NO_SAVE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (!pVehicle)
			printf("STORE_CAR_COLLIDED_WITH_NO_SAVE - Car doesn\'t exist\n");
		else {
			if (pVehicle->m_pLastDamageEntity == nil)
				SET_INTEGER_PARAM(0, -1);
			else {
				// what they are doing is not very safe as m_pLastDamageEntity doesn't have to be CVehicle
#ifdef FIX_BUGS
				if (!pVehicle->m_pLastDamageEntity->IsVehicle()) {
					SET_INTEGER_PARAM(0, -1);
				}
				else
#endif
				{
					SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex((CVehicle*)pVehicle->m_pLastDamageEntity));
					pVehicle->m_pLastDamageEntity = nil;
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_DROPS_WEAPONS_ON_DEATH:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bDropsWeaponsOnDeath = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_IS_CHAR_CROUCHING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bIsDucking);
		return 0;
	}
	case COMMAND_OVERRIDE_CAR_REMOTE_CONTROL:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->SetStatus(STATUS_PLAYER_REMOTE);
		CVehicle::bDisableRemoteDetonation = true;
		CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle = pVehicle;
		pVehicle->RegisterReference((CEntity**)&CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle);
		if (pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI || pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_PLANE) {
			TheCamera.TakeControl(pVehicle, CCam::MODE_CAM_ON_A_STRING, GET_INTEGER_PARAM(1) ? INTERPOLATION : JUMP_CUT, CAMCONTROL_SCRIPT);
			TheCamera.SetZoomValueCamStringScript(0);
		}
		else {
			TheCamera.TakeControl(pVehicle, CCam::MODE_1STPERSON, GET_INTEGER_PARAM(1) ? INTERPOLATION : JUMP_CUT, CAMCONTROL_SCRIPT);
			script_assert(pVehicle->IsCar());
			((CAutomobile*)pVehicle)->Damage.m_bSmashedDoorDoesntClose = true;
		}
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CAR);
		if (FindPlayerVehicle())
			FindPlayerVehicle()->bCanBeDamaged = false;
		return 0;
	}
	case COMMAND_CANCEL_REMOTE_MODE:
	{
		if (FindPlayerVehicle())
			FindPlayerVehicle()->bCanBeDamaged = true;
		CRemote::TakeRemoteControlledCarFromPlayer(false);
		CWorld::Players[CWorld::PlayerInFocus].field_D6 = false;
		CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle = nil;
		TheCamera.Restore();
		return 0;
	}
	case COMMAND_SET_OBJECT_TURN_SPEED:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVector vSpeed = GET_VECTOR_PARAM(1) / GAME_SPEED_TO_METERS_PER_SECOND;
		pObject->SetTurnSpeed(vSpeed.x, vSpeed.y, vSpeed.z);
		return 0;
	}
	case COMMAND_SET_OBJECT_MASS:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->m_fMass = GET_FLOAT_PARAM(1);
		pObject->m_fTurnMass = GET_FLOAT_PARAM(2);
		pObject->m_fAirResistance = GET_FLOAT_PARAM(3);
		if (pObject->m_fMass < 99998.0f) {
			pObject->bInfiniteMass = false;
			pObject->m_phy_flagA08 = false;
			pObject->bAffectedByGravity = true;
		}
		else {
			pObject->bInfiniteMass = true;
			pObject->m_phy_flagA08 = true;
			pObject->bAffectedByGravity = false;
		}
		return 0;
	}
	case COMMAND_HAS_CUTSCENE_LOADED:
		UpdateCompareFlag(CCutsceneMgr::ms_cutsceneLoadStatus == CUTSCENE_LOADED);
		return 0;
	case COMMAND_SET_UNIQUE_JUMPS_FOUND:
		CollectParameters(&m_nIp, 1);
		CStats::NumberOfUniqueJumpsFound = GET_INTEGER_PARAM(0);
		return 0;
	case todo__comm_941:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_941");
		return 0;
	}
	case COMMAND_SET_CHAR_DIVE_FROM_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed);
		pPed->bRespondsToThreats = true;
		pPed->SetEvasiveDive(pVehicle, 1);
		return 0;
	}
	case COMMAND_WRECK_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pVehicle = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->IsCar());
		pVehicle->m_fHealth = 0.0f;
		pVehicle->SetStatus(STATUS_WRECKED);
		pVehicle->bRenderScorched = true;
		pVehicle->Damage.FuckCarCompletely();
		if (pVehicle->GetModelIndex() != MI_RCBANDIT) {
			pVehicle->SetBumperDamage(CAR_BUMP_FRONT, VEHBUMPER_FRONT);
			pVehicle->SetBumperDamage(CAR_BUMP_REAR, VEHBUMPER_REAR);
			pVehicle->SetDoorDamage(CAR_BONNET, DOOR_BONNET);
			pVehicle->SetDoorDamage(CAR_BOOT, DOOR_BOOT);
			pVehicle->SetDoorDamage(CAR_DOOR_LF, DOOR_FRONT_LEFT);
			pVehicle->SetDoorDamage(CAR_DOOR_RF, DOOR_FRONT_RIGHT);
			pVehicle->SetDoorDamage(CAR_DOOR_LR, DOOR_REAR_LEFT);
			pVehicle->SetDoorDamage(CAR_DOOR_RR, DOOR_REAR_RIGHT);
		}
		pVehicle->m_bombType = CARBOMB_NONE;
		pVehicle->bEngineOn = false;
		pVehicle->bLightsOn = false;
		pVehicle->m_fHealth = 0.0f;
		pVehicle->m_nBombTimer = 0;
		pVehicle->m_bSirenOrAlarm = false;
		return 0;
	}
	case COMMAND_REGISTER_OUTFIT_CHANGE:
		// CStats::NumberOutfitChanges++;
		return 0;
	case COMMAND_HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		bool result = false;
		if (!pObject) {
			printf("HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON - Object doesn\'t exist\n");
		}
		else {
			if (GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYMELEE || GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYWEAPON)
				result = CheckDamagedWeaponType(pObject->m_nLastWeaponToDamage, GET_INTEGER_PARAM(1));
			else
				result = GET_INTEGER_PARAM(1) == pObject->m_nLastWeaponToDamage;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_CLEAR_OBJECT_LAST_WEAPON_DAMAGE:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		if (!pObject)
			printf("CLEAR_OBJECT_LAST_WEAPON_DAMAGE - pObject doesn\'t exist");
		else
			pObject->m_nLastWeaponToDamage = -1;
		return 0;
	}
	case COMMAND_SET_CAR_TURN_SPEED:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector vSpeed = GET_VECTOR_PARAM(1) / GAME_SPEED_TO_METERS_PER_SECOND;
		pVehicle->SetTurnSpeed(vSpeed.x, vSpeed.y, vSpeed.z);
		return 0;
	}
	case COMMAND_SET_CAR_MOVE_SPEED:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector vSpeed = GET_VECTOR_PARAM(1) / GAME_SPEED_TO_METERS_PER_SECOND;
		pVehicle->SetMoveSpeed(vSpeed);
		return 0;
	}
	case COMMAND_SET_OBJECT_PROOFS:
	{
		CollectParameters(&m_nIp, 6);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bBulletProof = (GET_INTEGER_PARAM(1) != 0);
		pObject->bFireProof = (GET_INTEGER_PARAM(2) != 0);
		pObject->bExplosionProof = (GET_INTEGER_PARAM(3) != 0);
		pObject->bCollisionProof = (GET_INTEGER_PARAM(4) != 0);
		pObject->bMeleeProof = (GET_INTEGER_PARAM(5) != 0);
		return 0;
	}
	case COMMAND_GET_CAMERA_PED_ZOOM_INDICATOR:
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FOLLOWPED)
			SET_INTEGER_PARAM(0, TheCamera.PedZoomIndicator);
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_CAMERA_PED_ZOOM_INDICATOR:
		CollectParameters(&m_nIp, 1);
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FOLLOWPED)
			TheCamera.PedZoomIndicator = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_GET_CAR_ORIENTATION:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_FLOAT_PARAM(1, LimitAngleOnCircle(RADTODEG(Asin(pVehicle->GetForward().z))));
		SET_FLOAT_PARAM(2, LimitAngleOnCircle(RADTODEG(Atan2(-pVehicle->GetForward().x, pVehicle->GetForward().y))));
		SET_FLOAT_PARAM(0, LimitAngleOnCircle(RADTODEG(Atan2(-pVehicle->GetRight().z, pVehicle->GetUp().z))));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_CAR_ORIENTATION:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->SetOrientation(DEGTORAD(GET_FLOAT_PARAM(2)), DEGTORAD(GET_FLOAT_PARAM(1)), DEGTORAD(GET_FLOAT_PARAM(3)));
		return 0;
	}
	case COMMAND_IS_DEBUG_MENU_ON:
		// on PS2 it's something actual - TODO
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_OPEN_VAN_BACK_DOORS:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		assert(pVehicle);
		pVehicle->ProcessOpenDoor(CAR_DOOR_RR, ANIM_STD_VAN_OPEN_DOOR_REAR_RHS, 1.0f);
		pVehicle->ProcessOpenDoor(CAR_DOOR_LR, ANIM_STD_VAN_OPEN_DOOR_REAR_LHS, 1.0f);
		return 0;
	}
	case COMMAND_GET_CHAR_THREAT_CHAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, 0);
		CEntity* pThreat = pPed->m_threatEntity;
		if (pThreat && pThreat->IsPed())
			SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex((CPed*)pThreat));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_FREEZE_PED_ZOOM_SWITCH:
		CollectParameters(&m_nIp, 1);
		TheCamera.m_bFreezePedZoomSwitch = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_OBJECT_RENDERED_DAMAGED:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bRenderDamaged = true;
		return 0;
	}
	case COMMAND_GET_RANDOM_CAR_IN_AREA_NO_SAVE:
	{
		CollectParameters(&m_nIp, 5);
		int handle = -1;
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
		while (i-- && handle == -1) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (pVehicle->GetVehicleAppearance() != VEHICLE_APPEARANCE_CAR && pVehicle->GetVehicleAppearance() != VEHICLE_APPEARANCE_BIKE)
				continue;
#ifdef FIX_BUGS
			if (pVehicle->m_fHealth <= 0.0f)
#else
			if (pVehicle->m_fHealth == 0.0f)
#endif
				continue;
			if (pVehicle->GetModelIndex() != GET_INTEGER_PARAM(4) && GET_INTEGER_PARAM(4) >= 0)
				continue;
			if (pVehicle->VehicleCreatedBy != RANDOM_VEHICLE)
				continue;
			if (!pVehicle->IsWithinArea(infX, infY, supX, supY))
				continue;
			handle = CPools::GetVehiclePool()->GetIndex(pVehicle);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_PLAYER_MADE_SAFE:
	{
		UpdateCompareFlag(CPad::GetPad(0)->IsPlayerControlsDisabledBy(PLAYERCONTROL_PLAYERINFO));
		return 0;
	}
	case COMMAND_IS_E3_BUILD:
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_CLEAR_BIG_MESSAGES:
		//CMessages::ClearBigMessagesOnly(); TODO
		//CHud::ClearBigMessagesExcept(2, 2); TODO
		CGarages::MessageEndTime = CGarages::MessageStartTime;
		return 0;
	case COMMAND_CLEAR_AREA_OF_OBJECTS:
	{
		CollectParameters(&m_nIp, 6);
		uint32 i = CPools::GetObjectPool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		while (i--) {
			CObject* pObject = CPools::GetObjectPool()->GetSlot(i);
			if (pObject && pObject->CanBeDeleted() && pObject->IsWithinArea(infX, infY, infZ, supX, supY, supZ)) {
				pObject->DeleteRwObject();
				CWorld::Remove(pObject);
				delete pObject;
			}
		}
		i = CPools::GetDummyPool()->GetSize();
		while (i--) {
			CDummy* pDummy = CPools::GetDummyPool()->GetSlot(i);
			if (pDummy && pDummy->IsObject() && pDummy->IsWithinArea(infX, infY, infZ, supX, supY, supZ)) {
				pDummy->DeleteRwObject();
				CWorld::Remove(pDummy);
				delete pDummy;
			}
		}
		return 0;
	}
	case COMMAND_LOAD_NON_STANDARD_PED_ANIM:
		CollectParameters(&m_nIp, 1);
		CPed::LoadNonStandardPedAnim((eWaitState)GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_UNLOAD_NON_STANDARD_PED_ANIM:
		CollectParameters(&m_nIp, 1);
		CPed::UnloadNonStandardPedAnim((eWaitState)GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_BUILD_WORLD_GEOMETRY:
		CollectParameters(&m_nIp, 1);
		if (/*gBuildWorldGeom*/ false) {
			//base::cWorldGeom::GetInstance()->Build(GET_INTEGER_PARAM(0));
			UpdateCompareFlag(true);
		}
		else {
			UpdateCompareFlag(false);
		}
		return 0;
	case COMMAND_STORE_BUILDING_SWAP:
	{
		CollectParameters(&m_nIp, 4);
		debug("mazahaka todo! COMMAND_STORE_BUILDING_SWAP\n");
		// base::cWorldGeom::GetInstance()->StoreBuildingSwap(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3) != 0);
		return 0;
	}
	case COMMAND_IS_MULTIPLAYER_ACTIVE:
#ifdef GTA_NETWORK
		UpdateCompareFlag(gIsMultiplayerGame);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_GET_MULTIPLAYER_MODE:
		SET_INTEGER_PARAM(0, 0); // TODO
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_MULTIPLAYER_SCRIPT_DONE:
		printf("COMMAND_MULTIPLAYER_SCRIPT_DONE\n");
		//gbStartingScriptsFromLua = false; TODO?
		return 0;
	case COMMAND_IS_MULTIPLAYER_SERVER:
		UpdateCompareFlag(false); // TODO?
		return 0;
	case COMMAND_IS_MULTIPLAYER_TEAM_GAME:
		UpdateCompareFlag(false); // TODO?
		return 0;
	case COMMAND_GET_MULTIPLAYER_TEAM_ID:
		SET_INTEGER_PARAM(0, 0); // TODO
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_DOES_SHORTCUT_TAXI_EXIST:
		UpdateCompareFlag(CGameLogic::pShortCutTaxi != nil);
		return 0;
	case COMMAND_SET_ONSCREEN_TIMER_COLOUR:
		CollectParameters(&m_nIp, 4);
		gbColour = CRGBA(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3));
		return 0;
	case COMMAND_SET_ONSCREEN_TIMER_BACKGROUND_COLOUR:
		CollectParameters(&m_nIp, 4);
		gbColour2 = CRGBA(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3));
		return 0;
	case COMMAND_REMOVE_CAR_BOOT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->IsCar());
		CAutomobile* pAutomobile = (CAutomobile*)pVehicle;
		pAutomobile->Damage.SetDoorStatus(DOOR_BOOT, DOOR_STATUS_MISSING);
		pAutomobile->SetDoorDamage(CAR_BOOT, DOOR_BOOT, true);
		return 0;
	}
	case COMMAND_ADD_POINT_3D_MARKER:
	{
		uint32 ip = m_nIp;
		uint32 id = (uint32)(uintptr)GetPointerToScriptVariable(&ip);
		static CVector vPreviousLocation;
		CollectParameters(&m_nIp, 7);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		if (vPreviousLocation != pos) {
			//C3dMarkers::CopyMarker(id, id - 1, 1, 1);
		}
		// TODO: 5 is not a valid type
		//C3dMarkers::PlaceMarker(id, 5, pos, GET_FLOAT_PARAM(3) * 0.7f, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), 255, 128, 0.0f, 1); // TODO: 0, 100.0f, 1, 0
		vPreviousLocation = pos;
		return 0;
	}
	case COMMAND_PRINT_HELP_ALWAYS:
	{
		// CHud::mAlwaysAllowHelpText = true; // TODO
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, true
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_ALWAYS:
	{
		// CHud::mAlwaysAllowHelpText = true; // TODO
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + true
		return 0;
	}
	case COMMAND_SET_CHAR_MAX_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_fHealth = GET_INTEGER_PARAM(1);
		pPed->m_fMaxHealth = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_SHOOT_TIMER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_nScriptShootTimer = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_ATTACK_TIMER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_nScriptAttackTimer = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_HELI_ROTOR_BLADES_FULLSPEED:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pHeli = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pHeli);
		if (pHeli->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI)
			pHeli->m_aWheelSpeed[1] = 0.22f;
		return 0;
	}
	case COMMAND_SET_CRUSHER_REWARD_MULTIPLIER:
	{
		CollectParameters(&m_nIp, 1);
		CGarages::CrusherRewardMultiplier = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SWAP_BUILDINGS:
	{
		CollectParameters(&m_nIp, 2);
		// base::cWorldStream::Instance()->SwapBuilding(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_STREAM_BUILDING_SWAPS:
	{
		// UpdateCompareFlag(base::cWorldStream::Instance()->StreamBuildingSwaps());
		UpdateCompareFlag(true);
		return 0;
	}
	case COMMAND_IS_WORLD_STREAMING_COMPLETE:
	{
		// UpdateCompareFlag(base::cWorldStream::Instance()->IsStreamingComplet());
		UpdateCompareFlag(true);
		return 0;
	}
	case COMMAND_SWAP_TO_STREAMED_SECTOR:
	{
		// base::cWorldStream::Instance()->SwapToStreamedSector();
		return 0;
	}
	case COMMAND_SET_CHAR_ATTACKS_PLAYER_WITH_COPS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bAttacksPlayerWithCops = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_REGISTER_FACE_PLANT_DISTANCE:
		CollectParameters(&m_nIp, 1);
		//CStats::LongestFacePlantDist = Max(CStats::LongestFacePlantDist, GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_ADD_EXPORTED_CARS:
		CollectParameters(&m_nIp, 1);
		// CStats::NumberOfExportedCars += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_TOTAL_EXPORT_CARS:
		CollectParameters(&m_nIp, 1);
		// CStats::TotalNumberOfCarExport = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_ADD_ARROW_3D_MARKER:
	{
		uint32 ip = m_nIp;
		uint32 id = (uint32)(uintptr)GetPointerToScriptVariable(&ip);
		CollectParameters(&m_nIp, 10);
		CVector pos = GET_VECTOR_PARAM(0);
		CVector dir = GET_VECTOR_PARAM(3);
		pos.z += GET_FLOAT_PARAM(9) + 7.0f;
		//C3dMarkers::PlaceMarker(id, MARKERTYPE_ARROW, pos, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8), 200, 1, 3.2f, 1, dir, 1.0f, 0, 0); - TODO
		return 0;
	}
	case todo__comm_995:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_995");
		return 0;
	}
	case todo__comm_996:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_996");
		return 0;
	}
	case COMMAND_IS_DEVELOPER:
#ifdef GTA_NETWORK
		UpdateCompareFlag(gDeveloperFlag || gIsMultiplayerGame);
#else
		UpdateCompareFlag(gDeveloperFlag);
#endif
		return 0;
	case COMMAND_SET_DEVELOPER_FLAG:
		CollectParameters(&m_nIp, 1);
		gDeveloperFlag = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_ATTACH_OBJECT_TO_CAR:
	{
		CollectParameters(&m_nIp, 5);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		CVector offset = GET_VECTOR_PARAM(2);
		// pObject->AttachObjectToEntity(pVehicle, offset);
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int32 CTheScripts::GetNewUniqueScriptSphereIndex(int32 index)
{
	if (ScriptSphereArray[index].m_Index >= UINT16_MAX - 1)
		ScriptSphereArray[index].m_Index = 1;
	else
		ScriptSphereArray[index].m_Index++;
	return (uint16)index | ScriptSphereArray[index].m_Index << 16;
}

int32 CTheScripts::GetActualScriptSphereIndex(int32 index)
{
	if (index == -1)
		return -1;
	uint16 check = (uint32)index >> 16;
	uint16 array_idx = index & (0xFFFF);
	script_assert(array_idx < ARRAY_SIZE(ScriptSphereArray));
	if (check != ScriptSphereArray[array_idx].m_Index)
		return -1;
	return array_idx;
}

void CTheScripts::DrawScriptSpheres()
{
	for (int i = 0; i < MAX_NUM_SCRIPT_SPHERES; i++) {
		if (ScriptSphereArray[i].m_bInUse)
			C3dMarkers::PlaceMarkerSet(ScriptSphereArray[i].m_Id, MARKERTYPE_CYLINDER, ScriptSphereArray[i].m_vecCenter, ScriptSphereArray[i].m_fRadius,
				SPHERE_MARKER_R, SPHERE_MARKER_G, SPHERE_MARKER_B, SPHERE_MARKER_A, SPHERE_MARKER_PULSE_PERIOD, SPHERE_MARKER_PULSE_FRACTION, 0);
	}
}

int32 CTheScripts::AddScriptSphere(int32 id, CVector pos, float radius)
{
	int16 i = 0;
	for (i = 0; i < MAX_NUM_SCRIPT_SPHERES; i++) {
		if (!ScriptSphereArray[i].m_bInUse)
			break;
	}
#ifdef FIX_BUGS
	if (i == MAX_NUM_SCRIPT_SPHERES)
		return -1;
#endif
	ScriptSphereArray[i].m_bInUse = true;
	ScriptSphereArray[i].m_Id = id;
	ScriptSphereArray[i].m_vecCenter = pos;
	ScriptSphereArray[i].m_fRadius = radius;
	return GetNewUniqueScriptSphereIndex(i);
}

void CTheScripts::RemoveScriptSphere(int32 index)
{
	index = GetActualScriptSphereIndex(index);
	if (index == -1)
		return;
	ScriptSphereArray[index].m_bInUse = false;
	ScriptSphereArray[index].m_Id = 0;
}

void CTheScripts::SwapNearestBuildingModel(float x, float y, float z, float radius, int mi1, int mi2)
{
	CVector pos(x, y, z);
	if (pos.z <= MAP_Z_LOW_LIMIT)
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
	if (mi1 < 0)
		mi1 = CTheScripts::UsedObjectArray[-mi1].index;
	if (mi2 < 0)
		mi2 = CTheScripts::UsedObjectArray[-mi2].index;
	int16 total;
	CEntity* apEntities[16];
	CWorld::FindObjectsOfTypeInRange(mi1, pos, radius, true, &total, 16, apEntities, true, false, false, false, false);
	if (total == 0)
		CWorld::FindObjectsOfTypeInRangeSectorList(mi1, CWorld::GetBigBuildingList(LEVEL_GENERIC), pos, radius, true, &total, 16, apEntities);
	if (total == 0)
		CWorld::FindObjectsOfTypeInRangeSectorList(mi1, CWorld::GetBigBuildingList(CTheZones::GetLevelFromPosition(&pos)), pos, radius, true, &total, 16, apEntities);
	CEntity* pClosestEntity = nil;
	float min_dist = 2.0f * radius;
	for (int i = 0; i < total; i++) {
		float dist = (apEntities[i]->GetPosition() - pos).Magnitude();
		if (dist < min_dist) {
			min_dist = dist;
			pClosestEntity = apEntities[i];
		}
	}
	CBuilding* pReplacedBuilding = ((CBuilding*)pClosestEntity);
	if (pReplacedBuilding) {
		pReplacedBuilding->ReplaceWithNewModel(mi2);
		AddToBuildingSwapArray(pReplacedBuilding, mi1, mi2);
	}
}

void CTheScripts::AddToBuildingSwapArray(CBuilding* pBuilding, int32 old_model, int32 new_model)
{
	int i = 0;
	bool found = false;
	while (i < MAX_NUM_BUILDING_SWAPS && !found) {
		if (BuildingSwapArray[i].m_pBuilding == pBuilding)
			found = true;
		else
			i++;
	}
	if (found) {
		if (BuildingSwapArray[i].m_nOldModel == new_model) {
			BuildingSwapArray[i].m_pBuilding = nil;
			BuildingSwapArray[i].m_nOldModel = BuildingSwapArray[i].m_nNewModel = -1;
		}
		else {
			BuildingSwapArray[i].m_nNewModel = new_model;
		}
	}
	else {
		i = 0;
		while (i < MAX_NUM_BUILDING_SWAPS && !found) {
			if (BuildingSwapArray[i].m_pBuilding == nil)
				found = true;
			else
				i++;
		}
		if (found) {
			BuildingSwapArray[i].m_pBuilding = pBuilding;
			BuildingSwapArray[i].m_nNewModel = new_model;
			BuildingSwapArray[i].m_nOldModel = old_model;
		}
	}
}

void CTheScripts::AddToInvisibilitySwapArray(CEntity* pEntity, bool remove)
{
	int i = 0;
	bool found = false;
	while (i < MAX_NUM_INVISIBILITY_SETTINGS && !found) {
		if (InvisibilitySettingArray[i] == pEntity)
			found = true;
		else
			i++;
	}
	if (found) {
		if (remove)
			InvisibilitySettingArray[i] = nil;
	}
	else if (!remove) {
		i = 0;
		while (i < MAX_NUM_INVISIBILITY_SETTINGS && !found) {
			if (InvisibilitySettingArray[i] == nil)
				found = true;
			else
				i++;
		}
		if (found)
			InvisibilitySettingArray[i] = pEntity;
	}
}

void CTheScripts::UndoBuildingSwaps()
{
	for (int i = 0; i < MAX_NUM_BUILDING_SWAPS; i++) {
		if (BuildingSwapArray[i].m_pBuilding) {
			BuildingSwapArray[i].m_pBuilding->ReplaceWithNewModel(BuildingSwapArray[i].m_nOldModel);
			BuildingSwapArray[i].m_pBuilding = nil;
			BuildingSwapArray[i].m_nOldModel = BuildingSwapArray[i].m_nNewModel = -1;
		}
	}
}

void CTheScripts::UndoEntityInvisibilitySettings()
{
	for (int i = 0; i < MAX_NUM_INVISIBILITY_SETTINGS; i++) {
		if (InvisibilitySettingArray[i]) {
			InvisibilitySettingArray[i]->bIsVisible = true;
			InvisibilitySettingArray[i] = nil;
		}
	}
}
