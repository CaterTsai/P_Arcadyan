#ifndef TEXT_CURVES_SLIDER
#define TEXT_CURVES_SLIDER

#include "SliderParameter.h"
#include "ofxXmlSettings.h"

//-----------------------------------------
#pragma region STRUCT Curve Element
typedef struct _stTEXT_CURVE_ELEMENT
{
	ofImage				TextImg;

	//Postion
	ofxAnimatableFloat	fAnimDuraction;
	ofPoint				Offset;	

	//Alpha
	float				fAlpha;
	ofxAnimatableFloat	fAnimAlpha;

	//Rotate
	bool				bIsRotate;

	_stTEXT_CURVE_ELEMENT()
		:fAlpha(cBASE_ALPHA)
		,bIsRotate(false)
	{}
	
	void update(float fDelta)
	{
		fAnimDuraction.update(fDelta);
		fAnimAlpha.update(fDelta);
		fAlpha = cBASE_ALPHA + fAnimAlpha.getCurrentValue();

		if(fAlpha == cBASE_ALPHA && fAnimDuraction.getCurrentValue() > 0.7)
		{
			fAnimAlpha.animateFromTo(0, 255 - cBASE_ALPHA);
		}
	}

}stTEXT_CURVE_ELEMENT;
#pragma endregion
#pragma region STRUCT Curve path
typedef struct _stTEXT_CURVE
{
	_stTEXT_CURVE()
		:IsDisplay(true)
		,Position(0)
		,fRotate(0)
	{}
	ofPoint		Position;
	float		fRotate;
	bool		IsDisplay;
}stTEXT_CURVE;
#pragma endregion

//-----------------------------------------
#pragma region CLASS TextCurveSlider
class TextCurveSlider
{
public:
	TextCurveSlider()
		:_bIsInit(false)
		,_bStartAnim(false)
		,_fTimer(0.0)
		,_fInterval(0.0)
		,_bDrawCurve(false)
		,_DrawPos(ofPoint(0, 0))
		,_fRotate(0.0)
		,_eRotateState(eTEXT_BACKWARD)
		,_bIsContanctSetup(false)
	{}

	void updateCurveSlider(float fDelta);
	void drawCurveSlider();
	void setCurveSliderData(string strDataXML, float fDuration, float fInterval);	
	void setCurveSliderPath(ofPoint StartPos, ofPoint EndPos, ofPoint C1, ofPoint C2, int iResolution = 200);
	void setDisablePath(float fStartT, float fEndT);
	void startCurveSlider();

private:
	void drawCurve();
	bool getPosition(float fDuraction, ofPoint& Position, float& Degree);
	bool getPosition(float fDuraction, ofPoint& Position);
	
public:
	inline void setCurveDisplay(bool bValue)
	{
		_bDrawCurve = bValue;
	}
	inline void setDrawPos(const ofPoint DrawPos)
	{
		_DrawPos = DrawPos;
	}
	inline void setDrawRotate(const float fRotate)
	{
		_fRotate = fRotate;
	}

private:
	bool		_bIsInit, _bStartAnim, _bDrawCurve;
	float		_fTimer;
	float		_fInterval;
	
	ofPoint		_DrawPos;
	float		_fRotate;

	vector<_stTEXT_CURVE_ELEMENT>::iterator	_IterElement;
	vector<_stTEXT_CURVE_ELEMENT>			_ElementList;
	deque<_stTEXT_CURVE>					_TextCurve;

////////////////////////////////////////
//Rotate
////////////////////////////////////////
public:
	void RotateToForward();
	void RotateToBackward();
private:
	void updateRotate(float fDelta);
	void pauseSlider();
	void resumeSlider();
	bool getRotateElement(vector<_stTEXT_CURVE_ELEMENT>::iterator& refIter);

private:
	eTEXT_ROTATE_STATE						_eRotateState;
	vector<_stTEXT_CURVE_ELEMENT>::iterator	_IterRotate;
	
	ofPoint					_RegisterPos;
	float					_RegisterRotate;
	ofxAnimatableFloat		_AnimRotate;
	ofxAnimatableOfPoint	_AnimForward;
	
////////////////////////////////////////
//Contanct
////////////////////////////////////////
public:
	void setupContanct();
private:
	
	void createText(ofImage& TextImg, string strYear, string strText1, string strText2, string strText3);
	
	void CreateGaussian(float (&afWeight)[cKERNEL_SIZE], float (&afOffset_)[cKERNEL_SIZE]);
	string ws2s(const wstring& wstr);

private:
	bool			_bIsContanctSetup;
	float			_afTexOffsetX[cKERNEL_SIZE][4];
	float			_afTexOffsetY[cKERNEL_SIZE][4];
	
	ofShader		_Blur;
	ofxTrueTypeFontUC _Font80;
	ofxTrueTypeFontUC _Font30;

////////////////////////////
//Event
////////////////////////////
public:
	ofEvent<bool>	TextSliderFinishEvent;

};
#pragma endregion




#endif // !TEXT_CURVES_SLIDER