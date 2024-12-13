
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h> // Для использования с OpenGL
#include <stdio.h>
#include <math.h>

#include "circle.h"
#include "line.h"
#include "objectController.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define ARRAY_SIZE 5

Object* array[ARRAY_SIZE] = {NULL, NULL, NULL, NULL, NULL};
int counter = 0;

int drawing = 0;

double mouseX, mouseY;

int updateCounter(int counter) {
	counter++;
	counter = counter % ARRAY_SIZE;
	return counter;
}

void errorCallback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void pressCallback() {
	fprintf(stdout, "Click!");
}

// int is_inside_circle(float x, float y, float rx, float ry, float radius) {
// 	return pow(x-rx, 2) + pow(y-ry, 2) < pow(radius, 2);
// }

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		int windowHight;
		glfwGetWindowSize(window, NULL, &windowHight);
		
		// mouseY = windowHight - mouseY;

		// ТУТ НУЖЕН ДЕСТРОЙ ОБЪЕКТОВ
		array[counter] = createCircleObject(createCircle(
			mouseX, mouseY, 50.0f, nvgRGBA(100, 200, 100, 200)
		));

		counter = updateCounter(counter);
        // if (is_inside_circle(mouseX, mouseY, 100, 100, 100)) {
		// 	printf("click on circle\n");
		// } else {
		// 	printf("%f - %f\n", mouseX, mouseY);
		// }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

        array[counter] = createLineObject(createLine(
			mouseX, mouseY, mouseX, mouseY, 2, nvgRGBA(100, 200, 100, 200)
		));
        counter = updateCounter(counter);
        drawing = 1;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        void* obj = array[(counter - 1 + ARRAY_SIZE) % ARRAY_SIZE]->object;
        Line* l = (Line*)obj;
        dropLineState(l);
        // printf((Line*)(array[(counter - 1 + ARRAY_SIZE) % ARRAY_SIZE]->object));
        drawing = 0;
    }   
}



// void setTransparent(GLFWwindow* window) {
//     // Получение HWND окна
//     HWND hwnd = glfwGetWin32Window(window);
//     if (!hwnd) {
//         fprintf(stderr, "Failed to get HWND from GLFW window\n");
//         return;
//     }

//     // Установка стиля окна
//     LONG style = GetWindowLong(hwnd, GWL_EXSTYLE);
//     SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_LAYERED);

//     // Установка прозрачности
//     SetLayeredWindowAttributes(hwnd, 0, 128, LWA_ALPHA); // 128 — уровень прозрачности (0-255)
// }

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwSetErrorCallback(errorCallback);

    // Установка параметров окна GLFW
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NanoVG Example", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
	// glfwSetWindowOpacity(window, 0.5f);


	if (!glfwGetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER)) {
		printf("window not transparent");
	}	

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Инициализация GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Инициализация NanoVG
    NVGcontext *vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    if (!vg) {
        fprintf(stderr, "Could not initialize NanoVG\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

	glfwSetMouseButtonCallback(window, mouse_button_callback);

    // setTransparent(window);
	// // Завел стурктуру круга
	// Circle circle = {100.0f, 200.0f, 100.0f, nvgRGBA(100, 200, 100, 255)};
	// Object array[1];

	// array[0].object = (void*) &circle;
	// array[0].objectType = CIRCLE;

    while (!glfwWindowShouldClose(window)) {
        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float pxRatio;
        
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Получение размеров окна и соотношения пикселей
        glfwGetWindowSize(window, &winWidth, &winHeight);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;

        // Очистка буфера
        glViewport(0, 0, fbWidth, fbHeight);
        // glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Альфа-значение 0 для прозрачного фона
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Рисование с использованием NanoVG
        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        // Рисуем круг
        // nvgBeginPath(vg);
        // nvgCircle(vg, winWidth / 2, winHeight / 2, 100);
        // nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
        // nvgFill(vg);

		// drawWrapper(vg, &circle);
		// objectDraw(vg, &array[0]);

		for (int i = 0; i < ARRAY_SIZE; i++) {
			if (array[i]) {
				objectDraw(vg, array[i]);
			}
		}

        // double mouseX, mouseY;
		// glfwGetCursorPos(window, &mouseX, &mouseY);
        // nvgBeginPath(vg);
        // nvgMoveTo(vg, 100, 100);
        // nvgLineTo(vg, mouseX, mouseY);
        // nvgStrokeColor(vg, nvgRGBA(150, 100, 100, 255));
        // nvgStrokeWidth(vg, 1);
        // nvgStroke(vg);
        // nvgClosePath(vg);



        nvgEndFrame(vg);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Очистка ресурсов
    nvgDeleteGL3(vg);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
