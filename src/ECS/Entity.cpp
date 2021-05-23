#include "Entity.h"

bool Entity::hasComponent(ComponentTypeEnum type){
    for (auto& c : m_components) {
        if (c->getComponentType() == type) {
            return true;
        }
    }
    return false;
}

Component* Entity::getComponent(ComponentTypeEnum type) {
    for (auto& c : m_components) {
        if (c->getComponentType() == type) {
            return c;
        }
    }
}
