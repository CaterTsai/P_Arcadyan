#include "TextSlider.h"

void TextSlider::SetupTextSlider(string strXMLFileName, ofPoint StartPos, ofVec3f Interval)
{
	//XML
	ofxXmlSettings	xmlLoader_;
	if(!xmlLoader_.loadFile(strXMLFileName))
	{
		ofLog(OF_LOG_ERROR, "Load text slider failed");
		return;
	}
	xmlLoader_.pushTag("ARCADYAN_TEXT_SLIDER_DATA");
	int iNum_ = xmlLoader_.getNumTags("TEXT_SLIDER");

	//Pamerater
	_StartPos = _DrawStartPos = StartPos;
	_Interval = Interval;
	_bStartSlider = false;

	//Filter
	_Blur.load("", "shader/GaussianBlur_Dynamic.frag");

	//font
	ofxTrueTypeFontUC Font80_;
	ofxTrueTypeFontUC Font30_;
	Font80_.loadFont("fonts/msjhbd.ttf", 80);
	Font30_.loadFont("fonts/msjhbd.ttf", 30);

	//Initial gaussian filter kernel
	float afBlurWeight_[cKERNEL_SIZE] = {0};
	float afOffset_[cKERNEL_SIZE] = {0};
	this->CreateGaussian(afBlurWeight_, afOffset_);

	float afTexOffsetX[cKERNEL_SIZE][4] = {0};
	float afTexOffsetY[cKERNEL_SIZE][4] = {0};

	//X
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; ++idx_)
	{
		afTexOffsetX[idx_][0] = afOffset_[idx_];
		afTexOffsetX[idx_][3] = afBlurWeight_[idx_];
	}

	//Y
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; ++idx_)
	{
		afTexOffsetY[idx_][1] = afOffset_[idx_];
		afTexOffsetY[idx_][3] = afBlurWeight_[idx_];
	}

	ofDisableBlendMode();
	bool bIsFirst_ = true;
	for(int idx_ = 0; idx_ < iNum_; ++idx_)
	{		
		string strYear_ = xmlLoader_.getValue("TEXT_SLIDER:YEAR", "", idx_);
		string strTitle_ = xmlLoader_.getValue("TEXT_SLIDER:TITLE", "", idx_);
		ofFbo TextFbo_, HighLightFbo_, BlurXFbo_, BlurYFbo_, AfterFilterFbo_;
		
		//Combine the text to an image
		TextFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
		TextFbo_.begin();
		{			
			ofSetColor(0,255, 40);
			Font80_.drawString(strYear_, 0, Font80_.getLineHeight());
			Font30_.drawString(strTitle_, 0, Font30_.getLineHeight() + Font80_.getLineHeight());
			//Font50_.drawString(ws2s(L"榮獲 Giraffe大賽金獎"), 0, Font50_.getLineHeight() + Font80_.getLineHeight());
		}
		TextFbo_.end();
		
		//Apply the filter

		//Blur X
		BlurXFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
		BlurXFbo_.begin();
		{
			ofSetColor(255);
			_Blur.begin();
			_Blur.setUniform4fv("vTexOffset", (float*)afTexOffsetX, cKERNEL_SIZE);
				TextFbo_.draw(0,0);
			_Blur.end();
		}
		BlurXFbo_.end();

		//Blur Y
		BlurYFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
		BlurYFbo_.begin();
		{
			ofSetColor(255);
			_Blur.begin();
			_Blur.setUniform4fv("vTexOffset", (float*)afTexOffsetY, cKERNEL_SIZE);
				BlurXFbo_.draw(0,0);
			_Blur.end();
		}
		BlurYFbo_.end();

		//blend with soure
		AfterFilterFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
		AfterFilterFbo_.begin();
		{	
			ofSetColor(0);
			
			BlurYFbo_.draw(-3, 5);

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);

			ofSetColor(255);
			BlurYFbo_.draw(0, 0);
			ofDisableBlendMode();
			
			ofEnableBlendMode(OF_BLENDMODE_ADD);
			TextFbo_.draw(0,0);
			ofDisableBlendMode();
		}
		AfterFilterFbo_.end();

		stTEXT_ELEMENT	stNewElement_;
		stNewElement_.IsEmpty = false;

		//Image
		ofPixels oTmpPixel_;
		AfterFilterFbo_.readToPixels(oTmpPixel_);
		stNewElement_.Image.setFromPixels(oTmpPixel_.getPixels(), AfterFilterFbo_.getWidth(), AfterFilterFbo_.getHeight(), OF_IMAGE_COLOR_ALPHA, true);
		
		//Random offset
		ofPoint oOffset_(-cTEXT_WIDTH/2, ofRandom(-200, 200), 0);
		stNewElement_.Pos = oOffset_;

		//Alpha
		stNewElement_.fAlpha = cBASE_ALPHA;		
		stNewElement_.AnimAlpha.setDuration(1);
		stNewElement_.AnimAlpha.setRepeatType(PLAY_ONCE);
		stNewElement_.AnimAlpha.setCurve(EASE_IN_EASE_OUT);

		_TextElementList[0].push_front(stNewElement_);
	}

	//insert the empty element
	for(int idx_ = 0; idx_ < TEXT_SLIDER_EMPTY_NUMBER; ++idx_)
	{
		stTEXT_ELEMENT	stEmptyElement_;
		stEmptyElement_.IsEmpty = true;
		stEmptyElement_.fAlpha = cBASE_ALPHA;		
		stEmptyElement_.AnimAlpha.setDuration(1);
		stEmptyElement_.AnimAlpha.setRepeatType(PLAY_ONCE);
		_TextElementList[0].push_back(stEmptyElement_);
	}
	_pTextElement = &_TextElementList[0];
	_pNextTextElement = &_TextElementList[1];


	//Initial Animation
	_AnimTimer.setDuration(2);
	_AnimTimer.setRepeatType(PLAY_ONCE);
	_AnimTimer.setCurve(LINEAR);

	_AnimRotate.setDuration(1);
	_AnimRotate.setRepeatType(PLAY_ONCE);
	_AnimRotate.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	_AnimForward.setDuration(1);
	_AnimForward.setRepeatType(PLAY_ONCE);
	_AnimForward.setCurve(AnimCurve::EASE_IN_EASE_OUT);
	_eRotateState = eTEXT_BACKWARD;
	_TmpPos.set(0);
}

//--------------------------------------------------------------
void TextSlider::UpdateTextSlider(float fDelta)
{	
	if(_bStartSlider)
	{	
		//Update Rotate to forward
		_AnimRotate.update(fDelta);
		_AnimForward.update(fDelta);
		switch(_eRotateState)
		{
		case eTEXT_ROTATE_TO_FORWARD:
			{
				if(_AnimRotate.getPercentDone() == 1.0 && _AnimForward.getPercentDone() == 1.0 )
				{
					_eRotateState = eTEXT_FORWARD;
				}
			}
			break;
		case eTEXT_ROTATE_TO_BACKWARD:
			{
				if(_AnimRotate.getPercentDone() == 1.0 && _AnimForward.getPercentDone() == 1.0 )
				{
					_eRotateState = eTEXT_BACKWARD;
					_AnimTimer.resume();
				}
			}
			break;
		}

		//Update Start Pos
		_AnimTimer.update(fDelta);
		if(_AnimTimer.isAnimating())
		{			
			_DrawStartPos = _StartPos - _Interval * _AnimTimer.getCurrentValue();
		}
		else
		{
			_DrawStartPos = _StartPos;
			
			//pop out Element
			stTEXT_ELEMENT&	refElement_ = _pTextElement->back();
			refElement_.fAlpha = cBASE_ALPHA;
			_pNextTextElement->push_front(refElement_);
			_pTextElement->pop_back();
			
			if(_pTextElement->size() <= 0)
			{
				_bStartSlider = false;
				ofNotifyEvent(TextSliderFinishEvent, _bStartSlider, this);
			}
			else
			{
				_AnimTimer.animateFromTo(0.0, 1.0);
			}

			//Loop
			//auto TmpElement_ = _TextElementList.back();
			//_TextElementList.pop_back();
			//TmpElement_.fAlpha = cBASE_ALPHA;
			//_TextElementList.push_front(TmpElement_);
			//_iActiveIdx++;
		}

		//Update All element alphs
		for(int idx_ = 0; idx_ < _pTextElement->size(); ++idx_)
		{
			_pTextElement->at(idx_).AnimAlpha.update(fDelta);
			if(_pTextElement->at(idx_).AnimAlpha.isAnimating())
			{	
				_pTextElement->at(idx_).fAlpha = _pTextElement->at(idx_).AnimAlpha.getCurrentValue();
			}
		}
	}
}

//--------------------------------------------------------------
void TextSlider::DrawTextSlider(float fRotateX, float fRotateY)
{	
	if(!_bStartSlider)
	{
		return;
	}

	ofPushStyle();
	ofPushMatrix();
	{
		ofEnableAlphaBlending();
		//Compute the draw pos
		list<ofPoint> oDrawPos_;
		for(int idx_ = 0; idx_ < _pTextElement->size(); ++idx_)
		{
			ofPoint oPos_ = _DrawStartPos + (_Interval * idx_);
			oDrawPos_.push_front(oPos_);
		}

		ofTranslate(_StartPos);
		ofRotateX(fRotateX);
		ofRotateY(fRotateY);

		//draw pos
		int idx_ = 0;
		list<ofPoint>::iterator oIter_ = oDrawPos_.begin();
		for(auto &TextElement_ : *(_pTextElement))
		{
			if(TextElement_.IsEmpty)
			{
				continue;
			}
			
			ofImage& oImg_ = TextElement_.Image;
			ofPoint& oPos_ = TextElement_.Pos;
			
			ofSetColor(255, TextElement_.fAlpha);
			if(_eRotateState != eTEXT_BACKWARD && _iActiveIdx == idx_)
			{
				ofPushMatrix();
				{
					ofTranslate(ofPoint(0, 0, _AnimForward.getCurrentPosition().z));
					ofRotateY(_AnimRotate.getCurrentValue());
					oImg_.draw(-oImg_.width/2 + oPos_.x,-oImg_.height/2 + oPos_.y);
				}
				ofPopMatrix();
			}
			else
			{
				oImg_.draw(-oImg_.width/2 + oPos_.x,-oImg_.height/2 + oPos_.y, oIter_->z);
			}

			if(oIter_->z > -1000.0 && TextElement_.fAlpha == cBASE_ALPHA)
			{
				TextElement_.AnimAlpha.animateFromTo(cBASE_ALPHA, 255);
				_iActiveIdx = idx_;
			}

			++oIter_;
			++idx_;
		}
		ofDisableAlphaBlending();
	}
	ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void TextSlider::ResetTextSlider()
{
	_bStartSlider = false;
	_eRotateState = eTEXT_BACKWARD;
	_TmpPos.set(0);
	this->SwitchPtr();
}

//--------------------------------------------------------------
void TextSlider::PlayTextSlider()
{
	_AnimTimer.animateFromTo(0.0, 1.0);
	_bStartSlider = true;
	_iActiveIdx = -1;
}

//--------------------------------------------------------------
void TextSlider::RotateToForward()
{
	if((_eRotateState == eTEXT_BACKWARD || _eRotateState == eTEXT_ROTATE_TO_BACKWARD) && _iActiveIdx != -1)
	{
		_AnimTimer.pause();

		_AnimRotate.animateFromTo(0, 90);
		_eRotateState = eTEXT_ROTATE_TO_FORWARD;

		//get position
		_TmpPos = _DrawStartPos + (_Interval * (_pTextElement->size() - _iActiveIdx - 1));

		_AnimForward.setPosition(_TmpPos);
		_AnimForward.animateTo(ofPoint(_TmpPos.x, _TmpPos.y, cFORWARD_Z));
	}
}

//--------------------------------------------------------------
void TextSlider::RotateToBackward()
{
	if(_eRotateState == eTEXT_FORWARD || _eRotateState == eTEXT_ROTATE_TO_FORWARD)
	{
		_AnimRotate.animateFromTo(90, 0);	
		_AnimForward.animateTo(_TmpPos);
		_eRotateState = eTEXT_ROTATE_TO_BACKWARD;
	}
}

//--------------------------------------------------------------
void TextSlider::CreateGaussian(float (&afWeight)[cKERNEL_SIZE], float (&afOffset_)[cKERNEL_SIZE])
{
	//index
	int iIndex_ = (cKERNEL_SIZE - 1)/2 * -1;
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; idx_++, iIndex_++)
	{
		afOffset_[idx_] = iIndex_;
	}
	
	float fA_ = 1/sqrt(2 * PI * cPOW_SIGMA);
	float fTotal_ = 0.0;
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; idx_++)
	{
		float fX_ = afOffset_[idx_];
		afWeight[idx_] = fA_ * exp(-1/2.0 * fX_ * fX_ * 1/cPOW_SIGMA); 
		fTotal_ += afWeight[idx_];
	}

	//normalized
	float fNormalized_ = 1/fTotal_;
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; idx_++)
	{
		afWeight[idx_] *= fNormalized_;
	}
}

//--------------------------------------------------------------
void TextSlider::SwitchPtr()
{	
	if(_pTextElement->size() == 0 && _pNextTextElement->size() > 0)
	{
		auto pTmp_ = _pTextElement;
		_pTextElement = _pNextTextElement;
		_pNextTextElement = pTmp_;
	}
}

//--------------------------------------------------------------
string TextSlider::ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
    string strTo( size_needed, 0 );
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
    return strTo;
}