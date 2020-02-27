#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleCollisionComponent
	{
		TriangleCollisionComponent(
			ECSEntity _connectedEntityA = ECSEntity(),
			ECSEntity _connectedEntityB = ECSEntity(),
			ECSEntity _connectedEntityC = ECSEntity())
			: entityA(_connectedEntityA),
			entityB(_connectedEntityB),
			entityC(_connectedEntityC)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		ECSEntity entityC;
	};
}
