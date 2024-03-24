
#include <imgui/imgui.h>

#include "../utilities/SDLToolKit.h"

#include "ImGuiFunctions.h"

#include "Canvas.h"
#include "ImGuiRendering.h"

#include "../src/logger/Logger.h"


ImGuiRendering::ImGuiRendering()
	: canvasWidth(960),
	canvasHeight(640),
	canvasPreviousWidth(canvasWidth),
	canvasPreviousHeight(canvasHeight),
	tileSize(32),
	tilePrevSize(tileSize),
	createdTiles(false),
	removedTiles(false),
	gridX(0),
	gridY(0),
	gridSnap(false),
	isExit(false) {

	canvas = std::make_shared<Canvas>(canvasWidth, canvasHeight);
	mouse = std::make_shared<Mouse>();
	imguiFunctions = std::make_shared<ImGuiFunctions>(mouse);
	editManager = std::make_unique<EditManager>();

	//call ImGui setup
	imguiFunctions->InitImGui();
	imguiFunctions->Setup();

	canvasPreviousWidth = canvasWidth;
	canvasPreviousHeight = canvasHeight;

	Logger::Lifecycle("ImGuiRendering Constructor Called!");
}

ImGuiRendering::~ImGuiRendering() {
	Logger::Lifecycle("ImGuiRendering Destructor Called!");
}


void ImGuiRendering::Update(EditorRenderer& renderer, const AssetManagerPtr& assetManager, SDL_Rect& camera, SDL_Rect& mouseTile, SDL_Event& event, const float& zoom, const float& dT) {
	//start frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			imguiFunctions->ShowFileMenu(renderer, assetManager, canvas, tileSize);
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Edit")) {
			//show edit menu
			if (ImGui::MenuItem("Undo", "CTRL + Z")) {
				editManager->Undo();
			}
			if (ImGui::MenuItem("Redo", "CTRL + Y")) {
				editManager->Redo();
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

			if (ImGui::MenuItem("Tilset Window")) {
				//TODO
			}

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
			ImGui::EndMenu();

		}
		ImGui::EndMainMenuBar();

	}
	//update mouse
	mouse->MousePanCamera(renderer, camera, assetManager, dT);
	mouse->UpdateMousePosition(camera);


	SetExit(imguiFunctions->GetExit());


	//render imgui
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());


	
}

void ImGuiRendering::RenderGrid(EditorRenderer& renderer, SDL_Rect& camera, const float& zoom) {
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