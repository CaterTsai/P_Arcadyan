#ifndef ARCADYAN_GREEN_BUILDING_CTRL
#define ARCADYAN_GREEN_BUILDING_CTRL

#include "ofGstVideoPlayer.h"
#include "ofxHapPlayer.h"
#include "ofxAnimatableFloat.h"
#include "ofxXmlSettings.h"
#include "protocol.h"

enum eIMAGE_STATE
{
	eIMAGE_DISABLE	=	0,
	eIMAGE_FADEIN,
	eIMAGE_DISPLAY,
	eIMAGE_FADEOUT
};

//-------------------------------------
//Struct @ImageSet
struct ImageSet
{
	ImageSet(string strImgPath, int iValue1, int iValue2)
		:eState(eIMAGE_DISABLE)
		,iTriggerFrame1(iValue1)
		,iTriggerFrame2(iValue2)
	{
		if(iTriggerFrame1 > iTriggerFrame2)
		{
			swap(iTriggerFrame1, iTriggerFrame2);
		}
		if(!Img.loadImage(strImgPath))
		{
			ofLog(OF_LOG_ERROR, "[GreenBuildingCtrl]load image failed : " + strImgPath);
		}

		_AnimAlpha.setDuration(0.5);
		_AnimAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
		_AnimAlpha.reset(0.0);
	}

	//-------------------------------------
	void update(float fDelta)
	{
		_AnimAlpha.update(fDelta);

		if(eState == eIMAGE_FADEIN && _AnimAlpha.hasFinishedAnimating() && _AnimAlpha.getPercentDone() == 1.0)
		{
			eState = eIMAGE_DISPLAY;
		}
		else if(eState == eIMAGE_FADEOUT && _AnimAlpha.hasFinishedAnimating() && _AnimAlpha.getPercentDone() == 1.0)
		{
			eState = eIMAGE_DISABLE;
		}
	}

	//-------------------------------------

	eIMAGE_STATE	eState;
	int		iTriggerFrame1, iTriggerFrame2;
	ofImage	Img;
	ofxAnimatableFloat	_AnimAlpha;
};

//-------------------------------------
//CLASS @GreenBuildingCtrl
class GreenBuildingCtrl
{
public:
	void setupGreenBuildingCtrl();
	void updateGreenBuildingCtrl(float fDelta, ofPoint CtrlPos);
	void drawGreenBuildingCtrl();

	void startGreenBuidling();
	void stopGreenBuidling();

private:
	bool			_bIsStart;
	ofVideoPlayer	_GreenBuilding;
	int				_iTotalFrame;
	ofVideoPlayer	_GreenBuildingLoop, _GreenBuildingLight;

	bool			_bFlip;

////////////////////////////
//Rotate & Control
////////////////////////////
private:
	void startRotate(bool bIsLeft);
	void stopRotate();

private:
	bool			_bIsRotate;
	ofImage			_Arrow, _ArrowLight;
	//ofImage			_ArrowLeft, _ArrowRight;
	ofxAnimatableFloat	_ArrowAlpha;

	ofRectangle		_ExitRect;
	float			_fExitCounter;

////////////////////////////
//Image Control
////////////////////////////
private:
	void initialImageList(string strXMLName);
	void updateImage(float fDelta, int iNowFrame);
	void drawImage();
	void resetImage();

private:
	ofPoint				_DrawPos;
	ofRectangle			_ImgSize;
	
	vector<ImageSet>	_ImageList;

////////////////////////////
//EVENT
////////////////////////////
public:
	ofEvent<bool>	_GreenBuildingEvent;

#ifdef TIMEOUT_MODE
//-------------------------------------------------
//Debug timer
//-------------------------------------------------
private:
	bool  _bStartTimer;
	float _fDebugTimer;
#endif // !TIMEOUT_MODE
};

#endif // !ARCADYAN_GREEN_BUILDING
