#pragma once
#include <string>
#include "GeneralStucts.h"
namespace Crusade
{
	class Texture;
	class SoundEffect;
	class ResourceService;
	class Resource final
	{
	public:
		Resource() = delete;
		~Resource() = delete;

		Resource(const Resource& other) = delete;
		Resource(Resource&& other) = delete;
		Resource& operator=(const Resource& other) = delete;
		Resource& operator=(Resource&& other) = delete;

		static Texture* LoadTexture(const std::string& file,bool isFullPath = false);
		static Texture* LoadTextTexture(const std::string& file, unsigned size, const std::string& text, const Color4f& color, bool isFullPath = false);
		static bool RemoveTexture(Texture* texture);
		static SoundEffect* LoadSoundEffect(const std::string& file, bool isFullPath = false);
	private:
		static ResourceService* m_Service;
		static void InitService();
	};
}
