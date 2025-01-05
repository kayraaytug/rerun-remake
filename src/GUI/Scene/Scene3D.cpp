#include "Scene3D.h"

void Scene3D::Setup()
{
    ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    Camera.fovy = 45;
    Camera.up.y = 1;
    Camera.target = {0, 0, 0};
    Camera.position = {12, 12, -12};
    DisableCursor();
}

void Scene3D::Show()
{
    if (!Open)
        return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

    if (ImGui::Begin(SCENE3D, &Open, ImGuiWindowFlags_NoScrollbar))
    {
        if (ImGui::IsWindowFocused())
            dataManager.selectedWindow = SCENE3D;
        // Get the current window content region size
        ImVec2 contentSize = ImGui::GetContentRegionAvail();
        ContentRect = {0, 0, contentSize.x, contentSize.y};

        // Check if content size has changed
        if (ContentRect.width != ViewTexture.texture.width || ContentRect.height != ViewTexture.texture.height)
        {
            // Reload render texture with new size
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture((int)ContentRect.width, (int)ContentRect.height);
        }

        // Draw the texture to fill the entire content area
        rlImGuiImageRect(&ViewTexture.texture,
                         (int)ContentRect.width,
                         (int)ContentRect.height,
                         Rectangle{0, 0, (float)ViewTexture.texture.width, (float)-ViewTexture.texture.height});
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void Scene3D::Update()
{
    if (!Open)
        return;

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        UpdateCamera(&Camera, CAMERA_FREE);
    }

    BeginTextureMode(ViewTexture);
    ClearBackground(DARKGRAY);
    DrawRectangleGradientV(0, 0, ViewTexture.texture.width, ViewTexture.texture.height,
                           Color{122, 26, 26, 120}, Color{16, 94, 30, 120});

    BeginMode3D(Camera);

    // Draw grid
    if (gridHovered)
    {
        DrawGridColored(gridSlices, gridSpacing, Vector3{0.0f, 0.9f, 0.3f});
    }
    else
    {
        DrawGridColored(gridSlices, gridSpacing, Vector3{0.75f, 0.75f, 0.75f});
    }

    // Create rotation matrices
    float angleX = rotateX * DEG2RAD;
    float angleY = rotateY * DEG2RAD;
    float angleZ = rotateZ * DEG2RAD;

    Matrix rotationX = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosf(angleX), -sinf(angleX), 0.0f,
        0.0f, sinf(angleX), cosf(angleX), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    Matrix rotationY = {
        cosf(angleY), 0.0f, sinf(angleY), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sinf(angleY), 0.0f, cosf(angleY), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    Matrix rotationZ = {
        cosf(angleZ), -sinf(angleZ), 0.0f, 0.0f,
        sinf(angleZ), cosf(angleZ), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    // Combine rotations
    Matrix rotationCombined = MatrixMultiply(rotationX, MatrixMultiply(rotationY, rotationZ));

    // Draw 3D points
    if (!dataManager.points3D.empty())
    {
        for (auto &point : dataManager.points3D)
        {
            Vector3 position = {float(point.x), float(point.y), float(point.z)};
            Vector3 transformedPosition = Vector3Transform(position, rotationCombined);

            Color pointColor = pointsHovered ? Color{0, 255, 0, 255} : Color{static_cast<unsigned char>(point.r), static_cast<unsigned char>(point.g), static_cast<unsigned char>(point.b), 255};

            DrawCube(transformedPosition, pointSize, pointSize, pointSize, pointColor);
        }
    }

    // Draw cameras
    if (!dataManager.colmapImages.empty())
    {
        for (const auto &img : dataManager.colmapImages)
        {
            Quaternion q = Quaternion{float(img.q.x()), float(img.q.y()),
                                      float(img.q.z()), float(img.q.w())};
            Matrix cameraRotation = QuaternionToMatrix(q);
            cameraRotation = MatrixMultiply(rotationCombined, cameraRotation);

            Vector3 translation = {float(img.t.x()), float(img.t.y()), float(img.t.z())};
            Vector3 cameraCenter = Vector3Transform(
                Vector3Scale(translation, -1.0f),
                MatrixTranspose(cameraRotation));

            // Draw camera cube
            if (img.idCamera == dataManager.Scene3D_CameraHoverID)
                DrawCube(cameraCenter, 0.1f, 0.1f, 0.1f, GREEN);
            else
                DrawCube(cameraCenter, 0.1f, 0.1f, 0.1f, RED);

            // Draw camera look direction
            Vector3 sceneCenter = {0.0f, 0.0f, 0.0f};
            Vector3 dirToCenter = Vector3Normalize(Vector3Subtract(sceneCenter, cameraCenter));
            DrawLine3D(cameraCenter,
                       Vector3Add(cameraCenter, Vector3Scale(dirToCenter, 0.5f)),
                       BLUE);
        }
    }

    EndMode3D();
    EndTextureMode();
}

void Scene3D::Shutdown()
{
    UnloadRenderTexture(ViewTexture);
}

void Scene3D::DrawGridColored(int slices, float spacing, Vector3 color)
{
    int halfSlices = slices / 2;

    rlBegin(RL_LINES);
    for (int i = -halfSlices; i <= halfSlices; i++)
    {
        if (i == 0)
        {
            rlColor3f(color.x, color.y, color.z);
        }
        else
        {
            rlColor3f(color.x, color.y, color.z);
        }

        rlVertex3f((float)i * spacing, 0.0f, (float)-halfSlices * spacing);
        rlVertex3f((float)i * spacing, 0.0f, (float)halfSlices * spacing);

        rlVertex3f((float)-halfSlices * spacing, 0.0f, (float)i * spacing);
        rlVertex3f((float)halfSlices * spacing, 0.0f, (float)i * spacing);
    }
    rlEnd();
}