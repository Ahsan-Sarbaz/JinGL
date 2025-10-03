#pragma once

#include "imgui/imgui.h"
#include "Platform.h"

/**
* Initializes ImGui
* 
*/
void InitImGui(const Window* window);

/**
* Starts a new ImGui frame
*/
void StartImGuiFrame();

/**
* Ends the current ImGui frame
*/
void EndImGuiFrame();

/**
* Shuts down ImGui
*/
void ShutdownImGui();

