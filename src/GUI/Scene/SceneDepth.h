#pragma once
#include "Scene.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <core/DataManager/DataManager.h>

class SceneDepth
{
private:
    DataManager &dataManager = DataManager::getInstance();
    std::vector<Texture> &textures = dataManager.depthTextures;
    int &currentFrame = dataManager.Timeline_currentFrame;

public:
    void Setup();
    void Show();
    void Update();
    void Shutdown();

    bool &Open = dataManager.SceneDepth_Open;
    Camera2D Camera = {0};
    RenderTexture2D ViewTexture;
    Texture ImageTexture;
};