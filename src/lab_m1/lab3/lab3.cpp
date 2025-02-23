#include "lab_m1/lab3/lab3.h"
#include "components/camera_input.h"
#include "core/engine.h"
#include "utils/memory_utils.h"
#include <vector>
#include <iostream>
#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include <cmath>
#include <algorithm>

using namespace std;
using namespace m1;


Lab3::Lab3()
{


}


Lab3::~Lab3()
{
}

glm::vec3 rotatePoint(glm::vec3 point, glm::vec3 center, glm::vec3 center1, float angle, float launchAngle) {
    float x = point.x - center.x;
    float y = point.y - center.y;
    float newX = x * cos(angle) - y * sin(angle);
    float newY = x * sin(angle) + y * cos(angle);
    return glm::vec3(newX + center.x, newY + center.y, 0);
}




void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);



    float bottomLength = 100;
    float topLength = 50;
    float height = 20;

    float height2 = 20;
    float bottomLength1 = 20;
    float topLength1 = 10;

    Mesh* trapez = object2D::CreateTrapezoid("Trapez", corner, bottomLength, topLength, height, glm::vec3(1.0f, 0.0f, 0.0f), true);
    AddMeshToList(trapez);
    Mesh* trapez1 = object2D::CreateTrapezoid1("Trapez1", corner, bottomLength, topLength, height, glm::vec3(1.0f, 0.0f, 0.0f), true);
    AddMeshToList(trapez1);

    float height1 = 30.0f;
    float width = 10.0f;




    Mesh* sinWaveRectangles = object2D::CreateSinWaveRectangles("sinWaveRectangles", corner, screenWidth, amplitude, frequency, amplitude1, frequency1, glm::vec3(1.0f, 1.0f, 0.0f), heightMap);
    AddMeshToList(sinWaveRectangles);


    Mesh* myCircle = object2D::CreateCircle("circleMesh", corner, 10.0f, glm::vec3(1, 0, 0), 100);
    AddMeshToList(myCircle);


    trapez2 = object2D::CreateDoubleTrapezoid2("Trapez2", glm::vec3(0, 0, 0),
        100.0f, 60.0f, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f),
        80.0f, 40.0f, 30.0f, glm::vec3(1.0f, 0.0f, 1.0f), rotationAngle);
    AddMeshToList(trapez2);

    trapez3 = object2D::CreateDoubleTrapezoid2("Trapez3", glm::vec3(0, 0, 0),
        100.0f, 60.0f, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f),
        80.0f, 40.0f, 30.0f, glm::vec3(1.0f, 0.0f, 1.0f), rotationAngle1);
    AddMeshToList(trapez3);

    rectangle1 = object2D::CreateRectangle("Rectangle", glm::vec3(0, 0, 0), heightRectangle, topRectangle, glm::vec3(0, 0, 0));
    AddMeshToList(rectangle1);

    rectangle2 = object2D::CreateRectangle("Rectangle2", glm::vec3(0, 0, 0), heightRectangle, topRectangle, glm::vec3(0, 1, 0));
    AddMeshToList(rectangle2);

    rectangle3 = object2D::CreateRectangle("Rectangle3", glm::vec3(0, 0, 0), heightRectangle, topRectangle, glm::vec3(0, 0, 0));
    AddMeshToList(rectangle3);

    rectangle4 = object2D::CreateRectangle("Rectangle4", glm::vec3(0, 0, 0), heightRectangle, topRectangle, glm::vec3(0, 1, 0));
    AddMeshToList(rectangle4);

 

}


void Lab3::FrameStart()
{

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void ApplyParabolicHole(std::vector<float>& heightMap, float mapWidth, float impactX, float radius, float impactDepth) {
    float pointSpacing = mapWidth / heightMap.size();
    int impactIndex = static_cast<int>(impactX / pointSpacing);

    float maxDistance = radius;

    for (int i = 0; i < heightMap.size(); ++i) {
        float distance = std::abs(i - impactIndex) * pointSpacing;


        if (distance < radius) {
            float parabolicDepth = impactDepth * (1.0f - pow(distance / radius, 2));
            heightMap[i] = std::max(0.0f, heightMap[i] - parabolicDepth);
        }
    }
}

void ApplyLandslide(std::vector<float>& heightMap, float heightThreshold, float transferRate, float deltaTime) {
    for (size_t i = 0; i < heightMap.size() - 1; ++i) {
        // Calculează diferența de înălțime între punctele adiacente
        float heightDiff = heightMap[i] - heightMap[i + 1];

        // Dacă diferența depășește pragul, aplică transferul de înălțime
        if (fabs(heightDiff) > heightThreshold) {
            // Calculăm valoarea de transfer ε bazată pe deltaTime și transferRate
            float epsilon = transferRate * deltaTime * fabs(heightDiff);

            // Transferă înălțimea de la punctul mai înalt la cel mai jos
            if (heightDiff > 0) {
                heightMap[i] -= epsilon;
                heightMap[i + 1] += epsilon;
            }
            else {
                heightMap[i] += epsilon;
                heightMap[i + 1] -= epsilon;
            }
        }
    }
}






void Lab3::Update(float deltaTimeSeconds)
{

    //cout << heightMap[0] << endl;
    //ApplyLandslide(heightMap, heightThreshold, transferRate, deltaTimeSeconds);

    // Actualizează mesh-ul sinWaveRectangles pentru a reflecta harta de înălțime modificată
    //meshes["sinWaveRectangles"] = object2D::UpdateSinWaveRectangles("sinWaveRectangles", corner, screenWidth, heightMap, glm::vec3(1.0f, 1.0f, 0.0f));

    if (isTrapez2) {
        launchAngle = M_PI / 2 + rotate + rotationAngle;
        translate1X = x1;
        translate1Y = heightMap[x1 / (screenWidth / numRectangles)] - 5;
        rotate = atan((heightMap[x1 / (screenWidth / numRectangles) + 1] - heightMap[x1 / (screenWidth / numRectangles)]) / (screenWidth / numRectangles));
        translation = rotatePoint(glm::vec3(translate1X, translate1Y + 70, 0), glm::vec3(translate1X, translate1Y, 0), glm::vec3(translate1X, translate1Y + 150, 0), rotate, launchAngle);
        translation2 = rotatePoint(glm::vec3(translate1X - 50, translate1Y + 170, 0), glm::vec3(translate1X, translate1Y, 0), glm::vec3(translate1X, translate1Y + 150, 0), rotate, launchAngle);



        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translation2.x, translation2.y) * transform2D::Rotate(rotate);
        RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);



        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translation2.x, translation2.y) * transform2D::Rotate(rotate);
        RenderMesh2D(meshes["Rectangle2"], shaders["VertexColor"], modelMatrix);

        rectangle1 = object2D::CreateRectangle("Rectangle", glm::vec3(0, 0, 0), heightRectangle, topRectangle, glm::vec3(0, 0, 0));
        AddMeshToList(rectangle1);

        rectangle2 = object2D::CreateRectangle("Rectangle2", glm::vec3(0, 0, 0), heightRectangle2, topRectangle2, glm::vec3(0, 1, 0));
        AddMeshToList(rectangle2);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translate1X, translate1Y) * transform2D::Rotate(rotate);
        RenderMesh2D(meshes["Trapez2"], shaders["VertexColor"], modelMatrix);




        trapez2 = object2D::CreateDoubleTrapezoid2("Trapez2", glm::vec3(0, 0, 0), 100.0f, 60.0f, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f), 80.0f, 40.0f, 30.0f, glm::vec3(1.0f, 0.0f, 1.0f), rotationAngle);
        AddMeshToList(trapez2);

      
        if (isFiring) {

            projectileVelocity.x = initialSpeed * cos(launchAngle);
            projectileVelocity.y = initialSpeed * sin(launchAngle);


            elapsedTime += deltaTimeSeconds;
            projectilePosition.x += projectileVelocity.x * deltaTimeSeconds;
            projectilePosition.y += projectileVelocity.y * deltaTimeSeconds - 0.5f * g * elapsedTime * elapsedTime;
            float hillHeight = 0;
            hillHeight = heightMap[projectilePosition.x / (screenWidth / numRectangles)];
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(projectilePosition.x, projectilePosition.y);
            RenderMesh2D(meshes["circleMesh"], shaders["VertexColor"], modelMatrix);






            if (projectilePosition.x >= translate2X - 50 && projectilePosition.x <= translate2X + 50 && projectilePosition.y <= translation1.y + 10) {

                if (nr > 0) {
                    nr--;
                    topRectangle3 -= 33.0f;
                }

                else

                {
                    isTrapez3 = false;
                    translate2X = 0;
                    translate2Y = 0;
                }

                isFiring = false;
                aruncare_tank = true;
            }
            else
                if (projectilePosition.y <= hillHeight && aruncare_tank == false) {



                    isFiring = false;
                    impactX = projectilePosition.x;
                    ApplyParabolicHole(heightMap, screenWidth, impactX, explosionRadius, impactDepth);
                    meshes["sinWaveRectangles"] = object2D::UpdateSinWaveRectangles("sinWaveRectangles", corner, screenWidth, heightMap, glm::vec3(1.0f, 1.0f, 0.0f));

                }
        }




    }


    if (isTrapez3) {
        launchAngle1 = M_PI / 2 + rotate1 + rotationAngle1;
        translate2X = x2;
        translate2Y = heightMap[x2 / (screenWidth / numRectangles)] - 5;
        rotate1 = atan((heightMap[x2 / (screenWidth / numRectangles) + 1] - heightMap[x2 / (screenWidth / numRectangles)]) / (screenWidth / numRectangles));
        translation1 = rotatePoint(glm::vec3(translate2X, translate2Y + 70, 0), glm::vec3(translate2X, translate2Y, 0), glm::vec3(translate2X, translate2Y + 150, 0), rotate1, launchAngle1);
        translation3 = rotatePoint(glm::vec3(translate2X - 50, translate2Y + 170, 0), glm::vec3(translate2X, translate2Y, 0), glm::vec3(translate2X, translate2Y + 150, 0), rotate1, launchAngle1);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translation3.x, translation3.y) * transform2D::Rotate(rotate1);
        RenderMesh2D(meshes["Rectangle3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translation3.x, translation3.y) * transform2D::Rotate(rotate1);
        RenderMesh2D(meshes["Rectangle4"], shaders["VertexColor"], modelMatrix);

        rectangle3 = object2D::CreateRectangle("Rectangle3", glm::vec3(0, 0, 0), heightRectangle3, topRectangle3, glm::vec3(0, 0, 0));
        AddMeshToList(rectangle3);

        rectangle4 = object2D::CreateRectangle("Rectangle4", glm::vec3(0, 0, 0), heightRectangle4, topRectangle4, glm::vec3(0, 1, 0));
        AddMeshToList(rectangle4);


        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translate2X, translate2Y) * transform2D::Rotate(rotate1);
        RenderMesh2D(meshes["Trapez3"], shaders["VertexColor"], modelMatrix);

        trapez3 = object2D::CreateDoubleTrapezoid2("Trapez3", glm::vec3(0, 0, 0), 100.0f, 60.0f, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f),
            80.0f, 40.0f, 30.0f, glm::vec3(1.0f, 0.0f, 1.0f), rotationAngle1);
        AddMeshToList(trapez3);

        if (isFiring1) {
            elapsedTime1 += deltaTimeSeconds;
            projectilePosition1.x += projectileVelocity1.x * deltaTimeSeconds;
            projectilePosition1.y += projectileVelocity1.y * deltaTimeSeconds - 0.5f * g * elapsedTime1 * elapsedTime1;
            

            float hillHeight = 0;
            hillHeight = heightMap[projectilePosition1.x / (screenWidth / numRectangles)];


            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(projectilePosition1.x, projectilePosition1.y);
            RenderMesh2D(meshes["circleMesh"], shaders["VertexColor"], modelMatrix);

            if (projectilePosition1.x >= translate1X - 50 && projectilePosition1.x <= translate1X + 50 && projectilePosition1.y <= translation2.y + 10) {

                if (nr1 > 0) {
                    nr1--;
                    topRectangle -= 33.0f;
                }

                else

                {
                    isTrapez2 = false;
                    translate1X = 0;
                    translate1Y = 0;
                }

                isFiring1 = false;
                aruncare_tank1 = true;
            }
            else
                if (projectilePosition1.y <= hillHeight && aruncare_tank1 == false) {
                    isFiring1 = false;
                    impactX = projectilePosition1.x;
                    //showTrajectory2 = true;
                    ApplyParabolicHole(heightMap, screenWidth, impactX, explosionRadius, impactDepth);
                    meshes["sinWaveRectangles"] = object2D::UpdateSinWaveRectangles("sinWaveRectangles", corner, screenWidth, heightMap, glm::vec3(1.0f, 1.0f, 0.0f));
                }

        }
    }
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0); // Ajustăm poziția pe verticală
    RenderMesh2D(meshes["sinWaveRectangles"], shaders["VertexColor"], modelMatrix);


}
void Lab3::FrameEnd()
{

}


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_A)) {

        x1 += 4;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        x1 -= 4;
    }

    if (window->KeyHold(GLFW_KEY_M)) {


        if (rotationAngle >= -M_PI / 2) {
            rotationAngle -= deltaTime;
        }

    }

    if (window->KeyHold(GLFW_KEY_N)) {
        if (rotationAngle <= M_PI / 2) {
            rotationAngle += deltaTime;
        }
    }


    if (window->KeyHold(GLFW_KEY_UP)) {


        if (rotationAngle1 >= -M_PI / 2) {
            rotationAngle1 -= deltaTime;
        }

    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (rotationAngle1 <= M_PI / 2) {
            rotationAngle1 += deltaTime;
        }
    }



    if (window->KeyHold(GLFW_KEY_LEFT)) {
        x2 -= 4;
    }


    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        x2 += 4;
    }
}


void Lab3::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE && !isFiring) {


        isFiring = true;
        elapsedTime = 0.0f;
        if (aruncare_tank == true) {
            aruncare_tank = false;
        }

        projectilePosition.x = translation.x;
        projectilePosition.y = translation.y;
        projectileVelocity.x = initialSpeed * cos(launchAngle);
        projectileVelocity.y = initialSpeed * sin(launchAngle);

    }

  
    if (key == GLFW_KEY_ENTER && !isFiring1) {
        isFiring1 = true;
        elapsedTime1 = 0.0f;

        if (aruncare_tank1 == true) {
            aruncare_tank1 = false;
        }

        projectilePosition1.x = translation1.x;
        projectilePosition1.y = translation1.y;
        projectileVelocity1.x = initialSpeed * cos(launchAngle1);
        projectileVelocity1.y = initialSpeed * sin(launchAngle1);

    }

    if (key == GLFW_KEY_T && !showTrajectory2) {

        trajectoryPoints1.clear();
        showTrajectory2 = true;
        elapsedTime2 = 0.0f;
        projectilePosition2.x = translation.x;
        projectilePosition2.y = translation.y;
        projectileVelocity.x = initialSpeed * cos(launchAngle);
        projectileVelocity.y = initialSpeed * sin(launchAngle);
        showTrajectory2 = true;
    }

}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event


    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        elapsedTime2 = 0.0f;
        projectilePosition2.x = translation.x;
        projectilePosition2.y = translation.y;
        showTrajectory = true;
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        trajectoryPoints1.clear();
        showTrajectory = false;
    }
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event




}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event

}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}


void Lab3::OnWindowResize(int width, int height)
{
}

