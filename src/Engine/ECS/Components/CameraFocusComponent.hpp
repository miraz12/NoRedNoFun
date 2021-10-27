#pragma once
#include "Component.hpp"
#include <glm/glm.hpp>

class CameraFocusComponent: public Component {
public:
	glm::vec2 offset;

	CameraFocusComponent();
private:
};
