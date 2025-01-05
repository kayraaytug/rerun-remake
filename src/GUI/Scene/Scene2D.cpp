#include "Scene2D.h"

void Scene2D::Setup()
{
    Camera.zoom = 1;
    Camera.target = {0, 0};
    Camera.rotation = 0;
    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    ImageTexture = {0};
}

void Scene2D::Show()
{
    if (!Open)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

    if (ImGui::Begin(SCENE2D, &Open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {
        if (ImGui::IsWindowFocused()) dataManager.selectedWindow = SCENE2D;
        if (!textures.empty())
        {
            ImageTexture = textures[currentFrame];

            ImVec2 size = ImGui::GetContentRegionAvail();

            float textureWidth = (float)ImageTexture.width;
            float textureHeight = (float)ImageTexture.height;
            float textureAspect = textureWidth / textureHeight;
            float contentAspect = size.x / size.y;
            float drawWidth, drawHeight;

            if (contentAspect > textureAspect)
            {
                drawHeight = size.y;
                drawWidth = drawHeight * textureAspect;
            }
            else
            {
                drawWidth = size.x;
                drawHeight = drawWidth / textureAspect;
            }

            ImVec2 position = ImGui::GetCursorScreenPos();
            float offsetX = (size.x - drawWidth) / 2.0f;
            float offsetY = (size.y - drawHeight) / 2.0f;
            ImGui::SetCursorScreenPos(ImVec2(position.x + offsetX, position.y + offsetY));

            rlImGuiImageRect(&ImageTexture, (int)drawWidth, (int)drawHeight, {0, 0, textureWidth, textureHeight});
        }
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void Scene2D::Update()
{
    if (!Open)
        return;

    if (IsWindowResized())
    {
        UnloadRenderTexture(ViewTexture);
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }
}

void Scene2D::Shutdown()
{
    UnloadRenderTexture(ViewTexture);
}