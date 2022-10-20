#pragma once
#include <string>
#include <vector>
#include "Service.h"

namespace Crusade
{
	struct Color4f;
	class Texture;
	class SoundEffect;
	class ResourceService : public Service
	{
	public:
		explicit ResourceService() = default;
		virtual ~ResourceService();

		ResourceService(const ResourceService& other) = delete;
		ResourceService(ResourceService&& other) = delete;
		ResourceService& operator=(const ResourceService& other) = delete;
		ResourceService& operator=(ResourceService&& other) = delete;
		
		virtual Texture* LoadTexture(const std::string& file, bool isFullPath = false) = 0;
		virtual Texture* LoadTextTexture(const std::string& file, unsigned int size, const std::string& text, const Color4f& color, bool isFullPath = false) = 0;
		virtual SoundEffect* LoadSoundEffect(const std::string& file, bool isFullPath = false) = 0;
		bool RemoveTexture(Texture* texture);
	protected:
		std::vector<Texture*> m_Textures;
		std::vector<SoundEffect*>m_SoundEffects;
		Texture* FindTexture(const std::string& path);
		SoundEffect* FindSoundEffect(const std::string& path);
	};
}
