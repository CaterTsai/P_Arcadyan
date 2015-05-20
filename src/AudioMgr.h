#ifndef ARCADYAN_AUDIO_MGR
#define ARCADYAN_AUDIO_MGR

#include "ofMain.h"

class AudioMgr
{
public:
	void update();

	void addAduio(string strName, string strFilepath, bool bIsLoop = false, bool bIsMultiPlay = true, float fVol = 1.0);
	void addBGM(string strName, string strFilepath);
	
	void playAudio(string strName);
	void stopAllAudio();
	
	void playBGM(string strName);

private:
	AudioMgr()
		:_strNowBGM("")
		,_strNextBGM("")
		,_bIsPlayBGM(false)
		,_bStartFadeout(false)
	{};

	AudioMgr(AudioMgr const&);
	void operator=(AudioMgr const&);

private:
	bool	_bIsPlayBGM;
	bool	_bStartFadeout;
	string	_strNextBGM, _strNowBGM;
	map<string, ofSoundPlayer>	_AudioMap;

//-------------------
//Singleton
//-------------------
public:
	static AudioMgr* GetInstance();
	static void Destroy();

private:
	static AudioMgr *pInstance;
};

#endif // !AIRWAVES_PROJECTOR_AUDIO_MGR
