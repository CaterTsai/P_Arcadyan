#ifndef TEXT_SLICER_PARAMETER
#define TEXT_SLICER_PARAMETER

#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxTrueTypeFontUC.h"

static const int cTEXT_WIDTH = 1000;
static const int cTEXT_HEIGHT = 300;
static const int cKERNEL_SIZE = 81;
static const float cGAUSSIAN_SIGMA = 5.0;
static const int cBASE_ALPHA = 30;

#define POW_SIGMA (cGAUSSIAN_SIGMA*cGAUSSIAN_SIGMA)

typedef enum eTEXT_ROTATE_STATE
{
	eTEXT_ROTATE_TO_FORWARD		=	0,
	eTEXT_FORWARD,
	eTEXT_ROTATE_TO_BACKWARD,
	eTEXT_BACKWARD,	
};

#endif // !TEXT_SLICER_PARAMETER
