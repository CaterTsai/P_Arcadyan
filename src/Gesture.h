#ifndef KINECT_GESTURE
#define KINECT_GESTURE

#include "protocol.h"
#include "GestureSegment.h"

typedef vector<shared_ptr<IGestureSegment>> GestureSegmentList;


///////////////////////////////////////
//@class Gesture
///////////////////////////////////////
class Gesture
{
public:
	Gesture(string strName, const GestureSegmentList& SementList):
		_strGestureName(strName),
		_SegmentList(SementList),
		_iNowGestureState(0),
		_iPauseCounter(0),
		_fCheckTimer(BASE_CHECK_TIME)
	{};

	void UpdateGesture(const float fDelta_, const stSCREEN_SKELETON&);
	void ResetGesture();

public:
	inline string getGestureName() const
	{
		return _strGestureName;
	}

private:
	string						_strGestureName;
	int							_iNowGestureState;
	int							_iPauseCounter;
	float						_fCheckTimer;
	GestureSegmentList			_SegmentList;
};

///////////////////////////////////////
//@class GestureEventArgs
///////////////////////////////////////
class GestureEventArgs : public ofEventArgs
{
public:
	string								_strGesutreName;
	static ofEvent<GestureEventArgs>	_event;
};
#endif //KINECT_GESTURE