#pragma once
#include "common.h"

class CFerrisWheel // todo maybe CFerrisWheels.process -> CFerrisWheel.Update
{
	//static uint32 keyTable[256];
public:
	static void Init(); // 1755E0 delegate check todo if need
	static void Update();
	static void Shutdown();
	// ops 1223 1224 1225 1226
};