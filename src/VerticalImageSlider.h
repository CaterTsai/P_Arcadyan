#ifndef VERTICAL_IMAGE_SLIDER
#define VERTICAL_IMAGE_SLIDER

#include "protocol.h"
#include "ofxAnimatableFloat.h"

static const int cSMALL_PHOTO_WIDTH = 324;
static const int cSMALL_PHOTO_HEIGHT = 186;
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
	void updateVirticalSlider(float fDelta);
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
};

#endif // !VERTICAL_IMAGE_SLIDER