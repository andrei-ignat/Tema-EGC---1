#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateTrapezoid(const std::string& name, glm::vec3 corner, float bottomLength, float topLength, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, float amplitude, float frequency, float amplitude1, float frequency1, glm::vec3 color, std::vector<float>& heightMap);
    Mesh* CreateTrapezoid1(const std::string& name, glm::vec3 corner, float bottomLength, float topLength, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateDoubleTrapezoid2(const std::string& name, glm::vec3 center, float bottomLength1, float topLength1, float height1, glm::vec3 color1, float bottomLength2, float topLength2, float height2, glm::vec3 color2, float rotationAngle);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, int numSegments);
    Mesh* UpdateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, const std::vector<float>& heightMap, glm::vec3 color);
    Mesh* CreateLine(const std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float height1, float top1, glm::vec3 color);
}