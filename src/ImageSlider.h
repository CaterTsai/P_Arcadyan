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
	void SetupImageSlider(string strXmlName, ofPoint RotateAxle, float fLength, float fIntervalTime = 5.0);
	
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
	ofxAnimatableFloat	_fAnimRotate;
	ofxTrueTypeFontUC	_Font;

	ofPoint			_RotateAxle;
	float			_fLength;
	
	int				_iDisplayIndex;
	int				_iRotateIndex;

	IMAGE_LIST		_ImageList;

	float			_IntervalTimer, _IntervalTimeout;
};


#endif // !_IMAGE_SLIDER_
