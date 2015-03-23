#include "GreenbuildingCtrl.h"

void GreenBuildingCtrl::setupGreenBuildingCtrl()
{
	//_GreenBuilding.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
	_GreenBuilding.setLoopState(ofLoopType::OF_LOOP_NONE);
	_GreenBuilding.loadMovie("videos/Greenbuilding_control.mov");
	_iTotalFrame = _GreenBuilding.getTotalNumFrames();

	_GreenBuildingLight.setPlayer(ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer));
	_GreenBuildingLight.setPixelFormat(ofPixelFormat::OF_PIXELS_RGBA);
	_GreenBuilding.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	_GreenBuildingLight.loadMovie("videos/Greenbuilding_nearlight.mov");

	_ArrowLeft.loadImage("images/ArrowLeft.png");
	_ArrowRight.loadImage("images/ArrowRight.png");


	_bIsStart = false;
	_bIsRotate = false;
}

//--------------------------------------------------------------
void GreenBuildingCtrl::updateGreenBuildingCtrl(float fDelta, ofPoint CtrlPos)
{
	if(!_bIsStart)
	{
		return;
	}

	_GreenBuilding.update();
	_GreenBuildingLight.update();

	if(CtrlPos.x >= 0 && CtrlPos.x < 250)
	{
		this->startRotate(true);
	}
	else if(CtrlPos.x < 1920 && CtrlPos.x > 1670)
	{
		this->startRotate(false);
	}
	else
	{
		this->stopRotate();
	}
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
		_GreenBuilding.draw(0, 0);

		ofEnableAlphaBlending();
		_GreenBuildingLight.draw(0, 0);

		_ArrowLeft.draw(100, ofGetWindowHeight()/2 - _ArrowLeft.height/2);
		_ArrowRight.draw(1820 - _ArrowRight.width, ofGetWindowHeight()/2 - _ArrowRight.height/2);
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
	_GreenBuilding.play();
	_GreenBuilding.setSpeed(0.0);
	_GreenBuildingLight.play();
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
	_GreenBuildingLight.stop();
}

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