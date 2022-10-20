#pragma once
#include "Component.h"
#include "GeneralStucts.h"
#include <vector>
namespace Crusade
{
	class Collider final : public Component
	{
	public:
		struct HitBox
		{
		public:
			friend class Collider;
			HitBox();
			Rectf hitBox;
			GameObject* owner = nullptr;
			int GetID()const { return ID; }
		private:
			int ID = 0;
			static int NextID;
		};
		
		Collider() = default;
		~Collider()override;

		Collider(const Collider& other) = delete;
		Collider(Collider&& other) = delete;
		Collider& operator=(const Collider& other) = delete;
		Collider& operator=(Collider&& other) = delete;

		int GetLayer()const { return m_Layer; }
		void SetLayer(const int layer) { m_Layer = layer; }

		void SetSize(const float width, const float height) { m_Width = width; m_Height = height; }
		void SetSize(const Vector2f& size) { m_Width = size.x; m_Height = size.y; }
		void SetOffSet(const float x, const float y) { m_OffSet = Point2f{ x,y }; }
		Rectf GetHitBox()const { return m_HitBox->hitBox; }
		
		std::vector<HitBox> GetCurrentColliding()const { return m_CurrentColliding; }
		std::vector<HitBox> GetCurrentCollidingEnter()const { return m_CurrentCollidingEnter; }
		std::vector<HitBox> GetCurrentCollidingExit()const { return m_CurrentCollidingExit; }

		void SetDebugRender(const bool x) { m_DebugRender = x; }

		static std::vector<HitBox*> CheckRect(const Rectf& rect);
		static std::vector<HitBox*> CheckCircle(const Circlef& circle);

	private:
		HitBox* m_HitBox = new HitBox{};
		Point2f m_OffSet{};
		float m_Width = 0;
		float m_Height = 0;
		int m_Layer = 0;
		bool m_DebugRender = false;
		std::vector<HitBox> m_CurrentColliding;
		std::vector<HitBox> m_CurrentCollidingEnter;
		std::vector<HitBox> m_CurrentCollidingExit;
		
		static std::vector<HitBox*>* HitBoxes;
		static int Counter;
		static bool HasBeenUpdated;
		
		void Awake() override;
		void Tick() override;
		void PreTick() override;
		void Render() const override;
		static void RegisterHitBox(HitBox* hitBox);
		static void UnRegisterHitBox(HitBox* hitBox);
		bool IsInList(HitBox* hitbox);
		void HandleCollision();
		void UpdateHitbox()const;
	};
}
