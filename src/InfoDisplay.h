#ifndef _INFO_DISPLAY_
#define _INFO_DISPLAY_

#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxXmlSettings.h"
#include "ofxAnimatableFloat.h"

static const int cINFO_WIDTH = 800;
static const int cINFO_HEIGHT = 550;


enum eWEATHER_CODE
{
	eWEATHER_COLUDY	=	0,
	eWEATHER_PARTLY_CLOUDY,
	eWEATHER_RAIN,
	eWEATHER_SUN,
	eWEATHER_THUNDER,
	eWEATHER_UNKNOW
};

enum eINFO_STATE
{
	eSTATE_UNDISPLAY	=	0,
	eSTATE_CHINESE_FADE_IN,
	eSTATE_CHINESE_DISPLAY,
	eSTATE_CHINESE_FADE_OUT,
	eSTATE_ENGLISH_FADE_IN,
	eSTATE_ENGLISH_DISPLAY,
	eSTATE_ENGLISH_FADE_OUT,
	eSTATE_FINISH
};

class InfoDisplay
{
public:
	void setupInfoDisplay(float fChangeTimeout = 3.0);
	void updateInfoDisplay(float fDelta = 0.0);
	void drawInfoDisplay();

	void startDisplay(float fFadeTime = .0);

private:
	bool				_bIsDisplay;
	eINFO_STATE			_eInfoState;
	ofxAnimatableFloat	_AnimFadeAlpha;
////////////////////////////
//Yahoo Weather
////////////////////////////
public:
	void getNowWeatherInfo();
private:
	void initWeather();	
	void newHttpRespone(ofxHttpResponse& Response);

	void ProcessingWeather(int iWeatherCode);

private:
	ofxHttpUtils	_HttpUtils;
	string			_strActionUrl;

	eWEATHER_CODE	_eWeatherCode;

	string			_strTemperature;
	bool			_bHaveWeatherInfo;

////////////////////////////
//Show Info
////////////////////////////
private:
	void initDisplay();
	void updateDisplay();

private:
	bool		_bIsDisplaySetup;
	ofShader	_Shadow, _Blur;
	ofFbo		_Display, _DisplayRef;

	bool		_bIsChinese;
	float		_fChange;
	float		_fChangeTimeout;
	string		_strTimeM;
	map<eWEATHER_CODE, ofImage>	_WeatherIcon;
		
	ofxTrueTypeFontUC	_FontMS80W;
	ofxTrueTypeFontUC	_FontMS80;
	ofxTrueTypeFontUC	_FontMS50;
	ofxTrueTypeFontUC	_FontMS40;

////////////////////////////
//Backplane
////////////////////////////
private:
	ofxAnimatableFloat	_AnimBackplaneAlpha;
	ofImage				_Backplane;

////////////////////////////
//Event
////////////////////////////
public:
	ofEvent<bool>	FinishEvent;

////////////////////////////
//Basic function
////////////////////////////
private:
	string ws2s(const wstring& wstr);

};


#endif // !_INFO_DISPLAY_
