#include "OpenGlSoundEffect.h"
#include <SDL_mixer.h>
#include <iostream>
using namespace Crusade;
OpenGlSoundEffect::OpenGlSoundEffect(const std::string& path)
	:SoundEffect(path),m_pMixChunk{ Mix_LoadWAV(path.c_str()) }
{
	if (m_pMixChunk == nullptr)
	{
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
	
}
OpenGlSoundEffect::~OpenGlSoundEffect()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}

bool OpenGlSoundEffect::IsPlaying()
{
	if (m_pMixChunk == nullptr)
		return false;

	return bool(Mix_Playing(m_CurrentChannel));
}

float OpenGlSoundEffect::GetDuration()
{
	if (m_pMixChunk == nullptr)
		return 0;
	
	return float(m_pMixChunk->alen);
	
	/*Uint32 points = 0;
	Uint32 frames = 0;
	int freq = 0;
	Uint16 fmt = 0;
	int chans = 0;

	if (!Mix_QuerySpec(&freq, &fmt, &chans))
	{
		return 0;
	}
	

	points = (m_pMixChunk->alen / ((fmt & 0xFF) / 8));
	frames = (points / chans);
	return  ((frames * 1000) / freq ) / 1000.f;*/
	
}

bool OpenGlSoundEffect::IsValid()
{
	return m_pMixChunk != nullptr;
}

bool OpenGlSoundEffect::Play(int loops)
{
	if (m_pMixChunk != nullptr)
	{
		int channel{ Mix_PlayChannel(-1, m_pMixChunk, loops) };
		m_CurrentChannel = channel;
		return channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void OpenGlSoundEffect::SetVolume(int value)
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk, value);
	}
}

int OpenGlSoundEffect::GetVolume() const
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	else
	{
		return -1;
	}
}

void OpenGlSoundEffect::StopAll()
{
	Mix_HaltChannel(-1);
}

void OpenGlSoundEffect::PauseAll()
{
	Mix_Pause(-1);
}
void OpenGlSoundEffect::ResumeAll()
{
	Mix_Resume(-1);
}