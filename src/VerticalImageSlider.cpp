#include "VerticalImageSlider.h"

void VirticalSlider::setupVirticalSlider(ofRectangle DisplayArea, float fInterval)
{
	_Display.allocate(DisplayArea.width, DisplayArea.height, GL_RGBA);
	_Frame.loadImage("images/frame.png");

	//Load the image
	ofDirectory	Dir_("images/Photoframe/");
	Dir_.allowExt("png");
	Dir_.listDir();

	for(int idx_ = 0; idx_ < Dir_.numFiles(); ++idx_)
	{
		ofImage	NewImg_(Dir_.getPath(idx_));
		_ImagesList.push_back(NewImg_);
	}

	_fInterval = fInterval;

	ofPoint CenterPos_(DisplayArea.width/2, DisplayArea.height/2);

	stSLIDER_UNIT FirstUnit_;
	FirstUnit_.iIndexOfList = 0;
	FirstUnit_.Position = CenterPos_;
	FirstUnit_.Position.x -= fInterval;
	FirstUnit_.backupPosition = FirstUnit_.Position;
	FirstUnit_.fScale = cSMALL_PHOTO_SCALE;

	stSLIDER_UNIT SecondUnit_;
	SecondUnit_.iIndexOfList = 1;
	SecondUnit_.Position = CenterPos_;
	SecondUnit_.backupPosition = SecondUnit_.Position;
	SecondUnit_.fScale = 1.0;

	stSLIDER_UNIT ThirdUnit_;
	ThirdUnit_.iIndexOfList = 2;
	ThirdUnit_.Position = CenterPos_;
	ThirdUnit_.Position.x += fInterval;
	ThirdUnit_.backupPosition = ThirdUnit_.Position;
	ThirdUnit_.fScale = cSMALL_PHOTO_SCALE;

	_SliderList.push_back(FirstUnit_);
	_SliderList.push_back(SecondUnit_);
	_SliderList.push_back(ThirdUnit_);

	//Animation
	_bStartAnim = false;
	_bIsToLeft = false;
	_AnimSlide.setDuration(cPHOTO_ANIMATION_DURATION);
	_AnimSlide.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimSlide.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	_AnimScale.setDuration(cPHOTO_ANIMATION_DURATION);
	_AnimScale.setRepeatType(AnimRepeat::PLAY_ONCE);
	_AnimScale.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	//update display
	this->updateDisplay();

	_bIsDisplay = false;
	_bCanMove = true;
	_ImgIndex = 1;

	this->setupControl();

#ifdef TIMEOUT_MODE
	//Debug
	_bStartTimer = false;
#endif // TIMEOUT_MODE
}

//--------------------------------------------------------------
void VirticalSlider::updateVirticalSlider(float fDelta, ofRectangle& CtrlArea)
{
	if(!_bIsDisplay || !_bCanMove)
	{
		return;
	}

	_AnimSlide.update(fDelta);
	_AnimScale.update(fDelta);
	if(_bStartAnim)
	{
		//move
		for(auto& Slider_ : _SliderList)
		{
			if(_bIsToLeft)
			{
				Slider_.Position.x = Slider_.backupPosition.x - _AnimSlide.getCurrentValue();
			}
			else
			{
				Slider_.Position.x = Slider_.backupPosition.x + _AnimSlide.getCurrentValue();
			}
		}

		//scale
		if(_bIsToLeft)
		{
			//Center (1->0)
			_SliderList[1].fScale = (1 - _AnimScale.getCurrentValue()) * (1 - cSMALL_PHOTO_SCALE) + cSMALL_PHOTO_SCALE;

			//Right (0->1)
			_SliderList[2].fScale = _AnimScale.getCurrentValue() * (1 - cSMALL_PHOTO_SCALE) + cSMALL_PHOTO_SCALE;
		}
		else
		{
			//Center (1->0)
			_SliderList[2].fScale = (1 - _AnimScale.getCurrentValue()) * (1 - cSMALL_PHOTO_SCALE) + cSMALL_PHOTO_SCALE;

			//Left (0->1)
			_SliderList[1].fScale = _AnimScale.getCurrentValue() * (1 - cSMALL_PHOTO_SCALE) + cSMALL_PHOTO_SCALE;
		}
		

		if(_AnimSlide.getPercentDone() == 1.0)
		{
			for(auto& Slider_ : _SliderList)
			{
				Slider_.backupPosition.x = Slider_.Position.x;
			}
			
			if(_bIsToLeft)
			{
				_SliderList.pop_front();
			}
			else
			{
				_SliderList.pop_back();
			}

			_bStartAnim = false;
		}
		this->updateDisplay();
	}

	//Control
	if(_LeftArea.intersects(CtrlArea))
	{
		if(this->toLeft())
		{
			string strMsg_ = "toLeft";
			ofNotifyEvent(_VerticalSliderEvent, strMsg_);
		}
	}
	if(_RightArea.intersects(CtrlArea))
	{
		if(this->toRight())
		{
			string strMsg_ = "toRight";
			ofNotifyEvent(_VerticalSliderEvent, strMsg_);
		}
	}
	if(_CameraArea.intersects(CtrlArea))
	{
		string strMsg_ = "takePicture";
		ofNotifyEvent(_VerticalSliderEvent, strMsg_);
	}

#ifdef TIMEOUT_MODE
	if(_bStartTimer)
	{
		_fDebugTimer -= fDelta;
		if(_fDebugTimer < 0.0)
		{
			string strMsg_ = "takePicture";
			ofNotifyEvent(_VerticalSliderEvent, strMsg_);

			_bStartTimer = false;
		}
	}
#endif // TIMEOUT_MODE
}

//--------------------------------------------------------------
void VirticalSlider::drawVirticalSlider(int x, int y)
{
	if(!_bIsDisplay)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(255);
	ofEnableAlphaBlending();
	_Display.draw(x, y);

	ofPopStyle();

	this->drawControl();
}

//--------------------------------------------------------------
void VirticalSlider::resetVirticalSlider()
{
	_bIsDisplay = false;
	_bCanMove = true;
}

//--------------------------------------------------------------
bool VirticalSlider::toRight()
{
	if(!_bIsDisplay || _bStartAnim || !_bCanMove)
	{
		return false;
	}

	_bStartAnim = true;
	_bIsToLeft = false;

	//Insert the new slider
	auto First_ = *(_SliderList.begin());
	_ImgIndex = First_.iIndexOfList;
	stSLIDER_UNIT	NewSlider_;
	NewSlider_.fScale = First_.fScale;
	NewSlider_.iIndexOfList = (First_.iIndexOfList - 1)>=0?(First_.iIndexOfList - 1):(_ImagesList.size() - 1);
	NewSlider_.Position = First_.Position;
	NewSlider_.Position.x -= _fInterval;
	NewSlider_.backupPosition = NewSlider_.Position;

	_SliderList.push_front(NewSlider_);

	_AnimSlide.animateFromTo(0, _fInterval);
	_AnimScale.animateFromTo(0.0, 1.0);
	return true;
}

//--------------------------------------------------------------
bool VirticalSlider::toLeft()
{
	if(!_bIsDisplay || _bStartAnim || !_bCanMove)
	{
		return false;
	}
	_bStartAnim = true;
	_bIsToLeft = true;

	//Insert the new slider
	auto Last = _SliderList.back();
	_ImgIndex = Last.iIndexOfList;
	stSLIDER_UNIT	NewSlider_;
	NewSlider_.fScale = Last.fScale;
	NewSlider_.iIndexOfList = (Last.iIndexOfList + 1)<_ImagesList.size()?(Last.iIndexOfList + 1):0;
	NewSlider_.Position = Last.Position;
	NewSlider_.Position.x += _fInterval;
	NewSlider_.backupPosition = NewSlider_.Position;

	_SliderList.push_back(NewSlider_);

	_AnimSlide.animateFromTo(0, _fInterval);
	_AnimScale.animateFromTo(0.0, 1.0);
	return true;
}

//--------------------------------------------------------------
void VirticalSlider::updateDisplay()
{
	//Update display fbo
	_Display.begin();
	{
		ofPushStyle();
		ofClear(255);
		ofSetColor(255);
		ofEnableAlphaBlending();
		for(auto Iter_ : _SliderList)
		{	
			float fFrameWidth_ = _Frame.width * Iter_.fScale;
			float fFrameHeight_ = _Frame.height * Iter_.fScale;
			_Frame.draw(	Iter_.Position.x - fFrameWidth_/2,
							Iter_.Position.y - fFrameHeight_/2,
							fFrameWidth_,
							fFrameHeight_);
			
			ofImage& refImg_ = _ImagesList[Iter_.iIndexOfList];
			float fDrawWidth_ = cSMALL_PHOTO_WIDTH * Iter_.fScale;
			float fDrawHeight_ = cSMALL_PHOTO_HEIGHT * Iter_.fScale;
			refImg_.draw(	Iter_.Position.x - fDrawWidth_/2,
							Iter_.Position.y - fDrawHeight_/2,
							fDrawWidth_,
							fDrawHeight_);
		}
		ofPopStyle();
	}
	_Display.end();
}

//--------------------------------------------------------------
void VirticalSlider::setupControl()
{
	_ArrowLeft.loadImage("images/ArrowLeft.png");
	_ArrowRight.loadImage("images/ArrowRight.png");
	_Camera.loadImage("images/camera.png");

	_LeftArea.setFromCenter(ofPoint(409, 823), _ArrowLeft.width, _ArrowLeft.height);
	_RightArea.setFromCenter(ofPoint(1527, 823), _ArrowRight.width, _ArrowRight.height);
	_CameraArea.setFromCenter(ofPoint(1635, 558), _Camera.width, _Camera.height);
}

//--------------------------------------------------------------
void VirticalSlider::drawControl()
{
	ofPushStyle();
	ofSetColor(255);
	ofEnableAlphaBlending();
	{
		_ArrowLeft.draw(_LeftArea);
		_ArrowRight.draw(_RightArea);

		_Camera.draw(_CameraArea);

	}
	ofPopStyle();
}