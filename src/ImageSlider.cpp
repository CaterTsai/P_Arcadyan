#include "ImageSlider.h"

//--------------------------------------------------------------
void ImageSlider::SetupImageSlider(string strXmlName, ofPoint RotateAxle, float fLength, float fIntervalTime)
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

	_RotateAxle = RotateAxle;
	_fLength = fLength;
	_iDisplayIndex = _iRotateIndex = 0;

	//Initial Animation
	_bStartAnimation = false;
	_fAnimRotate.setDuration(0.875);
	_fAnimRotate.setRepeatType(PLAY_ONCE);
	_fAnimRotate.setCurve(EASE_IN_EASE_OUT);

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

	_fAnimRotate.update(fDelta);
	if(_bStartAnimation)
	{		
		if(_fAnimRotate.hasFinishedAnimating() && _fAnimRotate.getPercentDone() == 1.0)
		{
			_bStartAnimation = false;
			_iDisplayIndex = _iRotateIndex;
		}
	}

	_IntervalTimer -= fDelta;
	if(_IntervalTimer <= 0.0)
	{
		this->SliderImage();

		//Reset timer
		_IntervalTimer = _IntervalTimeout;
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
	ofTranslate(_RotateAxle);
	ofRotateX(fRotateX);
	ofRotateY(fRotateY);
	{
		ofPushMatrix();
		{
			ofTranslate(0, -_fLength, 0);
			_ImageList[_iDisplayIndex].Image.draw(-880/2, -804/2);
		}
		ofPopMatrix();

		if(_bStartAnimation)
		{
			ofPushMatrix();
			{
				ofRotateZ(-_fAnimRotate.getCurrentValue());
				ofTranslate(0, -_fLength, 0);
				_ImageList[_iRotateIndex].Image.draw(-880/2, -804/2);
			}
			ofPopMatrix();
		}
	}
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
		_iRotateIndex = _iDisplayIndex + 1;
		if(_iRotateIndex >= _ImageList.size())
		{
			_bIsEnd = true;
		}
		else
		{
			_fAnimRotate.animateFromTo(90.0, 0);
			_bStartAnimation = true;
		}
	}
}

//--------------------------------------------------------------
void ImageSlider::StartSlider()
{
	_bDisplay = true;
	_bIsEnd = false;
	_iDisplayIndex = _iRotateIndex = 0;
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