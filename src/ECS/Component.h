#pragma once

//enum class containing all types of components. Add new enum if new component type is created
enum class ComponentTypeEnum {
	INPUT,
	PHYSICS,
	GRAPHICS
};

//Basic component interface which all other components implement
class Component {

public:

	virtual void update() = 0;

	virtual void getComponentType() = 0;
private:

	ComponentTypeEnum m_componentType;
};
