#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

#include <stdio.h>

// Тут будут определения типов
typedef enum objectType 
{
	CIRCLE,
} ObjectType;

// Это будет массив
typedef struct object
{
	ObjectType objectType;
	void *object;
	// void (*draw)(struct Object* self);
} Object;


Object* createObject(Circle* circle) {
	Object* object = malloc(sizeof(Object));
	object->object = (void*)circle;
	object->objectType = CIRCLE;
	return object;
}

void objectDraw(NVGcontext* vg, Object* object) {
	switch (object->objectType)
	{
	case CIRCLE:
		drawWrapper(vg, (Circle*)object->object);
		break;
	
	default:
		break;
	}
}

#endif // OBJECTCONTROLLER_H