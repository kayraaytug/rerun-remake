#pragma once
#include "Scene.h"
#include <core/DataManager/DataManager.h>
class Scene3D {
private:
    DataManager &dataManager = DataManager::getInstance();
    Rectangle ContentRect = {0};
    RenderTexture ViewTexture = {0};
    Texture2D GridTexture = { 0 };
    Camera3D Camera = {0};

public:
    void Setup();
    void Show();
    void Update();
    void Shutdown();
    void DrawGridColored(int slices, float spacing, Vector3 color);
    bool &Open = dataManager.Scene3D_Open;
    float &gridSpacing = dataManager.Scene3D_GridSpacing;
    int &gridSlices = dataManager.Scene3D_GridSlices;
    bool &gridHovered = dataManager.Scene3D_GridHovered;
    bool &pointsHovered = dataManager.Scene3D_PointsHovered;
    float &pointSize = dataManager.Scene3D_PointSize;
    float &rotateX = dataManager.Scene3D_rotateX;
    float &rotateY = dataManager.Scene3D_rotateY;
    float &rotateZ = dataManager.Scene3D_rotateZ;
};