#include "CollisionSystem.h"
#include "../../Engine/MapLoader/MapLoader.hpp"
#include "../../Engine/Physics/SAT.hpp"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/CollisionComponent.h"

CollisionSystem::CollisionSystem(ECSManager *ECSManager)
	: System(ECSManager, ComponentTypeEnum::COLLISION, ComponentTypeEnum::MOVEMENT, ComponentTypeEnum::POSITION) {

}


void CollisionSystem::update(float dt) {

	for (auto& e : m_entities) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		MovementComponent* m = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));
		CollisionComponent* c = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));

		//update position of shape
		c->m_shape.moveShape(glm::vec2(p->m_position.x, p->m_position.y));

		// Assuming that a map tile is 1x1 and map starts at 0,0
		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if (x == 0 && y == 0) {
					continue; // Don't do anything for the tile the player is in
				}

				int mapTileX = floor(p->m_position.x) + x;
				int mapTileY = floor(p->m_position.y) + y;
				if (!MapLoader::mapInstance->allowMovement(mapTileX, (int)MapLoader::mapInstance->getHeight() - 1 - mapTileY)) {
					// Movement not allowed, does the player overlap?

					Shape tileShape;
					//No need to add normals in this case since they will be the same as for player shape (both are aabb's for now)
					// TODO: Change this when implementign rotations of player shape.
					tileShape.addVertex(glm::vec2(mapTileX, mapTileY));
					tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
					tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
					tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY + 1.0f));

					glm::vec2 tempIntersectionAxis(0.0f);
					float tempIntersectionDepth = 0.0f;

					if (SAT::getIntersection(c->m_shape, tileShape, tempIntersectionAxis, tempIntersectionDepth)) {
						if (glm::length2(tempIntersectionAxis) > 0.0001f) {
							p->m_position += glm::vec3(tempIntersectionAxis.x, tempIntersectionAxis.y, 0.0f) * tempIntersectionDepth;
							glm::vec3 normalizedIntersectionAxis = { glm::normalize(tempIntersectionAxis).x, glm::normalize(tempIntersectionAxis).y, 0.0f };
							m->m_velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m->m_velocity);
						}
					}
				}
			}
		}
	}

}