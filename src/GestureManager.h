#ifndef KINECT_GESTURE_MANAGER
#define KINECT_GESTURE_MANAGER

#include "protocol.h"
#include "Gesture.h"

typedef list<Gesture> GestureList;

///////////////////////////////////////
//@class GestureManager
///////////////////////////////////////
class GestureManager
{
public:
	void SetupGestureManager();
	void UpdateGestureManager(const stSCREEN_SKELETON&);
	void AddGesture(string stName, GestureSegmentList& SementList);

	void startCheck(const string& Name);
	void stopCheck();

private:
	float			_fTimer;
	GestureList		_GestureList;

	bool			_bStartCheck;
	string			_GestureName;
};

#endif //KINECT_GEATURE_MANAGER