#pragma once

#include "../ecs/ECS.h"

#include "../eventmanager/EventManager.h"

#include "../components/BoxColliderComponent.h"

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
		Logger::Debug("Collided!");
		event.a.Kill();
	}

	void Update() {

	}
};