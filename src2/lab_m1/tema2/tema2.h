#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"
#include "lab_m1/tema2/maze.h"
#include "lab_m1/tema2/player.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implementedCamera::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float fov = 60;
        float left = -4.0f, right = 4.0f;
        float top = 6.0f, bottom = -6.0f;
        float znear = 0.01f, zfar = 100.0f;

        float angle = 0;
       
        int mazeWidth = 21;

        maze lab;
        int** maze;
        player jucator;

        bool shootFlag = false;
        float time = 3.0f;

    };
}   // namespace m1
