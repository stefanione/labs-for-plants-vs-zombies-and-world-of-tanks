#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;

float color = 0;
float x_pos, y_pos, z_pos, y_pos_s;
float bounce = 0, p = 1, cunt = 0;
char* object = "box";


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

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.
    
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
        Mesh* quad = new Mesh("quad");
        quad->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
        meshes[quad->GetMeshID()] = quad;

    }

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    float blue = 0.0f;
    float red = 0.0f;
    float green = 0.0f;
   
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    // glClearColor(0, 0, 0, 1);
    //glClearColor(red, color/2, color/2, 1); -> turcoaz dar nu genul care iti scoate ochii
    glClearColor(color/2, green, color/2, 1); // purple dar nu genul care iti scoate ochii

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
    RenderMesh(meshes["teapot"], glm::vec3(x_pos, y_pos, z_pos), glm::vec3(0.5f));
    
    
    RenderMesh(meshes["sphere"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
    RenderMesh(meshes["quad"], glm::vec3(-1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["sphere"], glm::vec3(3, 0.5f, 0));
    RenderMesh(meshes[object], glm::vec3(5, 0.5f, 0), glm::vec3(0.3f, 0.3f, 0.3f));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    /*if (p == 2) {
        if (y_pos_s <= 2) {
            y_pos_s += 0.5f * deltaTimeSeconds;
        }
        else {
            p--;
        }
    }
    else if (p == 1) {
        if (y_pos_s >= 0) {
            y_pos_s += (-0.5f) * deltaTimeSeconds;
        }  
    }*/

    if (p == 2) {
        if (y_pos <= 2) {
            y_pos += 0.5f * deltaTimeSeconds;
        }
        else {
            p--;
        }
    }
    else if (p == 1) {
        if (y_pos >= 0) {
            y_pos += (-0.5f) * deltaTimeSeconds;
        }
    }
}


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
    bounce = deltaTime;

    if (window->KeyHold(GLFW_KEY_W) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        z_pos += (-0.5f) * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        x_pos += (-0.5f) * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        z_pos += 0.5f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        x_pos += 0.5f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_E) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        y_pos += 0.5f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_Q) && (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
        y_pos += (-0.5f) * deltaTime;
    }

    
    
}

void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        color = 1;
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    if (key == GLFW_KEY_G) {
        if (strcmp(object, "box") == 0) {
            object = "teapot";
        } else if (strcmp(object, "teapot") == 0) {
            object = "sphere";
        }
        else if (strcmp(object, "sphere") == 0) {
            object = "box";
        }

    }
    
    if (key == GLFW_KEY_B) {
        p = 2;
    }

    

    
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



