#pragma once
#include <string>
#include "Delay.h"
namespace Crusade
{
	class TextureRenderer;
	class Animation final
	{
	public:
		Animation(const std::string& filepath, const int& colloms, const float& framesPerSec, const bool& isLoop);//HORIZONTAL ANIMATION
		Animation(const std::string& filepath, const int& colloms, const int& rows, const float& framesPerSec, const bool& isLoop);//VERTICAL ANIMATION
		~Animation()= default;

		Animation(const Animation& other) = delete;
		Animation(Animation&& other) = delete;
		Animation& operator=(const Animation& other) = delete;
		Animation& operator=(Animation&& other) = delete;
		
		void Start(TextureRenderer* renderer);
		void Update(TextureRenderer* renderer, const float& deltaTime);
		void SetAsMultiSprite(const int& currentRow, const int& maxColloms);

		int GetTag()const { return m_Tag; }
		bool GetIsFinished() const { return m_IsFinished; }
		std::string GetFilePath()const { return m_FilePath; }

	private:
		std::string m_FilePath{};
		float m_FramesPerSecond = 10;
		int m_CurrentCollom = 0;
		int m_CurrentRow = 0;
		int m_Rows = 1;
		int m_Colloms = 1;
		int m_Width = 0;
		int m_height = 0;
		int m_MaxColloms = 1;

		bool m_IsLoop = true;
		bool m_IsFinished = false;
		bool m_IsVertical = false;

		static int m_NextTag;
		int m_Tag = 0;
		Delay m_Delay{ 0 };
	};
}
