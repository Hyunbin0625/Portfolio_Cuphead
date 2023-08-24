#include "stdafx.h"
#include "ColliderComponent.h"

bool ColliderComponent::Intersect(const Vector2& coord)
{
	const Vector2& position = owner->GetPosition();
	const Vector2& scale = owner->GetScale();

	if (type == ColliderType::RECT)	// RECT�� ���
	{
		if (owner->GetRightVector() == RIGHT)	// ȸ������ check
		{
			Collision::RECT rect(position, scale);

			return Collision::IntersectRectCoord(rect, coord);	// �浹 check �Լ� ȣ�� �� ��ȯ
		}
		else	// ȸ���� �� ���
		{
			Matrix rectInverse = (owner->GetR() * owner->GetT()).Invert();	// Invert : ȣ���ϰ� �ִ� ����� ������� ���ؼ� ��ȯ�ϴ� �Լ�
			Vector2 transformedCoord = Vector2::Transform(coord, rectInverse);	// ��ǥ ��ȯ

			Collision::RECT rect(Vector2(), scale);


			return Collision::IntersectRectCoord(rect, transformedCoord);
		}
	}
	else if (type == ColliderType::CIRCLE)
	{
		Collision::CIRCLE circle(position, scale);

		return Collision::IntersectCircleCoord(circle, coord);
	}

	return false;
}

bool ColliderComponent::Intersect(const shared_ptr<ColliderComponent>& other)
{
	const Vector2& position = owner->GetPosition();
	const Vector2& scale = owner->GetScale();

	const Vector2& otherPos = other->GetOwner()->GetPosition();
	const Vector2& otherScale = other->GetOwner()->GetScale();

	if (type == ColliderType::RECT)
	{
		if (other->type == ColliderType::RECT)
		{
			if (owner->GetRightVector() == RIGHT && other->GetOwner()->GetRightVector() == RIGHT)
			{
				Collision::RECT rect1(position, scale);
				Collision::RECT rect2(otherPos, otherScale);

				return Collision::IntersectRectRect(rect1, rect2);
			}
			else
			{
				return Collision::IntersectRectRect(*owner, *(other->GetOwner()));	// object reference�� ���ϱ� ����
			}
		}
		else if (other->type == ColliderType::CIRCLE)
		{
			if (owner->GetRightVector() == RIGHT)
			{
				Collision::RECT rect1(position, scale);
				Collision::CIRCLE circle(otherPos, otherScale);

				return Collision::IntersectRectCircle(rect1, circle);
			}
			else
			{
				Matrix rectInverse = (owner->GetR() * owner->GetT()).Invert();
				Vector2 circlePivot = Vector2::Transform(otherPos, rectInverse);

				Collision::RECT rect(Vector2(), scale);
				Collision::CIRCLE circle(circlePivot, otherScale);

				return Collision::IntersectRectCircle(rect, circle);
			}
		}
	}
	else if (type == ColliderType::CIRCLE)
	{
		if (other->type == ColliderType::RECT)
		{
			if (other->GetOwner()->GetRightVector() == RIGHT)
			{
				Collision::CIRCLE circle(position, scale);
				Collision::RECT rect(otherPos, otherScale);

				return Collision::IntersectRectCircle(rect, circle);
			}
			else
			{
				Matrix rectInverse = (other->GetOwner()->GetR() * other->GetOwner()->GetT()).Invert();
				Vector2 circlePivot = Vector2::Transform(position, rectInverse);

				Collision::RECT rect(Vector2(), otherScale);
				Collision::CIRCLE circle(circlePivot, scale);

				return Collision::IntersectRectCircle(rect, circle);
			}
		}
		else if (other->type == ColliderType::CIRCLE)
		{
			Collision::CIRCLE circle1(position, scale);
			Collision::CIRCLE circle2(otherPos, otherScale);

			return Collision::IntersectCircleCircle(circle1, circle2);
		}
	}

	return false;
}
