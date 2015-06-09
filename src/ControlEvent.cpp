#include "ControlEvent.h"

//------------------------
//@CLASS TouchControlEvent
//------------------------
TouchControlEvent::TouchControlEvent(string strEventName):
	BaseControlEvent(strEventName),
	_bIsSetup(false)
{}

//--------------------------------------------------------------
TouchControlEvent::TouchControlEvent(ofImage& CtrlImg, string strEventName):
	BaseControlEvent(CtrlImg, strEventName),
	_bIsSetup(false)
{}

//--------------------------------------------------------------
void TouchControlEvent::updateControlEvent(ofPoint CtrlPos)
{
	if(!_bIsDisplay || !_bIsSetup)
	{
		return;
	}

	//update the control position
	_CtrlPos.set(CtrlPos);

	//check for touch
	if(!_bIsTrigger && _TargetArea.inside(CtrlPos))
	{
		_bIsTrigger = true;
		ofNotifyEvent(ControlEvent, _strEventName);
	}
}

//--------------------------------------------------------------
void TouchControlEvent::drawControlEvent()
{
	if(!_bIsDisplay || !_bIsSetup)
	{
		return;
	}

	ofPushStyle();
	ofEnableAlphaBlending();

	ofSetColor(255);
	
	if(_TargetImg.isAllocated())
	{
		_TargetImg.draw(_TargetArea);
	}

	if(_bHaveCtrlDisplay)
	{
		_CtrlImg.draw(_CtrlPos.x - _CtrlImg.width/2, _CtrlPos.y - _CtrlImg.height/2);
	}

	ofPopStyle();
}

//--------------------------------------------------------------
void TouchControlEvent::resetControlEvent()
{
	_bIsTrigger = false;
	this->setDisplay(false);
}

//--------------------------------------------------------------
void TouchControlEvent::setupTouchTarget(ofImage& TargetImg, ofPoint TargetPos)
{
	_TargetImg.clone(TargetImg);
	_TargetArea.setFromCenter(TargetPos, TargetImg.width, TargetImg.height);
	_bIsSetup = true;
}

//--------------------------------------------------------------
void TouchControlEvent::setupTouchTarget(ofRectangle TargetArea)
{
	_TargetArea.set(TargetArea);
	_bIsSetup = true;
}

//------------------------
//@CLASS DragControlEvent
//------------------------
DragControlEvent::DragControlEvent(string strEventName):
	BaseControlEvent(strEventName),
	_bIsSetup(false),
	_bIsTouch(false)
{}

//--------------------------------------------------------------
DragControlEvent::DragControlEvent(ofImage& CtrlImg, string strEventName):
	BaseControlEvent(CtrlImg, strEventName),
	_bIsSetup(false),
	_bIsTouch(false)
{}

//--------------------------------------------------------------
void DragControlEvent::updateControlEvent(ofPoint CtrlPos)
{
	if(!_bIsDisplay || !_bIsSetup)
	{
		return;
	}

	//update the control position
	_CtrlPos.set(CtrlPos);

	
	if(_bIsTrigger)
	{
		return;
	}

	if(!_bIsTouch)
	{
		//check for touch
		if(_TouchArea.inside(CtrlPos))
		{
			_bIsTouch = true;
		}
	}
	else
	{
		//update target position
		_TouchArea.setPosition(CtrlPos.x - _TouchArea.width/2, CtrlPos.y - _TouchArea.height/2);

		//check for target area
		if(_TargetArea.inside(CtrlPos))
		{
			_bIsTrigger = true;
			ofNotifyEvent(ControlEvent, _strEventName);
		}
	}
}

//--------------------------------------------------------------
void DragControlEvent::drawControlEvent()
{
	if(!_bIsDisplay || !_bIsSetup)
	{
		return;
	}

	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255);
	
	_TouchImg.draw(_TouchArea);
	if(_bHaveCtrlDisplay)
	{
		_CtrlImg.draw(_CtrlPos.x - _CtrlImg.width/2, _CtrlPos.y - _CtrlImg.height/2);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void DragControlEvent::resetControlEvent()
{
	_bIsTrigger = false;
	_bIsTouch = false;
	this->setDisplay(false);

	_TouchArea.set(_TouchAreaBackup);
}

//--------------------------------------------------------------
void DragControlEvent::setupDragEvent(ofImage& TouchImg, ofPoint TouchPos, ofRectangle TargetArea)
{
	_TouchImg.clone(TouchImg);
	_TouchArea.setFromCenter(TouchPos, TouchImg.width, TouchImg.height);
	_TouchAreaBackup.set(_TouchArea);

	_TargetArea.set(TargetArea);
	
	_bIsSetup = true;
}