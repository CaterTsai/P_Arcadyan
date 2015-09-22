#ifndef VERTICAL_IMAGE_SLIDER
#define VERTICAL_IMAGE_SLIDER

#include "protocol.h"
#include "ofxAnimatableFloat.h"

static const int cSMALL_PHOTO_WIDTH = 290;
static const int cSMALL_PHOTO_HEIGHT = 187;
static const float cSMALL_PHOTO_SCALE = 0.69;

typedef struct _stSLIDER_UNIT
{
	int			iIndexOfList;
	ofPoint		backupPosition;
	ofPoint		Position;
	float		fScale;
}stSLIDER_UNIT;

class VirticalSlider
{
public:
	void setupVirticalSlider(ofRectangle DisplayArea, float fInterval);
	void updateVirticalSlider(float fDelta, ofRectangle& CtrlArea);
	void drawVirticalSlider(int x, int y);
	void resetVirticalSlider();
	bool toRight();
	bool toLeft();
	
	inline void getNowImage(ofImage& refImage)
	{
		refImage = _ImagesList[_ImgIndex];
	}
	inline void setDisplay(bool bValue = true)
	{
		_bIsDisplay = bValue;

#ifdef TIMEOUT_MODE
		if(bValue)
		{
			_bStartTimer = true;
			_fDebugTimer = cTAKE_PHOTO_TIMEOUT;
		}
#endif // TIMEOUT_MODE
	}

	inline void setCanMove(bool bValue = true)
	{
		_bCanMove = bValue;
	}

private:
	void updateDisplay();

private:
	bool					_bIsDisplay;
	bool					_bCanMove;

	ofFbo					_Display;
	float					_fInterval;
	vector<ofImage>			_ImagesList;
	deque<stSLIDER_UNIT>	_SliderList;
	ofImage					_Frame;
	int						_ImgIndex;

	//move animation
	bool					_bStartAnim;
	bool					_bIsToLeft;
	ofxAnimatableFloat		_AnimSlide;

	//scale animation
	ofxAnimatableFloat		_AnimScale;

////////////////////////////
//Control
////////////////////////////
private:
	void setupControl();
	void drawControl();

private:
	ofImage			_ArrowLeft, _ArrowRight, _Camera;
	ofRectangle		_LeftArea, _RightArea, _CameraArea;


////////////////////////////
//EVENT
////////////////////////////
public:
	ofEvent<string>	_VerticalSliderEvent;

#ifdef TIMEOUT_MODE
//-------------------------------------------------
//Debug timer
//-------------------------------------------------
private:
	bool  _bStartTimer;
	float _fDebugTimer;
#endif // !TIMEOUT_MODE
};

#endif // !VERTICAL_IMAGE_SLIDER