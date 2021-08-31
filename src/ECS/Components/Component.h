#pragma once

//enum class containing all types of components. Add new enum if new component type is created
enum class ComponentTypeEnum {
	POSITION,
	MOVEMENT,
	INPUT,
	COLLISION,
	ACTION, 
	Health,
	Attack,
	DAMAGE
};

//Basic component interface which all other components implement
class Component {

public:

	virtual ComponentTypeEnum getComponentType() {
		return m_componentType;
	}

protected:
	ComponentTypeEnum m_componentType;
};
