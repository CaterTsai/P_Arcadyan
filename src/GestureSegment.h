#ifndef KINECT_GESTURE_SEGMENT
#define KINECT_GESTURE_SEGMENT

#include "protocol.h"
#include "ofxCTKinectV2.h"

enum eGestureCheckResult
{
	eGesutreCheck_Success	=	0,
	eGesutreCheck_Pause,
	eGesutreCheck_Fail,
	eGesutreCheck_Unknow,
};

///////////////////////////////////////
//@Interface IGestureSegment
///////////////////////////////////////
class IGestureSegment
{
public:
	IGestureSegment(){};
	 virtual eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&)
	{
		return eGesutreCheck_Unknow;
	}
};

///////////////////////////////////////
//Gesture:Open
///////////////////////////////////////
class OpenSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class OpenSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class OpenSegment3 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Wave Right
///////////////////////////////////////
class WaveRightSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class WaveRightSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Wave Left
///////////////////////////////////////
class WaveLeftSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class WaveLeftSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Swipe Right
///////////////////////////////////////
class SwipeRightSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);

};

class SwipeRightSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Swipe Left
///////////////////////////////////////
class SwipeLeftSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class SwipeLeftSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Swipe Up
///////////////////////////////////////
class SwipeUpSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class SwipeUpSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class SwipeUpSegment3 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Swipe Down
///////////////////////////////////////
class SwipeDownSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class SwipeDownSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class SwipeDownSegment3 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

#endif //KINECT_GEATURE_SEGMENT