#include "CollisionSystem.h"
#include "../../Engine/MapLoader/MapLoader.hpp"
#include "../../Engine/Physics/SAT.hpp"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/CollisionComponent.h"

CollisionSystem::CollisionSystem(ECSManager *ECSManager)
	: System(ECSManager, ComponentTypeEnum::COLLISION, ComponentTypeEnum::MOVEMENT, ComponentTypeEnum::POSITION) {

}


void CollisionSystem::update(float /*dt*/) {

	for (auto& e : m_entities) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		CollisionComponent* c = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));

		//update position of shape
		c->shape.setTransformMatrix(p->quad->getModelMatrix());

		collideWithMap(e);
		//Check for entity collisions and add them to e->m_collisionEntities

		// Update matrix after collision (the position changes if the object intersects with a wall)
		p->quad->getModelMatrix() = glm::translate(glm::mat4(1.0f), p->position);
		p->quad->getModelMatrix() = glm::rotate(p->quad->getModelMatrix(), p->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		p->quad->getModelMatrix() = glm::scale(p->quad->getModelMatrix(), p->scale);

		// Also update shape
		c->shape.setTransformMatrix(p->quad->getModelMatrix());
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
			if (!MapLoader::mapInstance->allowMovement(mapTileX, (int)MapLoader::mapInstance->getHeight() - 1 - mapTileY)) {
				// Movement not allowed, does the player overlap?
				tileShape.clearVertices();
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY + 1.0f));

				glm::vec2 tempIntersectionAxis(0.0f);
				float tempIntersectionDepth = 0.0f;
				glm::vec2 intersectionPoint(0.0f);

				if (SAT::getIntersection(c->shape, tileShape, tempIntersectionAxis, tempIntersectionDepth, intersectionPoint)) {
					if (glm::length2(tempIntersectionAxis) > 0.0001f) {
						p->position += glm::vec3(tempIntersectionAxis, 0.0f)  * tempIntersectionDepth;
						glm::vec3 normalizedIntersectionAxis = {glm::normalize(tempIntersectionAxis), 0.0f};
						m->velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m->velocity);
					}
				}
			}
		}
	}
}