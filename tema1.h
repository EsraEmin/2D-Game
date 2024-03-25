#pragma once

#include "components/simple_scene.h"
#include <vector>;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;
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

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void CheckCollisions(float deltaTimeSeconds);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
       /* bool Tema1::IsPointInsideObject(const glm::vec2& point, const std::string& objectName);*/

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        std::vector<int> coordx;
        std::vector<int> coordy;
        std::vector<int> patrate;
        std::vector<int> disparitie;
        std::vector<int> inamici;
        std::vector<int> inamici_color;
        float inamic, random_time;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        float unghi = 60;
        int n,m,what_romb;
        float stea,timpinamic,a,b,timp;
        glm::vec2 dragStartPosition;
        bool leftSteaDispare;
        bool luat1, luat2, luat3, luat4, drag, portocaliu, albastru, galben, mov;
     
    };
}   // namespace m1
