#pragma once
namespace Crusade
{
	class RenderService;
	class InputService;
	class ResourceService;
	class GraphicsService;
	class AudioService;
	class ServiceCreator final
	{
	public:
		ServiceCreator() = delete;
		~ServiceCreator() = delete;

		ServiceCreator(const ServiceCreator& other) = delete;
		ServiceCreator(ServiceCreator&& other) = delete;
		ServiceCreator& operator=(const ServiceCreator& other) = delete;
		ServiceCreator& operator=(ServiceCreator&& other) = delete;

		static RenderService* CreateRenderer();
		static InputService* CreateInputSystem();
		static ResourceService* CreateResourceManager();
		static GraphicsService* CreateGraphicsManager();
		static AudioService* CreateAudioManager();
	};
}

