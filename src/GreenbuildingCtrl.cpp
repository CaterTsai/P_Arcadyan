#include "GreenbuildingCtrl.h"

#pragma region Base Methon
void GreenBuildingCtrl::setupGreenBuildingCtrl()
{
	//_GreenBuildingLoop.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
	//_GreenBuildingLoop.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	_GreenBuildingLoop.loadMovie("videos/Greenbuilding_loop.mov");

	_GreenBuilding.setPlayer(ofPtr<ofxHapPlayer>(new ofxHapPlayer));
	_GreenBuilding.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	_GreenBuilding.loadMovie("videos/Greenbuilding_control.mov");
	_iTotalFrame = _GreenBuilding.getTotalNumFrames();

	_GreenBuildingLight.setPlayer(ofPtr<ofxHapPlayer>(new ofxHapPlayer));
	_GreenBuildingLight.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	_GreenBuildingLight.loadMovie("videos/Greenbuilding_nearlight.mov");

	_ArrowAlpha.setDuration(1.5);
	_ArrowAlpha.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	
	//_ArrowLeft.loadImage("images/ArrowLeft.png");
	//_ArrowRight.loadImage("images/ArrowRight.png");
	_Arrow.loadImage("images/greenBuildingArrow.png");
	_ArrowLight.loadImage("images/greenBuildingArrow_Light.png");

	_ExitRect.set(1680, 936, 206, 126);
	_fExitCounter = cGREEN_BUILDING_EXIT_TIME;

	//Image Control
	this->initialImageList("xml/_GreenBuildingImageData.xml");

	_bIsStart = false;
	_bIsRotate = false;
	_bFlip = false;

#ifdef TIMEOUT_MODE
	_bStartTimer = false;
#endif // TIMEOUT_MODE
}

//--------------------------------------------------------------
void GreenBuildingCtrl::updateGreenBuildingCtrl(float fDelta, ofPoint CtrlPos)
{
	if(!_bIsStart)
	{
		return;
	}
	_GreenBuilding.update();
	_GreenBuildingLoop.update();
	_GreenBuildingLight.update();

	_ArrowAlpha.update(fDelta);

	if(!_bFlip)
	{
		_GreenBuildingLoop.play();
		_bFlip = true;
	}

	//Image Control
	this->updateImage(fDelta, _GreenBuilding.getCurrentFrame());

	//Exit check
	if(_ExitRect.inside(CtrlPos))
	{
		this->stopRotate();
		_fExitCounter -= fDelta;
		if(_fExitCounter <= 0.0)
		{
			bool bValue_ = true;
			ofNotifyEvent(_GreenBuildingEvent, bValue_);
		}
		return;
	}
	else
	{
		_fExitCounter = cGREEN_BUILDING_EXIT_TIME;
	}

	//Rotate check
	if(CtrlPos.x >= 0 && CtrlPos.x <= WINDOW_WIDTH/4)
	{
		this->startRotate(true);
	}
	else if(CtrlPos.x < WINDOW_WIDTH && CtrlPos.x > WINDOW_WIDTH - WINDOW_WIDTH/4)
	{
		this->startRotate(false);
	}
	else
	{
		this->stopRotate();
	}

#ifdef TIMEOUT_MODE
	if(_bStartTimer)
	{
		_fDebugTimer -= fDelta;
		if(_fDebugTimer < 0.0)
		{
			this->stopRotate();
			bool bValue_ = true;
			ofNotifyEvent(_GreenBuildingEvent, bValue_);

			_bStartTimer = false;
		}
	}
#endif // TIMEOUT_MODE


}

//--------------------------------------------------------------
void GreenBuildingCtrl::drawGreenBuildingCtrl()
{
	if(!_bIsStart)
	{
		return;
	}

	ofPushStyle();
	{
		ofSetColor(255);
		ofDisableBlendMode();		
		if(_bFlip)
		{
			_GreenBuildingLoop.draw(0, 0);
		}

		ofEnableAlphaBlending();
		_GreenBuilding.draw(0, 0);
		_GreenBuildingLight.draw(0, 0);

		//Image List
		this->drawImage();

		//UI
		_Arrow.draw(0, 0);

		ofSetColor(255, _ArrowAlpha.getCurrentValue());
		_ArrowLight.draw(0, 0);
		//_ArrowLeft.draw(WINDOW_WIDTH/6 - _ArrowRight.width/2, 735 - _ArrowLeft.height/2);
		//_ArrowRight.draw((1920 - WINDOW_WIDTH/6) - _ArrowRight.width/2, 735 - _ArrowRight.height/2);

	}
	ofPopStyle();
}

//--------------------------------------------------------------
void GreenBuildingCtrl::startGreenBuidling()
{
	if(_bIsStart)
	{
		return;
	}

	_bIsStart = true;
	_bIsRotate = true;
	_bFlip = false;
	_GreenBuilding.play();
	_GreenBuilding.setFrame(0);
	_GreenBuilding.update();
	_GreenBuilding.setSpeed(0.0);
	
	_GreenBuildingLight.play();
	_ArrowAlpha.animateFromTo(0, 255);
	this->resetImage();

#ifdef TIMEOUT_MODE
	_bStartTimer = true;
	_fDebugTimer = cGREEN_OUT_TIMEOUT;
#endif // TIMEOUT_MODE
}

//--------------------------------------------------------------
void GreenBuildingCtrl::stopGreenBuidling()
{
	if(!_bIsStart)
	{
		return;
	}

	_bIsStart = false;
	_GreenBuilding.setFrame(0);
	_GreenBuilding.update();
	_GreenBuilding.stop();

	_GreenBuildingLoop.stop();
	_GreenBuildingLight.stop();
}
#pragma endregion

#pragma region Rotate & Control
//--------------------------------------------------------------
void GreenBuildingCtrl::startRotate(bool bIsLeft)
{
	_GreenBuilding.setPaused(false);
	
	if(bIsLeft)
	{
		_GreenBuilding.setSpeed(-1.0);
	}
	else
	{
		_GreenBuilding.setSpeed(1.0);
	}
}

//--------------------------------------------------------------
void GreenBuildingCtrl::stopRotate()
{
	_GreenBuilding.setPaused(true);
}
#pragma endregion

#pragma region Image Control
//--------------------------------------------------------------
void GreenBuildingCtrl::initialImageList(string strXMLName)
{
	ofxXmlSettings	xmlLoader_;
	if(!xmlLoader_.loadFile(strXMLName))
	{
		ofLog(OF_LOG_ERROR, "Load image slider failed");
		return;
	}

	xmlLoader_.pushTag("ARCADYAN_GREEN_BUILDING_IMAGE");
	int iNum_ = xmlLoader_.getNumTags("IMAGE_SET");

	for(int idx_ = 0; idx_ < iNum_; ++idx_)
	{
		string strImgPath_ = xmlLoader_.getValue("IMAGE_SET:IMAGE_PATH", "", idx_);
		int iTF1_ = xmlLoader_.getValue("IMAGE_SET:T_FRAME_1", 0, idx_);
		int iTF2_ = xmlLoader_.getValue("IMAGE_SET:T_FRAME_2", 0, idx_);

		ImageSet Tmp_(strImgPath_, iTF1_, iTF2_);
		_ImageList.push_back(Tmp_);
	}

	_ImgSize.set(0, 0, 388, 320);
	_DrawPos.set(1651, 493, 0);

}

//--------------------------------------------------------------
void GreenBuildingCtrl::updateImage(float fDelta, int iNowFrame)
{
	for(auto& Iter_ : _ImageList)
	{
		bool bInTriggerArea_ = (Iter_.iTriggerFrame1 <= iNowFrame && Iter_.iTriggerFrame2 >= iNowFrame);
		if(Iter_.eState == eIMAGE_DISPLAY && !bInTriggerArea_)
		{
			//Fade out
			Iter_.eState = eIMAGE_FADEOUT;
			Iter_._AnimAlpha.animateFromTo(255, 0);
		}
		else if(Iter_.eState == eIMAGE_DISABLE && bInTriggerArea_)
		{
			//Fade in
			Iter_.eState = eIMAGE_FADEIN;
			Iter_._AnimAlpha.animateFromTo(0, 255);
		}
		Iter_.update(fDelta);
	}
}

//--------------------------------------------------------------
void GreenBuildingCtrl::drawImage()
{
	ofPushStyle();
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(_DrawPos);
	ofRotateY(-12);
	{
		for(auto& Iter_ : _ImageList)
		{
			if(Iter_.eState != eIMAGE_DISABLE)
			{
				ofSetColor(255, Iter_._AnimAlpha.getCurrentValue());
				Iter_.Img.draw(-_ImgSize.width/2, -_ImgSize.height/2, _ImgSize.width, _ImgSize.height);
			}
		}
	}
	ofPopMatrix();
	ofPopStyle();	
}

//--------------------------------------------------------------
void GreenBuildingCtrl::resetImage()
{
	for(auto& Iter_ : _ImageList)
	{
		Iter_.eState = eIMAGE_DISABLE;
	}
}
#pragma endregion