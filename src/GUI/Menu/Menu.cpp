#include "Menu.h"

void Menu::Show()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New Project", nullptr, nullptr, true));
            if(ImGui::MenuItem("Open...", nullptr, nullptr, true));
            if(ImGui::MenuItem("Save", nullptr, nullptr, true));
            if(ImGui::MenuItem("Save as", nullptr, nullptr, true));
            if(ImGui::MenuItem("Quit", nullptr, nullptr, true)) exit(0);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::EndMenu();
        }
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Blueprint", nullptr, dataManager.Blueprint_Open, true)) dataManager.Blueprint_Open = !dataManager.Blueprint_Open;
            if (ImGui::MenuItem("Selection", nullptr, dataManager.Selection_Open, true)) dataManager.Selection_Open = !dataManager.Selection_Open;
            if (ImGui::MenuItem("Scene3D", nullptr, dataManager.Scene3D_Open, true)) dataManager.Scene3D_Open = !dataManager.Scene3D_Open;
            if (ImGui::MenuItem("Scene2D", nullptr, dataManager.Scene2D_Open, true)) dataManager.Scene2D_Open = !dataManager.Scene2D_Open;
            if (ImGui::MenuItem("Timeline", nullptr, dataManager.Timeline_Open, true)) dataManager.Timeline_Open = !dataManager.Timeline_Open;
            
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}