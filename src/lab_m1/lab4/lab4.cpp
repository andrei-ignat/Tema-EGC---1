#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;


    rotation = 0.0f;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::RenderScene() {
    translateX1 = translateX;
    translateY1 = translateY;
    translateZ1 = translateZ;
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(1, 0, 0.1);
    modelMatrix *= transform3D::Rotate(rotationX1, rotationX2, rotationX3);
    modelMatrix *= transform3D::Translate(-2.5, 0.5f, -1.0f);
    modelMatrix *= transform3D::Translate(translateX1, translateY1, translateZ1);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
    DrawCoordinateSystem();
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add transformation logic

    if (window->KeyHold(GLFW_KEY_W))
        translateZ += deltaTime * 2;
    if (window->KeyHold(GLFW_KEY_R))
        translateZ -= deltaTime * 2;
    if (window->KeyHold(GLFW_KEY_A))
        translateX -= deltaTime * 2;
    if (window->KeyHold(GLFW_KEY_D))
        translateX += deltaTime * 2;
    if (window->KeyHold(GLFW_KEY_S))
        translateY -= deltaTime * 2;
    if (window->KeyHold(GLFW_KEY_F))
        translateY += deltaTime * 2;

    if (window->KeyHold(GLFW_KEY_1)) {
        scaleX *= 1.01;
        scaleY *= 1.01;
        scaleZ *= 1.01;

    }

    if (window->KeyHold(GLFW_KEY_2)) {
        scaleX /= 1.01;
        scaleY /= 1.01;
        scaleZ /= 1.01;
    }

    if (window->KeyHold(GLFW_KEY_3)) {
        angularStepOX += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_4)) {
        angularStepOX -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_5)) {
        angularStepOY += deltaTime;
        rotationDirectionCub1 = 0.01f;
        tra1 = 1;
    }

    if (window->KeyHold(GLFW_KEY_6)) {
        angularStepOY -= deltaTime;
        rotationDirectionCub1 = -0.01f;
        tra1 = -1;
    }

    if (window->KeyHold(GLFW_KEY_7)) {
        angularStepOZ += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_8)) {
        angularStepOZ -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_M)) {
        translateX1 = tra1;
    }

    if (window->KeyHold(GLFW_KEY_N)) {
        rotation -= deltaTime;
    }


        

}


void Lab4::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }

    if (key == GLFW_KEY_I) {
        miniViewportArea.x = miniViewportArea.x + 10;

    }

    if (key == GLFW_KEY_J) {
        miniViewportArea.x = miniViewportArea.x - 10;
    }

    if (key == GLFW_KEY_K) {
        miniViewportArea.y = miniViewportArea.y + 10;
    }

    if (key == GLFW_KEY_L) {
        miniViewportArea.y = miniViewportArea.y - 10;
    }

    if (key == GLFW_KEY_U) {
        miniViewportArea.height = miniViewportArea.height * 1.1f;
        miniViewportArea.width = miniViewportArea.width * 1.1f;
    }

    if (key == GLFW_KEY_O) {
        miniViewportArea.height = miniViewportArea.height / 1.1f;
        miniViewportArea.width = miniViewportArea.width / 1.1f;
    }
    // TODO(student): Add viewport movement and scaling logic
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
