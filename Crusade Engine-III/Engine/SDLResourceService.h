#pragma once
#include "ResourceService.h"
namespace Crusade
{
	class SDLResourceService final : public ResourceService
	{
	public:
		SDLResourceService();
		Texture* LoadTexture(const std::string& file, bool isFullPath = false) override;
		Texture* LoadTextTexture(const std::string& file, unsigned size, const std::string& text, const Color4f& color, bool isFullPath = false) override;
		SoundEffect* LoadSoundEffect(const std::string& file, bool isFullPath = false) override;
	private:
		std::string m_PathExtra = "../Resources/";
	};
}
