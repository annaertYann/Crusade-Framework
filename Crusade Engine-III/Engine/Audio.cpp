#include "Audio.h"
#include "AudioService.h"
#include "ServiceLocator.h"
using namespace Crusade;
AudioService* Audio::m_Service = nullptr;

void Audio::play(const std::string& path, float volume, int loops)
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->play(path, volume, loops);
}

void Audio::StopAll()
{
	InitService();
	if (m_Service == nullptr)
		return;
	m_Service->StopAll();
}
void Crusade::Audio::SetOn(bool on)
{
	AudioService::m_On = on;
}

void Audio::InitService()
{
	if (m_Service == nullptr)
		m_Service = ServiceLocator::GetInstance().GetService<AudioService>();
}
