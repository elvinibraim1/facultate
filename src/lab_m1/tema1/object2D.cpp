#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <iostream>


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    glm::vec3 colorMiddle,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, colorMiddle),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(length, -length, 0), color),
        VertexFormat(corner + glm::vec3(-length, -length, 0), color),
        VertexFormat(corner + glm::vec3(-length, length, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        square->SetDrawMode(GL_LINE_STRIP);
        indices = { 1, 2, 3, 4, 1};
    }
    else {
        square->SetDrawMode(GL_TRIANGLES);
        indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1};
    }

    square->InitFromData(vertices, indices);
    return square;
}

float radians(int degrees) {
    return (degrees * M_PI) / 180;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color
    )
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {   
        VertexFormat(corner, glm::vec3(1, 1, 1)),
        VertexFormat(corner + glm::vec3(length , 0, 0), color)
    };

    for (int i = 360; i >= 10; i -= 10) {
        vertices.push_back(VertexFormat(corner + glm::vec3(length * cos(radians(i)), length * sin(radians(i)), 0), color));
    }

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1 };

    for (int i = 2; i <= 37; i++)
        indices.push_back(i);
    indices.push_back(1);

    circle->SetDrawMode(GL_TRIANGLE_FAN);

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
        VertexFormat(corner + glm::vec3(0, -length, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 3, 0, 2, 3 };

    if (!fill) {
        triangle->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}
