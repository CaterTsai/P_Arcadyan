#ifndef _IMAGE_SLIDER_
#define _IMAGE_SLIDER_

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxXmlSettings.h"

static int cIMAGE_WIDTH = 841;
static int cIMAGE_HEIGHT = 640;

static ofPoint cTEXT_POS = ofPoint(47, 745);

struct stImageUnit
{
	ofImage		Image;
	int			iIdx;
};

typedef deque<stImageUnit>			IMAGE_LIST;
typedef IMAGE_LIST::iterator		IMAGE_LIST_ITER;

class ImageSlider
{
public:
	void SetupImageSlider(string strXmlName, ofPoint oStartPos, ofVec3f oInterval, float fIntervalTime = 5.0);
	void SetupImageSliderFromFolder(string strFolderName, ofPoint oStartPos, ofVec3f oInterval, float fIntervalTime = 5.0);
	
	void UpdateImageSlider(float fDelta);
	void DrawImageSlider(float fRotateX, float fRotateY);

	void SliderImage();

	void StartSlider();
	void StopSlider();
	
	bool getIsDisplay(){return _bDisplay;};
	bool getIsEnd (){return _bIsEnd;};


	string ws2s(const wstring& wstr);


private:
	bool				_bDisplay;
	bool				_bIsEnd;

	bool				_bStartAnimation;
	ofxAnimatableFloat	_fAnimationTimer;
	ofxAnimatableFloat	_fAlpah;

	ofxTrueTypeFontUC	_Font;

	ofPoint			_StartPos;
	ofPoint			_DrawStartPos;
	ofVec3f			_Interval;

	float			_IntervalTimeout;
	float			_IntervalTimer;

	IMAGE_LIST		_ImageList;
};


#endif // !_IMAGE_SLIDER_
