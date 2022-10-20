#include "Wall.h"
void Wall::Awake()
{
	m_Collider = m_GameObject->AddComponent<Collider>();
}

void Wall::LateTick()
{
	const auto rect = m_Collider->GetHitBox();
	const auto list = Collider::CheckRect(rect);

	for (const auto& hitBox : list)
	{
		if (hitBox->owner->GetComponent<Wall>() != nullptr)
			continue;

		auto* collOther = hitBox->owner->GetComponent<Collider>();
		if (collOther != nullptr)
		{
			if(collOther->GetLayer() < 0)
				continue;
		}

		std::vector<Point2f> vertices;

		vertices.emplace_back(Point2f{ rect.left,rect.bottom });
		vertices.emplace_back(Point2f{ rect.left + rect.width,rect.bottom });
		vertices.emplace_back(Point2f{ rect.left + rect.width,rect.bottom + rect.height });
		vertices.emplace_back(Point2f{ rect.left,rect.bottom + rect.height });

		auto hitInfo = Math::HitInfo{};
		Math::Raycast(vertices,Point2f{hitBox->owner->GetTransform()->GetPosition()},Point2f{GetTransform()->GetPosition()},hitInfo);

		bool continu = true;
		while (continu)
		{
			continu = false;
			auto collisions = Collider::CheckRect(rect);
			for (const auto* collision : collisions)
			{
				if (collision->GetID() == hitBox->GetID() )
				{
					constexpr float distance = 1.f;
					auto position = collision->owner->GetTransform()->GetPosition();

					if (hitInfo.normal.Length() < 1)
						hitInfo.normal = Vector2f{1,1};

					position += hitInfo.normal * distance * -1;
					collision->owner->GetTransform()->SetPosition(position);
					continu = true;
				}
			}
		}
		hitBox->owner->SendMessage("WallHit");
	}
}
