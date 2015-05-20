#ifndef ARCADYAN_KINECT_CTRL
#define ARCADYAN_KINECT_CTRL

#include "protocol.h"
#include "ofxCTKinectV2.h"
#include "GestureManager.h"

const float	BASE_KINECT_WIDTH = 100.0;
const float	BASE_KINECT_HEIGHT = 80.0;

class KinectCtrl
{
public:
	KinectCtrl()
		:_bIsSetup(false)
		,_bHaveUser(false)
		,_bDisplayBody(false)
	{}

	void setupKinectCtrl();
	void updateKinectCtrl();
	void drawKinectCtrl();
	void exitKinectCtrl();

	bool getCtrlPos(ofVec2f refRightHandPos);
	void drawBody(ofPoint Pos, int iWidth, int iHeight);

private:
	bool		_bIsSetup;
	bool		_bDisplayBody;

	ofVec2f		_RightHandPos;
	ofImage		_BodyIndex;

	bool		_bHaveUser;
	ofVec2f		_CtrlPos;
	CTKinectV2	_CTKinect;

///////////////////////////////
//Gesture
///////////////////////////////
public:
	void setupGesture();
	void startGestureCheck(const string& strGesutreName);
	void stopGesutreCheck();
private:
	GestureManager	_GestureMgr;
};


#endif // !ARCADYAN_KINECT_CTRL
