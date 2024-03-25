#include "lab_m1/Tema1/tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>


#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/transform2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}



void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    n = 7;
    m = 3;
    stea = 10;
    inamic = 20;
    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height
    timpinamic = 0;
    leftSteaDispare = false;
    luat1 = false;
    luat2 = false;
    luat3 = false;
    luat4 = false;
    portocaliu = false;
    albastru = false;
    galben = false;
    mov = false;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    
    timp = rand() % 10;

    for (int i = 0; i < 3; i++) {
        coordx.push_back(rand() % 1280);
        coordy.push_back(rand() % 720);
    };
    for (int i = 0; i < 9; i++) {
        patrate.push_back(-1);
    };
    for (int i = 0; i < 9; i++) {
        disparitie.push_back(-1);
    };


    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0.7, 0.7, 0.7), false);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, 80, glm::vec3(1, 0, 0), true);
    AddMeshToList(square3);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, 60, 380, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);

    Mesh* star = object2D::CreateStar("star", corner, 20, glm::vec3(1.00 , 0.11 , 0.68), true);
    AddMeshToList(star);



    Mesh* ciudatportocaliu = object2D::CreateCiudat("ciudatportocaliu", corner, 18, glm::vec3(0.89 , 0.47 , 0.20), true);
    AddMeshToList(ciudatportocaliu);

    Mesh* starportocaliu = object2D::CreateProiectil("starportocaliu", corner, 5, glm::vec3(0.89, 0.47, 0.20), true);
    AddMeshToList(starportocaliu);

    Mesh* hexagonportocaliu= object2D::CreateHexagon("hexagonportocaliu", corner, 25, glm::vec3(0.89, 0.47, 0.20), glm::vec3(1,1,1), true);
    AddMeshToList(hexagonportocaliu);



    Mesh* ciudatalbastru = object2D::CreateCiudat("ciudatalbastru", corner, 18, glm::vec3(0.30 , 0.30 , 1.00), true);
    AddMeshToList(ciudatalbastru);

    Mesh* staralbastru = object2D::CreateProiectil("staralbastru", corner, 5, glm::vec3(0.30, 0.30, 1.00), true);
    AddMeshToList(staralbastru);

    Mesh* hexagonalbastru = object2D::CreateHexagon("hexagonalbastru", corner, 25, glm::vec3(0.30, 0.30, 1.00), glm::vec3(1,1,1), true);
    AddMeshToList(hexagonalbastru);




    Mesh* ciudatgalben = object2D::CreateCiudat("ciudatgalben", corner, 18, glm::vec3(0.85 , 0.85 , 0.10), true);
    AddMeshToList(ciudatgalben);

    Mesh* stargalben = object2D::CreateProiectil("stargalben", corner, 5, glm::vec3(0.85, 0.85, 0.10), true);
    AddMeshToList(stargalben);

    Mesh* hexagongalben = object2D::CreateHexagon("hexagongalben", corner, 25, glm::vec3(0.85, 0.85, 0.10), glm::vec3(1,1,1), true);
    AddMeshToList(hexagongalben);




    Mesh* ciudatmov = object2D::CreateCiudat("ciudatmov", corner, 18, glm::vec3(0.73 , 0.16 , 0.96), true);
    AddMeshToList(ciudatmov);

    Mesh* starmov = object2D::CreateProiectil("starmov", corner, 5, glm::vec3(0.73, 0.16, 0.96), true);
    AddMeshToList(starmov);

    Mesh* hexagonmov = object2D::CreateHexagon("hexagonmov", corner, 25, glm::vec3(0.73, 0.16, 0.96), glm::vec3(1,1,1), true);
    AddMeshToList(hexagonmov);




    Mesh* star2 = object2D::CreateStar("star2", corner, 5, glm::vec3(0.7, 0.7, 0.7), true);
    AddMeshToList(star2);

}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.1, 0, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

/*void reshape(int width, int height)
{
    //width = width;
    //height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);       // set projection parameters
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);

    glMatrixMode(GL_MODELVIEW);        // set projection parameters
    glLoadIdentity();
}*/


void Tema1::Update(float deltaTimeSeconds)
{
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    float cx = corner.x + squareSide / 2;
    float cy = corner.y + squareSide / 2;
    timpinamic = timpinamic - deltaTimeSeconds*100;
    glm::ivec2 resolution = window->GetResolution();

    translateX += deltaTimeSeconds ;

    //primul patrat de sus + ciudat
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(60, 580);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(50, 50);
    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(-45, -70);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);


    //al doilea patrat de sus + ciudat
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(240, 580);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(50, 50);
    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(-45, -70);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(45, 0);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    //al treilea patrat de sus + ciudat
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 580);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(50, 50);
    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(-45, -70);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(45, 0);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    //al patrulea patrat + ciudat
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 580);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(50, 50);
    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(-45, -70);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(45, 0);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(45, 0);
    RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);

    //patrate viata
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1150, 590);

    for (int i = 0; i < m; i++) {
        modelMatrix *= transform2D::Translate(-110, 0);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    }


    //stele pentru cumparat romburi
    modelMatrix *= transform2D::Translate(-50, -30);
    for (int i = 0; i < n; i++) {
        modelMatrix *= transform2D::Translate(50, 0);
        RenderMesh2D(meshes["star2"], shaders["VertexColor"], modelMatrix);
    };

    //random stuff
   /* modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(80, 400);
    modelMatrix *= transform2D::Translate(cx, cy);
    unghi = unghi - deltaTimeSeconds;
    modelMatrix *= transform2D::Rotate(unghi);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);*/

    
    //partea de jos cu un dreptunghi si 9*patrate
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 10);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 10);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 10);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 10);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(0, 140);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);



    //stele random
    for (int j = 0; j < coordx.size(); j++) {
        modelMatrix = transform2D::Translate(coordx[j], coordy[j]);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }
     
    if (stea >= 30) {
        for (int i = 0 ; i <  3; i++) {
            coordx.push_back(rand() % 1280);
            coordy.push_back(rand() % 720);
        }
        stea = 0;
    }
    else {
        stea = stea + deltaTimeSeconds;
    }

    //inamici
    for (int i = 0; i < inamici.size(); i++) {

        if (inamici[i] == 0) {
            //1300,60
            if (inamici_color[i] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 60);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonportocaliu"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 1) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 60);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonalbastru"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 2) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 60);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagongalben"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 3) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 60);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonmov"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
        if (inamici[i] == 1) {
            //1300,200
            if (inamici_color[i] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 200);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonportocaliu"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 1) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 200);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonalbastru"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 2) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 200);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagongalben"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 3) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 200);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonmov"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
        if (inamici[i] == 2) {
            //1300,340
            if (inamici_color[i] == 0) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 340);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonportocaliu"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 1) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 340);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonalbastru"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 2) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 340);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagongalben"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
            if (inamici_color[i] == 3) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(1300, 340);
                modelMatrix *= transform2D::Translate(timpinamic, 0);
                RenderMesh2D(meshes["hexagonmov"], shaders["VertexColor"], modelMatrix);
                if (timpinamic == 10) m--;
                if (m == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(600, 350);
                    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
    }

    random_time = rand() % 7;

    if (inamic >= 20) {
        int nr_inamici = rand() % 4 + 1;
        for (int i = 0; i < nr_inamici; i++) {
            inamici.push_back(rand() % 3);
            inamici_color.push_back(rand() % 4);
        }
        inamic = 15;
    }
    else {
        
        inamic = inamic + random_time + 1;
    }

    //stele care pleaca din romburi
    if (portocaliu == true) {

    }


    //drag and drop
    if (luat1 == true) {
        what_romb = 1;
        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
    }

    if (luat2 == true) {
        what_romb = 2;
        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
    }

    if (luat3 == true) {
        what_romb = 3;
        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
    }

    if (luat4 == true) {
        what_romb = 4;
        modelMatrix = glm::mat3(1);
        modelMatrix = transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < 9; i++) {
        if ((patrate[i] != -1)) {
            if ((i == 0)) {
                a = 150;
                b = 60;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 1)) {
                a = 150;
                b = 200;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 2)) {
                a = 150;
                b = 340;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 3)) {
                a = 300;
                b = 60;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 4)) {
                a = 300;
                b = 200;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 5)) {
                a = 300;
                b = 340;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 6)) {
                a = 450;
                b = 60;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 7)) {
                a = 450;
                b = 200;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }
            if ((i == 8)) {
                a = 450;
                b = 340;
                if (patrate[i] == 1) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatportocaliu"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 2) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatalbastru"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 3) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatgalben"], shaders["VertexColor"], modelMatrix);
                }
                else if (patrate[i] == 4) {
                    modelMatrix = transform2D::Translate(a, b);
                    RenderMesh2D(meshes["ciudatmov"], shaders["VertexColor"], modelMatrix);
                }
            }

        }
    }
    for (int i = 0; i < 9; i++) {
        if (disparitie[i] == 0 ) {

            disparitie[i] = -1;
            patrate[i] = -1;
            }
            if (scaleX <= 0 && scaleY <= 0) {
                scaleX = 1;
                scaleY = 1;
                disparitie[i] = -1;
                patrate[i] = -1;
            }
        

            
    }

 
}


void Tema1::FrameEnd()
{
}



void Tema1::OnInputUpdate(float deltaTime, int mods)
{
   
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseY = 720 - mouseY;

    if (leftSteaDispare == true) {
        if (luat1 == true || luat2 == true || luat3 == true || luat4 == true) {
            drag = true;
            translateX = mouseX;
            translateY = mouseY;

    } 

    }
    if (leftSteaDispare == false) {
        if (luat1 == false || luat2 == false || luat3 == false || luat4 == false) {
            drag = false;
            translateX = mouseX;
            translateY = mouseY;

        }
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
   
    if (button == window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        leftSteaDispare = true;
    }
    if (button == 2) {
        mouseY = 720 - mouseY;

        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 10 && mouseY <= 110) {
          //  disparitie[0] = 0;
            patrate[0] = -1;

        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 140 && mouseY <= 240) {
          //  disparitie[1] = 0;
            patrate[1] = -1;
        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 270 && mouseY <= 350) {
          //  disparitie[2] = 0;
            patrate[2] = -1;
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 10 && mouseY <= 110) {
          //  disparitie[3] = 0;
            patrate[3] = -1;
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 140 && mouseY <= 240) {
          //  disparitie[4] = 0;
            patrate[4] = -1;
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 270 && mouseY <= 370) {
          //  disparitie[5] = 0;
            patrate[5] = -1;
        }
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 10 && mouseY <= 110) {
          //  disparitie[6] = 0;
            patrate[6] = -1;
        }
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 140 && mouseY <= 240) {
          //  disparitie[7] = 0;
            patrate[7] = -1;
        }
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 270 && mouseY <= 370) {
          //  disparitie[8] = 0;
            patrate[8] = -1;
        }
    }

    if (leftSteaDispare == true) {

        mouseY = 720 - mouseY;
        for (int m = 0; m < coordx.size(); m++) {

            if ((mouseX <= (coordx[m] + 3.81f * 20) && mouseX >= (coordx[m] - 3.81f * 20)) && (mouseY <= (coordy[m] + 3.44f * 20) && mouseY >= (coordy[m] - 2.81f * 20)) && leftSteaDispare == true) {
                auto lx = coordx.begin() + m;
                auto ly = coordy.begin() + m;
                n++;
                coordx.erase(lx);
                coordy.erase(ly);

            }
        }

        if ((mouseX >= 60 && mouseX <= 160 && mouseY >= 580 && mouseY <= 680 && n > 0)) {
            luat1 = true;
            drag = true;
            translateX = mouseX;
            translateY = mouseY;
            cout << "am intrat si aici on btn press \endl";
        }
        if ((mouseX >= 240 && mouseX <= 340 && mouseY >= 580 && mouseY <= 680 && n > 1)) {
            luat2 = true;
            drag = true;
            translateX = mouseX;
            translateY = mouseY;

        }
        if ((mouseX >= 420 && mouseX <= 520 && mouseY >= 580 && mouseY <= 680 && n > 1)) {
            luat3 = true;
            drag = true;
            translateX = mouseX;
            translateY = mouseY;
        }
        if ((mouseX >= 600 && mouseX <= 700 && mouseY >= 580 && mouseY <= 680 && n > 2)) {
            luat4 = true;
            drag = true;
            translateX = mouseX;
            translateY = mouseY;
        }

    }
}




void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

    mouseY = 720 - mouseY;
        luat1 = false;
        luat2 = false;
        luat3 = false;
        luat4 = false;

    if (leftSteaDispare == true && drag == true) {


        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 10 && mouseY <= 110) {
            if (patrate[0] == -1) {
                patrate[0] = what_romb;
                drag = false;
                cout << "intru din  nou";
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben= true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
           
        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 140 && mouseY <= 240) {
            if (patrate[1] == -1) {
                patrate[1] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 100 && mouseX <= 200 && mouseY >= 270 && mouseY <= 350) {
            if (patrate[2] == -1) {
                patrate[2] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 10 && mouseY <= 110) {
            if (patrate[3] == -1) {
                patrate[3] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 140 && mouseY <= 240) {
            if (patrate[4] == -1) {
                patrate[4] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 250 && mouseX <= 350 && mouseY >= 270 && mouseY <= 370) {
            if (patrate[5] == -1) {
                patrate[5] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 10 && mouseY <= 110) {
            if (patrate[6] == -1) {
                patrate[6] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 140 && mouseY <= 240) {
            if (patrate[7] == -1) {
                patrate[7] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }  
        if (mouseX >= 400 && mouseX <= 500 && mouseY >= 270 && mouseY <= 370) {
            if (patrate[8] == -1) {
                patrate[8] = what_romb;
                drag = false;
                if (what_romb == 1) {
                    luat1 = false;
                    n--;
                    portocaliu = true;
                }
                if (what_romb == 2) {
                    luat2 = false;
                    n = n - 2;
                    albastru = true;
                }
                if (what_romb == 3) {
                    luat3 = false;
                    n = n - 2;
                    galben = true;
                }
                if (what_romb == 4) {
                    luat4 = false;
                    n = n - 3;
                    mov = true;
                }
            }
        }

    }
    
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
