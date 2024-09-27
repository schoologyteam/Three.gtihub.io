#include "TimecycleDebuger.h"

#include "common.h"
#include "TimeCycle.h"

namespace PLG_TD
{

float fDebug1_val = 0.0f;
float fDebug2_val = 0.0f;
float fDebug3_val = 0.0f;
float fDebug4_val = 0.0f;
float fDebug5_val = 0.0f;
float fDebug6_val = 0.0f;
float fDebug7_val = 0.0f;
float fDebug8_val = 0.0f;
float fDebug9_val = 0.0f;
float fDebug10_val = 0.0f;

int iDebug1_val = 0;
int iDebug2_val = 0;
int iDebug3_val = 0;
int iDebug4_val = 0;
int iDebug5_val = 0;
int iDebug6_val = 0;
int iDebug7_val = 0;
int iDebug8_val = 0;
int iDebug9_val = 0;
int iDebug10_val = 0;

void
Debug1(float val)
{
}




void
test()
{
	CTimeCycle::m_nCurrentSkyTopRed = 0;
	CTimeCycle::m_nCurrentSkyTopGreen = 0;
	CTimeCycle::m_nCurrentSkyTopBlue = 0;

	CTimeCycle::m_nCurrentSkyBottomRed = 0;
	CTimeCycle::m_nCurrentSkyBottomGreen = 0;
	CTimeCycle::m_nCurrentSkyBottomBlue = 0;

	CTimeCycle::m_nCurrentSunCoreRed = 0;
	CTimeCycle::m_nCurrentSunCoreGreen = 0;
	CTimeCycle::m_nCurrentSunCoreBlue = 0;

	CTimeCycle::m_nCurrentSunCoronaRed = 0;
	CTimeCycle::m_nCurrentSunCoronaGreen = 0;
	CTimeCycle::m_nCurrentSunCoronaBlue = 0;

	CTimeCycle::m_fCurrentSunSize = 0;

	CTimeCycle::m_nCurrentLowCloudsRed = 0;
	CTimeCycle::m_nCurrentLowCloudsGreen = 0;
	CTimeCycle::m_nCurrentLowCloudsBlue = 0;

	CTimeCycle::m_nCurrentFluffyCloudsTopRed = 0;
	CTimeCycle::m_nCurrentFluffyCloudsTopGreen = 0;
	CTimeCycle::m_nCurrentFluffyCloudsTopBlue = 0;

	CTimeCycle::m_nCurrentFluffyCloudsBottomRed = 0;
	CTimeCycle::m_nCurrentFluffyCloudsBottomGreen = 0;
	CTimeCycle::m_nCurrentFluffyCloudsBottomBlue = 0;

	CTimeCycle::m_fCurrentWaterRed = 0;
	CTimeCycle::m_fCurrentWaterGreen = 0;
	CTimeCycle::m_fCurrentWaterBlue = 0;
	CTimeCycle::m_fCurrentWaterAlpha = 0;

	CTimeCycle::m_fCurrentAmbientRed = 0;
	CTimeCycle::m_fCurrentAmbientGreen = 0;
	CTimeCycle::m_fCurrentAmbientBlue = 0;

	CTimeCycle::m_fCurrentAmbientRed_Obj = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Obj = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Obj = 0;

	CTimeCycle::m_fCurrentAmbientRed_Bl = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Bl = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Bl = 0;


	CTimeCycle::m_fCurrentAmbientRed_Obj_Bl = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Obj_Bl = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Obj_Bl = 0;

	CTimeCycle::m_fCurrentDirectionalRed = 0;
	CTimeCycle::m_fCurrentDirectionalGreen = 0;
	CTimeCycle::m_fCurrentDirectionalBlue = 0;

	CTimeCycle::m_fCurrentSpriteSize = 0;
	CTimeCycle::m_fCurrentSpriteBrightness = 0;
	CTimeCycle::m_nCurrentShadowStrength = 0;
	CTimeCycle::m_nCurrentLightShadowStrength = 0;
	CTimeCycle::m_nCurrentPoleShadowStrength = 0;
	CTimeCycle::m_fCurrentFarClip = 0;
	CTimeCycle::m_fCurrentFogStart = 0;
	CTimeCycle::m_fCurrentLightsOnGroundBrightness = 0;

	CTimeCycle::m_fCurrentBlurRed = 0;
	CTimeCycle::m_fCurrentBlurGreen = 0;
	CTimeCycle::m_fCurrentBlurBlue = 0;





	//-------------------------------------
	CTimeCycle::m_nCurrentSkyTopRed = 0;
	CTimeCycle::m_nCurrentSkyBottomRed = 0;
	CTimeCycle::m_nCurrentFogColourRed = 0;

	CTimeCycle::m_nCurrentSkyTopGreen = 0;
	CTimeCycle::m_nCurrentSkyBottomGreen = 0;
	CTimeCycle::m_nCurrentFogColourGreen = 0;

	CTimeCycle::m_nCurrentSkyTopBlue = 0;
	CTimeCycle::m_nCurrentSkyBottomBlue = 0;
	CTimeCycle::m_nCurrentFogColourBlue = 0;

	CTimeCycle::m_fCurrentAmbientRed = 0;
	CTimeCycle::m_fCurrentAmbientGreen = 0;
	CTimeCycle::m_fCurrentAmbientBlue = 0;
	CTimeCycle::m_fCurrentAmbientRed_Obj = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Obj = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Obj = 0;
	CTimeCycle::m_fCurrentAmbientRed_Bl = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Bl = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Bl = 0;
	CTimeCycle::m_fCurrentAmbientRed_Obj_Bl = 0;
	CTimeCycle::m_fCurrentAmbientGreen_Obj_Bl = 0;
	CTimeCycle::m_fCurrentAmbientBlue_Obj_Bl = 0;
	CTimeCycle::m_fCurrentDirectionalRed = 0;
	CTimeCycle::m_fCurrentDirectionalGreen = 0;
	CTimeCycle::m_fCurrentDirectionalBlue = 0;
}




//---------------------------
//---------------------------
//---------------------------
//---------------------------
//---------------------------
//---------------------------

void
test2()
{
	{
		float val = fDebug1_val;
		CTimeCycle::m_fCurrentAmbientRed = val;
		CTimeCycle::m_fCurrentAmbientGreen = val;
		CTimeCycle::m_fCurrentAmbientBlue = val;

		CTimeCycle::m_fCurrentAmbientRed_Obj = val;
		CTimeCycle::m_fCurrentAmbientGreen_Obj = val;
		CTimeCycle::m_fCurrentAmbientBlue_Obj = val;

		CTimeCycle::m_fCurrentAmbientRed_Bl = val;
		CTimeCycle::m_fCurrentAmbientGreen_Bl = val;
		CTimeCycle::m_fCurrentAmbientBlue_Bl = val;
	}

	do
	{
		float val1 = iDebug1_val;
		float val2 = iDebug2_val;
		float val3 = iDebug3_val;
		CTimeCycle::m_nCurrentSkyTopRed = val1;
		CTimeCycle::m_nCurrentSkyBottomRed = val1;
		CTimeCycle::m_nCurrentFogColourRed = val1;

		CTimeCycle::m_nCurrentSkyTopGreen = val2;
		CTimeCycle::m_nCurrentSkyBottomGreen = val2;
		CTimeCycle::m_nCurrentFogColourGreen = val2;

		CTimeCycle::m_nCurrentSkyTopBlue = val3;
		CTimeCycle::m_nCurrentSkyBottomBlue = val3;
		CTimeCycle::m_nCurrentFogColourBlue = val3;
		break;
		CTimeCycle::m_fCurrentAmbientRed = 0;
		CTimeCycle::m_fCurrentAmbientGreen = 0;
		CTimeCycle::m_fCurrentAmbientBlue = 0;
		CTimeCycle::m_fCurrentAmbientRed_Obj = 0;
		CTimeCycle::m_fCurrentAmbientGreen_Obj = 0;
		CTimeCycle::m_fCurrentAmbientBlue_Obj = 0;
		CTimeCycle::m_fCurrentAmbientRed_Bl = 0;
		CTimeCycle::m_fCurrentAmbientGreen_Bl = 0;
		CTimeCycle::m_fCurrentAmbientBlue_Bl = 0;
		CTimeCycle::m_fCurrentAmbientRed_Obj_Bl = 0;
		CTimeCycle::m_fCurrentAmbientGreen_Obj_Bl = 0;
		CTimeCycle::m_fCurrentAmbientBlue_Obj_Bl = 0;
		CTimeCycle::m_fCurrentDirectionalRed = 0;
		CTimeCycle::m_fCurrentDirectionalGreen = 0;
		CTimeCycle::m_fCurrentDirectionalBlue = 0;
	} while(0);

}





void
PLG_OnDraw()
{
	//test();
	//test2();
}

} // namespace PLG_TD