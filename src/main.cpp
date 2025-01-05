#include <imgui.h>
#include <rlImGui.h>
#include <config.h>
#include <GUI/GUI.h>
#include <iostream>

int main(int argc, char *argv[])
{
	MainConfig::init();
	GUI gui;
	gui.Setup();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
		rlImGuiBegin();
		ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

		// ImGui::ShowDemoWindow();
		gui.Show();
		gui.Update();
		DrawFPS(20, 20);
		
		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();

	return 0;
}