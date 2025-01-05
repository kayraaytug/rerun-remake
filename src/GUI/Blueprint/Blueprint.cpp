#include "Blueprint.h"
#include <iostream>

void Blueprint::Show()
{
    if (!Open)
        return;
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
    ImGui::Begin(ICON_FA_LIST " Blueprint", &Open);

    // Create the table with 1 column
    if (ImGui::BeginTable("HoverEventTable", 1))
    {

        for (auto &window : openWindows)
        {
            ImGui::TableNextRow();    // Advance to the next row
            ImGui::TableNextColumn(); // Move to the first column

            // Create a tree node for each row
            bool isExpanded = ImGui::TreeNode(window.c_str());

            // Check if the tree node expander is hovered
            // if (ImGui::IsItemHovered())
            // {
            //     ImGui::SetWindowFocus(window.c_str());
            // }
            if (isExpanded)
            {
                if (window == SCENE2D)
                {
                    AddImages();
                }
                if (window == SCENE3D)
                {
                    AddGrid();
                    AddCameras();
                    AddPoints();
                }
                if (window == TIMELINE)
                {
                    AddTimeline();
                }
                ImGui::TreePop();
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void Blueprint::AddImages()
{
    if (images.empty())
        return;
    if (ImGui::TreeNode(ICON_FA_IMAGE " Images")) // Ensure TreeNode is properly opened
    {
        for (int i = 0; i < images.size(); i++)
        {
            ImGui::PushID(i); // Unique ID for each camera in the loop

            // Use TreeNode for expandability
            if (ImGui::TreeNode((std::string(ICON_FA_IMAGE) + " " + images[i].fileName + "##" + std::to_string(i)).c_str()))
            {
                ImGui::Text("Path: %s", images[i].path.c_str());
                ImGui::Text("Resolution: %ux%u", images[i].width, images[i].height);
                ImGui::Text("Mipmaps: %u", images[i].mipmaps);

                ImGui::TreePop(); // Close TreeNode for this image
            }
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}

void Blueprint::AddColmapImages()
{
    if (colmapImages.empty())
        return;

    if (ImGui::TreeNode(ICON_FA_IMAGE " ColmapImages")) // Ensure TreeNode is properly opened
    {
        for (int i = 0; i < colmapImages.size(); i++)
        {
            ImGui::PushID(i); // Unique ID for each image in the loop
            if (ImGui::IsItemHovered())
            {
                dataManager.Scene3D_CameraHoverID = colmapImages[i].idCamera;
            }
            // Use TreeNode for expandability
            if (ImGui::TreeNode((std::string(ICON_FA_IMAGE) + " " + colmapImages[i].fileName + "##" + std::to_string(i)).c_str()))
            {
                // Display basic information
                ImGui::Text("File Name: %s", colmapImages[i].fileName.c_str());
                ImGui::Text("ID: %u", colmapImages[i].ID);
                ImGui::Text("Camera ID: %u", colmapImages[i].idCamera);

                // Display rotation quaternion
                ImGui::Text("Rotation (Quaternion): [%.3f, %.3f, %.3f, %.3f]",
                            colmapImages[i].q.w(), colmapImages[i].q.x(), colmapImages[i].q.y(), colmapImages[i].q.z());

                // Display translation vector
                ImGui::Text("Translation: [%.3f, %.3f, %.3f]",
                            colmapImages[i].t.x(), colmapImages[i].t.y(), colmapImages[i].t.z());

                // Display projections if any
                if (!colmapImages[i].projs.empty())
                {
                    if (ImGui::TreeNode("Projections"))
                    {
                        for (int j = 0; j < colmapImages[i].projs.size(); j++)
                        {
                            ImGui::PushID(j);
                            ImGui::Text("Projection %d:", j);
                            ImGui::Text("  Point ID: %u", colmapImages[i].projs[j].idPoint);
                            ImGui::Text("  Coordinates: [%.3f, %.3f]",
                                        colmapImages[i].projs[j].p.x(), colmapImages[i].projs[j].p.y());
                            ImGui::PopID();
                        }
                        ImGui::TreePop();
                    }
                }
                else
                {
                    ImGui::Text("No Projections");
                }

                ImGui::TreePop(); // Close TreeNode for this image
            }
            ImGui::PopID(); // Pop the ID for this image
        }
        ImGui::TreePop(); // Close TreeNode for "ColmapImages"
    }
}

void Blueprint::AddGrid()
{
    bool isHovered = false;

    // Check hover status before opening the TreeNode
    if (ImGui::TreeNode(ICON_FA_TABLE_CELLS " Grid"))
    {
        ImGui::SliderInt("Slices", &gridSlices, 1, 100, "%d");
        ImGui::SliderFloat("Spacing", &gridSpacing, 0, 2, "%.2f");

        ImGui::TreePop();
    }
    isHovered = ImGui::IsItemHovered();

    if (isHovered)
        gridHovered = true;
    else
        gridHovered = false;
}

void Blueprint::AddCameras()
{
    if (cameras.empty() || colmapImages.empty())
        return;
    if (ImGui::TreeNode(ICON_FA_CAMERA " Cameras")) // Ensure TreeNode is properly opened
    {
        for (int i = 0; i < cameras.size(); i++)
        {
            ImGui::PushID(i); // Unique ID for each camera in the loop
            if (ImGui::IsItemHovered())
            {
                dataManager.Scene3D_CameraHoverID = colmapImages[i].idCamera;
            }
            // Use TreeNode for expandability
            if (ImGui::TreeNode((std::string(ICON_FA_CAMERA) + " Camera " + std::to_string(i)).c_str()))
            {
                ImGui::Text("ID: %u", cameras[i].ID);
                ImGui::Text("Model: %s", cameras[i].model.c_str());
                ImGui::Text("Resolution: %ux%u", cameras[i].width, cameras[i].height);
                ImGui::Text("Focal Length: %.2f", cameras[i].f);
                ImGui::Text("Principal Point: (%.2f, %.2f)", cameras[i].cx, cameras[i].cy);
                ImGui::Text("Distortion Coefficient: %.2f", cameras[i].k);
                ImGui::Text("Rotation (Quaternion): [%.3f, %.3f, %.3f, %.3f]",
                            colmapImages[i].q.w(), colmapImages[i].q.x(), colmapImages[i].q.y(), colmapImages[i].q.z());
                ImGui::Text("Translation: [%.3f, %.3f, %.3f]",
                            colmapImages[i].t.x(), colmapImages[i].t.y(), colmapImages[i].t.z());

                ImGui::TreePop(); // Close TreeNode for this camera
            }

            ImGui::PopID(); // Pop the ID for this camera
        }
        ImGui::TreePop(); // Close TreeNode for "Cameras"
    }
}

void Blueprint::AddPoints()
{
    bool isHovered = false;
    if (points3D.empty())
        return;

    if (ImGui::TreeNode(ICON_FA_CIRCLE " Points3D")) // Ensure TreeNode is properly opened
    {
        ImGui::Text("Points: %zu", points3D.size());
        ImGui::TreePop(); // Close TreeNode for "Cameras"
    }

    isHovered = ImGui::IsItemHovered();

    if (isHovered)
        pointsHovered = true;
    else
        pointsHovered = false;
}

void Blueprint::AddTimeline()
{
    bool isHovered = false;

    for (int i = 0; i < images.size(); i++)
    {
        ImGui::PushID(i); // Unique ID for each camera in the loop
        if (ImGui::IsItemHovered())
        {
            dataManager.Scene3D_CameraHoverID = i;
        }

        // Use TreeNode for expandability
        if (ImGui::TreeNode((std::string(ICON_FA_IMAGE) + " " + images[i].fileName + "##" + std::to_string(i)).c_str()))
        {
            ImGui::Text("Path: %s", images[i].path.c_str());
            ImGui::Text("Resolution: %ux%u", images[i].width, images[i].height);
            ImGui::Text("Mipmaps: %u", images[i].mipmaps);

            ImGui::TreePop(); // Close TreeNode for this image
        }
        ImGui::PopID();
    }

    isHovered = ImGui::IsItemHovered();

    if (isHovered)
        timelineHovered = true;
    else
        timelineHovered = false;
}