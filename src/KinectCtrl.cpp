#include "KinectCtrl.h"

#pragma region Base Method
void KinectCtrl::setupKinectCtrl()
{
	_CTKinect.startThread();
	if(_CTKinect.initialKinectV2())
	{
		_bIsSetup = true;

		_CTKinect.enableSkeleton();
		_CTKinect.enableBodyIndex();
		this->setupGesture();
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
	
	ofVec2f Center_(stSkeleton_.aJoints[JointType::JointType_ShoulderLeft].x, stSkeleton_.aJoints[JointType::JointType_Head].y);
	float fDetectionWidth_ = (stSkeleton_.aJoints[JointType::JointType_ShoulderRight].x - stSkeleton_.aJoints[JointType::JointType_ShoulderLeft].x) * 1.8;
	float fDetectcionHeight_ = stSkeleton_.aJoints[JointType::JointType_SpineMid].y - stSkeleton_.aJoints[JointType::JointType_Head].y;
	Center_.x += fDetectionWidth_/2;
	Center_.y += fDetectcionHeight_/2;

	ofVec2f RightHand_ = stSkeleton_.aJoints[JointType::JointType_HandRight];

	_CtrlPos = RightHand_ - Center_;
	_CtrlPos.x = ofMap(_CtrlPos.x, -fDetectionWidth_/2, fDetectionWidth_/2, 0, WINDOW_WIDTH);
	_CtrlPos.y = ofMap(_CtrlPos.y, -fDetectcionHeight_/2, fDetectcionHeight_/2, 0, WINDOW_HEIGHT);

	//Gesture
	_GestureMgr.UpdateGestureManager(stSkeleton_);
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
bool KinectCtrl::getCtrlPos(ofVec2f& refRightHandPos)
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
#pragma endregion

#pragma region Gesture
void KinectCtrl::setupGesture()
{
	_GestureMgr.SetupGestureManager();

	//Open
	GestureSegmentList OpenSegmentList_;
	//OpenSegmentList_.push_back( make_shared<OpenSegment1>() );
	OpenSegmentList_.push_back( make_shared<OpenSegment2>() );
	OpenSegmentList_.push_back( make_shared<OpenSegment3>() );
	_GestureMgr.AddGesture(NAME_MANAGER::G_OPEN, OpenSegmentList_);

	//Wave
	GestureSegmentList WaveRightSegmentList_;
	WaveRightSegmentList_.push_back( make_shared<WaveRightSegment1>() );
	WaveRightSegmentList_.push_back( make_shared<WaveRightSegment2>() );
	WaveRightSegmentList_.push_back( make_shared<WaveRightSegment1>() );
	WaveRightSegmentList_.push_back( make_shared<WaveRightSegment2>() );
	_GestureMgr.AddGesture(NAME_MANAGER::G_WAVE_HAND, WaveRightSegmentList_);

	////Hand up
	//GestureSegmentList	RightHandUpSegmentList_;
	////RightHandUpSegmentList_.push_back( make_shared<RightHandUpSegment1>() );
	//RightHandUpSegmentList_.push_back( make_shared<RightHandUpSegment2>() );
	//_GestureMgr.AddGesture(NAME_MANAGER::G_HAND_UP, RightHandUpSegmentList_);

	////Hand down
	//GestureSegmentList	RightHandDownSegmentList_;
	////RightHandDownSegmentList_.push_back( make_shared<RightHandDownSegment1>() );
	//RightHandDownSegmentList_.push_back( make_shared<RightHandDownSegment2>() );
	//_GestureMgr.AddGesture(NAME_MANAGER::G_HAND_DOWN, RightHandDownSegmentList_);
}

//--------------------------------------------------------------
void KinectCtrl::startGestureCheck(const string& strGesutreName)
{
	_GestureMgr.startCheck(strGesutreName);
}

//--------------------------------------------------------------
void KinectCtrl::stopGesutreCheck()
{
	_GestureMgr.stopCheck();
}
#pragma endregion

