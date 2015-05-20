#include "Gesture.h"

//Event Initial
ofEvent<GestureEventArgs> GestureEventArgs::_event;

///////////////////////////////////////
//@class Gesture
///////////////////////////////////////

void Gesture::UpdateGesture(const float fDelta_, const stSCREEN_SKELETON& stSkeleton)
{
	_fCheckTimer -= fDelta_;

	if(_fCheckTimer > 0.0)
	{
		return;
	}

	switch(_SegmentList[_iNowGestureState]->CheckGesture(stSkeleton))
	{
	case eGesutreCheck_Success:
		{
			if((_iNowGestureState + 1) < _SegmentList.size())
			{
				_iNowGestureState++;
			}
			else
			{
				//Trigger Event
				GestureEventArgs oEvent_;
				oEvent_._strGesutreName = _strGestureName;
				ofNotifyEvent(GestureEventArgs::_event, oEvent_);

				_iNowGestureState = 0;
			}
			_iPauseCounter = 0;
			_fCheckTimer = BASE_CHECK_TIME;
		}
		break;
	case eGesutreCheck_Pause:
		{
			_iPauseCounter++;
			if(_iPauseCounter > PAUSE_COUNTER_LIMT)
			{
				_iPauseCounter = 0;
				_iNowGestureState = 0;
				_fCheckTimer = BASE_CHECK_TIME;
			}
		}
		break;
	case eGesutreCheck_Fail:
		{
			_iPauseCounter = 0;
			_iNowGestureState = 0;			
			_fCheckTimer = BASE_CHECK_TIME;
		}
		break;
	default:
		{
			ofLog(OF_LOG_NOTICE, "Unknow eGestureCheckResult");
		}
	}
	
}

//--------------------------------------------------------------
void Gesture::ResetGesture()
{
	_iPauseCounter = 0;
	_iNowGestureState = 0;	
	_fCheckTimer = BASE_CHECK_TIME;
}