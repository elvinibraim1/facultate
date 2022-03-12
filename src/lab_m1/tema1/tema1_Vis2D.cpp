#include "lab_m1/tema1/tema1_Vis2D.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "enemy.h"
#include "projectile.h"

using namespace std;
using namespace m1;


tema1_Vis2D::tema1_Vis2D()
{
}


tema1_Vis2D::~tema1_Vis2D()
{
}

void tema1_Vis2D::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 400;   // logic width
    logicSpace.height = 400;  // logic height

    glm::vec3 corner = glm::vec3(0, 0, 0);

    // vector inamici
    for (int i = 0; i < 30; i++)
        enemies.push_back(enemy());
    
    // player
    Mesh* circleP = object2D::CreateCircle("circleP", corner, 30, glm::vec3(0.66f, 0.22f, 1));
    AddMeshToList(circleP);
    Mesh* squareP = object2D::CreateSquare("squareP", corner, 7, glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), true);
    AddMeshToList(squareP);
    Mesh* triangleP = object2D::CreateTriangle("triangleP", corner, 7, glm::vec3(1, 0, 0), true);
    AddMeshToList(triangleP);

    // proiectil
    Mesh* square = object2D::CreateSquare("square", corner, 5, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), true);
    AddMeshToList(square);

    // inamic
    Mesh* squareE = object2D::CreateSquare("squareE", corner, 10, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), true);
    AddMeshToList(squareE);

    //healthbar
    Mesh* squareH = object2D::CreateSquare("squareH", corner, 10, glm::vec3(1, 0, 0), glm::vec3(0.95, 0, 0), true);
    AddMeshToList(squareH);
    Mesh* squareH2 = object2D::CreateSquare("squareH2", corner, 10, glm::vec3(1, 0, 0), glm::vec3(0.95, 0, 0), false);
    AddMeshToList(squareH2);

    //harta
    Mesh* squareM = object2D::CreateSquare("squareM", corner, 10, glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), true);
    AddMeshToList(squareM);
}

glm::mat3 tema1_Vis2D::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
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


void tema1_Vis2D::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void tema1_Vis2D::FrameStart()
{
}


void tema1_Vis2D::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(1, 1, 1), true);

    // unghi player fata de mouse
    if (mX > resolution.x / 2 && mY > resolution.y / 2)
        angularStep = atan((float)(abs(mY- resolution.y / 2)) / abs((mX - resolution.x / 2)));

    else if (mX > resolution.x / 2  && mY < resolution.y )
        angularStep = -atan((float)(abs(mY - resolution.y / 2)) / abs((mX - resolution.x / 2)));

    else if (mX < resolution.x / 2 && mY < resolution.y / 2)
        angularStep = 3 * M_PI / 2 - atan((float)(abs(mX - resolution.x / 2)) / abs((mY - resolution.y / 2)));

    else if (mX < resolution.x / 2 && mY > resolution.y / 2)
        angularStep = M_PI / 2 + atan((float)(abs(mX - resolution.x / 2)) / abs(mY - resolution.y / 2));


    // render player
    modelMatrix = transform2D::Translate(resolution.x / 2, 360);
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["circleP"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2D::Translate(resolution.x / 2 + 30, resolution.y / 2);
    modelMatrix *= transform2D::Translate(-30, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(30, 0);
    RenderMesh2D(meshes["squareP"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2D::Translate(resolution.x / 2 + 37, resolution.y / 2);
    modelMatrix *= transform2D::Translate(-37, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(37, 0);
    RenderMesh2D(meshes["triangleP"], shaders["VertexColor"], modelMatrix);

    
    // proiectil
    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, p1.translateX, p1.translateY, 1);
    modelMatrix *= transform2D::Translate(resolution.x / 2, resolution.y / 2);
    modelMatrix *= transform2D::Rotate(p1.angularStep);

    if (p1.time >= 0.5f) {
        if (shoot == 1) {
            p1.time = 0.0f;
            p1.setAngle(angularStepP);

            modelMatrix *= transform2D::Translate(resolution.x / 2, resolution.y / 2);
            p1.translateX = 0;
            p1.translateY = 0;
        }
    }

    if (shoot == 2) {
        p1.time += deltaTimeSeconds;
        p1.translateX += 720 * cos(p1.angularStep) / 2 * deltaTimeSeconds;
        p1.translateY += 720 * sin(p1.angularStep) / 2 * deltaTimeSeconds;

    }
    if (p1.time < 1.5) 
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);


    // inamic 
    for (int i = 0; i < enemies.size(); i++) {
        if (abs(abs(enemies.at(i).x - resolution.x / 2) - abs(enemies.at(i).translateX)) > 45 || abs(abs(enemies.at(i).y - resolution.y / 2) - abs(enemies.at(i).translateY)) > 45) {
            float angle = enemies.at(i).getAngle(enemies.at(i).x, enemies.at(i).y, resolution.x / 2, resolution.y / 2);
            enemies.at(i).translateX -= cos(angle);
            enemies.at(i).translateY -= sin(angle);

            modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, enemies.at(i).translateX, enemies.at(i).translateY, 1);
            modelMatrix *= transform2D::Translate(enemies.at(i).x - 25, enemies.at(i).y + 30);
            RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, enemies.at(i).translateX, enemies.at(i).translateY, 1);
            modelMatrix *= transform2D::Translate(enemies.at(i).x + 25, enemies.at(i).y + 30);
            RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);

            modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, enemies.at(i).translateX, enemies.at(i).translateY, 1);
            modelMatrix *= transform2D::Translate(enemies.at(i).x, enemies.at(i).y);
            modelMatrix *= transform2D::Scale(3, 3);
            RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);
        }
        else {
            if (health > 0) {
                health--;
                enemies.erase(enemies.begin() + i);
            }
        }
    }


    // healthbar - 10 vieti
    int xHealhbar = resolution.x - 70;
    int yHealtbar = resolution.y - 70;

    for (int i = (10 - health) * 10; i < 100; i += 10) {
        
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(xHealhbar - i, yHealtbar) * transform2D::Scale(0.5f, 1);
        RenderMesh2D(meshes["squareH"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(xHealhbar - 45, yHealtbar) * transform2D::Scale(5, 1);
    RenderMesh2D(meshes["squareH2"], shaders["VertexColor"], modelMatrix);


    // scena
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix);
}


void tema1_Vis2D::FrameEnd()
{
}


void tema1_Vis2D::DrawScene(glm::mat3 visMatrix)
{   
    modelMatrix = visMatrix * transform2D::Translate(-200, 200) * transform2D::Scale(2, 30);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(-60, 360) * transform2D::Scale(30, 2);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(400, 360) * transform2D::Scale(10, 40);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(500, -100) * transform2D::Scale(30, 15);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Rotate(RADIANS(45)) * transform2D::Translate(-300, -200) * transform2D::Scale(2, 20);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(200, 200) * transform2D::Scale(70, 70);
    RenderMesh2D(meshes["squareM"], shaders["VertexColor"], modelMatrix);

 }


void tema1_Vis2D::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W))
        logicSpace.y += 150 *deltaTime;

    if (window->KeyHold(GLFW_KEY_A))
        logicSpace.x -=150 * deltaTime;

    if (window->KeyHold(GLFW_KEY_S))
        logicSpace.y -= 150 * deltaTime;

    if (window->KeyHold(GLFW_KEY_D))
        logicSpace.x += 150 * deltaTime;

}


void tema1_Vis2D::OnKeyPress(int key, int mods)
{
}


void tema1_Vis2D::OnKeyRelease(int key, int mods)
{
}


void tema1_Vis2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mY = 720 - mouseY;
    mX = mouseX;
}


void tema1_Vis2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{   
    if (button == 1) {
        if (p1.time >= 0.5f) {
            angularStepP = angularStep;
            shoot = 1;
        }
    }                               
}


void tema1_Vis2D::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{   
    if (button == 1)
        shoot = 2;
}


void tema1_Vis2D::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
