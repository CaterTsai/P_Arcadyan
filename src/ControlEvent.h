#ifndef CONTROL_EVENT
#define CONTROL_EVENT

#include "protocol.h"

//------------------------
//@CLASS BaseControlEvent
//------------------------
class BaseControlEvent
{
public:
	BaseControlEvent(string strEventName):
		_bIsDisplay(false),
		_bIsTrigger(false),
		_bHaveCtrlDisplay(false),
		_strEventName(strEventName)
	{
		_CtrlPos.set(0);
	};

	BaseControlEvent(ofImage& CtrlImg, string strEventName):
		_bIsDisplay(false),
		_bIsTrigger(false),
		_bHaveCtrlDisplay(true),
		_strEventName(strEventName)
	{
		_CtrlPos.set(0);
		_CtrlImg.clone(CtrlImg);
	};

	virtual void updateControlEvent(ofPoint CtrlPos){};
	virtual void drawControlEvent(){};
	virtual void resetControlEvent(){};

	void setDisplay(const bool bIsDisplay)
	{
		_bIsDisplay = bIsDisplay;
	};

public:
	ofEvent<string>	ControlEvent;

protected:
	const bool	_bHaveCtrlDisplay;
	bool		_bIsTrigger;
	bool		_bIsDisplay;
	
	ofPoint		_CtrlPos;
	ofImage		_CtrlImg;
	string		_strEventName;
};

//------------------------
//@CLASS TouchControlEvent
//------------------------
class TouchControlEvent : public BaseControlEvent
{
public:
	TouchControlEvent(string strEventName);
	TouchControlEvent(ofImage& CtrlImg, string strEventName);
	void updateControlEvent(ofPoint CtrlPos) override;
	void drawControlEvent() override;
	void resetControlEvent() override;

	void setupTouchTarget(ofImage& TargetImg, ofPoint TargetPos);
	void setupTouchTarget(ofRectangle TargetArea);

	
private:
	bool		_bIsSetup;
	
	ofImage		_TargetImg;
	ofRectangle	_TargetArea;
};

//------------------------
//@CLASS DragControlEvent
//------------------------
class DragControlEvent : public BaseControlEvent
{
public:
	DragControlEvent(string strEventName);
	DragControlEvent(ofImage& CtrlImg, string strEventName);
	void updateControlEvent(ofPoint CtrlPos) override;
	void drawControlEvent() override;
	void resetControlEvent() override;

	void setupDragEvent(ofImage& TouchImg, ofPoint TouchPos, ofRectangle TargetArea);

private:
	bool		_bIsSetup;
	bool		_bIsTouch;

	ofImage		_TouchImg;
	ofRectangle	_TouchArea, _TouchAreaBackup;


	ofRectangle	_TargetArea;
};

#endif // !CONTROL_EVENT