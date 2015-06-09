#include "TimelineElement.h"

#pragma region Image Timeline Element
ImageTimelineElement::ImageTimelineElement(ofImage& Img, ofVec2f& Pos, float fTriggerT, float fLengthT)
	:BaseTimelineElement(fTriggerT, fLengthT)
	,_Img(Img)
	,_DrawCenterPos(Pos)
{
	float fTime_ = fLengthT*0.1;
	_fFadeTime = (fTime_>0.5?0.5:fTime_);
	_AnimAlpha.reset(0);
	_AnimAlpha.setDuration(_fFadeTime);
}

//--------------------------------------------------------------
void ImageTimelineElement::update(float fDelta)
{
	if(!_bIsStart)
	{
		return;
	}
	
	_AnimAlpha.update(fDelta);

	_Timer -= fDelta;
	if(_Timer <= 0.0)
	{
		_bIsStart = false;
	}
	
	if(_AnimAlpha.hasFinishedAnimating() && _AnimAlpha.getPercentDone() == 1.0)
	{
		if((_Timer - _fFadeTime) <= 0.0)
		{
			_AnimAlpha.animateFromTo(255, 0);
		}
	}
}

//--------------------------------------------------------------
void ImageTimelineElement::draw()
{
	if(!_bIsStart)
	{
		return;
	}

	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255, _AnimAlpha.getCurrentValue());
	{
		ofPushMatrix();
		ofTranslate(_DrawCenterPos);
		{
			_Img.draw(-_Img.width/2, -_Img.height/2);
		}
		ofPopMatrix();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ImageTimelineElement::start()
{
	if(_bIsStart)
	{
		return;
	}

	_bIsStart = true;
	_Timer = _fLengthT;
	_AnimAlpha.animateFromTo(0, 255);
}
#pragma endregion

#pragma region AudioTimeLineElement
AudioTimelineElement::AudioTimelineElement(ofSoundPlayer audio, float fTriggerT)
	:BaseTimelineElement(fTriggerT, 0.0)
	,_audio(audio)
{
	_audio = audio;
	_audio.setLoop(false);
}

//--------------------------------------------------------------
void AudioTimelineElement::start()
{
	_bIsStart = true;
	_audio.play();
}
#pragma endregion
