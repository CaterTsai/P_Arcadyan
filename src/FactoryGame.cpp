#include "FactoryGame.h"

#pragma region Base method
//--------------------------------------------------------------
void FactoryGame::setup()
{
	initialItems();
	initialPlayerVideo();
	initialArmVideo();
	initialInfoBoard();
}

//--------------------------------------------------------------
void FactoryGame::update(float fDelta, ofPoint& CtrlPos)
{
	updateArmVideo();

	if(!_bStart)
	{
		return;
	}
	_CtrlPos = CtrlPos;
	updateItems(fDelta);
	updatePlayerVideo();
	updateInfoBoard(fDelta);
}

//--------------------------------------------------------------
void FactoryGame::draw()
{
	drawArmVideo();

	if(!_bStart)
	{
		return;
	}	
	
	drawPlayerVideo();
	drawItems();
	drawInfoBoard();
}

//--------------------------------------------------------------
void FactoryGame::start()
{
	if(_bStart)
	{
		return;
	}
	_bStart = true;
	_eState = eFACTORY_CAP;

	startPlayerVideo();
	startArmLoop();

	changeItems(_eState);
	enterItems();
	_eItemState = eITEM_ENTER;

	resetInfoBoard();

	showInfo();	
}

//--------------------------------------------------------------
void FactoryGame::stop()
{
	if(!_bStart)
	{
		return;
	}

	_bStart = false;
}
#pragma endregion

#pragma region Arm Video
//--------------------------------------------------------------
void FactoryGame::initialArmVideo()
{
	//Video
	_ArmVideo.setPlayer(ofPtr<ofxHapPlayer>(new ofxHapPlayer));
	if(!_ArmVideo.loadMovie("videos/Factory_AutomaticArm.mov"))
	{
		ofLog(OF_LOG_ERROR, "[FactoryGame] Loading arm video failed");
	}
	_ArmVideo.setLoopState(ofLoopType::OF_LOOP_NONE);

	_iLoopPoint = 132;
}

//--------------------------------------------------------------
void FactoryGame::updateArmVideo()
{
	if(!_ArmVideo.isLoaded())
	{
		return;
	}

	_ArmVideo.update();
	int iFrame_ = _ArmVideo.getCurrentFrame();
	if(_bStartLoop)
	{
		if(abs(iFrame_ - _ArmVideo.getTotalNumFrames()) < 2)
		{
			_ArmVideo.setFrame(_iLoopPoint);
		}
	}
	else
	{
		if(abs(iFrame_ - _iLoopPoint) < 2)
		{
			_ArmVideo.setPaused(true);
		}
	}
}

//--------------------------------------------------------------
void FactoryGame::drawArmVideo()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255);
	{
		_ArmVideo.draw(0, 0);
	}
	ofPopStyle();	
}

//--------------------------------------------------------------
void FactoryGame::startArmLoop()
{
	if(_ArmVideo.isLoaded())
	{
		_bStartLoop = true;
		_ArmVideo.play();
	}
}

//--------------------------------------------------------------
void FactoryGame::enterArm()
{
	if(_ArmVideo.isLoaded())
	{
		_bStartLoop = false;
		_ArmVideo.play();
	}
}
#pragma endregion

#pragma region Player Video
//--------------------------------------------------------------
void FactoryGame::initialPlayerVideo()
{
	//Player Video
	_PlayerVideo.setPlayer(ofPtr<ofxHapPlayer>(new ofxHapPlayer));
	if(!_PlayerVideo.loadMovie("videos/Factory_Player.mov"))
	{
		ofLog(OF_LOG_ERROR, "[FactoryGame] Loading player video failed");
	}
	_PlayerVideo.setLoopState(ofLoopType::OF_LOOP_NONE);

	_PlayerCheckPoint[0] = make_pair(9, 66);
	_PlayerCheckPoint[1] = make_pair(93, 150);
	_PlayerCheckPoint[2] = make_pair(177, 234);
	_PlayerCheckPoint[3] = make_pair(261, 318);
}

//--------------------------------------------------------------
void FactoryGame::updatePlayerVideo()
{
	if(!_PlayerVideo.isLoaded() || !_PlayerVideo.isPlaying())
	{
		return;
	}

	_PlayerVideo.update();
	int iFrame_ = _PlayerVideo.getCurrentFrame();
	if(_bIsFinish && _PlayerVideo.getIsMovieDone())
	{
		//Finish
		showConclusion();
		_ArmVideo.setPaused(true);

		string strMsg_ = NAME_MANAGER::F_CloseCtrl;
		ofNotifyEvent(_FactoryEvent, strMsg_);
	}
	else
	{
		if(iFrame_ > _PlayerCheckPoint[_PlayerIndex].second)
		{
			_PlayerVideo.setFrame(_PlayerCheckPoint[_PlayerIndex].first);
		}
	}
}

//--------------------------------------------------------------
void FactoryGame::drawPlayerVideo()
{
	if(!_PlayerVideo.isLoaded() || !_PlayerVideo.isPlaying())
	{
		return;
	}
	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255);
	{
		_PlayerVideo.draw(0, 0);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void FactoryGame::startPlayerVideo()
{
	if(!_PlayerVideo.isLoaded())
	{
		return;
	}
	_bIsFinish = false;
	_PlayerIndex = 0;
	_PlayerVideo.play();
}

//--------------------------------------------------------------
void FactoryGame::nextStep()
{
	_PlayerIndex++;
	if(_PlayerIndex == 4)
	{
		_bIsFinish = true;
	}
}
#pragma endregion

#pragma region Items
//--------------------------------------------------------------
void FactoryGame::initialItems()
{
	vector<ofImage> cap_, chip_, antenna_, port_;
	cap_.resize(4);
	chip_.resize(4);
	antenna_.resize(4);
	port_.resize(4);

	_bIsSelectItem = false;
	_iItemPosIndex = -1;
	_PlugInTriggerRect = ofRectangle(486, 711, 367, 182);

	char Dir_[100];
	char cIndex_ = 'A';	
	for(int idx_ = 0; idx_ < cFACTORY_ITEMS_NUM; idx_++)
	{	
		sprintf_s(Dir_, 100, "images/FactoryItems/cap_%c.png", cIndex_ + idx_);
		cap_[idx_].loadImage(string(Dir_));

		sprintf_s(Dir_, 100, "images/FactoryItems/chip_%c.png", cIndex_ + idx_);
		chip_[idx_].loadImage(string(Dir_));

		sprintf_s(Dir_, 100, "images/FactoryItems/antenna_%c.png", cIndex_ + idx_);
		antenna_[idx_].loadImage(string(Dir_));

		sprintf_s(Dir_, 100, "images/FactoryItems/rj454port_%c.png", cIndex_ + idx_);
		port_[idx_].loadImage(string(Dir_));
	}

	_ItemMap.insert(make_pair(eFACTORY_CAP, cap_));
	_ItemMap.insert(make_pair(eFACTORY_CHIP, chip_));
	_ItemMap.insert(make_pair(eFACTORY_ANTENNA, antenna_));
	_ItemMap.insert(make_pair(eFACTORY_PORT, port_));

	_ItemPosList.push_back(stItemPos(ofRectangle(-588, 363, 147, 130)));
	_ItemPosList.push_back(stItemPos(ofRectangle(-441, 363, 147, 130)));
	_ItemPosList.push_back(stItemPos(ofRectangle(-294, 363, 147, 130)));
	_ItemPosList.push_back(stItemPos(ofRectangle(-147, 363, 147, 130)));
}

//--------------------------------------------------------------
void FactoryGame::updateItems(float fDelta)
{
	if(_eState == eFACTORY_FINISH)
	{
		return;
	}
	
	//Update animate
	bool bAllFinish_ = true;
	for(auto& Iter_ : _ItemPosList)
	{
		Iter_.update(fDelta);
		bAllFinish_ &= (Iter_.AnimX.hasFinishedAnimating() && Iter_.AnimX.getPercentDone() == 1.0);
	}

	switch(_eItemState)
	{
	case eITEM_OUT:
		{
			if(_bStart)
			{
				if( _eState == eFACTORY_PORT)
				{
					_eState = eFACTORY_FINISH;
				}
				else
				{
					_eState = (eFACTORY_STATE)(_eState + 1);
					changeItems(_eState);
					showInfo();
					enterItems();
					_eItemState = eITEM_ENTER;
				}
			}
		}
		break;
	case eITEM_ENTER:
		{
			if(bAllFinish_)
			{
				_eItemState = eITEM_IN;
			}
		}
		break;
	case eITEM_IN:
		{
			selectItemCheck();
			ItemPlugInCheck();
		}
		break;
	case eITEM_EXIT:
		{
			if(bAllFinish_)
			{
				_eItemState = eITEM_OUT;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void FactoryGame::drawItems()
{	
	if(_eItemState == eFACTORY_FINISH || _eItemState == eITEM_OUT)
	{
		return;
	}

	ofPushStyle();
	ofSetColor(255);
	{
		for(auto& iter_ : _ItemPosList)
		{
			if(!iter_.bIsSelect)
			{
				_ItemMap[_eState][iter_.Index].draw(iter_.getDrawRect());
			}
		}
	}

	if(_bIsSelectItem)
	{
		_ItemMap[_eState][_ItemPosList[_iItemPosIndex].Index].draw(_CtrlPos);
	}

	ofPopStyle();
}

//--------------------------------------------------------------
void FactoryGame::enterItems()
{
	if(!_bStart || _eItemState != eITEM_OUT)
	{
		return;
	}

	for(auto& Iter_ : _ItemPosList)
	{
		Iter_.Enter();
	}
	_eItemState = eITEM_ENTER;
}

//--------------------------------------------------------------
void FactoryGame::exitItems()
{
	if(!_bStart || _eItemState != eITEM_IN)
	{
		return;
	}

	for(auto& Iter_ : _ItemPosList)
	{
		Iter_.Exit();
	}
	_eItemState = eITEM_EXIT;
}

//--------------------------------------------------------------
void FactoryGame::selectItemCheck()
{
	int iSItemIndex_ = -1;
	bool bIsSelect_ = false;
	for(iSItemIndex_ = 0; iSItemIndex_ < _ItemPosList.size(); iSItemIndex_++)
	{
		if(_ItemPosList[iSItemIndex_].checkRect(_CtrlPos))
		{
			bIsSelect_ = true;
			break;
		}
	}

	if(!bIsSelect_ || iSItemIndex_ >= 4)
	{
		return;
	}

	if(_bIsSelectItem && iSItemIndex_ != _iItemPosIndex)
	{
		_ItemPosList[_iItemPosIndex].cancel();
		_iItemPosIndex = iSItemIndex_;
		_ItemPosList[_iItemPosIndex].select();
	}
	else if(!_bIsSelectItem)
	{
		_bIsSelectItem = true;
		_iItemPosIndex = iSItemIndex_;
		_ItemPosList[_iItemPosIndex].select();
	}
}

//--------------------------------------------------------------
void FactoryGame::ItemPlugInCheck()
{
	if(!_bIsSelectItem)
	{
		return;
	}

	if(_PlugInTriggerRect.inside(_CtrlPos))
	{
		if(_ItemPosList[_iItemPosIndex].Index == 0)
		{
			_bIsSelectItem = false;
			_iItemPosIndex = -1;
			nextStep();
			exitItems();
			hideInfo();
		}
		else
		{
			_ItemPosList[_iItemPosIndex].cancel();
			_bIsSelectItem = false;
			_iItemPosIndex = -1;
		}
	}
}

//--------------------------------------------------------------
void FactoryGame::changeItems(eFACTORY_STATE eState)
{
	if(_eState == eFACTORY_FINISH || _eItemState != eITEM_OUT)
	{
		return;
	}

	unsigned seed_ = std::chrono::system_clock::now().time_since_epoch().count();
	std::array<int, cFACTORY_ITEMS_NUM>  randIdx_ = {0, 1, 2, 3};
	shuffle(randIdx_.begin(), randIdx_.end(), default_random_engine(seed_));

	for(int idx_ = 0; idx_ < cFACTORY_ITEMS_NUM; ++idx_)
	{
		_ItemPosList[idx_].setIndex(randIdx_[idx_]);
		_ItemPosList[idx_].cancel();
	}
}
#pragma endregion

#pragma region Information board
//--------------------------------------------------------------
void FactoryGame::initialInfoBoard()
{
	_bShowConclusion = false;
	_InfoBoard.loadImage("images/factoryBoard.png");
	_InfoBenefit.loadImage("images/factoryBenefit.png");
	_InfoConclusion.loadImage("images/factoryTextEnd.png");
	_InfoConslusionMask.loadImage("images/factoryTextMask.png");

	ofImage text1_, text2_, text3_, text4_;
	text1_.loadImage("images/factoryTextBenefit01.png");
	text2_.loadImage("images/factoryTextBenefit02.png");
	text3_.loadImage("images/factoryTextBenefit03.png");
	text4_.loadImage("images/factoryTextBenefit04.png");
	_InfoList.insert(make_pair(eFACTORY_CAP, text1_));
	_InfoList.insert(make_pair(eFACTORY_CHIP, text2_));
	_InfoList.insert(make_pair(eFACTORY_ANTENNA, text3_));
	_InfoList.insert(make_pair(eFACTORY_PORT, text4_));
	
	_AnimTextAlpha.reset(1.0);
	_AnimTextAlpha.setDuration(0.5);

	_AnimConclusAlpha.setDuration(0.5);
}

//--------------------------------------------------------------
void FactoryGame::updateInfoBoard(float fDelta)
{
	_AnimTextAlpha.update(fDelta);
	_AnimConclusAlpha.update(fDelta);

	if(_bStartConclusion)
	{
		_ConclusionTimer -= fDelta;
		if(_ConclusionTimer <= 0.0)
		{
			hideConclusion();
		}
	}

	if(_AnimConclusAlpha.hasFinishedAnimating() && _AnimConclusAlpha.getPercentDone() == 1.0 && _AnimConclusAlpha.getCurrentValue() == 0.0)
	{
		_bShowConclusion = false;
		string strMsg_ = NAME_MANAGER::F_GameFinish;
		ofNotifyEvent(_FactoryEvent, strMsg_);
	}
}

//--------------------------------------------------------------
void FactoryGame::drawInfoBoard()
{
	ofPushStyle();
	ofSetColor(255);
	ofEnableAlphaBlending();
	{
		_InfoBoard.draw(0, 0);

		if(_eState != eFACTORY_FINISH)
		{	
			_InfoBenefit.draw(0, 0);

			ofSetColor(255, _AnimTextAlpha.getCurrentValue() * 255);
			_InfoList[_eState].draw(0, 0);

			ofPushMatrix();
			ofTranslate(960, 345);
			{
				_ItemMap[_eState][0].draw(-97, -85, 193, 170);
			}
			ofPopMatrix();
		}

		if(_bShowConclusion)
		{
			ofSetColor(255, _AnimConclusAlpha.getCurrentValue() * 255);
			//ofSetColor(255);
			_InfoConslusionMask.draw(0, 0);
			_InfoConclusion.draw(0, 0);
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void FactoryGame::resetInfoBoard()
{
	_bShowConclusion = false;
}

//--------------------------------------------------------------
void FactoryGame::showInfo()
{
	_AnimTextAlpha.animateFromTo(0.0, 1.0);
}

//--------------------------------------------------------------
void FactoryGame::hideInfo()
{
	_AnimTextAlpha.animateFromTo(1.0, 0.0);
}

//--------------------------------------------------------------
void FactoryGame::showConclusion()
{
	if(!_bShowConclusion)
	{
		_AnimConclusAlpha.animateFromTo(0.0, 1.0);
		_bShowConclusion = true;
		_bStartConclusion = true;
		_ConclusionTimer = 4.5;
	}	
}

//--------------------------------------------------------------
void FactoryGame::hideConclusion()
{
	if(_bShowConclusion && _bStartConclusion)
	{
		_AnimConclusAlpha.animateFromTo(1.0, 0.0);
		_bStartConclusion = false;
	}	
}
#pragma endregion
