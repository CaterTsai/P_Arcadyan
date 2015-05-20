#ifndef ARCADYAN_TIMELINE_TRIGGER
#define ARCADYAN_TIMELINE_TRIGGER

#include "TimelineElement.h"

class TimelineTrigger
{
public:
	TimelineTrigger()
		:_bStart(false)
		,_fMainTimer(0.0)
		,_bPause(false)
	{}

	~TimelineTrigger()
	{
		_TimelineList.clear();
	}

	void update(float fDelta);
	void updateInTime(float fDelta, float fTime);
	void draw();
	void reset();

	void addElement(ofPtr<BaseTimelineElement> pBaseElement);
public:
	inline void start()
	{
		_bStart = true;
		_fMainTimer = 0.0;
	}

	inline void jumpTo(float fTime)
	{
		_fMainTimer = fTime;
	}

	inline void setPause(float value)
	{
		_bPause = value;
	}

private:
	bool	_bStart, _bPause;
	float	_fMainTimer;
	list<ofPtr<BaseTimelineElement>>	_TimelineList;
};

#endif // !ARCADYAN_TIMELINE_TRIGGER
