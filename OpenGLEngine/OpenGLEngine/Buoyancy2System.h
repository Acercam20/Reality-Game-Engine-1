#pragma once
#include "ECSConfig.h"
#include "Buoyancy2Component.h"

namespace Reality
{
	class Buoyancy2System : public ECSSystem
	{
	public:
		Buoyancy2System();
		void Update(float deltaTime, float waterDensity);
	};
}
