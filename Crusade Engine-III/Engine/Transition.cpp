#include "Transition.h"
#include "Animation.h"
using namespace Crusade;
Transition::Transition(Animation* from, Animation* to, const std::string& name,const  bool hasToFinishAnimation, const bool hasCondition)
	:m_From(from)
	, m_To(to)
	, m_Name(name)
	, m_HasToFinishAnimation(hasToFinishAnimation)
{
	if (hasCondition)
		m_Condition = new bool();

}

Transition::~Transition()
{
	if (m_Condition != nullptr)
		delete m_Condition;
}


bool Transition::ToTransition()const
{
	bool condition = true;
	if (m_Condition)
	{
		condition = *m_Condition;
	}
	if (m_HasToFinishAnimation)
	{
		const auto hasToFinish = m_From->GetIsFinished();
		return hasToFinish && condition;
	}
	return condition;

}
