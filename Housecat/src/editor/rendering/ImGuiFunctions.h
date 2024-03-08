#pragma once

#include <string>


#include "TileAttributes.h"
#include <vector>

class ImGuiFunctions {
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

