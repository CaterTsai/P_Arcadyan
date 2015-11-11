#include "ofMain.h"
#include "Arcadyan.h"

//========================================================================
int main( ){

#ifdef MEM_CHECK
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
#endif MEM_CHECK

	//ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT,OF_GAME_MODE);			// <-------- setup the GL context
	ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new Arcadyan());
	
}
