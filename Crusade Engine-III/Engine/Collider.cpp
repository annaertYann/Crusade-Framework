#include "Collider.h"
#include <algorithm>
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"
#include "Graphics.h"
#include "Renderer.h"
using namespace Crusade;
int Collider::Counter = 0;
std::vector<Collider::HitBox*>* Collider::HitBoxes{};
bool Collider::HasBeenUpdated = false;
Collider::~Collider()
{
	Counter--;
	UnRegisterHitBox(m_HitBox);
	delete m_HitBox;
	m_HitBox = nullptr;
	
	if (Counter <= 0)
	{
		std::vector<HitBox*>().swap(*HitBoxes);
		delete HitBoxes;
		HitBoxes = nullptr;
	}
}

void Collider::Awake()
{
	if (!HitBoxes)
		HitBoxes = new std::vector<HitBox*>{};
	Counter++;
	RegisterHitBox(m_HitBox);
	m_HitBox->owner = m_GameObject;
	m_GameObject->AddComponent<Renderer>();
}

void Collider::RegisterHitBox(HitBox* hitBox)
{
	if (!hitBox)
		return;

	HitBoxes->push_back(hitBox);
}

void Collider::UnRegisterHitBox(HitBox* hitBox)
{
	HitBoxes->erase(std::remove_if(HitBoxes->begin(), HitBoxes->end(), [&](HitBox* p)
	{
		return p->ID == hitBox->ID;
	}), HitBoxes->end());
}

int Collider::HitBox::NextID = 0;

Collider::HitBox::HitBox()
{
	ID = NextID;
	NextID++;
}

void Collider::Tick()
{
	HasBeenUpdated = false;
}

void Collider::UpdateHitbox() const
{
	const auto scale = GetTransform()->GetScale();
	auto center = Point2f{ GetTransform()->GetPosition().x,GetTransform()->GetPosition().y };
	center.x += m_OffSet.x;
	center.y += m_OffSet.y;

	auto width = m_Width;
	auto heigt = m_Height;
	width *= abs(scale.x);
	heigt *= abs(scale.y);


	m_HitBox->hitBox.left = center.x - width / 2;
	m_HitBox->hitBox.bottom = center.y - heigt / 2;
	m_HitBox->hitBox.width = width;
	m_HitBox->hitBox.height = heigt;
}


void Collider::PreTick()
{
	if(!HasBeenUpdated)
	{
		HasBeenUpdated = true;
		for (const auto hitbox : *HitBoxes)
		{
			hitbox->owner->GetComponent<Collider>()->UpdateHitbox();
		}
	}
	
	HandleCollision();
}

void Collider::HandleCollision()
{
	m_CurrentCollidingEnter.clear();
	m_CurrentCollidingExit.clear();
	std::vector<HitBox> newCurrentColliding;
	for (auto* hitbox : *HitBoxes)
	{
		if (hitbox->ID != m_HitBox->ID)
		{
			const bool isColliding = Math::IsOverlapping(hitbox->hitBox, m_HitBox->hitBox);
			if (isColliding)
				newCurrentColliding.push_back(*hitbox);

			if (!IsInList(hitbox))
			{
				if (isColliding)
				{
					newCurrentColliding.push_back(*hitbox);
					m_CurrentCollidingEnter.push_back(*hitbox);
				}
			}
			else
			{
				if (!isColliding)
				{
					m_CurrentCollidingExit.push_back(*hitbox);
				}
			}
		}
	}
	m_CurrentColliding = newCurrentColliding;
}

bool Collider::IsInList(HitBox* hitbox)
{
	/*if (std::any_of(m_CurrentColliding.begin(), m_CurrentColliding.end(), [&](const HitBox& i) {return i.ID == hitbox->ID; }))
		return true;

	return false;*/
	for(const auto& hit : m_CurrentColliding)
	{
		if (hit.ID == hitbox->ID)
			return true;
	}
	return false;
}

void Collider::Render() const
{
	if (!m_DebugRender)
		return;

	Graphics::SetColor(Color4f{0,1,0,1});
	Graphics::RenderSquare(m_HitBox->hitBox, 1);
}

std::vector<Collider::HitBox*> Collider::CheckCircle(const Circlef& circle)
{
	std::vector<HitBox*> hitBoxes;
	for (auto* hitbox : *HitBoxes)
	{
		if (hitbox->owner->GetIsActive())
		{
			hitbox->owner->GetComponent<Collider>()->UpdateHitbox();
			if (Math::IsOverlapping(hitbox->hitBox, circle))
			{
				hitBoxes.push_back(hitbox);
			}
		}
	}
	return hitBoxes;
}

std::vector<Collider::HitBox*> Collider::CheckRect(const Rectf& rect)
{
	std::vector<HitBox*> hitBoxes;
	for (auto* hitbox : *HitBoxes)
	{
		if (hitbox->owner->GetIsActive())
		{
			hitbox->owner->GetComponent<Collider>()->UpdateHitbox();
			if (Math::IsOverlapping(hitbox->hitBox, rect))
			{
				hitBoxes.push_back(hitbox);
			}
		}
	}
	return hitBoxes;
}
