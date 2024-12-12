#ifndef RECT_H
#define RECT_H

#include <nanovg.h>

#include <stdio.h>
#include <math.h>


typedef struct rect
{
	double xPos;
	double yPos;
	double radius;
	NVGcolor color;
} Rect;


int is_inside_circle(float x, float y, float rx, float ry, float width, float heigh) {
	return 1;
}

void setColor(Rect* object, int r, int g, int b, int alpha) {
	object->color = nvgRGBA(r, g, b, alpha);
}

void drawWrapper(NVGcontext* vg, Rect* object) {
	nvgBeginPath(vg);
	nvgCircle(vg, object->xPos, object->yPos, object->radius);
	nvgFillColor(vg, object->color);
	nvgFill(vg);
}

#endif // RECT_H