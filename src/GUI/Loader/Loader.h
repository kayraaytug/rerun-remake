#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include <iostream>
#include <imgui.h>
#include <Core/DataManager/DataManager.h>

class Loader
{
private:
    DataManager &dataManager = DataManager::getInstance();
public:
    void Update();
};