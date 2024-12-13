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

void setCircleColor(Circle* object, int r, int g, int b, int alpha) {
	object->color = nvgRGBA(r, g, b, alpha);
}

void drawCircle(NVGcontext* vg, Circle* object) {
	nvgBeginPath(vg);
	nvgCircle(vg, object->xPos, object->yPos, object->radius);
	nvgFillColor(vg, object->color);
	nvgFill(vg);
	nvgClosePath(vg); // Надо ли оно тут
}

void destroy(Circle* object) {
    free(object);
}

Circle* createCircle(double xPos, double yPos, double radius, NVGcolor color) {
	Circle* circle = malloc(sizeof(Circle));
	circle->xPos = xPos;
	circle->yPos = yPos;
	circle->radius = radius;
	circle->color = color;
	return circle;
}

#endif // CIRCLE_H