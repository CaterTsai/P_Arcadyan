#ifndef ARCADYAN_GREEN_BUILDING_CTRL
#define ARCADYAN_GREEN_BUILDING_CTRL

#include "protocol.h"
#include "ofGstVideoPlayer.h"

class GreenBuildingCtrl
{
public:
	void setupGreenBuildingCtrl();
	void updateGreenBuildingCtrl(float fDelta, ofPoint CtrlPos);
	void drawGreenBuildingCtrl();

	void startGreenBuidling();
	void stopGreenBuidling();

private:
	void startRotate(bool bIsLeft);
	void stopRotate();
	
private:
	bool			_bIsStart;
	bool			_bIsRotate;
	
	ofVideoPlayer	_GreenBuilding;
	int				_iTotalFrame;
	ofVideoPlayer	_GreenBuildingLight;

	ofImage			_ArrowLeft, _ArrowRight;
};

#endif // !ARCADYAN_GREEN_BUILDING
