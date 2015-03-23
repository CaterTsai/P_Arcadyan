#ifndef _OFX_SUBTITLES_MANAGER_
#define _OFX_SUBTITLES_MANAGER_

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxTrueTypeFontUC.h"
#include <algorithm>

///////////////////////////////////
//Base function
///////////////////////////////////
static string ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
	string strTo( size_needed, 0 );
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
	return strTo;
}

///////////////////////////////////
//STRUCT
///////////////////////////////////
struct stSUBTITLE_UNITS
{
	ofImage				SubtitleImg;
	float				fValue;

	float				fDuration;
	ofSoundPlayer		Voice;
};

typedef list<stSUBTITLE_UNITS>	SUBTITLE_LIST;
typedef SUBTITLE_LIST::iterator	SUBTITLE_ITER;

///////////////////////////////////
//@CLASS BaseSubtitleMgr
///////////////////////////////////
class BaseSubtitleMgr
{
public:
	BaseSubtitleMgr(){};
	BaseSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor);

	void UpdateSubtitleMgr();
	void DrawSubtitleMgr();
	void AddSubtitle(string strText, ofImage& Backplane, float fValue, float fDuration, bool bFixBackplane = true);
	void AddSubtitle(string strText, ofImage& Backplane, float fValue, string VoiceFilePath, bool bFixBackplane = true);
	
	void ResetSubtitle();
	bool IsEnd();
protected:
	stSUBTITLE_UNITS CreateSubtitle(string strText, ofImage& Backplane, float fValue, float fDuration, bool bFixBackplane);

public:
	ofPoint				_DrawPos;
	
	ofColor				_TextColor;
	SUBTITLE_ITER		_NowSubtitle;
	SUBTITLE_LIST		_SubtitleList;

	ofxTrueTypeFontUC	_Font;
};

///////////////////////////////////
//@CLASS SwitchSubtitleMgr
///////////////////////////////////
class SwitchSubtitleMgr : public BaseSubtitleMgr
{
public:
	SwitchSubtitleMgr(){};
	SwitchSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor = ofColor(255));

	void UpdateSubtitleMgr();
	void DrawSubtitleMgr();

	void Switch(bool bTrunOn);
protected:
	void UpdateAnim(float fDelta, bool bGoNext = true);

protected:
	bool				_bIsDisplay;
	
	//Animatable
	float				_fMainTimer;
	ofxAnimatableFloat	_fAlpha;
};

///////////////////////////////////
//@CLASS TimeSubtitleMgr
///////////////////////////////////
class TimeSubtitleMgr : public SwitchSubtitleMgr
{
public:
	TimeSubtitleMgr(){};
	TimeSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor = ofColor(255));

	void UpdateSubtitleMgr(float fTime);
	void Start();

private:
	 bool FindClosestSubtitle(float fTime);

private:
	bool		_bStart;
};

#endif //_OFX_SUBTITLES_MANAGER_