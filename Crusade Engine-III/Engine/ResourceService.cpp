#include "ResourceService.h"
#include "Texture.h"
#include "SoundEffect.h"

using namespace Crusade;
ResourceService::~ResourceService()
{
	for(auto* texture : m_Textures)
	{
		delete texture;
	}
	for (auto* texture : m_SoundEffects)
	{
		delete texture;
	}
}

Texture* ResourceService::FindTexture(const std::string& path)
{
	auto point = std::find_if(m_Textures.begin(), m_Textures.end(), [&](Texture* p) { return p->GetPath() == path; });
	if (point != m_Textures.end())
		return *point;
	else
		return nullptr;
}

SoundEffect* ResourceService::FindSoundEffect(const std::string& path)
{
	auto point = std::find_if(m_SoundEffects.begin(), m_SoundEffects.end(), [&](SoundEffect* p) { return p->GetPath() == path; });
	if (point != m_SoundEffects.end())
		return *point;
	else
		return nullptr;
}

bool ResourceService::RemoveTexture(Texture* texture)
{
	m_Textures.erase(std::remove_if(m_Textures.begin(), m_Textures.end(), [&](Texture* object)
		{
			if(object->GetTag() == texture->GetTag())
			{
				delete object;
				object = nullptr;
				return true;
			}
			return false;
		}), m_Textures.end());

	return false;
}

