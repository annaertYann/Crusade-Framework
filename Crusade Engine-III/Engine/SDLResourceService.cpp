#include "SDLResourceService.h"
#include <SDL_image.h>
#include "OpenGLTexture.h"
#include "Debug.h"
#include "OpenGlSoundEffect.h"
using namespace Crusade;
SDLResourceService::SDLResourceService()
{
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		Debug::Print("Error Init PNG Support");
		return;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		Debug::Print("Error Init ttf Support");
		return;
	}

	const auto file = std::string("/../../Resources/");
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	auto path = std::string(buffer).substr(0, pos);
	path += file;
	m_PathExtra = path;

}

Texture* SDLResourceService::LoadTextTexture(const std::string& file,const unsigned size, const std::string& text, const Color4f& color, bool isFullPath)
{
	/*auto* iTried = FindTexture(m_PathExtra + file);

	if (iTried != nullptr)
		return iTried;*/
	auto pathextra = m_PathExtra;
	if (isFullPath)
		pathextra = "";

	Texture* temp = new OpenGLTexture{ text,pathextra + file,int(size),color };
	
	if (temp->IsCreationOk())
	{
		m_Textures.push_back(temp);
		return temp;
	}

	Debug::Print("Texture creation failed : resourceManager: loadTexttexture");
	Debug::Print(file);
	delete temp;

	auto* iTriedMissing = FindTexture(pathextra + "Crusade/MissingTexture.png");

	if (iTriedMissing != nullptr)
		return iTriedMissing;

	Texture* tempMissing = new OpenGLTexture{ pathextra + "Crusade/MissingTexture.png" };

	if (tempMissing->IsCreationOk())
	{
		m_Textures.push_back(tempMissing);
		return tempMissing;
	}
	Debug::Print("Can't find missingTexturePNG : resourceManager: loadtexture");
	delete tempMissing;
	return nullptr;
}

Texture* SDLResourceService::LoadTexture(const std::string& file, bool isFullPath )
{
	auto pathextra = m_PathExtra;
	if (isFullPath)
		pathextra = "";

	auto* iTried = FindTexture(pathextra + file);

	if (iTried != nullptr)
		return iTried;
	
	Texture* temp = new OpenGLTexture{ pathextra + file };
	
	if (temp->IsCreationOk())
	{
		m_Textures.push_back(temp);
		return temp;
	}
	Debug::Print("Texture creation failed : resourceManager: loadtexture");
	Debug::Print(file);
	delete temp;

	auto* iTriedMissing = FindTexture(pathextra + "Crusade/MissingTexture.png");

	if (iTriedMissing != nullptr)
		return iTriedMissing;

	Texture* tempMissing = new OpenGLTexture{ pathextra + "Crusade/MissingTexture.png"};

	if (tempMissing->IsCreationOk())
	{
		m_Textures.push_back(tempMissing);
		return tempMissing;
	}
	Debug::Print("Can't find missingTexturePNG : resourceManager: loadtexture");
	Debug::Print(file);
	delete tempMissing;
	return nullptr;
}

SoundEffect* SDLResourceService::LoadSoundEffect(const std::string& file, bool isFullPath)
{
	auto pathextra = m_PathExtra;
	if (isFullPath)
		pathextra = "";

	auto* iTried = FindSoundEffect(pathextra + file);

	if (iTried != nullptr)
		return iTried;

	SoundEffect* temp = new OpenGlSoundEffect{ pathextra + file };

	if (temp->IsValid())
	{
		m_SoundEffects.push_back(temp);
		return temp;
	}
	Debug::Print("SoundEffect creation failed : resourceManager: loadSoundEffect");
	Debug::Print(file);
	delete temp;

	return nullptr;
}
