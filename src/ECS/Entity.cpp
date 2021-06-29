#include "Entity.h"

Entity::Entity(int ID) {
    m_ID = ID;
}

//Dont know if this is the correct way to free components
Entity::~Entity() {
    for (auto *component : m_components) {
        delete component;
    }
}

void Entity::addComponent(Component* component) {
    if (!hasComponent(component->getComponentType())) {
        m_components.push_back(component);
    }
}

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
