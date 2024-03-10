#pragma once

#include <algorithm>

#include "../ecs/ECS.h"

#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

class MovementSystem: public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void Update(double deltaTime) {
		for (auto entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += static_cast<float>(rigidbody.velocity.x * deltaTime);
			transform.position.y += static_cast<float>(rigidbody.velocity.y * deltaTime);

			//new movement based on vel * dT * scale (non uniform scaling movement?)
			//float dX = static_cast<float>(rigidbody.velocity.x * deltaTime * transform.scale.x);
			//float dY = static_cast<float>(rigidbody.velocity.y * deltaTime * transform.scale.y);
			// Update position
			//transform.position.x += dX;
			//transform.position.y += dY;

			//prevent player form moving outside map
			if (entity.HasTag("player")) {
				//adjust padding for map (-5 on edge)
				int paddingLeft = -5;
				int paddingRight = -5;
				int paddingTop = -5;
				int paddingBottom = -5;

				paddingLeft *= transform.scale.x;
				paddingRight *= transform.scale.x;
				paddingTop *= transform.scale.y;
				paddingBottom *= transform.scale.y;

				//update position within boundaries
				transform.position.x = std::max(static_cast<float>(paddingLeft), std::min(transform.position.x, static_cast<float>(Game::mapWidth - paddingRight)));
				transform.position.y = std::max(static_cast<float>(paddingTop), std::min(transform.position.y, static_cast<float>(Game::mapHeight - paddingBottom)));
			}
		
			//checks if outside the map boundaries, buffer margin forgives 200 px W/H
			int cullingMargin = 200;
			bool isEntityOutsideMap = (
				transform.position.x > Game::mapWidth + cullingMargin ||
				transform.position.x < -cullingMargin ||
				transform.position.y > Game::mapHeight + cullingMargin ||
				transform.position.y < -cullingMargin 
			);

			if (!entity.HasTag("player") && isEntityOutsideMap ) {
				entity.Kill();
			}
		}
	}

};

