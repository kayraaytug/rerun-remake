#include "Selection.h"

void Selection::Show()
{
    if(!Open) return;
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
    if (ImGui::Begin(ICON_FA_I_CURSOR "Selection", &Open))
    {
        static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
        if (ImGui::BeginTable("Selectiontable", 1, flags))
        {
            ImGui::TableSetupColumn(dataManager.selectedWindow.c_str(), ImGuiTableColumnFlags_NoHide);
            ImGui::TableHeadersRow();
            
            if (dataManager.selectedWindow == SCENE2D){
                
                ShowScene2D();
            }

            else if (dataManager.selectedWindow == SCENE3D){
                
                ShowScene3D();
            }


        }
        ImGui::EndTable();
    }
    ImGui::End();
}

void Selection::ShowScene2D(){
    int &frame = dataManager.Timeline_currentFrame;
    if (dataManager.images.empty())
        return;
    ImGui::Text("Filename: %s", dataManager.images[frame].fileName.c_str());
    ImGui::Text("Path: %s", dataManager.images[frame].path.c_str());
    ImGui::Text("Resolution: %ux%u", dataManager.images[frame].width, dataManager.images[frame].height);
    ImGui::Text("Mipmaps: %u", dataManager.images[frame].mipmaps);
}

void Selection::ShowScene3D(){
    ImGui::SliderFloat("X", &dataManager.Scene3D_rotateX, -180, 180, "%.2f");
    ImGui::SliderFloat("Y", &dataManager.Scene3D_rotateY, -180, 180, "%.2f");
    ImGui::SliderFloat("Z", &dataManager.Scene3D_rotateZ, -180, 180, "%.2f");
    ImGui::SliderInt("Slices", &dataManager.Scene3D_GridSlices, 1, 100, "%d");
    ImGui::SliderFloat("Spacing", &dataManager.Scene3D_GridSpacing, 0, 2, "%.2f");
}

void Selection::ShowTimeline(){

}