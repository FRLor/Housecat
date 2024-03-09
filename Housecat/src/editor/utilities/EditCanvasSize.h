#pragma once

#include "./editmanager/EditManager.h"

class EditCanvasSize: public IEdit {
private:
	int canvasPreviousWidth;
	int canvasPreviousHeight;

	std::shared_ptr<class Canvas> canvas;

public:
	EditCanvasSize(std::shared_ptr<Canvas> canvas, int canvasPreviousWidth, int canvasPreviousHeight);
	~EditCanvasSize() = default;

	void Execute() override;
	void Undo() override;
	void Redo() override;

	EditCanvasSize(const EditCanvasSize&) = delete;
	EditCanvasSize& operator=(const EditCanvasSize&) = delete;
};

