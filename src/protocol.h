#ifndef _ARCADYAN_PROTOCOL_
#define _ARCADYAN_PROTOCOL_

//#define TIMEOUT_MODE
//#define MEM_CHECK

#include "ofMain.h"
#include "NameManager.h"

#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm>
#include <random>
#include <array>
#include <chrono>

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
static const float cKINECT_DETECTION_RANGE = 0.4; //x distance of kinect (m)
//Const pamerater
static const int NUMBER_OF_JOINT = 15;
static const int KINECT_DEPTH_WIDTH = 640;
static const int KINECT_DEPTH_HEIGHT = 480;

static const float BASE_CHECK_TIME = 0.15;
static const float SUCCESS_CHECK_TIMER = 0.08;
static const int PAUSE_COUNTER_LIMT = 20;

static const float cGREEN_BUILDING_EXIT_TIME = 1.5;

static const float cKINECT_BODY_WIDTH = 205;
static const float cKINECT_BODY_HEIGHT = 170;

static const float cTAKEPICTURE_TIME = 2.0f;

//-------------------------------
static const float cSHAKE_TIMEOUT	= 10;
static const float cOPEN_TIMEOUT	= 5;
static const float cGREEN_IN_TIMEOUT =  5;
static const float cGREEN_OUT_TIMEOUT = 10;
static const float cMILESTONE_IN_TIMEOUT = 5;
static const float cPRODUCT_IN_TIMEOUT = 5;
static const float cFACOTYR_NEXT_TIMEOUT = 3;
static const float cTAKE_PHOTO_TIMEOUT = 5;

static const ofRectangle cPHOTO_FRAME_KINECT_RECT = ofRectangle(38, 588, 1030, 580);
static const ofVec2f cPHOTO_DATE_POS = ofVec2f(553, 135);
static const int cPHOTO_DATE_FONT_SIZE = 40;

static const int cFACTORY_ITEMS_NUM = 4;
static const float cFACTORY_ITEMS_MOVE_DIST = 588;

#endif // !_ARCADYAN_PROTOCOL_
