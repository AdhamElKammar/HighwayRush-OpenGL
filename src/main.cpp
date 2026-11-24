#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Game.h"

namespace {
void reportGlfwError(int errorCode, const char* description) {
    std::cerr << "GLFW error " << errorCode << ": " << description << '\n';
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game != nullptr) {
        game->resize(width, height);
    }
}

bool isPressed(GLFWwindow* window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}
} // namespace

int main() {
    glfwSetErrorCallback(reportGlfwError);

    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Could not initialize GLFW.\n";
        return EXIT_FAILURE;
    }

    // OpenGL 2.1 provides a compatibility context for immediate-mode drawing.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(
        Renderer::WORLD_WIDTH,
        Renderer::WORLD_HEIGHT,
        "Highway Rush",
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        std::cerr << "Could not create the game window.\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Synchronize drawing with the monitor to reduce tearing.

    Game game;
    glfwSetWindowUserPointer(window, &game);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    game.resize(framebufferWidth, framebufferHeight);

    double previousTime = glfwGetTime();
    while (glfwWindowShouldClose(window) == GLFW_FALSE) {
        glfwPollEvents();
        if (glfwWindowShouldClose(window) == GLFW_TRUE ||
            isPressed(window, GLFW_KEY_ESCAPE)) {
            break;
        }

        const double currentTime = glfwGetTime();
        // Limit movement in one update after a pause or a slow frame.
        const float deltaTime = static_cast<float>(
            std::min(currentTime - previousTime, 0.05));
        previousTime = currentTime;

        if (game.hasCrashed()) {
            if (isPressed(window, GLFW_KEY_R)) {
                game.restart();
                glfwSetWindowTitle(window, "Highway Rush");
            }
        } else {
            const bool left = isPressed(window, GLFW_KEY_LEFT) ||
                              isPressed(window, GLFW_KEY_A);
            const bool right = isPressed(window, GLFW_KEY_RIGHT) ||
                               isPressed(window, GLFW_KEY_D);
            const bool accelerate = isPressed(window, GLFW_KEY_UP) ||
                                    isPressed(window, GLFW_KEY_W);
            const bool brake = isPressed(window, GLFW_KEY_DOWN) ||
                               isPressed(window, GLFW_KEY_S);
            game.update(deltaTime, right - left, accelerate, brake);
            if (game.hasCrashed()) {
                glfwSetWindowTitle(window, "Highway Rush | Crashed - press R to restart");
            }
        }
        game.render();

        // Show the completed back buffer.
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

