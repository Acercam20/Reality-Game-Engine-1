#pragma once
#include "ECSConfig.h"
#include "TriangleCollisionComponent.h"

namespace Reality
{
	class TriangleCollisionSystem : public ECSSystem
	{
	public:
		TriangleCollisionSystem();
		void Update(float deltaTime);

		void SetCollidingEntity(ECSEntity _Entity)
		{
			collidingEntity = _Entity;
		}

	private:
		ECSEntity collidingEntity;
	};
}
