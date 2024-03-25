#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A-0
        VertexFormat(corner + glm::vec3(-1.0f * size, 1.63f * size, 1) , color1),
        //B-1
        VertexFormat(corner + glm::vec3(1.0f * size, 1.63f * size, 1) , color1),
        //C-2
        VertexFormat(corner + glm::vec3(-1.0f * size, -1.63f * size, 1) , color1),
        //D-3
        VertexFormat(corner + glm::vec3(1.0f * size, -1.63f * size, 1) , color1),
        //E-4
        VertexFormat(corner + glm::vec3(-2.0f * size, 0 * size, 1) , color1),
        //F-5
        VertexFormat(corner + glm::vec3(2.0f * size, 0 * size, 1) , color1),
        //O-6
        VertexFormat(corner + glm::vec3(0 * size, 0 * size, 1) , color1),

        //A-7-g
        VertexFormat(corner + glm::vec3(-0.81f * size, 1.21f * size, 2) , color2),
        //B-8-h
        VertexFormat(corner + glm::vec3(0.81f * size, 1.21f * size, 2) , color2),
        //C-9-i
        VertexFormat(corner + glm::vec3(-0.81f * size, -1.21f * size, 2) , color2),
        //D-10-j
        VertexFormat(corner + glm::vec3(0.81f * size, -1.21f * size, 2) , color2),
        //E-11-k
        VertexFormat(corner + glm::vec3(-1.6f * size, 0 * size, 2) , color2),
        //F-12-l
        VertexFormat(corner + glm::vec3(1.6f * size, 0 * size, 2) , color2),
        //O-13
        VertexFormat(corner + glm::vec3(0 * size, 0 * size, 2) , color2)
    };
    /*{
        //A-0
        VertexFormat(corner + glm::vec3(3.9f * size, 9.75f * size, 0) , color1),
        //B-1
        VertexFormat(corner + glm::vec3(0 * size, 6.2 * size, 0) , color1),
        //C-2
        VertexFormat(corner + glm::vec3(1.25f * size, 1.5f * size ,0) , color1),
        //D-3
        VertexFormat(corner + glm::vec3(6.2f * size, 0.2f* size, 0) , color1),
        //E-4
        VertexFormat(corner + glm::vec3(9.75f * size, 3.50f * size, 0) , color1),
        //F-5
        VertexFormat(corner + glm::vec3(8.7f * size, 8.45f * size, 0) , color1),
        //O-6
        VertexFormat(corner + glm::vec3(4.75f * size, 5.0f * size, 0) , color1),

        //A-7
        VertexFormat(corner + glm::vec3(4.5f * size, 7.8f * size, 1) , color2),
        //B-8
        VertexFormat(corner + glm::vec3(2.0f * size, 5.5f * size, 1) , color2),
        //C-9
        VertexFormat(corner + glm::vec3(2.5f * size, 2.9f * size ,1) , color2),
        //D-10
        VertexFormat(corner + glm::vec3(6.0f * size, 2.0f * size, 1) , color2),
        //E-11
        VertexFormat(corner + glm::vec3(8.0f * size, 4.0f * size, 1) , color2),
        //F-12
        VertexFormat(corner + glm::vec3(7.5f * size, 7.0f * size, 1) , color2),
        //O-13
         VertexFormat(corner + glm::vec3(4.75f * size, 5.0f * size, 1) , color2)

        0, 1, 6,
        1, 2, 6,
        2, 3, 6,
        3, 4, 6,
        4, 5, 6,
        4, 0, 6,

        7, 8, 13,
        8, 9, 13,
        9, 10, 13,
        10, 11, 13,
        11, 12, 13,
        12, 7, 13
    };*/
    std::vector<unsigned int> indices =
    {
      
        0, 1, 6,
        1, 5, 6,
        5, 3, 6,
        3, 2, 6,
        2, 4, 6,
        4, 0, 6,

        7, 8, 13,
        8, 12, 13,
        12, 10, 13,
        10, 9, 13,
        9, 11, 13,
        11, 7, 13

    };

    Mesh* hexagon = new Mesh(name);

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {

        hexagon->SetDrawMode(GL_TRIANGLES);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float lenght,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;


    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(lenght, 0, 0), color),
        VertexFormat(corner + glm::vec3(lenght, lenght, 0), color),
        VertexFormat(corner + glm::vec3(0, lenght, 0) , color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float l,
    float L,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, L, 0), color),
        VertexFormat(corner + glm::vec3(l, L, 0), color),
        VertexFormat(corner + glm::vec3(l, 0, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {

        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    /*std::vector<VertexFormat> vertices =
    {
        //d-0
        VertexFormat(corner + glm::vec3(0 * size, 0 * size, 1) , color),
        //c-1
        VertexFormat(corner + glm::vec3(-0.3f * size, 0 * size, 1) , color),
        //f-2
        VertexFormat(corner + glm::vec3(0.19f * size, 0.36f * size ,1) , color),
        //a-3
        VertexFormat(corner + glm::vec3(-0.5f * size, 0.6f * size, 1) , color),
        //g-4
        VertexFormat(corner + glm::vec3(0.12f * size, 0.6f * size, 1) , color),
        //e-5
        VertexFormat(corner + glm::vec3(0.3f * size, 0 * size, 1) , color),
        //b-6
        VertexFormat(corner + glm::vec3(0.5f * size, 0.6f * size, 1) , color),
        //h-7
        VertexFormat(corner + glm::vec3(-0.12f * size, 0.6f * size, 1) , color),
        //c-8
        VertexFormat(corner + glm::vec3(-0.3f * size, 0 * size, 1) , color)
    };
    std::vector<unsigned int> indices = 
    {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    */
    std::vector<VertexFormat> vertices = 
    {
        //d-0
        VertexFormat(corner + glm::vec3(0 * size, 3.44f * size, 1) , color),
        //c-1
        VertexFormat(corner + glm::vec3(-2.0f * size, -2.83f * size, 1) , color),
        //h-2
        VertexFormat(corner + glm::vec3(1.21f * size, -0.49f * size ,1) , color),
        //a-3
        VertexFormat(corner + glm::vec3(-3.31f * size, 0.96f * size, 1) , color),
        //i-4
        VertexFormat(corner + glm::vec3(0.79f * size, 0.96f * size, 1) , color),
        //e-5
        VertexFormat(corner + glm::vec3(2.0f * size, -2.83f * size, 1) , color),
        //b-6
        VertexFormat(corner + glm::vec3(3.31f * size, 0.96f * size, 1) , color),
        //j-7
        VertexFormat(corner + glm::vec3(-0.79f * size, 0.96f * size, 1) , color),
        //c-8
        VertexFormat(corner + glm::vec3(-2.0f * size, -2.83f * size, 1) , color)

    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    Mesh* star = new Mesh(name);

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        star->SetDrawMode(GL_TRIANGLES);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateCiudat(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //A-0
        VertexFormat(corner + glm::vec3(0 * size, 2.0f * size, 1) , color),
        //B-1
        VertexFormat(corner + glm::vec3(-1.0f * size, 0 * size, 1) , color),
        //C-2
        VertexFormat(corner + glm::vec3(0 * size, -2.0f * size ,1) , color),
        //D-3
        VertexFormat(corner + glm::vec3(1.0f * size, 0 * size, 1) , color),

        //E-4
        VertexFormat(corner + glm::vec3(0.6f * size, 0.4f * size, 1) , color),
        //F-5
        VertexFormat(corner + glm::vec3(0.6f * size, -0.4f * size, 1) , color),
        //G-6
        VertexFormat(corner + glm::vec3(2.61f * size, -0.4f * size, 1) , color),
        //H-7
        VertexFormat(corner + glm::vec3(2.61f * size, 0.4f * size, 1) , color)
    }
    ;
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
        4, 5, 6,
        4, 7, 6
    };

    Mesh* ciudat = new Mesh(name);

    if (!fill) {
        ciudat->SetDrawMode(GL_LINE_LOOP);
    }
    else {

        ciudat->SetDrawMode(GL_TRIANGLES);
    }

    ciudat->InitFromData(vertices, indices);
    return ciudat;
}

Mesh* object2D::CreateProiectil(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //d-0
        VertexFormat(corner + glm::vec3(0 * size, 3.44f * size, 0) , color),
        //c-1
        VertexFormat(corner + glm::vec3(-2.0f * size, -2.83f * size, 0) , color),
        //h-2
        VertexFormat(corner + glm::vec3(1.21f * size, -0.49f * size ,0) , color),
        //a-3
        VertexFormat(corner + glm::vec3(-3.31f * size, 0.96f * size, 0) , color),
        //i-4
        VertexFormat(corner + glm::vec3(0.79f * size, 0.96f * size, 0) , color),
        //e-5
        VertexFormat(corner + glm::vec3(2.0f * size, -2.83f * size, 0) , color),
        //b-6
        VertexFormat(corner + glm::vec3(3.31f * size, 0.96f * size, 0) , color),
        //j-7
        VertexFormat(corner + glm::vec3(-0.79f * size, 0.96f * size, 0) , color),
        //c-8
        VertexFormat(corner + glm::vec3(-2.0f * size, -2.83f * size, 0) , color)

    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    Mesh* proiectil = new Mesh(name);

    if (!fill) {
        proiectil->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        proiectil->SetDrawMode(GL_TRIANGLES);
    }

    proiectil->InitFromData(vertices, indices);
    return proiectil;
}