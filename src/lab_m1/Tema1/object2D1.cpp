#include "object2D1.h"

#include <vector>
#include <cmath>

#include "core/engine.h"
#include "utils/gl_utils.h"

inline glm::mat3 Rotate(float radians) {
    return glm::transpose(glm::mat3(
        cosf(radians), -sinf(radians), 0,
        sinf(radians), cosf(radians), 0,
        0, 0, 1
    ));
}
glm::vec3 RotatePoint(glm::vec3 point, glm::vec3 pivot, float angle) {

    glm::mat3 rotationMatrix = Rotate(angle);
    glm::vec3 translatedPoint = point - pivot;
    glm::vec3 rotatedPoint = rotationMatrix * translatedPoint;
    return rotatedPoint + pivot;
}


Mesh* object2D1::CreateRectangle(const std::string& name, glm::vec3 center, float height1, float top1, glm::vec3 color) {

    glm::vec3 rectangle = center;
    glm::vec3 rectangle1 = center + glm::vec3(top1, 0, 0);
    glm::vec3 rectangle2 = center + glm::vec3(0, height1, 0);
    glm::vec3 rectangle3 = center + glm::vec3(top1, height1, 0);

    std::vector<VertexFormat> vertices = {
    VertexFormat(rectangle, color),
    VertexFormat(rectangle1, color),
    VertexFormat(rectangle2, color),
    VertexFormat(rectangle3, color)
    };

    std::vector<unsigned int> indices = {
       0, 2, 3,
       0, 3, 1
    };

    Mesh* rectangleX = new Mesh(name);
    rectangleX->InitFromData(vertices, indices);
    return rectangleX;


}
Mesh* object2D1::CreateDoubleTrapezoid2(const std::string& name, glm::vec3 center, float bottomLength1, float topLength1, float height1, glm::vec3 color1, float bottomLength2, float topLength2, float height2, glm::vec3 color2, float rotationAngle,float height3) {

    float halfBottomLength1 = bottomLength1 / 2.0f;
    float halfTopLength1 = topLength1 / 2.0f;


    glm::vec3 bottomLeft1 = center + glm::vec3(-halfTopLength1 * 1.5 - 10, 0, 0);
    glm::vec3 bottomRight1 = center + glm::vec3(halfTopLength1 * 1.5 + 10, 0, 0);
    glm::vec3 topLeft1 = center + glm::vec3(-halfBottomLength1 * 1.5, height3, 0);
    glm::vec3 topRight1 = center + glm::vec3(halfBottomLength1 * 1.5, height3, 0);

    glm::vec3 bottomLeft2 = center + glm::vec3(-halfBottomLength1 * 2, height3, 0);
    glm::vec3 bottomRight2 = center + glm::vec3(halfBottomLength1 * 2, height3, 0);
    glm::vec3 topLeft2 = center + glm::vec3(-halfTopLength1 * 2 - 20 , 2 * height1 - height2, 0);
    glm::vec3 topRight2 = center + glm::vec3(halfTopLength1 * 2 + 20,  2 * height1 - height2, 0);

    glm::vec3 rectangle1_1 = RotatePoint(center + glm::vec3(-halfBottomLength1 / 4, 2 * height1 - height2, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle);
    glm::vec3 rectangle1_2 = RotatePoint(center + glm::vec3(halfBottomLength1 / 4, 2 * height1 - height2, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle);
    glm::vec3 rectangle1_3 = RotatePoint(center + glm::vec3(-halfBottomLength1 / 4, 3 * height1 - height2 + 20, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle);
    glm::vec3 rectangle1_4 = RotatePoint(center + glm::vec3(halfBottomLength1 / 4, 3 * height1 - height2 + 20, 0), center + glm::vec3(0,  2 * height1 - height2, 0), rotationAngle);

  
    std::vector<VertexFormat> vertices = {
        VertexFormat(bottomLeft1, color1),
        VertexFormat(bottomRight1, color1),
        VertexFormat(topRight1, color1),
        VertexFormat(topLeft1, color1),
        VertexFormat(bottomLeft2, color2),
        VertexFormat(bottomRight2, color2),
        VertexFormat(topRight2, color2),
        VertexFormat(topLeft2, color2),
    };


    int numSegments = 100;
    glm::vec3 semicircleCenter = center + glm::vec3(0, 2 * height1 - height2, 0);
    float radius = 20;

    vertices.push_back(VertexFormat(semicircleCenter, color1));



    for (int i = 0; i <= numSegments; ++i) {
        float theta = (M_PI * i) / numSegments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);


        vertices.push_back(VertexFormat(semicircleCenter + glm::vec3(x, y, 0), color1));
    }

    vertices.push_back(VertexFormat(rectangle1_1, glm::vec3(0.0f,0.0f,0.0f)));
    vertices.push_back(VertexFormat(rectangle1_2, glm::vec3(0.0f,0.0f,0.0f)));
    vertices.push_back(VertexFormat(rectangle1_3, glm::vec3(0.0f, 0.0f, 0.0f)));
    vertices.push_back(VertexFormat(rectangle1_4, glm::vec3(0.0f, 0.0f, 0.0f)));


    std::vector<unsigned int> indices = {
        0, 1, 2, 
        2, 3, 0,
        4, 5, 6,
        6, 7, 4
    };


    for (int i = 9; i <= numSegments + 8; ++i) {
        indices.push_back(8);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(110);
    indices.push_back(112);
    indices.push_back(113);
    indices.push_back(110);
    indices.push_back(113);
    indices.push_back(111);

    Mesh* trapezoid = new Mesh(name);
    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}



Mesh* object2D1::UpdateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, const std::vector<float>& heightMap, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int numRectangles = heightMap.size();
    float rectWidth = screenWidth / numRectangles;

    for (int i = 0; i < numRectangles; ++i) {
        float x = corner.x + i * rectWidth;
        float height = heightMap[i];

        glm::vec3 bottomLeft = glm::vec3(x, corner.y, 0);
        glm::vec3 bottomRight = glm::vec3(x + rectWidth, corner.y, 0);
        glm::vec3 topLeft = glm::vec3(x, corner.y + height, 0);
        glm::vec3 topRight = glm::vec3(x + rectWidth, corner.y + height, 0);

        vertices.push_back(VertexFormat(bottomLeft, color));
        vertices.push_back(VertexFormat(bottomRight, color));
        vertices.push_back(VertexFormat(topRight, color));
        vertices.push_back(VertexFormat(topLeft, color));

        unsigned int baseIndex = i * 4;
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    }

    Mesh* updatedSinWaveRectangles = new Mesh(name);
    updatedSinWaveRectangles->SetDrawMode(GL_TRIANGLES);
    updatedSinWaveRectangles->InitFromData(vertices, indices);
    return updatedSinWaveRectangles;
}

Mesh* object2D1::CreateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, float amplitude, float frequency, float amplitude1, float frequency1, glm::vec3 color, std::vector<float>& heightMap) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

  
    int numRectangles = 1000;
    float rectWidth = screenWidth / numRectangles;
    heightMap.clear();

   
    for (int i = 0; i < numRectangles; ++i) {
        float x = corner.x + i * rectWidth;
        float height = amplitude * sin(frequency * x) +  amplitude1 * sin(frequency1 * x) + 245;     // Înălțimea calculată pe baza sinusoidei

        heightMap.push_back(height);

    
        glm::vec3 bottomLeft = glm::vec3(x, corner.y, 0);
        glm::vec3 bottomRight = glm::vec3(x + rectWidth, corner.y, 0);
        glm::vec3 topLeft = glm::vec3(x, corner.y + height, 0);
        glm::vec3 topRight = glm::vec3(x + rectWidth, corner.y + height, 0);

        vertices.push_back(VertexFormat(bottomLeft, color));
        vertices.push_back(VertexFormat(bottomRight, color));
        vertices.push_back(VertexFormat(topRight, color));
        vertices.push_back(VertexFormat(topLeft, color));


        unsigned int baseIndex = i * 4;
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 1);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex);
        indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 3);
    }

   
    Mesh* sinWaveRectangles = new Mesh(name);
    sinWaveRectangles->SetDrawMode(GL_TRIANGLES);
    sinWaveRectangles->InitFromData(vertices, indices);

    return sinWaveRectangles;
}


Mesh* object2D1::CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, int numSegments) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(center, color));


    for (int i = 0; i <= numSegments; ++i) {
        float theta = (2.0f * M_PI * i) / numSegments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);


        vertices.push_back(VertexFormat(center + glm::vec3(x, y, 0), color));
    }

    for (int i = 1; i <= numSegments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

  
    indices.push_back(0);
    indices.push_back(numSegments);
    indices.push_back(1);


    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D1::CreateLine(const std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(start, color);
    vertices.emplace_back(end, color);

    indices.push_back(0);
    indices.push_back(1);

    Mesh* line = new Mesh(name);
    line->SetDrawMode(GL_LINES);
    line->InitFromData(vertices, indices);

    return line;
}

