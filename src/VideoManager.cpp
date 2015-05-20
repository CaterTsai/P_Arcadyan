#include "VideoManager.h"

ofEvent<string> VideoManager::VideoEvent = ofEvent<string>(); 

VideoManager::VideoManager():
	_VideoTimer(.0),
	_bIsPlay(false),
	_bAllVideoDone(false),
	_iVideoIndex(0),
	_bNeedBackground(false)
{}

//--------------------------------------------------------------
void VideoManager::updateVideoManager()
{
	if(!_bIsPlay)
	{
		return;
	}

	//Is Empty?
	if(_VideoList[_iVideoIndex].bIsEmpty)
	{
	}
	else
	{
		//Update
		_VideoList[_iVideoIndex].VideoPlayer.update();
		
		if(_VideoList[_iVideoIndex].VideoPlayer.getLoopState() == OF_LOOP_NONE)
		{
			if(_VideoList[_iVideoIndex].VideoPlayer.getIsMovieDone())
			{	
				this->gotoNextVideo();

				if(_iVideoIndex < _VideoList.size())
				{
					_VideoList[_iVideoIndex].VideoPlayer.update();
				}
			}
		}
	}
	
	if(_bNeedBackground)
	{
		_BackgroundVideo.update();
	}
	
	//Update Now time
	if(_bIsPlay && !_VideoList[_iVideoIndex].bIsEmpty)
	{
		float fNewDuration_ =  _VideoList[_iVideoIndex].VideoPlayer.getDuration() * _VideoList[_iVideoIndex].VideoPlayer.getPosition();
		_NowTime = _VideoTimer;
		if(fNewDuration_ > 0.0)
		{
			_NowTime += fNewDuration_;
		}		
	}
}

//--------------------------------------------------------------
void VideoManager::drawVideoManager()
{
	ofPushStyle();
	{
		ofSetColor(255);
		if(!_bIsPlay)
		{
			return;
		}
	
		if(_bNeedBackground)
		{	
				ofEnableAlphaBlending();
				_BackgroundVideo.draw(0, 0);
				_VideoList[_iVideoIndex].VideoPlayer.draw(0, 0);
				ofDisableAlphaBlending();
		}
		else
		{
			_VideoList[_iVideoIndex].VideoPlayer.draw(0, 0);
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void VideoManager::addVideoWithSourcePlayer(string strFileName, string strVideoName, bool bIsLoop, bool bWaitLoop)
{
	ofVideoPlayer NewVideo_;
	
	if(NewVideo_.loadMovie(strFileName))
	{
		if(bIsLoop)
		{
			NewVideo_.setLoopState(OF_LOOP_NORMAL);
		}
		else
		{
			NewVideo_.setLoopState(OF_LOOP_NONE);
		}
		
		stVideoUnit stNewVideoUnit_;
		stNewVideoUnit_.bHaveLoop = bIsLoop;
		stNewVideoUnit_.bWaitLoop = bWaitLoop;
		stNewVideoUnit_.VideoPlayer = NewVideo_;
		stNewVideoUnit_.strName = strVideoName;
		_VideoList.push_back(stNewVideoUnit_);
	}
	else
	{
		ofLog(OF_LOG_ERROR, "Load video failed! : %s", strFileName);
	}
}

//--------------------------------------------------------------
void VideoManager::addVideo(string strFileName, string strVideoName, ofPtr<ofBaseVideoPlayer> pPlayer, bool bHaveAlpha, bool bIsLoop, bool bWaitLoop)
{
	ofVideoPlayer NewVideo_;
	NewVideo_.setPlayer(pPlayer);
	
	if(bHaveAlpha)
	{
		NewVideo_.setPixelFormat(ofPixelFormat::OF_PIXELS_RGBA);
	}

	if(NewVideo_.loadMovie(strFileName))
	{
		if(bIsLoop)
		{
			NewVideo_.setLoopState(OF_LOOP_NORMAL);
		}
		else
		{
			NewVideo_.setLoopState(OF_LOOP_NONE);
		}

		stVideoUnit stNewVideoUnit_;
		stNewVideoUnit_.strName = strVideoName;
		stNewVideoUnit_.bHaveAlpha = bHaveAlpha;
		stNewVideoUnit_.bHaveLoop = bIsLoop;
		stNewVideoUnit_.bWaitLoop = bWaitLoop;
		stNewVideoUnit_.VideoPlayer = NewVideo_;
		_VideoList.push_back(stNewVideoUnit_);
	}
	else
	{
		ofLog(OF_LOG_ERROR, "Load video failed! : %s", strFileName);
	}
}

//--------------------------------------------------------------
void VideoManager::addEmpty(string strName)
{
	stVideoUnit stNewEmptyUnit_;
	stNewEmptyUnit_.bIsEmpty = true;
	stNewEmptyUnit_.bHaveAlpha = false;
	stNewEmptyUnit_.bHaveLoop = false;
	stNewEmptyUnit_.strName = strName;
	_VideoList.push_back(stNewEmptyUnit_);
}

//--------------------------------------------------------------
void VideoManager::setBackgroundVideo(string strFileName)
{
	ofVideoPlayer BackgroundVideo_;
	
	if(BackgroundVideo_.loadMovie(strFileName))
	{
		BackgroundVideo_.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	}
	else
	{
		ofLog(OF_LOG_ERROR, "Load background video failed! : %s", strFileName);
	}
}

//--------------------------------------------------------------
void VideoManager::setBackgroundVideo(string strFileName, ofPtr<ofBaseVideoPlayer> pPlayer)
{
	_BackgroundVideo.setPlayer(pPlayer);

	if(_BackgroundVideo.loadMovie(strFileName))
	{
		_BackgroundVideo.setLoopState(ofLoopType::OF_LOOP_NORMAL);
	}
	else
	{
		ofLog(OF_LOG_ERROR, "Load background video failed! : %s", strFileName);
	}
}

//--------------------------------------------------------------
void VideoManager::play()
{
	_iVideoIndex = 0;
	_bAllVideoDone = false;
	_VideoTimer = .0f;
	if(_VideoList.size() > 0)
	{
		if(!_VideoList[_iVideoIndex].bIsEmpty)
		{
			_bIsPlay = true;
			_bNeedBackground = (_VideoList[_iVideoIndex].bHaveAlpha);
			_VideoList[_iVideoIndex].VideoPlayer.play();
		}
		_BackgroundVideo.play();
	}
}

//--------------------------------------------------------------
void VideoManager::next()
{
	if(!_bIsPlay)
	{
		return;
	}

	if(_VideoList[_iVideoIndex].bIsEmpty)
	{
		this->gotoNextVideo();
	}
	else
	{
		if(_VideoList[_iVideoIndex].VideoPlayer.getLoopState() == OF_LOOP_NORMAL)
		{
			if(_VideoList[_iVideoIndex].bWaitLoop)
			{
				_VideoList[_iVideoIndex].VideoPlayer.setLoopState(OF_LOOP_NONE);
			}
			else
			{
				this->gotoNextVideo();
			}
		}
	}
}

//--------------------------------------------------------------
void VideoManager::stop()
{	
	for(int idx_ = 0; idx_ < _VideoList.size(); ++idx_)
	{
		if(!_VideoList[idx_].bIsEmpty)
		{
			_VideoList[idx_].VideoPlayer.setFrame(0);
			_VideoList[idx_].VideoPlayer.update();
			_VideoList[idx_].VideoPlayer.stop();

			if(_VideoList[idx_].bHaveLoop)
			{
				_VideoList[idx_].VideoPlayer.setLoopState(ofLoopType::OF_LOOP_NORMAL);
			}
		}
	}
	_BackgroundVideo.setFrame(0);
	_BackgroundVideo.update();
	_BackgroundVideo.stop();
}

//--------------------------------------------------------------
void VideoManager::gotoNextVideo()
{
	if(!_bIsPlay)
	{
		return;
	}
	
	if(!_VideoList[_iVideoIndex].bIsEmpty)
	{
		_VideoTimer += _VideoList[_iVideoIndex].VideoPlayer.getDuration();	
		_VideoList[_iVideoIndex].VideoPlayer.stop();
	}

	_iVideoIndex++;	
	if(_iVideoIndex >= _VideoList.size() )
	{
		_bIsPlay = false;
		_bAllVideoDone = true;
		_VideoTimer = .0f;

		string strMsg_;
		strMsg_ = "V_VideoDone";
		ofNotifyEvent(VideoEvent, strMsg_);
	}
	else
	{
		if(_VideoList[_iVideoIndex].bIsEmpty)
		{
			_bNeedBackground = true;
		}
		else
		{
			_bNeedBackground = (_VideoList[_iVideoIndex].bHaveAlpha);
			_VideoList[_iVideoIndex].VideoPlayer.play();
		}

		//event
		if(_VideoList[_iVideoIndex].bIsEmpty || _VideoList[_iVideoIndex].bHaveLoop)
		{
			ofNotifyEvent(VideoEvent, _VideoList[_iVideoIndex].strName);
		}
	}
}
