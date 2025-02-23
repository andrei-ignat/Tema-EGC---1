#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
     public:
        Lab1();
        ~Lab1();

        void Init() override;

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
        int red, blue, green;
        bool isColorChanged = false;
        int current = 0;
        float currentpos1X = 2.0f, currentpos1Y = 1.0f, currentpos1Z = -2.0f;
        float currentpos2X = -1.0f, currentpos2Y = 0.5f, currentpos2Z = 0.0f;
        float currentpos3X = 1.0f, currentpos3Y = 0.5f, currentpos3Z = 0.0f;
        const float g = -9.8f;
        float vy = 0.0f;
        bool jump = false;
        float initialPosY = 0.0f;
        float jumpPower = 5.0f;
        float currentPOS;

        // TODO(student): Class variables go here

    };
}   // namespace m1
