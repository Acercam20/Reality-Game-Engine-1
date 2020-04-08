#include "BuoyancySystem.h"
#include "BuoyancyComponent.h"
#include "TransformComponentV2.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime, float waterDensity)
	{
		for (auto e : getEntities())
		{
			auto& buoyancyObject = e.getComponent<BuoyancyComponent>();

			if (buoyancyObject.floatingEntity.hasComponent<TransformComponentV2>())
			{
				float depth = buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().y;
				auto& rigidbody = e.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = buoyancyObject.floatingEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				buoyancyObject.centerOfBuoyancy = Vector3(buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().x, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().y, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition().z - 25);


				if (depth >= buoyancyObject.waterHeight + buoyancyObject.maxDepth)
				{
					return;
				}

				getWorld().data.renderUtil->DrawCube(buoyancyObject.centerOfBuoyancy, Vector3(5, 5, 5));
				Vector3 force = Vector3(0, 0, 0);

				//if (depth <= buoyancyObject.waterHeight - buoyancyObject.maxDepth)
				if (depth < 0.0f)
				{
					float force = (waterDensity * buoyancyObject.volume) * 0.1f * buoyancyObject.maxDepth;
					forceAndTorque.AddForceAtPoint(Vector3(0, force, 0), buoyancyObject.centerOfBuoyancy, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition());
					//force.y = waterDensity * buoyancyObject.volume;
					//buoyancyObject.floatingEntity.getComponent<ForceAccumulatorComponent>().AddForce(force);
				}
				else
				{
					float force = waterDensity * buoyancyObject.volume * (depth - buoyancyObject.maxDepth - buoyancyObject.waterHeight) * 0.1f * buoyancyObject.maxDepth;
					forceAndTorque.AddForceAtPoint(Vector3(0, force, 0), buoyancyObject.centerOfBuoyancy, buoyancyObject.floatingEntity.getComponent<TransformComponentV2>().GetPosition());
					//force.y = waterDensity * buoyancyObject.volume * (depth - buoyancyObject.maxDepth - buoyancyObject.waterHeight) / 2 * buoyancyObject.maxDepth;
					//buoyancyObject.floatingEntity.getComponent<ForceAccumulatorComponent>().AddForce(force);
				}
				return;
			}
		}
	}
}
