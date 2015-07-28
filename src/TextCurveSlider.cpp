#include "TextCurveSlider.h"

void TextCurveSlider::updateCurveSlider(float fDelta, ofRectangle& CtrlArea)
{
	if(!_bStartAnim)
	{
		return;
	}

	for(auto& Element_ : _ElementList )
	{
		Element_.update(fDelta);
	}

	_CtrlArea = CtrlArea;

	//Check Ctrl
	auto Iter_ = _ElementList.rbegin();
	for(; Iter_ != _ElementList.rend(); ++Iter_)
	{
		if(Iter_->fAlpha > cBASE_ALPHA)
		{
			break;
		}
	}
	if(Iter_ != _ElementList.rend() && Iter_->TriggerArea.intersects(CtrlArea))
	{
		if(_eRotateState == eTEXT_CAN_FORWARD)
		{
			this->RotateToForward();
		}
		else if(_eRotateState == eTEXT_CAN_GOBACK)
		{
			this->RotateToBackward();
		}
	}

	//rotate
	this->updateRotate(fDelta);
	if(_eRotateState != eTEXT_CAN_FORWARD && _eRotateState != eTEXT_BACKWARD)
	{
		return;
	}

	//start next element
	if(_IterElement == _ElementList.end())
	{
		//Check last element
		_stTEXT_CURVE_ELEMENT Last_ = _ElementList.back();
		if(Last_.fAnimDuraction.hasFinishedAnimating())
		{
			//Finish
			_bStartAnim = false;
			ofNotifyEvent(TextSliderFinishEvent, _bStartAnim, this);

		}
		return;
	}

	_fTimer += fDelta;
	if(_fTimer < _fInterval)
	{
		return;
	}
	_fTimer = 0;
	
	_IterElement->fAnimDuraction.animateFromTo(0.0, 1.0);
	_IterElement->fAnimAlpha.reset();
	_IterElement->fAlpha = cBASE_ALPHA;
	_IterElement++;
}

//--------------------------------------------------------------
void TextCurveSlider::drawCurveSlider()
{
	if(_bDrawCurve)
	{
		this->drawCurve();
	}
	
	if(!_bStartAnim)
	{
		return;
	}

	ofPushStyle();
	ofPushMatrix();
	{	
		ofEnableAlphaBlending();
		ofTranslate(_DrawPos);
		ofRotateY(_fRotate);
		
		for(auto RIter_ = _ElementList.rbegin(); RIter_ < _ElementList.rend(); ++RIter_)
		{
			ofPoint Pos_;
			GLdouble screenX_, screenY_, screenZ_;
			GLdouble screen2X_, screen2Y_, screen2Z_;

			float fRotate_;
			if(RIter_->fAnimDuraction.hasFinishedAnimating())
			{
				continue;
			}

			if(!RIter_->bIsRotate)
			{
				float fDuraction_ = RIter_->fAnimDuraction.getCurrentValue();
				
				if(!this->getPosition(fDuraction_, Pos_, fRotate_))
				{
					continue;
				}

				ofPushMatrix();
				ofTranslate(Pos_);
				ofRotateY(60);
				ofSetColor(255, 255, 255, RIter_->fAlpha);
				
				RIter_->TextImg.draw(	-RIter_->TextImg.width/2 + RIter_->Offset.x,
										-RIter_->TextImg.height/2 + RIter_->Offset.y);

				glGetDoublev(GL_MODELVIEW_MATRIX, _mvM);
				glGetDoublev(GL_PROJECTION_MATRIX, _pM);
				glGetIntegerv(GL_VIEWPORT, _vp);

				ofPopMatrix();
			}
			else
			{
				ofPushMatrix();
				ofTranslate(_AnimForward.getCurrentPosition());
				ofRotateY(_AnimRotate.getCurrentValue());
				ofSetColor(255, 255, 255, RIter_->fAlpha);
				RIter_->TextImg.draw(	-RIter_->TextImg.width/2 + RIter_->Offset.x,
										-RIter_->TextImg.height/2 + RIter_->Offset.y,
										0);

				glGetDoublev(GL_MODELVIEW_MATRIX, _mvM);
				glGetDoublev(GL_PROJECTION_MATRIX, _pM);
				glGetIntegerv(GL_VIEWPORT, _vp);
				ofPopMatrix();
			}

			//Get Screen position
			gluProject(	-RIter_->TextImg.width/2 + RIter_->Offset.x,
						-RIter_->TextImg.height/2 + RIter_->Offset.y,
						0,
						_mvM, _pM, _vp, &screenX_, &screenY_, &screenZ_);

			gluProject(	RIter_->TextImg.width/2 + RIter_->Offset.x,
						RIter_->TextImg.height/2 + RIter_->Offset.y,
						0,
						_mvM, _pM, _vp, &screen2X_, &screen2Y_, &screen2Z_);

			ofPoint Pos1_, Pos2_;

			Pos1_.x = screenX_;
			Pos1_.y = ofGetWindowHeight() - screenY_;
			Pos1_.z = 0;

			Pos2_.x = screen2X_;
			Pos2_.y = ofGetWindowHeight() - screen2Y_;
			Pos2_.z = 0;

			RIter_->TriggerArea.set(ofRectangle(Pos1_, Pos2_));
		}
	}
	ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void TextCurveSlider::drawTriggerRect()
{	
	auto Iter_ = _ElementList.rbegin();
	for(; Iter_ != _ElementList.rend(); ++Iter_)
	{
		if(Iter_->fAlpha > cBASE_ALPHA)
		{
			break;
		}
	}

	if(Iter_ == _ElementList.rend())
	{
		return;
	}

	ofPushStyle();
	{
		ofNoFill();
		ofSetLineWidth(3);
		ofSetColor(255, 0, 0);

		ofRect(Iter_->TriggerArea);
	}	
	ofPopStyle();	
}

//--------------------------------------------------------------
void TextCurveSlider::setCurveSliderData(string strDataXML, float fDuration, float fInterval)
{
	_ElementList.clear();
	_fInterval = fInterval;

	//XML
	ofxXmlSettings	xmlLoader_;
	if(!xmlLoader_.loadFile(strDataXML))
	{
		ofLog(OF_LOG_ERROR, "Load text slider failed");
		return;
	}
	xmlLoader_.pushTag("ARCADYAN_TEXT_SLIDER_DATA");
	int iNum_ = xmlLoader_.getNumTags("TEXT_SLIDER");

	for(int idx_ = 0; idx_ < iNum_; ++idx_)
	{		
		string strYear_ = xmlLoader_.getValue("TEXT_SLIDER:YEAR", "", idx_);
		string strText1_ = xmlLoader_.getValue("TEXT_SLIDER:TEXT1", "", idx_);
		string strText2_ = xmlLoader_.getValue("TEXT_SLIDER:TEXT2", "", idx_);
		string strText3_ = xmlLoader_.getValue("TEXT_SLIDER:TEXT3", "", idx_);

		stTEXT_CURVE_ELEMENT	NewElement_;
		this->createText(NewElement_.TextImg, strYear_, strText1_, strText2_, strText3_);
		
		//Random offset
		ofPoint oOffset_(-cTEXT_WIDTH/2, ofRandom(-200, 200), 0);
		NewElement_.Offset = oOffset_;

		//Position
		NewElement_.fAnimDuraction.setDuration(fDuration);
		NewElement_.fAnimDuraction.setCurve(LINEAR);
		NewElement_.fAnimDuraction.setRepeatType(PLAY_ONCE);

		//Alpha
		NewElement_.fAlpha = cBASE_ALPHA;		
		NewElement_.fAnimAlpha.setDuration(1.0);
		NewElement_.fAnimAlpha.setRepeatType(PLAY_ONCE);
		NewElement_.fAnimAlpha.setCurve(EASE_IN_EASE_OUT);

		_ElementList.push_back(NewElement_);
	}
	_IterElement = _ElementList.begin();
}

//--------------------------------------------------------------
void TextCurveSlider::setCurveSliderPath(ofPoint StartPos, ofPoint EndPos, ofPoint C1, ofPoint C2, int iResolution)
{
	double dUnitT_ = 1.0/(iResolution-1);
	double dT_ = 0.0;
	for(int idx_ = 0; idx_ < iResolution; idx_++)
	{
		stTEXT_CURVE	TmpCurve_;

		dT_ = dUnitT_ * idx_;
		TmpCurve_.IsDisplay = true;
		TmpCurve_.Position = ofBezierPoint(StartPos, C1, C2, EndPos, dT_);
		ofPoint Vector_ = ofBezierTangent(StartPos, C1, C2, EndPos, dT_).normalized();
		if(Vector_.x <= 0)
		{
			TmpCurve_.fRotate = Vector_.angle(ofVec3f(0, 0, -1));
		}
		else
		{
			TmpCurve_.fRotate = -Vector_.angle(ofVec3f(0, 0, -1));
		}
		_TextCurve.push_front(TmpCurve_);
	}
}

//--------------------------------------------------------------
void TextCurveSlider::setDisablePath(float fStartT, float fEndT)
{
	if(fStartT > fEndT)
	{
		swap(fStartT, fEndT);
	}
	int StartIdx_ = static_cast<int>(_TextCurve.size() * fStartT + 0.5);
	int EndIdx_ = static_cast<int>(_TextCurve.size() * fEndT + 0.5);


	for(;StartIdx_ < EndIdx_; StartIdx_++)
	{
		_TextCurve.at(StartIdx_).IsDisplay = false;
	}
}

//--------------------------------------------------------------
void TextCurveSlider::startCurveSlider()
{
	if(_bStartAnim)
	{
		return;
	}

	for(auto Iter_ = _ElementList.begin(); Iter_ != _ElementList.end(); ++Iter_)
	{
		Iter_->fAlpha = cBASE_ALPHA;
		Iter_->fAnimAlpha.reset();
		Iter_->bIsRotate = false;
		Iter_->fAnimDuraction.reset(0);
	}

	_IterElement = _ElementList.begin();
	_IterElement->fAnimDuraction.animateFromTo(0.0, 1.0);
	_fTimer = 0;
	_IterElement++;
	_bStartAnim = true;
	_eRotateState = eTEXT_CAN_FORWARD;
}

//--------------------------------------------------------------
void TextCurveSlider::drawCurve()
{
	ofPushMatrix();
	ofPushStyle();
	{
		ofTranslate(_DrawPos);
		ofRotateY(_fRotate);
		ofSetColor(255);
		for(auto& Pos_ : _TextCurve)
		{	
			ofRect(Pos_.Position.x, Pos_.Position.y, Pos_.Position.z, 50, 50);
		}
	}
	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
bool TextCurveSlider::getPosition(float fDuraction, ofPoint& Position, float& Degree)
{
	int index_ = static_cast<int>(floor(_TextCurve.size() * fDuraction));

	try
	{
		Position = _TextCurve.at(index_).Position;
		Degree = _TextCurve.at(index_).fRotate;
		return _TextCurve.at(index_).IsDisplay;

	} catch(const exception &e)
	{
		ofLog(OF_LOG_ERROR, e.what());
		return false;
	}
}

//--------------------------------------------------------------
bool TextCurveSlider::getPosition(float fDuraction, ofPoint& Position)
{
	float fDegree_;
	return this->getPosition(fDuraction, Position, fDegree_);
}

#pragma region Rotate
//--------------------------------------------------------------
//Rotate
void TextCurveSlider::RotateToForward()
{
	if(!_bStartAnim)
	{		
		return;
	}

	if(_eRotateState == eTEXT_CAN_FORWARD)
	{
		if(!this->getRotateElement(_IterRotate))
		{
			return;
		}

		if(_IterRotate->fAnimDuraction.hasFinishedAnimating())
		{
			return;
		}

		_IterRotate->bIsRotate = true;
		
		this->getPosition(_IterRotate->fAnimDuraction.getCurrentValue(), _RegisterPos, _RegisterRotate);
		
		//_AnimRotate.animateFromTo(_RegisterRotate, 90);
		_AnimRotate.animateFromTo(60, 90);
		_AnimForward.setPosition(_RegisterPos);
		_AnimForward.animateTo(ofPoint(_RegisterPos.x, _RegisterPos.y, cFORWARD_Z));

		this->pauseSlider();		
		_eRotateState = eTEXT_ROTATE_TO_FORWARD;
	}
}

//--------------------------------------------------------------
void TextCurveSlider::RotateToBackward()
{
	if(!_bStartAnim)
	{		
		return;
	}

	if(_eRotateState == eTEXT_CAN_GOBACK)
	{
		//_AnimRotate.animateFromTo(90, _RegisterRotate);
		_AnimRotate.animateFromTo(90, 60);
		_AnimForward.animateTo(_RegisterPos);
		_eRotateState = eTEXT_ROTATE_TO_BACKWARD;
	}
}

//--------------------------------------------------------------
void TextCurveSlider::updateRotate(float fDelta)
{
	_AnimRotate.update(fDelta);
	_AnimForward.update(fDelta);

	switch(_eRotateState)
	{
	case eTEXT_ROTATE_TO_FORWARD:
		{
			if( _AnimRotate.getPercentDone() == 1.0 && _AnimForward.getPercentDone() == 1.0 )
			{
				_eRotateState = eTEXT_FORWARD;
				_fRotateTimer = cCAN_GOBCAK_TIME;
			}
		}
		break;
	case eTEXT_FORWARD:
		{
			_fRotateTimer -= fDelta;
			if(_fRotateTimer <= 0.0)
			{
				_eRotateState = eTEXT_CAN_GOBACK;
			}
		}
		break;
	case eTEXT_ROTATE_TO_BACKWARD:
		{
			if( _AnimRotate.getPercentDone() == 1.0 && _AnimForward.getPercentDone() == 1.0 )
			{
				_IterRotate->bIsRotate = false;
				_eRotateState = eTEXT_BACKWARD;
				_fRotateTimer = cCAN_FORWARD_TIME;
				this->resumeSlider();
			}
		}
		break;
	case eTEXT_BACKWARD:
		{
			_fRotateTimer -= fDelta;
			if(_fRotateTimer <= 0.0)
			{
				_eRotateState = eTEXT_CAN_FORWARD;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void TextCurveSlider::pauseSlider()
{
	for(auto& Element_ : _ElementList)
	{
		Element_.fAnimDuraction.pause();
	}
}

//--------------------------------------------------------------
void TextCurveSlider::resumeSlider()
{
	for(auto& Element_ : _ElementList)
	{
		Element_.fAnimDuraction.resume();
	}
}

//--------------------------------------------------------------
bool TextCurveSlider::getRotateElement(vector<_stTEXT_CURVE_ELEMENT>::iterator& refIter)
{
	if(!_bStartAnim || _eRotateState != eTEXT_CAN_FORWARD)
	{
		return false;
	}

	bool bHaveActive_ = false;
	for(auto Iter = _ElementList.begin(); Iter != _ElementList.end(); ++Iter)
	{
		if(Iter->fAlpha <= cBASE_ALPHA)
		{
			break;
		}
		bHaveActive_ = true;
		refIter = Iter;
	}
	return bHaveActive_;
}
#pragma endregion

#pragma region Contanct
//--------------------------------------------------------------
//Contanct
void TextCurveSlider::setupContanct()
{
	if(_bIsContanctSetup)
	{
		return;
	}
	//Filter
	_Blur.load("", "shader/GaussianBlur_Dynamic.frag");

	//font
	_Font80.loadFont("fonts/msjhbd.ttf", 80);
	_Font30.loadFont("fonts/msjhbd.ttf", 30);

	//Initial gaussian filter kernel
	float afBlurWeight_[cKERNEL_SIZE] = {0};
	float afOffset_[cKERNEL_SIZE] = {0};
	this->CreateGaussian(afBlurWeight_, afOffset_);

	//X
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; ++idx_)
	{
		_afTexOffsetX[idx_][0] = afOffset_[idx_];
		_afTexOffsetX[idx_][1] = 0;
		_afTexOffsetX[idx_][2] = 0;
		_afTexOffsetX[idx_][3] = afBlurWeight_[idx_];
	}

	//Y
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; ++idx_)
	{
		_afTexOffsetY[idx_][0] = 0;
		_afTexOffsetY[idx_][1] = afOffset_[idx_];
		_afTexOffsetY[idx_][2] = 0;
		_afTexOffsetY[idx_][3] = afBlurWeight_[idx_];
	}
	_bIsContanctSetup = true;
}

//--------------------------------------------------------------
void TextCurveSlider::createText(ofImage& TextImg, string strYear, string strText1, string strText2, string strText3)
{
	if(!_bIsContanctSetup)
	{
		this->setupContanct();
	}

	ofPushStyle();
	ofDisableBlendMode();
	ofFbo oTextFbo_, oBlurXFbo_, oBlurYFbo_, oAfterFilterFbo_, oShadowFbo_;
		
	//Combine the text to an image
	oTextFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
	oTextFbo_.begin();
	{	
		ofSetColor(0,255,40);

		int iDrawHeight_ = _Font80.getLineHeight();
		_Font80.drawString(strYear, 0, _Font80.getLineHeight());		

		iDrawHeight_ += _Font30.getLineHeight();
		_Font30.drawString(strText1, 0, iDrawHeight_);

		iDrawHeight_ += _Font30.getLineHeight();
		_Font30.drawString(strText2, 0, iDrawHeight_);

		iDrawHeight_ += _Font30.getLineHeight();
		_Font30.drawString(strText3, 0, iDrawHeight_);
	}
	oTextFbo_.end();
		
	//Apply the filter
	//Blur X
	oBlurXFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
	oBlurXFbo_.begin();
	{
		//ofClear(255,255,255, 0);
		ofSetColor(255);
		_Blur.begin();
		_Blur.setUniform4fv("vTexOffset", (float*)_afTexOffsetX, cKERNEL_SIZE);
			oTextFbo_.draw(0,0);
		_Blur.end();
	}
	oBlurXFbo_.end();

	//Blur Y
	oBlurYFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
	oBlurYFbo_.begin();
	{
		//ofClear(255,255,255, 0);
		ofSetColor(255);
		_Blur.begin();
		_Blur.setUniform4fv("vTexOffset", (float*)_afTexOffsetY, cKERNEL_SIZE);
			oBlurXFbo_.draw(0,0);
		_Blur.end();
	}
	oBlurYFbo_.end();
		
	//blend with soure
	oAfterFilterFbo_.allocate(cTEXT_WIDTH, cTEXT_HEIGHT, GL_RGBA);
	oAfterFilterFbo_.begin();
	{	
		ofSetColor(0);
		oBlurYFbo_.draw(-3, 5);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);

		ofSetColor(255);
		oBlurYFbo_.draw(0, 0);
		ofDisableBlendMode();

		ofEnableBlendMode(OF_BLENDMODE_ADD);

		//ofSetColor(255);
		oTextFbo_.draw(0,0);
		ofDisableBlendMode();
	}
	oAfterFilterFbo_.end();

	//Image
	ofPixels oTmpPixel_;
	TextImg.clear();
	oAfterFilterFbo_.readToPixels(oTmpPixel_);
	TextImg.setFromPixels(oTmpPixel_.getPixels(), oAfterFilterFbo_.getWidth(), oAfterFilterFbo_.getHeight(), OF_IMAGE_COLOR_ALPHA, true);

	ofPopStyle();
}

//--------------------------------------------------------------
void TextCurveSlider::CreateGaussian(float (&afWeight)[cKERNEL_SIZE], float (&afOffset_)[cKERNEL_SIZE])
{
	//index
	int iIndex_ = (cKERNEL_SIZE - 1)/2 * -1;
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; idx_++, iIndex_++)
	{
		afOffset_[idx_] = iIndex_;
	}
	
	float fA_ = 1/sqrt(2 * PI * POW_SIGMA);
	float fTotal_ = 0.0;
	for(int idx_ = 0; idx_ < cKERNEL_SIZE; idx_++)
	{
		float fX_ = afOffset_[idx_];
		afWeight[idx_] = fA_ * exp(-1/2.0 * fX_ * fX_ * 1/POW_SIGMA); 
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
string TextCurveSlider::ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
    string strTo( size_needed, 0 );
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
  
	return strTo;
}

#pragma endregion
