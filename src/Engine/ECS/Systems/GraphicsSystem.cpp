#include "GraphicsSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/GraphicsComponent.hpp"

#include "Rendering.hpp"

#include <glad/glad.h>
#include <iostream>

GraphicsSystem::GraphicsSystem(ECSManager * ECSManager) :
    m_quadManager(m_instancedShaderProgram),
    m_screenQuad(m_screenShaderProgram),
    m_mapLoader(m_simpleShaderProgram, "resources/Maps/simple.map"),
    System(ECSManager, ComponentTypeEnum::POSITION, ComponentTypeEnum::GRAPHICS){
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

void GraphicsSystem::init(unsigned int width, unsigned int height) {
    m_width = width; 
    m_height = height;

    // Framebuffer
    glGenFramebuffers(static_cast<int>(m_fbos.size()), m_fbos.data());
    glGenTextures(static_cast<int>(m_colTexs.size()), m_colTexs.data());
    glGenRenderbuffers(static_cast<int>(m_rbos.size()), m_rbos.data());

    for(unsigned int i = 0; i < m_fbos.size(); ++i) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbos[i]);
        glBindTexture(GL_TEXTURE_2D, m_colTexs[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colTexs[i], 0);

        glBindRenderbuffer(GL_RENDERBUFFER, m_rbos[i]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); 
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbos[i]); 

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_screenQuad.setTexture(m_colTexs[1]);
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

void GraphicsSystem::reInit(unsigned int width, unsigned int height) {
    m_width = width; 
    m_height = height;

    glDeleteFramebuffers(static_cast<int>(m_fbos.size()), m_fbos.data());
    glGenFramebuffers(static_cast<int>(m_fbos.size()), m_fbos.data());

    for(unsigned int i = 0; i < m_fbos.size(); ++i) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbos[i]);
        glBindTexture(GL_TEXTURE_2D, m_colTexs[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colTexs[i], 0);

        glBindRenderbuffer(GL_RENDERBUFFER, m_rbos[i]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); 
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbos[i]); 

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}



