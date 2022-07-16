///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "fmod_vc.lib")

//////////////
// INCLUDES //
//////////////
#include <fmod.hpp>
#include <windows.h>
#include <WinUser.h>

///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
///////////////////////////////////////////////////////////////////////////////
class SoundClass
{
public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();
	bool Initialize(HWND);
	void Shutdown();
	bool Frame(float, float, float, bool);

private:
	bool InitializeFMODSound(HWND);
	void ShutdownFMODSound();

	bool LoadSound(char*, FMOD_MODE, FMOD::Sound**);
	void ShutdownSounds();

	bool Play2DSound(FMOD::Sound*, float);
	bool Play3DSound(FMOD::Sound*, FMOD_VECTOR*, float);

private:
	FMOD::System* m_System;
	FMOD::Sound *m_Music, *m_Sound0, *m_Sound1, *m_Sound2, *m_Click;
	bool m_mouseClickState;
};

#endif