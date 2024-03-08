
#include <imgui/imgui.h>

#include "../utilities/SDLToolKit.h"

#include "ImGuiFunctions.h"

#include "Canvas.h"
#include "ImGuiRendering.h"

#include "../src/logger/Logger.h"


ImGuiRendering::ImGuiRendering()
	: canvasWidth(0),
	canvasHeight(0),
	tileSize(32),
	gridX(0),
	gridY(0) {

	canvas = std::make_shared<Canvas>(canvasWidth, canvasHeight);

	canvasPreviousWidth = 0;
	canvasPreviousHeight = 0;

	Logger::Lifecycle("ImGuiRendering Constructor Called!");
}

ImGuiRendering::~ImGuiRendering() {
	Logger::Lifecycle("ImGuiRendering Destructor Called!");
}


void ImGuiRendering::Update(SDL_Renderer& renderer) {
	ImGui::NewFrame();
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			//show file menu
			//call ShowFileMenu
			//file management
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Edit")) {
			//show edit menu
			if (ImGui::MenuItem("Undo", "CTRL + Z")) {
				//call Undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL + Y")) {
				//call Redo();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			//show view menu
			//call View();

			//if (ImGui::Checkbox("Show Grid", &grid) {
			// 
			//}
			//if (ImGui::Checkbox("Snap to Grid", &grid) {
			// 
			//}
			if (ImGui::MenuItem("Zoom In", "CTRL + +")) {

			}
			if (ImGui::MenuItem("Zoom Out", "CTRL + -")) {

			}
			if (ImGui::MenuItem("Fit to View")) {

			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Project")) {
			//show project menu

			//clamp
			//if (ImGui::InputInt("Tile Size", &tileSize, x, x)) {
			//	if (tileSize <= x) {
			//		tileSize = x;
			//}

			//if (ImGui::InputInt("Canvas Width", &canvasWidth, &tileSize, &tileSize)) {
			//	if width increase

			//clamp
			//	if (canvasWidth <= x) {
			//    canvasWidth = x;
			//	  SetWidth
			//	}
			//}

			//if (ImGui::InputInt("Canvas Height", &canvasHeight, &tileSize, &tileSize)) {
			//	if width increase

			//clamp
			//	if (canvasHeight <= x) {
			//    canvasHeight = x;
			//	  SetHeight
			//	}
			//}
		}

	}

	ImGui::EndMainMenuBar();

	
}

void ImGuiRendering::RenderGrid(SDL_Renderer& renderer) {
	//render
	//for tiles y
	//for tiles x
}


void ImGuiRendering::CreateNewCanvas() {
	//default val

	//destroy
}

void ImGuiRendering::UpdateCanvas() {
	//update val?
}