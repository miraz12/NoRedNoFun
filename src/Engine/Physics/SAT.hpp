#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

#include "Shape.hpp"

namespace SAT {

    float getOverlap(const glm::vec2 &overlapVector, const std::vector<glm::vec2> &shapeAVertices, const std::vector<glm::vec2> &shapeBVertices, bool &reverse) {
        float maxA = -INFINITY;
        float minA = INFINITY;
        float maxB = -INFINITY;
        float minB = INFINITY;

        for (unsigned int i = 0; i < shapeAVertices.size(); i++) {
            float dot = glm::dot(overlapVector, shapeAVertices[i]);
            if (dot < minA) {
                minA = dot;
            }
            if (dot > maxA) {
                maxA = dot;
            }
        }

        for (unsigned int i = 0; i < shapeBVertices.size(); i++) {
            float dot = glm::dot(overlapVector, shapeBVertices[i]);
            if (dot < minB) {
                minB = dot;
            }
            if (dot > maxB) {
                maxB = dot;
            }
        }

        float overlap1 = maxB - minA;
        float overlap2 = maxA - minB;
        if (overlap1 >= 0.0f && overlap2 >= 0.0f) {
            if (overlap1 > overlap2) {
                reverse = true;
                return overlap2;
            }
            else {
                reverse = false;
                return overlap1;
            }
        }

        return -1.0f;
    }

    bool getIntersection(const Shape &shapeA, const Shape &shapeB, glm::vec2 &intersectionAxis, float &intersectionDepth) {
        intersectionDepth = INFINITY;

        auto shapeAVertices = shapeA.getVertices();
        auto shapeBVertices = shapeB.getVertices();

        const std::vector<glm::vec2> &shapeANormals = shapeA.getNormals();
        for (unsigned int i = 0; i < shapeANormals.size(); i++) {
            bool reverse = false;
            float overlap = getOverlap(shapeANormals[i], shapeAVertices, shapeBVertices, reverse);

            if (overlap < 0.0f) {
                return false;
            }

            if (overlap < intersectionDepth) {
                intersectionDepth = overlap;
                intersectionAxis = shapeANormals[i] - shapeANormals[i] * 2.0f * (float) reverse;
            }
        }

        const std::vector<glm::vec2> &shapeBNormals = shapeB.getNormals();
        for (unsigned int i = 0; i < shapeBNormals.size(); i++) {
            bool reverse = false;
            float overlap = getOverlap(shapeBNormals[i], shapeAVertices, shapeBVertices, reverse);

            if (overlap < 0.0f) {
                return false;
            }

            if (overlap < intersectionDepth) {
                intersectionDepth = overlap;
                intersectionAxis = shapeBNormals[i] - shapeBNormals[i] * 2.0f * (float) reverse;
            }
        }
        return true;
    }

}
