#pragma once
#include "Component.h"
#include "GeneralStucts.h"
namespace Crusade
{
	class Transform final : public Component
	{
	public:
		Transform() = default;

		void SetPosition(const Vector2f& position) { m_Position = position; }
		void SetPosition(const float x , const float y) { m_Position = Vector2f{x,y}; }
		Vector2f &GetPosition() { return m_Position; }

		void SetScale(const Vector2f& scale) { m_Scale = scale; }
		void SetScale(const float scaleX, const float scaleY) { m_Scale = Vector2f{ scaleX,scaleY }; }
		Vector2f& GetScale() { return m_Scale; }

		void SetRotation(const float rotation) { m_Rotation = rotation; }
		float& GetRotation() { return m_Rotation; }

		void Rotate(const float rotation) { m_Rotation += rotation; }
		void Translate(const Vector2f& translation) { m_Position += translation; }
		void Scale(const Vector2f& scale) { m_Scale.x *= scale.x; m_Scale.y *= scale.y; }

	private:
		Vector2f m_Position{};
		Vector2f m_Scale{1,1};
		float m_Rotation{0};
		Vector2f m_PreviousPos{};
		float m_PreviousRotation{};
		Vector2f m_PreviousScale{1,1};

		void Tick() override;
	};
}
