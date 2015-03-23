#ifndef _VIDEO_MANAGER_
#define _VIDEO_MANAGER_

#include "protocol.h"
#include "ofxSubtitlesMgr.h"
#include "ofxXmlSettings.h"

struct stVideoUnit
{
	ofVideoPlayer	VideoPlayer;
	string			strName;
	bool			bHaveAlpha;
	bool			bHaveLoop;
	bool			bIsEmpty;
	bool			bWaitLoop;

	stVideoUnit():
		bHaveAlpha(false),
		bHaveLoop(false),
		bIsEmpty(false)
	{}
};

class VideoManager
{
public:
	VideoManager();
	void setupVideoManager();
	void updateVideoManager();
	void drawVideoManager();

////////////////////////////
//Video
////////////////////////////
public:
	
	void addVideoWithSourcePlayer(string strFileName, string strVideoName, bool bIsLoop = false, bool bWaitLoop = false);
	void addVideo(string strFileName, string strVideoName, ofPtr<ofBaseVideoPlayer> pPlayer, bool bHaveAlpha = false, bool bIsLoop = false, bool bWaitLoop = false);
	void addEmpty(string strName);

	void setBackgroundVideo(string strFileName);
	void setBackgroundVideo(string strFileName, ofPtr<ofBaseVideoPlayer> pPlayer);
	
	void play();
	void next();
	void stop();

private:
	void gotoNextVideo();
	
private:
	bool					_bIsPlay;
	bool					_bAllVideoDone;

	int						_iVideoIndex;
	vector<stVideoUnit>		_VideoList;
	
	bool					_bNeedBackground;
	ofVideoPlayer			_BackgroundVideo;
	
	float					_VideoTimer;

////////////////////////////
//Event
////////////////////////////
public:
	static ofEvent<string>	VideoEvent;

////////////////////////////
//Subtitles
////////////////////////////
private:
	void loadSubtitle();
private:
	bool					_bLoadSubtitle;
	ofPtr<TimeSubtitleMgr>	_pSubtitleMgr;
	ofImage					_Plane;
};


#endif // !_VIDEO_MANAGER_