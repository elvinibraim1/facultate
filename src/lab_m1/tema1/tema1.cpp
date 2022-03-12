#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

using namespace std;
using namespace m1;

tema1::tema1()
{
}


tema1::~tema1()
{
}


void tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    translateX = 0;
    translateY = 0;
    translateXP = 0;
    translateYP = 0;
    translateXI = 0;
    translateYI = 0;


    scaleX = 1;
    scaleY = 1;

    angularStep = 0;
    angularStepP = 0;

    centerX = 640;
    centerY = 360;

    Mesh* circleP = object2D::CreateCircle("circleP", corner, 30, glm::vec3(0.66f, 0.22f, 1));
    AddMeshToList(circleP);

    Mesh* squareP = object2D::CreateSquare("squareP", corner, 7, glm::vec3(1, 0, 0), true);
    AddMeshToList(squareP);

    Mesh* triangleP = object2D::CreateTriangle("triangleP", corner, 7, glm::vec3(1, 0, 0), true);
    AddMeshToList(triangleP);

    // player

    Mesh* square = object2D::CreateSquare("square", corner, 5, glm::vec3(0, 0, 0), true);
    AddMeshToList(square);

    //proiectil

    Mesh* squareE = object2D::CreateSquare("squareE", corner, 10, glm::vec3(0, 1, 0), true);
    AddMeshToList(squareE);

    // inamic

}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema1::Update(float deltaTimeSeconds)
{   
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (mX >= centerX && mY >= centerY)
        angularStep = atan((abs(mY - centerY)) / abs((mX - centerX)));

    if (mX >= centerX && mY < centerY)
        angularStep = -atan((abs(mY - centerY)) / abs((mX - centerX)));

    if (mX < centerX && mY < centerY)
        angularStep = 3 * M_PI / 2 - atan((abs(mX - centerX)) / abs((mY - centerY)));

    if (mX < centerX && mY >= centerY)
        angularStep = M_PI / 2 + atan((abs(mX - centerX)) / abs((mY - centerY)));

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
    modelMatrix *= transform2D::Translate(640, 360);
    modelMatrix *= transform2D::Rotate(angularStep);
    RenderMesh2D(meshes["circleP"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
    modelMatrix *= transform2D::Translate(670, 360);
    modelMatrix *= transform2D::Translate(-30, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(30, 0);
    RenderMesh2D(meshes["squareP"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
    modelMatrix *= transform2D::Translate(677, 360);
    modelMatrix *= transform2D::Translate(-37, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(37, 0);
    RenderMesh2D(meshes["triangleP"], shaders["VertexColor"], modelMatrix);

    //player

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateXP, translateYP, 1);
    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angularStepP);

    if (shoot == 1) {

        modelMatrix *= transform2D::Translate(centerX, centerY);
        translateXP = 0;
        translateYP = 0;

    }

    if (shoot == 2) {

        translateXP += 720 * cos(angularStepP) / 3 * deltaTimeSeconds;
        translateYP += 720 * sin(angularStepP) / 3 * deltaTimeSeconds;

    }

    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    //proiectil

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateXI, translateYI, 1);
    modelMatrix *= transform2D::Translate(150, 250);
    RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateXI, translateYI, 1);
    modelMatrix *= transform2D::Translate(200, 250);
    RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1, 0, 0, 0, 1, 0, translateXI, translateYI, 1);
    modelMatrix *= transform2D::Translate(175, 220);
    modelMatrix *= transform2D::Scale(3, 3);
    RenderMesh2D(meshes["squareE"], shaders["VertexColor"], modelMatrix);

    translateXI += translateX / 3 * deltaTimeSeconds;
    translateYI += translateY / 3 * deltaTimeSeconds;

    //inamic
    
}


void tema1::FrameEnd()
{
}


void tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) {
        translateY += 1000 * deltaTime;
        centerY = translateY + 360;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        translateY -= 1000 * deltaTime;
        centerY = translateY + 360;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        translateX -= 1000 * deltaTime;
        centerX = translateX + 640;
        cout << centerX << " ";
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        translateX += 1000 * deltaTime;
        centerX = translateX + 640;;
    }

}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    
}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{   
    // Add mouse move event
    mY = 720 - mouseY;
    mX = mouseX;

}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    shoot = 1;

    angularStepP = angularStep;
 


}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    shoot = 2;
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}
