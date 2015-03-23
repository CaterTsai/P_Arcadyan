#include "ImageSlider.h"

//--------------------------------------------------------------
void ImageSlider::SetupImageSlider(string strXmlName, ofPoint oStartPos, ofVec3f oInterval, float fIntervalTime)
{
	ofxXmlSettings	xmlLoader_;

	ofxTrueTypeFontUC oFont_;
	oFont_.loadFont("fonts/msjhbd.ttf", 30);

	ofImage	PhotoFrame_;
	PhotoFrame_.loadImage("images/photo_frame.png");

	if(!xmlLoader_.loadFile(strXmlName))
	{
		ofLog(OF_LOG_ERROR, "Load image slider failed");
		return;
	}

	xmlLoader_.pushTag("ARCADYAN_IMAGE_SLIDER_DATA");
	int iNum_ = xmlLoader_.getNumTags("IMAGE_SLIDER");

	for(int idx_ = 0; idx_ < iNum_; ++idx_)
	{
		ofImage	NewImg_;
		string strImgPath_ = xmlLoader_.getValue("IMAGE_SLIDER:IMAGE_PATH", "", idx_);
		string strMessage_ = xmlLoader_.getValue("IMAGE_SLIDER:MESSAGE", "", idx_);
		if(strImgPath_ == "")
		{
			continue;
		}

		if(!NewImg_.loadImage(strImgPath_))
		{
			ofLog(OF_LOG_ERROR, "Load image failed : " + strImgPath_);
			continue;
		}

		NewImg_.resize(cIMAGE_WIDTH, cIMAGE_HEIGHT);
		
		ofFbo oNewFbo_;
		oNewFbo_.allocate(880, 804, GL_RGBA);
		ofPoint oImgPos_(19, 19);
		oNewFbo_.begin();
		{
			ofBackground(255);
			
			ofSetColor(255);
			PhotoFrame_.draw(0, 0);
			NewImg_.draw(oImgPos_);

			ofSetColor(0);
			oFont_.drawString(strMessage_, cTEXT_POS.x, cTEXT_POS.y);
		}	
		oNewFbo_.end();
		
		stImageUnit	NewUnit_;
		ofPixels oTmpPixel_;
		oNewFbo_.readToPixels(oTmpPixel_);
		NewUnit_.Image.setFromPixels(oTmpPixel_.getPixels(), oNewFbo_.getWidth(), oNewFbo_.getHeight(), OF_IMAGE_COLOR_ALPHA, true);
		NewUnit_.iIdx = idx_;
		
		_ImageList.push_back(NewUnit_);
	}

	_StartPos = _DrawStartPos = oStartPos;
	_Interval = oInterval;

	//Initial Animation
	_bStartAnimation = false;
	_fAnimationTimer.setDuration(0.5);
	_fAnimationTimer.setRepeatType(PLAY_ONCE);
	_fAnimationTimer.setCurve(EASE_IN_EASE_OUT);

	_fAlpah.setDuration(0.5);
	_fAlpah.setRepeatType(PLAY_ONCE);
	_fAlpah.setCurve(EASE_IN_EASE_OUT);

	//Interval Timeout
	_IntervalTimeout = fIntervalTime;

	_bDisplay = false;
	_bIsEnd = true;
}

//--------------------------------------------------------------
void ImageSlider::SetupImageSliderFromFolder(string strFolderName, ofPoint oStartPos, ofVec3f oInterval, float fIntervalTime)
{	
	//Load image
	ofDirectory	oImgDir_(strFolderName);
	oImgDir_.allowExt("jpg");
	oImgDir_.listDir();

	ofxTrueTypeFontUC oFont_;
	oFont_.loadFont("fonts/msjhbd.ttf", 55);

	ofImage	PhotoFrame_;
	PhotoFrame_.loadImage("images/photo_frame.png");

	for(int idx_ =  0; idx_ < oImgDir_.numFiles(); ++idx_)
	{
		ofImage	oNewImg_;
		oNewImg_.loadImage(oImgDir_.getPath(idx_));
		oNewImg_.resize(cIMAGE_WIDTH, cIMAGE_HEIGHT);
		
		ofFbo oNewFbo_;
		oNewFbo_.allocate(880, 804, GL_RGBA);
		ofPoint oImgPos_(19, 19);
		oNewFbo_.begin();
		{
			ofBackground(255);
			
			ofSetColor(255);
			PhotoFrame_.draw(0, 0);
			oNewImg_.draw(oImgPos_);

			ofSetColor(0);
			oFont_.drawString(ws2s(L"2014 ¶ê¹Ú­pµe"), cTEXT_POS.x, cTEXT_POS.y);
		}	
		oNewFbo_.end();
		
		stImageUnit	NewUnit_;
		ofPixels oTmpPixel_;
		oNewFbo_.readToPixels(oTmpPixel_);
		NewUnit_.Image.setFromPixels(oTmpPixel_.getPixels(), oNewFbo_.getWidth(), oNewFbo_.getHeight(), OF_IMAGE_COLOR_ALPHA, true);
		NewUnit_.iIdx = idx_;
		
		_ImageList.push_back(NewUnit_);
	}
	
	_StartPos = _DrawStartPos = oStartPos;
	_Interval = oInterval;

	//Initial Animation
	_bStartAnimation = false;
	_fAnimationTimer.setDuration(0.5);
	_fAnimationTimer.setRepeatType(PLAY_ONCE);
	_fAnimationTimer.setCurve(EASE_IN_EASE_OUT);

	_fAlpah.setDuration(0.5);
	_fAlpah.setRepeatType(PLAY_ONCE);
	_fAlpah.setCurve(EASE_IN_EASE_OUT);

	//Interval Timeout
	_IntervalTimeout = fIntervalTime;

	_bDisplay = false;
	_bIsEnd = true;

}

//--------------------------------------------------------------
void ImageSlider::UpdateImageSlider(float fDelta)
{
	if(fDelta <= 0.0)
	{
		return;
	}

	if(!_bDisplay || _bIsEnd)
	{
		return;
	}

	if(_bStartAnimation)
	{	
		_fAnimationTimer.update(fDelta);
		_fAlpah.update(fDelta);

		if(_fAnimationTimer.getPercentDone() == 1.0)
		{	
			_DrawStartPos = _StartPos;
			stImageUnit TmpImg_ = *(_ImageList.begin());
			_ImageList.pop_front();
			_ImageList.push_back(TmpImg_);

			_bStartAnimation = false;
		}
		else
		{
			_DrawStartPos.z = _StartPos.z + _fAnimationTimer.getCurrentValue();
		}
	}
	else
	{
		_IntervalTimer -= fDelta;
		if(_IntervalTimer <= 0.0)
		{
			this->SliderImage();

			//Reset timer
			_IntervalTimer = _IntervalTimeout;
		}
	}
}

//--------------------------------------------------------------
void ImageSlider::DrawImageSlider(float fRotateX, float fRotateY)
{
	if(!_bDisplay)
	{
		return;
	}

	ofPushStyle();

	ofSetColor(255);
	ofPushMatrix();

	ofTranslate(_StartPos);
	ofRotateX(fRotateX);
	ofRotateY(fRotateY);
	ofSetDepthTest(true);
	
	if(!_bStartAnimation)
	{
		ofSetColor(255);
		for(int idx_ = 0; idx_ < _ImageList.size(); ++idx_)
		{
			ofPoint oPos_ = _DrawStartPos + (_Interval * idx_);
			_ImageList[idx_].Image.draw(-_ImageList[idx_].Image.width/2, -_ImageList[idx_].Image.height/2, oPos_.z);
		}
	}
	else
	{
		ofPoint oPos_ = _DrawStartPos;
		ofSetColor(255, 255, 255, _fAlpah.getCurrentValue());
		_ImageList[0].Image.draw(-_ImageList[0].Image.width/2, -_ImageList[0].Image.height/2, oPos_.z);
		
		ofSetColor(255);
		for(int idx_ = 1; idx_ < _ImageList.size(); ++idx_)
		{
			ofPoint oPos_ = _DrawStartPos + (_Interval * idx_);
			_ImageList[idx_].Image.draw(-_ImageList[idx_].Image.width/2, -_ImageList[idx_].Image.height/2, oPos_.z);
		}
	}
	ofSetDepthTest(false);
	ofPopMatrix();

	ofPopStyle();
}

//--------------------------------------------------------------
void ImageSlider::SliderImage()
{
	if(!_bDisplay || _bIsEnd)
	{
		return;
	}

	if(!_bStartAnimation)
	{
		if(_ImageList[0].iIdx != _ImageList.size() - 1)
		{	
			_fAnimationTimer.animateFromTo(0, -_Interval.z);
			_fAlpah.animateFromTo(255, 0);
			_bStartAnimation = true;
		}
		else
		{
			_bIsEnd = true;
		}
	}
}

//--------------------------------------------------------------
void ImageSlider::StartSlider()
{
	_bDisplay = true;
	_bIsEnd = false;

	if(_ImageList.size() == 0)
	{
		_bDisplay = false;
		_bIsEnd = true;
	}
	else
	{
		//sort image list by index
		sort(	_ImageList.begin(), 
				_ImageList.end(), 
				[](const stImageUnit& a, const stImageUnit& b) -> bool
				{
					return a.iIdx < b.iIdx;
				}
		);

		_IntervalTimer = _IntervalTimeout;
	}
}

//--------------------------------------------------------------
void ImageSlider::StopSlider()
{
	_bDisplay = false;
	_bIsEnd = true;
}

//--------------------------------------------------------------
string ImageSlider::ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
    string strTo( size_needed, 0 );
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
    return strTo;
}