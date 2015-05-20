#include "GestureManager.h"

void GestureManager::SetupGestureManager()
{
	_fTimer = ofGetElapsedTimef();
	_bStartCheck = false;
	_GestureName = "";
}

//--------------------------------------------------------------
void GestureManager::UpdateGestureManager(const stSCREEN_SKELETON& stSkeleton)
{
	if(!_bStartCheck)
	{
		return;
	}
	
	float fDelta_ = ofGetElapsedTimef() - _fTimer;
	_fTimer += fDelta_;

	auto pIter_ = _GestureList.begin();
	for(;pIter_ != _GestureList.end();++pIter_)
	{
		if(pIter_->getGestureName() == _GestureName)
		{
			pIter_->UpdateGesture(fDelta_, stSkeleton);
		}
	}
}

//--------------------------------------------------------------
void GestureManager::AddGesture(string stName, GestureSegmentList& SementList)
{
	Gesture NewGesture_(stName, SementList);
	_GestureList.push_back(NewGesture_);	
}

//--------------------------------------------------------------
void GestureManager::startCheck(const string& Name)
{
	_bStartCheck = false;
	_GestureName = "";

	bool bHaveThisGesture_ = false;
	for(auto& Iter_ : _GestureList)
	{
		if(Iter_.getGestureName() == Name)
		{
			bHaveThisGesture_ = true;
			break;
		}
	}

	if(bHaveThisGesture_)
	{
		_bStartCheck = true;
		_GestureName = Name;
	}
}

//--------------------------------------------------------------
void GestureManager::stopCheck()
{
	_bStartCheck = false;
	_GestureName = "";

	for(auto& Iter_ : _GestureList)
	{
		Iter_.ResetGesture();
	}
}