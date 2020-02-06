#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 1)
		{
			mass = _mass;
		}
		float mass;
	};
}
