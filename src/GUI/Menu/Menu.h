#pragma once
#include <imgui.h>
#include <Core/DataManager/DataManager.h>

class Menu {
    private:
        DataManager &dataManager = DataManager::getInstance();
    public:
        void Show();
};