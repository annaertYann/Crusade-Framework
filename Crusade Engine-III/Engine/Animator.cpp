#include "Animator.h"
#include "Debug.h"
#include "GameObject.h"
#include "Time.h"
#include "TextureRenderer.h"
using namespace Crusade;
Animator::~Animator()
{
	for(const auto* transition : m_Transitions)
	{
		delete transition;
		transition = nullptr;
	}

	for (const auto* animation : m_Animations)
	{
		delete animation;
		animation = nullptr;
	}
}


void Animator::SetStartAnimation(Animation* animation)
{
	m_CurrentAnimation = animation;
	m_Animations.push_back(animation);
}

void Animator::Awake()
{
	m_Renderer = m_GameObject->AddComponent<TextureRenderer>();
	
}

void Animator::Start()
{
	if(m_CurrentAnimation)
	m_CurrentAnimation->Start(m_Renderer);
}

void Animator::Tick()
{
	for (const auto& transition : m_Transitions)
	{
		if (m_CurrentAnimation->GetTag() == transition->GetFrom()->GetTag())
		{
			if (transition->ToTransition())
			{
				ResetAllConditions();
				m_CurrentAnimation = transition->GetTo();
				m_CurrentAnimation->Start(m_Renderer);
				break;
			}
		}
	}
	m_CurrentAnimation->Update(m_Renderer, Time::GetDeltaTime());
}
void Animator::TriggerTransition(const std::string& name)
{
	for (const auto& transition : m_Transitions)
	{
		if (transition->GetName() == name && transition->GetCondition() != nullptr)
		{
			*transition->GetCondition() = true;
			return;
		}
	}
}
void Animator::ResetAllConditions()
{
	for (const auto& transition : m_Transitions)
	{
		if (transition->GetCondition()) { *transition->GetCondition() = false; }
	}
}

void Animator::AddTransition(Transition* transition)
{
	if (!IsInAnimations(transition->GetFrom()))
		m_Animations.push_back(transition->GetFrom());
	if (!IsInAnimations(transition->GetTo()))
		m_Animations.push_back(transition->GetTo());
	m_Transitions.push_back(transition);
}

bool Animator::IsInAnimations(Animation* anim)
{
	for(const auto* animation :m_Animations)
	{
		if (animation->GetTag() == anim->GetTag())
			return true;
	}
	return false;
}