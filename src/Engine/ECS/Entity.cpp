#include "Entity.hpp"

Entity::Entity(int ID)
: m_ID(ID), m_playable(false), m_name("none"), m_components(){
}

//Dont know if this is the correct way to free components
Entity::~Entity() {
    for (unsigned int i = 0; i < m_components.size(); i++) {
        delete m_components[i];
    }
    m_components.clear();
}

const int Entity::getID()
{
    return m_ID;
}

bool Entity::addComponent(Component* component) {
    if (!hasComponent(component->getComponentType())) {
        m_components.push_back(component);
        return true;
    }
    return false;
}

bool Entity::hasComponent(ComponentTypeEnum type){
    for (auto& c : m_components) {
        if (c->getComponentType() == type) {
            return true;
        }
    }
    return false;
}

void Entity::removeComponent(ComponentTypeEnum removeComponent)
{
    for (unsigned int i = 0; i < m_components.size(); i++) {
        if (m_components[i]->getComponentType() == removeComponent) {
            delete m_components[i];
            m_components.erase(m_components.begin() + i);
            return;
        }
    }
}

Component* Entity::getComponent(ComponentTypeEnum type) {
    for (auto* c : m_components) {
        if ((c != nullptr) && c->getComponentType() == type) {
            return c;
        }
    }

    return nullptr;
}
