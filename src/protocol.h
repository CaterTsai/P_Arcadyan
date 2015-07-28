#ifndef _ARCADYAN_PROTOCOL_
#define _ARCADYAN_PROTOCOL_

#define TIMEOUT_MODE
#define MEM_CHECK

#include "ofMain.h"
#include "NameManager.h"

#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG


static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 1080;

static const int WEBCAM_WIDTH = 1920;
static const int WEBCAM_HEIGHT = 1080;

static const int TEXT_SLIDER_EMPTY_NUMBER = 7;

static const float cPHOTO_ANIMATION_DURATION = 1.0;

//Subtitle
static const ofColor SUBTITLE_COLOR = ofColor(255);
static const float SUBTITLE_FONT_SIZE = 60;

//Kinect
//DEFINE
#define uint8 unsigned char
#define uint16 unsigned short

//Const pamerater
const int NUMBER_OF_JOINT = 15;
const int KINECT_DEPTH_WIDTH = 640;
const int KINECT_DEPTH_HEIGHT = 480;

const float BASE_CHECK_TIME = 0.15;
const float SUCCESS_CHECK_TIMER = 0.08;
const int PAUSE_COUNTER_LIMT = 20;

const float cGREEN_BUILDING_EXIT_TIME = 1.5;

const float cKINECT_BODY_WIDTH = 205;
const float cKINECT_BODY_HEIGHT = 170;

//-------------------------------
const float cSHAKE_TIMEOUT	= 10;
const float cOPEN_TIMEOUT	= 5;
const float cGREEN_IN_TIMEOUT =  5;
const float cGREEN_OUT_TIMEOUT = 10;
const float cMILESTONE_IN_TIMEOUT = 5;
const float cPRODUCT_IN_TIMEOUT = 5;
const float cTAKE_PHOTO_TIMEOUT = 5;

#endif // !_ARCADYAN_PROTOCOL_
