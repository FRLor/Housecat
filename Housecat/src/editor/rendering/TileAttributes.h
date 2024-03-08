#pragma once

#include <glm/glm.hpp>

struct TileAttributes {
	int tileWidth;
	int tileHeight;
	int scaleX;
	int scaleY;
	glm::vec2 tileOffset;

	//TODO
	//animated tiles
	//int numFrames;
	//int frameSpeed;

	//bool isLooped;

	TileAttributes(int tileWidth = 0, int tileHeight = 0, int scaleX = 1, int scaleY = 1, glm::vec2 tileOffset = { 0, 0 }) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->tileOffset = tileOffset;
	}	

	~TileAttributes() = default;	
};