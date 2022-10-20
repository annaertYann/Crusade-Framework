#pragma once
#include <memory>
#include <vector>
#include "Singleton.h"
#include "Service.h"
namespace Crusade
{
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		template <typename T> T* GetService();
		template <typename T> void RegisterService(Service* service);
		void ResetServices();

	private:
		std::vector<std::unique_ptr<Service>>* m_Services = nullptr;
	};

	inline void ServiceLocator::ResetServices()
	{
		delete m_Services;
		m_Services = nullptr;
	}

	template <typename T>
	T* ServiceLocator::GetService()
	{
		if (m_Services == nullptr)
			return nullptr;

		for (const std::unique_ptr<Service>& service : *m_Services)
		{
			T* temp = dynamic_cast<T*>(service.get());
			if (temp != nullptr)
				return temp;
		}
		return nullptr;
	}

	template <typename T>
	void ServiceLocator::RegisterService(Service* service)
	{
		if (m_Services == nullptr)
			m_Services = new std::vector<std::unique_ptr<Service>>();

		T* newSerivce = dynamic_cast<T*>(service);
		bool fail = false;
		if (newSerivce == nullptr)
			fail = true;
		if (GetService<T>() != nullptr)
			fail = true;
		if (fail)
		{
			return;
		}
		m_Services->push_back(std::unique_ptr<Service>(service));
	}
}
