#ifndef _NAME_MANAGER_
#define _NAME_MANAGER_

#include <string>
using namespace std;


#define CREATE_VALUE(NAME) static const string NAME = #NAME;
#define CREATE_VALUE_WITH_VALUE(NAME, VALUE) static const string NAME = VALUE;


namespace NAME_MANAGER
{
//-------------------------------------------------
//Theatre
//-------------------------------------------------

///////////////////////////////////////
// Scenes
//////////////////////////////////////
	CREATE_VALUE(S_Open);
	CREATE_VALUE(S_Gate);
	CREATE_VALUE(S_MainScenes);
	CREATE_VALUE(S_GreenBuilding)
	CREATE_VALUE(S_Milestone);
	CREATE_VALUE(S_Product);
	CREATE_VALUE(S_TakePicture);

///////////////////////////////////////
// Actor
//////////////////////////////////////

	CREATE_VALUE(A_SwingHandTipsVideo);
	CREATE_VALUE(A_DoorImageBG);
	CREATE_VALUE(A_MainScenesBG);
	CREATE_VALUE(A_MainScenesGlass);
	CREATE_VALUE(A_OpenTipsVideo);
	CREATE_VALUE(A_DoorOpenVideo);	
	CREATE_VALUE(A_GreenBuildingTips);
	CREATE_VALUE(A_GreenBuildingLight);
	CREATE_VALUE(A_GreenBuildingZoomIn);
	CREATE_VALUE(A_GreenBuildingShowBuidling);
	CREATE_VALUE(A_MilestoneTips);
	CREATE_VALUE(A_MilestoneBlackGlass);
	CREATE_VALUE(A_MilestoneCountdown);
	CREATE_VALUE(A_MilestoneZoomIn);
	CREATE_VALUE(A_MilestoneVideoLoop);
	CREATE_VALUE(A_MilestoneNearBG);
	CREATE_VALUE(A_ProductTips);
	CREATE_VALUE(A_PictureTips);
	CREATE_VALUE(A_PictureBackplane);
	CREATE_VALUE(A_ChoosePhotoframeText);
	CREATE_VALUE(A_CheeseText);
	CREATE_VALUE(A_PictureCountdown);
	CREATE_VALUE(A_WEBCAM);
	CREATE_VALUE(A_PhotoFrame);

///////////////////////////////////////
// Plane
//////////////////////////////////////

	CREATE_VALUE(P_OpenSwingTips);
	CREATE_VALUE(P_GateBG);
	CREATE_VALUE(P_GateVideo);
	CREATE_VALUE(P_MainScenesBG);
	CREATE_VALUE(P_GreenBuildingBG);
	CREATE_VALUE(P_GreenBuildingUI);
	CREATE_VALUE(P_MilestoneNearBG);
	CREATE_VALUE(P_MilestoneBG);
	CREATE_VALUE(P_MilestoneUI); 
	CREATE_VALUE(P_ProductBG);
	CREATE_VALUE(P_ProductUI);
	CREATE_VALUE(P_TakePictureBG);
	CREATE_VALUE(P_TakePictureTips);
	CREATE_VALUE(P_TakePictureUI);
	
///////////////////////////////////////
// Element
//////////////////////////////////////
	CREATE_VALUE(E_OpenTips);
	CREATE_VALUE(E_GateBG);
	CREATE_VALUE(E_GateOpenVideo);
	CREATE_VALUE(E_GateOpenTips)	
	CREATE_VALUE(E_MainScenesBG);
	CREATE_VALUE(E_MainScenesGlass);
	CREATE_VALUE(E_GreenBuildingBG);
	CREATE_VALUE(E_GreenBuildingGlass);
	CREATE_VALUE(E_GreenBuildingLight);
	CREATE_VALUE(E_GreenBuildingTips);
	CREATE_VALUE(E_GreenBuildingZoomIn);
	CREATE_VALUE(E_GreenBuildingShowBuilding);
	CREATE_VALUE(E_MilestoneBG);
	CREATE_VALUE(E_MilestoneGlass);
	CREATE_VALUE(E_MilestoneBlackGlass);
	CREATE_VALUE(E_MilestoneTips);	
	CREATE_VALUE(E_MilestoneCountdown);
	CREATE_VALUE(E_MilestoneZoomIn);
	CREATE_VALUE(E_MilestoneVideoLoop);
	CREATE_VALUE(E_MilestoneNearBG);
	CREATE_VALUE(E_ProductBG);
	CREATE_VALUE(E_ProductGlass);
	CREATE_VALUE(E_ProductTips);
	CREATE_VALUE(E_TakePictureBG);
	CREATE_VALUE(E_TakePictureGlass);
	CREATE_VALUE(E_TakePictureTips);
	CREATE_VALUE(E_TakePictureBackplane);
	CREATE_VALUE(E_ChoosePhotoframeText);
	CREATE_VALUE(E_CheeseText);
	CREATE_VALUE(E_TakePictureCountdown);
	CREATE_VALUE(E_WEBCAM);
	CREATE_VALUE(E_PhotoFrame);

///////////////////////////////////////
// Animation Init
//////////////////////////////////////
	CREATE_VALUE(INIT_PhotoFrameChange);

///////////////////////////////////////
// Animation
//////////////////////////////////////
	CREATE_VALUE(ANIM_GreenBuildingLightFadeIn);
	CREATE_VALUE(ANIM_MilstoneZoomInFadeOut);
	CREATE_VALUE(ANIM_TakePictureTipsFadeIn);
	CREATE_VALUE(ANIM_TakePictureTipsFadeOut);
	CREATE_VALUE(ANIM_TakePictureFadeIn);
	CREATE_VALUE(ANIM_PhotoFrameFadeOut);
	CREATE_VALUE(ANIM_PhotoFrameFadeIn);

///////////////////////////////////////
// Outside trigger
//////////////////////////////////////
	CREATE_VALUE(T_DoorIsOpen);
	CREATE_VALUE(T_Greenbuilding_Show);
	CREATE_VALUE(T_PlayMilestone);
	CREATE_VALUE(T_TakePictureIsReady);
	CREATE_VALUE(T_ChangePhotoFrame);

///////////////////////////////////////
// Control Event
//////////////////////////////////////
	CREATE_VALUE(C_GreenBuilding);
	CREATE_VALUE(C_Milestone);
	CREATE_VALUE(C_Product);
};



#endif //_NAME_MANAGER_