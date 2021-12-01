#include "CollisionSystem.hpp"
#include "Physics/SAT.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/ECSManager.hpp"



CollisionSystem::CollisionSystem(ECSManager *ECSManager)
	: System(ECSManager, ComponentTypeEnum::COLLISION, ComponentTypeEnum::MOVEMENT, ComponentTypeEnum::POSITION) {

}


void CollisionSystem::update(float /*dt*/) {
	
	// Update position of shapes
	for (auto& e : m_entities) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		CollisionComponent* c = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));

		c->shape.setTransformMatrix(p->calculateMatrix());
		c->currentCollisionEntities.clear(); // Clear current collisions
	}


	for (auto& e : m_entities) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		CollisionComponent* c = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));
		MovementComponent* m = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));

		// Collide with other entities
		for (auto& e2 : m_entities) {
			if (e->getID() == e2->getID()) {
				continue;
			}

			CollisionComponent* c2 = static_cast<CollisionComponent*>(e2->getComponent(ComponentTypeEnum::COLLISION));

			glm::vec2 tempIntersectionAxis(0.0f);
			float tempIntersectionDepth = 0.0f;

			if (SAT::getIntersection(c->shape, c2->shape, tempIntersectionAxis, tempIntersectionDepth)) {
				if (c2->effectMovement) {
					if (glm::length2(tempIntersectionAxis) > 0.0001f) {
						p->position += glm::vec3(tempIntersectionAxis, 0.0f)  * tempIntersectionDepth;
						glm::vec3 normalizedIntersectionAxis = {glm::normalize(tempIntersectionAxis), 0.0f};
						m->velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m->velocity);

						// Update shape
						c->shape.setTransformMatrix(p->calculateMatrix());
					}
				}
				c->currentCollisionEntities.emplace_back(e2); // Save collision
			}
		}

		collideWithMap(e);
	}
}

void CollisionSystem::collideWithMap(Entity *e) {
	PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
	MovementComponent* m = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));
	CollisionComponent* c = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));

    // Assuming that a map tile is 1x1 and map starts at 0,0
	Shape tileShape;
	tileShape.addNormal(glm::vec2(1.0f, 0.0f));
	tileShape.addNormal(glm::vec2(0.0f, 1.0f));
	
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (x == 0 && y == 0) {
				continue; // Don't do anything for the tile the player is in
			}

			int mapTileX = (int) floor(p->position.x) + x;
			int mapTileY = (int) floor(p->position.y) + y;
			if (!ECSManager::getInstance().getGraphicsSystem()->getMapLoader()->allowMovement(mapTileX, (int)ECSManager::getInstance().getGraphicsSystem()->getMapLoader()->getHeight() - 1 - mapTileY)) {
				// Movement not allowed, does the player overlap?
				tileShape.clearVertices();
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY + 1.0f));

				glm::vec2 tempIntersectionAxis(0.0f);
				float tempIntersectionDepth = 0.0f;

				if (SAT::getIntersection(c->shape, tileShape, tempIntersectionAxis, tempIntersectionDepth)) {
					if (glm::length2(tempIntersectionAxis) > 0.0001f) {
						p->position += glm::vec3(tempIntersectionAxis, 0.0f)  * tempIntersectionDepth;
						glm::vec3 normalizedIntersectionAxis = {glm::normalize(tempIntersectionAxis), 0.0f};
						m->velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m->velocity);

						// Update shape
						c->shape.setTransformMatrix(p->calculateMatrix());
					}
					c->currentCollisionEntities.emplace_back(nullptr);
				}
			}
		}
	}
}