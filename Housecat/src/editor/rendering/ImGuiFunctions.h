#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TileAttributes.h"

#include "../../ecs/ECS.h"

#include "../editmanager/EditManager.h"

class ImGuiFunctions: public System {
private:
	//tile
	TileAttributes tileAttributes;
	int tileWidth;
	int tileHeight;
	int textureWidth;
	int textureHeight;

	//project
	std::string file;
	std::string assetID;

	//tilesets
	std::vector<std::string> tilesets;
	std::vector<std::string> tilesetsTarget;

	std::unique_ptr<class EditManager> editManager;


public:
	ImGuiFunctions();
	~ImGuiFunctions();

	//TODO
	//project management
	void ShowFileMenu();

	void ShowToolsMenu();

	//TODO
	//file management
	void NewProject();

	void OpenProject();

	void Save();

	//TODO
	//shortcut management
	void ApplyShortcuts();
};

