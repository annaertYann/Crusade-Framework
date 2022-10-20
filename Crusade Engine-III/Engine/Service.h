#pragma once
namespace Crusade
{
	class Service
	{
	public:
		Service() = default;
		virtual ~Service() = default;

		Service(const Service& other) = delete;
		Service(Service&& other) = delete;
		Service& operator=(const Service& other) = delete;
		Service& operator=(Service&& other) = delete;
	private:
	};
}
