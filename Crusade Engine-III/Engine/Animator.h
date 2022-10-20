#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include "Transition.h"
#include "Animation.h"
namespace Crusade
{
	class Animator final :public Component
	{
	public:
		Animator() = default;
		~Animator()override;
		
		Animator(const Animator& other) = delete;
		Animator(Animator&& other) = delete;
		Animator& operator=(const Animator& other) = delete;
		Animator& operator=(Animator&& other) = delete;
		
		void AddTransition(Transition* transition);
		void TriggerTransition(const std::string& name);
		void SetStartAnimation(Animation* animation);
	
	private:
		void ResetAllConditions();
		void Awake() override;
		void Start() override;
		void Tick() override;
		bool IsInAnimations(Animation* animation);
		std::vector<Transition*>m_Transitions{};
		std::vector<Animation*>m_Animations{};
		Animation* m_CurrentAnimation{};
		TextureRenderer* m_Renderer{};
	};
}
