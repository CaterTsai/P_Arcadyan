#include "Arcadyan.h"

#pragma region Base Method
//--------------------------------------------------------------
void Arcadyan::setup()
{
	ofBackground(255);
	ofSetVerticalSync(true);
	
	//Video Manager
	this->InitialVideoManager();

	//Timeline Subtitle
	this->InitialSubtitle("xml/_SubtitleData.xml");

	//Image Slider
	this->InitialImageSlider();

	//GB Ctrl
	_bStartMove = false;
	_GreenBuildingCtrl.setupGreenBuildingCtrl();
	ofAddListener(_GreenBuildingCtrl._GreenBuildingEvent, this, &Arcadyan::onGreenBuildingExit);

	//Text Slider
	this->InitialTextSlider();
	ofAddListener(_TextCurveSlider.TextSliderFinishEvent, this, &Arcadyan::onTextSlider);

	//Photo Frame Slider
	_PhotoFrameSlider.setupVirticalSlider(ofRectangle(0, 0, 1024, 250), (cSMALL_PHOTO_WIDTH * cSMALL_PHOTO_SCALE) + 90);
	ofAddListener(_PhotoFrameSlider._VerticalSliderEvent, this, &Arcadyan::onPhotoFrameChange);

	//Theatre
	_Arcadyan.setupTheatre();
	ofAddListener(_Arcadyan.ArcadyanTheaterEvent, this, &Arcadyan::onArcadyanTheaterEvent);

	//Kinect Ctrl
	_KinectCtrl.setupKinectCtrl();
	ofAddListener(GestureEventArgs::_event, this, &Arcadyan::OnGestureEvent);
	_DisplayBody = true;
	_bHaveUser = false;

	//Info Display
	_InfoDisplay.setupInfoDisplay();
	_InfoDisplay.getNowWeatherInfo();
	ofAddListener(_InfoDisplay.FinishEvent, this, &Arcadyan::onInfoDisplay);

	//Audio & BGM
	this->setupAudioMgr();
	AudioMgr::GetInstance()->playBGM(NAME_MANAGER::BGM_OPEN);

	_VideoMgr.play();
	_SubtitleMgr.start();
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
	if(_KinectCtrl.getSetup())
	{
		_KinectCtrl.updateKinectCtrl();
		if(!_bHaveUser && _KinectCtrl.getHaveUser())
		{
			_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_SwingTipsFadein);
			_KinectCtrl.startGestureCheck(NAME_MANAGER::G_HAND_UP);
			_KinectCtrl.startGestureCheck(NAME_MANAGER::G_WAVE_HAND);
		}
		else if(_bHaveUser && !_KinectCtrl.getHaveUser())
		{
			_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_SwingTipsFadeout);
			_KinectCtrl.stopGesutreCheck();
		}
		_bHaveUser = _KinectCtrl.getHaveUser();
	}
	
	ofVec2f CtrlPos_;
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
		_PhotoFrameSlider.updateVirticalSlider(fDelta_, CtrlPos_);

		//Get Kinect RGB camera Image
		ofxDynamicImageElement* pDynamicPtr_ = nullptr;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_CamDisplay, pDynamicPtr_);

		ofImage Display_;
		_KinectCtrl.getRGBCam(Display_);
		pDynamicPtr_->updateImg(Display_);
	}

	//Update Timeline Subtitle
	if(_bFollowVideo)
	{
		_SubtitleMgr.updateInTime(fDelta_, _VideoMgr.getNowTime());
	}
	else
	{
		_SubtitleMgr.update(fDelta_);
	}

	//Theatre
	_Arcadyan.updateTheatre(fDelta_, CtrlPos_);

	//Audio & BGM
	AudioMgr::GetInstance()->update();

	//Show FPS
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void Arcadyan::draw()
{
	this->drawBeforeTheatre();
	_Arcadyan.drawTheatre();
	this->drawAfterTheatre();
}

//--------------------------------------------------------------
void Arcadyan::exit()
{
	_KinectCtrl.exitKinectCtrl();
}

//--------------------------------------------------------------
void Arcadyan::keyPressed(int key)
{
	switch(key)
	{
	case 'b':
		{
			_DisplayBody ^= true;
			break;
		}
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

			//BGM change
			AudioMgr::GetInstance()->playBGM(NAME_MANAGER::BGM_INTRO);

			ofxVideoElement*	pVideoElement_;
			_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
			pVideoElement_->StopVideo();
		}
		break;
	case 'z':
		{
			//Start take picture
			ofxAnimationImageElement* pCountdown_;
			_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_TakePictureCountdown, pCountdown_);
			pCountdown_->PlayAnimation();
			pCountdown_->SetVisible(true);

			//Stop photo frame slider
			_PhotoFrameSlider.setCanMove(false);
			_PhotoFrameSlider.setDisplay(false);

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
			if(_PhotoFrameSlider.toRight())
			{
				_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
			}			
		}
		break;
	case 'l':
		{
			if(_PhotoFrameSlider.toLeft())
			{
				_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
			}
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
#pragma endregion

#pragma region Theatre
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

		if(_DisplayBody)
		{
			_KinectCtrl.drawBody(ofPoint(0, WINDOW_HEIGHT - cKINECT_BODY_HEIGHT), cKINECT_BODY_WIDTH, cKINECT_BODY_HEIGHT);
		}
	}
	else if(strScenesName_ == NAME_MANAGER::S_Milestone)
	{
		_TextCurveSlider.drawCurveSlider();

		if(_DisplayBody)
		{
			_KinectCtrl.drawBody(ofPoint(0, WINDOW_HEIGHT - cKINECT_BODY_HEIGHT), cKINECT_BODY_WIDTH, cKINECT_BODY_HEIGHT);
		}
	}
	else if(strScenesName_ == NAME_MANAGER::S_TakePicture)
	{
		_PhotoFrameSlider.drawVirticalSlider(448, 703);
	}

	_SubtitleMgr.draw();
}

//--------------------------------------------------------------
void Arcadyan::onArcadyanTheaterEvent(string& e)
{
	if(e == NAME_MANAGER::T_DoorIsOpen)
	{
		_InfoDisplay.startDisplay(1.5);
	}
	else if(e == NAME_MANAGER::T_Greenbuilding_Show)
	{
		_GreenBuildingCtrl.startGreenBuidling();
	}
	else if(e == NAME_MANAGER::T_PlayMilestone)
	{
		_TextCurveSlider.startCurveSlider();

		_KinectCtrl.startGestureCheck(NAME_MANAGER::G_HAND_UP);
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

		//Start Kinect RGB camera
		_KinectCtrl.setRGBCam(true);
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
	else if(e == NAME_MANAGER::T_TakePhoto)
	{
		this->takePicture();
	}
	else if(e == NAME_MANAGER::T_StartEnding)
	{
		
	}
	else if(e == NAME_MANAGER::T_Ending)
	{
		this->resetTheatre();
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

	//Subtitle
	this->resetSubtitle();

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

	//Change BGM
	AudioMgr::GetInstance()->playBGM(NAME_MANAGER::BGM_OPEN);

	_bHaveUser = false;
}
#pragma endregion

#pragma region Kinect
void Arcadyan::OnGestureEvent(GestureEventArgs &e)
{
	if(e._strGesutreName == NAME_MANAGER::G_WAVE_HAND)
	{
		_VideoMgr.next();

		ofxVideoElement*	pVideoElement_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
		pVideoElement_->StopVideo();

		_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_SwingTipsFadeout);

		_KinectCtrl.stopGesutreCheck();

		AudioMgr::GetInstance()->playBGM(NAME_MANAGER::BGM_INTRO);
	}
	else if(e._strGesutreName == NAME_MANAGER::G_OPEN)
	{
		_Arcadyan.OpenTheGate();

		ofxVideoElement*	pVideoElement_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_GateOpenTips, pVideoElement_);
		pVideoElement_->StopVideo();

		_KinectCtrl.stopGesutreCheck();
	}
	else if(e._strGesutreName == NAME_MANAGER::G_HAND_UP)
	{
		_TextCurveSlider.RotateToForward();
		_KinectCtrl.stopGesutreCheck();
		_KinectCtrl.startGestureCheck(NAME_MANAGER::G_HAND_DOWN);
	}
	else if(e._strGesutreName == NAME_MANAGER::G_HAND_DOWN)
	{
		_TextCurveSlider.RotateToBackward();
		_KinectCtrl.stopGesutreCheck();
		_KinectCtrl.startGestureCheck(NAME_MANAGER::G_HAND_UP);
	}
	
}
#pragma endregion

#pragma region Timeline Subtitle
//--------------------------------------------------------------
void Arcadyan::InitialSubtitle(string strFilename)
{
	_backplane.loadImage("images/backplane2.png");
	_SubtitleCreater.setSubtitleColor(ofColor(255));
	_SubtitleCreater.setSubtitleFont("fonts/msjhbd.ttf", SUBTITLE_FONT_SIZE);
	_bFollowVideo = true;
	ofxXmlSettings	xml_;
	if(!xml_.loadFile(strFilename))
	{
		ofLog(OF_LOG_ERROR, "[Timeline]Load timeline slider failed");
		return;
	}

	//Subtitle - TEXT
	int iTextNum_ = xml_.getNumTags("SUBTITLE_TEXT");
	for(int idx_ = 0; idx_ < iTextNum_; ++idx_)
	{
		string strSubtitle_ = xml_.getValue("SUBTITLE_TEXT:TEXT", "", idx_);
		float fTrigger_ = xml_.getValue("SUBTITLE_TEXT:TRIGGER", 0.0, idx_);
		float fLength_ = xml_.getValue("SUBTITLE_TEXT:LENGTH", 0.0, idx_);

		ofImage Img_;
		_SubtitleCreater.Subtitle2Image(strSubtitle_, Img_, _backplane);
		_SubtitleMgr.addElement(ofPtr<ImageTimelineElement>(new ImageTimelineElement(Img_, ofVec2f(WINDOW_WIDTH/2, WINDOW_HEIGHT - Img_.height - 50), fTrigger_, fLength_)));
	}

	//Subtitle - AUDIO
	//int iAudioNum_ = xml_.getNumTags("SUBTITLE_AUDIO");
	//for(int idx_ = 0; idx_ < iAudioNum_; ++idx_)
	//{
	//	string strSubtitle_ = xml_.getValue("SUBTITLE_AUDIO:FILE_NAME", "", idx_);
	//	float fTrigger_ = xml_.getValue("SUBTITLE_AUDIO:TRIGGER", 0.0, idx_);

	//	ofSoundPlayer Audio_;
	//	Audio_.loadSound("audios" + strSubtitle_);
	//	_SubtitleMgr.addElement(ofPtr<AudioTimelineElement>(new AudioTimelineElement(Audio_, fTrigger_)));
	//}
}

//--------------------------------------------------------------
void Arcadyan::resetSubtitle()
{
	_SubtitleMgr.reset();
	_bFollowVideo = true;
	_SubtitleMgr.start();
}

#pragma endregion

#pragma region Video Manager
//--------------------------------------------------------------
void Arcadyan::InitialVideoManager()
{
	_VideoMgr.addVideoWithSourcePlayer("videos/intro_loop.mov", "V_IntroLoop", true);
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

		_bFollowVideo = false;

		//Play BGM
		AudioMgr::GetInstance()->playBGM(NAME_MANAGER::BGM_MAIN);

		//Kinect gesture check
		_KinectCtrl.startGestureCheck(NAME_MANAGER::G_OPEN);
	}
	else if(e == "V_IntroLoop")
	{
		//ofxVideoElement*	pVideoElement_;
		//_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_OpenTips, pVideoElement_);
		//pVideoElement_->PlayVideo();

		//Kinect gesture check

	}
	else if(e == "V_SliderLoop")
	{
		_ImgSlider.StartSlider();
	}
}
#pragma endregion

#pragma region Slider
//--------------------------------------------------------------
//Image Slider
void Arcadyan::InitialImageSlider()
{
	_fImgRotateX = 0.0;
	_fImgRotateY = 10.0;
	_ImgSlider.SetupImageSlider("xml/_ImageSliderData.xml", ofPoint(750, ofGetHeight()/2 + WINDOW_HEIGHT, 0), WINDOW_HEIGHT, 2.0);
}

//--------------------------------------------------------------
//Text Curve Slider
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
	_KinectCtrl.stopGesutreCheck();

	_Arcadyan._Director.TransitTo(TRANSITION_TYPE::eTRANSITION_FADE);
}

//--------------------------------------------------------------
//Photo Frame Slider
void Arcadyan::takePicture()
{
	ofImage PhotoFrame_, Photo_, MixResult_;
	ofxDynamicImageElement* pCamDisplay_ = nullptr;
	ofxDynamicImageElement* pPhoto_ = nullptr;

	_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_CamDisplay, pCamDisplay_);
	_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_Photo, pPhoto_);

	//get webcam image
	pCamDisplay_->getImage(Photo_);
	//pWebcam_->getImage(Photo_);

	//get photo frame
	_PhotoFrameSlider.getNowImage(PhotoFrame_);

	//mix the photo
	ofFbo	Canvas_;
	Canvas_.allocate(Photo_.getWidth(), Photo_.getHeight(), GL_RGBA);
	Canvas_.begin();
	{
		ofPushStyle();
		ofSetColor(255);

		Photo_.draw(0, 0);		
		PhotoFrame_.draw(0, 0);
		ofPopStyle();
	}
	Canvas_.end();

	ofPixels pix_;
	Canvas_.readToPixels(pix_);
	MixResult_.setFromPixels(pix_.getPixels(), Canvas_.getWidth(), Canvas_.getHeight(), OF_IMAGE_COLOR_ALPHA);
	
	pPhoto_->updateImg(MixResult_);
	pPhoto_->SetVisible(true);

	//save the photo
	string strPhotoName_ = ofGetTimestampString("photos/%Y%m%d_%H%M.png");
	MixResult_.saveImage(strPhotoName_);
}

//--------------------------------------------------------------
void Arcadyan::onPhotoFrameChange(string& e)
{
	if(e == "toLeft")
	{
		_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
	}
	else if(e == "toRight")
	{
		_Arcadyan.TheatreAnimInit(NAME_MANAGER::INIT_PhotoFrameChange);
	}
	else if(e == "takePicture")
	{
		//Start take picture
		ofxAnimationImageElement* pCountdown_;
		_Arcadyan._Director.GetElementPtr(NAME_MANAGER::E_TakePictureCountdown, pCountdown_);
		pCountdown_->PlayAnimation();
		pCountdown_->SetVisible(true);

		//Stop photo frame slider
		_PhotoFrameSlider.setCanMove(false);
		_PhotoFrameSlider.setDisplay(false);
	}
}
#pragma endregion

#pragma region Info display
//--------------------------------------------------------------
void Arcadyan::onInfoDisplay(bool& e)
{
	_Arcadyan._Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
}
#pragma endregion

#pragma region Green Building Ctrl
//--------------------------------------------------------------
void Arcadyan::onGreenBuildingExit(bool& e)
{
	if(_Arcadyan._Director.GetNowScenes()->GetScenesName() == NAME_MANAGER::S_GreenBuilding)
	{
		_Arcadyan._Director.TransitTo(eTransitionsType::eTRANSITION_FADE);
		_GreenBuildingCtrl.stopGreenBuidling();
		_Arcadyan.playCityLoop();
	}
}
#pragma endregion

#pragma region Audio & BGM
//--------------------------------------------------------------
void Arcadyan::setupAudioMgr()
{
	AudioMgr::GetInstance()->addBGM(NAME_MANAGER::BGM_OPEN, "audios/bgm_open.mp3");
	AudioMgr::GetInstance()->addBGM(NAME_MANAGER::BGM_INTRO, "audios/bgm_intro.mp3");
	AudioMgr::GetInstance()->addBGM(NAME_MANAGER::BGM_MAIN, "audios/bgm_main.mp3");
}
#pragma endregion
