#ifndef ARCADYAN_TEXT_SLIDER
#define ARCADYAN_TEXT_SLIDER

#include "protocol.h"

#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxXmlSettings.h"

static const int cKERNEL_SIZE = 81;
static const float cGAUSSIAN_SIGMA = 5.0;
static const float cPOW_SIGMA = (cGAUSSIAN_SIGMA * cGAUSSIAN_SIGMA);
static const int cBASE_ALPHA = 30;

static const int cTEXT_WIDTH = 1000;
static const int cTEXT_HEIGHT = 300;

static const int cFORWARD_Z = -400;

typedef struct _stTEXT_ELEMENT
{
	ofImage				Image;
	ofPoint				Pos;
	float				fAlpha;
	ofxAnimatableFloat	AnimAlpha;
	bool				IsEmpty;
}stTEXT_ELEMENT;

enum eTEXT_ROTATE_STATE
{
	eTEXT_ROTATE_TO_FORWARD		=	0,
	eTEXT_FORWARD,
	eTEXT_ROTATE_TO_BACKWARD,
	eTEXT_BACKWARD,
};

typedef deque<stTEXT_ELEMENT>	TEXT_ELEMENT_LIST;

class TextSlider
{
public:
	void SetupTextSlider(string strXMLFileName, ofPoint StartPos, ofVec3f onterval);
	void UpdateTextSlider(float fDelta);
	void DrawTextSlider(float fRotateX, float fRotateY);
	void ResetTextSlider();

	void PlayTextSlider();
	
	void RotateToForward();
	void RotateToBackward();

private:
	void CreateGaussian(float (&afWeight)[cKERNEL_SIZE], float (&afOffset_)[cKERNEL_SIZE]);
	void SwitchPtr();
	
	string ws2s(const wstring& wstr);

private:
	bool				_bStartSlider;
	
	ofxAnimatableFloat	_AnimTimer;

	//Rotate to forward
	int						_iActiveIdx;
	ofPoint					_TmpPos;
	ofxAnimatableFloat		_AnimRotate;
	ofxAnimatableOfPoint	_AnimForward;
	eTEXT_ROTATE_STATE		_eRotateState;

	ofPoint				_StartPos;
	ofPoint				_DrawStartPos;
	ofVec3f				_Interval;

	TEXT_ELEMENT_LIST*	_pTextElement;
	TEXT_ELEMENT_LIST*  _pNextTextElement;
	TEXT_ELEMENT_LIST	_TextElementList[2];


////////////////////////////////////////
//Image Filter
////////////////////////////////////////
	ofShader		_Blur;

////////////////////////////
//Event
////////////////////////////
public:
	ofEvent<bool>	TextSliderFinishEvent;
};

#endif // !ARCADYAN_TEXT_SLIDER
