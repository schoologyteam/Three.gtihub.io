#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Bike.h"
#include "CarCtrl.h"
#include "Cranes.h"
#include "Credits.h"
#include "CutsceneMgr.h"
#include "DMAudio.h"
#include "FileMgr.h"
#include "Fire.h"
#include "Frontend.h"
#include "Garages.h"
#include "General.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#include "Hud.h"
#include "Messages.h"
#include "Pad.h"
#include "Particle.h"
#include "Phones.h"
#include "Population.h"
#include "Pools.h"
#include "Record.h"
#include "Remote.h"
#include "Restart.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Weather.h"
#include "Zones.h"
#include "main.h"
#include "GameLogic.h"
#include "Sprite.h"
#include "CarAI.h"
#include "Pickups.h"
#include "Fluff.h"
#include "CustomSoundTrack.h"
//new
#include "User.h"

// LCS: file done except TODOs

#ifdef USE_DEBUG_SCRIPT_LOADER
extern const char* scriptfile;
#endif

bool CRunningScript::ThisIsAValidRandomCop(uint32 mi, int cop, int swat, int fbi, int army, int miami)
{
	switch (mi)
	{
	case MI_COP: if (cop) return true; break;
	case MI_SWAT: if (swat) return true; break;
	case MI_FBI: if (fbi) return true; break;
	case MI_ARMY: if (army) return true; break;
	default: if (mi >= MI_VICE1 && mi <= MI_VICE8 && miami) return true; break;
	}
	return false;
}

bool CRunningScript::ThisIsAValidRandomPed(uint32 pedtype, int civ, int gang, int criminal)
{
    switch (pedtype) {
    case PEDTYPE_CIVMALE:
    case PEDTYPE_CIVFEMALE:
        return civ;
    case PEDTYPE_GANG1:
    case PEDTYPE_GANG2:
    case PEDTYPE_GANG3:
    case PEDTYPE_GANG4:
    case PEDTYPE_GANG5:
    case PEDTYPE_GANG6:
    case PEDTYPE_GANG7:
    case PEDTYPE_GANG8:
    case PEDTYPE_GANG9:
        return gang;
    case PEDTYPE_CRIMINAL:
    case PEDTYPE_PROSTITUTE:
        return criminal;
    default:
        return false;
    }
}

int8 CRunningScript::ProcessCommands1000To1099(int32 command)
{
	switch (command) {
	case COMMAND_DETACH_OBJECT_FROM_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		// if (pObject && pObject->m_pAttachedTo)
		//	pObject->DettachObjectFromEntity();
		return 0;
	}
	case COMMAND_SET_PAD_STICKS_MULTIPLIER:
	{
		CollectParameters(&m_nIp, 2);
		CPad::GetPad(0)->unk_B4 = GET_FLOAT_PARAM(0);
		CPad::GetPad(0)->unk_B8 = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_OVERRIDE_FADE:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // true, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, false
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_ANGLE_BETWEEN_POINTS:
	{
		CollectParameters(&m_nIp, 4);
		SET_FLOAT_PARAM(0, CGeneral::GetAngleBetweenPoints(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_OVERRIDE_CHAR_MOVE_ANIM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOverrideMoveAnim = true;
		return 0;
	}
	case LCSWRONG_COMMAND_1627:
	{
		CollectParameters(&m_nIp, 1);
		// something related to debug menu, not implemented
		return 0;
	}
	case COMMAND_ENABLE_EMERGENCY_VEHICLES:
	{
		CollectParameters(&m_nIp, 1);
		gbEmergencyVehiclesEnabled = GET_INTEGER_PARAM(0) != 0;
		return 0;
	}
	case COMMAND_ADD_UNLOCKED_COSTUME:
		CollectParameters(&m_nIp, 1);
		// CStats::AddUnlockedCostume(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CLEAR_MULTIPLAYER_SPLASH_SCREEN:
		// ClearMultiplayerSplashScreen();
		return 0;
	case COMMAND_PRINT_WITH_2_NUMBERS_NOW_NO_BRIEF:
	{
		wchar* key = GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		SET_FLOAT_PARAM(1, LimitAngleOnCircle(RADTODEG(Asin(pObject->GetForward().z))));
		SET_FLOAT_PARAM(2, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetForward().x, pObject->GetForward().y))));
		SET_FLOAT_PARAM(0, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetRight().z, pObject->GetUp().z))));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->SetOrientation(DEGTORAD(GET_FLOAT_PARAM(2)), DEGTORAD(GET_FLOAT_PARAM(1)), DEGTORAD(GET_FLOAT_PARAM(3)));
		return 0;
	}
	case COMMAND_CHANGE_ONSCREEN_COUNTER_PREFIX:
	{
		uint16 offset = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.ChangeCounterPrefix(offset, GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_STORE_PLAYER_OUTFIT: // vcs done
	{
		//char tmp[12]; // TODO
		//CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		//int32 *ptr = GetPointerToScriptVariable(&m_nIp);
		//debug("%p\n", ptr);
		const char *key = GetKeyFromScript(&m_nIp);
		script_assert(key);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			CGameLogic::mStoredPlayerOutfit[i] = key[i];
		printf("STORED PLAYOUR OUTFIT : %s\n", CGameLogic::mStoredPlayerOutfit);
		//m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_STRING:
	{
		char onscreen_str1[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 2);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(1), onscreen_str1, 0, GET_INTEGER_PARAM(0), nil, 0);
		return 0;
	}
	case COMMAND_SET_PLAYER_CURRENT_WEAPON_AMMO_IN_CLIP:
	{
		CollectParameters(&m_nIp, 1);
		CWeapon* pWeapon = FindPlayerPed()->GetWeapon();
		if (pWeapon && GET_INTEGER_PARAM(0))
			pWeapon->m_nAmmoInClip = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SET_CHAR_WAIT_STATE_REPEAT:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->SetWaitState((eWaitState)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) >= 0 ? &GET_INTEGER_PARAM(2) : nil, true);
		return 0;
	}
	case COMMAND_LOCK_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::LockGarage(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_IS_FINAL_GAME:
#ifdef FINAL
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_SET_ALLOWED_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CTheScripts::AllowedCollision[0] = GET_INTEGER_PARAM(0);
		CTheScripts::AllowedCollision[1] = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_2_STRINGS:
	{
		char onscreen_str1[12];
		char onscreen_str2[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 3);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		wchar* text2 = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str2, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(1), onscreen_str2, 0, GET_INTEGER_PARAM(0), onscreen_str1, GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_GET_PLAYER_STORED_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_storedWeapon);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISABLE_PAUSE_MENU:
		CollectParameters(&m_nIp, 1);
		// FrontEndMenuManager.mDisablePauseMenu = GET_INTEGER_PARAM(0) != 0; // TODO: static + member
		return 0;
	case COMMAND_IS_CHANNEL_PLAYING:
		CollectParameters(&m_nIp, 1);
		//UpdateCompareFlag(DMAudio.IsChannelPlaying(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_SET_CLOCK_EVENT_WARNING:
		CollectParameters(&m_nIp, 3);
		/*
		if (CHud::m_ClockEventWarningMinutes || GET_INTEGER_PARAMS(2)){
			CHud::m_ClockEventWarningMinutes = GET_INTEGER_PARAMS(2);
			CHud::m_ClockEventMinutes = GET_INTEGER_PARAMS(1);
			CHud::m_ClockEventHours = GET_INTEGER_PARAMS(0);
			CHud::m_ClockEventFlashTimer = 0;
		}
		*/
		return 0;
	case COMMAND_SET_EXTRA_COLOUR_LIGHT_DIRECTION:
		CollectParameters(&m_nIp, 3);
		// CWeather::ExtraColourLightDir = GET_VECTOR_PARAM(0);
		// CWeather::ExtraColourLightDir.Normalise();
		return 0;
	case todo__comm_1029:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1029");
		return 0;
	}
	case COMMAND_PRINT_HELP_NO_BRIEF:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_NO_BRIEF:
	{
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_PRINT_HELP_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_SET_CAR_IS_REWARD:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bRewardVehicle = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case todo__comm_1035:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1035");
		return 0;
	}
	case todo__comm_1036:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1036");
		return 0;
	}
	case todo__comm_1037:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1037");
		return 0;
	}
	case todo__comm_1038:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1038");
		return 0;
	}
	case todo__comm_1039:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1039");
		return 0;
	}
	case todo__comm_1040:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1040");
		return 0;
	}
	case todo__comm_1041:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1041");
		return 0;
	}
	case todo__comm_1042:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1042");
		return 0;
	}
	case todo__comm_1043:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1043");
		return 0;
	}
	case todo__comm_1044:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1044");
		return 0;
	}
	case todo__comm_1045:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1045");
		return 0;
	}
	case todo__comm_1046:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1046");
		return 0;
	}
	case todo__comm_1047:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1047");
		return 0;
	}
	case todo__comm_1048:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1048");
		return 0;
	}
	case todo__comm_1049:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1049");
		return 0;
	}
	case todo__comm_1050:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1050");
		return 0;
	}
	case todo__comm_1051:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1051");
		return 0;
	}
	case todo__comm_1052:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1052");
		return 0;
	}
	case todo__comm_1053:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1053");
		return 0;
	}
	case todo__comm_1054:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1054");
		return 0;
	}
	case todo__comm_1055:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1055");
		return 0;
	}
	case todo__comm_1056:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1056");
		return 0;
	}
	case todo__comm_1057:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1057");
		return 0;
	}
	case todo__comm_1058:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1058");
		return 0;
	}
	case todo__comm_1059:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1059");
		return 0;
	}
	case todo__comm_1060:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1060");
		return 0;
	}
	case todo__comm_1061:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1061");
		return 0;
	}
	case todo__comm_1062:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1062");
		return 0;
	}
	case todo__comm_1063:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1063");
		return 0;
	}
	case todo__comm_1064:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1064");
		return 0;
	}
	case todo__comm_1065:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1065");
		return 0;
	}
	case todo__comm_1066:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1066");
		return 0;
	}
	case todo__comm_1067:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1067");
		return 0;
	}
	case todo__comm_1068:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1068");
		return 0;
	}
	case todo__comm_1069:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1069");
		return 0;
	}
	case todo__comm_1070:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1070");
		return 0;
	}
	case todo__comm_1071:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1071");
		return 0;
	}
	case todo__comm_1072:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1072");
		return 0;
	}
	case todo__comm_1073:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1073");
		return 0;
	}
	case todo__comm_1074:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1074");
		return 0;
	}
	case todo__comm_1075:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1075");
		return 0;
	}
	case todo__comm_1076:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1076");
		return 0;
	}
	case todo__comm_1077:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1077");
		return 0;
	}
	case todo__comm_1078:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1078");
		return 0;
	}
	case todo__comm_1079:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1079");
		return 0;
	}
	case todo__comm_1080:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1080");
		return 0;
	}
	case todo__comm_1081:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1081");
		return 0;
	}
	case todo__comm_1082:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1082");
		return 0;
	}
	case todo__comm_1083:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1083");
		return 0;
	}
	case todo__comm_1084:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1084");
		return 0;
	}
	case todo__comm_1085:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1085");
		return 0;
	}
	case todo__comm_1086:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1086");
		return 0;
	}
	case todo__comm_1087:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1087");
		return 0;
	}
	case todo__comm_1088:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1088");
		return 0;
	}
	case todo__comm_1089:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1089");
		return 0;
	}
	case todo__comm_1090:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1090");
		return 0;
	}
	case todo__comm_1091:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1091");
		return 0;
	}
	case todo__comm_1092:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1092");
		return 0;
	}
	case todo__comm_1093:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1093");
		return 0;
	}
	case todo__comm_1094:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1094");
		return 0;
	}
	case todo__comm_1095:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1095");
		return 0;
	}
	case todo__comm_1096:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1096");
		return 0;
	}
	case todo__comm_1097:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1097");
		return 0;
	}
	case todo__comm_1098:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1098");
		return 0;
	}
	case todo__comm_1099:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1099");
		return 0;
	}

	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1100To1199(int32 command)
{
	char tmp[48];
	switch (command) {
	case todo__comm_1100:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1100");
		return 0;
	}
	case todo__comm_1101:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1101");
		return 0;
	}
	case todo__comm_1102:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1102");
		return 0;
	}
	case todo__comm_1103:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1103");
		return 0;
	}
	case todo__comm_1104:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1104");
		return 0;
	}
	case todo__comm_1105:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1105");
		return 0;
	}
	case todo__comm_1106:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1106");
		return 0;
	}
	case todo__comm_1107:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1107");
		return 0;
	}
	case todo__comm_1108:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1108");
		return 0;
	}
	case todo__comm_1109:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1109");
		return 0;
	}
	case todo__comm_1110:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1110");
		return 0;
	}
	case todo__comm_1111:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1111");
		return 0;
	}
	case todo__comm_1112:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1112");
		return 0;
	}
	case todo__comm_1113:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1113");
		return 0;
	}
	case todo__comm_1114:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1114");
		return 0;
	}
	case todo__comm_1115:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1115");
		return 0;
	}
	case todo__comm_1116:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1116");
		return 0;
	}
	case todo__comm_1117:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1117");
		return 0;
	}
	case todo__comm_1118:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1118");
		return 0;
	}
	case todo__comm_1119:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1119");
		return 0;
	}
	case todo__comm_1120:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1120");
		return 0;
	}
	case todo__comm_1121:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1121");
		return 0;
	}
	case todo__comm_1122:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1122");
		return 0;
	}
	case todo__comm_1123:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1123");
		return 0;
	}
	case todo__comm_1124:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1124");
		return 0;
	}
	case todo__comm_1125:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1125");
		return 0;
	}
	case todo__comm_1126:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1126");
		return 0;
	}
	case todo__comm_1127:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1127");
		return 0;
	}
	case todo__comm_1128:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1128");
		return 0;
	}
	case todo__comm_1129:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1129");
		return 0;
	}
	case todo__comm_1130:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1130");
		return 0;
	}
	case todo__comm_1131:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1131");
		return 0;
	}
	case todo__comm_1132:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1132");
		return 0;
	}
	case todo__comm_1133:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1133");
		return 0;
	}
	case todo__comm_1134:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1134");
		return 0;
	}
	case todo__comm_1135:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1135");
		return 0;
	}
	case todo__comm_1136:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1136");
		return 0;
	}
	case todo__comm_1137:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1137");
		return 0;
	}
	case todo__comm_1138:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1138");
		return 0;
	}
	case todo__comm_1139:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1139");
		return 0;
	}
	case todo__comm_1140:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1140");
		return 0;
	}
	case todo__comm_1141:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1141");
		return 0;
	}
	case todo__comm_1142:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1142");
		return 0;
	}
	case todo__comm_1143:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1143");
		return 0;
	}
	case todo__comm_1144:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1144");
		return 0;
	}
	case todo__comm_1145:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1145");
		return 0;
	}
	case todo__comm_1146:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1146");
		return 0;
	}
	case todo__comm_1147:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1147");
		return 0;
	}
	case todo__comm_1148:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1148");
		return 0;
	}
	case todo__comm_1149:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1149");
		return 0;
	}
	case todo__comm_1150:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1150");
		return 0;
	}
	case todo__comm_1151:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1151");
		return 0;
	}
	case todo__comm_1152:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1152");
		return 0;
	}
	case todo__comm_1153:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1153");
		return 0;
	}
	case todo__comm_1154:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1154");
		return 0;
	}
	case todo__comm_1155:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1155");
		return 0;
	}
	case todo__comm_1156:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1156");
		return 0;
	}
	case todo__comm_1157:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1157");
		return 0;
	}
	case todo__comm_1158:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1158");
		return 0;
	}
	case todo__comm_1159:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1159");
		return 0;
	}
	case todo__comm_1160:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1160");
		return 0;
	}
	case todo__comm_1161:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1161");
		return 0;
	}
	case todo__comm_1162:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1162");
		return 0;
	}
	case todo__comm_1163:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1163");
		return 0;
	}
	case todo__comm_1164:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1164");
		return 0;
	}
	case todo__comm_1165:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1165");
		return 0;
	}
	case todo__comm_1166:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1166");
		return 0;
	}
	case todo__comm_1167:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1167");
		return 0;
	}
	case todo__comm_1168:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1168");
		return 0;
	}
	case todo__comm_1169:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1169");
		return 0;
	}
	case todo__comm_1170:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1170");
		return 0;
	}
	case todo__comm_1171:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1171");
		return 0;
	}
	case todo__comm_1172:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1172");
		return 0;
	}
	case todo__comm_1173:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1173");
		return 0;
	}
	case todo__comm_1174:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1174");
		return 0;
	}
	case todo__comm_1175:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1175");
		return 0;
	}
	case todo__comm_1176:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1176");
		return 0;
	}
	case todo__comm_1177:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1177");
		return 0;
	}
	case todo__comm_1178:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1178");
		return 0;
	}
	case todo__comm_1179:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1179");
		return 0;
	}
	case todo__comm_1180:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1180");
		return 0;
	}
	case todo__comm_1181:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1181");
		return 0;
	}
	case todo__comm_1182:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1182");
		return 0;
	}
	case todo__comm_1183:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1183");
		return 0;
	}
	case todo__comm_1184:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1184");
		return 0;
	}
	case todo__comm_1185:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1185");
		return 0;
	}
	case todo__comm_1186:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1186");
		return 0;
	}
	case todo__comm_1187:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1187");
		return 0;
	}
	case todo__comm_1188:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1188");
		return 0;
	}
	case todo__comm_1189:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1189");
		return 0;
	}
	case todo__comm_1190:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1190");
		return 0;
	}
	case todo__comm_1191:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1191");
		return 0;
	}
	case todo__comm_1192:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1192");
		return 0;
	}
	case todo__comm_1193:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1193");
		return 0;
	}
	case todo__comm_1194:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1194");
		return 0;
	}
	case todo__comm_1195:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1195");
		return 0;
	}
	case todo__comm_1196:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1196");
		return 0;
	}
	case todo__comm_1197:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1197");
		return 0;
	}
	case todo__comm_1198:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1198");
		return 0;
	}
	case todo__comm_1199:
	{
		script_assert(false && "TODO_OR_CHECK_todo__comm_1199");
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
