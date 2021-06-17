#pragma once

#include "../Rendering/Rendering.hpp"
#include "../Rendering/Objects/Quad.hpp"

class Game {
public:
	Game(Rendering &rendering);
	~Game();

	void update(float dt);
private:
	Rendering& m_rendering;
	Quad* m_testQuad;
};