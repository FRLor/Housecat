#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"
#include "../components/DamageAreaComponent.h"

#include "../events/CollisionEvent.h"

class DamageSystem : public System {
public:
	DamageSystem() {
		RequireComponent<BoxColliderComponent>();
	}

	void ListenToEvents(std::unique_ptr<EventManager>& eventManager) {
		eventManager->ListenToEvent<CollisionEvent>(this, &DamageSystem::HandleCollision);
	}

	void HandleCollision(CollisionEvent& event) {
		Entity a = event.a;
		Entity b = event.b;

		Logger::Debug("Collision!");
		
		if (a.HasGroup("hazards") || a.HasGroup("enemy") && b.HasTag("player")) {
			EntityOnDamageArea(a, b);
		}
		if (b.HasGroup("hazards") || b.HasGroup("enemy") && a.HasTag("player")) {
			EntityOnDamageArea(b, a);
		}

		//REMIND
		//player attacks enemy?
		/*if (a.HasGroup("player") && b.HasGroup("enemy")) {

		}
		if (b.HasGroup("player") && a.HasGroup("enemy")) {

		}*/

	}

	void EntityOnDamageArea(Entity area, Entity entity) {
		const auto damageArea = area.GetComponent<DamageAreaComponent>();

		if (!damageArea.isFriendly) {
			//reduce health of entity
			auto& health = entity.GetComponent<HealthComponent>();
			health.healthPercent -= damageArea.hitPercentDamage;

			if (health.healthPercent <= 0) {
				entity.Kill();
			}
		}
	}

	void Update() {

	}
};