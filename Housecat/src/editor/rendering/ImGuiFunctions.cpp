
#include <imgui.h>

#include "ImGuiFunctions.h"

#include "../utilities/SDLToolkit.h"
#include "../editmanager/EditManager.h"

ImGuiFunctions::ImGuiFunctions()
	//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	Undo(false),
	Redo(false),
	file(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	editManager(std::make_unique<EditManager>()) {
	
	//Logger::Lifecycle("ImGuiFunctions Constructor Called!");
}

ImGuiFunctions::~ImGuiFunctions() {
	//Logger::Lifecycle("ImGuiFunctions Destructor Called!");
}

//TODO
//ImGui management
void ImGuiFunctions::InitImGui() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void ImGuiFunctions::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, int& tileSize) {
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New Project", "CTRL+N")) {
			NewProject();
		}
		if (ImGui::MenuItem("Open Project", "CTRL+O")) {
			OpenProject(renderer, assetManager, canvas, tileSize);
		}
		if (ImGui::MenuItem("Save", "CTRL+S")) {
			Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);

			//TODO 
			//file management
		}
		if (ImGui::MenuItem("Exit", "ALT+F4")) {
			//EXIT
		}
		ImGui::EndMenu();
	}
}

void ImGuiFunctions::ShowEditMenu() {
	if (ImGui::BeginMenu("Edit")) {
		if (ImGui::MenuItem("Undo", "CTRL+Z")) {
			//Undo = true;
		}
		if (ImGui::MenuItem("Redo", "CTRL+Y")) {
			//Redo = true;
		}
		ImGui::EndMenu();
	}
}

void ImGuiFunctions::ShowViewMenu() {
	if (ImGui::BeginMenu("View")) {
		if (ImGui::MenuItem("Show Grid", "CTRL+G")) {
			//TODO
			//grid management
		}
		if (ImGui::MenuItem("Grid Snapping")) {
			//TODO
			
		}
		if (ImGui::MenuItem("Zoom In")) {
			//TODO
			
		}
		if (ImGui::MenuItem("Zoom Out")) {
			//TODO
			
		}
		ImGui::EndMenu();
	}
}

void ImGuiFunctions::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager) {
	if (ImGui::BeginMenu("Add Tileset")) {
		//TODO
		//file management

		
	}
	ImGui::EndMenu();
}

//TODO
//file management
void ImGuiFunctions::NewProject() {

}

void ImGuiFunctions::OpenProject(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, int& tileSize) {

}

void ImGuiFunctions::Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize) {

}

//TODO
//tileset management
void ImGuiFunctions::TileAttributes(const AssetManagerPtr& assetManager) {

}

void ImGuiFunctions::SetTileset(const AssetManagerPtr& assetManager) {

}


//TODO
//shortcut management
void ImGuiFunctions::ApplyShortcuts() {

}
