///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "SoundClass.h"

SoundClass::SoundClass()
{
    m_System = 0;
    m_Music = 0;
    m_Sound0 = 0;
    m_Sound1 = 0;
    m_Sound2 = 0;
}

SoundClass::SoundClass(const SoundClass& other)
{
}

SoundClass::~SoundClass()
{
}

bool SoundClass::Initialize(HWND hwnd)
{
    bool result;

    result = InitializeFMODSound(hwnd);
    if (!result)
    {
        return false;
    }

    // Set listener and group position
    m_System->set3DListenerAttributes(0, new FMOD_VECTOR{ 0.0f, 0.0f, 0.0f }, 0, new FMOD_VECTOR{ 0.0f, 0.0f, 1.0f }, new FMOD_VECTOR{ 0.0f, 1.0f, 0.0f });

    // Load music
    result = LoadSound((char*) "../RealEX/music/preBattle.mp3", FMOD_LOOP_NORMAL, &m_Music);
    if (!result)
    {
        MessageBox(hwnd, L"Error loading sound file.", L"Error", MB_OK);
        return false;
    }

    // Play music
    result = Play2DSound(m_Music, 0.2f);
    if (!result)
    {
        MessageBox(hwnd, L"Error playing sound file.", L"Error", MB_OK);
        return false;
    }

    // Load mouse click event sound
    result = LoadSound((char*)"../RealEX/fx/drum_2.ogg", FMOD_DEFAULT, &m_Click);
    if (!result)
    {
        MessageBox(hwnd, L"Error loading sound file.", L"Error", MB_OK);
        return false;
    }

    // Set mouse last click state to false.
    m_mouseClickState = false;

    // Load first sound
    result = LoadSound((char*)"../RealEX/fx/d_blacksmith2.ogg", FMOD_3D, &m_Sound0);
    if (!result)
    {
        MessageBox(hwnd, L"Error loading sound file.", L"Error", MB_OK);
        return false;
    }

    // Play first sound
    result = Play3DSound(m_Sound0, new FMOD_VECTOR{52.0f, 10.5f, -7.0f}, 1.0f);
    if (!result)
    {
        MessageBox(hwnd, L"Error playing sound file.", L"Error", MB_OK);
        return false;
    }

    // Load second sound
    result = LoadSound((char*)"../RealEX/fx/d_owl2.ogg", FMOD_3D, &m_Sound1);
    if (!result)
    {
        MessageBox(hwnd, L"Error loading sound file.", L"Error", MB_OK);
        return false;
    }

    // Play second sound
    result = Play3DSound(m_Sound1, new FMOD_VECTOR{ 48.0f, 11.0f, -7.5f}, 1.0f);
    if (!result)
    {
        MessageBox(hwnd, L"Error playing sound file.", L"Error", MB_OK);
        return false;
    }

    // Update the system so the sounds get placed properly
    m_System->update();

	return true;
}

bool SoundClass::Frame(float posX, float posY, float posZ, bool mouseClickState)
{
    bool result;
    m_System->set3DListenerAttributes(0, new FMOD_VECTOR{ posX, posY, posZ }, 0, new FMOD_VECTOR{ 0.0f, 0.0f, 1.0f }, new FMOD_VECTOR{ 0.0f, 1.0f, 0.0f });
    m_System->update();

    // If the click state is different from the last one, play the click sound
    if (mouseClickState != m_mouseClickState && mouseClickState)
    {
        // Play the click sound
        result = Play2DSound(m_Click, 1.0f);
        if (!result)
        {
            return false;
        }
    }

    // Update the mouse click state
    m_mouseClickState = mouseClickState;

    return true;
}

void SoundClass::Shutdown()
{
    //Paitone you dumbass idiot, used resources get shutdown first
    ShutdownSounds();

    //The system is shutdown the last dammit
    ShutdownFMODSound();

    return;
}

bool SoundClass::InitializeFMODSound(HWND hwnd)
{
    FMOD_RESULT result;

    result = FMOD::System_Create(&m_System); // Create the main system object.
    if (result != FMOD_OK)
    {
        MessageBox(hwnd, L"Could not create FMOD System object.", L"Error", MB_OK);
        return false;
    }

    result = m_System->init(512, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
    if (result != FMOD_OK)
    {
        MessageBox(hwnd, L"Could not initialize FMOD System object.", L"Error", MB_OK);
        return false;
    }

    return true;
}

void SoundClass::ShutdownFMODSound()
{
    if (m_System)
    {
        m_System->release();
        m_System = 0;
    }
}

bool SoundClass::LoadSound(char* path, FMOD_MODE mode, FMOD::Sound** sound)
{
    FMOD_RESULT result;

    // For FMOD_MODE see https://www.fmod.com/resources/documentation-api?version=2.02&page=core-api-common.html#fmod_mode
    result = m_System->createSound(path, mode, 0, sound);
    if (result != FMOD_OK)
    {
        return false;
    }

    return true;
}

void SoundClass::ShutdownSounds()
{
    if (m_Music)
    {
        m_Music->release();
        m_Music = 0;
    }
    
    if (m_Sound0)
    {
        m_Sound0->release();
        m_Sound0 = 0;
    }

    if (m_Sound1)
    {
        m_Sound1->release();
        m_Sound1 = 0;
    }

    if (m_Sound2)
    {
        m_Sound2->release();
        m_Sound2 = 0;
    }

    return;
}

bool SoundClass::Play2DSound(FMOD::Sound* sound, float vol)
{
    FMOD_RESULT result;
    FMOD::Channel* channel;

    result = m_System->playSound(sound, 0, false, &channel);
    if (result != FMOD_OK)
    {
        return false;
    }
    channel->setVolume(vol);

    return true;
}

bool SoundClass::Play3DSound(FMOD::Sound* sound, FMOD_VECTOR* pos, float vol)
{
    FMOD_RESULT result;
    FMOD::Channel* channel;

    result = m_System->playSound(sound, 0, false, &channel);
    if (result != FMOD_OK)
    {
        return false;
    }

    channel->set3DAttributes(pos, new FMOD_VECTOR{ 0.0f, 0.0f, 0.0f });
    channel->setVolume(vol);

    return true;
}