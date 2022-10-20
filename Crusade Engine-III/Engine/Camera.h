#pragma once
#include "Component.h"
#include "GeneralStucts.h"
#include "Delay.h"

namespace Crusade
{
	class Transform;
	class Camera final : public Component
	{
	public:
		static Camera* GetMain() { return Main; }
		static void SetAsMain(Camera* camera) { Main = camera; }
		Vector2f ScreenToWorld(const Vector2f& screenPosition)const;
		Rectf GetCameraWindow()const;
		void ScreenShake(float duration, float strenght, float frequency);

	private:
		static Camera* Main;
		int m_CameraCounter = 0;
		static int NextCameraCounter;
		Transform* m_Transform = nullptr;
		Rectf m_CameraWindow{};
		Delay m_ShakeDuration{ 0 };
		float m_ShakeStrenght = 0;
		Delay m_ShakeFrequency{ 0 };
		Vector2f m_ShakeOffSet{};

		void Awake() override;
		void LateTick() override;
		void OnDestroy() override;
		Rectf CreateCameraWindow() const;
		Vector2f CalculateShake();
	};
}
