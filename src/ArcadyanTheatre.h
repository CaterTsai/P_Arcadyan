#ifndef ARCADYAN_THEATER
#define ARCADYAN_THEATER

#include "protocol.h"
#include "ControlEvent.h"
#include "ofGstVideoPlayer.h"
#include "ofxHapPlayer.h"
#include "ofxTheatreDirector.h"
#include "ofxAnimatableFloat.h"
//-------------------------------------------------
//Theatre
//-------------------------------------------------
class ArcadyanTheatre
{
public:
	void setupTheatre();
	void updateTheatre(float fDelta, ofPoint CtrlPos = ofPoint(0));
	void drawTheatre();
	void resetTheatre();

	void TheatreAnimInit(string strScenes);
	void onTheatreEvent(ofxTheatreEventArgs& e);

public:
	ofxDirector		_Director;

//-------------------------------
// Background object
//-------------------------------
public:
	void playCityLoop();
	void stopCityLoop();

private:
	void setupCityLoop();
	void updateCityLoop();
	void drawCityLoop();

private:
	bool			_bIsCityLoopPlaying;
	ofVideoPlayer	_CityLoop;
//-------------------------------
// @Scenes : Open
//-------------------------------

//-------------------------------
// @Scenes : Gate
//-------------------------------
public:
	void TriggerTheGateLight();
	void OpenTheGate();
private:
	void setupScenesGate();
	void updateScenesGate(float fDelta);
	void drawScenesGate();

private:
	ofxAnimatableFloat	_AnimAlpha;
	ofImage		_DoorBelt, _DoorLight;
	
	bool		_bTriggerOpen;

//-------------------------------
// @Scenes : Main Scenes
//-------------------------------

//-------------------------------
// @Scenes : GreenBuilding
//-------------------------------
public:
	void GreenbuildingZoomIn();

//-------------------------------
// @Scenes : Milestone
//-------------------------------
public:
	void MilestoneZoomIn();

//-------------------------------
// Control Event
//-------------------------------
public:
	void onControlEvent(string& e);

private:
	void setupControlEvent();
	void updateControlEvent(ofPoint CtrlPos);
	void drawControlEvent();
	void resetControlEvent();
	void enableControlEvent(string strScenceName);
	void disableControlEvent(string strScenceName);

private:
	multimap<string, shared_ptr<BaseControlEvent>>	_CtrlEventMgr;

////////////////////////////
//Event
////////////////////////////
public:
	ofEvent<string>	ArcadyanTheaterEvent;


#ifdef TIMEOUT_MODE
//-------------------------------------------------
//Debug timer
//-------------------------------------------------
private:
	bool  _bStartTimer;
	float _fDebugTimer;
#endif // TIMEOUT_MODE


};
#endif // !ARCADYAN_THEATER
