#include "GraphicsSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/GraphicsComponent.hpp"


#include <glad/glad.h>
#include <iostream>

GraphicsSystem::GraphicsSystem(ECSManager * ECSManager) :
    System(ECSManager, ComponentTypeEnum::POSITION, ComponentTypeEnum::GRAPHICS),
    m_quadManager(m_instancedShaderProgram),
    m_screenQuad(m_screenShaderProgram),
    m_mapLoader(m_simpleShaderProgram, "resources/Maps/simple.map") {
    initGL();
}

void GraphicsSystem::update(float /*dt*/) {
	for (auto& e : m_entities) {
		PositionComponent *p = static_cast<PositionComponent *>(e->getComponent(ComponentTypeEnum::POSITION));
		GraphicsComponent *g = static_cast<GraphicsComponent*>(e->getComponent(ComponentTypeEnum::GRAPHICS));

        g->quad->getModelMatrix() = p->calculateMatrix();
	}

    draw();
}

void GraphicsSystem::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_simpleShaderProgram.use();
    m_camera.bindViewMatrix(m_simpleShaderProgram.getUniformLocation("viewMatrix"));
    m_mapLoader.draw();
    glEnable(GL_DEPTH_TEST);
    m_instancedShaderProgram.use();
	m_camera.bindViewMatrix(m_instancedShaderProgram.getUniformLocation("viewMatrix"));
	m_quadManager.draw();
}

void GraphicsSystem::initGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // Back-face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

//     glEnable(GL_LINE_SMOOTH); // Line antialiasing
    glLineWidth(3.0f); // Sets line width of things like wireframe and draw lines
    glPointSize(3.0f);
}
