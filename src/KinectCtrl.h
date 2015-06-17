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

	bool getCtrlPos(ofVec2f& refRightHandPos);
	void drawBody(ofPoint Pos, int iWidth, int iHeight);

public:
	inline bool getSetup()
	{
		return _bIsSetup;
	}

	inline bool getHaveUser()
	{
		return _bHaveUser;
	}

private:
	bool		_bIsSetup;
	bool		_bDisplayBody;

	ofVec2f		_RightHandPos;
	ofImage		_BodyIndex;

	bool		_bHaveUser;
	ofVec2f		_CtrlPos;
	CTKinectV2	_CTKinect;

///////////////////////////////
//RGB
///////////////////////////////
public:
	bool getRGBCam(ofImage& refDisplay)
	{
		return _CTKinect.getColorFrame(refDisplay);
	}
public:
	inline void setRGBCam(bool bValue)
	{
		bValue?_CTKinect.enableColorFrame():_CTKinect.disableColorFrame();
	}

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
