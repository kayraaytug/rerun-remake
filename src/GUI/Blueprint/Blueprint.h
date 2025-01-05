#pragma once
#include <Core/DataManager/DataManager.h>
#include <imgui.h>
#include <string>
#include <IconsFontAwesome6.h>

class Blueprint{
private:
    DataManager &dataManager = DataManager::getInstance();

public:
    void Show();
    void AddCameras();
    void AddGrid();
    void AddImages();
    void AddColmapImages();
    void AddPoints();
    void AddTimeline();
    bool &Open = dataManager.Blueprint_Open;
    bool &gridHovered = dataManager.Scene3D_GridHovered;
    bool &pointsHovered = dataManager.Scene3D_PointsHovered;
    bool &timelineHovered = dataManager.Scene3D_TimelineHovered;
    int &gridSlices = dataManager.Scene3D_GridSlices;
    float &gridSpacing = dataManager.Scene3D_GridSpacing;
    std::list<std::string> &openWindows = dataManager.openWindows;
    std::vector<ColmapCamera> &cameras = dataManager.cameras;
    std::vector<Texture> &textures = dataManager.textures;
    std::vector<ImageData> &images = dataManager.images;
    std::vector<ColmapPoint3D> &points3D = dataManager.points3D;
    std::vector<ColmapImage> &colmapImages = dataManager.colmapImages;
};