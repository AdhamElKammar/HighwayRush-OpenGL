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

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
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

    while (glfwWindowShouldClose(window) == GLFW_FALSE) {
        processInput(window);
        game.render();

        // Show the completed back buffer, then collect window and key events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

