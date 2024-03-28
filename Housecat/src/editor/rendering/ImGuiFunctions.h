#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileAttributes.h"
#include "Canvas.h"

#include "../utilities/SDLToolKit.h"
#include "../utilities/editmanager/EditManager.h"
#include "../utilities/mouse/Mouse.h"
#include "../utilities/FileDialogue.h"
#include "../utilities/ProjectManagement.h"


#include "../../ecs/ECS.h"
#include "../../assetmanager/AssetManager.h"

class ImGuiFunctions: public System {
private:
	//tile
	TileAttributes tileAttributes;
	TileAttributes tilePrevAttributes;
	int tileWidth;
	int tileHeight;
	int textureWidth;
	int textureHeight;

	bool loadTileset;
	bool isNewFile;
	bool tilesetLoaded;


	//edit
	bool Undo;
	bool Redo;

	//exit
	bool isExit;

	//project
	std::string fileName;
	std::string assetID;
	std::string imageName;
	std::string luaFile;



	//tilesets
	std::vector<std::string> tilesets;
	std::vector<std::string> tilesetsTarget;

	std::unique_ptr<class FileDialogue> fileDialog;
	std::unique_ptr<class ProjectManagement> projectManagement;

	std::unique_ptr<class EditManager> editManager;

	std::shared_ptr<class Mouse> mouse;

public:
	ImGuiFunctions(class std::shared_ptr<Mouse>& mouse);
	~ImGuiFunctions();
	
	//TODO
	//ImGui
	void InitImGui();

	void Setup();

	//TODO
	//project management
	void ShowFileMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, sol::state& lua, int& tileSize);

	void ShowEditMenu();

	void ShowViewMenu();

	void ShowProjectMenu(EditorRenderer& renderer, const AssetManagerPtr& assetManager);

	//TODO
	//file management
	void NewProject();

	void Open(EditorRenderer& renderer, const AssetManagerPtr& assetManager, std::shared_ptr<Canvas>& canvas, sol::state& lua, int& tileSize);

	void Save(EditorRenderer& renderer, const AssetManagerPtr& assetManager, const int& canvasWidth, const int& canvasHeight, int& tileSize);

	//TODO
	//tileset management
	void TilesetWindow(const AssetManagerPtr& assetManager, const glm::vec2& mouseRect);

	void TilesetLayers(const AssetManagerPtr& assetManager);

	void TileAttributes(const AssetManagerPtr& assetManager, std::shared_ptr<class Mouse>& mouse);


	//TODO
	//shortcut management
	void ApplyShortcuts();

	//exit
	const bool& GetExit() const {
		return isExit;
	}
};

