#include "Road.h"

#include <GLFW/glfw3.h>

#include "Renderer.h"

namespace {
constexpr float ROAD_LEFT = 220.0f;
constexpr float ROAD_WIDTH = 840.0f;
constexpr float LANE_WIDTH = ROAD_WIDTH / 3.0f;
}

void Road::draw() const {
    drawRoadsideScenery();
    drawRoadSurface();
    drawLaneMarkings();
}

void Road::drawRoadsideScenery() const {
    Renderer::drawRectangle(0.0f, 0.0f, ROAD_LEFT, Renderer::WORLD_HEIGHT,
                            0.08f, 0.25f, 0.15f);
    Renderer::drawRectangle(ROAD_LEFT + ROAD_WIDTH, 0.0f, ROAD_LEFT,
                            Renderer::WORLD_HEIGHT, 0.08f, 0.25f, 0.15f);

    // Repeated shrubs make the roadside less empty while using simple circles.
    for (int y = 55; y < Renderer::WORLD_HEIGHT; y += 135) {
        Renderer::drawCircle(95.0f, static_cast<float>(y), 30.0f,
                             0.10f, 0.40f, 0.20f);
        Renderer::drawCircle(1175.0f, static_cast<float>(y + 55), 28.0f,
                             0.10f, 0.40f, 0.20f);
    }
}

void Road::drawRoadSurface() const {
    // Pale shoulders and white edge lines clearly separate road from grass.
    Renderer::drawRectangle(ROAD_LEFT - 14.0f, 0.0f, ROAD_WIDTH + 28.0f,
                            Renderer::WORLD_HEIGHT, 0.65f, 0.65f, 0.61f);
    Renderer::drawRectangle(ROAD_LEFT, 0.0f, ROAD_WIDTH,
                            Renderer::WORLD_HEIGHT, 0.16f, 0.18f, 0.20f);
    Renderer::drawRectangle(ROAD_LEFT + 8.0f, 0.0f, 6.0f,
                            Renderer::WORLD_HEIGHT, 0.95f, 0.95f, 0.90f);
    Renderer::drawRectangle(ROAD_LEFT + ROAD_WIDTH - 14.0f, 0.0f, 6.0f,
                            Renderer::WORLD_HEIGHT, 0.95f, 0.95f, 0.90f);
}

void Road::drawLaneMarkings() const {
    constexpr float DASH_WIDTH = 8.0f;
    constexpr float DASH_HEIGHT = 72.0f;
    constexpr float DASH_GAP = 48.0f;

    for (int divider = 1; divider <= 2; ++divider) {
        const float dividerX = ROAD_LEFT + LANE_WIDTH * divider;

        for (float y = -24.0f; y < Renderer::WORLD_HEIGHT;
             y += DASH_HEIGHT + DASH_GAP) {
            Renderer::drawRectangle(dividerX - DASH_WIDTH / 2.0f, y,
                                    DASH_WIDTH, DASH_HEIGHT,
                                    0.95f, 0.82f, 0.18f);
        }
    }
}

