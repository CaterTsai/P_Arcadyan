#include "InfoDisplay.h"

//--------------------------------------------------------------
void InfoDisplay::setupInfoDisplay(float fChangeTimeout)
{
	_fChangeTimeout = fChangeTimeout;

	this->initWeather();
	this->initDisplay();
	
	_bIsDisplay = false;
	_eInfoState = eSTATE_UNDISPLAY;
	_AnimFadeAlpha.setCurve(AnimCurve::EASE_IN);
}

//--------------------------------------------------------------
void InfoDisplay::updateInfoDisplay(float fDelta_)
{
	if(!_bIsDisplaySetup)
	{
		return;
	}

	if(_bIsDisplay)
	{
		_AnimFadeAlpha.update(fDelta_);
		_AnimBackplaneAlpha.update(fDelta_);
		switch(_eInfoState)
		{
		case eSTATE_CHINESE_FADE_IN:
			{
				if(_AnimFadeAlpha.getPercentDone() == 1.0)
				{
					_eInfoState = eSTATE_CHINESE_DISPLAY;
					_fChange = _fChangeTimeout;
				}
			}
			break;
		case eSTATE_CHINESE_DISPLAY:
			{
				_fChange -= fDelta_;
				if(_fChange <= 0.0)
				{
					_eInfoState = eSTATE_CHINESE_FADE_OUT;
					_AnimFadeAlpha.setDuration(0.5);
					_AnimFadeAlpha.animateFromTo(255, 0);
				}
			}
			break;
		case eSTATE_CHINESE_FADE_OUT:
			{
				if(_AnimFadeAlpha.getPercentDone() == 1.0)
				{
					_bIsChinese = false;
					this->updateDisplay();

					_AnimFadeAlpha.setDuration(0.5);
					_AnimFadeAlpha.animateFromTo(0, 255);
					_eInfoState = eSTATE_ENGLISH_FADE_IN;
				}
			}
			break;
		case eSTATE_ENGLISH_FADE_IN:
			{
				if(_AnimFadeAlpha.getPercentDone() == 1.0)
				{
					_eInfoState = eSTATE_ENGLISH_DISPLAY;
					_fChange = _fChangeTimeout;
				}
			}
			break;
		case eSTATE_ENGLISH_DISPLAY:
			{
				_fChange -= fDelta_;
				if(_fChange <= 0.0)
				{
					_eInfoState = eSTATE_ENGLISH_FADE_OUT;
					_AnimFadeAlpha.setDuration(1.0);
					_AnimFadeAlpha.animateFromTo(255, 0);

					_AnimBackplaneAlpha.setDuration(2.0);
					_AnimBackplaneAlpha.animateFromTo(255, 0);
				}
			}
			break;
		case eSTATE_ENGLISH_FADE_OUT:
			{
				if(_AnimBackplaneAlpha.getPercentDone() == 1.0)
				{
					_eInfoState = eSTATE_FINISH;
					_bIsDisplay = false;

					ofNotifyEvent(FinishEvent, _bIsDisplay, this);
				}
			}
			break;
		}
	}
}

//--------------------------------------------------------------
void InfoDisplay::drawInfoDisplay()
{
	if(!_bIsDisplaySetup)
	{
		return;
	}

	//Show backplane
	ofPushStyle();
		ofEnableAlphaBlending();

		ofSetColor(255, _AnimBackplaneAlpha.getCurrentValue());
		_Backplane.draw(0, 0);

		ofSetColor(255, _AnimFadeAlpha.getCurrentValue());
		ofPushMatrix();		
			ofTranslate(215, 215);
			ofRotateY(60);

			ofPushMatrix();
				ofTranslate(0, _DisplayRef.getHeight());
				ofScale(1, -1);
				ofTranslate(0, -_DisplayRef.getHeight());
				_DisplayRef.draw(0, 0);
			ofPopMatrix();
		
			_Display.draw(0, 0);
		ofPopMatrix();
		ofDisableAlphaBlending();
	ofPopStyle();
}

//--------------------------------------------------------------
void InfoDisplay::startDisplay(float fFadeTime)
{	
	_bIsChinese = true;
	_bIsDisplay = true;
	_eInfoState = eSTATE_CHINESE_FADE_IN;

	this->updateDisplay();
	
	_AnimFadeAlpha.setDuration(fFadeTime);
	_AnimFadeAlpha.animateFromTo(0, 255);

	_AnimBackplaneAlpha.setDuration(fFadeTime);
	_AnimBackplaneAlpha.animateFromTo(0, 255);
}

//--------------------------------------------------------------
void InfoDisplay::initWeather()
{
	_strActionUrl = "http://weather.yahooapis.com/forecastrss?w=2306185&u=c";

	ofAddListener(_HttpUtils.newResponseEvent, this, &InfoDisplay::newHttpRespone);
	_HttpUtils.start();

	_strTemperature		= "";
	_bHaveWeatherInfo	= false;
	_eWeatherCode = eWEATHER_UNKNOW;
}

//--------------------------------------------------------------
void InfoDisplay::getNowWeatherInfo()
{
	ofxHttpForm	HttpForm_;
	HttpForm_.action = _strActionUrl;
	HttpForm_.method = OFX_HTTP_GET;

	_HttpUtils.addForm(HttpForm_);
}

//--------------------------------------------------------------
void InfoDisplay::newHttpRespone(ofxHttpResponse& Response)
{
	ofxXmlSettings	oXml_;
	int iWeatherCode_ = 3200;
	oXml_.clear();
	if(oXml_.loadFromBuffer(ofToString(Response.responseBody)))
	{
		ofLogNotice()<<"Load weather information success";

		oXml_.pushTag("rss");
		oXml_.pushTag("channel");
		oXml_.pushTag("item");

		iWeatherCode_ = ofToInt(oXml_.getAttribute("yweather:condition", "code", "false", 0, true));
		_strTemperature = oXml_.getAttribute("yweather:condition", "temp", "false", 0, true) + ws2s(L"°C");
		
		oXml_.popTag();
		oXml_.popTag();
		oXml_.popTag();

		ProcessingWeather(iWeatherCode_);
		_bHaveWeatherInfo	= true;
	}
}

//--------------------------------------------------------------
void InfoDisplay::ProcessingWeather(int iWeatherCode)
{
	switch(iWeatherCode)
	{
	case 27:
	case 28:
	case 29:
	case 30:
	case 44:
		{
			_eWeatherCode = eWEATHER_PARTLY_CLOUDY;
		}
		break;
	case 0:
	case 1:
	case 2:
	case 5:
	case 6:
	case 8:
	case 9:
	case 35:
		{
			_eWeatherCode = eWEATHER_RAIN;
		}
		break;
	case 32:
	case 33:
	case 34:
	case 36:
		{
			_eWeatherCode = eWEATHER_SUN;
		}
		break;
	case 3:
	case 4:
	case 37:
	case 38:
	case 39:
	case 45:
		{
			_eWeatherCode = eWEATHER_THUNDER;
		}
		break;
	default:
		{
			_eWeatherCode = eWEATHER_COLUDY;
		}
		break;
	}

}

//--------------------------------------------------------------
void InfoDisplay::initDisplay()
{
	_Display.allocate(cINFO_WIDTH, cINFO_HEIGHT, GL_RGBA);
	_DisplayRef.allocate(cINFO_WIDTH, cINFO_HEIGHT, GL_RGBA);
	_bIsDisplaySetup = false;

	//load fonts
	_FontMS80W.loadFont("fonts/msjhbd.ttf", 80);
	_FontMS80W.setLetterSpacing(1.3);
	_FontMS80.loadFont("fonts/msjhbd.ttf", 80);
	_FontMS80.setSpaceSize(1.05);
	_FontMS50.loadFont("fonts/msjhbd.ttf", 50);
	_FontMS40.loadFont("fonts/msjhbd.ttf", 40);

	//shader
	_Shadow.load("", "shader/shadow.frag");
	_Blur.load("", "shader/GaussianBlur.frag");

	ofImage Img_;
	Img_.loadImage("images/weather/w_partly_cloudy.png");
	_WeatherIcon[eWEATHER_PARTLY_CLOUDY] = Img_;
	Img_.loadImage("images/weather/w_cloudy.png");
	_WeatherIcon[eWEATHER_COLUDY] = Img_;
	Img_.loadImage("images/weather/w_rain.png");
	_WeatherIcon[eWEATHER_RAIN] = Img_;
	Img_.loadImage("images/weather/w_sun.png");
	_WeatherIcon[eWEATHER_SUN] = Img_;
	Img_.loadImage("images/weather/w_thunder.png");
	_WeatherIcon[eWEATHER_THUNDER] = Img_;

	//Back plane
	_Backplane.loadImage("images/Infodisplay_mask.png");

	_fChange = _fChangeTimeout;
	_bIsChinese = true;
}

//--------------------------------------------------------------
void InfoDisplay::updateDisplay()
{
	if(_bHaveWeatherInfo)
	{
		//Draw Weather Info
		ofFbo	Canvas_;
		Canvas_.allocate(cINFO_WIDTH, cINFO_HEIGHT, GL_RGBA);
		ofEnableAlphaBlending();
		Canvas_.begin();
		{
			ofRectangle oWelcomRect_, oRect_;
			float	fNowHeight_ = 0.0;
			float	fNowWidth_ = 0.0;

			//Draw Welcome
			ofSetColor(240);
			if(_bIsChinese)
			{	
				oWelcomRect_ = _FontMS80W.getStringBoundingBox(ws2s(L"歡迎來到智易"), 0, 0);
				_FontMS80W.drawString(ws2s(L"歡迎來到智易"), cINFO_WIDTH/2 - oWelcomRect_.getWidth()/2, 0 + oWelcomRect_.getHeight());
			}
			else
			{
				oWelcomRect_ = _FontMS50.getStringBoundingBox("Welcome to Arcadyan", 0, 0);
				_FontMS50.drawString("Welcome to Arcadyan", cINFO_WIDTH/2 - oWelcomRect_.getWidth()/2, 0 + oWelcomRect_.getHeight());
			}

			//fNowHeight_ = oWelcomRect_.getHeight() + 70;
			//fNowWidth_ = cINFO_WIDTH/2 - oWelcomRect_.getWidth()/2 + oWelcomRect_.getWidth()/6;
			fNowHeight_ = 167;
			fNowWidth_ = 133;

			//Draw Weather Icon
			ofSetColor(255);
			ofImage WeahterIcon_ = _WeatherIcon[eWEATHER_PARTLY_CLOUDY];
			if(_WeatherIcon.find(_eWeatherCode) != _WeatherIcon.end())
			{	
				WeahterIcon_ = _WeatherIcon[_eWeatherCode];
			}
			_WeatherIcon[_eWeatherCode].draw(fNowWidth_ - _WeatherIcon[_eWeatherCode].getWidth()/2, fNowHeight_);

			//Draw Temperature
			ofSetColor(240);
			oRect_ = _FontMS50.getStringBoundingBox(_strTemperature, 0, 0);
			_FontMS50.drawString(_strTemperature, fNowWidth_ - oRect_.getWidth()/2, fNowHeight_ + WeahterIcon_.getHeight() + 100);

			fNowHeight_ += WeahterIcon_.getHeight()/2;
			fNowWidth_ = cINFO_WIDTH/2 - oWelcomRect_.getWidth()/2 + (oWelcomRect_.getWidth()/6) * 4;

			//Draw City
			ofSetColor(240);
			oRect_ = _FontMS40.getStringBoundingBox("HsingChu Taiwan", 0, 0);
			_FontMS40.drawString("HsingChu-Taiwan", fNowWidth_ - oRect_.getWidth()/2, fNowHeight_ + oRect_.getHeight()/2);

			fNowHeight_ += oRect_.getHeight();

			//Draw Time
			ofSetColor(240);
			string strTime_ = ofGetTimestampString("%A %h:%M");
			_strTimeM = ofGetTimestampString("%M");
			oRect_ = _FontMS80.getStringBoundingBox(strTime_, 0, 0);
			_FontMS80.drawString(strTime_, fNowWidth_ - 483.0/2, fNowHeight_ + oRect_.getHeight());
			
			
		}
		Canvas_.end();
		
		//Draw Shadow
		ofSetColor(255);
		ofPoint Offset_(-5, 5);
		_Display.begin();
		{
			ofClear(0);
			_Shadow.begin();
				Canvas_.draw(Offset_);
			_Shadow.end();
			Canvas_.draw(0, 0);
		}
		_Display.end();

		//Draw Ref
		_DisplayRef.begin();
		{
			ofClear(255);
			_Blur.begin();
				_Display.draw(0, 0);
			_Blur.end();
		}
		_DisplayRef.end();

		_bIsDisplaySetup = true;
		ofDisableAlphaBlending();
	}
}

//--------------------------------------------------------------
string InfoDisplay::ws2s(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, 0);
    string strTo( size_needed, 0 );
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, 0);
    return strTo;
}