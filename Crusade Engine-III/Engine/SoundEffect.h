#pragma once
#include <string>

namespace Crusade
{
	class SoundEffect
	{
	public:
		explicit SoundEffect(const std::string& path);
		virtual ~SoundEffect() = default;
		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect& operator=(const SoundEffect& rhs) = delete;
		SoundEffect(SoundEffect&& other) = delete;
		SoundEffect& operator=(SoundEffect&& rhs) = delete;

		virtual bool Play(int loops = 0) = 0;
		virtual void SetVolume(int value) = 0;
		virtual int GetVolume() const = 0;
		virtual void StopAll() = 0;
		virtual void PauseAll() = 0;
		virtual void ResumeAll() = 0;
		virtual bool IsValid() = 0;
		virtual float GetDuration() = 0;
		virtual bool IsPlaying() = 0;
		std::string GetPath()const { return m_Path; }
	private:
		std::string m_Path;
	};
}