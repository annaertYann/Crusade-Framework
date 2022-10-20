#include "Resource.h"
#include "ServiceLocator.h"
#include "ResourceService.h"
using namespace Crusade;
ResourceService* Resource::m_Service = nullptr;

Texture* Resource::LoadTextTexture(const std::string& file, unsigned size, const std::string& text, const Color4f& color, bool isFullPath )
{
	InitService();
	if (m_Service == nullptr)
		return nullptr;
	return m_Service->LoadTextTexture(file,size,text,color,isFullPath);
}

Texture* Resource::LoadTexture(const std::string& file, bool isFullPath )
{
	InitService();
	if (m_Service == nullptr)
		return nullptr;
	return m_Service->LoadTexture(file,isFullPath);
}

bool Resource::RemoveTexture(Texture* texture)
{
	InitService();
	if (m_Service == nullptr)
		return false;
	return m_Service->RemoveTexture(texture);
}

SoundEffect* Resource::LoadSoundEffect(const std::string& file, bool isFullPath)
{
	InitService();
	if (m_Service == nullptr)
		return nullptr;

	return m_Service->LoadSoundEffect(file,isFullPath);
}

void Resource::InitService()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<ResourceService>();
}
