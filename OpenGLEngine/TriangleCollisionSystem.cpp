#include "TriangleCollisionSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	TriangleCollisionSystem::TriangleCollisionSystem()
	{
		requireComponent<TriangleCollisionComponent>();
	}

	void TriangleCollisionSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& tri = e.getComponent<TriangleCollisionComponent>();

			Vector3 point1 = tri.entityA.getComponent<TransformComponent>().position;
			Vector3 point2 = tri.entityB.getComponent<TransformComponent>().position;
			Vector3 point3 = tri.entityC.getComponent<TransformComponent>().position;

			Vector3 center = (point1 + point2 + point3) / 3.0f;
			Vector3 normal = glm::normalize(glm::cross(point2 - point1, point3 - point1));
			float planeD = -(normal.x * center.x + normal.y * center.y + normal.z * center.z);

			Vector4 plane = Vector4(normal, planeD);
			Vector4 contactPoint = Vector4(collidingEntity.getComponent<TransformComponent>().position, 1);

			float distance = glm::dot(plane, contactPoint);
			float penetration = 1 - distance;
			Vector3 dir = glm::normalize(Vector3(contactPoint) - center);

			Vector3 a = glm::cross(point2 - point1, point3 - point1);
			Vector3 b = collidingEntity.getComponent<TransformComponent>().position - point1;

			float e = glm::dot(glm::cross(point2 - point1, b), a) / glm::dot(a, a);
			float f = glm::dot(glm::cross(b, point3 - point1), a) / glm::dot(a, a);
			float h = 1 - (e - f);

			if (((0 <= h) && (h <= 1) &&
				(0 <= f) && (f <= 1) &&
				(0 <= e) && (e <= 1))
				)
			{
				if (abs(distance) < 1)
				{
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(tri.entityA, collidingEntity, 0.8f, -normal, penetration);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(tri.entityB, collidingEntity, 0.8f, -normal, penetration);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(tri.entityC, collidingEntity, 0.8f, -normal, penetration);
				}
			}
		}
	}
}
