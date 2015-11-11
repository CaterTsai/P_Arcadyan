#include "ArcadyanTheatre.h"

//--------------------------------------------------------------
void ArcadyanTheatre::setupTheatre()
{
	
	_Director.SetStageSize(ofGetWindowWidth(), ofGetWindowHeight());

#pragma region Scenes
	///////////////////////
	//Scenes
	///////////////////////	
	_Director.AddScenes(NAME_MANAGER::S_Open);
	_Director.AddScenes(NAME_MANAGER::S_Gate);
	_Director.AddScenes(NAME_MANAGER::S_MainScenes);
	_Director.AddScenes(NAME_MANAGER::S_GreenBuilding);
	_Director.AddScenes(NAME_MANAGER::S_Milestone);
	_Director.AddScenes(NAME_MANAGER::S_ProductAndFactory);
	_Director.AddScenes(NAME_MANAGER::S_TakePicture);
#pragma endregion

#pragma region Actor
	//////////////////////
	//Actor
	//////////////////////
	//S_Open
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_SwingHandWordTips, "images/start_tip.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_SwingHandTipsVideo, "videos/tips/swing.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));

	//S_Gate
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_DoorImageBG, "images/Door.jpg"));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_DoorOpenVideo, "videos/timetravel.mov"));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_OpenTipsVideo, "videos/tips/open.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	
	//S_MainScenes
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_MainScenesBG, "images/MainScenes.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_MainScenesGlass, "images/MainScenes_glass.png", eBLEND_SCREEN));

	//S_GreenBuilding
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_GreenBuildingTips, "videos/tips/GreenBuildingTips.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_GreenBuildingLight, "videos/Greenbuilding_light.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_GreenBuildingZoomIn, "videos/Greenbuilding_zoomin.mov"));

	//S_Milestone
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_MilestoneTips, "videos/tips/MilestoneTips.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_MilestoneBlackGlass, "images/Milestone_glass.png", eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_MilestoneCountdown, "videos/milstone_countdown.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_SCREEN));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_MilestoneZoomIn, "videos/milstone_zoomin.mov"));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_MilestoneNearBG, "images/Milestone_near.png"));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_MilestoneVideoLoop, "videos/milstone_loop.mov", eBLEND_SCREEN));
	
	//S_Product
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_ProductTips, "videos/tips/ProductTips.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer), eBLEND_ALPHA));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_ProductAndFactoryIntro, "videos/product_2_factoryIntro.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer)));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_FactoryBG, "images/factory_bg.png"));
	
	//S_TakePicture
	_Director.AddActor(new ofxDynamicImageActor(NAME_MANAGER::A_PictureBG));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_PictureTips, "images/PictureTips.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_PictureBackplane, "images/PicturePlane.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_ChoosePhotoframeText, "images/PhotoText_1.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxImageActor(NAME_MANAGER::A_CheeseText, "images/PhotoText_2.png", eBLEND_ALPHA));
	_Director.AddActor(new ofxAnimationImageActor(NAME_MANAGER::A_PictureCountdown, "images/countdown/", eBLEND_ALPHA));
	_Director.AddActor(new ofxDynamicImageActor(NAME_MANAGER::A_CamDisplay));
	_Director.AddActor(new ofxDynamicImageActor(NAME_MANAGER::A_PhotoFrame, eBLEND_ALPHA));
	_Director.AddActor(new ofxDynamicImageActor(NAME_MANAGER::A_Photo));
	_Director.AddActor(new ofxVideoActor(NAME_MANAGER::A_Ending, "videos/ending.mov", ofPtr<ofxHapPlayer>(new ofxHapPlayer)));
#pragma endregion

#pragma region Plane
	///////////////////////
	//Plane
	//////////////////////
	//S_Open
	_Director.AddPlane(NAME_MANAGER::S_Open, NAME_MANAGER::P_OpenSwingTips, 0, ofPoint(0, 0), WINDOW_WIDTH, WINDOW_HEIGHT, false);
		
	//S_Gate
	_Director.AddPlane(NAME_MANAGER::S_Gate, NAME_MANAGER::P_GateBG, 0);
	_Director.AddPlane(NAME_MANAGER::S_Gate, NAME_MANAGER::P_GateVideo, 1);

	//S_MainScenes
	_Director.AddPlane(NAME_MANAGER::S_MainScenes, NAME_MANAGER::P_MainScenesBG, 0);

	//S_GreenBuilding
	_Director.AddPlane(NAME_MANAGER::S_GreenBuilding, NAME_MANAGER::P_GreenBuildingBG, 0);
	_Director.AddPlane(NAME_MANAGER::S_GreenBuilding, NAME_MANAGER::P_GreenBuildingUI, 1);

	//S_Milestone
	_Director.AddPlane(NAME_MANAGER::S_Milestone, NAME_MANAGER::P_MilestoneNearBG, 0);
	_Director.AddPlane(NAME_MANAGER::S_Milestone, NAME_MANAGER::P_MilestoneBG, 1);
	_Director.AddPlane(NAME_MANAGER::S_Milestone, NAME_MANAGER::P_MilestoneUI, 2);

	//S_Product
	_Director.AddPlane(NAME_MANAGER::S_ProductAndFactory, NAME_MANAGER::P_FactoryBG, 0);
	_Director.AddPlane(NAME_MANAGER::S_ProductAndFactory, NAME_MANAGER::P_ProductBG, 1);
	_Director.AddPlane(NAME_MANAGER::S_ProductAndFactory, NAME_MANAGER::P_ProductUI, 2);
	//_Director.AddPlane(NAME_MANAGER::S_ProductAndFactory, NAME_MANAGER::P_FactoryUI, 3);

	//S_TakePicutre
	_Director.AddPlane(NAME_MANAGER::S_TakePicture, NAME_MANAGER::P_TakePictureBG, 1);
	_Director.AddPlane(NAME_MANAGER::S_TakePicture, NAME_MANAGER::P_TakePictureTips, 2);
	_Director.AddPlane(NAME_MANAGER::S_TakePicture, NAME_MANAGER::P_TakePictureUI, 3, ofPoint(0), WINDOW_WIDTH, WINDOW_HEIGHT, false);
	_Director.AddPlane(NAME_MANAGER::S_TakePicture, NAME_MANAGER::P_TakePictureEnding, 0);
#pragma endregion

#pragma region Element
	///////////////////////
	//Elemect
	///////////////////////
	//S_Open
	_Director.AddElement(NAME_MANAGER::E_OpenTips, NAME_MANAGER::P_OpenSwingTips, NAME_MANAGER::A_SwingHandTipsVideo);
	_Director.AddElement(NAME_MANAGER::E_OpenWordTips, NAME_MANAGER::P_OpenSwingTips, NAME_MANAGER::A_SwingHandWordTips, 1, ofPoint(WINDOW_WIDTH/2 - 1634/2, WINDOW_HEIGHT - 127 - 50));

	//S_Gate
	_Director.AddElement(NAME_MANAGER::E_GateBG, NAME_MANAGER::P_GateBG, NAME_MANAGER::A_DoorImageBG);
	_Director.AddElement(NAME_MANAGER::E_GateOpenTips, NAME_MANAGER::P_GateVideo, NAME_MANAGER::A_OpenTipsVideo);
	_Director.AddElement(NAME_MANAGER::E_GateOpenVideo, NAME_MANAGER::P_GateVideo, NAME_MANAGER::A_DoorOpenVideo);
	
	//S_MainScenes
	_Director.AddElement(NAME_MANAGER::E_MainScenesBG, NAME_MANAGER::P_MainScenesBG, NAME_MANAGER::A_MainScenesBG, 0);
	_Director.AddElement(NAME_MANAGER::E_MainScenesGlass, NAME_MANAGER::P_MainScenesBG, NAME_MANAGER::A_MainScenesGlass, 1);

	//S_GreenBuilding
	_Director.AddElement(NAME_MANAGER::E_GreenBuildingBG, NAME_MANAGER::P_GreenBuildingBG, NAME_MANAGER::A_MainScenesBG, 0);
	_Director.AddElement(NAME_MANAGER::E_GreenBuildingGlass, NAME_MANAGER::P_GreenBuildingBG, NAME_MANAGER::A_MainScenesGlass, 1);
	_Director.AddElement(NAME_MANAGER::E_GreenBuildingLight, NAME_MANAGER::P_GreenBuildingBG, NAME_MANAGER::A_GreenBuildingLight, 2, ofPoint(0), false);
	_Director.AddElement(NAME_MANAGER::E_GreenBuildingTips, NAME_MANAGER::P_GreenBuildingUI, NAME_MANAGER::A_GreenBuildingTips, 1);
	_Director.AddElement(NAME_MANAGER::E_GreenBuildingZoomIn, NAME_MANAGER::P_GreenBuildingUI, NAME_MANAGER::A_GreenBuildingZoomIn, 10);

	//S_Milestone
	_Director.AddElement(NAME_MANAGER::E_MilestoneBG, NAME_MANAGER::P_MilestoneBG, NAME_MANAGER::A_MainScenesBG, 0);
	_Director.AddElement(NAME_MANAGER::E_MilestoneGlass, NAME_MANAGER::P_MilestoneBG, NAME_MANAGER::A_MainScenesGlass, 1);
	_Director.AddElement(NAME_MANAGER::E_MilestoneBlackGlass, NAME_MANAGER::P_MilestoneBG, NAME_MANAGER::A_MilestoneBlackGlass, 2);
	
	_Director.AddElement(NAME_MANAGER::E_MilestoneTips, NAME_MANAGER::P_MilestoneUI, NAME_MANAGER::A_MilestoneTips, 0);
	_Director.AddElement(NAME_MANAGER::E_MilestoneCountdown, NAME_MANAGER::P_MilestoneUI, NAME_MANAGER::A_MilestoneCountdown, 1);
	_Director.AddElement(NAME_MANAGER::E_MilestoneZoomIn, NAME_MANAGER::P_MilestoneUI, NAME_MANAGER::A_MilestoneZoomIn, 2);

	_Director.AddElement(NAME_MANAGER::E_MilestoneNearBG, NAME_MANAGER::P_MilestoneNearBG, NAME_MANAGER::A_MilestoneNearBG, 0);
	_Director.AddElement(NAME_MANAGER::E_MilestoneVideoLoop, NAME_MANAGER::P_MilestoneNearBG, NAME_MANAGER::A_MilestoneVideoLoop, 1);
	
	//S_ProductAndFactory
	_Director.AddElement(NAME_MANAGER::E_ProductBG, NAME_MANAGER::P_ProductBG, NAME_MANAGER::A_MainScenesBG, 0);
	_Director.AddElement(NAME_MANAGER::E_ProductGlass, NAME_MANAGER::P_ProductBG, NAME_MANAGER::A_MainScenesGlass, 1);
	_Director.AddElement(NAME_MANAGER::E_ProductTips, NAME_MANAGER::P_ProductUI, NAME_MANAGER::A_ProductTips);

	_Director.AddElement(NAME_MANAGER::E_ProductVideoAndFactoryIntro, NAME_MANAGER::P_ProductUI, NAME_MANAGER::A_ProductAndFactoryIntro, 1);
	_Director.AddElement(NAME_MANAGER::E_FactoryBG, NAME_MANAGER::P_FactoryBG, NAME_MANAGER::A_FactoryBG, 0, ofPoint(0), false);
	
	//S_TakePicture
	//_Director.AddElement(NAME_MANAGER::E_TakePictureBG, NAME_MANAGER::P_TakePictureBG, NAME_MANAGER::A_MainScenesBG, 0);
	//_Director.AddElement(NAME_MANAGER::E_TakePictureGlass, NAME_MANAGER::P_TakePictureBG, NAME_MANAGER::A_MainScenesGlass, 1);
	_Director.AddElement(NAME_MANAGER::E_TakePictureBG, NAME_MANAGER::P_TakePictureBG, NAME_MANAGER::A_PictureBG, 0);
	_Director.AddElement(NAME_MANAGER::E_TakePictureTips, NAME_MANAGER::P_TakePictureTips, NAME_MANAGER::A_PictureTips, 10, ofPoint(0), false);
	_Director.AddElement(NAME_MANAGER::E_TakePictureBackplane, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_PictureBackplane, 0, ofPoint(53, 67));
	_Director.AddElement(NAME_MANAGER::E_ChoosePhotoframeText, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_ChoosePhotoframeText, 1, ofPoint(1497, 222));
	_Director.AddElement(NAME_MANAGER::E_CheeseText, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_CheeseText, 2, ofPoint(1497, 207), false);
	_Director.AddElement(NAME_MANAGER::E_TakePictureCountdown, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_PictureCountdown, 4, ofPoint(910, 300), false);
	_Director.AddElement(NAME_MANAGER::E_PhotoFrame, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_PhotoFrame, 3, ofPoint(569, 142));
	_Director.AddElement(NAME_MANAGER::E_CamDisplay, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_CamDisplay, 4, ofPoint(585, 387));
	_Director.AddElement(NAME_MANAGER::E_Photo, NAME_MANAGER::P_TakePictureUI, NAME_MANAGER::A_Photo, 6, ofPoint(569, 142), false);
	_Director.AddElement(NAME_MANAGER::E_Ending, NAME_MANAGER::P_TakePictureEnding, NAME_MANAGER::A_Ending, 0, ofPoint(0, 0), false);
#pragma endregion
	
#pragma region Element Setting
	///////////////////////
	//Element Setting
	///////////////////////
	ofxVideoElement* pVideoElement_;
	_Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MANAGER::E_GateOpenTips, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_GateOpenVideo, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingTips, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingLight, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingZoomIn, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneTips, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneCountdown, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneZoomIn, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneVideoLoop, pVideoElement_);
	pVideoElement_->SetVideoLoop(true);
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_ProductTips, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);

	_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	_Director.GetElementPtr(NAME_MANAGER::E_Ending, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(false);

	ofxDynamicImageElement*	pDyamnicElement_;
	_Director.GetElementPtr(NAME_MANAGER::E_CamDisplay, pDyamnicElement_);
	pDyamnicElement_->m_stElementBase.fScale = 0.225;
	pDyamnicElement_->m_stElementBaseBackup.fScale = 0.225;
	//pDyamnicElement_->m_stElementBase.bIsMirror = true;
	//pDyamnicElement_->m_stElementBaseBackup.bIsMirror = true;
		
	_Director.GetElementPtr(NAME_MANAGER::E_PhotoFrame, pDyamnicElement_);
	pDyamnicElement_->m_stElementBase.fScale = 0.42;
	pDyamnicElement_->m_stElementBaseBackup.fScale = 0.42;

	_Director.GetElementPtr(NAME_MANAGER::E_Photo, pDyamnicElement_);
	pDyamnicElement_->m_stElementBase.fScale = 0.42;
	pDyamnicElement_->m_stElementBaseBackup.fScale = 0.42;

	ofxAnimationImageElement* pAnimationElement_;
	_Director.GetElementPtr(NAME_MANAGER::E_TakePictureCountdown, pAnimationElement_);
	pAnimationElement_->SetSPF(1);
	pAnimationElement_->SetEvent(true);
#pragma endregion	

	///////////////////////
	//Setup each Scenes
	///////////////////////
	this->setupScenesGate();

	///////////////////////
	//Setup other object
	///////////////////////
	this->setupCityLoop();
	this->setupControlEvent();

	///////////////////////
	//Setting
	///////////////////////
	ofAddListener(ofxTheatreEventArgs::TheatreEvent, this, &ArcadyanTheatre::onTheatreEvent);
	_Director.Play();

#ifdef TIMEOUT_MODE
	_bStartTimer = false;
#endif // TIMEOUT_MODE

}

//--------------------------------------------------------------
void ArcadyanTheatre::updateTheatre(float fDelta, ofPoint CtrlPos)
{
	string strScenesName_ = _Director.GetNowScenes()->GetScenesName();
	int iFrame_ = 0;
	if(strScenesName_ == NAME_MANAGER::S_Open)
	{

	}
	else if(strScenesName_ == NAME_MANAGER::S_Gate)
	{
		this->updateScenesGate(fDelta);
	}
	else if(strScenesName_ == NAME_MANAGER::S_GreenBuilding)
	{
#ifdef TIMEOUT_MODE
		if(_bStartTimer)
		{
			_fDebugTimer -= fDelta;
			if(_fDebugTimer < 0.0)
			{
				this->disableControlEvent(NAME_MANAGER::S_GreenBuilding);
				this->GreenbuildingZoomIn();
				_bStartTimer = false;
			}
		}
#endif // TIMEOUT_MODE
	}
	else if(strScenesName_ == NAME_MANAGER::S_MainScenes)
	{
	}
	else if(strScenesName_ == NAME_MANAGER::S_Milestone)
	{
#ifdef TIMEOUT_MODE
		if(_bStartTimer)
		{
			_fDebugTimer -= fDelta;
			if(_fDebugTimer < 0.0)
			{
				this->disableControlEvent(NAME_MANAGER::S_Milestone);
				this->MilestoneZoomIn();
				_bStartTimer = false;
			}
		}
#endif // TIMEOUT_MODE
	}
	else if(strScenesName_ == NAME_MANAGER::S_ProductAndFactory)
	{
		ofxVideoElement* pVideo_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, pVideo_);
		iFrame_ = pVideo_->GetFrame();

#ifdef TIMEOUT_MODE
		if(_bStartTimer)
		{
			_fDebugTimer -= fDelta;
			if(_fDebugTimer < 0.0)
			{
				ofxVideoElement	*pVideo_ = nullptr;
				_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, pVideo_);
				pVideo_->PlayVideo();		

				this->disableControlEvent(NAME_MANAGER::S_ProductAndFactory);
				_bStartTimer = false;
			}
		}
#endif // TIMEOUT_MODE
	}

	this->updateCityLoop();
	this->updateControlEvent(CtrlPos);
	_Director.update(iFrame_);
}

//--------------------------------------------------------------
void ArcadyanTheatre::drawTheatre()
{
	ofPushStyle();
	{
		ofSetColor(255);
		this->drawCityLoop();

		_Director.draw();

		string strScenesName_ = _Director.GetNowScenes()->GetScenesName();

		if(strScenesName_ == NAME_MANAGER::S_Open)
		{
		}
		else if(strScenesName_ == NAME_MANAGER::S_Gate)
		{
			this->drawScenesGate();
		}
		else if(strScenesName_ == NAME_MANAGER::S_MainScenes)
		{
		}
		else if(strScenesName_ == NAME_MANAGER::S_Milestone)
		{
		}

		this->drawControlEvent();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ArcadyanTheatre::resetTheatre()
{	
	//City loop
	this->stopCityLoop();

	//Control Event
	this->resetControlEvent();

	_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
}

//--------------------------------------------------------------
void ArcadyanTheatre::TheatreAnimInit(string strScenes)
{
	ofxBaseElement* pElementPtr_;
	ofxPlane* pPlanePtr_;

	if(strScenes == NAME_MANAGER::S_GreenBuilding)
	{
		_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingLight, pElementPtr_);
		_Director.AddAnimation(NAME_MANAGER::S_GreenBuilding, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_GreenBuildingLightFadeIn, pElementPtr_));
	}
	else if(strScenes == NAME_MANAGER::S_Milestone)
	{
		_Director.GetPlanePtr(NAME_MANAGER::P_MilestoneUI, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_Milestone, 0, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_MilstoneZoomInFadeOut, pPlanePtr_, 0.3, 0.0, 0.0));
	}
	else if(strScenes == NAME_MANAGER::S_ProductAndFactory)
	{
		_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, pElementPtr_);
		_Director.AddVideoAnimation(NAME_MANAGER::S_ProductAndFactory,  new ofxEmptyAnimation(NAME_MANAGER::ANIM_FactoryArmEnter, pElementPtr_, 1866, 0.0));
	}
	else if(strScenes == NAME_MANAGER::S_TakePicture)
	{
		_Director.GetElementPtr(NAME_MANAGER::E_TakePictureTips, pElementPtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_TakePictureTipsFadeIn, pElementPtr_, 0.5, 1, 3));
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_TakePictureTipsFadeOut, pElementPtr_, 0.5, 1, 0));
		
		_Director.GetPlanePtr(NAME_MANAGER::P_TakePictureUI, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_TakePictureFadeIn, pPlanePtr_, 0.5, 1, 0));
	}
	else if(strScenes == NAME_MANAGER::INIT_SwingTipsFadein)
	{
		_Director.GetPlanePtr(NAME_MANAGER::P_OpenSwingTips, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_Open, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_SwingTipsFadeIn, pPlanePtr_, 0.5, 0.0, 0.0));
	}
	else if(strScenes == NAME_MANAGER::INIT_SwingTipsFadeout)
	{
		_Director.GetPlanePtr(NAME_MANAGER::P_OpenSwingTips, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_Open, 0, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_SwingTipsFadeOut, pPlanePtr_, 0.5, 0.0, 0.0));
	}
	else if(strScenes == NAME_MANAGER::INIT_PhotoFrameChange)
	{
		_Director.GetElementPtr(NAME_MANAGER::E_PhotoFrame, pElementPtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_PhotoFrameFadeOut, pElementPtr_, 0.3, 0.0, 0.0));
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_PhotoFrameFadeIn, pElementPtr_, 0.3, 0.2, 0.0));
	}
	else if(strScenes == NAME_MANAGER::INIT_Ending)
	{
		_Director.GetElementPtr(NAME_MANAGER::E_Ending, pElementPtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxEmptyAnimation(NAME_MANAGER::ANIM_EndingWaiting, pElementPtr_, 0.0, 5.0, 0));
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 0, new ofxFadeInAnimation(NAME_MANAGER::ANIM_EndingFadeIn, pElementPtr_, 0.0, 0.0, 0));

		_Director.GetPlanePtr(NAME_MANAGER::P_TakePictureUI, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 1, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_TakePictureUIFadeOut, pPlanePtr_, 2, 5.0, 0));

		_Director.GetPlanePtr(NAME_MANAGER::P_TakePictureBG, pPlanePtr_);
		_Director.AddAnimation(NAME_MANAGER::S_TakePicture, 2, new ofxFadeOutAnimation(NAME_MANAGER::ANIM_TakePictureBGFadeOut, pPlanePtr_, 2, 5.0, 0));
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::onTheatreEvent(ofxTheatreEventArgs& e)
{
	//Scences Event
	if(e.strMessage == NAME_MANAGER::S_Open)
	{
		this->stopCityLoop();
	}
	else if(e.strMessage == NAME_MANAGER::S_Milestone)
	{
		this->stopCityLoop();
	}
	else if(e.strMessage == NAME_MANAGER::S_ProductAndFactory)
	{
		this->TheatreAnimInit(NAME_MANAGER::S_ProductAndFactory);
		this->playCityLoop();
	}
	
	//Video Event
	if(e.strMessage == NAME_MANAGER::E_GateOpenVideo)
	{
		this->playCityLoop();
		_Director.TransitTo();
		string strEventMsg_ = NAME_MANAGER::T_DoorIsOpen;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::E_GreenBuildingTips)
	{
		this->TheatreAnimInit(NAME_MANAGER::S_GreenBuilding);
		this->enableControlEvent(NAME_MANAGER::S_GreenBuilding);

		ofxVideoElement*	pVideoElement_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingLight, pVideoElement_);
		pVideoElement_->PlayVideo();

		_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingTips, pVideoElement_);
		pVideoElement_->StopVideo();

#ifdef TIMEOUT_MODE
		_bStartTimer = true;
		_fDebugTimer = cGREEN_IN_TIMEOUT;
#endif // TIMEOUT_MODE

	}
	else if(e.strMessage == NAME_MANAGER::E_GreenBuildingZoomIn)
	{
		ofxVideoElement*	pVideoElement_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingLight, pVideoElement_);
		pVideoElement_->StopVideo();

		string strEventMsg_ = NAME_MANAGER::T_Greenbuilding_Show;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::E_MilestoneTips)
	{
		//Start the countdown loop
		ofxVideoElement*	pMilestonCountdown_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_MilestoneCountdown, pMilestonCountdown_);
		pMilestonCountdown_->PlayVideo();

		this->enableControlEvent(NAME_MANAGER::S_Milestone);

#ifdef TIMEOUT_MODE
		_bStartTimer = true;
		_fDebugTimer = cMILESTONE_IN_TIMEOUT;
#endif // TIMEOUT_MODE
	}
	else if(e.strMessage == NAME_MANAGER::E_MilestoneZoomIn)
	{	
		ofxVideoElement*	pMilestonLoop_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_MilestoneVideoLoop, pMilestonLoop_);
		pMilestonLoop_->PlayVideo();
		
		//Fade out the Zoom in video
		this->TheatreAnimInit(NAME_MANAGER::S_Milestone);

		string strEventMsg_ = NAME_MANAGER::T_PlayMilestone;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::E_ProductTips)
	{	
		this->enableControlEvent(NAME_MANAGER::S_ProductAndFactory);

#ifdef TIMEOUT_MODE
		_bStartTimer = true;
		_fDebugTimer = cPRODUCT_IN_TIMEOUT;
#endif // TIMEOUT_MODE
	}
	else if(e.strMessage == NAME_MANAGER::E_ProductVideoAndFactoryIntro)
	{
		stopCityLoop();
		ofxBaseElement *ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, ptr_);
		ptr_->SetVisible(false);

		_Director.GetElementPtr(NAME_MANAGER::E_FactoryBG, ptr_);
		ptr_->SetVisible(true);

		ofxPlane *pPlane_ = nullptr;
		_Director.GetPlanePtr(NAME_MANAGER::P_ProductBG, pPlane_);
		pPlane_->SetVisible(false);

		_Director.GetPlanePtr(NAME_MANAGER::P_ProductUI, pPlane_);
		pPlane_->SetVisible(false);

		string strEventMsg_ = NAME_MANAGER::T_StartFactory;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::E_Ending)
	{
		string strEventMsg_ = NAME_MANAGER::T_Ending;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}

	//Animation Element Event
	if(e.strMessage == NAME_MANAGER::E_TakePictureCountdown)
	{
		ofxAnimationImageElement* ptr_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_TakePictureCountdown, ptr_);
		ptr_->SetVisible(false);

		string strEventMsg_ = NAME_MANAGER::T_TakePhoto;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);

		//set ending video
		this->TheatreAnimInit(NAME_MANAGER::INIT_Ending);
	}

	//Animation Event
	if(e.strMessage == NAME_MANAGER::ANIM_MilstoneZoomInFadeOut)
	{
		//stop all video
		ofxVideoElement*	pVideoElement_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_MilestoneZoomIn, pVideoElement_);
		pVideoElement_->StopVideo();

		ofxPlane*	pPlane_ = nullptr;
		_Director.GetPlanePtr(NAME_MANAGER::P_MilestoneUI, pPlane_);
		pPlane_->SetVisible(false);
	}
	else if(e.strMessage == NAME_MANAGER::ANIM_FactoryArmEnter)
	{
		string strEventMsg_ = NAME_MANAGER::T_EnterArm;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::ANIM_TakePictureFadeIn)
	{
		string strEventMsg_ = NAME_MANAGER::T_TakePictureIsReady;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::ANIM_PhotoFrameFadeOut)
	{
		string strEventMsg_ = NAME_MANAGER::T_ChangePhotoFrame;
		ofNotifyEvent(ArcadyanTheaterEvent, strEventMsg_, this);
	}
	else if(e.strMessage == NAME_MANAGER::ANIM_EndingWaiting)
	{
		ofxVideoElement*	pVideoElement_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_Ending, pVideoElement_);
		pVideoElement_->PlayVideo();

		this->stopCityLoop();
	}
}

#pragma region CityLoop
//--------------------------------------------------------------
void ArcadyanTheatre::setupCityLoop()
{
	//_CityLoop.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
	//_CityLoop.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	_CityLoop.loadMovie("videos/city_loop.mov");
	_bIsCityLoopPlaying = false;
}

//--------------------------------------------------------------
void ArcadyanTheatre::updateCityLoop()
{
	if(_bIsCityLoopPlaying)
	{
		_CityLoop.update();
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::drawCityLoop()
{
	if(_bIsCityLoopPlaying)
	{
		ofPushStyle();
		{
			ofSetColor(255);
			_CityLoop.draw(0, 0);
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::playCityLoop()
{
	_bIsCityLoopPlaying = true;
	_CityLoop.play();
}

//--------------------------------------------------------------
void ArcadyanTheatre::stopCityLoop()
{
	_CityLoop.stop();
	_bIsCityLoopPlaying = false;
}
#pragma endregion

#pragma region Process each scene
//--------------------------------------------------------------
void ArcadyanTheatre::TriggerTheGateLight()
{
	_bTriggerOpen = false;
	_AnimAlpha.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	_AnimAlpha.animateFromTo(0, 255);
}

//--------------------------------------------------------------
void ArcadyanTheatre::OpenTheGate()
{
	_bTriggerOpen = true;
	_AnimAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimAlpha.animateTo(255);
}

//--------------------------------------------------------------
void ArcadyanTheatre::setupScenesGate()
{
	_DoorBelt.loadImage("images/Door_Belt.png");
	_DoorLight.loadImage("images/Door_Light.png");

	_bTriggerOpen = false;

	_AnimAlpha.setCurve(AnimCurve::EASE_IN_EASE_OUT);
	_AnimAlpha.setDuration(1.0);
	_AnimAlpha.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
}

//--------------------------------------------------------------
void ArcadyanTheatre::updateScenesGate(float fDelta)
{
	_AnimAlpha.update(fDelta);

	if(_bTriggerOpen && _AnimAlpha.getPercentDone() == 1.0)
	{
		_bTriggerOpen = false;
		
		//Play open video
		ofxVideoElement* pVideoElement_;
		_Director.GetElementPtr(NAME_MANAGER::E_GateOpenVideo, pVideoElement_);
		pVideoElement_->PlayVideo();
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::drawScenesGate()
{
	if(_AnimAlpha.isAnimating())
	{
		ofPushStyle();
		{
			ofSetColor(255, _AnimAlpha.getCurrentValue());
		
			ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);
				_DoorBelt.draw(0, 0);
			ofDisableBlendMode();

			ofSetColor(_AnimAlpha.getCurrentValue());
			ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SCREEN);
				_DoorLight.draw(0, 0);
			ofDisableBlendMode();
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::GreenbuildingZoomIn()
{
	ofxVideoElement* pVideoElement_;
	
	//Play zoom-in video
	_Director.GetElementPtr(NAME_MANAGER::E_GreenBuildingZoomIn, pVideoElement_);
	pVideoElement_->PlayVideo();
	
	//Stop city loop
	this->stopCityLoop();
}

//--------------------------------------------------------------
void ArcadyanTheatre::MilestoneZoomIn()
{
	ofxVideoElement* pVideoElement_ = nullptr;

	//Stop the countdown
	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneCountdown, pVideoElement_);
	pVideoElement_->StopVideo();

	//Play zoom-in video
	_Director.GetElementPtr(NAME_MANAGER::E_MilestoneZoomIn, pVideoElement_);
	pVideoElement_->PlayVideo();
	
	ofxPlane*	pPlane_ = nullptr;
	_Director.GetPlanePtr(NAME_MANAGER::P_MilestoneBG, pPlane_);
	pPlane_->SetVisible(false);

	//Stop city loop
	this->stopCityLoop();
}
#pragma endregion

#pragma region ControlEvent
//--------------------------------------------------------------
void ArcadyanTheatre::onControlEvent(string& e)
{
	if(e == NAME_MANAGER::C_GreenBuilding)
	{
		this->disableControlEvent(NAME_MANAGER::S_GreenBuilding);
		this->GreenbuildingZoomIn();
	}
	else if(e == NAME_MANAGER::C_Milestone)
	{
		this->disableControlEvent(NAME_MANAGER::S_Milestone);
		this->MilestoneZoomIn();
	}
	else if(e == NAME_MANAGER::C_Product)
	{
		ofxVideoElement	*pVideo_ = nullptr;
		_Director.GetElementPtr(NAME_MANAGER::E_ProductVideoAndFactoryIntro, pVideo_);
		pVideo_->PlayVideo();		

		this->disableControlEvent(NAME_MANAGER::S_ProductAndFactory);

		//_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
		//this->TheatreAnimInit(NAME_MANAGER::S_TakePicture);
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::setupControlEvent()
{
	ofImage CtrlImg_;
	CtrlImg_.loadImage("images/hand.png");
	
	//Green Building
	ofImage TouchImg_;
	TouchImg_.loadImage("images/GreenBuilding_target.png");
	auto pGreenbuildingCtrlPtr_ = make_shared<DragControlEvent>(CtrlImg_, NAME_MANAGER::C_GreenBuilding);
	pGreenbuildingCtrlPtr_->setupDragEvent(TouchImg_, ofPoint(520, 510), ofRectangle(895, 485, 335, 160));
	_CtrlEventMgr.insert(make_pair(NAME_MANAGER::S_GreenBuilding, pGreenbuildingCtrlPtr_));

	//Milestone
	auto pMilestoneCtrlPtr_ = make_shared<TouchControlEvent>(CtrlImg_, NAME_MANAGER::C_Milestone);
	pMilestoneCtrlPtr_->setupTouchTarget(ofRectangle(255, 325, 265, 260));
	_CtrlEventMgr.insert(make_pair(NAME_MANAGER::S_Milestone, pMilestoneCtrlPtr_));

	//Product
	ofImage ProductImg_;
	ProductImg_.loadImage("images/Product_target.png");
	auto pProductCtrlPtr_ = make_shared<TouchControlEvent>(CtrlImg_, NAME_MANAGER::C_Product);
	pProductCtrlPtr_->setupTouchTarget(ProductImg_, ofPoint(1255, 510));
	_CtrlEventMgr.insert(make_pair(NAME_MANAGER::S_ProductAndFactory, pProductCtrlPtr_));


	//Add event listener
	ofAddListener(pGreenbuildingCtrlPtr_->ControlEvent, this, &ArcadyanTheatre::onControlEvent);
	ofAddListener(pMilestoneCtrlPtr_->ControlEvent, this, &ArcadyanTheatre::onControlEvent);
	ofAddListener(pProductCtrlPtr_->ControlEvent, this, &ArcadyanTheatre::onControlEvent);
}

//--------------------------------------------------------------
void ArcadyanTheatre::updateControlEvent(ofPoint CtrlPos)
{
	string strScenesName_ = _Director.GetNowScenes()->GetScenesName();
	

	for(auto Iter_ = _CtrlEventMgr.begin(); Iter_ != _CtrlEventMgr.end(); ++Iter_)
	{	
		if(Iter_->first == strScenesName_)
		{
			Iter_->second->updateControlEvent(CtrlPos);
		}
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::drawControlEvent()
{
	string strScenesName_ = _Director.GetNowScenes()->GetScenesName();
	
	for(auto Iter_ = _CtrlEventMgr.begin(); Iter_ != _CtrlEventMgr.end(); ++Iter_)
	{
		if(Iter_->first == strScenesName_)
		{
			Iter_->second->drawControlEvent();
		}
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::enableControlEvent(string strScenceName)
{
	for(auto Iter_ = _CtrlEventMgr.begin(); Iter_ != _CtrlEventMgr.end(); ++Iter_)
	{
		if(Iter_->first == strScenceName)
		{
			Iter_->second->setDisplay(true);
		}
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::disableControlEvent(string strScenceName)
{
	for(auto Iter_ = _CtrlEventMgr.begin(); Iter_ != _CtrlEventMgr.end(); ++Iter_)
	{
		if(Iter_->first == strScenceName)
		{
			Iter_->second->setDisplay(false);
		}
	}
}

//--------------------------------------------------------------
void ArcadyanTheatre::resetControlEvent()
{
	for(auto Iter_ : _CtrlEventMgr)
	{
		Iter_.second->resetControlEvent();
	}
}
#pragma endregion