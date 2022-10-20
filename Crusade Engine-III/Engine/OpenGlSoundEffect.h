#pragma once
#include "SoundEffect.h"
struct Mix_Chunk;
namespace Crusade
{
	class OpenGlSoundEffect final : public SoundEffect
	{
	public:
		explicit OpenGlSoundEffect(const std::string& path);
		~OpenGlSoundEffect();
		OpenGlSoundEffect(const OpenGlSoundEffect& other) = delete;
		OpenGlSoundEffect& operator=(const OpenGlSoundEffect& rhs) = delete;
		OpenGlSoundEffect(OpenGlSoundEffect&& other) = delete;
		OpenGlSoundEffect& operator=(OpenGlSoundEffect&& rhs) = delete;

		bool Play(int loops) override;
		void SetVolume(int value) override;
		int GetVolume() const override;
		void StopAll() override;
		void PauseAll() override;
		void ResumeAll() override;
		bool IsValid() override;
		float GetDuration() override;
		bool IsPlaying() override;
	private:
		int m_CurrentChannel = -1;
		Mix_Chunk* m_pMixChunk;
	};
}