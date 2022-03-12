#pragma once

#include "components/simple_scene.h"
#include "enemy.h"
#include "projectile.h"
#include <vector>


namespace m1
{
    class tema1_Vis2D : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        tema1_Vis2D();
        ~tema1_Vis2D();
        void Init() override;
        
     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void DrawScene(glm::mat3 visMatrix);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        float translateX = 0, translateY = 0;
        float translateXP1 = 0, translateYP1 = 0;
        float translateXP2 = 0, translateYP2 = 0;
        float translateXI = 0, translateYI = 0;
        float scaleX = 1, scaleY = 1;
        float angularStep = 0, angularStepP = 0;
        int mX, mY;
        int shoot = 0;
        std::vector<enemy> enemies;
        projectile p1;
        projectile p2;
        int health = 10;
    };
}
