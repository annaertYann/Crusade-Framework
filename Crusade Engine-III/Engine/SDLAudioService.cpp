#include "SDLAudioService.h"
#include <SDL_mixer.h>
#include "Resource.h"
#include "OpenGlSoundEffect.h"
#include "Debug.h"

using namespace Crusade;

void SDLAudioService::play(const std::string& path, float volume, int loops)
{
	if (!m_On)
		return;

	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_SoundRequests.push_back(SoundRequirements(path, volume,loops));
	m_WorkAvailable.notify_one();
}

void SDLAudioService::ProcessSoundRequests()
{
	do
	{
		std::unique_lock<std::mutex>mLock{ m_Mutex };

		if (m_Stop)
		{
			Mix_HaltChannel(-1);
			m_Stop = false;
		}

		if (!m_SoundRequests.empty())
		{
			SoundRequirements var = m_SoundRequests.back();
			m_SoundRequests.pop_back();
			auto* SoundEffect = Resource::LoadSoundEffect(var.ID);
			if(SoundEffect != nullptr)
			{
				SoundEffect->SetVolume(int(var.volume));
				SoundEffect->Play(var.Loops);
			}
		}
		
		if (m_SoundRequests.empty())
		{
			m_WorkAvailable.wait(mLock);
		}
		
	} while (!m_SoundRequests.empty()||m_Stop);
}
SDLAudioService::SDLAudioService()
{
	m_Thread = std::thread(&SDLAudioService::ProcessSoundRequests, this);

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0)
	{
		Debug::Print("Error Creating openglRenderer");
		return;
	}

}

SDLAudioService::~SDLAudioService()
{
	m_WorkAvailable.notify_one();
	m_Thread.join();
}


void SDLAudioService::StopAll()
{
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_WorkAvailable.notify_one();
	m_Stop = true;
}
