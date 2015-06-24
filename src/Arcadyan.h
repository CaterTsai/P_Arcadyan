#pragma once

#include "protocol.h"
#include "VideoManager.h"
#include "ofGstVideoPlayer.h"
#include "ArcadyanTheatre.h"
#include "NameManager.h"
#include "InfoDisplay.h"
#include "TextCurveSlider.h"
#include "ImageSlider.h"
#include "VerticalImageSlider.h"
#include "GreenbuildingCtrl.h"
#include "KinectCtrl.h"
#include "TimelineTrigger.h"
#include "SubtitleCreater.h"
#include "AudioMgr.h"
#include "ControlEvent.h"

class Arcadyan : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mousePressed( int x, int y, int button );
	void mouseReleased(int x, int y, int button );

private:
	float	_fMainTimer;

//-------------------------------------------------
//Theatre
//-------------------------------------------------
public:
	void drawBeforeTheatre();
	void drawAfterTheatre();
	void onArcadyanTheaterEvent(string& e);

	void resetTheatre();
public:
	ArcadyanTheatre	_Arcadyan;

//-------------------------------------------------
//Kinect
//-------------------------------------------------
public:
	void KinectCtrlSetup();
	void KinectCtrlUpdate();
	void KinectCtrlDraw();
	void OnGestureEvent(GestureEventArgs &e);

public:
	inline void setCtrlDisplay(bool bValue)
	{
		_bDisplayCtrl = bValue;
	}
public:
	bool		_bHaveUser;
	KinectCtrl	_KinectCtrl;

	bool		_DisplayBody;

	//Ctrl
	bool		_bDisplayCtrl;
	ofImage		_CtrlImg;
	ofRectangle	_CtrlArea;
	
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
	map<string, shared_ptr<BaseControlEvent>>	_CtrlEventMgr;

//-------------------------------------------------
//Timeline Subtitle
//-------------------------------------------------
public:
	void InitialSubtitle(string strFilename);
	void resetSubtitle();
private:
	SubtitleCreater		_SubtitleCreater;
	TimelineTrigger		_SubtitleMgr;
	ofImage				_backplane;
	bool				_bFollowVideo;
//-------------------------------------------------
//Video manager
//-------------------------------------------------
public:
	void InitialVideoManager();
	void onVideoEvent(string& e);
private:
	bool			_bVideoIsStart;
	VideoManager	_VideoMgr;

//-------------------------------------------------
//Image Slider
//-------------------------------------------------
public:
	void InitialImageSlider();
	
private:
	ImageSlider		_ImgSlider;
	float			_fImgRotateX;
	float			_fImgRotateY;

//-------------------------------------------------
//Text Curve Slider
//-------------------------------------------------
public:
	void InitialTextSlider();
	void onTextSlider(bool& e);

private:
	TextCurveSlider	_TextCurveSlider;

//-------------------------------------------------
//Photo Frame Slider
//-------------------------------------------------
public:
	void takePicture();
	void savePicture();
	void onPhotoFrameChange(string& e);

private:
	ofImage			_MixResult;
	bool			_bCanSavePhoto;
	VirticalSlider	_PhotoFrameSlider;

//-------------------------------------------------
//Info Display
//-------------------------------------------------
private:
	void onInfoDisplay(bool& e);

private:
	InfoDisplay		_InfoDisplay;

//-------------------------------------------------
//Green Buidling Ctrl
//-------------------------------------------------
public:
	void onGreenBuildingExit(bool& e);

private:
	bool				_bStartMove;
	GreenBuildingCtrl	_GreenBuildingCtrl;

//-------------------------------------------------
//Audio & BGM
//-------------------------------------------------
private:
	void setupAudioMgr();
};
