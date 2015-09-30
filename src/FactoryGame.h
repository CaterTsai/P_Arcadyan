#ifndef _ARCADYAN_FACTORY_GAME_
#define _ARCADYAN_FACTORY_GAME_

#include "ofxHapPlayer.h"
#include "ofxAnimatableFloat.h"
#include "protocol.h"

enum eFACTORY_STATE
{	
	eFACTORY_FINISH =	0,
	eFACTORY_CAP,
	eFACTORY_CHIP,
	eFACTORY_ANTENNA,
	eFACTORY_PORT,
	
};

enum eFACTORY_ITEM_STATE
{
	eITEM_OUT = 0,
	eITEM_ENTER,
	eITEM_IN,
	eITEM_EXIT
};

#pragma region struct stItemPos
typedef struct _stItemPos
{
	_stItemPos(ofRectangle rect)
		:Rect(rect)
		,Index(-1)
		,bIsSelect(false)
	{
		Pos = ofVec2f(rect.x, rect.y);
		AnimX.setDuration(1.0);
		AnimX.setRepeatType(AnimRepeat::PLAY_ONCE);
	}

	inline void update(float fDelta)
	{
		AnimX.update(fDelta);
		Rect.x = Pos.x + AnimX.getCurrentValue() * cFACTORY_ITEMS_MOVE_DIST;
	}

	inline void Enter()
	{
		AnimX.setCurve(AnimCurve::BOUNCY);
		AnimX.animateFromTo(0, 1);
	}

	inline void Exit()
	{
		AnimX.setCurve(AnimCurve::EASE_OUT);
		AnimX.animateFromTo(1, 0);
	}

	inline void setIndex(int idx)
	{
		Index = idx;
	}

	inline ofRectangle getDrawRect()
	{
		return Rect;
		//return ofVec2f(Pos.x + cFACTORY_ITEMS_MOVE_DIST * AnimX.getCurrentValue(), Pos.y);
	}

	inline bool checkRect(ofPoint CtrlPos)
	{
		return Rect.inside(CtrlPos);
	}

	inline int select()
	{
		bIsSelect = true;
		return Index;
	}

	inline void cancel()
	{
		bIsSelect = false;
	}

	bool	bIsSelect;
	int		Index;
	ofVec2f	Pos;
	ofRectangle	Rect;
	ofxAnimatableFloat	AnimX;
}stItemPos;
#pragma endregion

class FactoryGame
{
public:
	FactoryGame()
		:_bStart(false)
		,_eState(eFACTORY_FINISH)
		,_eItemState(eITEM_OUT)
	{}
	void setup();
	void update(float fDelta, ofPoint& CtrlPos);
	void draw();

	void start();
	void stop();

private:
	bool					_bStart;
	
	ofImage			_ScorePlane;
	eFACTORY_STATE	_eState;
//-------------------------
//Arm Video 
//-------------------------
private:
	void initialArmVideo();
	void updateArmVideo();
	void drawArmVideo();
		
	void startArmLoop();

public:
	void enterArm();

private:
	bool						_bStartLoop;
	int							_iLoopPoint;
	ofVideoPlayer		_ArmVideo;
//-------------------------
//Player Video
//-------------------------
private:
	void initialPlayerVideo();
	void updatePlayerVideo();
	void drawPlayerVideo();

	void startPlayerVideo();
public:
	void nextStep();
private:
	bool					_bIsFinish;
	int						_PlayerIndex;
	ofVideoPlayer	_PlayerVideo;
	pair<int, int>	_PlayerCheckPoint[4];

//-------------------------
//Items
//-------------------------
public:
	void enterItems();
	void exitItems();

private:
	void initialItems();
	void updateItems(float fDelta);
	void drawItems();

	void selectItemCheck();
	void ItemPlugInCheck();

	void changeItems(eFACTORY_STATE eState);
private:
	eFACTORY_ITEM_STATE										_eItemState;
	vector<stItemPos>												_ItemPosList;
	map<eFACTORY_STATE, vector<ofImage>>	_ItemMap;
	
	bool																			_bIsSelectItem;
	int																				_iItemPosIndex;
	ofPoint																		_CtrlPos;
	ofRectangle																_PlugInTriggerRect;
//-------------------------
//Information board
//-------------------------
private:
	void initialInfoBoard();
	void updateInfoBoard(float fDelta);
	void drawInfoBoard();
	void resetInfoBoard();

public:
	void showInfo();
	void hideInfo();	
	
	void showConclusion();
	void hideConclusion();
	//void 
private:
	bool															_bShowConclusion;
	ofImage													_InfoBoard, _InfoBenefit, _InfoConclusion, _InfoConslusionMask;	

	bool															_bStartConclusion;
	float															_ConclusionTimer;

	map<eFACTORY_STATE, ofImage>	_InfoList;
	ofxAnimatableFloat								_AnimTextAlpha, _AnimConclusAlpha;

////////////////////////////
//EVENT
////////////////////////////
public:
	ofEvent<string>	_FactoryEvent;
};

#endif // !_ARCADYAN_FACTORY_GAME_