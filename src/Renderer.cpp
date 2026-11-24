#include "Renderer.h"

#include <cmath>

#include <GLFW/glfw3.h>

#include "Player.h"
#include "Road.h"
#include "TrafficCar.h"

void Renderer::setViewport(int framebufferWidth, int framebufferHeight) const {
    if (framebufferWidth <= 0 || framebufferHeight <= 0) {
        return;
    }

    // Letterboxing preserves the 16:9 world instead of stretching the cars.
    const float worldAspect = static_cast<float>(WORLD_WIDTH) / WORLD_HEIGHT;
    const float windowAspect = static_cast<float>(framebufferWidth) /
                               framebufferHeight;

    int viewportWidth = framebufferWidth;
    int viewportHeight = framebufferHeight;
    int viewportX = 0;
    int viewportY = 0;

    if (windowAspect > worldAspect) {
        viewportWidth = static_cast<int>(framebufferHeight * worldAspect);
        viewportX = (framebufferWidth - viewportWidth) / 2;
    } else {
        viewportHeight = static_cast<int>(framebufferWidth / worldAspect);
        viewportY = (framebufferHeight - viewportHeight) / 2;
    }

    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // World coordinates match the original window size. (0, 0) is bottom-left.
    glOrtho(0.0, WORLD_WIDTH, 0.0, WORLD_HEIGHT, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::drawScene(const Road& road, const Player& player,
                         const std::vector<TrafficCar>& traffic) const {
    glClearColor(0.04f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    road.draw();
    for (const TrafficCar& car : traffic) {
        car.draw();
    }
    player.draw();
}

void Renderer::drawRectangle(float left, float bottom, float width,
                             float height, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(left, bottom);
    glVertex2f(left + width, bottom);
    glVertex2f(left + width, bottom + height);
    glVertex2f(left, bottom + height);
    glEnd();
}

void Renderer::drawCircle(float centerX, float centerY, float radius,
                          float red, float green, float blue,
                          int numberOfSides) {
    constexpr float PI = 3.1415926535f;

    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);

    for (int side = 0; side <= numberOfSides; ++side) {
        const float angle = 2.0f * PI * side / numberOfSides;
        glVertex2f(centerX + std::cos(angle) * radius,
                   centerY + std::sin(angle) * radius);
    }

    glEnd();
}

