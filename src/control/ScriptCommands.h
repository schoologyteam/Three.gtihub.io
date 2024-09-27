#pragma once

enum
{
	COMMAND_NOP,
	COMMAND_WAIT,
	COMMAND_GOTO,
	COMMAND_SHAKE_CAM,
       COMMAND_SET_VAR_INT,
       COMMAND_SET_VAR_FLOAT,
    COMMAND_SET_VAR_STRING,
       COMMAND_ADD_VAL_TO_INT_LVAR,
       COMMAND_ADD_VAL_TO_FLOAT_LVAR,
       COMMAND_SUB_VAL_FROM_INT_VAR,
       COMMAND_SUB_VAL_FROM_FLOAT_VAR,
       COMMAND_MULT_INT_LVAR_BY_VAL,
       COMMAND_MULT_FLOAT_LVAR_BY_VAL,
       COMMAND_DIV_INT_LVAR_BY_VAL,
       COMMAND_DIV_FLOAT_LVAR_BY_VAL,
       COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER,
       COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR,
       COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR,
       COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER,
       COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR,
       COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR,
       COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER,
       COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR,
       COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR,
       COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER,
       COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR,
       COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR,
       COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER,
       COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR,
       COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER,
       COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR,
    COMMAND_IS_STRING_VAR_EQUAL_TO_STRING_VAR_31,
    COMMAND_IS_STRING_VAR_EQUAL_TO_STRING_VAR_32,
	COMMAND_GOTO_IF_TRUE,
	COMMAND_GOTO_IF_FALSE,
	COMMAND_TERMINATE_THIS_SCRIPT,
	COMMAND_START_NEW_SCRIPT,
	COMMAND_GOSUB,
	COMMAND_RETURN,
	COMMAND_LINE,
	COMMAND_CREATE_PLAYER,
       COMMAND_ADD_INT_LVAR_TO_INT_LVAR,
       COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR,
       COMMAND_SUB_INT_LVAR_FROM_INT_LVAR,
       COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR,
       COMMAND_MULT_INT_LVAR_BY_INT_LVAR,
       COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR,
       COMMAND_DIV_INT_LVAR_BY_INT_LVAR,
       COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR,
       COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR,
       COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR,
       COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR,
       COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR,
       COMMAND_SET_VAR_INT_TO_LVAR_INT, // todo lvar to var
       COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT,
    DUPLICATE_COMMAND_55,
       COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT, // sb ��������
       COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT,
	COMMAND_ABS_VAR_INT,
	COMMAND_ABS_VAR_FLOAT,
	COMMAND_GENERATE_RANDOM_FLOAT,
	COMMAND_GENERATE_RANDOM_INT,
	COMMAND_CREATE_CHAR,
	COMMAND_DELETE_CHAR,
	COMMAND_CHAR_WANDER_DIR,
	COMMAND_CHAR_FOLLOW_PATH,
	COMMAND_CHAR_SET_IDLE,
	COMMAND_GET_CHAR_COORDINATES,
	COMMAND_SET_CHAR_COORDINATES,
	COMMAND_IS_CHAR_STILL_ALIVE,
	COMMAND_IS_CHAR_IN_AREA_2D,
	COMMAND_IS_CHAR_IN_AREA_3D,
	COMMAND_CREATE_CAR,
	COMMAND_DELETE_CAR,
	COMMAND_CAR_GOTO_COORDINATES,
	COMMAND_CAR_WANDER_RANDOMLY,
	COMMAND_CAR_SET_IDLE,
	COMMAND_GET_CAR_COORDINATES,
	COMMAND_SET_CAR_COORDINATES,
	COMMAND_IS_CAR_STILL_ALIVE,
	COMMAND_SET_CAR_CRUISE_SPEED,
	COMMAND_SET_CAR_DRIVING_STYLE,
	COMMAND_SET_CAR_MISSION,
	COMMAND_IS_CAR_IN_AREA_2D,
	COMMAND_IS_CAR_IN_AREA_3D,
	COMMAND_PRINT_BIG,
	COMMAND_PRINT,
	COMMAND_PRINT_NOW,
	COMMAND_PRINT_SOON,
	COMMAND_CLEAR_PRINTS,
	COMMAND_GET_TIME_OF_DAY,
	COMMAND_SET_TIME_OF_DAY,
	COMMAND_GET_MINUTES_TO_TIME_OF_DAY,
	COMMAND_IS_POINT_ON_SCREEN,
	COMMAND_RETURN_TRUE,
	COMMAND_RETURN_FALSE,
		COMMAND_NULL_96,
		COMMAND_NULL_97,
		COMMAND_NULL_98,
		COMMAND_NULL_99,
		COMMAND_NULL_100,
		COMMAND_NULL_101,
		COMMAND_NULL_102,
		COMMAND_NULL_103,
		COMMAND_NULL_104,
		COMMAND_NULL_105,
		COMMAND_NULL_106,
		COMMAND_NULL_107,
		COMMAND_NULL_108,
		COMMAND_NULL_109,
		COMMAND_NULL_110,
		COMMAND_NULL_111,
		COMMAND_NULL_112,
		COMMAND_NULL_113,
		COMMAND_NULL_114,
		COMMAND_NULL_115,
		COMMAND_NULL_116,
		COMMAND_NULL_117,
		COMMAND_NULL_118,
		COMMAND_NULL_119,
	COMMAND_ANDOR,
	COMMAND_LAUNCH_MISSION,
	COMMAND_MISSION_HAS_FINISHED,
	COMMAND_STORE_CAR_CHAR_IS_IN,
	COMMAND_IS_CHAR_IN_CAR,
	COMMAND_IS_CHAR_IN_MODEL,
	COMMAND_IS_CHAR_IN_ANY_CAR,
	COMMAND_IS_BUTTON_PRESSED,
	COMMAND_LOCATE_CHAR_ANY_MEANS_2D,
	COMMAND_LOCATE_CHAR_ON_FOOT_2D,
	COMMAND_LOCATE_CHAR_IN_CAR_2D,
	COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D,
	COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D,
	COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D,
	COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D,
	COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D,
	COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D,
       COMMAND_LOCATE_CHAR_ANY_MEANS_3D, //COMMAND_LOCATE_PLAYER_ANY_MEANS_3D, ??
	COMMAND_LOCATE_CHAR_ON_FOOT_3D,
	COMMAND_LOCATE_CHAR_IN_CAR_3D,
	COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D,
	COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D,
	COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D,
	COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D,
	COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D,
	COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D,
	COMMAND_CREATE_OBJECT,
	COMMAND_DELETE_OBJECT,
	COMMAND_ADD_SCORE,
	COMMAND_IS_SCORE_GREATER,
	COMMAND_STORE_SCORE,
	COMMAND_GIVE_REMOTE_CONTROLLED_CAR_TO_PLAYER,
	COMMAND_ALTER_WANTED_LEVEL,
	COMMAND_ALTER_WANTED_LEVEL_NO_DROP,
	COMMAND_IS_WANTED_LEVEL_GREATER,
	COMMAND_CLEAR_WANTED_LEVEL,
	COMMAND_SET_DEATHARREST_STATE,
	COMMAND_HAS_DEATHARREST_BEEN_EXECUTED,
	COMMAND_ADD_AMMO_TO_CHAR,
	COMMAND_IS_CHAR_DEAD,
	COMMAND_IS_CAR_DEAD,
	COMMAND_SET_CHAR_THREAT_SEARCH,
	COMMAND_SET_CHAR_OBJ_NO_OBJ,
	COMMAND_IS_CHAR_OBJECTIVE_PASSED,
	COMMAND_CREATE_CHAR_INSIDE_CAR,
	COMMAND_HAS_PLAYER_BEEN_ARRESTED,
	COMMAND_IS_CAR_MODEL,
	COMMAND_GIVE_CAR_ALARM,
	COMMAND_IS_CAR_CRUSHED,
	COMMAND_CREATE_CAR_GENERATOR,
	COMMAND_SWITCH_CAR_GENERATOR,
	COMMAND_DISPLAY_ONSCREEN_TIMER,
	COMMAND_CLEAR_ONSCREEN_TIMER,
	COMMAND_DISPLAY_ONSCREEN_COUNTER,
	COMMAND_CLEAR_ONSCREEN_COUNTER,
	COMMAND_SET_ZONE_CAR_INFO,
	COMMAND_IS_CHAR_IN_ZONE,
	COMMAND_SET_CAR_DENSITY,
	COMMAND_SET_PED_DENSITY,
	COMMAND_POINT_CAMERA_AT_PLAYER,
	COMMAND_POINT_CAMERA_AT_CAR,
	COMMAND_POINT_CAMERA_AT_CHAR,
	COMMAND_RESTORE_CAMERA,
	COMMAND_SET_ZONE_PED_INFO,
	COMMAND_SET_TIME_SCALE,
	COMMAND_SET_FIXED_CAMERA_POSITION,
	COMMAND_POINT_CAMERA_AT_POINT,
	COMMAND_REMOVE_BLIP,
	COMMAND_CHANGE_BLIP_COLOUR,
	COMMAND_DIM_BLIP,
	COMMAND_ADD_BLIP_FOR_COORD_OLD,
	COMMAND_CHANGE_BLIP_SCALE,
	COMMAND_ADD_BLIP_FOR_CAR,
	COMMAND_ADD_BLIP_FOR_CHAR,
	COMMAND_ADD_BLIP_FOR_OBJECT,
	COMMAND_ADD_BLIP_FOR_COORD,
	COMMAND_CHANGE_BLIP_DISPLAY,
	COMMAND_ADD_SPRITE_BLIP_FOR_CONTACT_POINT,
	COMMAND_ADD_SPRITE_BLIP_FOR_COORD,
	COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_COORD,
	COMMAND_SET_FADING_COLOUR,
	COMMAND_DO_FADE,
	COMMAND_GET_FADING_STATUS,
	COMMAND_ADD_HOSPITAL_RESTART,
	COMMAND_ADD_POLICE_RESTART,
	COMMAND_OVERRIDE_NEXT_RESTART,
	COMMAND_GET_CHAR_HEADING,
	COMMAND_SET_CHAR_HEADING,
	COMMAND_GET_CAR_HEADING,
	COMMAND_SET_CAR_HEADING,
	COMMAND_GET_OBJECT_HEADING,
	COMMAND_SET_OBJECT_HEADING,
	COMMAND_IS_CHAR_TOUCHING_OBJECT,
	COMMAND_SET_CHAR_AMMO,
	COMMAND_DECLARE_MISSION_FLAG,
	COMMAND_IS_CHAR_HEALTH_GREATER,
	COMMAND_IS_CAR_HEALTH_GREATER,
	COMMAND_ADD_ONE_OFF_SOUND,
	COMMAND_ADD_CONTINUOUS_SOUND,
	COMMAND_REMOVE_SOUND,
	COMMAND_IS_CAR_STUCK_ON_ROOF,
	COMMAND_ADD_UPSIDEDOWN_CAR_CHECK,
	COMMAND_REMOVE_UPSIDEDOWN_CAR_CHECK,
	COMMAND_SET_CHAR_OBJ_WAIT_ON_FOOT,
	COMMAND_SET_CHAR_OBJ_FLEE_ON_FOOT_TILL_SAFE,
	COMMAND_SET_CHAR_OBJ_GUARD_SPOT,
	COMMAND_SET_CHAR_OBJ_GUARD_AREA,
	COMMAND_SET_CHAR_OBJ_WAIT_IN_CAR,
	COMMAND_SET_CHAR_OBJ_KILL_CHAR_ON_FOOT,
	COMMAND_SET_CHAR_OBJ_KILL_CHAR_ANY_MEANS,
	COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS,
	COMMAND_SET_CHAR_OBJ_GOTO_CHAR_ON_FOOT,
	COMMAND_SET_CHAR_OBJ_LEAVE_CAR,
	COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_PASSENGER,
	COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_DRIVER,
	COMMAND_SET_CHAR_OBJ_DESTROY_OBJECT,
	COMMAND_SET_CHAR_OBJ_DESTROY_CAR,
	COMMAND_SET_CHAR_OBJ_GOTO_AREA_ON_FOOT,
	COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT,
	COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION,
	COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR,
	COMMAND_SET_CHAR_OBJ_LEAVE_ANY_CAR,
	COMMAND_SET_CHAR_OBJ_FLEE_CAR,
	COMMAND_SET_CHAR_OBJ_WALK_TO_CHAR,
	COMMAND_SET_CHAR_OBJ_AIM_GUN_AT_CHAR,
	COMMAND_SET_CHAR_OBJ_SPRINT_TO_COORD,
	COMMAND_IS_CHAR_IN_AREA_ON_FOOT_2D,
	COMMAND_IS_CHAR_IN_AREA_IN_CAR_2D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_2D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_2D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_2D,
	COMMAND_IS_CHAR_IN_AREA_ON_FOOT_3D,
	COMMAND_IS_CHAR_IN_AREA_IN_CAR_3D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_3D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_3D,
	COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_3D,
	COMMAND_IS_CAR_STOPPED_IN_AREA_2D,
	COMMAND_IS_CAR_STOPPED_IN_AREA_3D,
	COMMAND_LOCATE_CAR_2D,
	COMMAND_LOCATE_STOPPED_CAR_2D,
	COMMAND_LOCATE_CAR_3D,
	COMMAND_LOCATE_STOPPED_CAR_3D,
	COMMAND_GIVE_WEAPON_TO_CHAR,
	COMMAND_SET_PLAYER_CONTROL,
	COMMAND_FORCE_WEATHER,
	COMMAND_FORCE_WEATHER_NOW,
	COMMAND_RELEASE_WEATHER,
	COMMAND_SET_CURRENT_CHAR_WEAPON,
	COMMAND_GET_OBJECT_COORDINATES,
	COMMAND_SET_OBJECT_COORDINATES,
	COMMAND_GET_GAME_TIMER,
	COMMAND_TURN_CHAR_TO_FACE_COORD,
	COMMAND_STORE_WANTED_LEVEL,
	COMMAND_IS_CAR_STOPPED,
	COMMAND_MARK_CHAR_AS_NO_LONGER_NEEDED,
	COMMAND_MARK_CAR_AS_NO_LONGER_NEEDED,
	COMMAND_MARK_OBJECT_AS_NO_LONGER_NEEDED,
	COMMAND_DONT_REMOVE_CHAR,
	COMMAND_DONT_REMOVE_CAR,
	COMMAND_DONT_REMOVE_OBJECT,
	COMMAND_CREATE_CHAR_AS_PASSENGER,
	COMMAND_SET_CHAR_AS_LEADER,
	COMMAND_LEAVE_GROUP,
	COMMAND_SET_CHAR_OBJ_FOLLOW_ROUTE,
	COMMAND_ADD_ROUTE_POINT,
	COMMAND_PRINT_WITH_NUMBER_BIG,
	COMMAND_PRINT_WITH_NUMBER,
	COMMAND_PRINT_WITH_NUMBER_NOW,
	COMMAND_PRINT_WITH_NUMBER_SOON,
	COMMAND_SWITCH_ROADS_ON,
	COMMAND_SWITCH_ROADS_OFF,
	COMMAND_GET_NUMBER_OF_PASSENGERS,
	COMMAND_GET_MAXIMUM_NUMBER_OF_PASSENGERS,
	COMMAND_SET_CAR_DENSITY_MULTIPLIER,
	COMMAND_SET_CAR_HEAVY,
	COMMAND_CLEAR_CHAR_THREAT_SEARCH,
	COMMAND_SET_MAX_WANTED_LEVEL,
		COMMAND_NULL_297,
		COMMAND_NULL_298,
		COMMAND_NULL_299,
	COMMAND_IS_CAR_IN_AIR_PROPER,
	COMMAND_IS_CAR_UPSIDEDOWN,
	COMMAND_SET_POLICE_IGNORE_PLAYER,
	COMMAND_START_KILL_FRENZY,
	COMMAND_READ_KILL_FRENZY_STATUS,
	COMMAND_SQRT,
	COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D,
	COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D,
	COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D,
	COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D,
	COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D,
	COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D,
	COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE,
	COMMAND_GENERATE_RANDOM_INT_IN_RANGE,
	COMMAND_LOCK_CAR_DOORS,
	COMMAND_EXPLODE_CAR,
	COMMAND_ADD_EXPLOSION,
	COMMAND_IS_CAR_UPRIGHT,
	COMMAND_TURN_CHAR_TO_FACE_CHAR,
	COMMAND_CREATE_PICKUP,
	COMMAND_HAS_PICKUP_BEEN_COLLECTED,
	COMMAND_REMOVE_PICKUP,
	COMMAND_SET_TAXI_LIGHTS,
	COMMAND_PRINT_BIG_Q,
	COMMAND_PRINT_WITH_NUMBER_BIG_Q,
	COMMAND_SET_GARAGE,
	COMMAND_SET_TARGET_CAR_FOR_MISSION_GARAGE,
	COMMAND_IS_CAR_IN_MISSION_GARAGE,
	COMMAND_SET_FREE_BOMBS,
	COMMAND_IS_CAR_ARMED_WITH_ANY_BOMB,
	COMMAND_APPLY_BRAKES_TO_PLAYERS_CAR,
	COMMAND_SET_CHAR_HEALTH,
	COMMAND_SET_CAR_HEALTH,
	COMMAND_GET_CHAR_HEALTH,
	COMMAND_GET_CAR_HEALTH,
	COMMAND_IS_CAR_ARMED_WITH_BOMB,
	COMMAND_CHANGE_CAR_COLOUR,
	COMMAND_SWITCH_PED_ROADS_ON,
	COMMAND_SWITCH_PED_ROADS_OFF,
	COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS,
	COMMAND_STOP_CHAR_LOOKING,
	COMMAND_SET_GANG_PED_MODELS,
	COMMAND_SET_GANG_CAR_MODEL,
	COMMAND_SET_GANG_WEAPONS,
	COMMAND_SET_CHAR_OBJ_RUN_TO_COORD,
	COMMAND_LOAD_SPECIAL_CHARACTER,
	COMMAND_HAS_SPECIAL_CHARACTER_LOADED,
	COMMAND_IS_PLAYER_IN_REMOTE_MODE,
	COMMAND_ARM_CAR_WITH_BOMB,
	COMMAND_SET_CHAR_PERSONALITY,
	COMMAND_SET_CUTSCENE_OFFSET,
	COMMAND_SET_ANIM_GROUP_FOR_CHAR,
	COMMAND_REQUEST_MODEL,
	COMMAND_HAS_MODEL_LOADED,
	COMMAND_MARK_MODEL_AS_NO_LONGER_NEEDED,
	COMMAND_GRAB_PHONE,
	COMMAND_TURN_PHONE_OFF,
	COMMAND_DRAW_CORONA,
	COMMAND_STORE_WEATHER,
	COMMAND_RESTORE_WEATHER,
	COMMAND_STORE_CLOCK,
	COMMAND_RESTORE_CLOCK,
	COMMAND_RESTART_CRITICAL_MISSION,
	todo__comm_363,
	COMMAND_SET_COLL_OBJ_NO_OBJ,
	COMMAND_SET_COLL_OBJ_WAIT_ON_FOOT,
	COMMAND_SET_COLL_OBJ_FLEE_ON_FOOT_TILL_SAFE,
	COMMAND_SET_COLL_OBJ_GUARD_SPOT,
	COMMAND_SET_COLL_OBJ_GUARD_AREA,
	COMMAND_SET_COLL_OBJ_WAIT_IN_CAR,
	COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT,
	COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS,
	COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS,
	COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT,
	todo__comm_374,
	COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_PASSENGER,
	COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_DRIVER,
	todo__comm_377,
	todo__comm_378,
	COMMAND_SET_COLL_OBJ_GOTO_AREA_ON_FOOT,
	COMMAND_SET_COLL_OBJ_GOTO_COORD_ON_FOOT,
	todo__comm_381,
	todo__comm_382,
	COMMAND_SET_COLL_OBJ_LEAVE_CAR,
	todo__comm_384,
	todo__comm_385,
	todo__comm_386,
	todo__comm_387,
	COMMAND_SET_COLL_OBJ_FOLLOW_ROUTE,
	COMMAND_SET_COLL_OBJ_RUN_TO_COORD,
	todo__comm_390,
	todo__comm_391,
	todo__comm_392,
	todo__comm_393,
	todo__comm_394,
	todo__comm_395,
	todo__comm_396,
	todo__comm_397,
	todo__comm_398,
	todo__comm_399,
	todo__comm_400,
	todo__comm_401,
	todo__comm_402,
	todo__comm_403,
	todo__comm_404,
	todo__comm_405,
	todo__comm_406,
	todo__comm_407,
	todo__comm_408,
	todo__comm_409,
	todo__comm_410,
	todo__comm_411,
	todo__comm_412,
	todo__comm_413,
	todo__comm_414,
	todo__comm_415,
	todo__comm_416,
	todo__comm_417,
	todo__comm_418,
	todo__comm_419,
	COMMAND_SET_CHAR_HEED_THREATS,
	COMMAND_GET_CONTROLLER_MODE,
	COMMAND_SET_CAN_RESPRAY_CAR,
	COMMAND_UNLOAD_SPECIAL_CHARACTER,
	COMMAND_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER,
	COMMAND_GET_NUM_OF_MODELS_KILLED_BY_PLAYER,
	COMMAND_CREATE_OBJECT_NO_OFFSET,
	COMMAND_IS_BOAT,
	COMMAND_IS_CHAR_STOPPED,
	COMMAND_MESSAGE_WAIT,
	COMMAND_SWITCH_WIDESCREEN,
	COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER,
	COMMAND_SET_CAR_ONLY_DAMAGED_BY_PLAYER,
	COMMAND_SET_CHAR_PROOFS,
	COMMAND_SET_CAR_PROOFS,
	COMMAND_IS_CAR_IN_WATER,
	COMMAND_GET_CLOSEST_CHAR_NODE,
	COMMAND_GET_CLOSEST_CAR_NODE,
	COMMAND_CAR_GOTO_COORDINATES_ACCURATE,
	COMMAND_IS_CAR_ON_SCREEN,
	COMMAND_IS_CHAR_ON_SCREEN,
	COMMAND_IS_OBJECT_ON_SCREEN,
	COMMAND_GOSUB_FILE,
	COMMAND_GET_GROUND_Z_FOR_3D_COORD,
	COMMAND_START_SCRIPT_FIRE,
	COMMAND_IS_SCRIPT_FIRE_EXTINGUISHED,
	COMMAND_REMOVE_SCRIPT_FIRE,
	COMMAND_BOAT_GOTO_COORDS,
	COMMAND_BOAT_STOP,
	COMMAND_IS_PLAYER_SHOOTING_IN_AREA,
	COMMAND_IS_CURRENT_CHAR_WEAPON,
	COMMAND_SET_BOAT_CRUISE_SPEED,
	COMMAND_GET_RANDOM_CHAR_IN_AREA,
	COMMAND_IS_PLAYER_IN_TAXI,
	COMMAND_IS_PLAYER_SHOOTING,
	COMMAND_IS_CHAR_SHOOTING,
	COMMAND_CREATE_MONEY_PICKUP,
	COMMAND_SET_CHAR_ACCURACY,
	COMMAND_GET_CAR_SPEED,
	COMMAND_LOAD_CUTSCENE,
	COMMAND_START_CUTSCENE,
	COMMAND_HAS_CUTSCENE_FINISHED,
	COMMAND_CLEAR_CUTSCENE,
	COMMAND_RESTORE_CAMERA_JUMPCUT,
	COMMAND_IS_CHAR_MODEL,
	COMMAND_LOAD_SPECIAL_MODEL,
	COMMAND_SIN,
	COMMAND_COS,
	COMMAND_GET_CAR_FORWARD_X,
	COMMAND_GET_CAR_FORWARD_Y,
	COMMAND_CHANGE_GARAGE_TYPE,
	COMMAND_ACTIVATE_CRUSHER_CRANE,
	COMMAND_PRINT_WITH_2_NUMBERS,
	COMMAND_PRINT_WITH_2_NUMBERS_NOW,
	COMMAND_PRINT_WITH_2_NUMBERS_SOON,
	COMMAND_PRINT_WITH_3_NUMBERS,
	COMMAND_PRINT_WITH_3_NUMBERS_NOW,
	COMMAND_PRINT_WITH_4_NUMBERS,
	COMMAND_PRINT_WITH_6_NUMBERS,
	COMMAND_PLAYER_MADE_PROGRESS,
	COMMAND_SET_PROGRESS_TOTAL,
	COMMAND_REGISTER_JUMP_DISTANCE,
	COMMAND_REGISTER_JUMP_HEIGHT,
	COMMAND_REGISTER_JUMP_FLIPS,
	COMMAND_REGISTER_JUMP_SPINS,
	COMMAND_REGISTER_JUMP_STUNT,
	COMMAND_REGISTER_UNIQUE_JUMP_FOUND,
	COMMAND_SET_UNIQUE_JUMPS_TOTAL,
	COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI,
	COMMAND_REGISTER_MONEY_MADE_TAXI,
	COMMAND_REGISTER_MISSION_GIVEN,
	COMMAND_REGISTER_MISSION_PASSED,
	COMMAND_SET_CHAR_RUNNING,
	COMMAND_REMOVE_ALL_SCRIPT_FIRES,
	COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON,
	COMMAND_HAS_CAR_BEEN_DAMAGED_BY_WEAPON,
	COMMAND_IS_CHAR_IN_PLAYERS_GROUP,
	COMMAND_EXPLODE_CHAR_HEAD,
	COMMAND_ANCHOR_BOAT,
	COMMAND_SET_ZONE_GROUP,
	COMMAND_START_CAR_FIRE,
	COMMAND_START_CHAR_FIRE,
	COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA,
	COMMAND_HAS_RESPRAY_HAPPENED,
	COMMAND_SET_CAMERA_ZOOM,
	COMMAND_CREATE_PICKUP_WITH_AMMO,
	todo__comm_506,
	COMMAND_SET_PLAYER_NEVER_GETS_TIRED,
	COMMAND_SET_PLAYER_FAST_RELOAD,
	COMMAND_SET_CHAR_BLEEDING,
	todo__comm_510,
	COMMAND_SET_FREE_RESPRAYS,
	COMMAND_SET_CHAR_VISIBLE,
	COMMAND_SET_CAR_VISIBLE,
	COMMAND_IS_AREA_OCCUPIED,
	COMMAND_DISPLAY_TEXT,
	COMMAND_SET_TEXT_SCALE,
	COMMAND_SET_TEXT_COLOUR,
	COMMAND_SET_TEXT_JUSTIFY,
	COMMAND_SET_TEXT_CENTRE,
	COMMAND_SET_TEXT_WRAPX,
	todo__comm_521,
	COMMAND_SET_TEXT_BACKGROUND,
	COMMAND_ROTATE_OBJECT,
	COMMAND_SLIDE_OBJECT,
	COMMAND_REMOVE_CHAR_ELEGANTLY,
	COMMAND_SET_CHAR_STAY_IN_SAME_PLACE,
	COMMAND_UNDRESS_CHAR,
	COMMAND_IS_EXPLOSION_IN_AREA,
	COMMAND_PLACE_OBJECT_RELATIVE_TO_CAR,
	COMMAND_MAKE_OBJECT_TARGETTABLE,
	COMMAND_ADD_ARMOUR_TO_CHAR,
	COMMAND_OPEN_GARAGE,
	COMMAND_CLOSE_GARAGE,
	COMMAND_WARP_CHAR_FROM_CAR_TO_COORD,
	COMMAND_SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE,
	COMMAND_HAS_CHAR_SPOTTED_CHAR,
	COMMAND_SET_CHAR_OBJ_HAIL_TAXI,
	COMMAND_HAS_OBJECT_BEEN_DAMAGED,
	COMMAND_START_KILL_FRENZY_HEADSHOT,
	COMMAND_WARP_CHAR_INTO_CAR,
	COMMAND_SWITCH_CAR_RADIO,
	COMMAND_PRINT_WITH_2_NUMBERS_BIG,
	COMMAND_PRINT_WITH_3_NUMBERS_BIG,
	COMMAND_SET_CHAR_WAIT_STATE,
	COMMAND_SET_CAMERA_BEHIND_PLAYER,
	COMMAND_CREATE_RANDOM_CHAR,
	COMMAND_IS_SNIPER_BULLET_IN_AREA,
	COMMAND_SET_OBJECT_VELOCITY,
	COMMAND_SET_OBJECT_COLLISION,
	COMMAND_PRINT_STRING_IN_STRING_NOW,
	COMMAND_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY,
	COMMAND_LOAD_ALL_MODELS_NOW,
	COMMAND_ADD_TO_OBJECT_VELOCITY,
	COMMAND_SET_OBJECT_DYNAMIC,
	COMMAND_PLAY_MISSION_PASSED_TUNE,
	COMMAND_CLEAR_AREA,
	COMMAND_FREEZE_ONSCREEN_TIMER,
	COMMAND_SWITCH_CAR_SIREN,
	COMMAND_SWITCH_PED_ROADS_OFF_ANGLED,
	COMMAND_SET_CAR_WATERTIGHT,
	COMMAND_ADD_MOVING_PARTICLE_EFFECT,
	COMMAND_SET_CHAR_CANT_BE_DRAGGED_OUT,
	COMMAND_TURN_CAR_TO_FACE_COORD,
	COMMAND_IS_CRANE_LIFTING_CAR,
	COMMAND_DRAW_SPHERE,
	COMMAND_SET_CAR_STATUS,
	COMMAND_IS_CHAR_MALE,
	COMMAND_SCRIPT_NAME,
	COMMAND_SAVE_INT_TO_DEBUG_FILE,
	COMMAND_SAVE_FLOAT_TO_DEBUG_FILE,
	COMMAND_SAVE_NEWLINE_TO_DEBUG_FILE,
	COMMAND_POLICE_RADIO_MESSAGE,
	COMMAND_SET_CAR_STRONG,
	COMMAND_REMOVE_ROUTE,
	COMMAND_SWITCH_RUBBISH,
	COMMAND_REMOVE_PARTICLE_EFFECTS_IN_AREA,
	COMMAND_SWITCH_STREAMING,
	COMMAND_IS_GARAGE_OPEN,
	COMMAND_IS_GARAGE_CLOSED,
	COMMAND_SWAP_NEAREST_BUILDING_MODEL,
	COMMAND_SWITCH_WORLD_PROCESSING,
	COMMAND_CLEAR_AREA_OF_CARS,
	COMMAND_SET_ROTATING_GARAGE_DOOR,
	COMMAND_ADD_SPHERE,
	COMMAND_REMOVE_SPHERE,
	COMMAND_SET_EVERYONE_IGNORE_PLAYER,
	COMMAND_STORE_CAR_CHAR_IS_IN_NO_SAVE,
	COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_STRING,
	COMMAND_DISPLAY_ONSCREEN_COUNTER_WITH_STRING,
	COMMAND_CREATE_RANDOM_CAR_FOR_CAR_PARK,
	COMMAND_SET_WANTED_MULTIPLIER,
	COMMAND_SET_CAMERA_IN_FRONT_OF_PLAYER,
	COMMAND_IS_CAR_VISIBLY_DAMAGED,
	COMMAND_DOES_OBJECT_EXIST,
	COMMAND_LOAD_SCENE,
	COMMAND_ADD_STUCK_CAR_CHECK,
	COMMAND_REMOVE_STUCK_CAR_CHECK,
	COMMAND_IS_CAR_STUCK,
	COMMAND_LOAD_MISSION_AUDIO,
	COMMAND_HAS_MISSION_AUDIO_LOADED,
	todo__comm_601,
	COMMAND_HAS_MISSION_AUDIO_FINISHED,
	COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING,
	COMMAND_HAS_IMPORT_GARAGE_SLOT_BEEN_FILLED,
	COMMAND_CLEAR_THIS_PRINT,
	COMMAND_CLEAR_THIS_BIG_PRINT,
	COMMAND_SET_MISSION_AUDIO_POSITION,
	COMMAND_ACTIVATE_SAVE_MENU,
	COMMAND_HAS_SAVE_GAME_FINISHED,
	COMMAND_NO_SPECIAL_CAMERA_FOR_THIS_GARAGE,
	COMMAND_ADD_BLIP_FOR_PICKUP,
	COMMAND_SET_PED_DENSITY_MULTIPLIER,
	COMMAND_FORCE_RANDOM_PED_TYPE,
	COMMAND_SET_TEXT_RIGHT_JUSTIFY,
	COMMAND_PRINT_HELP,
	COMMAND_CLEAR_HELP,
	COMMAND_FLASH_HUD_OBJECT,
	COMMAND_IS_CHAR_IN_CONTROL,
	COMMAND_SET_GENERATE_CARS_AROUND_CAMERA,
	COMMAND_CLEAR_SMALL_PRINTS,
	COMMAND_SET_UPSIDEDOWN_CAR_NOT_DAMAGED,
	COMMAND_CAN_PLAYER_START_MISSION,
	COMMAND_MAKE_PLAYER_SAFE_FOR_CUTSCENE,
	COMMAND_USE_TEXT_COMMANDS,
	COMMAND_SET_THREAT_FOR_PED_TYPE,
	COMMAND_CLEAR_THREAT_FOR_PED_TYPE,
	COMMAND_GET_CAR_COLOURS,
	COMMAND_SET_ALL_CARS_CAN_BE_DAMAGED,
	COMMAND_SET_CAR_CAN_BE_DAMAGED,
	COMMAND_SET_CHARS_CHATTING,
	COMMAND_SET_DRUNK_INPUT_DELAY,
	COMMAND_SET_CHAR_MONEY,
	COMMAND_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS,
	COMMAND_REGISTER_LIFE_SAVED,
	COMMAND_REGISTER_CRIMINAL_CAUGHT,
	COMMAND_REGISTER_AMBULANCE_LEVEL,
	COMMAND_REGISTER_FIRE_EXTINGUISHED,
	COMMAND_TURN_PHONE_ON,
	COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS,
	COMMAND_SET_TOTAL_NUMBER_OF_KILL_FRENZIES,
	COMMAND_BLOW_UP_RC_BUGGY,
	COMMAND_IS_FRENCH_GAME,
	COMMAND_IS_GERMAN_GAME,
	COMMAND_CLEAR_MISSION_AUDIO,
	COMMAND_SET_CHAR_USE_PEDNODE_SEEK,
	COMMAND_SET_GET_OUT_OF_JAIL_FREE,
	COMMAND_SET_FREE_HEALTH_CARE,
	todo__comm_648,
	COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL,
	COMMAND_SET_OBJECT_DRAW_LAST,
	todo__comm_651,
	COMMAND_SET_CHAR_SAY,
	COMMAND_SET_NEAR_CLIP,
	COMMAND_SET_RADIO_CHANNEL,
	COMMAND_DOES_GARAGE_CONTAIN_CAR,
	COMMAND_SET_CAR_TRACTION,
	COMMAND_ARE_MEASUREMENTS_IN_METRES,
	COMMAND_CONVERT_METRES_TO_FEET,
	COMMAND_MARK_ROADS_BETWEEN_LEVELS,
	COMMAND_SET_CAR_AVOID_LEVEL_TRANSITIONS,
	COMMAND_CLEAR_AREA_OF_CHARS,
	COMMAND_SET_TOTAL_NUMBER_OF_MISSIONS,
	COMMAND_CONVERT_METRES_TO_FEET_INT,
	COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER,
	COMMAND_IS_CAR_PASSENGER_SEAT_FREE,
	COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT,
	COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL,
	COMMAND_START_CREDITS,
	COMMAND_STOP_CREDITS,
	COMMAND_ARE_CREDITS_FINISHED,
	COMMAND_CREATE_SINGLE_PARTICLE,
	COMMAND_SET_MUSIC_DOES_FADE,
	COMMAND_PLAY_END_OF_GAME_TUNE,
	COMMAND_STOP_END_OF_GAME_TUNE,
	COMMAND_GET_CAR_MODEL,
	COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED,
	COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS,
	COMMAND_IS_CHAR_SITTING_IN_CAR,
	COMMAND_IS_CHAR_SITTING_IN_ANY_CAR,
	COMMAND_IS_CHAR_ON_FOOT,
	COMMAND_LOAD_SPLASH_SCREEN,
	todo__comm_682,
	COMMAND_ENABLE_PLAYER_CONTROL_CAMERA,
	COMMAND_SET_OBJECT_ROTATION,
	COMMAND_GET_DEBUG_CAMERA_COORDINATES,
	todo__comm_686,
	todo__comm_687,
	COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME,
	COMMAND_DISPLAY_TEXT_WITH_NUMBER,
	COMMAND_DISPLAY_TEXT_WITH_2_NUMBERS,
	COMMAND_SET_ALL_OCCUPANTS_OF_CAR_LEAVE_CAR,
	COMMAND_SET_INTERPOLATION_PARAMETERS,
	COMMAND_GET_DEBUG_CAMERA_POINT_AT,
	COMMAND_ATTACH_CHAR_TO_CAR,
	COMMAND_DETACH_CHAR_FROM_CAR,
	todo__comm_696,
	COMMAND_SET_CAR_CHANGE_LANE,
	COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE,
	COMMAND_CLEAR_CAR_LAST_WEAPON_DAMAGE,
	COMMAND_GET_RANDOM_COP_IN_AREA,
	COMMAND_GET_DRIVER_OF_CAR,
	COMMAND_GET_NUMBER_OF_FOLLOWERS,
	COMMAND_GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER,
	COMMAND_GET_CURRENT_CHAR_WEAPON,
	COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D,
	COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D,
	COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D,
	COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D,
	COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D,
	COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D,
	COMMAND_SET_CAR_TEMP_ACTION,
	COMMAND_IS_CHAR_ON_ANY_BIKE,
	COMMAND_CAN_CHAR_SEE_DEAD_CHAR,
	COMMAND_SET_ENTER_CAR_RANGE_MULTIPLIER,
	COMMAND_SET_THREAT_REACTION_RANGE_MULTIPLIER,
	COMMAND_SET_CHAR_CEASE_ATTACK_TIMER,
	COMMAND_GET_REMOTE_CONTROLLED_CAR,
	COMMAND_IS_PC_VERSION,
	COMMAND_IS_MODEL_AVAILABLE,
	COMMAND_SHUT_CHAR_UP,
	COMMAND_SET_ENABLE_RC_DETONATE,
	COMMAND_SET_CAR_RANDOM_ROUTE_SEED,
	todo__comm_723,
	COMMAND_REMOVE_ALL_CHAR_WEAPONS,
	COMMAND_HAS_CHAR_GOT_WEAPON,
	COMMAND_SET_TANK_DETONATE_CARS,
	COMMAND_GET_POSITION_OF_ANALOGUE_STICKS,
	COMMAND_IS_CAR_ON_FIRE,
	COMMAND_IS_CAR_TYRE_BURST,
	COMMAND_HELI_GOTO_COORDS,
	DUPLICATE_COMMAND_731, //ProcessCommand_27_28_29_30_731_
	COMMAND_GET_DEAD_CHAR_PICKUP_COORDS,
	COMMAND_CREATE_PROTECTION_PICKUP,
	todo__comm_734,
	todo__comm_735,
	todo__comm_736,
	COMMAND_IS_CHAR_IN_WATER,
    DUPLICATE_COMMAND_738, //ProcessCommand_4_5_53_54_738_
	DUPLICATE_COMMAND_739, //ProcessCommand_15_16_17_739_740_
	DUPLICATE_COMMAND_740, //ProcessCommand_15_16_17_739_740_
	DUPLICATE_COMMAND_741, //ProcessCommand_21_22_23_741_742_
	DUPLICATE_COMMAND_742, //ProcessCommand_21_22_23_741_742_
	COMMAND_GET_CHAR_WEAPON_IN_SLOT,
	COMMAND_GET_CLOSEST_STRAIGHT_ROAD,
	COMMAND_SET_CAR_FORWARD_SPEED,
	COMMAND_SET_AREA_VISIBLE,
	COMMAND_MARK_CAR_AS_CONVOY_CAR,
	COMMAND_RESET_HAVOC_CAUSED_BY_PLAYER,
	COMMAND_GET_HAVOC_CAUSED_BY_PLAYER,
	COMMAND_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS,
	COMMAND_HAS_CHAR_BEEN_PHOTOGRAPHED,
	COMMAND_SWITCH_SECURITY_CAMERA,
	todo__comm_753,
	COMMAND_SET_HELI_ORIENTATION,
	COMMAND_CLEAR_HELI_ORIENTATION,
	COMMAND_PLANE_GOTO_COORDS,
	COMMAND_GET_NTH_CLOSEST_CAR_NODE,
	COMMAND_GET_NTH_CLOSEST_CHAR_NODE,
	COMMAND_SET_ENABLE_RC_DETONATE_ON_CONTACT,
	COMMAND_FREEZE_CHAR_POSITION,
	COMMAND_SET_CHAR_DROWNS_IN_WATER,
	COMMAND_SET_OBJECT_RECORDS_COLLISIONS,
	COMMAND_HAS_OBJECT_COLLIDED_WITH_ANYTHING,
	COMMAND_REMOVE_RC_BUGGY,
	COMMAND_HAS_PHOTOGRAPH_BEEN_TAKEN,
	COMMAND_GET_CHAR_ARMOUR,
	COMMAND_SET_HELI_STABILISER,
	COMMAND_SET_CAR_STRAIGHT_LINE_DISTANCE,
	COMMAND_POP_CAR_BOOT,
	COMMAND_SET_PLAYER_MOOD,
	COMMAND_REQUEST_COLLISION,
	COMMAND_LOCATE_OBJECT_2D,
	COMMAND_LOCATE_OBJECT_3D,
	COMMAND_IS_OBJECT_IN_WATER,
	COMMAND_IS_OBJECT_IN_AREA_2D,
	COMMAND_IS_OBJECT_IN_AREA_3D,
	COMMAND_SET_CHAR_CROUCH,
	todo__comm_778,
	COMMAND_REQUEST_ANIMATION,
	COMMAND_HAS_ANIMATION_LOADED,
	COMMAND_REMOVE_ANIMATION,
	COMMAND_SET_CHAR_SHUFFLE_INTO_DRIVERS_SEAT,
	COMMAND_ATTACH_CHAR_TO_OBJECT,
	COMMAND_SET_CHAR_AS_PLAYER_FRIEND,
	COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING,
	COMMAND_ADD_SET_PIECE,
	COMMAND_SET_EXTRA_COLOURS,
	COMMAND_CLEAR_EXTRA_COLOURS,
	COMMAND_GET_WHEELIE_STATS,
	COMMAND_BURST_CAR_TYRE,
	COMMAND_IS_CHAR_OBJ_NO_OBJ,
	COMMAND_IS_PLAYER_WEARING,
	COMMAND_SET_PLAYER_CAN_DO_DRIVE_BY,
	COMMAND_CREATE_SWAT_ROPE,
	COMMAND_SET_CAR_MODEL_COMPONENTS,
	COMMAND_CLOSE_ALL_CAR_DOORS,
	COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D,
	COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D,
	COMMAND_POP_CAR_BOOT_USING_PHYSICS,
	COMMAND_IS_CHAR_LEAVING_VEHICLE_TO_DIE,
	COMMAND_SORT_OUT_OBJECT_COLLISION_WITH_CAR,
	COMMAND_IS_CHAR_WANDER_PATH_CLEAR,
	COMMAND_PRINT_HELP_FOREVER,
	COMMAND_SET_CHAR_CAN_BE_DAMAGED_BY_MEMBERS_OF_GANG,
	COMMAND_FREEZE_CAR_POSITION,
	COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CHAR,
	COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CAR,
	COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CHAR,
	COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CAR,
	COMMAND_GET_RADIO_CHANNEL,
	COMMAND_IS_CHAR_DROWNING_IN_WATER,
	COMMAND_HAS_GLASS_BEEN_SHATTERED_NEARBY,
	COMMAND_SET_CHAR_STAY_IN_CAR_WHEN_JACKED,
	COMMAND_ADD_MONEY_SPENT_ON_WEAPONS,
	COMMAND_SET_CHAR_ANSWERING_MOBILE,
	COMMAND_SET_PLAYER_DRUNKENNESS,
	COMMAND_SET_CHAR_IN_PLAYERS_GROUP_CAN_FIGHT,
	COMMAND_CLEAR_CHAR_WAIT_STATE,
	COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE,
	COMMAND_SET_CAN_BURST_CAR_TYRES,
	COMMAND_FIRE_HUNTER_GUN,
	todo__comm_822,
	COMMAND_CHECK_FOR_PED_MODEL_AROUND_PLAYER,
	COMMAND_CLEAR_CHAR_FOLLOW_PATH,
	COMMAND_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE,
	COMMAND_LOAD_MISSION_TEXT,
	COMMAND_CLEAR_CHAR_LAST_DAMAGE_ENTITY,
	COMMAND_CLEAR_CAR_LAST_DAMAGE_ENTITY,
	COMMAND_FREEZE_OBJECT_POSITION,
	COMMAND_SET_UP_TAXI_SHORTCUT,
	COMMAND_CLEAR_TAXI_SHORTCUT,
	COMMAND_INCREASE_PLAYER_MAX_HEALTH,
	COMMAND_INCREASE_PLAYER_MAX_ARMOUR,
	COMMAND_CREATE_RANDOM_CHAR_AS_DRIVER,
	COMMAND_CREATE_RANDOM_CHAR_AS_PASSENGER,
	COMMAND_SET_CHAR_IGNORE_THREATS_BEHIND_OBJECTS,
	COMMAND_MAKE_HELI_COME_CRASHING_DOWN,
	COMMAND_SET_OBJECT_AREA_VISIBLE,
	COMMAND_SET_CHAR_NEVER_TARGETTED,
	COMMAND_SET_CHAR_CROUCH_WHEN_THREATENED,
	COMMAND_IS_CHAR_IN_ANY_POLICE_VEHICLE,
	COMMAND_DOES_CHAR_EXIST,
	COMMAND_DOES_VEHICLE_EXIST,
	COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_CONTACT_POINT,
	COMMAND_IS_CHAR_STUCK,
	COMMAND_SET_ALL_TAXIS_HAVE_NITRO,
	COMMAND_SET_CHAR_STOP_SHOOT_DONT_SEEK_ENTITY,
	COMMAND_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION,
	COMMAND_REGISTER_VIGILANTE_LEVEL,
	COMMAND_CLEAR_ALL_CHAR_ANIMS,
	COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE,
	COMMAND_WANTED_STARS_ARE_FLASHING,
	COMMAND_SET_ALLOW_HURRICANES,
	COMMAND_PLAY_ANNOUNCEMENT,
	COMMAND_SET_PLAYER_IS_IN_STADIUM,
	COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER,
	COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM,
	COMMAND_DISPLAY_RADAR,
	COMMAND_IS_PLAYER_IN_INFO_ZONE,
	COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE,
	COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR,
	COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG,
	COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG,
	COMMAND_ADD_BIG_GUN_FLASH,
	COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM,
	COMMAND_GET_PROGRESS_PERCENTAGE,
	COMMAND_SET_SHORTCUT_PICKUP_POINT,
	COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION,
	COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA,
	COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA,
	COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS,
	COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR,
	COMMAND_SET_VEHICLE_TO_FADE_IN,
	COMMAND_REGISTER_ODDJOB_MISSION_PASSED,
	COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI,
	COMMAND_IS_CHAR_DUCKING,
	COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI,
	COMMAND_REGISTER_FIRE_LEVEL,
	COMMAND_IS_AUSTRALIAN_GAME,
	COMMAND_DISARM_CAR_BOMB,
	COMMAND_IS_JAPANESE_GAME,
	COMMAND_DOT_PRODUCT_2D,
	COMMAND_DOT_PRODUCT_3D,
	COMMAND_DEBUG_PRINT_WITH_1_FLOAT,
	COMMAND_DEBUG_PRINT_WITH_2_FLOATS,
	COMMAND_DEBUG_PRINT_WITH_3_FLOATS,
	COMMAND_GET_PAD_BUTTON_STATE,
	COMMAND_SET_NAVIGATION_ARROW,
	COMMAND_CLEAR_NAVIGATION_ARROW,
    COMMAND_CALLNOT, // lcs swap call callnot, lcs call 0x8, callnot 0xC, vcs 0x8 is 891 so is call
	COMMAND_CALL,
	COMMAND_IS_CAR_AUTOMOBILE,
	COMMAND_IS_CAR_BIKE,
	COMMAND_IS_CAR_PLANE,
	COMMAND_IS_CAR_HELI,
		COMMAND_NULL_896,
		COMMAND_NULL_897,
		COMMAND_NULL_898,
		COMMAND_NULL_899,
		COMMAND_NULL_900,
		COMMAND_NULL_901,
		COMMAND_NULL_902,
		COMMAND_NULL_903,
		COMMAND_NULL_904,
		COMMAND_NULL_905,
		COMMAND_NULL_906,
		COMMAND_NULL_907,
		COMMAND_NULL_908,
		COMMAND_NULL_909,
		COMMAND_NULL_910,
		COMMAND_NULL_911,
       LCSWRONG_COMMAND_1476,
	COMMAND_RETURN_IF_TRUE,
	COMMAND_RETURN_TRUE_IF_TRUE,
	COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_BEHIND,
	COMMAND_SET_RC_HELI_HEIGHT_LIMIT,
	COMMAND_CREATE_SCRIPT_CORONA,
	COMMAND_REMOVE_SCRIPT_CORONA,
	COMMAND_IS_BOAT_IN_WATER,
	COMMAND_IS_CAR_DRIVER_BEING_JACKED,
	COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_IN_FRONT,
	COMMAND_SET_CAR_TILTED_BY_CHAR,
	COMMAND_GET_WEAPON_TYPE_FOR_PICKUP_IN_AREA,
	todo__comm_924,
	   LCSWRONG_COMMAND_1489,
       LCSWRONG_COMMAND_1490,
	todo__comm_927,
	COMMAND_SET_DEBUG_MENU_ACTIVE,
	COMMAND_SET_DRAW_HUD,
	COMMAND_GET_RANDOM_CHAR_IN_AREA_NO_CHECKS,
	COMMAND_GET_RANDOM_CAR_IN_AREA_NO_CHECKS_NO_SAVE,
	COMMAND_STORE_CAR_COLLIDED_WITH_NO_SAVE,
	COMMAND_SET_CHAR_DROPS_WEAPONS_ON_DEATH,
	COMMAND_IS_CHAR_CROUCHING,
	COMMAND_OVERRIDE_CAR_REMOTE_CONTROL,
	COMMAND_CANCEL_REMOTE_MODE,
	COMMAND_SET_OBJECT_TURN_SPEED,
	COMMAND_SET_OBJECT_MASS,
	COMMAND_HAS_CUTSCENE_LOADED,
	COMMAND_SET_UNIQUE_JUMPS_FOUND,
	todo__comm_941,
	COMMAND_SET_CHAR_DIVE_FROM_CAR,
	COMMAND_WRECK_CAR,
	COMMAND_REGISTER_OUTFIT_CHANGE,
	COMMAND_HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON,
	COMMAND_CLEAR_OBJECT_LAST_WEAPON_DAMAGE,
	COMMAND_SET_CAR_TURN_SPEED,
	COMMAND_SET_CAR_MOVE_SPEED,
	COMMAND_SET_OBJECT_PROOFS,
	COMMAND_GET_CAMERA_PED_ZOOM_INDICATOR,
	COMMAND_SET_CAMERA_PED_ZOOM_INDICATOR,
	COMMAND_GET_CAR_ORIENTATION,
	COMMAND_SET_CAR_ORIENTATION,
	COMMAND_IS_DEBUG_MENU_ON,
	COMMAND_OPEN_VAN_BACK_DOORS,
	COMMAND_GET_CHAR_THREAT_CHAR,
	COMMAND_FREEZE_PED_ZOOM_SWITCH,
	COMMAND_SET_OBJECT_RENDERED_DAMAGED,
	COMMAND_GET_RANDOM_CAR_IN_AREA_NO_SAVE,
	COMMAND_IS_PLAYER_MADE_SAFE,
	COMMAND_IS_E3_BUILD,
	COMMAND_CLEAR_BIG_MESSAGES,
	COMMAND_CLEAR_AREA_OF_OBJECTS,
	COMMAND_LOAD_NON_STANDARD_PED_ANIM,
	COMMAND_UNLOAD_NON_STANDARD_PED_ANIM,
	COMMAND_BUILD_WORLD_GEOMETRY,
	COMMAND_STORE_BUILDING_SWAP,
	COMMAND_IS_MULTIPLAYER_ACTIVE,
	COMMAND_GET_MULTIPLAYER_MODE,
	COMMAND_MULTIPLAYER_SCRIPT_DONE,
	COMMAND_IS_MULTIPLAYER_SERVER,
	COMMAND_IS_MULTIPLAYER_TEAM_GAME,
	COMMAND_GET_MULTIPLAYER_TEAM_ID,
	COMMAND_DOES_SHORTCUT_TAXI_EXIST,
	COMMAND_SET_ONSCREEN_TIMER_COLOUR,
	COMMAND_SET_ONSCREEN_TIMER_BACKGROUND_COLOUR,
	COMMAND_REMOVE_CAR_BOOT,
	COMMAND_ADD_POINT_3D_MARKER,
	COMMAND_PRINT_HELP_ALWAYS,
	COMMAND_PRINT_HELP_FOREVER_ALWAYS,
	COMMAND_SET_CHAR_MAX_HEALTH,
	COMMAND_SET_CHAR_SHOOT_TIMER,
	COMMAND_SET_CHAR_ATTACK_TIMER,
	COMMAND_SET_HELI_ROTOR_BLADES_FULLSPEED,
	COMMAND_SET_CRUSHER_REWARD_MULTIPLIER,
	COMMAND_SWAP_BUILDINGS,
	COMMAND_STREAM_BUILDING_SWAPS,
	COMMAND_IS_WORLD_STREAMING_COMPLETE,
	COMMAND_SWAP_TO_STREAMED_SECTOR,
	COMMAND_SET_CHAR_ATTACKS_PLAYER_WITH_COPS,
	COMMAND_REGISTER_FACE_PLANT_DISTANCE,
	COMMAND_ADD_EXPORTED_CARS,
	COMMAND_SET_TOTAL_EXPORT_CARS,
	COMMAND_ADD_ARROW_3D_MARKER,
	todo__comm_995,
	todo__comm_996,
	COMMAND_IS_DEVELOPER,
	COMMAND_SET_DEVELOPER_FLAG,
	COMMAND_ATTACH_OBJECT_TO_CAR,
	COMMAND_DETACH_OBJECT_FROM_CAR,
	COMMAND_SET_PAD_STICKS_MULTIPLIER,
	COMMAND_PRINT_SUBTITLE_NOW,
	COMMAND_PRINT_SUBTITLE_NOW_OVERRIDE_FADE,
	COMMAND_PRINT_SUBTITLE_NOW_NO_BRIEF,
	COMMAND_PRINT_WITH_NUMBER_NOW_NO_BRIEF,
	COMMAND_GET_ANGLE_BETWEEN_POINTS,
	COMMAND_OVERRIDE_CHAR_MOVE_ANIM,
       LCSWRONG_COMMAND_1627,
	COMMAND_ENABLE_EMERGENCY_VEHICLES,
	COMMAND_ADD_UNLOCKED_COSTUME,
	COMMAND_CLEAR_MULTIPLAYER_SPLASH_SCREEN,
	COMMAND_PRINT_WITH_2_NUMBERS_NOW_NO_BRIEF,
	COMMAND_GET_OBJECT_ORIENTATION,
	COMMAND_SET_OBJECT_ORIENTATION,
	COMMAND_CHANGE_ONSCREEN_COUNTER_PREFIX,
	COMMAND_STORE_PLAYER_OUTFIT,
	COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_STRING,
	COMMAND_SET_PLAYER_CURRENT_WEAPON_AMMO_IN_CLIP,
	COMMAND_SET_CHAR_WAIT_STATE_REPEAT,
	COMMAND_LOCK_GARAGE,
	COMMAND_IS_FINAL_GAME,
	COMMAND_SET_ALLOWED_COLLISION,
	COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_2_STRINGS,
	COMMAND_GET_PLAYER_STORED_WEAPON,
	COMMAND_DISABLE_PAUSE_MENU,
	COMMAND_IS_CHANNEL_PLAYING,
	COMMAND_SET_CLOCK_EVENT_WARNING,
	COMMAND_SET_EXTRA_COLOUR_LIGHT_DIRECTION,
	todo__comm_1029,
	COMMAND_PRINT_HELP_NO_BRIEF,
	COMMAND_PRINT_HELP_FOREVER_NO_BRIEF,
	COMMAND_PRINT_HELP_ALWAYS_NO_BRIEF,
	COMMAND_PRINT_HELP_FOREVER_ALWAYS_NO_BRIEF,
	COMMAND_SET_CAR_IS_REWARD,
	todo__comm_1035,
	todo__comm_1036,
	todo__comm_1037,
	todo__comm_1038,
	todo__comm_1039,
	todo__comm_1040,
	todo__comm_1041,
	todo__comm_1042,
	todo__comm_1043,
	todo__comm_1044,
	todo__comm_1045,
	todo__comm_1046,
	todo__comm_1047,
	todo__comm_1048,
	todo__comm_1049,
	todo__comm_1050,
	todo__comm_1051,
	todo__comm_1052,
	todo__comm_1053,
	todo__comm_1054,
	todo__comm_1055,
	todo__comm_1056,
	todo__comm_1057,
	todo__comm_1058,
	todo__comm_1059,
	todo__comm_1060,
	todo__comm_1061,
	todo__comm_1062,
	todo__comm_1063,
	todo__comm_1064,
	todo__comm_1065,
	todo__comm_1066,
	todo__comm_1067,
	todo__comm_1068,
	todo__comm_1069,
	todo__comm_1070,
	todo__comm_1071,
	todo__comm_1072,
	todo__comm_1073,
	todo__comm_1074,
	todo__comm_1075,
	todo__comm_1076,
	todo__comm_1077,
	todo__comm_1078,
	todo__comm_1079,
	todo__comm_1080,
	todo__comm_1081,
	todo__comm_1082,
	todo__comm_1083,
	todo__comm_1084,
	todo__comm_1085,
	todo__comm_1086,
	todo__comm_1087,
	todo__comm_1088,
	todo__comm_1089,
	todo__comm_1090,
	todo__comm_1091,
	todo__comm_1092,
	todo__comm_1093,
	todo__comm_1094,
	todo__comm_1095,
	todo__comm_1096,
	todo__comm_1097,
	todo__comm_1098,
	todo__comm_1099,
	todo__comm_1100,
	todo__comm_1101,
	todo__comm_1102,
	todo__comm_1103,
	todo__comm_1104,
	todo__comm_1105,
	todo__comm_1106,
	todo__comm_1107,
	todo__comm_1108,
	todo__comm_1109,
	todo__comm_1110,
	todo__comm_1111,
	todo__comm_1112,
	todo__comm_1113,
	todo__comm_1114,
	todo__comm_1115,
	todo__comm_1116,
	todo__comm_1117,
	todo__comm_1118,
	todo__comm_1119,
	todo__comm_1120,
	todo__comm_1121,
	todo__comm_1122,
	todo__comm_1123,
	todo__comm_1124,
	todo__comm_1125,
	todo__comm_1126,
	todo__comm_1127,
	todo__comm_1128,
	todo__comm_1129,
	todo__comm_1130,
	todo__comm_1131,
	todo__comm_1132,
	todo__comm_1133,
	todo__comm_1134,
	todo__comm_1135,
	todo__comm_1136,
	todo__comm_1137,
	todo__comm_1138,
	todo__comm_1139,
	todo__comm_1140,
	todo__comm_1141,
	todo__comm_1142,
	todo__comm_1143,
	todo__comm_1144,
	todo__comm_1145,
	todo__comm_1146,
	todo__comm_1147,
	todo__comm_1148,
	todo__comm_1149,
	todo__comm_1150,
	todo__comm_1151,
	todo__comm_1152,
	todo__comm_1153,
	todo__comm_1154,
	todo__comm_1155,
	todo__comm_1156,
	todo__comm_1157,
	todo__comm_1158,
	todo__comm_1159,
	todo__comm_1160,
	todo__comm_1161,
	todo__comm_1162,
	todo__comm_1163,
	todo__comm_1164,
	todo__comm_1165,
	todo__comm_1166,
	todo__comm_1167,
	todo__comm_1168,
	todo__comm_1169,
	todo__comm_1170,
	todo__comm_1171,
	todo__comm_1172,
	todo__comm_1173,
	todo__comm_1174,
	todo__comm_1175,
	todo__comm_1176,
	todo__comm_1177,
	todo__comm_1178,
	todo__comm_1179,
	todo__comm_1180,
	todo__comm_1181,
	todo__comm_1182,
	todo__comm_1183,
	todo__comm_1184,
	todo__comm_1185,
	todo__comm_1186,
	todo__comm_1187,
	todo__comm_1188,
	todo__comm_1189,
	todo__comm_1190,
	todo__comm_1191,
	todo__comm_1192,
	todo__comm_1193,
	todo__comm_1194,
	todo__comm_1195,
	todo__comm_1196,
	todo__comm_1197,
	todo__comm_1198,
	todo__comm_1199,
	todo__comm_1200,
	todo__comm_1201,
	todo__comm_1202,
	todo__comm_1203,
	todo__comm_1204,
	todo__comm_1205,
	todo__comm_1206,
	todo__comm_1207,
	todo__comm_1208,
	todo__comm_1209,
	todo__comm_1210,
	todo__comm_1211,
	todo__comm_1212,
	todo__comm_1213,
	todo__comm_1214,
	todo__comm_1215,
	todo__comm_1216,
	todo__comm_1217,
	todo__comm_1218,
	todo__comm_1219,
	todo__comm_1220,
	todo__comm_1221,
	todo__comm_1222,
	todo__comm_1223,
	todo__comm_1224,
	todo__comm_1225,
	todo__comm_1226,
	todo__comm_1227,
	todo__comm_1228,
	todo__comm_1229,
	todo__comm_1230,
	todo__comm_1231,
	todo__comm_1232,
	todo__comm_1233,
	todo__comm_1234,
	todo__comm_1235,
	todo__comm_1236,
	todo__comm_1237,
	todo__comm_1238,
	todo__comm_1239,
	todo__comm_1240,
	todo__comm_1241,
	todo__comm_1242,
	todo__comm_1243,
	todo__comm_1244,
	todo__comm_1245,
	todo__comm_1246,
	todo__comm_1247,
	todo__comm_1248,
	todo__comm_1249,
	todo__comm_1250,
	todo__comm_1251,
	todo__comm_1252,
	todo__comm_1253,
	todo__comm_1254,
	todo__comm_1255,
	todo__comm_1256,
	todo__comm_1257,
	todo__comm_1258,
	todo__comm_1259,
	todo__comm_1260,
	todo__comm_1261,
	todo__comm_1262,
	todo__comm_1263,
	todo__comm_1264,
	todo__comm_1265,
	todo__comm_1266,
	todo__comm_1267,
	todo__comm_1268,
	todo__comm_1269,
	todo__comm_1270,
	todo__comm_1271,
	todo__comm_1272,
	todo__comm_1273,
	todo__comm_1274,
	todo__comm_1275,
	todo__comm_1276,
	todo__comm_1277,
	todo__comm_1278,
	todo__comm_1279,
	todo__comm_1280,
	todo__comm_1281,
	todo__comm_1282,
	todo__comm_1283,
	todo__comm_1284,
	todo__comm_1285,
	todo__comm_1286,
	todo__comm_1287,
	todo__comm_1288,
	todo__comm_1289,
	todo__comm_1290,
	todo__comm_1291,
	todo__comm_1292,
	todo__comm_1293,
	todo__comm_1294,
	todo__comm_1295,
	todo__comm_1296,
	todo__comm_1297,
	todo__comm_1298,
	todo__comm_1299,
	todo__comm_1300,
	todo__comm_1301,
	todo__comm_1302,
	todo__comm_1303,
	todo__comm_1304,
	todo__comm_1305,
	todo__comm_1306,
	todo__comm_1307,
	todo__comm_1308,
	todo__comm_1309,
	todo__comm_1310,
	todo__comm_1311,
	todo__comm_1312,
	todo__comm_1313,
	todo__comm_1314,
	todo__comm_1315,
	todo__comm_1316,
	todo__comm_1317,
	todo__comm_1318,
	todo__comm_1319,
	todo__comm_1320,
	todo__comm_1321,
	todo__comm_1322,
	todo__comm_1323,
	todo__comm_1324,
	todo__comm_1325,
	todo__comm_1326,
	todo__comm_1327,
	todo__comm_1328,
	todo__comm_1329,
	todo__comm_1330,
	todo__comm_1331,
	todo__comm_1332,
	todo__comm_1333,
	todo__comm_1334,
	todo__comm_1335,
	todo__comm_1336,
	todo__comm_1337,
	todo__comm_1338,
	todo__comm_1339,
	todo__comm_1340,
	todo__comm_1341,
	todo__comm_1342,
	todo__comm_1343,
	todo__comm_1344,
	todo__comm_1345,
	todo__comm_1346,
	todo__comm_1347,
	todo__comm_1348,
	todo__comm_1349,
	todo__comm_1350,
	todo__comm_1351,
	todo__comm_1352,
	todo__comm_1353,
	todo__comm_1354,
	todo__comm_1355,
	todo__comm_1356,
	todo__comm_1357,
	todo__comm_1358,
	todo__comm_1359,
	todo__comm_1360,
	todo__comm_1361,
	todo__comm_1362,
	todo__comm_1363,
	todo__comm_1364,
	todo__comm_1365,
	todo__comm_1366,
	todo__comm_1367,
	todo__comm_1368,
	todo__comm_1369,
	todo__comm_1370,
	todo__comm_1371,
	todo__comm_1372,
	todo__comm_1373,
	todo__comm_1374,
	todo__comm_1375,
	todo__comm_1376,
	todo__comm_1377,
	todo__comm_1378,
	todo__comm_1379,
	todo__comm_1380,

	// old lcs ops //---------------------------------------------------------------------------


#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
	LAST_SCRIPT_COMMAND
#endif
};

#ifdef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT

enum eScriptArgument
{
	ARGTYPE_NONE = 0,
	ARGTYPE_INT,
	ARGTYPE_FLOAT,
	ARGTYPE_STRING,
	ARGTYPE_LABEL,
	ARGTYPE_BOOL,
	ARGTYPE_PED_HANDLE,
	ARGTYPE_VEHICLE_HANDLE,
	ARGTYPE_OBJECT_HANDLE,
	ARGTYPE_ANDOR,
	ARGTYPE_LIST,
	ARGTYPE_FUNCTION
};

struct tScriptCommandData
{
	int id;
	const char name[64];
	eScriptArgument input[18];
	eScriptArgument output[18];
	bool cond;
	int position;
	const char name_override[8];
};
#endif