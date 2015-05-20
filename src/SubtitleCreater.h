#ifndef ARCADYAN_SUBTITLE_CREATER
#define ARCADYAN_SUBTITLE_CREATER

#include "protocol.h"
#include "ofxTrueTypeFontUC.h"

class SubtitleCreater
{
public:
	void Subtitle2Image(string Subtitle, ofImage& output, ofImage& backplane)
	{
		output.clear();
		if(!_SubtitleFont.isLoaded())
		{
			return;
		}
		ofRectangle TextRect_ = _SubtitleFont.getStringBoundingBox(Subtitle, 0, 0);

		float fNewWidth_, fNewHeight_;
		if(backplane.isAllocated())
		{
			fNewWidth_ = TextRect_.getWidth() * 2.0;
			fNewHeight_ = TextRect_.getHeight() * 1.2;
		}

		ofFbo ImgFbo_;	
		ImgFbo_.allocate(fNewWidth_, fNewHeight_, GL_RGBA);
		ImgFbo_.begin();
		{
			ofClear(255, 255, 255, 0);

			if(backplane.isAllocated())
			{
				ofSetColor(255);
				backplane.draw(0,0, fNewWidth_, fNewHeight_);
			}

			ofSetColor(_SubtitleColor);
			_SubtitleFont.drawString(	Subtitle, 
						fNewWidth_/2 - TextRect_.getWidth()/2, 
						fNewHeight_/2 + TextRect_.getHeight()/2
			);
		}
		ImgFbo_.end();

		ofPixels oTmpPixel_;
		ImgFbo_.readToPixels(oTmpPixel_);
		output.setFromPixels(oTmpPixel_.getPixels(), fNewWidth_, fNewHeight_, OF_IMAGE_COLOR_ALPHA, true);

	}

	inline void setSubtitleFont(string FontPath, int iFontSize)
	{
		if(!_SubtitleFont.loadFont(FontPath, iFontSize))
		{
			ofLog(OF_LOG_ERROR, "[SubtitleCreater]Load font file failed");
		}
	}

	inline void setSubtitleColor(ofColor Color)
	{
		_SubtitleColor = Color;
	}

public:
	ofColor	_SubtitleColor;
	ofxTrueTypeFontUC _SubtitleFont;
};



#endif // !ARCADYAN_SUBTITLE_CREATER
