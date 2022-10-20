#include "Camera.h"
#include "Graphics.h"
#include "Transform.h"
#include "Time.h"
#include "Random.h"
#include "ProjectSettings.h"
using namespace Crusade;
Camera* Camera::Main = nullptr;
int Camera::NextCameraCounter = 0;
void Camera::Awake()
{
	m_CameraCounter = NextCameraCounter;
	NextCameraCounter++;
	m_Transform = GetTransform();
	Main = this;

	
}

void Camera::OnDestroy()
{
	if(Main->m_CameraCounter == m_CameraCounter)
		Main = nullptr;
}

void Camera::LateTick()
{
	if (Main->m_CameraCounter != m_CameraCounter)
		return;

	auto position = m_Transform->GetPosition();
	const auto rotation = m_Transform->GetRotation();
	const auto scale = m_Transform->GetScale().x;
	const auto window = Graphics::GetWindow();
	const auto referenceWindow = *ProjectSettings::GameReferenceWindow;
	position += CalculateShake();

	Graphics::ClearMatrix();
	Vector2f cameraTranslation{ window.width / 2, window.height / 2 };
	cameraTranslation *=  1 / scale;
	const Vector2f objectTranslation{ -position.x, -position.y };
	const Vector2f translation{cameraTranslation + objectTranslation};
	const Vector2f windowReferenceScale{ (window.width / referenceWindow.width) , (window.height / referenceWindow.height) };
	Vector2f windowReferencerTranslation{ (referenceWindow.width - window.width) / 2  , (referenceWindow.height  - window.height) / 2};
	windowReferencerTranslation *= 1 / scale;

	Graphics::Scale(windowReferenceScale.x, windowReferenceScale.y, 1);
	Graphics::Scale(scale,scale,1);
	Graphics::Translate(windowReferencerTranslation.x, windowReferencerTranslation.y, 0);
	Graphics::Translate(translation.x , translation.y , 0);
	Graphics::Translate(-objectTranslation.x,- objectTranslation.y, 0);
	Graphics::Rotate(rotation, 0, 0, 1);
	Graphics::Translate(objectTranslation.x, objectTranslation.y, 0);

	m_CameraWindow = CreateCameraWindow();
}

Vector2f Camera::ScreenToWorld(const Vector2f& screenPosition)const
{
	const auto position = m_Transform->GetPosition();
	const auto window = Graphics::GetWindow();
	const auto referenceWindow = *ProjectSettings::GameReferenceWindow;
	const Vector2f windowReferenceScale{ (window.width / referenceWindow.width) , (window.height / referenceWindow.height) };
	Vector2f scale = Vector2f(1 / m_Transform->GetScale().x , 1 / m_Transform->GetScale().x);
	scale.x *=  1 / windowReferenceScale.x;
	scale.y *= 1 / windowReferenceScale.y;

	Vector2f newPos = screenPosition;
	newPos.x = screenPosition.x * scale.x;
	newPos.y = window.height * scale.y - screenPosition.y * scale.y;

	Vector2f cameraTranslation{ -window.width / 2, -window.height / 2 };
	cameraTranslation.x *= scale.x;
	cameraTranslation.y *= scale.y;
	const Vector2f objectTranslation{ position.x, position.y };
	const Vector2f translation{ cameraTranslation + objectTranslation };

	newPos += translation;
	return newPos;
}

Rectf Camera::GetCameraWindow() const
{
	return m_CameraWindow;
}

Rectf Camera::CreateCameraWindow() const
{
	const auto scale = 1 / m_Transform->GetScale().x;
	const auto window = Graphics::GetWindow();
	const auto position = m_Transform->GetPosition();
	const Vector2f objectTranslation{ position.x, position.y };
	Vector2f cameraTranslation{ -window.width / 2, -window.height / 2 }; cameraTranslation *= scale;

	return Rectf{ objectTranslation.x + cameraTranslation.x,objectTranslation.y + cameraTranslation.y,
		Graphics::GetWindow().width * scale,Graphics::GetWindow().height * scale };
}

void Camera::ScreenShake(const float duration,const float strenght,const float frequency)
{
	m_ShakeDuration.SetDelayTime(duration);
	m_ShakeFrequency.SetDelayTime(frequency);
	m_ShakeStrenght = strenght;
	m_ShakeDuration.Start();
	m_ShakeFrequency.Start();
}

Vector2f Camera::CalculateShake()
{
	if(m_ShakeDuration.Update(Time::GetDeltaTime()))
	{
		m_ShakeOffSet = Vector2f{};
		m_ShakeDuration.Stop();
	}

	if (m_ShakeDuration.GetActive())
		if (m_ShakeFrequency.Update(Time::GetDeltaTime()))
		{
			m_ShakeFrequency.Start();
			m_ShakeOffSet = Vector2f{ Random::Range(-m_ShakeStrenght,m_ShakeStrenght),{Random::Range(-m_ShakeStrenght,m_ShakeStrenght)} };
		}

	return m_ShakeOffSet;
}
