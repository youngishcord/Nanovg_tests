
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h> // Для использования с OpenGL
#include <stdio.h>
#include <math.h>

#include "circle.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		int windowHight;
		glfwGetWindowSize(window, NULL, &windowHight);
		mouseY = windowHight - mouseY;

        if (is_inside_circle(mouseX, mouseY, 100, 100, 100)) {
			printf("click on circle\n");
		} else {
			printf("%f - %f\n", mouseX, mouseY);
		}
    }
}
int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwSetErrorCallback(errorCallback);

    // Установка параметров окна GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "NanoVG Example", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
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


	// Завел стурктуру круга
	Circle circle = {100.0f, 100.0f, 100.0f, nvgRGBA(100, 100, 100, 255)};

    while (!glfwWindowShouldClose(window)) {
        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float pxRatio;

        // Получение размеров окна и соотношения пикселей
        glfwGetWindowSize(window, &winWidth, &winHeight);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;

        // Очистка буфера
        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Рисование с использованием NanoVG
        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        // Рисуем круг
        // nvgBeginPath(vg);
        // nvgCircle(vg, winWidth / 2, winHeight / 2, 100);
        // nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
        // nvgFill(vg);
		drawWrapper(vg, &circle);


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
