#ifndef LINE_H
#define LINE_H

#include <nanovg.h>

#include <stdio.h>
#include <math.h>

typedef struct line
{
	double startX;
	double startY;
	double endX;
	double endY;
	double width;
	int state;
	NVGcolor color;
} Line;

Line* createLine(double startX, double startY, double endX, 
				 double endY, double width, NVGcolor color)
{
	Line* line = malloc(sizeof(Line));
	line->startX = startX;
	line->startY = startY;
	line->endX = endX;
	line->endY = endY;
	line->width = width;
	line->color = color;
	line->state = 1;
	return line;
}

void setLineColor(Line* object, int r, int g, int b, int alpha) {
	object->color = nvgRGBA(r, g, b, alpha);
}

void drawLine(NVGcontext* vg, Line* object) {
	nvgBeginPath(vg);
    nvgMoveTo(vg, object->startX, object->startY);
    nvgLineTo(vg, object->endX, object->endY);
	nvgStrokeColor(vg, object->color);
    nvgStrokeWidth(vg, object->width);
    nvgStroke(vg);
    nvgClosePath(vg);
}

void updateStartPos(Line* object, double xPos, double yPos) {
	object->startX = xPos;
	object->startY = yPos;
}

void updateEndPos(Line* object, double xPos, double yPos) {
	object->endX = xPos;
	object->endY = yPos;
}

void dropLineState(Line* object) {
	object->state = 0;
}

#endif // LINE_H