#include "TimelineTrigger.h"

void TimelineTrigger::update(float fDelta)
{
	if(!_bStart || _bPause)
	{
		return;
	}

	_fMainTimer += fDelta;
	for(auto& Iter_ : _TimelineList)
	{	
		Iter_->update(fDelta);

		if(abs(Iter_->getTriggerT() - _fMainTimer) < 0.05)
		{
			//Close enough
			Iter_->start();
		}
		else if(Iter_->getTriggerT() > _fMainTimer)
		{
			break;
		}
	}
}

//--------------------------------------------------------------
void TimelineTrigger::updateInTime(float fDelta, float fTime)
{
	if(!_bStart || _bPause)
	{
		return;
	}

	_fMainTimer = fTime;
	for(auto& Iter_ : _TimelineList)
	{	
		Iter_->update(fDelta);

		if(abs(Iter_->getTriggerT() - _fMainTimer) < 0.05)
		{
			//Close enough
			Iter_->start();
		}
		else if(Iter_->getTriggerT() > _fMainTimer)
		{
			break;
		}
	}
}

//--------------------------------------------------------------
void TimelineTrigger::draw()
{
	if(!_bStart)
	{
		return;
	}

	for(auto& Iter_ : _TimelineList)
	{	
		Iter_->draw();
	}
}

//--------------------------------------------------------------
void TimelineTrigger::reset()
{
	_bStart = false;
	_fMainTimer = 0.0;
}

//--------------------------------------------------------------
void TimelineTrigger::addElement(ofPtr<BaseTimelineElement> pBaseElement)
{
	if(_bStart)
	{
		return;
	}

	_TimelineList.push_back(pBaseElement);

	_TimelineList.sort(
		[](const ofPtr<BaseTimelineElement> a, const ofPtr<BaseTimelineElement> b)
		{
			return a->getTriggerT() < b->getTriggerT();
		}
	);
}