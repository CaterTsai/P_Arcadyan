#include "Arcadyan.h"

//--------------------------------------------------------------
void Arcadyan::setup()
{
	ofBackground(255);
	ofSetVerticalSync(true);

	//Video Manager
	this->InitialVideoManager();

	//Image Slider
	this->InitialImageSlider();

	//GB Ctrl
	_bStartMove = false;
	_GreenBuildingCtrl.setupGreenBuildingCtrl();

	//Text Slider
	this->InitialTextSlider();
	ofAddListener(_TextCurveSlider.TextSliderFinishEvent, this, &Arcadyan::onTextSlider);

	//Photo Frame Slider
	_PhotoFrameSlider.setupVirticalSlider(ofRectangle(0, 0, 1024, 250), (cSMALL_PHOTO_WIDTH * cSMALL_PHOTO_SCALE) + 90);
	
	//Theatre
	_Arcadyan.setupTheatre();
	ofAddListener(_Arcadyan.ArcadyanTheaterEvent, this, &Arcadyan::onArcadyanTheaterEvent);

	//Kinect Ctrl
	//_KinectCtrl.setupKinectCtrl();

	//Info Display
	_InfoDisplay.setupInfoDisplay();
	_InfoDisplay.getNowWeatherInfo();
	ofAddListener(_InfoDisplay.FinishEvent, this, &Arcadyan::onInfoDisplay);

	_VideoMgr.play();

	//Timer
	_fMainTimer = ofGetElapsedTimef();

	ofToggleFullscreen();
	ofHideCursor();
}

//--------------------------------------------------------------
void Arcadyan::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	//Update KinectCtrl and get ctrl poss
	//_KinectCtrl.updateKinectCtrl();
	
	ofPoint CtrlPos_;
	if(!_KinectCtrl.getCtrlPos(CtrlPos_))
	{
		CtrlPos_.set(ofGetMouseX(), ofGetMouseY());
	}	

	//
	string strScenesName_ = _Arcadyan._Director.GetNowScenes()->GetScenesName();
	if(strScenesName_ == NAME_MANAGER::S_Open)
	{
		_VideoMgr.updateVideoManager();

		if(_ImgSlider.getIsDisplay())
		{
			_ImgSlider.UpdateImageSlider(fDelta_);
			if(_ImgSlider.getIsEnd())
			{
				_ImgSlider.StopSlider();
				_VideoMgr.next();
			}
		}
	}
	else if(strScenesName_ == NAME_MANAGER::S_MainScenes)
	{
		_InfoDisplay.updateInfoDisplay(fDelta_);
	}
	else if(strScenesName_ == NAME_MANAGER::S_GreenBuilding)
	{
		_GreenBuildingCtrl.updateGreenBuildingCtrl(fDelta_, CtrlPos_);
	}
	else if(strScenesName_ == NAME_MANAGER::S_Milestone)
	{
		_TextCurveSlider.updateCurveSlider(fDelta_);
	}
	else if(strScenesName_ == NAME_MANAGER::S_TakePicture)
	{
		_PhotoFrameSlider.updateVirticalSlider(fDelta_);
	}

	//Theatre
	_Arcadyan.updateTheatre(fDelta_, CtrlPos_);

	//Show FPS
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void Arcadyan::draw()
{
	this->drawBeforeTheatre();
	_Arcadyan.drawTheatre();
	this->drawAfterTheatre();

	//_KinectCtrl.drawKinectCtrl();
}

//--------------------------------------------------------------
void Arcadyan::exit()
{
	//_KinectCtrl.exitKinectCtrl();
}

//--------------------------------------------------------------
void Arcadyan::keyPressed(int key)
{
	switch(key)
	{
	case 'o':
		{
			_Arcadyan.OpenTheGate();

			ofxVideoElement*	pVideoElement_;
			_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_GateOpenTips, pVideoElement_);
			pVideoElement_->StopVideo();
		}
		break;
	case 'n':
		{
			_VideoMgr.next();

			ofxVideoElement*	pVideoElement_;
			_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
			pVideoElement_->StopVideo();
		}
		break;
	case 'z':
		{
			if(_Arcadyan._Director.GetNowScenes()->GetScenesName() == NAME_MANAGER::S_GreenBuilding)
			{
				_Arcadyan.GreenbuildingZoomIn();
			}
			else if(_Arcadyan._Director.GetNowScenes()->GetScenesName() == NAME_MANAGER::S_Milestone)
			{
				_Arcadyan.MilestoneZoomIn();
			}
		}
		break;
	case 't':
		{
			if(_Arcadyan._Director.GetNowScenes()->GetScenesName() == NAME_MANAGER::S_GreenBuilding)
			{
				_Arcadyan._Director.TransitTo(eTransitionsType::eTRANSITION_FADE);
				_GreenBuildingCtrl.stopGreenBuidling();
				_Arcadyan.playCityLoop();
			}
			else
			{
				_Arcadyan._Director.TransitTo(eTransitionsType::eTRANSITION_NONE);
			}
		}
		break;
	case 'f':
		{
			ofToggleFullscreen();
		}
		break;
	case 'r':
		{
			_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
			_PhotoFrameSlider.toRight();
		}
		break;
	case 'l':
		{
			_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
			_PhotoFrameSlider.toLeft();
		}
		break;
	case '1':
		{
			_TextCurveSlider.RotateToForward();
		}
		break;
	case '2':
		{
			_TextCurveSlider.RotateToBackward();
		}
		break;
	case '0':
		{
			this->resetTheatre();
		}
		break;
	}
}

//--------------------------------------------------------------
void Arcadyan::mousePressed( int x, int y, int button )
{
}

//--------------------------------------------------------------
void Arcadyan::mouseReleased(int x, int y, int button )
{
}

//--------------------------------------------------------------
void Arcadyan::drawBeforeTheatre()
{
	string strScenesName_ = _Arcadyan._Director.GetNowScenes()->GetScenesName();

	if(strScenesName_ == NAME_MANAGER::S_Open)
	{
		_VideoMgr.drawVideoManager();
	}
	else if(strScenesName_ == NAME_MANAGER::S_MainScenes)
	{
	}
	else if(strScenesName_ == NAME_MANAGER::S_Milestone)
	{
	}
}

//--------------------------------------------------------------
void Arcadyan::drawAfterTheatre()
{
	string strScenesName_ = _Arcadyan._Director.GetNowScenes()->GetScenesName();

	if(strScenesName_ == NAME_MANAGER::S_Open)
	{
		_ImgSlider.DrawImageSlider(_fImgRotateX, _fImgRotateY);
	}
	else if(strScenesName_ == NAME_MANAGER::S_MainScenes)
	{
		_InfoDisplay.drawInfoDisplay();
	}
	else if(strScenesName_ == NAME_MANAGER::S_GreenBuilding)
	{
		_GreenBuildingCtrl.drawGreenBuildingCtrl();
	}
	else if(strScenesName_ == NAME_MANAGER::S_Milestone)
	{
		_TextCurveSlider.drawCurveSlider();
	}
	else if(strScenesName_ == NAME_MANAGER::S_TakePicture)
	{
		_PhotoFrameSlider.drawVirticalSlider(448, 703);
	}
}

//--------------------------------------------------------------
void Arcadyan::onArcadyanTheaterEvent(string& e)
{
	if(e == NAME_MANAGER::T_DoorIsOpen)
	{
		_InfoDisplay.startDisplay(3);
	}
	else if(e == NAME_MANAGER::T_Greenbuilding_Show)
	{
		_fX = ofGetMouseX();
		_GreenBuildingCtrl.startGreenBuidling();
	}
	else if(e == NAME_MANAGER::T_PlayMilestone)
	{
		_TextCurveSlider.startCurveSlider();
	}
	else if(e == NAME_MANAGER::T_TakePictureIsReady)
	{
		//Get now photo frame
		ofImage NowPhotoFrame_;
		_PhotoFrameSlider.getNowImage(NowPhotoFrame_);
		ofxDynamicImageElement* pPhotoFrame_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_PhotoFrame, pPhotoFrame_);
		pPhotoFrame_->updateImg(NowPhotoFrame_);
		
		_PhotoFrameSlider.setDisplay();
	}
	else if(e == NAME_MANAGER::T_ChangePhotoFrame)
	{
		//Get now photo frame
		ofImage NowPhotoFrame_;
		_PhotoFrameSlider.getNowImage(NowPhotoFrame_);
		ofxDynamicImageElement* pPhotoFrame_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_PhotoFrame, pPhotoFrame_);
		pPhotoFrame_->updateImg(NowPhotoFrame_);
	}
	else
	{
		ofLog(OF_LOG_WARNING, "Unknow event from ArcadyanTheater");
	}
}

//--------------------------------------------------------------
void Arcadyan::resetTheatre()
{
	//Video Manager
	_VideoMgr.stop();

	//Image Slider
	_ImgSlider.StopSlider();

	//Info Display
	_InfoDisplay.getNowWeatherInfo();

	//Green Bilding
	_GreenBuildingCtrl.stopGreenBuidling();

	//Milstion
	

	//Photo Frame Slider
	_PhotoFrameSlider.resetVirticalSlider();

	//Theatre
	_Arcadyan.resetTheatre();

	//Start
	_VideoMgr.play();
}

//--------------------------------------------------------------
void Arcadyan::InitialVideoManager()
{
	_VideoMgr.setupVideoManager();
	
	//_VideoMgr.addVideo("videos/intro_in.mov", "V_IntroIn", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), false);
	//_VideoMgr.addVideo("videos/intro_loop.mov", "V_IntroLoop", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), false, true, true);
	//_VideoMgr.addVideo("videos/intro_out.mov", "V_IntroOut", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), false);
	
	_VideoMgr.addVideoWithSourcePlayer("videos/intro_in.mov", "V_IntroIn");
	_VideoMgr.addVideoWithSourcePlayer("videos/intro_loop.mov", "V_IntroLoop", true, true);
	_VideoMgr.addVideoWithSourcePlayer("videos/intro_out.mov", "V_IntroOut");

	_VideoMgr.addVideo("videos/Cloud_intro.mov", "V_FadeIn",ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), true);
	_VideoMgr.addVideo("videos/csr.mov", "V_CSR",ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), true);
	_VideoMgr.addVideo("videos/slider_loop.mov", "V_SliderLoop",ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), true, true, false);
	
	_VideoMgr.addVideo("videos/open.mov", "V_Door",ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer), true);

	_VideoMgr.setBackgroundVideo("videos/clouds_Loop.mp4", (ofPtr<ofBaseVideoPlayer>)ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));

	ofAddListener(VideoManager::VideoEvent, this, &Arcadyan::onVideoEvent);
}

//--------------------------------------------------------------
void Arcadyan::onVideoEvent(string& e)
{
	if(e == "V_VideoDone")
	{
		_Arcadyan._Director.TransitTo(eTransitionsType::eTRANSITION_NONE);
		_Arcadyan.TriggerTheGateLight();

		ofxVideoElement*	pVideoElement_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_GateOpenTips, pVideoElement_);
		pVideoElement_->PlayVideo();
	}
	else if(e == "V_IntroLoop")
	{
		ofxVideoElement*	pVideoElement_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
		pVideoElement_->PlayVideo();
	}
	else if(e == "V_SliderLoop")
	{
		_ImgSlider.StartSlider();
	}
}

//--------------------------------------------------------------
void Arcadyan::InitialImageSlider()
{
	_fImgRotateX = 0.0;
	_fImgRotateY = 10.0;
	_ImgSlider.SetupImageSlider("xml/_ImageSliderData.xml", ofPoint(750, ofGetHeight()/2, 0), ofPoint(0, 0, -1000), 1.0);
}

//--------------------------------------------------------------
void Arcadyan::onInfoDisplay(bool& e)
{
	_Arcadyan._Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
}

//--------------------------------------------------------------
void Arcadyan::InitialTextSlider()
{
	_TextCurveSlider.setupContanct();
	_TextCurveSlider.setCurveSliderData("xml/_TextSliderData.xml", 10, 2);
	_TextCurveSlider.setCurveSliderPath(
		ofPoint(0, 0, 1000)
		,ofPoint(0, 0, -5000)
		,ofPoint(-1000, 0, 0)
		,ofPoint(-1000, 0, -4000)
		,1000
	);
	_TextCurveSlider.setDrawPos(ofPoint(ofGetWindowWidth()/2, ofGetWindowHeight()/2));
	_TextCurveSlider.setDrawRotate(-50);
}

//--------------------------------------------------------------
void Arcadyan::onTextSlider(bool& e)
{
	//ofxVideoElement*	pMilestonLoop_ = nullptr;
	//_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_MilestoneVideoLoop, pMilestonLoop_);
	//pMilestonLoop_->StopVideo();

	//_Arcadyan.playCityLoop();
	_Arcadyan._Director.TransitTo(TRANSITION_TYPE::eTRANSITION_FADE);
}