#include "EditCanvasSize.h"

#include "../rendering/Canvas.h"

EditCanvasSize::EditCanvasSize(std::shared_ptr<Canvas> canvas, int canvasPreviousWidth, int canvasPreviousHeight) 
	//reduce ref (new test)
	: canvas(std::move(canvas)),
	canvasPreviousWidth(canvasPreviousWidth),
	canvasPreviousHeight(canvasPreviousHeight) {

}

void EditCanvasSize::Execute() {

}

void EditCanvasSize::Undo() {
	//swap width
	int width = canvas->GetCanvasWidth();

	canvas->SetCanvasWidth(canvasPreviousWidth);
	canvasPreviousWidth = width;

	//swap height
	int height = canvas->GetCanvasHeight();

	canvas->SetCanvasHeight(canvasPreviousHeight);
	canvasPreviousHeight = height;
}

void EditCanvasSize::Redo() {
	//no dup
	Undo();
}

