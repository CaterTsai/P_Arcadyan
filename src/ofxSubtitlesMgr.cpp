#include "ofxSubtitlesMgr.h"

///////////////////////////////////
//@CLASS BaseSubtitleMgr
///////////////////////////////////
BaseSubtitleMgr::BaseSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor):
	_DrawPos(oPos), _TextColor(TextColor)
{
	if(!_Font.loadFont(strFontName, fFontSize))
	{
		ofLog(OF_LOG_ERROR, "Can't load font file :" + strFontName);
	}
	_NowSubtitle = _SubtitleList.begin();
};

//--------------------------------------------------------------
void BaseSubtitleMgr::UpdateSubtitleMgr()
{
	cout<<"Hey, You need to override this base function (UpdateSubtitleMgr)."<<endl;
}

//--------------------------------------------------------------
void BaseSubtitleMgr::DrawSubtitleMgr()
{
	cout<<"Hey, You need to override this base function (DrawSubtitleMgr)."<<endl;
}

//--------------------------------------------------------------
void BaseSubtitleMgr::AddSubtitle(string strText, ofImage& Backplane, float fValue, float fDuration, bool bFixBackplane)
{
	auto NewSubtitle_ = CreateSubtitle(strText, Backplane, fValue, fDuration, bFixBackplane);
	_SubtitleList.push_back(NewSubtitle_);
	
	if(_SubtitleList.size() == 1)
	{
		_NowSubtitle = _SubtitleList.begin();
	}

	//sort 
	_SubtitleList.sort([](const stSUBTITLE_UNITS& a, const stSUBTITLE_UNITS& b){ return a.fValue < b.fValue;});

}

//--------------------------------------------------------------
void BaseSubtitleMgr::AddSubtitle(string strText, ofImage& Backplane, float fValue, string VoiceFilePath, bool bFixBackplane)
{
	ofSoundPlayer	VoicePlayer_;
	
	if(VoicePlayer_.loadSound(VoiceFilePath))
	{
		VoicePlayer_.play();
		VoicePlayer_.setPosition(0.5f);
		int Length_ = VoicePlayer_.getPositionMS();
		float fDuration_ = VoicePlayer_.getPositionMS() * 2 / 1000.0;
		auto NewSubtitle_ = CreateSubtitle(strText, Backplane, fValue, fDuration_, bFixBackplane);

		VoicePlayer_.setPosition(0.0f);
		VoicePlayer_.stop();
		NewSubtitle_.Voice = VoicePlayer_;
		_SubtitleList.push_back(NewSubtitle_);

		if(_SubtitleList.size() == 1)
		{
			_NowSubtitle = _SubtitleList.begin();
		}

		//sort 
		_SubtitleList.sort([](const stSUBTITLE_UNITS& a, const stSUBTITLE_UNITS& b){ return a.fValue < b.fValue;});
	}
	else
	{
		ofLog(OF_LOG_ERROR, "Voice is null");
	}
}

//--------------------------------------------------------------
void BaseSubtitleMgr::ResetSubtitle()
{
	_NowSubtitle = _SubtitleList.begin();
}

//--------------------------------------------------------------
stSUBTITLE_UNITS BaseSubtitleMgr::CreateSubtitle(string strText, ofImage& Backplane, float fValue, float fDuration, bool bFixBackplane)
{
	ofRectangle TextRect_ = _Font.getStringBoundingBox(strText, 0, 0);

	float fNewWidth_, fNewHeight_;
	
	if(Backplane.isAllocated() && bFixBackplane)
	{
		fNewWidth_ = Backplane.getWidth();
		fNewHeight_ = Backplane.getHeight();
	}
	else
	{
		fNewWidth_ = TextRect_.getWidth() * 1.2;
		fNewHeight_ = TextRect_.getHeight() *1.1;
	}

	ofFbo ImgFbo_;	
	ImgFbo_.allocate(fNewWidth_, fNewHeight_, GL_RGBA);

	ImgFbo_.begin();
	{
		ofClear(255, 255, 255, 0);

		if(Backplane.isAllocated())
		{
			ofSetColor(255);
			Backplane.draw(0,0, fNewWidth_, fNewHeight_);
		}

		ofSetColor(_TextColor);
		_Font.drawString(	strText, 
							fNewWidth_/2 - TextRect_.getWidth()/2, 
							fNewHeight_/2 + TextRect_.getHeight()/2
						);
	}
	ImgFbo_.end();

	ofPixels oTmpPixel_;
	ImgFbo_.readToPixels(oTmpPixel_);

	stSUBTITLE_UNITS stNewSubtitle_;
	stNewSubtitle_.fValue = fValue;
	stNewSubtitle_.fDuration = fDuration;
	stNewSubtitle_.SubtitleImg.setFromPixels(oTmpPixel_.getPixels(), fNewWidth_, fNewHeight_, OF_IMAGE_COLOR_ALPHA, true);
	
	return stNewSubtitle_;
}


//--------------------------------------------------------------
bool BaseSubtitleMgr::IsEnd()
{
	return _NowSubtitle == _SubtitleList.end();
}

///////////////////////////////////
//@CLASS SwitchSubtitleMgr
///////////////////////////////////
SwitchSubtitleMgr::SwitchSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor):
	BaseSubtitleMgr(strFontName, fFontSize, oPos, TextColor), _bIsDisplay(false)
{
	_fMainTimer = ofGetElapsedTimef();

	_fAlpha.setDuration(0.5);
	_fAlpha.setRepeatType(AnimRepeat::PLAY_ONCE);
	_fAlpha.setCurve(AnimCurve::EASE_IN);

}

//--------------------------------------------------------------
void SwitchSubtitleMgr::UpdateSubtitleMgr()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	this->UpdateAnim(fDelta_);


}

//--------------------------------------------------------------
void SwitchSubtitleMgr::DrawSubtitleMgr()
{
	if(!_bIsDisplay)
	{
		return;
	}

	if(_NowSubtitle != _SubtitleList.end())
	{
		ofPushStyle();
		{
			ofEnableAlphaBlending();
		
			ofSetColor(255, 255, 255, _fAlpha.getCurrentValue());
			_NowSubtitle->SubtitleImg.draw(_DrawPos.x - _NowSubtitle->SubtitleImg.width/2, _DrawPos.y - _NowSubtitle->SubtitleImg.height/2);
			ofDisableAlphaBlending();
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void SwitchSubtitleMgr::Switch(bool bTrunOn)
{
	if(this->IsEnd())
	{
		return;
	}

	if(_fAlpha.isAnimating())
	{
		return;
	}

	if(!_bIsDisplay && bTrunOn)
	{
		_bIsDisplay = true;

		_fAlpha.animateFromTo(0.0, 255.0);
		
		//Play Voice
		if(_NowSubtitle->Voice.isLoaded())
		{
			_NowSubtitle->Voice.play();
		}
	}
	else if(!bTrunOn)
	{
		_fAlpha.animateFromTo(255.0, 0.0);
	}
}

//--------------------------------------------------------------
void SwitchSubtitleMgr::UpdateAnim(float fDelta, bool bGoNext)
{
	_fAlpha.update(fDelta);
	if(!_fAlpha.isAnimating())
	{
		if(_bIsDisplay && _fAlpha.getCurrentValue() == 0.0)
		{
			_bIsDisplay = false;

			if(bGoNext)
			{
				_NowSubtitle++;
			}
		}
	}
}
///////////////////////////////////
//@CLASS TimeSubtitleMgr
///////////////////////////////////
TimeSubtitleMgr::TimeSubtitleMgr(string strFontName, float fFontSize, ofPoint& oPos, ofColor TextColor):
	SwitchSubtitleMgr(strFontName, fFontSize, oPos, TextColor), _bStart(false)
{}

//--------------------------------------------------------------
void TimeSubtitleMgr::UpdateSubtitleMgr(float fTime)
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	this->UpdateAnim(fDelta_, false);

	if(!this->FindClosestSubtitle(fTime))
	{	
		if(_bIsDisplay)
		{
			this->Switch(false);
		}
		return;
	}
	
	if(_bStart)
	{
		if(fTime >= _NowSubtitle->fValue && fTime <= _NowSubtitle->fValue + _NowSubtitle->fDuration)
		{
			this->Switch(true);
		}
	}
}

//--------------------------------------------------------------
void TimeSubtitleMgr::Start()
{
	this->ResetSubtitle();
	_bStart = true;
}

//--------------------------------------------------------------
bool TimeSubtitleMgr::FindClosestSubtitle(float fTime)
{
	if(!_bStart)
	{
		return false;
	}

	bool bFindClosest_ = false;
	for(auto Iter_ = _SubtitleList.begin(); Iter_ != _SubtitleList.end(); ++Iter_)
	{
		if(fTime >= Iter_->fValue && fTime < Iter_->fValue + Iter_->fDuration)
		{
			_NowSubtitle = Iter_;
			bFindClosest_ = true;
		}
	}

	return bFindClosest_;
}