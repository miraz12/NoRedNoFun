#pragma once

#include "SimpleShaderProgram.hpp"
#include "Pen.hpp"
#include "Quad.hpp"
#include "Canvas.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

    Canvas& getCanvas();
    Pen& getPen();

    void draw();
private:
    SimpleShaderProgram m_shaderProgram;
    Canvas m_canvas;
    Quad m_quad;
    Pen m_pen;

    void initGL();
};
