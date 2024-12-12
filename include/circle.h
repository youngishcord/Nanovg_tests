#ifndef CIRCLE_H
#define CIRCLE_H

#include <nanovg.h>

#include <stdio.h>
#include <math.h>


typedef struct circle
{
	double xPos;
	double yPos;
	double radius;
	NVGcolor color;
} Circle;


int is_inside_circle(float x, float y, float rx, float ry, float radius) {
	return pow(x-rx, 2) + pow(y-ry, 2) < pow(radius, 2);
}

void setColor(Circle* object, int r, int g, int b, int alpha) {
	object->color = nvgRGBA(r, g, b, alpha);
}

void drawWrapper(NVGcontext* vg, Circle* object) {
	nvgBeginPath(vg);
	nvgCircle(vg, object->xPos, object->yPos, object->radius);
	nvgFillColor(vg, object->color);
	nvgFill(vg);
}

#endif // CIRCLE_H