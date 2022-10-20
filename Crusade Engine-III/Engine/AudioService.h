#pragma once
#include <iostream>
#include "Service.h"
namespace Crusade
{
	class SoundEffect;
	class AudioService : public Service
	{
	public:
		AudioService() = default;
		virtual ~AudioService() = default;
		AudioService(const AudioService& other) = delete;
		AudioService(AudioService&& other) = delete;
		AudioService& operator=(const AudioService& other) = delete;
		AudioService& operator=(AudioService&& other) = delete;

		virtual void play(const std::string& path,float volume = 1,int loops = 0) = 0;
		virtual void StopAll() = 0;
		static bool m_On;
	protected:
		
	private:
		virtual void ProcessSoundRequests() = 0;
		
	};
}
