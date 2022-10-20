#pragma once
#include <functional>
#include "BlackBoard.h"
#include "DecisionMaking.h"
namespace Crusade
{
	enum class BehaviorState
	{
		Failure,
		Success,
		Running
	};

	class IBehavior
	{
	public:
		IBehavior() = default;
		virtual ~IBehavior() = default;

		IBehavior(const IBehavior& other) = delete;
		IBehavior(IBehavior&& other) = delete;
		IBehavior& operator=(const IBehavior& other) = delete;
		IBehavior& operator=(IBehavior&& other) = delete;

		virtual BehaviorState Execute(Blackboard* pBlackBoard) = 0;

	protected:
		BehaviorState m_CurrentState = BehaviorState::Failure;
	};

	class BehaviorComposite : public IBehavior
	{
	public:
		explicit BehaviorComposite(std::vector<IBehavior*> childrenBehaviors)
		{
			m_ChildrenBehaviors = childrenBehaviors;
		}
		~BehaviorComposite() override
		{
			for (const auto pb : m_ChildrenBehaviors)
				delete pb;

			m_ChildrenBehaviors.clear();
		}

		BehaviorComposite(const BehaviorComposite& other) = delete;
		BehaviorComposite(BehaviorComposite&& other) = delete;
		BehaviorComposite& operator=(const BehaviorComposite& other) = delete;
		BehaviorComposite& operator=(BehaviorComposite&& other) = delete;

		BehaviorState Execute(Blackboard* pBlackBoard) override = 0;

	protected:
		std::vector<IBehavior*> m_ChildrenBehaviors = {};
	};

	class BehaviorSelector : public BehaviorComposite
	{
	public:
		explicit BehaviorSelector(std::vector<IBehavior*> childrenBehaviors) :
			BehaviorComposite(childrenBehaviors) {}
		~BehaviorSelector() override = default;

		BehaviorSelector(const BehaviorSelector& other) = delete;
		BehaviorSelector(BehaviorSelector&& other) = delete;
		BehaviorSelector& operator=(const BehaviorSelector& other) = delete;
		BehaviorSelector& operator=(BehaviorSelector&& other) = delete;

		BehaviorState Execute(Blackboard* pBlackBoard) override;
	};

	class BehaviorSequence : public BehaviorComposite
	{
	public:
		explicit BehaviorSequence(std::vector<IBehavior*> childrenBehaviors) :
			BehaviorComposite(childrenBehaviors) {}
		virtual ~BehaviorSequence() = default;

		virtual BehaviorState Execute(Blackboard* pBlackBoard) override;
	};

	class BehaviorPartialSequence : public BehaviorSequence
	{
	public:
		explicit BehaviorPartialSequence(std::vector<IBehavior*> childrenBehaviors)
			: BehaviorSequence(childrenBehaviors) {}
		virtual ~BehaviorPartialSequence() = default;

		virtual BehaviorState Execute(Blackboard* pBlackBoard) override;

	private:
		unsigned int m_CurrentBehaviorIndex = 0;
	};

	class BehaviorConditional : public IBehavior
	{
	public:
		explicit BehaviorConditional(std::function<bool(Blackboard*)> fp) : m_fpConditional(fp) {}
		BehaviorState Execute(Blackboard* pBlackBoard) override;

	private:
		std::function<bool(Blackboard*)> m_fpConditional = nullptr;
	};

	class BehaviorAction : public IBehavior
	{
	public:
		explicit BehaviorAction(std::function<BehaviorState(Blackboard*)> fp) : m_fpAction(fp) {}
		BehaviorState Execute(Blackboard* pBlackBoard) override;

	private:
		std::function<BehaviorState(Blackboard*)> m_fpAction = nullptr;
	};

	class BehaviorTree final : public DecisionMaking
	{
	public:
		explicit BehaviorTree(IBehavior* pRootComposite)
			:m_pBlackBoard{ new Blackboard() }, m_pRootComposite(pRootComposite){}

		~BehaviorTree() override
		{
			delete m_pRootComposite;
			delete m_pBlackBoard;
		}

		BehaviorTree(const BehaviorTree& other) = delete;
		BehaviorTree(BehaviorTree&& other) = delete;
		BehaviorTree& operator=(const BehaviorTree& other) = delete;
		BehaviorTree& operator=(BehaviorTree&& other) = delete;

		void Update(float ) override
		{
			if (m_pRootComposite == nullptr)
			{
				m_CurrentState = BehaviorState::Failure;
				return;
			}

			m_CurrentState = m_pRootComposite->Execute(m_pBlackBoard);
		}

		Blackboard* GetBlackboard() const { return m_pBlackBoard; }

	private:
		BehaviorState m_CurrentState = BehaviorState::Failure;
		Blackboard* m_pBlackBoard = nullptr;
		IBehavior* m_pRootComposite = nullptr;
	};
}