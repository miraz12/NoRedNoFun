#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

#include "Shape.hpp"

namespace SAT {

    inline float getOverlap(const glm::vec2 &overlapVector, const std::vector<glm::vec2> &shapeAVertices, const std::vector<glm::vec2> &shapeBVertices, bool &reverse) {
        float maxA = glm::dot(overlapVector, shapeAVertices[0]);
        float minA = maxA;
        float maxB = glm::dot(overlapVector, shapeBVertices[0]);
        float minB = maxB;

        float tempDot = 0.0f;

        for (unsigned int i = 1; i < shapeAVertices.size(); i++) {
            tempDot = glm::dot(overlapVector, shapeAVertices[i]);
            if (tempDot < minA) {
                minA = tempDot;
            }
            if (tempDot > maxA) {
                maxA = tempDot;
            }
        }

        for (unsigned int i = 1; i < shapeBVertices.size(); i++) {
            tempDot =  glm::dot(overlapVector, shapeBVertices[i]);
            if (tempDot < minB) {
                minB = tempDot;
            }
            if (tempDot > maxB) {
                maxB = tempDot;
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

    inline void calculateIntersectionPoint(const glm::vec2 &intersectionLine, 
        const std::vector<glm::vec2> &shapeAVertices, 
        const std::vector<glm::vec2> &shapeBVertices, 
        const std::vector<unsigned int> &shapeAIndices, 
        const std::vector<unsigned int> &shapeBIndices, 
        glm::vec2 &intersectionPoint) 
    { 
        float maxA = glm::dot(intersectionLine, shapeAVertices[shapeAIndices[0]]);
        unsigned int maxAIndex = shapeAIndices[0];
        float minA = maxA;
        unsigned int minAIndex = maxAIndex;
        float maxB = glm::dot(intersectionLine, shapeBVertices[shapeBIndices[0]]);
        unsigned int maxBIndex = shapeBIndices[0];
        float minB = maxB;
        unsigned int minBIndex = maxBIndex;

        float tempDot = 0.0f;

        for (unsigned int i = 1; i < shapeAIndices.size(); i++) {
            tempDot = glm::dot(intersectionLine, shapeAVertices[shapeAIndices[i]]);
            if (tempDot < minA) {
                minA = tempDot;
                minAIndex = shapeAIndices[i];
            }
            if (tempDot > maxA) {
                maxA = tempDot;
                maxAIndex = shapeAIndices[i];
            }
        }

        for (unsigned int i = 1; i < shapeBIndices.size(); i++) {
            tempDot =  glm::dot(intersectionLine, shapeBVertices[shapeBIndices[i]]);
            if (tempDot < minB) {
                minB = tempDot;
                minBIndex = shapeBIndices[i];
            }
            if (tempDot > maxB) {
                maxB = tempDot;
                maxBIndex = shapeBIndices[i];
            }
        }
            
        if (maxA > maxB && minA < minB) { // B interval is completely inside A interval, use middle of A interval
            intersectionPoint = (shapeBVertices[maxBIndex] + shapeBVertices[minBIndex]) * 0.5f; 
        }
        else if (maxB > maxA && minB < minA) { // A interval is completely inside B interval, use middle of A interval
            intersectionPoint = (shapeAVertices[maxAIndex] + shapeAVertices[minAIndex]) * 0.5f; 
        }
        else if (maxA - minB < maxB - minA) { // max A and min B is the overlap, calculate middle of overlap
            intersectionPoint = (shapeAVertices[maxAIndex] + shapeBVertices[minBIndex]) * 0.5f; 
        }
        else { // max B and min A is the overlap, calculate middle of overlap
            intersectionPoint = (shapeAVertices[minAIndex] + shapeBVertices[maxBIndex]) * 0.5f; 
        }
    }
	
	inline bool getIntersection(Shape &shapeA, Shape &shapeB, glm::vec2 &intersectionAxis, float &intersectionDepth) {
        intersectionDepth = INFINITY;

        auto shapeAVertices = shapeA.getTransformedVertices();
        auto shapeBVertices = shapeB.getTransformedVertices();

        auto shapeANormals = shapeA.getTransformedNormals();
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

        auto shapeBNormals = shapeB.getTransformedNormals();
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

    inline bool getIntersection(Shape &shapeA, Shape &shapeB, glm::vec2 &intersectionAxis, float &intersectionDepth, glm::vec2 &intersectionPoint) {
        intersectionDepth = INFINITY;

        auto shapeAVertices = shapeA.getTransformedVertices();
        auto shapeBVertices = shapeB.getTransformedVertices();

        auto shapeANormals = shapeA.getTransformedNormals();
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

        auto shapeBNormals = shapeB.getTransformedNormals();
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

        // Intersection occured, find out intersection point
        std::vector<unsigned int> shapeAIntersectionPointIndices;
        std::vector<unsigned int> shapeBIntersectionPointIndices;
        // Vector is always pointing from B to A so only have to keep track of max projection for B and min projection for A
        float minA = glm::dot(shapeAVertices[0], intersectionAxis);
        shapeAIntersectionPointIndices.emplace_back(0);

        float maxB = glm::dot(shapeBVertices[0], intersectionAxis);
        shapeBIntersectionPointIndices.emplace_back(0);
        
        float tempDot = 0.0f;

        // Find for A
        for (unsigned int i = 1; i < shapeAVertices.size(); i++) {
            tempDot = glm::dot(shapeAVertices[i], intersectionAxis);
            if (tempDot < minA - 0.00001f) {
                minA = tempDot;
                shapeAIntersectionPointIndices.clear();
                shapeAIntersectionPointIndices.emplace_back(i);
            } else if (tempDot <= minA) {
                shapeAIntersectionPointIndices.emplace_back(i);
            }
        }

        // Find for B
        for (unsigned int i = 1; i < shapeBVertices.size(); i++) {
            tempDot = glm::dot(shapeBVertices[i], intersectionAxis);
            if (tempDot > maxB + 0.00001f) {
                maxB = tempDot;
                shapeBIntersectionPointIndices.clear();
                shapeBIntersectionPointIndices.emplace_back(i);
            } else if (tempDot >= maxB) {
                shapeBIntersectionPointIndices.emplace_back(i);
            }
        }

        // Calculate intersection point
        if (shapeAIntersectionPointIndices.size() == 1) {
            intersectionPoint = shapeAVertices[shapeAIntersectionPointIndices[0]];
        }
        else if (shapeBIntersectionPointIndices.size() == 1) {
            intersectionPoint = shapeBVertices[shapeBIntersectionPointIndices[0]];
        }
        else {
            glm::vec2 intersectionLine = glm::vec2(intersectionAxis.y, -intersectionAxis.x); // Rotated intersection axis 90 degrees
            calculateIntersectionPoint(intersectionLine, shapeAVertices, shapeBVertices, shapeAIntersectionPointIndices, shapeBIntersectionPointIndices, intersectionPoint);
        }

        return true;
    }

    inline bool getRaycastOverlap(const glm::vec2& testVec, const std::vector<glm::vec2>& vertices, const glm::vec2& rayStart, const glm::vec2& rayDir, float& timeFirst, float& timeLast, const float timeMax) {
		float min1 = INFINITY, min2 = INFINITY;
		float max1 = -INFINITY, max2 = -INFINITY;

		float tempDot;

		for (const auto& vert : vertices) {
			tempDot = dot(vert, testVec);

			if (tempDot < min1) {
				min1 = tempDot;
			}
			if (tempDot > max1) {
				max1 = tempDot;
			}
		}

        tempDot = dot(rayStart, testVec);

        if (tempDot < min2) {
            min2 = tempDot;
        }
        if (tempDot > max2) {
            max2 = tempDot;
        }

		float T;
		float speed = dot(testVec, rayDir);

		if (max2 < min1) { // Interval (2) initially on left of interval (1)
			if (speed <= 0.f) { return false; } // Intervals moving apart

			T = (min1 - max2) / speed;
			if (T > timeFirst) { timeFirst = T; }
			if (timeFirst > timeMax) { return false; } // Early exit

			T = (max1 - min2) / speed;
			if (T < timeLast) { timeLast = T; }
			if (timeFirst > timeLast) { return false; } // Early exit
		}
		else  if (max1 < min2) { // Interval (2) initially on right of interval (1)
			if (speed >= 0.f) { return false; } // Intervals moving apart

			T = (max1 - min2) / speed;
			if (T > timeFirst) { timeFirst = T; }
			if (timeFirst > timeMax) { return false; } // Early exit

			T = (min1 - max2) / speed;
			if (T < timeLast) { timeLast = T; }
			if (timeFirst > timeLast) { return false; } // Early exit
		}
		else { // Interval (1) and interval (2) overlap
			if (speed > 0.f) {
				T = (max1 - min2) / speed;
				if (T < timeLast) { timeLast = T; }
				if (timeFirst > timeLast) { return false; } // Early exit
			}
			else if (speed < 0.f) {
				T = (min1 - max2) / speed;
				if (T < timeLast) { timeLast = T; }
				if (timeFirst > timeLast) { return false; } // Early exit
			}
		}

		return true;
	}

    inline float getRaycastIntersection(const glm::vec2& rayStart, const glm::vec2& rayDir, Shape& shape, const float maxDist) {
        float timeFirst = 0.f;
		float timeLast = INFINITY;

		const std::vector<glm::vec2>& s1Norms = shape.getTransformedNormals();
		for (const auto& it : s1Norms) {
			if (!getRaycastOverlap(it, shape.getTransformedVertices(), rayStart, glm::normalize(rayDir), timeFirst, timeLast, maxDist)) {
				return -1.0f;
			}
		}

		return timeFirst;
    }

}
