
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
	gridSnap(true),
	gridShow(true),
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
	//calc full tiles in canvas
	int xTiles = canvas->GetCanvasWidth() / tileSize;
	int yTiles = canvas->GetCanvasHeight() / tileSize;


	if (gridShow) {

		SDL_SetRenderDrawColor(renderer.get(), 140, 140, 140, SDL_ALPHA_OPAQUE);

		//vertical
		for (int i = 0; i <= xTiles; i++) {
			int x = std::floor(i * tileSize * zoom) - camera.x;
			SDL_RenderDrawLine(renderer.get(), x, 0 - camera.y, x, (yTiles * tileSize * zoom) - camera.y);
		}

		//horizontal
		for (int j = 0; j <= yTiles; j++) {
			int y = std::floor(j * tileSize * zoom) - camera.y;
			SDL_RenderDrawLine(renderer.get(), 0 - camera.x, y, (xTiles * tileSize * zoom) - camera.x, y);
		}
	}

	//boundary
	SDL_SetRenderDrawColor(renderer.get(), 37, 39, 41, SDL_ALPHA_OPAQUE);
	SDL_Rect boundaryRect = { 0 - camera.x, 0 - camera.y, xTiles * tileSize * zoom, yTiles * tileSize * zoom };
	SDL_RenderDrawRect(renderer.get(), &boundaryRect);
}


void ImGuiRendering::CreateNewCanvas() {
	//default val

	//destroy
}

void ImGuiRendering::UpdateCanvas() {
	//update val?
}