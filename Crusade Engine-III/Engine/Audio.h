#pragma once
#include <string>
namespace Crusade
{
	class AudioService;
	class Audio final
	{
	public:
		Audio() = delete;
		~Audio() = delete;

		Audio(const Audio& other) = delete;
		Audio(Audio&& other) = delete;
		Audio& operator=(const Audio& other) = delete;
		Audio& operator=(Audio&& other) = delete;

		static  void play(const std::string& path, float volume = 1, int loops = 0);
		static  void StopAll();
		static void SetOn(bool on);
	private:
		static AudioService* m_Service;
		static void InitService();
	};
}
