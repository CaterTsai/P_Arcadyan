#ifndef _VIDEO_MANAGER_
#define _VIDEO_MANAGER_

#include "protocol.h"

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

public:
	inline float getNowTime() const
	{
		return _NowTime;
	}

private:
	void gotoNextVideo();
	
private:
	bool					_bIsPlay;
	bool					_bAllVideoDone;

	int						_iVideoIndex;
	vector<stVideoUnit>		_VideoList;
	
	bool					_bNeedBackground;
	ofVideoPlayer			_BackgroundVideo;
	
	float					_VideoTimer, _NowTime;

////////////////////////////
//Event
////////////////////////////
public:
	static ofEvent<string>	VideoEvent;

};


#endif // !_VIDEO_MANAGER_