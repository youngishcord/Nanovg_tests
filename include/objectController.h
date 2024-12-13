#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <stdio.h>

extern int drawing;
extern double mouseX;
extern double mouseY;


// Тут будут определения типов
typedef enum objectType 
{
	CIRCLE,
	LINE,
} ObjectType;

// Это будет массив
typedef struct object
{
	ObjectType objectType;
	void *object;
	// void (*draw)(struct Object* self);
} Object;


Object* createCircleObject(Circle* circle) {
	Object* object = malloc(sizeof(Object));
	object->object = (void*)circle;
	object->objectType = CIRCLE;
	return object;
}


Object* createLineObject(Line* line) {
	Object* object = malloc(sizeof(Object));
	object->object = (void*)line;
	object->objectType = LINE;
	return object;
}

void objectDraw(NVGcontext* vg, Object* object) {
	switch (object->objectType)
	{
	case CIRCLE:
		drawCircle(vg, (Circle*)object->object);
		break;
	case LINE:
		Line* line = (Line*)object->object;
		if (drawing && line->state) {
			updateEndPos(line, mouseX, mouseY);
		}
		drawLine(vg, line);
		break;
	default:
		break;
	}
}

#endif // OBJECTCONTROLLER_H