#pragma once
#include <vector>
#include <string>
namespace Crusade
{
	class Painter  
	{
	public:
		Painter();
		virtual ~Painter() = default;

		Painter(const Painter& other) = delete;
		Painter(Painter&& other) = delete;
		Painter& operator=(const Painter& other) = delete;
		Painter& operator=(Painter&& other) = delete;

		virtual void Render()const = 0;
		int GetID()const { return m_ID; }

		void SetLayer(const int& layer);
		int& GetLayer() { return m_Layer; }

	private:
		int m_ID;
		static int m_NextID;
		int m_Layer {};
	};
}
