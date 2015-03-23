#include "KinectCtrl.h"

void KinectCtrl::setupKinectCtrl()
{
	_CTKinect.startThread();
	if(_CTKinect.initialKinectV2())
	{
		_bIsSetup = true;
		_CTKinect.enableSkeleton();
	}
}

//--------------------------------------------------------------
void KinectCtrl::updateKinectCtrl()
{
	_bHaveUser = false;
	if(!_bIsSetup)
	{
		return;
	}

	//Update ctrl position
	stSCREEN_SKELETON	stSkeleton_;
	if(!_CTKinect.getSkeleton(stSkeleton_))
	{	
		return;
	}
	_bHaveUser = true;
	
	ofVec2f Center_ = stSkeleton_.aJoints[JointType::JointType_SpineShoulder];
	ofVec2f RightHand_ = stSkeleton_.aJoints[JointType::JointType_HandRight];

	_CtrlPos = RightHand_ - Center_;
	_CtrlPos.x = ofMap(_CtrlPos.x, -BASE_KINECT_WIDTH, BASE_KINECT_WIDTH, 0, WINDOW_WIDTH);
	_CtrlPos.y = ofMap(_CtrlPos.y, -BASE_KINECT_HEIGHT, BASE_KINECT_HEIGHT, 0, WINDOW_HEIGHT);
}

//--------------------------------------------------------------
void KinectCtrl::drawKinectCtrl()
{
	if(!_bIsSetup)
	{
		return;
	}

	if(_bHaveUser)
	{
		ofPushStyle();
		{
			ofSetColor(255, 0, 0);
			ofCircle(_CtrlPos, 30);
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void KinectCtrl::exitKinectCtrl()
{
	_CTKinect.stopThread();
}

//--------------------------------------------------------------
bool KinectCtrl::getCtrlPos(ofVec2f refRightHandPos)
{	
	if(!_bIsSetup || !_bHaveUser)
	{
		return false;
	}

	refRightHandPos.set(0);
	refRightHandPos = _CtrlPos;	
	return true;
}

//--------------------------------------------------------------
void KinectCtrl::drawBody(ofPoint Pos, int iWidth, int iHeight)
{
	if(!_bIsSetup)
	{
		return;
	}

	if(_CTKinect.getBodyIndex(_BodyIndex) && _BodyIndex.bAllocated())
	{
		ofPushStyle();
		{
			ofSetColor(255);
			_BodyIndex.draw(Pos, iWidth, iHeight);
		}
		ofPopStyle();
	
	}
}