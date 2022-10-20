#pragma once
#include <string>
namespace Crusade
{
	class Animation;
	class Transition final
	{
	public:
		Transition(Animation* from, Animation* to, const std::string& name, bool hasToFinishAnimation, bool hasCondition);
		~Transition();
		
		Transition(const Transition& other) = delete;
		Transition(Transition&& other) = delete;
		Transition& operator=(const Transition& other) = delete;
		Transition& operator=(Transition&& other) = delete;
		
		bool ToTransition()const;
		std::string GetName() const { return m_Name; }
		Animation* GetFrom()const { return m_From; }
		Animation* GetTo()const { return m_To; }
		bool* GetCondition() const { return m_Condition; }
	
	private:
		bool m_HasToFinishAnimation = false;
		Animation* m_From{};
		Animation* m_To{};
		bool* m_Condition{ nullptr };
		std::string m_Name{};
	};

}
