#pragma once
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <IconsFontAwesome6.h>
#include <raylib.h>
#include <algorithm>
#include <Core/types.h>
#include <Core/utils.h>

#define SCENE2D ICON_FA_IMAGE " RGB"
#define SCENEDEPTH ICON_FA_IMAGE " Depth"

#define SCENE3D ICON_FA_MAXIMIZE " 3D"
#define TIMELINE ICON_FA_TIMELINE " Timeline"
class DataManager
{
private:
    DataManager() = default;
    DataManager(const DataManager &) = delete;
    DataManager &operator=(const DataManager &) = delete;

public:
    static DataManager &getInstance()
    {
        static DataManager instance;
        return instance;
    }

    // Shared Data
    std::vector<std::string> filePaths;
    std::vector<Texture> textures;
    std::vector<Texture> depthTextures;
    std::vector<ImageData> images;
    std::vector<ColmapCamera> cameras;
    std::vector<ColmapPoint3D> points3D;
    std::vector<ColmapImage> colmapImages;
    Model model = {0};
    
    // State
    bool Scene2D_Open = true;
    bool SceneDepth_Open = true;
    bool Scene3D_Open = true;
    bool Blueprint_Open = true;
    bool Selection_Open = true;
    bool Timeline_Open = true;
    std::string selectedWindow = "";
    std::list<std::string> openWindows = {SCENE2D, SCENE3D, TIMELINE};
    // Hover
    bool Scene3D_GridHovered = false;
    bool Scene3D_PointsHovered = false;
    int  Scene3D_CameraHoverID = -1;
    bool Scene3D_TimelineHovered = false;

    // Grid
    int   Scene3D_GridSlices = 10;
    float Scene3D_GridSpacing = 1.0f;

    // Point
    float Scene3D_PointSize = 0.005f;

    // Rotation angles (deg)
    float Scene3D_rotateX = 0.0f;
    float Scene3D_rotateY = 0.0f;
    float Scene3D_rotateZ = -90.0f;

    int Timeline_currentFrame = 0;
    int Timeline_frameMin = 0;
    int Timeline_frameMax = 100;

    // Functions
    void LoadImages(std::vector<std::string> &paths);
    void LoadImagesFolder(const std::string &folderPath);
    void LoadDepths(std::vector<std::string> &paths);
    void LoadDepthFolder(const std::string &folderPath);
    bool LoadImagesTXT(const std::string &path);
    bool LoadCamerasTXT(const std::string &path);
    bool LoadPoints3DTXT(const std::string &path);
};