#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Boat.h"
#include "CarCtrl.h"
#include "Clock.h"
#include "ColStore.h"
#include "Coronas.h"
#include "Cranes.h"
#include "CutsceneMgr.h"
#include "Darkel.h"
#include "Explosion.h"
#include "Fire.h"
#include "General.h"
#include "Garages.h"
#include "Heli.h"
#include "Messages.h"
#include "Pad.h"
#include "ParticleObject.h"
#include "Phones.h"
#include "Pickups.h"
#include "PointLights.h"
#include "Population.h"
#include "Pools.h"
#include "ProjectileInfo.h"
#include "Radar.h"
#include "Restart.h"
#include "Stats.h"
#include "Streaming.h"
#include "User.h"
#include "WaterLevel.h"
#include "Weather.h"
#include "Zones.h"
#include "GameLogic.h"
#include "Bike.h"
#include "Wanted.h"
//new
#include "AnimBlendAssociation.h"
#include "DMAudio.h"
#include "BulletInfo.h"
#include "SpecialFX.h"
#include "PedRoutes.h"
#include "CivilianPed.h"
#include "CarAI.h"
#include "Hud.h"
#include "Frontend.h"
#include "FileMgr.h"
#include "CustomSoundTrack.h"
#include "Credits.h"
#include "Particle.h"
#include "main.h"
#include "Ropes.h"
#include "Timecycle.h"
#include "SetPieces.h"
#include "KeyGen.h"
#include "Remote.h"
#include "Rubbish.h"

// LCS: file done except TODOs

#ifdef FIX_BUGS
static bool
IsSlideObjectUsedWrongByScript(const CVector &posTarget, const CVector &slideBy)
{
	// TODO?
	return false;
}
#endif


int8 CRunningScript::ProcessCommands500To599(int32 command)
{
	char strbuff[52];
	char onscreen_str[KEY_LENGTH_IN_SCRIPT];
	CMatrix tmp_matrix;
	switch (command) {
	case COMMAND_START_CAR_FIRE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, gFireManager.StartScriptFire(pVehicle->GetPosition(), pVehicle, 0.8f, 1));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_START_CHAR_FIRE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, gFireManager.StartScriptFire(pPed->GetPosition(), pPed, 0.8f, 1));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA:
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
			if (!pVehicle->bUsesCollision)
				continue;
			if (GET_INTEGER_PARAM(4) != pVehicle->GetModelIndex() && GET_INTEGER_PARAM(4) >= 0)
				continue;
			if (pVehicle->VehicleCreatedBy != RANDOM_VEHICLE)
				continue;
			if (!pVehicle->IsWithinArea(infX, infY, supX, supY))
				continue;
			handle = CPools::GetVehiclePool()->GetIndex(pVehicle);
			pVehicle->VehicleCreatedBy = MISSION_VEHICLE;
			++CCarCtrl::NumMissionCars;
			--CCarCtrl::NumRandomCars;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(handle, CLEANUP_CAR);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_HAS_RESPRAY_HAPPENED:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::HasResprayHappened(GET_INTEGER_PARAM(0)));
		return 0;
	}
	case COMMAND_SET_CAMERA_ZOOM:
	{
		CollectParameters(&m_nIp, 1);
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FOLLOWPED)
			TheCamera.SetZoomValueFollowPedScript(GET_INTEGER_PARAM(0));
		else if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_CAM_ON_A_STRING)
			TheCamera.SetZoomValueCamStringScript(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_CREATE_PICKUP_WITH_AMMO:
	{
		CollectParameters(&m_nIp, 6);

		//script_assert(false && "TMP REMOVED COMMAND_CREATE_PICKUP_WITH_AMMO BY MI");
		//return 0;

		int16 model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		CVector pos = GET_VECTOR_PARAM(3);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, model, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case todo__comm_506:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_506");
		return 0;
	}
	case COMMAND_SET_PLAYER_NEVER_GETS_TIRED:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayer = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayer->m_bInfiniteSprint = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_PLAYER_FAST_RELOAD:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayer = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayer->m_bFastReload = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CHAR_BLEEDING:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bPedIsBleeding = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case todo__comm_510:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_510");
		return 0;
	}
	case COMMAND_SET_FREE_RESPRAYS:
		CollectParameters(&m_nIp, 1);
		CGarages::SetFreeResprays(GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_SET_CHAR_VISIBLE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIsVisible = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CAR_VISIBLE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bIsVisible = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_IS_AREA_OCCUPIED:
	{
		CollectParameters(&m_nIp, 11);
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
		int16 total;
		CWorld::FindObjectsIntersectingCube(CVector(infX, infY, infZ), CVector(supX, supY, supZ), &total, 2, nil,
			!!GET_INTEGER_PARAM(6), !!GET_INTEGER_PARAM(7), !!GET_INTEGER_PARAM(8), !!GET_INTEGER_PARAM(9), !!GET_INTEGER_PARAM(10));
		UpdateCompareFlag(total > 0);
		return 0;
	}
	case COMMAND_DISPLAY_TEXT:
	{
		CollectParameters(&m_nIp, 2);
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtY = GET_FLOAT_PARAM(1);
		uint16 len = CMessages::GetWideStringLength(text);
		for (uint16 i = 0; i < len; i++)
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_Text[i] = text[i];
		for (uint16 i = len; i < SCRIPT_TEXT_MAX_LENGTH; i++)
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_Text[i] = 0;
		++CTheScripts::NumberOfIntroTextLinesThisFrame;
		return 0;
	}
	case COMMAND_SET_TEXT_SCALE:
	{
		CollectParameters(&m_nIp, 2);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fScaleX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fScaleY = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_SET_TEXT_COLOUR:
	{
		CollectParameters(&m_nIp, 4);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_sColor =
			CRGBA(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3));
		return 0;
	}
	case COMMAND_SET_TEXT_JUSTIFY:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_bJustify = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_SET_TEXT_CENTRE:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_bCentered = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_SET_TEXT_WRAPX:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fWrapX = GET_FLOAT_PARAM(0);
		return 0;
	}
	case todo__comm_521:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_521");
		return 0;
	}
	case COMMAND_SET_TEXT_BACKGROUND:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_bBackground = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_ROTATE_OBJECT:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		float fx = pObject->GetForward().x;
		float fy = pObject->GetForward().y;
		float heading = LimitAngleOnCircle(
			RADTODEG(Atan2(-pObject->GetForward().x, pObject->GetForward().y)));
		float headingTarget = GET_FLOAT_PARAM(1);
#ifdef FIX_BUGS
		float rotateBy = GET_FLOAT_PARAM(2) * CTimer::GetTimeStepFix();
#else
		float rotateBy = GET_FLOAT_PARAM(2);
#endif
		if (headingTarget == heading) { // using direct comparasion here is fine
			UpdateCompareFlag(true);
			return 0;
		}
		float angleClockwise = LimitAngleOnCircle(headingTarget - heading);
		float angleCounterclockwise = LimitAngleOnCircle(heading - headingTarget);
		float newHeading;
		if (angleClockwise < angleCounterclockwise)
			newHeading = rotateBy < angleClockwise ? heading + rotateBy : headingTarget;
		else
			newHeading = rotateBy < angleCounterclockwise ? heading - rotateBy : headingTarget;
		bool obstacleInPath = false;
		if (GET_INTEGER_PARAM(3)) {
			CVector pos = pObject->GetPosition();
			tmp_matrix.SetRotateZ(DEGTORAD(newHeading));
			tmp_matrix.GetPosition() += pos;
			CColModel* pColModel = pObject->GetColModel();
			CVector cp1 = tmp_matrix * pColModel->boundingBox.min;
			CVector cp2 = tmp_matrix * CVector(pColModel->boundingBox.max.x, pColModel->boundingBox.min.y, pColModel->boundingBox.min.z);
			CVector cp3 = tmp_matrix * CVector(pColModel->boundingBox.min.x, pColModel->boundingBox.max.y, pColModel->boundingBox.min.z);
			CVector cp4 = tmp_matrix * CVector(pColModel->boundingBox.min.x, pColModel->boundingBox.min.y, pColModel->boundingBox.max.z);
			int16 collisions;
			CWorld::FindObjectsIntersectingAngledCollisionBox(pColModel->boundingBox, tmp_matrix, pos,
				Min(cp1.x, Min(cp2.x, Min(cp3.x, cp4.x))),
				Min(cp1.y, Min(cp2.y, Min(cp3.y, cp4.y))),
				Max(cp1.x, Max(cp2.x, Max(cp3.x, cp4.x))),
				Max(cp1.y, Max(cp2.y, Max(cp3.y, cp4.y))),
				&collisions, 2, nil, false, true, true, false, false);
			if (collisions > 0)
				obstacleInPath = true;
		}
		if (obstacleInPath) {
			UpdateCompareFlag(true);
			return 0;
		}
		pObject->SetHeading(DEGTORAD(newHeading));
		pObject->GetMatrix().UpdateRW();
		pObject->UpdateRwFrame();
		UpdateCompareFlag(newHeading == headingTarget); // using direct comparasion here is fine
		return 0;
	}
	case COMMAND_SLIDE_OBJECT:
	{
		CollectParameters(&m_nIp, 8);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVector pos = pObject->GetPosition();
		CVector posTarget = GET_VECTOR_PARAM(1);
		CVector slideBy = GET_VECTOR_PARAM(4);
#ifdef FIX_BUGS
		// the check is a hack for original script, where some objects are moved
		// via SLIDE_OBJECT instead of SET_OBJECT_POSITION
		// assuming the slide will take exactly one frame, which is true
		// only without accounting time step (which is a bug)
		if (!IsSlideObjectUsedWrongByScript(posTarget, slideBy))
			slideBy *= CTimer::GetTimeStepFix();
#endif
		if (posTarget == pos) { // using direct comparasion here is fine
			UpdateCompareFlag(true);
			return 0;
		}
		CVector posDiff = pos - posTarget;
		CVector newPosition;
		if (posDiff.x < 0)
			newPosition.x = -posDiff.x < slideBy.x ? posTarget.x : pos.x + slideBy.x;
		else
			newPosition.x = posDiff.x < slideBy.x ? posTarget.x : pos.x - slideBy.x;
		if (posDiff.y < 0)
			newPosition.y = -posDiff.y < slideBy.y ? posTarget.y : pos.y + slideBy.y;
		else
			newPosition.y = posDiff.y < slideBy.y ? posTarget.y : pos.y - slideBy.y;
		if (posDiff.z < 0)
			newPosition.z = -posDiff.z < slideBy.z ? posTarget.z : pos.z + slideBy.z;
		else
			newPosition.z = posDiff.z < slideBy.z ? posTarget.z : pos.z - slideBy.z;
		bool obstacleInPath = false;
		if (GET_INTEGER_PARAM(7)) {
			tmp_matrix = pObject->GetMatrix();
			tmp_matrix.GetPosition() = newPosition;
			CColModel* pColModel = pObject->GetColModel();
			CVector cp1 = tmp_matrix * pColModel->boundingBox.min;
			CVector cp2 = tmp_matrix * CVector(pColModel->boundingBox.max.x, pColModel->boundingBox.min.y, pColModel->boundingBox.min.z);
			CVector cp3 = tmp_matrix * CVector(pColModel->boundingBox.min.x, pColModel->boundingBox.max.y, pColModel->boundingBox.min.z);
			CVector cp4 = tmp_matrix * CVector(pColModel->boundingBox.min.x, pColModel->boundingBox.min.y, pColModel->boundingBox.max.z);
			int16 collisions;
			CWorld::FindObjectsIntersectingAngledCollisionBox(pColModel->boundingBox, tmp_matrix, newPosition,
				Min(cp1.x, Min(cp2.x, Min(cp3.x, cp4.x))),
				Min(cp1.y, Min(cp2.y, Min(cp3.y, cp4.y))),
				Max(cp1.x, Max(cp2.x, Max(cp3.x, cp4.x))),
				Max(cp1.y, Max(cp2.y, Max(cp3.y, cp4.y))),
				&collisions, 2, nil, false, true, true, false, false);
			if (collisions > 0)
				obstacleInPath = true;
		}
		if (obstacleInPath) {
			UpdateCompareFlag(true);
			return 0;
		}
		pObject->Teleport(newPosition);
		UpdateCompareFlag(newPosition == posTarget); // using direct comparasion here is fine
		return 0;
	}
	case COMMAND_REMOVE_CHAR_ELEGANTLY:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed && pPed->CharCreatedBy == MISSION_CHAR){
			CWorld::RemoveReferencesToDeletedObject(pPed);
			if (pPed->bInVehicle && pPed->m_pMyVehicle)
				CTheScripts::RemoveThisPed(pPed);
			else{
				pPed->CharCreatedBy = RANDOM_CHAR;
				pPed->bRespondsToThreats = true;
				pPed->bScriptObjectiveCompleted = false;
				pPed->ClearLeader();
				--CPopulation::ms_nTotalMissionPeds;
				pPed->bFadeOut = true;
				CWorld::RemoveReferencesToDeletedObject(pPed);
			}
		}
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.RemoveEntityFromList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_SET_CHAR_STAY_IN_SAME_PLACE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bKindaStayInSamePlace = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_UNDRESS_CHAR:
	{
		script_assert(false && "todo string arg");
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		char name[KEY_LENGTH_IN_SCRIPT];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, name);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			name[i] = tolower(name[i]);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		pPed->Undress(name);
		return 0;
	}
	case COMMAND_IS_EXPLOSION_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		float infX = GET_FLOAT_PARAM(1);
		float infY = GET_FLOAT_PARAM(2);
		float infZ = GET_FLOAT_PARAM(3);
		float supX = GET_FLOAT_PARAM(4);
		float supY = GET_FLOAT_PARAM(5);
		float supZ = GET_FLOAT_PARAM(6);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(4);
			supX = GET_FLOAT_PARAM(1);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(5);
			supY = GET_FLOAT_PARAM(2);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(6);
			supZ = GET_FLOAT_PARAM(3);
		}
		UpdateCompareFlag(CExplosion::TestForExplosionInArea((eExplosionType)GET_INTEGER_PARAM(0),
			infX, supX, infY, supY, infZ, supZ));
		return 0;
	}
	case COMMAND_PLACE_OBJECT_RELATIVE_TO_CAR:
	{
		CollectParameters(&m_nIp, 5);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		CVector offset = GET_VECTOR_PARAM(2);
		CPhysical::PlacePhysicalRelativeToOtherPhysical(pVehicle, pObject, offset);
		return 0;
	}
	case COMMAND_MAKE_OBJECT_TARGETTABLE:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CPlayerPed* pPlayerPed = CWorld::Players[CWorld::PlayerInFocus].m_pPed;
		script_assert(pPlayerPed);
		pPlayerPed->MakeObjectTargettable(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_ADD_ARMOUR_TO_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_fArmour = Clamp(pPed->m_fArmour + GET_INTEGER_PARAM(1), 0.0f, 100.0f);
		return 0;
	}
	case COMMAND_OPEN_GARAGE:
	{
		CollectParameters(&m_nIp, 1);
		CGarages::OpenGarage(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_CLOSE_GARAGE:
	{
		CollectParameters(&m_nIp, 1);
		CGarages::CloseGarage(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_WARP_CHAR_FROM_CAR_TO_COORD:
	{
		CollectParameters(&m_nIp, 4);
		CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		if (pPed->bInVehicle){
			if (pPed->m_pMyVehicle->bIsBus)
				pPed->bRenderPedInCar = true;
			if (pPed->m_pMyVehicle->pDriver == pPed){
				pPed->m_pMyVehicle->RemoveDriver();
				pPed->m_pMyVehicle->SetStatus(STATUS_ABANDONED);
				pPed->m_pMyVehicle->bEngineOn = false;
				pPed->m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
				pPed->m_pMyVehicle->SetMoveSpeed(0.0f, 0.0f, -0.00001f);
				pPed->m_pMyVehicle->SetTurnSpeed(0.0f, 0.0f, 0.0f);
			}else{
				pPed->m_pMyVehicle->RemovePassenger(pPed);
			}
			if (pPed->m_vehDoor) {
				eDoors door;
				switch (pPed->m_vehDoor) {
				case CAR_DOOR_LF:
					door = DOOR_FRONT_LEFT;
					break;
				case CAR_DOOR_RF:
					door = DOOR_FRONT_RIGHT;
					break;
				case CAR_DOOR_LR:
					door = DOOR_REAR_LEFT;
					break;
				case CAR_DOOR_RR:
					door = DOOR_REAR_RIGHT;
					break;
				}
				if (pPed->GetPedState() == PED_EXIT_CAR || pPed->GetPedState() == PED_DRAG_FROM_CAR || !pPed->m_pMyVehicle->IsDoorClosed(door)) {
					uint8 flags = 0;
					if (pPed->m_pMyVehicle->IsBike()) {
						if (pPed->m_vehDoor == CAR_DOOR_LF ||
							pPed->m_vehDoor == CAR_DOOR_RF ||
							pPed->m_vehDoor == CAR_WINDSCREEN)
							flags = CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_RF;
						else if (pPed->m_vehDoor == CAR_DOOR_LR ||
							pPed->m_vehDoor == CAR_DOOR_RR)
							flags = CAR_DOOR_FLAG_LR | CAR_DOOR_FLAG_RR;
					}
					else {
						switch (pPed->m_vehDoor) {
						case CAR_DOOR_LF:
							flags = pPed->m_pMyVehicle->m_nNumMaxPassengers != 0 ? CAR_DOOR_FLAG_LF : CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_LR;
							break;
						case CAR_DOOR_LR:
							flags = pPed->m_pMyVehicle->m_nNumMaxPassengers != 0 ? CAR_DOOR_FLAG_LR : CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_LR;
							break;
						case CAR_DOOR_RF:
							flags = CAR_DOOR_FLAG_RF;
							break;
						case CAR_DOOR_RR:
							flags = CAR_DOOR_FLAG_RR;
							break;
						}
					}
					pPed->m_pMyVehicle->m_nGettingOutFlags &= ~flags;
					pPed->m_pMyVehicle->ProcessOpenDoor(pPed->m_vehDoor, ANIM_STD_NUM, 0.0f);
				}
			}
		}
		pPed->RemoveInCarAnims();
		pPed->bInVehicle = false;
		pPed->m_pMyVehicle = nil;
		pPed->SetPedState(PED_IDLE);
		pPed->m_nLastPedState = PED_NONE;
		pPed->bUsesCollision = true;
		pPed->SetMoveSpeed(0.0f, 0.0f, 0.0f);
		pPed->ReplaceWeaponWhenExitingVehicle();
		if (pPed->m_pVehicleAnim)
			pPed->m_pVehicleAnim->blendDelta = -1000.0f;
		pPed->m_pVehicleAnim = nil;
		pPed->RestartNonPartialAnims();
		pPed->SetMoveState(PEDMOVE_NONE);
		CAnimManager::BlendAnimation(pPed->GetClump(), pPed->m_animGroup, ANIM_STD_IDLE, 1000.0f);
		pos.z += pPed->GetDistanceFromCentreOfMassToBaseOfModel();
		pPed->Teleport(pos);
		CTheScripts::ClearSpaceForMissionEntity(pos, pPed);
		return 0;
	}
	case COMMAND_SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE:
	{
		CollectParameters(&m_nIp, 6);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float range = GET_FLOAT_PARAM(3);
		int mi = GET_INTEGER_PARAM(4) < 0 ? CTheScripts::UsedObjectArray[-GET_INTEGER_PARAM(4)].index : GET_INTEGER_PARAM(4);
		int16 total;
		CEntity* apEntities[16];
		CWorld::FindObjectsOfTypeInRange(mi, pos, range, true, &total, 16, apEntities, true, false, false, true, true);
		if (total == 0)
			CWorld::FindObjectsOfTypeInRangeSectorList(mi, CWorld::GetBigBuildingList(LEVEL_GENERIC), pos, range, true, &total, 16, apEntities);
		if (total == 0)
			CWorld::FindObjectsOfTypeInRangeSectorList(mi, CWorld::GetBigBuildingList(CTheZones::GetLevelFromPosition(&pos)), pos, range, true, &total, 16, apEntities);
		CEntity* pClosestEntity = nil;
		float min_dist = 2.0f * range;
		for (int i = 0; i < total; i++) {
			float dist = (apEntities[i]->GetPosition() - pos).Magnitude();
			if (dist < min_dist) {
				min_dist = dist;
				pClosestEntity = apEntities[i];
			}
		}
		if (pClosestEntity) {
			pClosestEntity->bIsVisible = (GET_INTEGER_PARAM(5) != 0);
			CTheScripts::AddToInvisibilitySwapArray(pClosestEntity, GET_INTEGER_PARAM(5) != 0);
		}
		return 0;
	}
	case COMMAND_HAS_CHAR_SPOTTED_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTarget);
		UpdateCompareFlag(pPed->OurPedCanSeeThisOne(pTarget));
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_HAIL_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_HAIL_TAXI);
		return 0;
	}
	case COMMAND_HAS_OBJECT_BEEN_DAMAGED:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		UpdateCompareFlag(pObject->bRenderDamaged || !pObject->bIsVisible);
		return 0;
	}
	case COMMAND_START_KILL_FRENZY_HEADSHOT:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CDarkel::StartFrenzy((eWeaponType)GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2),
			GET_INTEGER_PARAM(3), text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5),
			GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7) != 0, true);
		return 0;
	}
	case COMMAND_WARP_CHAR_INTO_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		pPed->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, pVehicle);
		pPed->WarpPedIntoCar(pVehicle);
		pPed->RestorePreviousObjective();
		return 0;
	}
	case COMMAND_SWITCH_CAR_RADIO:
		CollectParameters(&m_nIp, 1);
		DMAudio.ChangeMusicMode(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_PRINT_WITH_2_NUMBERS_BIG:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddBigMessageWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3) - 1, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_3_NUMBERS_BIG:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddBigMessageWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4) - 1, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	case COMMAND_SET_CHAR_WAIT_STATE:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->SetWaitState((eWaitState)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) >= 0 ? &GET_INTEGER_PARAM(2) : nil);
		return 0;
	}
	case COMMAND_SET_CAMERA_BEHIND_PLAYER:
		TheCamera.SetCameraDirectlyBehindForFollowPed_CamOnAString();
		return 0;
	case COMMAND_CREATE_RANDOM_CHAR:
	{
		CollectParameters(&m_nIp, 3);
		CZoneInfo zoneinfo;
		CTheZones::GetZoneInfoForTimeOfDay(&CWorld::Players[CWorld::PlayerInFocus].GetPos(), &zoneinfo);
		int mi;
		ePedType pedtype = PEDTYPE_COP;
		int attempt = 0;
		while (pedtype != PEDTYPE_CIVMALE && pedtype != PEDTYPE_CIVFEMALE && attempt < 5) {
			mi = CPopulation::ChooseCivilianOccupation(zoneinfo.pedGroup);
			if (CModelInfo::GetModelInfo(mi)->GetRwObject())
				pedtype = ((CPedModelInfo*)(CModelInfo::GetModelInfo(mi)))->m_pedType;
			attempt++;
		}
		if (!CModelInfo::GetModelInfo(mi)->GetRwObject()) {
			mi = MI_MALE01;
			pedtype = ((CPedModelInfo*)(CModelInfo::GetModelInfo(mi)))->m_pedType;
		}
		CPed* ped = new CCivilianPed(pedtype, mi);
		ped->CharCreatedBy = MISSION_CHAR;
		ped->bRespondsToThreats = false;
		ped->bAllowMedicsToReviveMe = false;
		ped->bIsPlayerFriend = false;
		CVector pos = GET_VECTOR_PARAM(0);
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
		CPopulation::ms_nTotalMissionPeds++;
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(ped));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CHAR);
		return 0;
	}
	case COMMAND_IS_SNIPER_BULLET_IN_AREA:
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
		UpdateCompareFlag(CBulletInfo::TestForSniperBullet(infX, supX, infY, supY, infZ, supZ));
		return 0;
	}
	case COMMAND_SET_OBJECT_VELOCITY:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->SetMoveSpeed(GET_VECTOR_PARAM(1) * METERS_PER_SECOND_TO_GAME_SPEED);
		return 0;
	}
	case COMMAND_SET_OBJECT_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bUsesCollision = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_PRINT_STRING_IN_STRING_NOW:
	{
		wchar* source = GetTextByKeyFromScript(&m_nIp);
		wchar* pstr = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddMessageJumpQWithString(source, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), pstr);
		return 0;
	}
	case COMMAND_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0) - GET_FLOAT_PARAM(3);
		float supX = GET_FLOAT_PARAM(0) + GET_FLOAT_PARAM(3);
		float infY = GET_FLOAT_PARAM(1) - GET_FLOAT_PARAM(4);
		float supY = GET_FLOAT_PARAM(1) + GET_FLOAT_PARAM(4);
		float infZ = GET_FLOAT_PARAM(2) - GET_FLOAT_PARAM(5);
		float supZ = GET_FLOAT_PARAM(2) + GET_FLOAT_PARAM(5);
		if (infX > supX) {
			float tmp = infX;
			infX = supX;
			supX = tmp;
		}
		if (infY > supY) {
			float tmp = infY;
			infY = supY;
			supY = tmp;
		}
		if (infZ > supZ) {
			float tmp = infZ;
			infZ = supZ;
			supZ = tmp;
		}
		int16 total;
		CWorld::FindMissionEntitiesIntersectingCube(CVector(infX, infY, infZ), CVector(supX, supY, supZ), &total, 2, nil, true, true, true);
		UpdateCompareFlag(total > 0);
		return 0;
	}
	case COMMAND_LOAD_ALL_MODELS_NOW:
#ifdef FIX_BUGS
		CTimer::Suspend();
#else
		CTimer::Stop();
#endif
		CStreaming::LoadAllRequestedModels(false);
#ifdef FIX_BUGS
		CTimer::Resume();
#else
		CTimer::Update();
#endif
		return 0;
	case COMMAND_ADD_TO_OBJECT_VELOCITY:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->AddToMoveSpeed(GET_VECTOR_PARAM(1) * METERS_PER_SECOND_TO_GAME_SPEED);
		return 0;
	}
	case COMMAND_SET_OBJECT_DYNAMIC:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		if (GET_INTEGER_PARAM(1)) {
			if (pObject->bIsStatic) {
				pObject->SetIsStatic(false);
				pObject->AddToMovingList();
			}
		}
		else {
			if (!pObject->bIsStatic) {
				pObject->SetIsStatic(true);
				pObject->RemoveFromMovingList();
			}
		}
		return 0;
	}
	case COMMAND_PLAY_MISSION_PASSED_TUNE:
	{
		CollectParameters(&m_nIp, 1);
		DMAudio.ChangeMusicMode(MUSICMODE_FRONTEND);
		DMAudio.PlayFrontEndTrack(GET_INTEGER_PARAM(0) + STREAMED_SOUND_MISSION_COMPLETED - 1, FALSE);
#ifndef GTA_PSP
		//DMAudio.SaveAnnouncementsWhenMissionPassedPlayed(); // TODO!
#endif
		return 0;
	}
	case COMMAND_CLEAR_AREA:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CWorld::ClearExcitingStuffFromArea(pos, GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4));
#ifdef GTA_MOBILE
		// CPopulation::ms_blockPedCreationForAFrame = true;
#endif
		return 0;
	}
	case COMMAND_FREEZE_ONSCREEN_TIMER:
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.m_bDisabled = GET_INTEGER_PARAM(0) != 0;
		return 0;
	case COMMAND_SWITCH_CAR_SIREN:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_bSirenOrAlarm = GET_INTEGER_PARAM(1) != 0;
		return 0;
	}
	case COMMAND_SWITCH_PED_ROADS_OFF_ANGLED:
		CollectParameters(&m_nIp, 7);
		ThePaths.SwitchRoadsInAngledArea(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2),
			GET_FLOAT_PARAM(3), GET_FLOAT_PARAM(4), GET_FLOAT_PARAM(5), GET_FLOAT_PARAM(6), 0, 0);
		return 0;
	case COMMAND_SET_CAR_WATERTIGHT:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (pVehicle->IsBike()) {
			CBike* pBike = (CBike*)pVehicle;
			pBike->bWaterTight = GET_INTEGER_PARAM(1) != 0;
		}
		else if (pVehicle->IsCar()) {
			CAutomobile* pCar = (CAutomobile*)pVehicle;
			pCar->bWaterTight = GET_INTEGER_PARAM(1) != 0;
		}
		return 0;
	}
	case COMMAND_ADD_MOVING_PARTICLE_EFFECT:
	{
		CollectParameters(&m_nIp, 12);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float size = Max(0.0f, GET_FLOAT_PARAM(7));
		eParticleObjectType type = (eParticleObjectType)GET_INTEGER_PARAM(0);
		RwRGBA color;
		if (type == POBJECT_SMOKE_TRAIL){
			color.alpha = -1;
			color.red = GET_INTEGER_PARAM(8);
			color.green = GET_INTEGER_PARAM(9);
			color.blue = GET_INTEGER_PARAM(10);
		}else{
			color.alpha = color.red = color.blue = color.green = 0;
		}
		CVector target = GET_VECTOR_PARAM(4);
		CParticleObject::AddObject(type, pos, target, size, GET_INTEGER_PARAM(11), color, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_CANT_BE_DRAGGED_OUT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bDontDragMeOutCar = GET_INTEGER_PARAM(1) != 0;
		return 0;
	}
	case COMMAND_TURN_CAR_TO_FACE_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		const CVector& pos = pVehicle->GetPosition();
		float heading = CGeneral::GetATanOfXY(pos.x - GET_FLOAT_PARAM(1), pos.y - GET_FLOAT_PARAM(2)) + HALFPI;
		if (heading > TWOPI)
			heading -= TWOPI;
		pVehicle->SetHeading(heading);
		return 0;
	}
	case COMMAND_IS_CRANE_LIFTING_CAR:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(2));
		UpdateCompareFlag(CCranes::IsThisCarPickedUp(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), pVehicle));
		return 0;
	}
	case COMMAND_DRAW_SPHERE:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		C3dMarkers::PlaceMarkerSet((uintptr)this + m_nIp, MARKERTYPE_CYLINDER, pos, GET_FLOAT_PARAM(3),
			SPHERE_MARKER_R, SPHERE_MARKER_G, SPHERE_MARKER_B, SPHERE_MARKER_A,
			SPHERE_MARKER_PULSE_PERIOD, SPHERE_MARKER_PULSE_FRACTION, 0);
		return 0;
	}
	case COMMAND_SET_CAR_STATUS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->SetStatus(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_CHAR_MALE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->m_nPedType != PEDTYPE_CIVFEMALE && pPed->m_nPedType != PEDTYPE_PROSTITUTE);
		return 0;
	}
	case COMMAND_SCRIPT_NAME: // vcs done/tested
	{
		//CollectParameters(&m_nIp, 1); // 0x0A type string include here, GET_INTEGER_PARAM(0) store ip string in collect
		//const char *str = GET_INTEGER_PARAM(0) ? (const char *)&CTheScripts::ScriptSpace[GET_INTEGER_PARAM(0)] : nil;

		const char *str = GetKeyFromScript(&m_nIp);
		strncpy(strbuff, str, KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			strbuff[i] = tolower(strbuff[i]);
		//m_nIp += KEY_LENGTH_IN_SCRIPT; // lcs
		strncpy(m_abScriptName, strbuff, KEY_LENGTH_IN_SCRIPT);
		return 0;
	}
	case COMMAND_SAVE_INT_TO_DEBUG_FILE:
		// TODO: implement something here
		CollectParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SAVE_FLOAT_TO_DEBUG_FILE:
		CollectParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SAVE_NEWLINE_TO_DEBUG_FILE:
		return 0;
	case COMMAND_POLICE_RADIO_MESSAGE:
		CollectParameters(&m_nIp, 3);
		DMAudio.PlaySuspectLastSeen(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2));
		return 0;
	case COMMAND_SET_CAR_STRONG:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bTakeLessDamage = GET_INTEGER_PARAM(1) != 0;
		return 0;
	}
	case COMMAND_REMOVE_ROUTE:
	{
		CollectParameters(&m_nIp, 1);
		CRouteNode::RemoveRoute(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_SWITCH_RUBBISH:
	{
		CollectParameters(&m_nIp, 1);
		CRubbish::SetVisibility(GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_REMOVE_PARTICLE_EFFECTS_IN_AREA:
	{
		CollectParameters(&m_nIp, 6);
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float z1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		float z2 = GET_FLOAT_PARAM(5);
		CParticleObject* tmp = CParticleObject::pCloseListHead;
		while (tmp) {
			CParticleObject* next = tmp->m_pNext;
			if (tmp->IsWithinArea(x1, y1, z1, x2, y2, z2))
				tmp->RemoveObject();
			tmp = next;
		}
		tmp = CParticleObject::pFarListHead;
		while (tmp) {
			CParticleObject* next = tmp->m_pNext;
			if (tmp->IsWithinArea(x1, y1, z1, x2, y2, z2))
				tmp->RemoveObject();
			tmp = next;
		}
		return 0;
	}
	case COMMAND_SWITCH_STREAMING:
		CollectParameters(&m_nIp, 1);
		CStreaming::ms_disableStreaming = GET_INTEGER_PARAM(0) == 0;
		return 0;
	case COMMAND_IS_GARAGE_OPEN:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::IsGarageOpen(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_IS_GARAGE_CLOSED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::IsGarageClosed(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_SWAP_NEAREST_BUILDING_MODEL:
	{
		CollectParameters(&m_nIp, 6);
		CTheScripts::SwapNearestBuildingModel(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5));
		return 0;
	}
	case COMMAND_SWITCH_WORLD_PROCESSING:
		CollectParameters(&m_nIp, 1);
		CWorld::bProcessCutsceneOnly = GET_INTEGER_PARAM(0) == 0;
		return 0;
	case COMMAND_CLEAR_AREA_OF_CARS:
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
		CWorld::ClearCarsFromArea(infX, infY, infZ, supX, supY, supZ);
		return 0;
	}
	case COMMAND_SET_ROTATING_GARAGE_DOOR:
		CollectParameters(&m_nIp, 1);
		CGarages::SetGarageDoorToRotate(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_ADD_SPHERE:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = GET_FLOAT_PARAM(3);
		CTheScripts::GetActualScriptSphereIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CTheScripts::AddScriptSphere((uintptr)this + m_nIp, pos, radius));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_REMOVE_SPHERE:
		CollectParameters(&m_nIp, 1);
		CTheScripts::RemoveScriptSphere(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_SET_EVERYONE_IGNORE_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->m_pWanted->m_bIgnoredByEveryone = true;
			CWorld::StopAllLawEnforcersInTheirTracks();
		}
		else {
			pPed->m_pWanted->m_bIgnoredByEveryone = false;
		}
		return 0;
	}
	case COMMAND_STORE_CAR_CHAR_IS_IN_NO_SAVE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = pPed->bInVehicle ? pPed->m_pMyVehicle : nil;
		SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex(pVehicle));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_STRING:
	{
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ???
		strncpy(onscreen_str, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddClock(var, onscreen_str, GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_COUNTER_WITH_STRING:
	{
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ???
		strncpy(onscreen_str, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(0), onscreen_str, 0, -1, nil, 0);
		return 0;
	}
	case COMMAND_CREATE_RANDOM_CAR_FOR_CAR_PARK:
	{
		CollectParameters(&m_nIp, 4);
		if (CCarCtrl::NumRandomCars >= 30)
			return 0;
		int attempts;
		int model = -1;
		int index = CGeneral::GetRandomNumberInRange(0, MAXVEHICLESLOADED);
		for (attempts = 0; attempts < MAXVEHICLESLOADED; attempts++) {
			if (model != -1)
				break;
			model = CStreaming::ms_vehiclesLoaded[index];
			if (model == -1)
				continue;
			if (CModelInfo::IsCarModel(model) || CModelInfo::IsBikeModel(model)) {
				switch (model) {
				case MI_LANDSTAL:
				case MI_LINERUN:
				case MI_RIO:
				case MI_FIRETRUCK:
				case MI_TRASH:
				case MI_STRETCH:
				case MI_VOODOO:
				case MI_MULE:
				case MI_AMBULAN:
				case MI_FBICAR:
				case MI_MRWHOOP:
				case MI_BFINJECT:
				case MI_HEARSE:
				case MI_HUNTER:
				case MI_POLICE:
				case MI_ENFORCER:
				case MI_SECURICA:
				case MI_PREDATOR:
				case MI_BUS:
				case MI_RHINO:
				case MI_BARRACKS:
				case MI_CUBAN:
				case MI_CHOPPER:
				case MI_ANGEL:
				case MI_COACH:
				case MI_RCBANDIT:
				case MI_PACKER:
				case MI_SENTXS:
				case MI_SQUALO:
				case MI_SEASPAR:
				case MI_PIZZABOY:
				case MI_NOODLEBOY:
				case MI_ANGEL2:
				case MI_SANCHEZ2:
				case MI_GANGBUR:
				case MI_AIRTRAIN:
				case MI_DEADDODO:
				case MI_SPEEDER:
				case MI_REEFER:
				case MI_TROPIC:
				case MI_FLATBED:
				case MI_YANKEE:
				case MI_CADDY:
				case MI_BORGNINE:
				case MI_TOPFUN:
				case MI_CAMPVAN:
				case MI_BALLOT:
				case MI_SKIMMER:
				case MI_RCBARON:
				case MI_RCRAIDER:
				case MI_SPARROW:
				case MI_PATRIOT:
				case MI_LOVEFIST:
				case MI_COASTG:
				case MI_DINGHY:
				case MI_HERMES:
				case MI_SABRETUR:
				case MI_PHEONIX:
				case MI_WALTON:
				case MI_COMET:
				case MI_DELUXO:
				case MI_BURRITO:
				case MI_SPAND:
				case MI_MARQUIS:
				case MI_BAGGAGE:
				case MI_KAUFMAN:
				case MI_MAVERICK:
				case MI_VCNMAV:
				case MI_RANCHER:
				case MI_FBIRANCH:
				case MI_JETMAX:
				case MI_HOTRING:
				case MI_SANDKING:
				case MI_BLISTAC:
				case MI_POLMAV:
				case MI_BOXVILLE:
				case MI_BENSON:
				case MI_MESA:
				case MI_RCGOBLIN:
				case MI_HOTRINA:
				case MI_HOTRINB:
				case MI_BLOODRA:
				case MI_BLOODRB:
				case MI_VICECHEE:
				case MI_CABBIE:
				case MI_MAFIA:
					model = -1;
					break;
				case MI_IDAHO:
				case MI_STINGER:
				case MI_PEREN:
				case MI_SENTINEL:
				case MI_MANANA:
				case MI_INFERNUS:
				case MI_PONY:
				case MI_CHEETAH:
				case MI_MOONBEAM:
				case MI_ESPERANT:
				case MI_TAXI:
				case MI_WASHING:
				case MI_BOBCAT:
				case MI_BANSHEE:
				case MI_STALLION:
				case MI_RUMPO:
				case MI_ADMIRAL:
				case MI_PCJ600:
				case MI_FAGGIO:
				case MI_FREEWAY:
				case MI_GLENDALE:
				case MI_OCEANIC:
				case MI_SANCHEZ:
				case MI_SABRE:
				case MI_REGINA:
				case MI_VIRGO:
				case MI_GREENWOO:
					break;
				default:
					printf("CREATE_RANDOM_CAR_FOR_CAR_PARK - Unknown car model %d\n", CStreaming::ms_vehiclesLoaded[index]);
					model = -1;
					break;
				}
			}
			else
				model = -1;
			if (++index >= 50)
				index = 0;
		}
		if (model == -1)
			return 0;
		CVehicle* car;
		if (CModelInfo::IsBikeModel(model)) {
			car = new CBike(model, RANDOM_VEHICLE);
			((CBike*)(car))->bIsStanding = true;
		}
		else
			car = new CAutomobile(model, RANDOM_VEHICLE);
		CVector pos = GET_VECTOR_PARAM(0);
		pos.z += car->GetDistanceFromCentreOfMassToBaseOfModel();
		car->SetPosition(pos);
		car->SetHeading(DEGTORAD(GET_FLOAT_PARAM(3)));
		CTheScripts::ClearSpaceForMissionEntity(pos, car);
		car->SetStatus(STATUS_ABANDONED);
		car->bIsLocked = false;
		car->bIsCarParkVehicle = true;
		CCarCtrl::JoinCarWithRoadSystem(car);
		car->AutoPilot.m_nCarMission = MISSION_NONE;
		car->AutoPilot.m_nTempAction = TEMPACT_NONE;
		car->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_STOP_FOR_CARS;
		car->AutoPilot.m_nCruiseSpeed = car->AutoPilot.m_fMaxTrafficSpeed = 9.0f;
		car->AutoPilot.m_nCurrentLane = car->AutoPilot.m_nNextLane = 0;
		car->bEngineOn = false;
		car->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pos);
		CWorld::Add(car);
		return 0;
	}
	case COMMAND_SET_WANTED_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		FindPlayerPed()->m_pWanted->m_fCrimeSensitivity = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_SET_CAMERA_IN_FRONT_OF_PLAYER:
		TheCamera.SetCameraDirectlyInFrontForFollowPed_CamOnAString();
		return 0;
	case COMMAND_IS_CAR_VISIBLY_DAMAGED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->bIsDamaged);
		return 0;
	}
	case COMMAND_DOES_OBJECT_EXIST:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_LOAD_SCENE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
#ifdef FIX_BUGS
		CTimer::Suspend();
#else
		CTimer::Stop();
#endif
		CStreaming::LoadSceneCollision(pos);
#ifdef FIX_BUGS
		CTimer::Suspend();
#else
		CTimer::Update();
#endif
		return 0;
	}
	case COMMAND_ADD_STUCK_CAR_CHECK:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CTheScripts::StuckCars.AddCarToCheck(GET_INTEGER_PARAM(0), GET_FLOAT_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_REMOVE_STUCK_CAR_CHECK:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::StuckCars.RemoveCarFromCheck(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_IS_CAR_STUCK:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CTheScripts::StuckCars.HasCarBeenStuckForAWhile(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_LOAD_MISSION_AUDIO:
	{
		script_assert(false && "todo string arg");
		CollectParameters(&m_nIp, 1);
		strncpy(strbuff, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			strbuff[i] = tolower(strbuff[i]);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		DMAudio.PreloadMissionAudio(GET_INTEGER_PARAM(0) - 1, strbuff);
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands600To699(int32 command)
{
	char tmp[48];
	switch (command){
	case COMMAND_HAS_MISSION_AUDIO_LOADED:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(DMAudio.GetMissionAudioLoadingStatus(GET_INTEGER_PARAM(0) - 1) == 1);
		return 0;
	}
	case todo__comm_601:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_601");
		return 0;
	}
	case COMMAND_HAS_MISSION_AUDIO_FINISHED:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(DMAudio.IsMissionAudioSampleFinished(GET_INTEGER_PARAM(0) - 1));
		return 0;
	}
	case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		int node = ThePaths.FindNodeClosestToCoors(pos, 0, 999999.9f, true, true);
		SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(node));
		SET_FLOAT_PARAM(3, ThePaths.FindNodeOrientationForCarPlacement(node));
		StoreParameters(&m_nIp, 4);
		return 0;
	}
	case COMMAND_HAS_IMPORT_GARAGE_SLOT_BEEN_FILLED:
	{
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(CGarages::HasImportExportGarageCollectedThisCar(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1) - 1));
		return 0;
	}
	case COMMAND_CLEAR_THIS_PRINT:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CMessages::ClearThisPrint(text);
		return 0;
	}
	case COMMAND_CLEAR_THIS_BIG_PRINT:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CMessages::ClearThisBigPrint(text);
		return 0;
	}
	case COMMAND_SET_MISSION_AUDIO_POSITION:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(1);
		DMAudio.SetMissionAudioLocation(GET_INTEGER_PARAM(0) - 1, pos.x, pos.y, pos.z);
		return 0;
	}
	case COMMAND_ACTIVATE_SAVE_MENU:
	{
		CStats::SafeHouseVisits++;
		FrontEndMenuManager.m_bActivateSaveMenu = true;
		FindPlayerPed()->SetMoveSpeed(0.0f, 0.0f, 0.0f);
		FindPlayerPed()->SetTurnSpeed(0.0f, 0.0f, 0.0f);
		return 0;
	}
	case COMMAND_HAS_SAVE_GAME_FINISHED:
		UpdateCompareFlag(!FrontEndMenuManager.m_bMenuActive && !FrontEndMenuManager.m_bActivateSaveMenu);
		return 0;
	case COMMAND_NO_SPECIAL_CAMERA_FOR_THIS_GARAGE:
		CollectParameters(&m_nIp, 1);
		CGarages::SetLeaveCameraForThisGarage(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_ADD_BLIP_FOR_PICKUP:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPickups::aPickUps[CPickups::GetActualPickupIndex(GET_INTEGER_PARAM(0))].m_pObject;
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int handle = CRadar::SetEntityBlip(BLIP_OBJECT, CPools::GetObjectPool()->GetIndex(pObject), 6, BLIP_DISPLAY_BOTH);
		CRadar::ChangeBlipScale(handle, 3);
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_PED_DENSITY_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		CPopulation::PedDensityMultiplier = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_FORCE_RANDOM_PED_TYPE:
		CollectParameters(&m_nIp, 1);
		CPopulation::m_AllRandomPedsThisType = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_TEXT_RIGHT_JUSTIFY:
		CollectParameters(&m_nIp, 1);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_bRightJustify = GET_INTEGER_PARAM(0) != 0;
		return 0;
	case COMMAND_PRINT_HELP:
	{
		/* maybe will be useful? TODO
		if (CCamera::m_bUseMouse3rdPerson && (
			strcmp((char*)&CTheScripts::ScriptSpace[m_nIp], "HELP15") == 0 ||
			strcmp((char*)&CTheScripts::ScriptSpace[m_nIp], "GUN_2A") == 0 ||
			strcmp((char*)&CTheScripts::ScriptSpace[m_nIp], "GUN_2C") == 0 ||
			strcmp((char*)&CTheScripts::ScriptSpace[m_nIp], "GUN_2D") == 0)) {
			m_nIp += KEY_LENGTH_IN_SCRIPT;
			return 0;
		}
		*/
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false);
		return 0;
	}
	case COMMAND_CLEAR_HELP:
		//CHud::gLastPrintForeverString = false; TODO
		CHud::SetHelpMessage(nil, false);
		return 0;
	case COMMAND_FLASH_HUD_OBJECT:
		CollectParameters(&m_nIp, 1);
		CHud::m_ItemToFlash = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_IS_CHAR_IN_CONTROL:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed->IsPedInControl());
		return 0;
	}
	case COMMAND_SET_GENERATE_CARS_AROUND_CAMERA:
		CollectParameters(&m_nIp, 1);
		CCarCtrl::bCarsGeneratedAroundCamera = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_CLEAR_SMALL_PRINTS:
		CMessages::ClearSmallMessagesOnly();
		//CHud::ClearSmallMessages(); // TODO
		return 0;
	case COMMAND_SET_UPSIDEDOWN_CAR_NOT_DAMAGED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		//assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		// they call this for bikes again, we don't really want to destroy the structure...
#ifdef FIX_BUGS
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
#endif
			((CAutomobile*)pVehicle)->bNotDamagedUpsideDown = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_CAN_PLAYER_START_MISSION:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPlayerPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPlayerPed);
		UpdateCompareFlag(pPlayerPed->CanStartMission() || pPlayerPed->m_nPedState == PED_DRIVING);
		return 0;
	}
	case COMMAND_MAKE_PLAYER_SAFE_FOR_CUTSCENE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		CPad::GetPad(GET_INTEGER_PARAM(0))->SetDisablePlayerControls(PLAYERCONTROL_CUTSCENE);
		pPlayerInfo->MakePlayerSafe(true);
		CCutsceneMgr::StartCutsceneProcessing();
		return 0;
	}
	case COMMAND_USE_TEXT_COMMANDS:
		CollectParameters(&m_nIp, 1);
		CTheScripts::UseTextCommands = (GET_INTEGER_PARAM(0) != 0) ? 2 : 1;
		return 0;
	case COMMAND_SET_THREAT_FOR_PED_TYPE:
		CollectParameters(&m_nIp, 2);
		CPedType::AddThreat(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_CLEAR_THREAT_FOR_PED_TYPE:
		CollectParameters(&m_nIp, 2);
		CPedType::RemoveThreat(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_GET_CAR_COLOURS:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_currentColour1);
		SET_INTEGER_PARAM(1, pVehicle->m_currentColour2);
		StoreParameters(&m_nIp, 2);
		return 0;
	}
	case COMMAND_SET_ALL_CARS_CAN_BE_DAMAGED:
		CollectParameters(&m_nIp, 1);
		CWorld::SetAllCarsCanBeDamaged(GET_INTEGER_PARAM(0) != 0);
		if (!GET_INTEGER_PARAM(0))
			CWorld::ExtinguishAllCarFiresInArea(FindPlayerCoors(), 4000.0f);
		return 0;
	case COMMAND_SET_CAR_CAN_BE_DAMAGED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		pVehicle->bCanBeDamaged = GET_INTEGER_PARAM(1) != 0;
		if (!GET_INTEGER_PARAM(1))
			pVehicle->ExtinguishCarFire();
		return 0;
	}
	case COMMAND_SET_CHARS_CHATTING:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed1 = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed2 = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed1 && pPed2);
		pPed1->SetChat(pPed2, GET_INTEGER_PARAM(2));
		pPed2->SetChat(pPed1, GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_SET_DRUNK_INPUT_DELAY:
	{
		CollectParameters(&m_nIp, 2);
		assert(GET_INTEGER_PARAM(1) < CPad::DRUNK_STEERING_BUFFER_SIZE);
		CPad::GetPad(GET_INTEGER_PARAM(0))->SetDrunkInputDelay(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_SET_CHAR_MONEY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_nPedMoney = GET_INTEGER_PARAM(1);
		pPed->bMoneyHasBeenGivenByScript = true;
		return 0;
	}
	case COMMAND_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVector result = Multiply3x3(pObject->GetMatrix(), GET_VECTOR_PARAM(1)) + pObject->GetPosition();
		SET_VECTOR_PARAM(0, result);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_REGISTER_LIFE_SAVED:
		CStats::AnotherLifeSavedWithAmbulance();
		return 0;
	case COMMAND_REGISTER_CRIMINAL_CAUGHT:
		CStats::AnotherCriminalCaught();
		return 0;
	case COMMAND_REGISTER_AMBULANCE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelAmbulanceMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_FIRE_EXTINGUISHED:
		CStats::AnotherFireExtinguished();
		return 0;
	case COMMAND_TURN_PHONE_ON:
		CollectParameters(&m_nIp, 1);
		gPhoneInfo.m_aPhones[GET_INTEGER_PARAM(0)].m_nState = PHONE_STATE_9;
		return 0;
	case COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector result = Multiply3x3(pVehicle->GetMatrix(), GET_VECTOR_PARAM(1)) + pVehicle->GetPosition();
		SET_VECTOR_PARAM(0, result);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_TOTAL_NUMBER_OF_KILL_FRENZIES:
		CollectParameters(&m_nIp, 1);
		CStats::SetTotalNumberKillFrenzies(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_BLOW_UP_RC_BUGGY:
		CWorld::Players[CWorld::PlayerInFocus].BlowUpRCBuggy(true);
		return 0;
	case COMMAND_IS_FRENCH_GAME:
		UpdateCompareFlag(CGame::frenchGame);
		return 0;
	case COMMAND_IS_GERMAN_GAME:
		UpdateCompareFlag(CGame::germanGame);
		return 0;
	case COMMAND_CLEAR_MISSION_AUDIO:
		CollectParameters(&m_nIp, 1);
		DMAudio.ClearMissionAudio(GET_INTEGER_PARAM(0) - 1);
		return 0;
	case COMMAND_SET_CHAR_USE_PEDNODE_SEEK:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1))
			pPed->m_pNextPathNode = nil;
		pPed->bUsePedNodeSeek = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_GET_OUT_OF_JAIL_FREE:
		CollectParameters(&m_nIp, 2);
		CWorld::Players[GET_INTEGER_PARAM(0)].m_bGetOutOfJailFree = !!GET_INTEGER_PARAM(1);
		return 0;
	case COMMAND_SET_FREE_HEALTH_CARE:
		CollectParameters(&m_nIp, 2);
		CWorld::Players[GET_INTEGER_PARAM(0)].m_bGetOutOfHospitalFree = !!GET_INTEGER_PARAM(1);
		return 0;
	case todo__comm_648:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_648");
		return 0;
	}
	case COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL:
	{
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
		uint32 oldIp = m_nIp;
#endif
		CollectParameters(&m_nIp, 1);

		if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
			if (GET_INTEGER_PARAM(0) < UINT16_MAX - 1)
				return 0;
			SET_INTEGER_PARAM(0, UINT16_MAX - GET_INTEGER_PARAM(0));
		}
#ifdef MISSION_REPLAY
		missionRetryScriptIndex = GET_INTEGER_PARAM(0);
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
		if (CTheScripts::MissionSupportsMissionReplay(missionRetryScriptIndex)){
			if (!AlreadySavedGame) {
				m_nIp = oldIp - 2;
				SaveGameForPause(SAVE_TYPE_QUICKSAVE_FOR_SCRIPT);
				AlreadySavedGame = true;
				return 0;
			}
			else {
				AlreadySavedGame = false;
			}
		}
#endif
#endif
		CTimer::Suspend();
		int offset = CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0)] + 8;
		int size = CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0) + 1] - CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0)];
		if (size <= 0)
			size = CTheScripts::LargestMissionScriptSize;
		CFileMgr::Seek(gScriptsFile, offset, 0);
		CFileMgr::Read(gScriptsFile, (const char*)&CTheScripts::ScriptSpace[CTheScripts::MainScriptSize], size);
		CRunningScript* pMissionScript = CTheScripts::StartNewScript(CTheScripts::MainScriptSize);
		CTimer::Resume();
		pMissionScript->m_bIsMissionScript = true;
		pMissionScript->m_bMissionFlag = true;
		CTheScripts::bAlreadyRunningAMissionScript = true;
		memset(&CTheScripts::ScriptSpace[CTheScripts::NumTrueGlobals * 4 + 8], 0, CTheScripts::MostGlobals * 4);
		pMissionScript->Process();
		return 0;
	}
	case COMMAND_SET_OBJECT_DRAW_LAST:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bDrawLast = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case todo__comm_651:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_651");
		return 0;
	}
	case COMMAND_SET_CHAR_SAY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		switch (GET_INTEGER_PARAM(1)) {
		case 15:
			pPed->Say(0x93); // TODO
			break;
		default:
			break;
		}
		return 0;
	}
	case COMMAND_SET_NEAR_CLIP:
		CollectParameters(&m_nIp, 1);
		TheCamera.SetNearClipScript(GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_SET_RADIO_CHANNEL:
		CollectParameters(&m_nIp, 2);
		if (!cCustomSoundTrack::Instance()->IsPlaying())
			DMAudio.SetRadioChannel(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_DOES_GARAGE_CONTAIN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		UpdateCompareFlag(CGarages::IsThisCarWithinGarageArea(GET_INTEGER_PARAM(0), pVehicle));
		return 0;
	}
	case COMMAND_SET_CAR_TRACTION:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float fTraction = GET_FLOAT_PARAM(1);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR || pVehicle->m_vehType == VEHICLE_TYPE_BIKE);
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
			((CAutomobile*)pVehicle)->m_fTraction = fTraction;
		else
			((CBike*)pVehicle)->m_fTraction = fTraction;
		return 0;
	}
	case COMMAND_ARE_MEASUREMENTS_IN_METRES:
#ifdef USE_MEASUREMENTS_IN_METERS
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_CONVERT_METRES_TO_FEET:
	{
		CollectParameters(&m_nIp, 1);
		float fMeterValue = GET_FLOAT_PARAM(0);
		float fFeetValue = fMeterValue / METERS_IN_FOOT;
		SET_FLOAT_PARAM(0, fFeetValue);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_MARK_ROADS_BETWEEN_LEVELS:
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
		ThePaths.MarkRoadsBetweenLevelsInArea(infX, supX, infY, supY, infZ, supZ);
		return 0;
	}
	case COMMAND_SET_CAR_AVOID_LEVEL_TRANSITIONS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_bStayInCurrentLevel = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_CLEAR_AREA_OF_CHARS:
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
		CWorld::ClearPedsFromArea(infX, infY, infZ, supX, supY, supZ);
		return 0;
	}
	case COMMAND_SET_TOTAL_NUMBER_OF_MISSIONS:
		CollectParameters(&m_nIp, 1);
		CStats::SetTotalNumberMissions(CGame::germanGame ? GET_INTEGER_PARAM(0) - 2 : GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CONVERT_METRES_TO_FEET_INT:
		CollectParameters(&m_nIp, 1);
		GET_INTEGER_PARAM(0) *= FEET_IN_METER;
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed);
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(2) < 0)
			pPed->WarpPedIntoCarAsPassenger(pVehicle, GET_INTEGER_PARAM(2));
		else {
			script_assert(GET_INTEGER_PARAM(2) >= 0 && GET_INTEGER_PARAM(2) < ARRAY_SIZE(pVehicle->pPassengers));
			pPed->WarpPedIntoCarAsPassenger(pVehicle, GET_INTEGER_PARAM(2));
		}
		return 0;

	}
	case COMMAND_IS_CAR_PASSENGER_SEAT_FREE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) < pVehicle->m_nNumMaxPassengers && pVehicle->pPassengers[GET_INTEGER_PARAM(1)] == nil);
		return 0;
	}
	case COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(GET_INTEGER_PARAM(1) >= 0 && GET_INTEGER_PARAM(1) < ARRAY_SIZE(pVehicle->pPassengers));
		CPed* pPassenger = pVehicle->pPassengers[GET_INTEGER_PARAM(1)];
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPassenger));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bChrisCriminal = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_START_CREDITS:
		CollectParameters(&m_nIp, 1);
		CCredits::Start(); // TODO: CCredits::Start(GET_INTEGER_PARAM(0))
		return 0;
	case COMMAND_STOP_CREDITS:
		CCredits::Stop();
		return 0;
	case COMMAND_ARE_CREDITS_FINISHED:
		UpdateCompareFlag(CCredits::AreCreditsDone());
		return 0;
	case COMMAND_CREATE_SINGLE_PARTICLE:
		CollectParameters(&m_nIp, 8);
		CParticle::AddParticle((tParticleType)GET_INTEGER_PARAM(0), GET_VECTOR_PARAM(1),
			GET_VECTOR_PARAM(4), nil, GET_FLOAT_PARAM(7), 0, 0, 0, 0);
		return 0;
	case COMMAND_SET_MUSIC_DOES_FADE:
		CollectParameters(&m_nIp, 1);
		TheCamera.m_bIgnoreFadingStuffForMusic = (GET_INTEGER_PARAM(0) == 0);
		return 0;
	case COMMAND_PLAY_END_OF_GAME_TUNE:
		DMAudio.ChangeMusicMode(MUSICMODE_FRONTEND);
		DMAudio.PlayFrontEndTrack(STREAMED_SOUND_CUTSCENE_FINALE, 1); // third parameter is 1
		return 0;
	case COMMAND_STOP_END_OF_GAME_TUNE:
		DMAudio.StopCutSceneMusic();
		DMAudio.ChangeMusicMode(MUSICMODE_GAME);
		return 0;
	case COMMAND_GET_CAR_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->GetModelIndex());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED:
		UpdateCompareFlag(CVehicle::bAllDodosCheat || CVehicle::bCheat3 || CVehicle::bHoverCheat || CVehicle::bCheat8 || CVehicle::bCheat9);
		return 0;
	case COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bNoCriticalHits = (GET_INTEGER_PARAM(1) == 0);
		return 0;
	}
	case COMMAND_IS_CHAR_SITTING_IN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR && pPed->m_pMyVehicle == pVehicle);
		return 0;
	}
	case COMMAND_IS_CHAR_SITTING_IN_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR);
		return 0;
	}
	case COMMAND_IS_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(!pPed->bInVehicle && pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER &&
			pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER);
		return 0;
	}
	case COMMAND_LOAD_SPLASH_SCREEN:
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			tmp[i] = tolower(tmp[i]);
		m_nIp += 8;
		LoadSplash(tmp);
		return 0;
	case todo__comm_682:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_682");
		return 0;
	}
	case COMMAND_ENABLE_PLAYER_CONTROL_CAMERA:
		CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_CAMERA);
		return 0;
	case COMMAND_SET_OBJECT_ROTATION:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CWorld::Remove(pObject);
		pObject->SetOrientation(
			DEGTORAD(GET_FLOAT_PARAM(1)),
			DEGTORAD(GET_FLOAT_PARAM(2)),
			DEGTORAD(GET_FLOAT_PARAM(3)));
		pObject->GetMatrix().UpdateRW();
		pObject->UpdateRwFrame();
		CWorld::Add(pObject);
		return 0;
	}
	case COMMAND_GET_DEBUG_CAMERA_COORDINATES:
		SET_VECTOR_PARAM(0, TheCamera.Cams[2].Source);
		StoreParameters(&m_nIp, 3);
		return 0;
	case todo__comm_686:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_686");
		return 0;
	}
	case todo__comm_687:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_687");
		return 0;
	}
	case COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME:
	{
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			tmp[i] = tolower(tmp[i]);
		m_nIp += 8;
		CRunningScript* pScript = CTheScripts::pActiveScripts;
		while (pScript) {
			CRunningScript* pNext = pScript->next;
			if (strcmp(pScript->m_abScriptName, tmp) == 0) {
				pScript->RemoveScriptFromList(&CTheScripts::pActiveScripts);
				pScript->AddScriptToList(&CTheScripts::pIdleScripts);
			}
			pScript = pNext;
		}
		return 0;
	}
	case COMMAND_DISPLAY_TEXT_WITH_NUMBER:
	{
		CollectParameters(&m_nIp, 2);
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtY = GET_FLOAT_PARAM(1);
		CollectParameters(&m_nIp, 1);
		CMessages::InsertNumberInString(text, GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1,
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame++].m_Text);
		return 0;
	}
	case COMMAND_DISPLAY_TEXT_WITH_2_NUMBERS:
	{
		CollectParameters(&m_nIp, 2);
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtY = GET_FLOAT_PARAM(1);
		CollectParameters(&m_nIp, 2);
		CMessages::InsertNumberInString(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1,
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame++].m_Text);
		return 0;
	}
	case COMMAND_SET_ALL_OCCUPANTS_OF_CAR_LEAVE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CCarAI::TellOccupantsToLeaveCar(pVehicle);
		return 0;
	}
	case COMMAND_SET_INTERPOLATION_PARAMETERS:
		CollectParameters(&m_nIp, 2);
		TheCamera.SetParametersForScriptInterpolation(GET_FLOAT_PARAM(0), 100.0f - GET_FLOAT_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_GET_DEBUG_CAMERA_POINT_AT:
		SET_VECTOR_PARAM(0, TheCamera.Cams[2].Source + TheCamera.Cams[2].Front);
		StoreParameters(&m_nIp, 3);
		return 0;
	case COMMAND_ATTACH_CHAR_TO_CAR:
	{
		CollectParameters(&m_nIp, 8);
		CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle *pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->AttachPedToEntity(pVehicle, GET_VECTOR_PARAM(2), GET_INTEGER_PARAM(5), DEGTORAD(GET_FLOAT_PARAM(6)), (eWeaponType)GET_INTEGER_PARAM(7));
		return 0;
	}
	case COMMAND_DETACH_CHAR_FROM_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed && pPed->m_attachedTo) {
			pPed->DettachPedFromEntity();
			pPed->bIsAimingGun = false;
		}
		return 0;
	}
	case todo__comm_696:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_696");
		return 0;
	}
	case COMMAND_SET_CAR_CHANGE_LANE: // for some reason changed in SA
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_bStayInFastLane = !GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->m_lastWepDam = -1;
		else
			debug("CLEAR_CHAR_LAST_WEAPON_DAMAGE - Character doesn't exist\n");
		return 0;
	}
	case COMMAND_CLEAR_CAR_LAST_WEAPON_DAMAGE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle)
			pVehicle->m_nLastWeaponDamage = -1;
		else
			debug("CLEAR_CAR_LAST_WEAPON_DAMAGE - Vehicle doesn't exist\n");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands700To799(int32 command)
{
	switch (command){
	case COMMAND_GET_RANDOM_COP_IN_AREA:
	{
		CollectParameters(&m_nIp, 9);
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
			if (pPed->m_nPedType != PEDTYPE_COP)
				continue;
			if (!ThisIsAValidRandomCop(pPed->GetModelIndex(), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8)))
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl() && pPed->GetPedState() != PED_DRIVING && pPed->GetPedState() != PED_ABSEIL)
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - COP_PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + COP_PED_FIND_Z_OFFSET < pPed->GetPosition().z)
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
	case COMMAND_GET_DRIVER_OF_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CPed* pDriver = pVehicle->pDriver;
		if (pDriver)
			SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pDriver));
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_NUMBER_OF_FOLLOWERS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pLeader = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pLeader);
		int total = 0;
		int i = CPools::GetPedPool()->GetSize();
		while (--i) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (pPed->m_leader == pLeader)
				total++;
		}
		SET_INTEGER_PARAM(0, total);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER:
	{
		CollectParameters(&m_nIp, 6);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRemote::GivePlayerRemoteControlledCar(pos.x, pos.y, pos.z, DEGTORAD(GET_FLOAT_PARAM(4)), GET_INTEGER_PARAM(5));
		return 0;
	}
	case COMMAND_GET_CURRENT_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->GetWeapon()->m_eWeaponType);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D:
		LocateCharObjectCommand(command, &m_nIp);
		return 0;
	case COMMAND_SET_CAR_TEMP_ACTION:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_nTempAction = (uint8)GET_INTEGER_PARAM(1);
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(2);
		return 0;
	}
	case COMMAND_IS_CHAR_ON_ANY_BIKE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle&& pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BIKE);
		return 0;
	}
	case COMMAND_CAN_CHAR_SEE_DEAD_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		int pedtype = GET_INTEGER_PARAM(1);
		bool can = false;
		for (int i = 0; i < pPed->m_numNearPeds; i++) {
			CPed* pTestPed = pPed->m_nearPeds[i];
			if (pTestPed->m_fHealth <= 0.0f && pTestPed->m_nPedType == pedtype && pPed->OurPedCanSeeThisOne(pTestPed))
				can = true;
		}
		UpdateCompareFlag(can);
		return 0;
	}
	case COMMAND_SET_ENTER_CAR_RANGE_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		CPed::nEnterCarRangeMultiplier = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_SET_THREAT_REACTION_RANGE_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		CPed::nThreatReactionRangeMultiplier = GET_FLOAT_PARAM(0);
		if (CPed::nThreatReactionRangeMultiplier < 1)
			CPed::nThreatReactionRangeMultiplier = 1;
		return 0;
	case COMMAND_SET_CHAR_CEASE_ATTACK_TIMER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_ceaseAttackTimer = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_REMOTE_CONTROLLED_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CWorld::Players[GET_INTEGER_PARAM(0)].m_pRemoteVehicle;
		if (pVehicle)
			SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex(pVehicle));
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_PC_VERSION:
#ifdef GTA_PC
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_IS_MODEL_AVAILABLE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CModelInfo::GetModelInfo(GET_INTEGER_PARAM(0)) != nil);
		return 0;
	case COMMAND_SHUT_CHAR_UP:
		CollectParameters(&m_nIp, 2);
		DMAudio.SetPedTalkingStatus(CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0)), GET_INTEGER_PARAM(1) == 0);
		return 0;
	case COMMAND_SET_ENABLE_RC_DETONATE:
		CollectParameters(&m_nIp, 1);
		CVehicle::bDisableRemoteDetonation = !GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_CAR_RANDOM_ROUTE_SEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_nRouteSeed = GET_INTEGER_PARAM(1);
		return 0;
	}
	case todo__comm_723:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_723");
		return 0;
	}
	case COMMAND_REMOVE_ALL_CHAR_WEAPONS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->ClearWeapons();
		return 0;
	}
	case COMMAND_HAS_CHAR_GOT_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		bool bFound = false;
		for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
			if (pPed->GetWeapon(i).m_eWeaponType == GET_INTEGER_PARAM(1)) {
				bFound = true;
				break;
			}
		}
		UpdateCompareFlag(bFound);
		return 0;
	}
	case COMMAND_SET_TANK_DETONATE_CARS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		((CAutomobile*)pVehicle)->bTankDetonateCars = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_POSITION_OF_ANALOGUE_STICKS:
	{
		CollectParameters(&m_nIp, 1);
		CPad* pPad = CPad::GetPad(GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, pPad->NewState.LeftStickX);
		SET_INTEGER_PARAM(1, pPad->NewState.LeftStickY);
		SET_INTEGER_PARAM(2, pPad->NewState.RightStickX);
		SET_INTEGER_PARAM(3, pPad->NewState.RightStickY);
		StoreParameters(&m_nIp, 4);
		return 0;
	}
	case COMMAND_IS_CAR_ON_FIRE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		bool bOnFire = false;
		if (pVehicle->m_pCarFire)
			bOnFire = true;
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR && ((CAutomobile*)pVehicle)->Damage.GetEngineStatus() >= ENGINE_STATUS_ON_FIRE)
			bOnFire = true;
		if (pVehicle->m_fHealth < 250.0f)
			bOnFire = true;
		UpdateCompareFlag(bOnFire);
		return 0;
	}
	case COMMAND_IS_CAR_TYRE_BURST:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		bool bIsBurst = false;
		CBike* pBike = (CBike*)pVehicle;
		if (pVehicle->IsBike()) {
			if (GET_INTEGER_PARAM(1) == 4) {
				for (int i = 0; i < 2; i++) {
					if (pBike->m_wheelStatus[i] == WHEEL_STATUS_BURST)
						bIsBurst = true;
				}
			}
			else {
				if (GET_INTEGER_PARAM(1) == 2)
					SET_INTEGER_PARAM(1, 0);
				if (GET_INTEGER_PARAM(1) == 3)
					SET_INTEGER_PARAM(1, 1);
				bIsBurst = pBike->m_wheelStatus[GET_INTEGER_PARAM(1)] == WHEEL_STATUS_BURST;
			}
		}
		else {
			CAutomobile* pCar = (CAutomobile*)pVehicle;
			if (GET_INTEGER_PARAM(1) == 4) {
				for (int i = 0; i < 4; i++) {
					if (pCar->Damage.GetWheelStatus(i) == WHEEL_STATUS_BURST)
						bIsBurst = true;
				}
			}
			else
				bIsBurst = pCar->Damage.GetWheelStatus(GET_INTEGER_PARAM(1) == WHEEL_STATUS_BURST);
		}
		UpdateCompareFlag(bIsBurst);
		return 0;
	}
	case COMMAND_HELI_GOTO_COORDS:
	{
		CollectParameters(&m_nIp, 5);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI);
		((CAutomobile*)pVehicle)->TellHeliToGoToCoors(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4));
		return 0;
	}
	case DUPLICATE_COMMAND_731:
	{
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(27); // header duplicate
	}
	case COMMAND_GET_DEAD_CHAR_PICKUP_COORDS:
	{
		CollectParameters(&m_nIp, 1);
		CPed *pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVector pos;
		pTarget->CreateDeadPedPickupCoors(&pos.x, &pos.y, &pos.z);
		SET_VECTOR_PARAM(0, pos);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_CREATE_PROTECTION_PICKUP:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, MI_PICKUP_REVENUE, PICKUP_ASSET_REVENUE, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4))); // TODO: gpModelIndices
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case todo__comm_734:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_734");
		return 0;
	}
	case todo__comm_735:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_735");
		return 0;
	}
	case todo__comm_736:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_736");
		return 0;
	}
	case COMMAND_IS_CHAR_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed && pPed->bIsInWater);
		return 0;
	}
	case DUPLICATE_COMMAND_738:
	{
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(4); // header duplicate
	}
	case DUPLICATE_COMMAND_739:
	case DUPLICATE_COMMAND_740:
	{
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(15); // header duplicate
	}
	case DUPLICATE_COMMAND_741:
	case DUPLICATE_COMMAND_742:
	{
		script_assert(false && "DUPLICATE HACK NEED TEST"); // DUPLICATEH.TXT
		return this->ProcessCommands0To99(21); // header duplicate
	}
	case COMMAND_GET_CHAR_WEAPON_IN_SLOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->GetWeapon(GET_INTEGER_PARAM(1) - 1).m_eWeaponType);
		SET_INTEGER_PARAM(1, pPed->GetWeapon(GET_INTEGER_PARAM(1) - 1).m_nAmmoTotal);
		SET_INTEGER_PARAM(2, CPickups::ModelForWeapon((eWeaponType)GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_GET_CLOSEST_STRAIGHT_ROAD:
	{
		CollectParameters(&m_nIp, 5);
		int node1, node2;
		float angle;
		ThePaths.FindNodePairClosestToCoors(GET_VECTOR_PARAM(0), PATH_CAR, &node1, &node2, &angle,
			GET_FLOAT_PARAM(3), GET_FLOAT_PARAM(4), true, true);
		if (node1 == -1) {
			for (int i = 0; i < 7; i++)
				ScriptParams[i] = 0;
		}
		else {
			SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(node1));
			SET_VECTOR_PARAM(3, ThePaths.FindNodeCoorsForScript(node2));
			SET_FLOAT_PARAM(6, angle);
		}
		StoreParameters(&m_nIp, 7);
		return 0;
	}
	case COMMAND_SET_CAR_FORWARD_SPEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		float speed = GET_FLOAT_PARAM(1) / GAME_SPEED_TO_CARAI_SPEED;
		pVehicle->SetMoveSpeed(pVehicle->GetForward() * speed);
		if (pVehicle->IsRealHeli() && pVehicle->IsCar())
			((CAutomobile*)pVehicle)->m_aWheelSpeed[1] = 0.22f;
		return 0;
	}
	case COMMAND_SET_AREA_VISIBLE:
		CollectParameters(&m_nIp, 1);
		CGame::currArea = GET_INTEGER_PARAM(0);
		CStreaming::RemoveBuildingsNotInArea(GET_INTEGER_PARAM(0)); 
		return 0;
	case COMMAND_MARK_CAR_AS_CONVOY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bPartOfConvoy = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_RESET_HAVOC_CAUSED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CWorld::Players[GET_INTEGER_PARAM(0)].m_nHavocLevel = 0;
		return 0;
	}
	case COMMAND_GET_HAVOC_CAUSED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CWorld::Players[GET_INTEGER_PARAM(0)].m_nHavocLevel);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector result = Multiply3x3(pPed->GetMatrix(), GET_VECTOR_PARAM(1)) + pPed->GetPosition();
		SET_VECTOR_PARAM(0, result);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_HAS_CHAR_BEEN_PHOTOGRAPHED:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		bool result = false;
		if (pPed->bHasBeenPhotographed) {
			result = true;
			pPed->bHasBeenPhotographed = false;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_SWITCH_SECURITY_CAMERA:
	{
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0) != 0) {
			// TheCamera.MBlur.? = 3; TODO(LCS)
			CSpecialFX::bVideoCam = true;
		}
		else {
			// TheCamera.MBlur.Reset();
			CSpecialFX::bVideoCam = false;
		}
		return 0;
	}
	case todo__comm_753:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_753");
		return 0;
	}
	case COMMAND_SET_HELI_ORIENTATION:
	{
		CollectParameters(&m_nIp, 2);
		CAutomobile* pHeli = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pHeli && pHeli->IsCar() && pHeli->IsRealHeli());
		float fAngle = DEGTORAD(GET_FLOAT_PARAM(1) - 90.0f);
		while (fAngle < 0.0f)
			fAngle += TWOPI;
		while (fAngle > TWOPI)
			fAngle -= TWOPI;
		pHeli->SetHeliOrientation(fAngle);
		return 0;
	}
	case COMMAND_CLEAR_HELI_ORIENTATION:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pHeli = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pHeli && pHeli->IsCar() && pHeli->IsRealHeli());
		pHeli->ClearHeliOrientation();
		return 0;
	}
	case COMMAND_PLANE_GOTO_COORDS:
	{
		CollectParameters(&m_nIp, 5);
		CAutomobile* pPlane = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPlane && pPlane->IsCar() && pPlane->IsRealPlane());
		pPlane->TellPlaneToGoToCoors(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4));
		return 0;
	}
	case COMMAND_GET_NTH_CLOSEST_CAR_NODE:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(ThePaths.FindNthNodeClosestToCoors(pos, 0, 999999.9f, true, true, GET_INTEGER_PARAM(3) - 1)));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_GET_NTH_CLOSEST_CHAR_NODE:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(ThePaths.FindNthNodeClosestToCoors(pos, 1, 999999.9f, true, true, GET_INTEGER_PARAM(3) - 1)));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_ENABLE_RC_DETONATE_ON_CONTACT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle::bDisableRemoteDetonationOnContact = (GET_INTEGER_PARAM(0) == 0);
		return 0;
	}
	case COMMAND_FREEZE_CHAR_POSITION:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIsFrozen = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CHAR_DROWNS_IN_WATER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bDrownsInWater = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_OBJECT_RECORDS_COLLISIONS:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bUseCollisionRecords = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_HAS_OBJECT_COLLIDED_WITH_ANYTHING:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		UpdateCompareFlag(pObject->m_nCollisionRecords != 0);
		return 0;
	}
	case COMMAND_REMOVE_RC_BUGGY:
	{
		CWorld::Players[CWorld::PlayerInFocus].BlowUpRCBuggy(false);
		return 0;
	}
	case COMMAND_HAS_PHOTOGRAPH_BEEN_TAKEN:
		UpdateCompareFlag(CWeapon::bPhotographHasBeenTaken);
		CWeapon::bPhotographHasBeenTaken = false;
		return 0;
	case COMMAND_GET_CHAR_ARMOUR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_fArmour);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_HELI_STABILISER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bHeliMinimumTilt = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CAR_STRAIGHT_LINE_DISTANCE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_nSwitchDistance = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_POP_CAR_BOOT:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pCar = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pCar&& pCar->IsCar());
		pCar->PopBoot();
		return 0;
	}
	case COMMAND_SET_PLAYER_MOOD:
	{
		CollectParameters(&m_nIp, 3);
		DMAudio.SetPlayersMood(GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_REQUEST_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CVector pos;
		pos.x = GET_FLOAT_PARAM(0);
		pos.y = GET_FLOAT_PARAM(1);
		pos.z = 0.0f;
		CColStore::RequestCollision(pos);
		return 0;
	}
	case COMMAND_LOCATE_OBJECT_2D:
	case COMMAND_LOCATE_OBJECT_3D:
		LocateObjectCommand(command, &m_nIp);
		return 0;
	case COMMAND_IS_OBJECT_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pObject && pObject->bIsInWater);
		return 0;
	}
	case COMMAND_IS_OBJECT_IN_AREA_2D:
	case COMMAND_IS_OBJECT_IN_AREA_3D:
		ObjectInAreaCheckCommand(command, &m_nIp);
		return 0;
	case COMMAND_SET_CHAR_CROUCH:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->bCrouchWhenShooting = true;
			pPed->SetDuck(GET_INTEGER_PARAM(2), true);
		}
		else {
			pPed->ClearDuck(true);
			pPed->bCrouchWhenShooting = false;
		}
		return 0;
	}
	case todo__comm_778:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_778");
		return 0;
	}
	case COMMAND_REQUEST_ANIMATION:
	{
		char key[KEY_LENGTH_IN_SCRIPT];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CStreaming::RequestAnim(CAnimManager::GetAnimationBlockIndex(key), (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		return 0;
	}
	case COMMAND_HAS_ANIMATION_LOADED:
	{
		char key[KEY_LENGTH_IN_SCRIPT];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		UpdateCompareFlag(CAnimManager::GetAnimationBlock(key)->isLoaded);
		return 0;
	}
	case COMMAND_REMOVE_ANIMATION:
	{
		char key[KEY_LENGTH_IN_SCRIPT];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CStreaming::RemoveAnim(CAnimManager::GetAnimationBlockIndex(key));
		// + empty function on PS2 (not PSP)
		return 0;
	}
	case COMMAND_SET_CHAR_SHUFFLE_INTO_DRIVERS_SEAT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		pPed->PedShuffle();
		return 0;
	}
	case COMMAND_ATTACH_CHAR_TO_OBJECT:
	{
		CollectParameters(&m_nIp, 8);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->AttachPedToEntity(pObject, GET_VECTOR_PARAM(2), GET_INTEGER_PARAM(5), DEGTORAD(GET_INTEGER_PARAM(6)), (eWeaponType)GET_INTEGER_PARAM(7));
		return 0;
	}
	case COMMAND_SET_CHAR_AS_PLAYER_FRIEND:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIsPlayerFriend = GET_INTEGER_PARAM(2);
		return 0;
	}
	case COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING:
	{
		char onscreen_str[12];
		//script_assert(CTheScripts::ScriptSpace[m_nIp++] == ARGUMENT_GLOBALVAR);
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 2);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]); // ???
		strncpy(onscreen_str, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(0), onscreen_str, GET_INTEGER_PARAM(1) - 1, -1, nil, 0);
		return 0;
	}
	case COMMAND_ADD_SET_PIECE:
	{
		CollectParameters(&m_nIp, 13);
		float fTriggerInfX = GET_FLOAT_PARAM(1);
		float fTriggerInfY = GET_FLOAT_PARAM(2);
		float fTriggerSupX = GET_FLOAT_PARAM(3);
		float fTriggerSupY = GET_FLOAT_PARAM(4);
		float fSpawn1X = GET_FLOAT_PARAM(5);
		float fSpawn1Y = GET_FLOAT_PARAM(6);
		float fTarget1X = GET_FLOAT_PARAM(7);
		float fTarget1Y = GET_FLOAT_PARAM(8);
		float fSpawn2X = GET_FLOAT_PARAM(9);
		float fSpawn2Y = GET_FLOAT_PARAM(10);
		float fTarget2X = GET_FLOAT_PARAM(11);
		float fTarget2Y = GET_FLOAT_PARAM(12);
		CSetPieces::AddOne(GET_INTEGER_PARAM(0),
			CVector2D(fTriggerInfX, fTriggerInfY), CVector2D(fTriggerSupX, fTriggerSupY),
			CVector2D(fSpawn1X, fSpawn1Y), CVector2D(fTarget1X, fTarget1Y),
			CVector2D(fSpawn2X, fSpawn2Y), CVector2D(fTarget2X, fTarget2Y));
		return 0;
	}
	case COMMAND_SET_EXTRA_COLOURS:
	{
		CollectParameters(&m_nIp, 2);
		CTimeCycle::StartExtraColour(GET_INTEGER_PARAM(0)-1, GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_CLEAR_EXTRA_COLOURS:
	{
		CollectParameters(&m_nIp, 1);
		CTimeCycle::StopExtraColour(GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_GET_WHEELIE_STATS:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		SET_INTEGER_PARAM(0, pPlayerInfo->m_nLastTimeCarSpentOnTwoWheels);
		SET_FLOAT_PARAM(1, pPlayerInfo->m_nLastDistanceCarTravelledOnTwoWheels);
		SET_INTEGER_PARAM(2, pPlayerInfo->m_nLastTimeSpentOnWheelie);
		SET_FLOAT_PARAM(3, pPlayerInfo->m_nLastDistanceTravelledOnWheelie);
		SET_INTEGER_PARAM(4, pPlayerInfo->m_nLastTimeSpentOnStoppie);
		SET_FLOAT_PARAM(5, pPlayerInfo->m_nLastDistanceTravelledOnStoppie);
		StoreParameters(&m_nIp, 6);
		pPlayerInfo->m_nLastTimeCarSpentOnTwoWheels = 0;
		pPlayerInfo->m_nLastDistanceCarTravelledOnTwoWheels = 0.0f;
		pPlayerInfo->m_nLastTimeSpentOnWheelie = 0;
		pPlayerInfo->m_nLastDistanceTravelledOnWheelie = 0.0f;
		pPlayerInfo->m_nLastTimeSpentOnStoppie = 0;
		pPlayerInfo->m_nLastDistanceTravelledOnStoppie = 0.0f;
		return 0;
	}
	case COMMAND_BURST_CAR_TYRE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle->IsBike()) {
			if (GET_INTEGER_PARAM(1) == 2)
				SET_INTEGER_PARAM(1, 0);
			else if (GET_INTEGER_PARAM(1) == 3)
				SET_INTEGER_PARAM(1, 1);
		}
		pVehicle->BurstTyre(GET_INTEGER_PARAM(1), true);
		return 0;
	}
	case COMMAND_IS_CHAR_OBJ_NO_OBJ:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->m_prevObjective == OBJECTIVE_NONE && pPed->m_objective == OBJECTIVE_NONE);
		return 0;
	}
	case COMMAND_IS_PLAYER_WEARING:
	{
		CollectParameters(&m_nIp, 1);
		char key[12];
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			key[i] = tolower(key[i]);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(CModelInfo::GetModelInfo(pPed->GetModelIndex())->GetNameHashKey() == CKeyGen::GetUppercaseKey(key));
		return 0;
	}
	case COMMAND_SET_PLAYER_CAN_DO_DRIVE_BY:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		pPlayerInfo->m_bDriveByAllowed = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_CREATE_SWAT_ROPE:
	{
		CollectParameters(&m_nIp, 3);
		CRopes::CreateRopeWithSwatComingDown(GET_VECTOR_PARAM(0));
		return 0;
	}
	case COMMAND_SET_CAR_MODEL_COMPONENTS:
	{
		CollectParameters(&m_nIp, 3);
		CVehicleModelInfo::SetComponentsToUse(GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_CLOSE_ALL_CAR_DOORS:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pCar = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pCar&& pCar->IsCar());
		pCar->CloseAllDoors();
		return 0;
	}
	case COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D:
	{
		CollectParameters(&m_nIp, 4);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float X2 = GET_FLOAT_PARAM(2);
		float Y2 = GET_FLOAT_PARAM(3);
		SET_FLOAT_PARAM(0, (CVector2D(X1, Y1) - CVector2D(X2, Y2)).Magnitude());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D:
	{
		CollectParameters(&m_nIp, 6);
		SET_FLOAT_PARAM(0, (GET_VECTOR_PARAM(0) - GET_VECTOR_PARAM(3)).Magnitude());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_POP_CAR_BOOT_USING_PHYSICS:
	{
		CollectParameters(&m_nIp, 1);
		CAutomobile* pCar = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pCar && pCar->IsCar());
		pCar->PopBootUsingPhysics();
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}
