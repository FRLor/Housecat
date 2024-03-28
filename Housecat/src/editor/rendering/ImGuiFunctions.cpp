
#include <imgui.h>

#include "ImGuiFunctions.h"

#include "../utilities/SDLToolkit.h"
#include "../utilities/editmanager/EditManager.h"
#include <sol/sol.hpp>

ImGuiFunctions::ImGuiFunctions(class std::shared_ptr<Mouse>& mouse)
	//int tileWidth, tileHeight, scaleX, scaleY, layer, tileOffset, srcRectX, srcRectY
	: tileAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tilePrevAttributes{ 16, 16, 1, 1, 0, {0, 0}, 0, 0 },
	tileWidth(16),
	tileHeight(16),
	textureWidth(0),
	textureHeight(0),
	loadTileset(false),
	isNewFile(false),
	tilesetLoaded(false),
	newCanvas(false),
	isReset(false),
	Undo(false),
	Redo(false),
	isExit(false),
	fileName(""),
	assetID(""),
	tilesets(),
	tilesetsTarget(),
	mouse(mouse),
	editManager(std::make_unique<EditManager>()),
	fileDialog(std::make_unique<FileDialogue>()),
	projectManagement(std::make_unique<ProjectManagement>()) {
	
	//Logger::Lifecycle("ImGuiFunctions Constructor Called!");
}

ImGuiFunctions::~ImGuiFunctions() {
	//Logger::Lifecycle("ImGuiFunctions Destructor Called!");
}

//TODO
//ImGui management
void ImGuiFunctions::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& IO = ImGui::GetIO(); (void)IO;
}

void ImGuiFunctions::Setup() {
	//TODO
	//ImGui
}

//TODO
//menu bar management
void ImGuiFunctions::ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, sol::state& lua, int& tileSize) {
//MENU file interact
	if (ImGui::MenuItem("New Project", "CTRL+N")) {
		isNewFile = true;
	}
	if (ImGui::MenuItem("Open", "CTRL+O")) {
		Open(renderer, assetManager, canvas, lua, tileSize);
	}
	if (ImGui::MenuItem("Save", "CTRL+S")) {
		Save(renderer, assetManager, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}
	if (ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
		//TODO
		//file management
		std::string file = fileDialog->SaveFile();

		if (file == "") {
			return;
		}
		fileName = file;
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvas->GetCanvasWidth(), canvas->GetCanvasHeight(), tileSize);
	}

	if (ImGui::MenuItem("Export to Lua Table")) {
		std::string file = fileDialog->SaveFile();

		if (file == "") {
			// Set Lua file to the selected filename
			return;
		}
		luaFile = file;
		projectManagement->SaveAsLua(luaFile, tilesets, tilesetsTarget, tileSize);
	}

	if (ImGui::MenuItem("Exit", "ESC")) {
		isExit = true;
	}
}

//MOVE TO ImGuiRendering
//void ImGuiFunctions::ShowEditMenu() {
//	//MENU edit interact
//	if (ImGui::MenuItem("Undo", "CTRL+Z")) {
//		//Undo = true;
//	}
//	if (ImGui::MenuItem("Redo", "CTRL+Y")) {
//		//Redo = true;
//	}
//}

//MOVE TO ImGuiRendering
//void ImGuiFunctions::ShowViewMenu() {
//	//MENU view interact
//	if (ImGui::MenuItem("Show Grid", "CTRL+G")) {
//		//TODO
//		//grid management
//	}
//	if (ImGui::MenuItem("Grid Snapping")) {
//		//TODO
//			
//	}
//	if (ImGui::MenuItem("Zoom In")) {
//		//TODO
//			
//	}
//	if (ImGui::MenuItem("Zoom Out")) {
//		//TODO
//			
//	}
//}

void ImGuiFunctions::ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager) {

	if (ImGui::MenuItem("Add Tileset")) {
		FileDialogue fileDialog;
		imageName = fileDialog.OpenTextureFile();

		if (imageName.empty()) {
			return;
		}

		std::filesystem::path path(imageName);
		assetID = path.stem().string();

		for (const auto& assets : tilesets) {
			if (assets == assetID) {
				return;
			}
		}

		assetManager->AddEditorTexture(renderer, assetID, imageName);

		if (SDL_QueryTexture(assetManager->ReturnEditorTexture(assetID).get(), NULL, NULL, &textureWidth, &textureHeight) != 0) {
			const char* error = SDL_GetError();
			loadTileset = false;
		}
		else {
			loadTileset = true;
			tilesets.push_back(assetID);
			tilesetsTarget.push_back(imageName);
			tilesetLoaded = true;
		}

	}
}

//TODO
//file management
void ImGuiFunctions::NewProject() {

}

void ImGuiFunctions::Open(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, sol::state& lua, int& tileSize) {
	fileName = fileDialog->OpenFile();

	if (fileName == "") {
		return;
	}
	projectManagement->OpenProject(lua, fileName, renderer, canvas, assetManager, tilesets, tilesetsTarget, tileSize);
}

void ImGuiFunctions::Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize) {
	if (fileName == "") {
		fileName = fileDialog->SaveFile();

		if (fileName == "") {
			return;
		}
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvasWidth, canvasHeight, tileSize);
	}
	else {
		projectManagement->SaveProject(fileName, tilesets, tilesetsTarget, canvasWidth, canvasHeight, tileSize);
	}
}

//TODO
//tileset management
void ImGuiFunctions::TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect) {
	if (ImGui::Begin("Tileset"), &loadTileset) {
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
	ImGui::End();
}

void ImGuiFunctions::TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse) {
	//tile attributes interact
	//if (ImGui::BeginMenu("Tilesets")) {
	//	//multiple tilesets
	//}
	//if (ImGui::BeginMenu("Transform")) {
	//	//scale
	//}
	//if (ImGui::BeginMenu("Sprite")) {
	//	//mouse x mouse y

	//}
	//ImGui::End();

}

void ImGuiFunctions::TilesetLayers(const AssetManagerPtr& assetManager) {
	//layers interact
	/*if (ImGui::BeginMenu("Layer")) {

	}
	ImGui::End();*/
}



void ImGuiFunctions::OpenNewWindow() {
	if (!isNewFile) {
		return;
	}

	if (ImGui::Begin("New Canvas")) {
		ImGui::Text("Are you sure?");
		ImGui::Spacing();

		if (ImGui::Button("Yes")) {
			newCanvas = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("No")) {
			isNewFile = false;
		}
		ImGui::End();
	}

	if (newCanvas) {
		ResetLoadedFiles();
		isNewFile = false;
		newCanvas = false;
	}
}

void ImGuiFunctions::ResetLoadedFiles() {
	fileName = "";
	assetID = "";
	imageName = "";
	loadTileset = false;
	tilesets.clear();
	tilesetsTarget.clear();
	isReset = true;
}





//TODO
//shortcut management
void ImGuiFunctions::ApplyShortcuts() {

}
