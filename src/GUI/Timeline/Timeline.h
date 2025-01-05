#include <imgui.h>
#include <vector>
#include <Core/DataManager/DataManager.h>
#include <IconsFontAwesome6.h>

class Timeline
{
private:
    DataManager &dataManager = DataManager::getInstance();
    bool &Open = dataManager.Timeline_Open;
    std::vector<Texture> &textures = dataManager.textures;
    int &frameMin = dataManager.Timeline_frameMin;
    int &frameMax = dataManager.Timeline_frameMax;
    int &currentFrame = dataManager.Timeline_currentFrame;
    float frameWidth = 10.0f;

public:
    void Show()
    {
        if (!Open)
            return;
        ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
        ImGui::Begin(TIMELINE, &Open);
        if (ImGui::IsWindowFocused()) dataManager.selectedWindow = TIMELINE;

        // Get drawing context
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();

        // Dynamically set the frameWidth to fit all frames within the content region
        int totalFrames = frameMax - frameMin + 1;
        frameWidth = canvas_size.x / totalFrames;

        // Background
        draw_list->AddRectFilled(
            canvas_pos,
            ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
            IM_COL32(20, 24, 25, 255));

        // Frame numbers and lines
        for (int i = frameMin; i <= frameMax; i += 10)
        {
            float x = canvas_pos.x + (i - frameMin) * frameWidth;
            // Vertical line
            draw_list->AddLine(
                ImVec2(x, canvas_pos.y),
                ImVec2(x, canvas_pos.y + canvas_size.y),
                IM_COL32(60, 60, 60, 255));

            // Frame number
            char tmps[32];
            sprintf(tmps, "%d", i);
            draw_list->AddText(
                ImVec2(x + 3, canvas_pos.y),
                IM_COL32(255, 255, 255, 255),
                tmps);
        }

        // Current frame marker
        if (currentFrame >= frameMin && currentFrame <= frameMax)
        {
            float x = canvas_pos.x + (currentFrame - frameMin) * frameWidth;
            draw_list->AddLine(
                ImVec2(x, canvas_pos.y),
                ImVec2(x, canvas_pos.y + canvas_size.y),
                IM_COL32(255, 255, 255, 255),
                2.0f);
        }

        // Draw events
        for (size_t i = 0; i < textures.size(); i++)
        {
            float start_x = canvas_pos.x + (i - frameMin) * frameWidth;

            // Event circle
            ImU32 color = IM_COL32(220, 220, 220, 255);
            ImU32 colorHovered = IM_COL32(0, 255, 0, 255);
            if (i == dataManager.Scene3D_CameraHoverID)
                draw_list->AddNgonFilled(
                ImVec2(start_x, canvas_pos.y + canvas_size.y * 0.5),
                5.0,
                colorHovered,
                4);
            else
            draw_list->AddNgonFilled(
                ImVec2(start_x, canvas_pos.y + canvas_size.y * 0.5),
                5.0,
                color,
                4);
        }

        // Make the widget interactive
        canvas_size.x -= 10;
        canvas_size.y -= 10;
        ImGui::InvisibleButton("canvas", canvas_size);

        // Handle mouse interactions
        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

            if (ImGui::IsMouseDown(0))
            {
                ImVec2 mouse_pos = ImGui::GetMousePos();
                float relative_x = mouse_pos.x - canvas_pos.x;
                int new_frame = frameMin + static_cast<int>(relative_x / frameWidth);
                currentFrame = std::max(frameMin, std::min(frameMax, new_frame));
                dataManager.Scene3D_CameraHoverID = currentFrame;
            }
        }

        ImGui::End();
    }

    // Getters and setters
    void SetFrameRange(int min, int max)
    {
        frameMin = min;
        frameMax = max;
    }
    void SetFrameWidth(float width) { frameWidth = width; }
};
