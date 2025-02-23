#include "object2D.h"

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


Mesh* object2D::CreateRectangle(const std::string& name, glm::vec3 center, float height1, float top1, glm::vec3 color) {

    glm::vec3 rectangle = center;
    glm::vec3 rectangle1 = center + glm::vec3(top1, 0, 0);
    glm::vec3 rectangle2 = center + glm::vec3(0, height1, 0);
    glm::vec3 rectangle3 = center + glm::vec3(top1, height1, 0);

    std::vector<VertexFormat> vertices = {
    VertexFormat(rectangle, color),  // v0
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
Mesh* object2D::CreateDoubleTrapezoid2(const std::string& name, glm::vec3 center, float bottomLength1, float topLength1, float height1, glm::vec3 color1, float bottomLength2, float topLength2, float height2, glm::vec3 color2, float rotationAngle) {

    float halfBottomLength1 = bottomLength1 / 2.0f;
    float halfTopLength1 = topLength1 / 2.0f;

    // Define trapezoid vertices
    glm::vec3 bottomLeft1 = center + glm::vec3(-halfTopLength1, 0, 0); // v0
    glm::vec3 bottomRight1 = center + glm::vec3(halfTopLength1, 0, 0); // v1
    glm::vec3 topLeft1 = center + glm::vec3(-halfBottomLength1, height2, 0); // v2
    glm::vec3 topRight1 = center + glm::vec3(halfBottomLength1, height2, 0); // v3

    glm::vec3 bottomLeft2 = center + glm::vec3(-halfBottomLength1, height2, 0); // v4
    glm::vec3 bottomRight2 = center + glm::vec3(halfBottomLength1, height2, 0); // v5
    glm::vec3 topLeft2 = center + glm::vec3(-halfTopLength1,  2 * height1 - height2, 0); // v6
    glm::vec3 topRight2 = center + glm::vec3(halfTopLength1,  2 * height1 - height2, 0); // v7

    glm::vec3 rectangle1_1 = RotatePoint(center + glm::vec3(-halfBottomLength1 / 4, 2 * height1 - height2, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle); //v8
    glm::vec3 rectangle1_2 = RotatePoint(center + glm::vec3(halfBottomLength1 / 4, 2 * height1 - height2, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle); //v9
    glm::vec3 rectangle1_3 = RotatePoint(center + glm::vec3(-halfBottomLength1 / 4, 3 * height1 -height2, 0), center + glm::vec3(0, 2 * height1 - height2, 0), rotationAngle);  //v10
    glm::vec3 rectangle1_4 = RotatePoint(center + glm::vec3(halfBottomLength1 / 4, 3 * height1 - height2, 0), center + glm::vec3(0,  2 * height1 - height2, 0), rotationAngle); //v11

    // Define vertices for the semicircle
    std::vector<VertexFormat> vertices = {
        VertexFormat(bottomLeft1, color1),  // v0
        VertexFormat(bottomRight1, color1), // v1
        VertexFormat(topRight1, color1),    // v2
        VertexFormat(topLeft1, color1),     // v3
        VertexFormat(bottomLeft2, color2),  // v4
        VertexFormat(bottomRight2, color2), // v5
        VertexFormat(topRight2, color2),    // v6
        VertexFormat(topLeft2, color2),     // v7
    };



    // Create semicircle vertices
    int numSegments = 100; // Number of segments for the semicircle
    glm::vec3 semicircleCenter = center + glm::vec3(0, 2 * height1 - height2, 0); // Center of semicircle
    float radius = 20; // Radius of the semicircle

    vertices.push_back(VertexFormat(semicircleCenter, color1)); // Center vertex of the semicircle



    for (int i = 0; i <= numSegments; ++i) {
        float theta = (M_PI * i) / numSegments; // Angle for each segment
        float x = radius * cos(theta);
        float y = radius * sin(theta);

        // Add the vertex for the semicircle
        vertices.push_back(VertexFormat(semicircleCenter + glm::vec3(x, y, 0), color1));
    }

    vertices.push_back(VertexFormat(rectangle1_1, color2));
    vertices.push_back(VertexFormat(rectangle1_2, color2));
    vertices.push_back(VertexFormat(rectangle1_3, color2));
    vertices.push_back(VertexFormat(rectangle1_4, color2));

    // Define indices for the trapezoids
    std::vector<unsigned int> indices = {
        0, 1, 2, // First triangle (v0, v1, v2) - first trapezoid
        2, 3, 0, // Second triangle (v2, v3, v0) - first trapezoid
        4, 5, 6, // First triangle (v4, v5, v6) - second trapezoid
        6, 7, 4
    };

    // Create indices for the semicircle (fan)
    for (int i = 9; i <= numSegments + 8; ++i) {
        indices.push_back(8); // Center vertex
        indices.push_back(i); // Current vertex
        indices.push_back(i + 1); // Next vertex (wrap around)
    }

    indices.push_back(110);
    indices.push_back(112);
    indices.push_back(113);
    indices.push_back(110);
    indices.push_back(113);
    indices.push_back(111);



    // Create the mesh for the trapezoids and semicircle
    Mesh* trapezoid = new Mesh(name);
    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}



Mesh* object2D::CreateTrapezoid(const std::string& name, glm::vec3 corner, float bottomLength, float topLength, float height, glm::vec3 color, bool fill) {
    // Calculăm offset-urile față de centru
    float halfBottomLength = bottomLength / 2.0f;
    float halfTopLength = topLength / 2.0f;

    // Definim cele patru colțuri ale trapezului, centrate pe corner
    glm::vec3 bottomLeft = corner + glm::vec3(-halfBottomLength, 0, 0);         // v0
    glm::vec3 bottomRight = corner + glm::vec3(halfBottomLength, 0, 0);         // v1
    glm::vec3 topLeft = corner + glm::vec3(-halfTopLength, height, 0);          // v2
    glm::vec3 topRight = corner + glm::vec3(halfTopLength, height, 0);          // v3

    // Definim lista de vertecși pentru fiecare colț și culoarea asociată
    std::vector<VertexFormat> vertices = {
        VertexFormat(bottomLeft, color),  // v0
        VertexFormat(bottomRight, color), // v1
        VertexFormat(topRight, color),    // v2
        VertexFormat(topLeft, color)      // v3
    };

    // Definim indicii pentru triunghiuri
    std::vector<unsigned int> indices = {
       0, 1, 2, // Primul triunghi (v0, v1, v2)
       2, 3, 0  // Al doilea triunghi (v2, v3, v0)
    };

    // Creăm obiectul mesh pentru trapez
    Mesh* trapezoid = new Mesh(name);
    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}

Mesh* object2D::CreateTrapezoid1(const std::string& name, glm::vec3 corner, float bottomLength, float topLength, float height, glm::vec3 color, bool fill) {
    float halfBottomLength = bottomLength / 2.0f;
    float halfTopLength = topLength / 2.0f;

    // Definim cele patru colțuri ale trapezului, centrate pe corner
    glm::vec3 bottomLeft = corner + glm::vec3(-halfBottomLength, 0, 0);         // v0
    glm::vec3 bottomRight = corner + glm::vec3(halfBottomLength, 0, 0);         // v1
    glm::vec3 topLeft = corner + glm::vec3(-halfTopLength, height, 0);          // v2
    glm::vec3 topRight = corner + glm::vec3(halfTopLength, height, 0);          // v3


    // Definim lista de vertecși pentru fiecare colț și culoarea asociată
    std::vector<VertexFormat> vertices = {
        VertexFormat(bottomLeft, color),  // v0
        VertexFormat(bottomRight, color), // v1
        VertexFormat(topRight, color),    // v2
        VertexFormat(topLeft, color)      // v3
    };

    // Definim indicii pentru triunghiuri
    std::vector<unsigned int> indices = {
       0, 1, 2, // Primul triunghi (v0, v1, v2)
       2, 3, 0  // Al doilea triunghi (v2, v3, v0)
    };

    // Creăm obiectul mesh pentru trapez
    Mesh* trapezoid1 = new Mesh(name);
    trapezoid1->InitFromData(vertices, indices);
    return trapezoid1;
    
}



Mesh* object2D::UpdateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, const std::vector<float>& heightMap, glm::vec3 color) {
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

Mesh* object2D::CreateSinWaveRectangles(const std::string& name, glm::vec3 corner, float screenWidth, float amplitude, float frequency, float amplitude1, float frequency1, glm::vec3 color, std::vector<float>& heightMap) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Împărțim ecranul în 1000 de părți și calculăm lățimea fiecărui dreptunghi
    int numRectangles = 1000;
    float rectWidth = screenWidth / numRectangles;
    heightMap.clear();

    // Generăm dreptunghiurile în funcție de sinusoidă
    for (int i = 0; i < numRectangles; ++i) {
        float x = corner.x + i * rectWidth;
        float height = amplitude * sin(frequency * x) +  amplitude1 * sin(frequency1 * x) + 245;     // Înălțimea calculată pe baza sinusoidei

        heightMap.push_back(height);

        // Definim vertecșii pentru fiecare dreptunghi
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

    // Cream mesh-ul și setăm modul de desenare la GL_TRIANGLES
    Mesh* sinWaveRectangles = new Mesh(name);
    sinWaveRectangles->SetDrawMode(GL_TRIANGLES);
    sinWaveRectangles->InitFromData(vertices, indices);

    return sinWaveRectangles;
}


Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, int numSegments) {
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

    // Initialize the mesh with vertices and indices
    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateLine(const std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Define the start and end points of the line
    vertices.emplace_back(start, color);
    vertices.emplace_back(end, color);

    // Define the indices for the line segment
    indices.push_back(0); // Start vertex
    indices.push_back(1); // End vertex

    // Create the mesh object
    Mesh* line = new Mesh(name);
    line->SetDrawMode(GL_LINES);  // Set draw mode to lines
    line->InitFromData(vertices, indices);

    return line;
}

