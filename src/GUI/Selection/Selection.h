#pragma once
#include <imgui.h>
#include <Core/DataManager/DataManager.h>
#include <IconsFontAwesome6.h>
class Selection {
    private:
    DataManager &dataManager = DataManager::getInstance();
    public:
        void Show();
        void ShowScene3D();
        void ShowScene2D();
        void ShowTimeline();
        bool &Open = dataManager.Selection_Open;
};