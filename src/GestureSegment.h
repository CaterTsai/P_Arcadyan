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
//Gesture:Right Hand up
///////////////////////////////////////
class RightHandUpSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class RightHandUpSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};
///////////////////////////////////////
//Gesture:Right Hand down
///////////////////////////////////////
class RightHandDownSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class RightHandDownSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

///////////////////////////////////////
//Gesture:Left Hand up
///////////////////////////////////////
class LeftHandUpSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class LeftHandUpSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};
///////////////////////////////////////
//Gesture:Left Hand down
///////////////////////////////////////
class LeftHandDownSegment1 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};

class LeftHandDownSegment2 : public IGestureSegment
{
	eGestureCheckResult	CheckGesture(const stSCREEN_SKELETON&);
};
#endif //KINECT_GEATURE_SEGMENT