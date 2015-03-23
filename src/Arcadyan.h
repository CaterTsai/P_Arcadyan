#pragma once

#include "protocol.h"
#include "VideoManager.h"
#include "ofGstVideoPlayer.h"
#include "ArcadyanTheatre.h"
#include "NameManager.h"
#include "InfoDisplay.h"
//#include "TextSlider.h"
#include "TextCurveSlider.h"
#include "ImageSlider.h"
#include "VerticalImageSlider.h"
#include "GreenbuildingCtrl.h"
#include "KinectCtrl.h"

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
	KinectCtrl	_KinectCtrl;

//-------------------------------------------------
//Video with subtitles
//-------------------------------------------------
public:
	void InitialVideoManager();
	void onVideoEvent(string& e);
private:
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
//Info Display
//-------------------------------------------------
private:
	void onInfoDisplay(bool& e);

private:
	InfoDisplay		_InfoDisplay;

//-------------------------------------------------
//Green Buidling Ctrl
//-------------------------------------------------
private:
	bool				_bStartMove;
	float				_fX;
	GreenBuildingCtrl	_GreenBuildingCtrl;

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
private:
	VirticalSlider	_PhotoFrameSlider;
};
