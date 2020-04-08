#include "Buoyancy2System.h"
#include "Buoyancy2Component.h"
#include "TransformComponentV2.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	Buoyancy2System::Buoyancy2System()
	{
		requireComponent<Buoyancy2Component>();
		requireComponent<TransformComponentV2>();
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
	}

	void Buoyancy2System::Update(float deltaTime, float waterDensity)
	{
		for (auto e : getEntities())
		{
			auto& buoyancyObject = e.getComponent<Buoyancy2Component>();

			if (buoyancyObject.floatingEntity.hasComponent<TransformComponentV2>())
			{
				float depth = buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().y;
				auto& rigidbody = e.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = buoyancyObject.floatingEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				buoyancyObject.centerOfBuoyancy = Vector3(buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().x, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().y - 10, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().z + 25);

				if (depth >= buoyancyObject.waterHeight + buoyancyObject.maxDepth)
				{
					return;
				}

				Vector3 force = Vector3(0, 0, 0);
				getWorld().data.renderUtil->DrawCube(buoyancyObject.centerOfBuoyancy, Vector3(9, 9, 9));

				//if (depth <= buoyancyObject.waterHeight - buoyancyObject.maxDepth)
				if (depth < 0.0f)
				{
					float force = (waterDensity * buoyancyObject.volume) * 0.1f * buoyancyObject.maxDepth;
					forceAndTorque.AddForceAtPoint(Vector3(0, force, 0), buoyancyObject.centerOfBuoyancy, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition());
				}
				else
				{
					float force = waterDensity * buoyancyObject.volume * (depth - buoyancyObject.maxDepth - buoyancyObject.waterHeight) * 0.1f * buoyancyObject.maxDepth;
					forceAndTorque.AddForceAtPoint(Vector3(0, force, 0), buoyancyObject.centerOfBuoyancy, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition());
				}
				return;
			}
		}
	}
}
