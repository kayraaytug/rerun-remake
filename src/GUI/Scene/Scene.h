#pragma once
#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <rlImGui.h>
#include <rlgl.h>
#include <IconsFontAwesome6.h>

class Scene {
    public:
        bool Open = true;
        virtual void Setup();
        virtual void Show();
        virtual void Update();
        virtual void Shutdown();
};