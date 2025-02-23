#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/transform2D1.h"
#include "object2D1.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

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


    protected:
        glm::mat3 modelMatrix;
        float translateX1;
        float positionX, positionY;
        int numPoints = 1000;
        float screenWidth = 1280.0f;
        float translate1X, translate1Y;
        float rotate;
        float rotate1;
        float translate2X, translate2Y;
        float translate3X = 0.0f;
        float amplitude = 100.0f;
        float frequency = 0.01f;
        float amplitude1 = 120.0f;
        float frequency1 = 0.0011f;
        float numRectangles = 1000.0f;
        float x1 = 0 + 150 * (screenWidth / numRectangles);
        float x2 = 0 + 450 * (screenWidth / numRectangles);
        float rotationAngle = 0.0f;
        float rotationAngle1 = 0.0f;
        float heightThreshold = 1.0f;   // Pragul diferenței de înălțime
        float transferRate = 1.0f;


        float g = 9.8f;
        int ok1 = 0;
        bool isFiring = false;
        bool isFiring1 = false;
        float initialSpeed = 300.0f;
        float launchAngle = 0.0f;
        float launchAngle1 = 0.0f;
        float elapsedTime = 0.0f;
        float elapsedTime1 = 0.0f;
        float elapsedTime2 = 0.0f;
        Mesh* trapez2;
        Mesh* trapez3;
        bool isTrapez3 = true;
        bool isTrapez2 = true;
        float projectileSpeed = 200;
        bool returnning1 = false;
        glm::vec3 projectilePosition;         // Poziția proiectilului
        glm::vec3 projectileVelocity;
        glm::vec3 projectilePosition1;
        glm::vec3 projectileVelocity1;
        glm::vec3 projectilePosition2;
        int nr2 = 0;
        float rotation1 = 0.0f;
        glm::vec3 translation;
        glm::vec3 corner = glm::vec3(0, 0, 0);
        glm::vec3 translation1;
        glm::vec3 translation2;
        glm::vec3 translation3;

        bool ok;
        bool ok2 = false;
        std::vector<float> heightMap;
        int rotationDirection = 1;
        float impactX;
        float explosionRadius = 0.2f * screenWidth;
        float impactDepth = 100.0f;
        std::vector<glm::vec3> trajectoryPoints1;
        bool showTrajectory = false;
        bool showTrajectory1 = false;
        bool showTrajectory2 = false;
        bool aruncare_tank = false;
        bool aruncare_tank1 = false;
        int nr = 2;
        int nr1 = 2;

        float heightRectangle = 30.0f;
        float topRectangle = 99.0f;
        float heightRectangle2 = 30.0f;
        float topRectangle2 = 99.0f;

        float heightRectangle3 = 30.0f;
        float topRectangle3 = 99.0f;

        float heightRectangle4 = 30.0f;
        float topRectangle4 = 99.0f;

        Mesh* rectangle1;
        Mesh* rectangle2;
        Mesh* rectangle3;
        Mesh* rectangle4;
        //float numRectangles = 1000.0f;
    };
}   // namespace m1
