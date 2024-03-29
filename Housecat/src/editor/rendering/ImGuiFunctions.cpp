
#include <imgui.h>

#include "ImGuiFunctions.h"

#include "../utilities/SDLToolkit.h"
#include "../utilities/editmanager/EditManager.h"

ImGuiFunctions::ImGuiFunctions(class std::shared_ptr<Mouse>& mouse)
	//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	isImageLoaded(false),
	Undo(false),
	Redo(false),
	file(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	mouse(mouse),
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

void ImGuiFunctions::Setup() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void ImGuiFunctions::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, int& tileSize) {
	//MENU file interact
	if (ImGui::MenuItem("New Project", "CTRL+N")) {
		NewProject();
	}
	if (ImGui::MenuItem("Open Project", "CTRL+O")) {
		OpenProject(renderer, assetManager, canvas, tileSize);
	}
	if (ImGui::MenuItem("Save", "CTRL+S")) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}
	if (ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
	}
	if (ImGui::MenuItem("Exit", "ALT+F4")) {
		//EXIT
	}
}

void ImGuiFunctions::ShowEditMenu() {
	//MENU edit interact
	if (ImGui::MenuItem("Undo", "CTRL+Z")) {
		//Undo = true;
	}
	if (ImGui::MenuItem("Redo", "CTRL+Y")) {
		//Redo = true;
	}
}

void ImGuiFunctions::ShowViewMenu() {
	//MENU view interact
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
}

void ImGuiFunctions::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse) {
	//MENU project interact
	if (ImGui::BeginMenu("Add Map")) {
		//TODO
	}
	if (ImGui::BeginMenu("Import Tileset")) {
		//TODO
		//file management

	}
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
void ImGuiFunctions::TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect) {
	if (ImGui::Begin("Tileset"), isImageLoaded) {
		//resize on mouse scroll
		float scrollX = ImGui::GetScrollX();
		float scrollY = ImGui::GetScrollY();
		int imageWidth = textureWidth * 2;
		int imageHeight = textureHeight;

		ImGui::Image(assetManager->GetTexture(assetID), ImVec2(imageWidth, imageHeight));

		int mousePosX = static_cast<int>(ImGui::GetMousePos().x - ImGui::GetWindowPos().x + scrollX);
		int mousePosY = static_cast<int>(ImGui::GetMousePos().y - ImGui::GetWindowPos().y + scrollY);

		int tileCol = imageWidth / (mouseRect.x * 2);
		int tileRow = imageHeight / (mouseRect.y * 2);

		//store highlighted tiles
		auto highlightTiles = ImGui::GetWindowDrawList();

		//render tileset textures
		for (int c = 0; c < tileCol; c++) {
			for (int r = 0; r < tileRow; r++) {
				// Calculate tile boundaries
				int tileAX = (imageWidth / tileCol) * c;
				int tileAY = (imageHeight / tileRow) * r;
				int tileBX = tileAX + (imageWidth / tileCol);
				int tileBY = tileAX + (imageHeight / tileRow);

				//wihtin tile area
				if (mousePosX >= tileAX && mousePosX <= tileBX && mousePosY >= tileAY && mousePosY <= tileBY) {
					//highlight blueish
					highlightTiles->AddRectFilled(ImVec2(tileAX, tileAY), ImVec2(tileBX, tileBY), IM_COL32(0, 0, 255, 100));

					if (ImGui::IsMouseClicked(0)) {
						tileAttributes.srcRectX = c * (int)mouseRect.x * 2;
						tileAttributes.srcRectY = r * (int)mouseRect.y * 2;
					}
				}
			}
		}			
	}
}

void ImGuiFunctions::TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse) {
	//tile attributes interact
	if (ImGui::BeginMenu("Tilesets")) {
		//multiple tilesets
	}
	if (ImGui::BeginMenu("Transform")) {
		//scale
	}
	if (ImGui::BeginMenu("Sprite")) {
		//mouse x mouse y

	}
}

void ImGuiFunctions::TilesetLayers(const AssetManagerPtr& assetManager) {
	//layers interact
	if (ImGui::BeginMenu("Layer")) {

	}
}








//TODO
//shortcut management
void ImGuiFunctions::ApplyShortcuts() {

}
