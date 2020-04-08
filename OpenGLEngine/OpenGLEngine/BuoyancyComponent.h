#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(float _maxDepth = 20.0f,
			float _volume = 20.0f,
			float _waterHeight = 50.0f,
			float _liquidDensity = 100.0f,
			ECSEntity _floatingEntity = ECSEntity(),
			Vector3 _centerOfBuoyancy = Vector3(0, 0, 0)) :
			maxDepth(_maxDepth),
			volume(_volume),
			waterHeight(_waterHeight),
			liquidDensity(_liquidDensity),
			floatingEntity(_floatingEntity),
			centerOfBuoyancy(_centerOfBuoyancy)
		{

		}
		float maxDepth;
		float volume;
		float waterHeight;
		float liquidDensity;
		ECSEntity floatingEntity;
		Color color = Color(1, 1, 0, 1);
		Vector3 centerOfBuoyancy;
	};
}
