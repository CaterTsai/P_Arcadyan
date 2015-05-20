#ifndef ARCADYAN_TIMELINE_ELEMENT
#define ARCADYAN_TIMELINE_ELEMENT

#include "ofMain.h"
#include "ofxAnimatableFloat.h"

#pragma region Base Timeline Element
//Base Timeline Element
class BaseTimelineElement
{
public:
	BaseTimelineElement(float fTrigger, float fLenght)
		:_bIsStart(false)
		,_fTriggerT(fTrigger)
		,_fLengthT(fLenght)
	{}
	virtual void update(float fDelta){};
	virtual void draw(){};
	virtual void start(){};

public:
	inline float getTriggerT() const
	{
		return _fTriggerT;
	}

	inline float getLengthT() const
	{
		return _fLengthT;
	}
	

protected:
	bool	_bIsStart;
	float	_fTriggerT;
	float	_fLengthT;
};
#pragma endregion

#pragma region Image Timeline Element
//Audio Timeline Element
class ImageTimelineElement : public BaseTimelineElement
{
public:
	ImageTimelineElement(ofImage& Img, ofVec2f& Pos, float fTriggerT, float fLengthT);
	void update(float fDelta) override;
	void draw() override;
	void start() override;

private:
	ofImage		_Img;
	ofVec2f		_DrawCenterPos;
	ofxAnimatableFloat	_AnimAlpha;

	float		_fFadeTime, _Timer;
};
#pragma endregion

#pragma region Audio Timeline Element
//Audio Timeline Element
class AudioTimelineElement : public BaseTimelineElement
{
public:
	AudioTimelineElement(ofSoundPlayer audio, float fTriggerT);
	void start() override;

private:
	ofSoundPlayer _audio;
};
#pragma endregion

#endif // !ARCADYAN_TIMELINE_ELEMENT
