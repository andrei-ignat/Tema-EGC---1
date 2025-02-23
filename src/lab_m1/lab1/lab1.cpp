#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!

}


Lab1::~Lab1()
{
    red = 2.0f;
    blue = 3.0f;
    green = 4.0f;

}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* teapot = new Mesh("teapot");
        teapot->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[teapot->GetMeshID()] = teapot;
    }

    {
        Mesh* sphere = new Mesh("sphere");
        sphere->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[sphere->GetMeshID()] = sphere;

    }

    {
        Mesh* sphere1 = new Mesh("sphere");
        sphere1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[sphere1->GetMeshID()] = sphere1;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
   // RGBA (0.39, 0.58, 0.93, 1.0)

    if (isColorChanged)
        //glClearColor(0, 0, 0, 1);
        glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    else
        glClearColor(0, 0, 0, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(currentpos1X, currentpos1Y, currentpos1Z), glm::vec3(1));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(currentpos2X, currentpos2Y, currentpos2Z));


    switch (current) {
       case 0:
           RenderMesh(meshes["box"], glm::vec3(currentpos3X, currentpos3Y, currentpos3Z));
           break;
       case 1:
           RenderMesh(meshes["teapot"], glm::vec3(currentpos3X, currentpos3Y, currentpos3Z), glm::vec3(1));
           break;
       default:
           RenderMesh(meshes["sphere"], glm::vec3(currentpos3X, currentpos3Y, currentpos3Z));
           break;
    }

    if (jump) {
        currentPOS = currentpos1Y;
        currentpos1Y += vy * deltaTimeSeconds;// Update position with current velocity
        vy -= g * deltaTimeSeconds;
        //currentpos1Y = currentPOS;
        // Apply gravity

        // If the object has come back down to the initial position, stop the jump
        if (currentpos1Y <= initialPosY) {
            currentpos1Y = initialPosY;
            vy = 0;  // Reset velocity
            jump = false;  // Stop jumping
        }
    }
    

   // RenderMesh(meshes["box"], glm::vec3(2, 3.5f, 1), glm::vec3(1));
}

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    if (window->KeyHold(GLFW_KEY_0)) {
        currentpos1X = currentpos1X + 1 * deltaTime;
        currentpos2X = currentpos2X + 1 * deltaTime;
        currentpos3X = currentpos3X + 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_1)) {
        currentpos1X = currentpos1X - 1 * deltaTime;
        currentpos2X = currentpos2X - 1 * deltaTime;
        currentpos3X = currentpos3X - 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_2)) {
        currentpos1Y = currentpos1Y + 1 * deltaTime;
        currentpos2Y = currentpos2Y + 1 * deltaTime;
        currentpos3Y = currentpos3Y + 1 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_3)) {
        currentpos1Y = currentpos1Y - 1 * deltaTime;
        currentpos2Y = currentpos2Y - 1 * deltaTime;
        currentpos3Y = currentpos3Y - 1 * deltaTime;
    }





}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {

        if (!isColorChanged)
            isColorChanged = true;
        else
            isColorChanged = false;

        // TODO(student): Change the values of the color components.

    }

    if (key == GLFW_KEY_B) {
        current++;
        if (current == 3) {
            current = 0;
        }
    }

    if (key == GLFW_KEY_A) {
        currentpos1X--;
        currentpos2X--;
        currentpos3X--;
    }

    if (key == GLFW_KEY_D) {
        currentpos1X++;
        currentpos2X++;
        currentpos3X++;
    }

    if (key == GLFW_KEY_W) {
        currentpos1Y--;
        currentpos2Y--;
        currentpos3Y--;
    }

    if (key == GLFW_KEY_X) {
        currentpos1Y++;
        currentpos2Y++;
        currentpos3Y++;
    }

    if (key == GLFW_KEY_C) {
        currentpos1Z++;
        currentpos2Z++;
        currentpos3Z++;
    }

    if (key == GLFW_KEY_Q) {
        currentpos1Z--;
        currentpos2Z--;
        currentpos3Z--;
    }

    if (key == GLFW_KEY_4 && !jump) {
        jump = true;
        vy = jumpPower;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
