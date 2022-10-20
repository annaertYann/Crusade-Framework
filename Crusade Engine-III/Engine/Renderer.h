#pragma once
#include "Component.h"
namespace Crusade
{
	class Painter;
	class Renderer final : public Component
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;

		static void RegisterPainter(Painter* painter);
		static void UnRegisterPainter(Painter* painter);

		void SetLayer(const int& layer);
		int GetLayer()const { return m_Layer; }
		static void SetLayer(GameObject* object, const int& layer);

	private:
		Painter* m_Painter = nullptr;
		int m_Layer{};

		void Awake()override;
		void Start() override;
		void OnDisable() override;
		void OnEnable() override;
		void OnDestroy() override;
	};
}
