#include "Animation.h"
#include "TextureRenderer.h"
#include "Texture.h"
using namespace Crusade;

int Animation::m_NextTag = 0;

Animation::Animation(const std::string& filepath, const int& colloms, const float& framesPerSec, const bool& isLoop)
{
	m_FilePath = filepath;
	m_Colloms = colloms;
	m_MaxColloms = m_Colloms;
	m_FramesPerSecond = framesPerSec;
	m_IsLoop = isLoop;
	m_Delay.SetDelayTime(1 / framesPerSec);
	m_Tag = m_NextTag;
	m_NextTag++;
	m_IsFinished = false;
}

Animation::Animation(const std::string& filepath, const int& colloms, const int& rows, const float& framesPerSec, const bool& isLoop)
{
	m_FilePath = filepath;
	m_Rows = rows;
	m_Colloms = colloms;
	m_MaxColloms = m_Colloms;
	m_FramesPerSecond = framesPerSec;
	m_IsLoop = isLoop;
	m_Delay.SetDelayTime(1 / framesPerSec);
	m_IsVertical = true;
	m_Tag = m_NextTag;
	m_NextTag++;
	m_IsFinished = false;
}

void Animation::Start(TextureRenderer* renderer)
{
	renderer->SetTexture(m_FilePath);
	if (!renderer->GetCurrentTexture())
		return;
	m_Width = int(renderer->GetCurrentTexture()->GetWidth());
	m_height = int(renderer->GetCurrentTexture()->GetHeight());
	m_CurrentCollom = 0;
	renderer->SetSourceRect(Rectf(
		float(m_CurrentCollom) * float(float(m_Width) / m_Colloms),
		float(m_CurrentRow) * (float(m_height) / m_Rows),
		float(m_Width) / float(m_Colloms),
		float(m_height) / float(m_Rows)));
	m_Delay.Start();
	m_IsFinished = false;
	if (m_IsVertical)
	{
		m_CurrentRow = 0;
	}
}

void Animation::Update(TextureRenderer* renderer, const float& deltaTime)
{
	if (m_Delay.Update(deltaTime))
	{
		m_Delay.Start();
		m_IsFinished = false;
		if (m_CurrentCollom <= m_MaxColloms - 1)
		{
			m_CurrentCollom++;
		}
		if (m_CurrentCollom >= m_MaxColloms)
		{
			if (m_IsVertical)
			{
				m_CurrentRow++;
				m_CurrentCollom = 0;
				if (m_CurrentRow >= m_Rows)
				{
					if (m_IsLoop)
					{
						m_CurrentRow = 0;
						m_IsFinished = true;
					}
					else
					{
						m_CurrentCollom = m_MaxColloms - 1;
						m_CurrentRow = m_Rows - 1;
						m_IsFinished = true;
					}
				}
			}
			else
			{
				if (m_IsLoop)
				{
					m_CurrentCollom = 0;
					m_IsFinished = true;
				}
				else
				{
					m_CurrentCollom = m_MaxColloms - 1;
					m_IsFinished = true;
				}
			}
		}
		renderer->SetSourceRect(Rectf(
			float(m_CurrentCollom) * float(float(m_Width) / m_Colloms),
			float(m_CurrentRow) * (float(m_height) / m_Rows),
			float(m_Width) / float(m_Colloms),
			float(m_height) / float(m_Rows)));
	}
}

void Animation::SetAsMultiSprite(const int& currentRow, const int& maxColloms)
{
	m_CurrentRow = currentRow;
	m_MaxColloms = maxColloms;
	m_IsVertical = false;
}