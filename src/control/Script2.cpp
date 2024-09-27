#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Camera.h"
#include "CarCtrl.h"
#include "CarGen.h"
#include "CivilianPed.h"
#include "CopPed.h"
#include "Cranes.h"
#include "DMAudio.h"
#include "EmergencyPed.h"
#include "Garages.h"
#include "General.h"
#include "Messages.h"
#include "Pad.h"
#include "PedRoutes.h"
#include "Pools.h"
#include "Population.h"
#include "Radar.h"
#include "Restart.h"
#include "Shadows.h"
#include "User.h"
#include "Wanted.h"
#include "WaterLevel.h"
#include "Weather.h"
#include "World.h"
#include "Zones.h"
//new
#include "Streaming.h"
#include "Bike.h"
#include "Darkel.h"
#include "Explosion.h"
#include "Pickups.h"
#include "CutsceneMgr.h"
#include "Coronas.h"
#include "Clock.h"
#include "Phones.h"
#include "GameLogic.h"
#include "Stats.h"
#include "Fire.h"
#include "ColStore.h"

// LCS: file done except TODOs

int8 CRunningScript::ProcessCommands300To399(int32 command)
{
	switch (command) {
	case COMMAND_IS_CAR_IN_AIR_PROPER:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->m_nCollisionRecords == 0);
		return 0;
	}
	case COMMAND_IS_CAR_UPSIDEDOWN:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetUp().z <= UPSIDEDOWN_UP_THRESHOLD);
		return 0;
	}
	case COMMAND_SET_POLICE_IGNORE_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->m_pWanted->m_bIgnoredByCops = true;
			CWorld::StopAllLawEnforcersInTheirTracks();
		}
		else {
			pPed->m_pWanted->m_bIgnoredByCops = false;
		}
		return 0;
	}
	case COMMAND_START_KILL_FRENZY:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CDarkel::StartFrenzy((eWeaponType)GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2),
			GET_INTEGER_PARAM(3), text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5),
			GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7) != 0, false);
		return 0;
	}
	case COMMAND_READ_KILL_FRENZY_STATUS:
	{
		SET_INTEGER_PARAM(0, CDarkel::ReadStatus());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SQRT:
	{
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Sqrt(GET_FLOAT_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D:
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D:
		LocateCharCarCommand(command, &m_nIp);
		return 0;
	case COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE:
		CollectParameters(&m_nIp, 2);
		SET_FLOAT_PARAM(0, CGeneral::GetRandomNumberInRange(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_GENERATE_RANDOM_INT_IN_RANGE:
		CollectParameters(&m_nIp, 2);
		SET_INTEGER_PARAM(0, CGeneral::GetRandomNumberInRange(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_LOCK_CAR_DOORS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_nDoorLock = (eCarLock)GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_EXPLODE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bCanBeDamaged = true;
		pVehicle->BlowUpCar(nil);
		return 0;
	}
	case COMMAND_ADD_EXPLOSION:
		CollectParameters(&m_nIp, 4);
		CExplosion::AddExplosion(nil, nil, (eExplosionType)GET_INTEGER_PARAM(3), GET_VECTOR_PARAM(0), 0, true); // last argument is 0 (default? - TODO)
		return 0;

	case COMMAND_IS_CAR_UPRIGHT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetUp().z >= 0.0f);
		return 0;
	}
	case COMMAND_TURN_CHAR_TO_FACE_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CVehicle* pVehicle = pSourcePed->bInVehicle ? pSourcePed->m_pMyVehicle : nil;
		CVector2D sourcePos = pSourcePed->bInVehicle ? pVehicle->GetPosition() : pSourcePed->GetPosition();
		CVector2D targetPos = pTargetPed->bInVehicle ? pTargetPed->m_pMyVehicle->GetPosition() : pTargetPed->GetPosition();
		float angle = CGeneral::GetATanOfXY(sourcePos.x - targetPos.x, sourcePos.y - targetPos.y) + HALFPI;
		if (angle > TWOPI)
			angle -= TWOPI;
		if (!pVehicle) {
			pSourcePed->m_fRotationCur = angle;
			pSourcePed->m_fRotationDest = angle;
			pSourcePed->SetHeading(angle);
		}
		return 0;
	}
	case COMMAND_CREATE_PICKUP:
	{
		CollectParameters(&m_nIp, 5);
		int16 model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		CVector pos = GET_VECTOR_PARAM(2);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, model, GET_INTEGER_PARAM(1), 0));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_HAS_PICKUP_BEEN_COLLECTED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CPickups::IsPickUpPickedUp(GET_INTEGER_PARAM(0)) != 0);
		return 0;
	case COMMAND_REMOVE_PICKUP:
		CollectParameters(&m_nIp, 1);
		CPickups::RemovePickUp(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_SET_TAXI_LIGHTS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		((CAutomobile*)pVehicle)->SetTaxiLight(GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_PRINT_BIG_Q:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddBigMessageQ(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1) - 1);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_BIG_Q:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddBigMessageWithNumberQ(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) - 1,
			GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_SET_GARAGE:
	{
		CollectParameters(&m_nIp, 9);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float supX = GET_FLOAT_PARAM(5);
		float supY = GET_FLOAT_PARAM(6);
		float supZ = GET_FLOAT_PARAM(7);
		SET_INTEGER_PARAM(0, CGarages::AddOne(infX, infY, infZ, X2, Y2, supX, supY, supZ, GET_INTEGER_PARAM(8), 0));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_TARGET_CAR_FOR_MISSION_GARAGE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pTarget;
		if (GET_INTEGER_PARAM(1) >= 0) {
			pTarget = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		}
		else {
			pTarget = nil;
		}
		CGarages::SetTargetCarForMissonGarage(GET_INTEGER_PARAM(0), pTarget);
		return 0;
	}
	case COMMAND_IS_CAR_IN_MISSION_GARAGE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::HasCarBeenDroppedOffYet(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_SET_FREE_BOMBS:
	{
		CollectParameters(&m_nIp, 1);
		CGarages::SetFreeBombs(GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_IS_CAR_ARMED_WITH_ANY_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar())
			UpdateCompareFlag(((CAutomobile*)pVehicle)->m_bombType != 0);
		else if (pVehicle->IsBike())
			UpdateCompareFlag(((CBike*)pVehicle)->m_bombType != 0);
		else
			UpdateCompareFlag(false);
#else
		CAutomobile* pCar = (CVehicle*)pVehicle;
		UpdateCompareFlag(pCar->m_bombType != 0); //TODO: enum
#endif
		return 0;
	}
	case COMMAND_APPLY_BRAKES_TO_PLAYERS_CAR:
		CollectParameters(&m_nIp, 2);
		CPad::GetPad(GET_INTEGER_PARAM(0))->bApplyBrakes = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	case COMMAND_SET_CHAR_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->m_fHealth = GET_INTEGER_PARAM(1);
		}
		else if (pPed->bInVehicle) {
			pPed->SetDead();
			if (!pPed->IsPlayer())
				pPed->FlagToDestroyWhenNextProcessed();
		}
		else {
			pPed->SetDie(); // last argument = 13 (default? TODO)
		}
		return 0;
	}
	case COMMAND_SET_CAR_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_fHealth = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_CHAR_HEALTH:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_fHealth);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CAR_HEALTH:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_fHealth);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CAR_ARMED_WITH_BOMB:
	{
		CollectParameters(&m_nIp, 2);
		CAutomobile* pVehicle = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar())
			UpdateCompareFlag(((CAutomobile*)pVehicle)->m_bombType == GET_INTEGER_PARAM(1));
		else if (pVehicle->IsBike())
			UpdateCompareFlag(((CBike*)pVehicle)->m_bombType == GET_INTEGER_PARAM(1));
		else
			UpdateCompareFlag(false);
#else
		CAutomobile* pCar = (CVehicle*)pVehicle;
		UpdateCompareFlag(pCar->m_bombType != 0); //TODO: enum
#endif
		return 0;
	}
	case COMMAND_CHANGE_CAR_COLOUR:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (GET_INTEGER_PARAM(1) >= 256 || GET_INTEGER_PARAM(2) >= 256)
			debug("CHANGE_CAR_COLOUR - Colours must be less than %d", 256);
		pVehicle->m_currentColour1 = GET_INTEGER_PARAM(1);
		pVehicle->m_currentColour2 = GET_INTEGER_PARAM(2);
		return 0;
	}
	case COMMAND_SWITCH_PED_ROADS_ON:
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
		ThePaths.SwitchPedRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, false);
		return 0;
	}
	case COMMAND_SWITCH_PED_ROADS_OFF:
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
		ThePaths.SwitchPedRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, true);
		return 0;
	}
	case COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pSourcePed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTargetPed);
		pSourcePed->SetLookFlag(pTargetPed, true, true);
		pSourcePed->SetLookTimer(60000);
		return 0;
	}
	case COMMAND_STOP_CHAR_LOOKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pSourcePed);
		pSourcePed->ClearLookFlag();
		pSourcePed->bKeepTryingToLook = false;
		if (pSourcePed->GetPedState() == PED_LOOK_HEADING || pSourcePed->GetPedState() == PED_LOOK_ENTITY)
			pSourcePed->RestorePreviousState();
		return 0;
	}
	case COMMAND_SET_GANG_PED_MODELS:
		CollectParameters(&m_nIp, 3);
		CGangs::SetGangPedModels(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_SET_GANG_CAR_MODEL:
		CollectParameters(&m_nIp, 2);
		CGangs::SetGangVehicleModel(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_SET_GANG_WEAPONS:
		CollectParameters(&m_nIp, 3);
		CGangs::SetGangWeapons(GET_INTEGER_PARAM(0), (eWeaponType)GET_INTEGER_PARAM(1), (eWeaponType)GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_SET_CHAR_OBJ_RUN_TO_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector pos;
		pos.x = GET_FLOAT_PARAM(1);
		pos.y = GET_FLOAT_PARAM(2);
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_RUN_TO_AREA, pos);
		return 0;
	}
	case COMMAND_LOAD_SPECIAL_CHARACTER:
	{
		CollectParameters(&m_nIp, 1);
		char name[16];
		strncpy(name, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			name[i] = tolower(name[i]);
		CStreaming::RequestSpecialChar(GET_INTEGER_PARAM(0) - 1, name, STREAMFLAGS_DEPENDENCY | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_HAS_SPECIAL_CHARACTER_LOADED:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CStreaming::HasSpecialCharLoaded(GET_INTEGER_PARAM(0) - 1));
		return 0;
	}
	case COMMAND_IS_PLAYER_IN_REMOTE_MODE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].IsPlayerInRemoteMode());
		return 0;
	case COMMAND_ARM_CAR_WITH_BOMB:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar()) {
			((CAutomobile*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
			((CAutomobile*)pVehicle)->m_pBombRigger = FindPlayerPed();
		}
		else if (pVehicle->IsBike()) {
			((CBike*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
			((CBike*)pVehicle)->m_pBombRigger = FindPlayerPed();
		}
#else
		((CAutomobile*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
		((CAutomobile*)pVehicle)->m_pBombRigger = FindPlayerPed();
#endif
		return 0;
	}
	case COMMAND_SET_CHAR_PERSONALITY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->SetPedStats((ePedStats)GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_SET_CUTSCENE_OFFSET:
		CollectParameters(&m_nIp, 3);
		CCutsceneMgr::SetCutsceneOffset(GET_VECTOR_PARAM(0));
		return 0;
	case COMMAND_SET_ANIM_GROUP_FOR_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_animGroup = (AssocGroupId)GET_INTEGER_PARAM(1);
		pPed->bOverrideMoveAnim = false;
		return 0;
	}
	case COMMAND_REQUEST_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		CStreaming::RequestModel(model, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		if (model == MI_MINIGUN)
#ifdef FIX_BUGS
			CStreaming::RequestModel(MI_MINIGUN2, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
#else
			CStreaming::RequestModel(MI_MINIGUN2, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | STREAMFLAGS_SCRIPTOWNED);
#endif
		return 0;
	}
	case COMMAND_HAS_MODEL_LOADED:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		UpdateCompareFlag(CStreaming::HasModelLoaded(model)/* || cWorldStream::Instance()->pDynamic(model, 0) */); // TODO
		return 0;
	}
	case COMMAND_MARK_MODEL_AS_NO_LONGER_NEEDED:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		if (m_bIsMissionScript)
			CStreaming::SetMissionDoesntRequireModel(model);
		else
			CStreaming::SetAmbientMissionDoesntRequireModel(model);
		return 0;
	}
	case COMMAND_GRAB_PHONE:
	{
		CollectParameters(&m_nIp, 2);
		SET_INTEGER_PARAM(0, gPhoneInfo.GrabPhone(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_TURN_PHONE_OFF:
	{
		CollectParameters(&m_nIp, 1);
		gPhoneInfo.SetPhoneMessage_JustOnce(GET_INTEGER_PARAM(0), nil, nil, nil, nil, nil, nil);
		return 0;
	}
	case COMMAND_DRAW_CORONA:
	{
		uint32 ip = m_nIp;
		int32* ptr = GetPointerToScriptVariable(&ip);
		CollectParameters(&m_nIp, 9);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CCoronas::RegisterCorona((uintptr)ptr, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8),
			255, pos, -GET_FLOAT_PARAM(3), 450.0f, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), 1, 0, 0, 0.0f);
		return 0;
	}
	case COMMAND_STORE_WEATHER:
		CWeather::StoreWeatherState();
		return 0;
	case COMMAND_RESTORE_WEATHER:
		CWeather::RestoreWeatherState();
	case COMMAND_STORE_CLOCK:
		CClock::StoreClock();
		return 0;
	case COMMAND_RESTORE_CLOCK:
		CClock::RestoreClock();
		return 0;
	case COMMAND_RESTART_CRITICAL_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRestart::OverrideNextRestart(pos, GET_FLOAT_PARAM(3));
		if (CWorld::Players[CWorld::PlayerInFocus].m_WBState != WBSTATE_PLAYING)
			printf("RESTART_CRITICAL_MISSION - Player state is not PLAYING\n");
		CWorld::Players[CWorld::PlayerInFocus].PlayerFailedCriticalMission();
		return 0;
	}
	case todo__comm_363:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_363");
		return 0;
	}
	/*case COMMAND_SET_COLL_OBJ_NO_OBJ:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_NONE);
		return 0;
	case COMMAND_SET_COLL_OBJ_WAIT_ON_FOOT:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_WAIT_ON_FOOT);
		return 0;
	case COMMAND_SET_COLL_OBJ_FLEE_ON_FOOT_TILL_SAFE:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);
		return 0;
	case COMMAND_SET_COLL_OBJ_GUARD_SPOT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GUARD_AREA, pos);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GUARD_AREA:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GUARD_AREA, pos, radius);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_WAIT_IN_CAR:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_WAIT_IN_CAR);
		return 0;
	case COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ON_FOOT, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ANY_MEANS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_CHAR_ON_FOOT, pPed);
		return 0;
	}*/
	case todo__comm_374:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_374");
		return 0;
	}
	/*case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_ENTER_CAR_AS_PASSENGER, pVehicle);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_DRIVER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_ENTER_CAR_AS_DRIVER, pVehicle);
		return 0;
	}*/
	case todo__comm_377:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_377");
		return 0;
	}
	case todo__comm_378:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_378");
		return 0;
	}
	/*case COMMAND_SET_COLL_OBJ_GOTO_AREA_ON_FOOT:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_AREA_ON_FOOT, pos, radius);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GOTO_COORD_ON_FOOT:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), CWorld::FindGroundZForCoord(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_AREA_ON_FOOT, pos);
		return 0;
	}*/
	case todo__comm_381:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_381");
		return 0;
	}
	case todo__comm_382:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_382");
		return 0;
	}
	/*case COMMAND_SET_COLL_OBJ_LEAVE_CAR:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_LEAVE_CAR);
		return 0;*/
	case todo__comm_384:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_384");
		return 0;
	}
	case todo__comm_385:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_385");
		return 0;
	}
	case todo__comm_386:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_386");
		return 0;
	}
	case todo__comm_387:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_387");
		return 0;
	}
	/*case COMMAND_SET_COLL_OBJ_FOLLOW_ROUTE:
		CollectParameters(&m_nIp, 3);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FOLLOW_ROUTE, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_SET_COLL_OBJ_RUN_TO_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), CWorld::FindGroundZForCoord(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_RUN_TO_AREA, pos);
		return 0;
	}*/
	case todo__comm_390:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_390");
		return 0;
	}
	case todo__comm_391:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_391");
		return 0;
	}
	case todo__comm_392:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_392");
		return 0;
	}
	case todo__comm_393:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_393");
		return 0;
	}
	case todo__comm_394:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_394");
		return 0;
	}
	case todo__comm_395:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_395");
		return 0;
	}
	case todo__comm_396:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_396");
		return 0;
	}
	case todo__comm_397:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_397");
		return 0;
	}
	case todo__comm_398:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_398");
		return 0;
	}
	case todo__comm_399:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_399");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands400To499(int32 command)
{
	switch (command) {
	case todo__comm_400:
	case todo__comm_401:
	case todo__comm_402:
	case todo__comm_403:
	case todo__comm_404:
	case todo__comm_405:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_400-405");
		return 0;
	}
	case todo__comm_406:
	case todo__comm_407:
	case todo__comm_408:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_406-408");
		return 0;
	}
	case todo__comm_409:
	case todo__comm_410:
	case todo__comm_411:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_409-411");
		return 0;
	}
	case todo__comm_413:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_413");
		return 0;
	}
	case todo__comm_412:
	case todo__comm_414:
	case todo__comm_415:
	case todo__comm_416:
	case todo__comm_417:
	case todo__comm_418:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_412-418");
		return 0;
	}
	case todo__comm_419:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_419");
		return 0;
	}
	case COMMAND_SET_CHAR_HEED_THREATS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bRespondsToThreats = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_GET_CONTROLLER_MODE:
#if defined(GTA_PC) && !defined(DETECT_PAD_INPUT_SWITCH)
		SET_INTEGER_PARAM(0, 0);
#else
		SET_INTEGER_PARAM(0, CPad::IsAffectedByController ? CPad::GetPad(0)->Mode : 0);
#endif
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_CAN_RESPRAY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		//assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		// they DO call this for bikes, we don't really want to destroy the structure...
#ifdef FIX_BUGS
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
#endif
			((CAutomobile*)pVehicle)->bFixedColour = (GET_INTEGER_PARAM(1) == 0);
#ifdef FIX_BUGS
		else if (pVehicle->m_vehType == VEHICLE_TYPE_BIKE)
			((CBike*)pVehicle)->bFixedColour = (GET_INTEGER_PARAM(1) == 0);
#endif
		
		return 0;
	}
	case COMMAND_UNLOAD_SPECIAL_CHARACTER:
		CollectParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CStreaming::SetMissionDoesntRequireSpecialChar(GET_INTEGER_PARAM(0) - 1);
		else
			CStreaming::SetAmbientMissionDoesntRequireSpecialChar(GET_INTEGER_PARAM(0) - 1);
		return 0;
	case COMMAND_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER:
		CDarkel::ResetModelsKilledByPlayer();
		return 0;
	case COMMAND_GET_NUM_OF_MODELS_KILLED_BY_PLAYER:
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CDarkel::QueryModelsKilledByPlayer(GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_CREATE_OBJECT_NO_OFFSET:
	{
		CollectParameters(&m_nIp, 4);
		script_assert(false && "TMP REMOVED COMMAND_CREATE_OBJECT_NO_OFFSET");
		return 0;

		int mi = GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::UsedObjectArray[-GET_INTEGER_PARAM(0)].index;
		CObject* pObj = new CObject(mi, false);
;		pObj->ObjectCreatedBy = MISSION_OBJECT;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pObj->SetPosition(pos);
		pObj->SetOrientation(0.0f, 0.0f, 0.0f);
		pObj->GetMatrix().UpdateRW();
		pObj->UpdateRwFrame();
		CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(mi);
		if (pModelInfo->IsBuilding() && ((CSimpleModelInfo*)pModelInfo)->m_isBigBuilding)
			pObj->SetupBigBuilding();
		CTheScripts::ClearSpaceForMissionEntity(pos, pObj);
		CWorld::Add(pObj);
		SET_INTEGER_PARAM(0, CPools::GetObjectPool()->GetIndex(pObj));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_IS_BOAT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT);
		return 0;
	}
	case COMMAND_IS_CHAR_STOPPED:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(CTheScripts::IsPedStopped(pPed));
		return 0;
	}
	case COMMAND_MESSAGE_WAIT:
		CollectParameters(&m_nIp, 2);
		m_nWakeTime = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(0);
		if (GET_INTEGER_PARAM(1) != 0)
			m_bSkipWakeTime = true;
		return 1;
	case COMMAND_SWITCH_WIDESCREEN:
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0) != 0)
			TheCamera.SetWideScreenOn();
		else {
			// TODO(LCS): unknown field
			TheCamera.SetWideScreenOff();
		}
		return 0;
	case COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyDamagedByPlayer = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CAR_ONLY_DAMAGED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bOnlyDamagedByPlayer = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CHAR_PROOFS:
	{
		CollectParameters(&m_nIp, 6);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bBulletProof = (GET_INTEGER_PARAM(1) != 0);
		pPed->bFireProof = (GET_INTEGER_PARAM(2) != 0);
		pPed->bExplosionProof = (GET_INTEGER_PARAM(3) != 0);
		pPed->bCollisionProof = (GET_INTEGER_PARAM(4) != 0);
		pPed->bMeleeProof = (GET_INTEGER_PARAM(5) != 0);
		return 0;
	}
	case COMMAND_SET_CAR_PROOFS:
	{
		CollectParameters(&m_nIp, 6);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bBulletProof = (GET_INTEGER_PARAM(1) != 0);
		pVehicle->bFireProof = (GET_INTEGER_PARAM(2) != 0);
		pVehicle->bExplosionProof = (GET_INTEGER_PARAM(3) != 0);
		pVehicle->bCollisionProof = (GET_INTEGER_PARAM(4) != 0);
		pVehicle->bMeleeProof = (GET_INTEGER_PARAM(5) != 0);
		return 0;
	}
	case COMMAND_IS_CAR_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pVehicle && pVehicle->bIsInWater);
		return 0;
	}
	case COMMAND_GET_CLOSEST_CHAR_NODE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CPathNode* pNode = &ThePaths.m_pathNodes[ThePaths.FindNodeClosestToCoors(pos, 1, 800.0f, true)];
		SET_VECTOR_PARAM(0, pNode->GetPosition());
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_GET_CLOSEST_CAR_NODE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(ThePaths.FindNodeClosestToCoors(pos, 0, 800.0f, true, true)));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_CAR_GOTO_COORDINATES_ACCURATE:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += pVehicle->GetDistanceFromCentreOfMassToBaseOfModel();
		uint8 nOldMission = pVehicle->AutoPilot.m_nCarMission;
		if (CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, pos, false))
			pVehicle->AutoPilot.m_nCarMission = MISSION_GOTO_COORDS_STRAIGHT_ACCURATE;
		else
			pVehicle->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_ACCURATE;
		pVehicle->SetStatus(STATUS_PHYSICS);
		pVehicle->bEngineOn = true;
		pVehicle->AutoPilot.m_nCruiseSpeed = Max(1, pVehicle->AutoPilot.m_nCruiseSpeed);
		if (nOldMission != pVehicle->AutoPilot.m_nCarMission)
			pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	case COMMAND_IS_CAR_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pVehicle->GetBoundCentre(), pVehicle->GetBoundRadius()));
		return 0;
	}
	case COMMAND_IS_CHAR_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pPed->GetBoundCentre(), pPed->GetBoundRadius()));
		return 0;
	}
	case COMMAND_IS_OBJECT_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pObject->GetBoundCentre(), pObject->GetBoundRadius()));
		return 0;
	}
	case COMMAND_GOSUB_FILE:
	{
		CollectParameters(&m_nIp, 2);
		script_assert(m_nStackPointer < MAX_STACK_DEPTH);
		m_anStack[m_nStackPointer++] = m_nIp;
		SetIP(GET_INTEGER_PARAM(0));
		// GET_INTEGER_PARAM(1) == filename
		return 0;
	}
	case COMMAND_GET_GROUND_Z_FOR_3D_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		bool success;
		SET_FLOAT_PARAM(0, CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &success));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_START_SCRIPT_FIRE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_INTEGER_PARAM(0, gFireManager.StartScriptFire(pos, nil, 0.8f, 1));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_SCRIPT_FIRE_EXTINGUISHED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(gFireManager.IsScriptFireExtinguish(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_REMOVE_SCRIPT_FIRE:
		CollectParameters(&m_nIp, 1);
		gFireManager.RemoveScriptFire(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_BOAT_GOTO_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &pos.z, false);
		pBoat->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_ASTHECROWSWIMS;
		pBoat->AutoPilot.m_vecDestinationCoors = pos;
		pBoat->SetStatus(STATUS_PHYSICS);
		pBoat->bEngineOn = true;
		pBoat->AutoPilot.m_nCruiseSpeed = Max(1, pBoat->AutoPilot.m_nCruiseSpeed);
		pBoat->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	case COMMAND_BOAT_STOP:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		pBoat->AutoPilot.m_nCarMission = MISSION_NONE;
		pBoat->SetStatus(STATUS_PHYSICS);
		pBoat->bEngineOn = false;
		pBoat->AutoPilot.m_nCruiseSpeed = 0;
		return 0;
	}
	case COMMAND_IS_PLAYER_SHOOTING_IN_AREA:
	{
		CollectParameters(&m_nIp, 6);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		UpdateCompareFlag(pPed->bIsShooting && pPed->IsWithinArea(x1, y1, x2, y2));
		if (GET_INTEGER_PARAM(5))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, MAP_Z_LOW_LIMIT);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugSquare(x1, y1, x2, y2);
		*/
		return 0;
	}
	case COMMAND_IS_CURRENT_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) == pPed->GetWeapon()->m_eWeaponType);
		return 0;
	}
	case COMMAND_SET_BOAT_CRUISE_SPEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		pBoat->AutoPilot.m_nCruiseSpeed = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_GET_RANDOM_CHAR_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float x2 = GET_FLOAT_PARAM(2);
		float y2 = GET_FLOAT_PARAM(3);
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1){
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
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7)))
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
	case COMMAND_IS_PLAYER_IN_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->IsTaxi());
		return 0;
	}
	case COMMAND_IS_PLAYER_SHOOTING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bIsShooting);
		return 0;
	}
	case COMMAND_IS_CHAR_SHOOTING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bIsShooting);
		return 0;
	}
	case COMMAND_CREATE_MONEY_PICKUP:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, MI_MONEY, PICKUP_MONEY, GET_INTEGER_PARAM(3)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_ACCURACY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_wepAccuracy = Min(100, GET_INTEGER_PARAM(1) * 1.25f);
		return 0;
	}
	case COMMAND_GET_CAR_SPEED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_FLOAT_PARAM(0, pVehicle->GetSpeed().Magnitude() * GAME_SPEED_TO_METERS_PER_SECOND);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOAD_CUTSCENE:
	{
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		// unknown call FUN_29df68(name) on PS2 - not on PSP
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CColStore::RemoveAllCollision();
		CCutsceneMgr::LoadCutsceneData(name);
		return 0;
	}
	case COMMAND_START_CUTSCENE:
		CCutsceneMgr::StartCutscene();
		return 0;
	case COMMAND_HAS_CUTSCENE_FINISHED:
	{
		bool bFinished = CCutsceneMgr::HasCutsceneFinished();
		if (bFinished)
			printf("cutscene has now finished\n");
		UpdateCompareFlag(bFinished);
		return 0;
	}
	case COMMAND_CLEAR_CUTSCENE:
		// unknown call on PS2 FUN_29DFA0() - not on PSP
		printf("clear cutscene\n");
		CCutsceneMgr::DeleteCutsceneData();
		return 0;
	case COMMAND_RESTORE_CAMERA_JUMPCUT:
		TheCamera.RestoreWithJumpCut();
		return 0;
	case COMMAND_IS_CHAR_MODEL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) == pPed->GetModelIndex());
		return 0;
	}
	case COMMAND_LOAD_SPECIAL_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			name[i] = tolower(name[i]);
		CStreaming::RequestSpecialModel(GET_INTEGER_PARAM(0), name, STREAMFLAGS_DEPENDENCY | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_SIN:
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Sin(DEGTORAD(GET_FLOAT_PARAM(0))));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_COS:
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Cos(DEGTORAD(GET_FLOAT_PARAM(0))));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_GET_CAR_FORWARD_X:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float forwardX = pVehicle->GetForward().x / pVehicle->GetForward().Magnitude2D();
		SET_FLOAT_PARAM(0, forwardX);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CAR_FORWARD_Y:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float forwardY = pVehicle->GetForward().y / pVehicle->GetForward().Magnitude2D();
		SET_FLOAT_PARAM(0, forwardY);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_CHANGE_GARAGE_TYPE:
		CollectParameters(&m_nIp, 2);
		CGarages::ChangeGarageType(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), 0);
		return 0;
	case COMMAND_ACTIVATE_CRUSHER_CRANE:
	{
		CollectParameters(&m_nIp, 10);
		float infX = GET_FLOAT_PARAM(2);
		float infY = GET_FLOAT_PARAM(3);
		float supX = GET_FLOAT_PARAM(4);
		float supY = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(4);
			supX = GET_FLOAT_PARAM(2);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(5);
			supY = GET_FLOAT_PARAM(3);
		}
		CCranes::ActivateCrane(infX, supX, infY, supY,
			GET_FLOAT_PARAM(6), GET_FLOAT_PARAM(7), GET_FLOAT_PARAM(8),
			DEGTORAD(GET_FLOAT_PARAM(9)), true, false,
			GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1));
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS_NOW:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS_SOON:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_3_NUMBERS:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_3_NUMBERS_NOW:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_4_NUMBERS:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 6);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_6_NUMBERS:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5));
		return 0;
	}
	case COMMAND_PLAYER_MADE_PROGRESS:
		CollectParameters(&m_nIp, 1);
		CStats::ProgressMade += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_PROGRESS_TOTAL:
		CollectParameters(&m_nIp, 1);
		CStats::TotalProgressInGame = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_JUMP_DISTANCE:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpDistance = Max(CStats::MaximumJumpDistance, GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_HEIGHT:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpHeight = Max(CStats::MaximumJumpHeight, GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_FLIPS:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpFlips = Max(CStats::MaximumJumpFlips, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_SPINS:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpSpins = Max(CStats::MaximumJumpSpins, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_STUNT:
		CollectParameters(&m_nIp, 1);
		CStats::BestStuntJump = Max(CStats::BestStuntJump, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_UNIQUE_JUMP_FOUND:
		++CStats::NumberOfUniqueJumpsFound;
		return 0;
	case COMMAND_SET_UNIQUE_JUMPS_TOTAL:
		CollectParameters(&m_nIp, 1);
		CStats::TotalNumberOfUniqueJumps = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI:
		++CStats::PassengersDroppedOffWithTaxi;
		return 0;
	case COMMAND_REGISTER_MONEY_MADE_TAXI:
		CollectParameters(&m_nIp, 1);
		CStats::MoneyMadeWithTaxi += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_MISSION_GIVEN:
		++CStats::MissionsGiven;
		return 0;
	case COMMAND_REGISTER_MISSION_PASSED:
	{
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		strncpy(CStats::LastMissionPassedName, name, KEY_LENGTH_IN_SCRIPT);
		++CStats::MissionsPassed;
		CStats::CheckPointReachedSuccessfully();
		CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMilliseconds();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	}
	case COMMAND_SET_CHAR_RUNNING:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIsRunning = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_REMOVE_ALL_SCRIPT_FIRES:
		gFireManager.RemoveAllScriptFires();
		return 0;
	case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		bool result = false;
		if (!pPed)
			printf("HAS_CHAR_BEEN_DAMAGED_BY_WEAPON - Character doesn't exist\n");
		else {
			if (GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYMELEE || GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYWEAPON)
				result = CheckDamagedWeaponType(pPed->m_lastWepDam, GET_INTEGER_PARAM(1));
			else
				result = GET_INTEGER_PARAM(1) == pPed->m_lastWepDam;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		bool result = false;
		if (!pVehicle)
			printf("HAS_CAR_BEEN_DAMAGED_BY_WEAPON - Vehicle doesn't exist\n");
		else {
			if (GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYMELEE || GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYWEAPON)
				result = CheckDamagedWeaponType(pVehicle->m_nLastWeaponDamage, GET_INTEGER_PARAM(1));
			else
				result = GET_INTEGER_PARAM(1) == pVehicle->m_nLastWeaponDamage;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_PLAYERS_GROUP:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pLeader = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		script_assert(pPed);
		script_assert(pLeader);
		UpdateCompareFlag(pPed->m_leader == pLeader && !pPed->bWaitForLeaderToComeCloser);
		return 0;
	}
	case COMMAND_EXPLODE_CHAR_HEAD:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->InflictDamage(nil, WEAPONTYPE_SNIPERRIFLE, 1000.0f, PEDPIECE_HEAD, 0);
		return 0;
	}
	case COMMAND_ANCHOR_BOAT:
	{
		CollectParameters(&m_nIp, 2);
		CBoat* pBoat = (CBoat*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pBoat && pBoat->m_vehType == VEHICLE_TYPE_BOAT);
		pBoat->m_bIsAnchored = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_ZONE_GROUP:
	{
		char zone[KEY_LENGTH_IN_SCRIPT];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, zone);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CollectParameters(&m_nIp, 2);
		int zone_id = CTheZones::FindZoneByLabelAndReturnIndex(zone, ZONE_INFO);
		if (zone_id < 0) {
			printf("Couldn't find zone - %s\n", zone);
			return 0;
		}
		while (zone_id >= 0) {
			CTheZones::SetPedGroup(zone_id, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
			zone_id = CTheZones::FindNextZoneByLabelAndReturnIndex(zone, ZONE_INFO);
		}
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}
