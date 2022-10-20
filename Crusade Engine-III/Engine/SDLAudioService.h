#pragma once
#include "AudioService.h"
#include <thread>
#include <mutex>
#include <vector>
#include "SoundEffect.h"
namespace Crusade
{

	class SDLAudioService :public AudioService
	{
	public:
		struct SoundRequirements
		{
			SoundRequirements(std::string iD, float vol, int loops) { ID = iD; volume = vol; Loops = loops; }
			std::string ID;
			float volume;
			int Loops;
		};
		SDLAudioService();
		~SDLAudioService() override;
		void play(const std::string& path, float volume, int loops) override;
		void ProcessSoundRequests() override;
		void StopAll() override;
	private:
		std::condition_variable m_WorkAvailable;
		std::mutex m_Mutex;
		std::thread m_Thread;
		std::vector<SoundRequirements>m_SoundRequests;
		bool m_Stop = false;
	};
}
