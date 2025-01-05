#include "GUI.h"
#include "imgui.h"
#include <cstdlib>

void GUI::Setup()
{
    scene2D.Setup();
    sceneDepth.Setup();
    scene3D.Setup();
}

void GUI::Show()
{
    menu.Show();
    blueprint.Show();
    selection.Show();
    scene2D.Show();
    sceneDepth.Show();
    scene3D.Show();
    timeline.Show();
}

void GUI::Update()
{
    loader.Update();
    scene2D.Update();
    sceneDepth.Update();
    scene3D.Update();
}

void GUI::Shutdown()
{
    scene2D.Shutdown();
    sceneDepth.Shutdown();
    scene3D.Shutdown();
}