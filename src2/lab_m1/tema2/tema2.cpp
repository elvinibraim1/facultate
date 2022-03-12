#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>


using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = true;
       
    lab.setWidth(25);
    int** mazeMat = lab.mazeGen();
    maze = mazeMat;
    jucator.setCoord(lab.xPlayer, lab.yPlayer);

    camera = new implementedCamera::Camera();
    camera->Set(glm::vec3(0, 2.5f, 3.0f) + glm::vec3(2 * jucator.x, 0, 2 * jucator.y), glm::vec3(0, 1, 0) + glm::vec3(2 * jucator.x, 0, 2 * jucator.y), glm::vec3(0, 1, 0));


    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* podea = new Mesh("plane");
        podea->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[podea->GetMeshID()] = podea;

    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, znear, zfar);

}

void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{   
    { // plan
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(25, 0, 25));
        RenderMesh(meshes["plane"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
    }

    { // labirint
        glm::mat4 modelMatrix = glm::mat4(1);
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 25; j++) {
                if (maze[i][j] == 1) {
                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(2 * i  + 1, 1, 2 * j + 1));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 2));
                    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 1, 0));
                }

                if (maze[i][j] == 2) {
                    modelMatrix = glm::mat4(1);
                   modelMatrix = glm::translate(modelMatrix, glm::vec3(2 * i  + 0.5, 1, 2 * j + 0.5));
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5, 0, 0.5));
                    modelMatrix = glm::rotate(modelMatrix, angle + i, glm::vec3(0, 1, 0));
                    angle += deltaTimeSeconds;
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, -0.5));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
                    RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 0, 0));
                }

            }
    }

    if (renderCameraTarget) {
        { // cap
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.5f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f, 0.3f, 0.3f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 0.992f, 0.815f));
        }

        { // corp
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.97f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::rotate(modelMatrix, 1.57f, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.7f, 0.5f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.182f, 0.542f, 0.339f));
        }

        { // maini
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.37f, 1.12f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.4f, 0.2f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.182f, 0.542f, 0.339f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.37f, 1.12f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.4f, 0.2f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.182f, 0.542f, 0.339f));
        }

        { // picioare
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.15f, 0.3f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.6f, 0.2f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.254f, 0.411f, 0.882f));

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.15f, 0.3f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.6f, 0.2f));
            RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix, glm::vec3(0.254f, 0.411f, 0.882f));
        }

    }
    else {
       /* {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.3f, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition()));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -camera->GetTargetPosition()[1], 0));
            RenderMesh(meshes["teapot"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 0, 0));
        }*/
    }

    if (shootFlag == true || time < 3.0f) {
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 5, 10));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
            RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, glm::vec3(0, 1, 0));
        }
    }   

}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{   
    shader = shaders.at("Color");

    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniform3f(shader->GetUniformLocation("color"), color.r, color.g, color.b);

    mesh->Render();
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 4.0f;

        if (window->KeyHold(GLFW_KEY_W))
            camera->MoveForward(cameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_A))
            camera->TranslateRight(-cameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_S))
            camera->MoveForward(-cameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_D))
            camera->TranslateRight(cameraSpeed * deltaTime);

       /* if (window->KeyHold(GLFW_KEY_Q))
            camera->TranslateUpward(-cameraSpeed * deltaTime);

        if (window->KeyHold(GLFW_KEY_E))
            camera->TranslateUpward(cameraSpeed * deltaTime);*/
    }

}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL) {
        renderCameraTarget = !renderCameraTarget;
        if (renderCameraTarget == false)
            camera->MoveForward(1.5f);
        else
            camera->MoveForward(-1.5f);
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{

}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (renderCameraTarget == false) {
            camera->RotateFirstPerson_OX(-sensivityOY * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOX * deltaX);
        }

        if (renderCameraTarget == true) {
            camera->RotateThirdPerson_OX(-sensivityOY * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOX * deltaX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{   
    if (button == 1 && renderCameraTarget == false) {
        shootFlag = true;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{   
    if (button == 1) {
        shootFlag = false;
        time = 0.0f;
    }
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
