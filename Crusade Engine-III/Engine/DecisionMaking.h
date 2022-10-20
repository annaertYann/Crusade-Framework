#pragma once
namespace Crusade
{
	class DecisionMaking
	{
	public:
		DecisionMaking() = default;
		virtual ~DecisionMaking() = default;

		DecisionMaking(const DecisionMaking& other) = delete;
		DecisionMaking(DecisionMaking&& other) = delete;
		DecisionMaking& operator=(const DecisionMaking& other) = delete;
		DecisionMaking& operator=(DecisionMaking&& other) = delete;

		virtual void Update(float deltaT) = 0;

	};
}