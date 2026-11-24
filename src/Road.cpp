#include "Road.h"

#include "Renderer.h"

namespace {
constexpr float ROAD_WIDTH = Road::RIGHT_EDGE - Road::LEFT_EDGE;
constexpr float LANE_WIDTH = ROAD_WIDTH / Road::LANE_COUNT;
constexpr float DASH_HEIGHT = 72.0f;
constexpr float DASH_GAP = 48.0f;
constexpr float DASH_SPACING = DASH_HEIGHT + DASH_GAP;
}

float Road::laneCenter(int lane) {
    return LEFT_EDGE + LANE_WIDTH * (lane + 0.5f);
}

void Road::update(float distance) {
    markingOffset -= distance;
    // Moving a full dash spacing produces the same pattern.
    while (markingOffset <= -DASH_SPACING) {
        markingOffset += DASH_SPACING;
    }
}

void Road::draw() const {
    drawRoadsideScenery();
    drawRoadSurface();
    drawLaneMarkings();
}

void Road::drawRoadsideScenery() const {
    Renderer::drawRectangle(0.0f, 0.0f, LEFT_EDGE, Renderer::WORLD_HEIGHT,
                            0.08f, 0.25f, 0.15f);
    Renderer::drawRectangle(RIGHT_EDGE, 0.0f, Renderer::WORLD_WIDTH - RIGHT_EDGE,
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
    Renderer::drawRectangle(LEFT_EDGE - 14.0f, 0.0f, ROAD_WIDTH + 28.0f,
                            Renderer::WORLD_HEIGHT, 0.65f, 0.65f, 0.61f);
    Renderer::drawRectangle(LEFT_EDGE, 0.0f, ROAD_WIDTH,
                            Renderer::WORLD_HEIGHT, 0.16f, 0.18f, 0.20f);
    Renderer::drawRectangle(LEFT_EDGE + 8.0f, 0.0f, 6.0f,
                            Renderer::WORLD_HEIGHT, 0.95f, 0.95f, 0.90f);
    Renderer::drawRectangle(RIGHT_EDGE - 14.0f, 0.0f, 6.0f,
                            Renderer::WORLD_HEIGHT, 0.95f, 0.95f, 0.90f);
}

void Road::drawLaneMarkings() const {
    constexpr float DASH_WIDTH = 8.0f;

    for (int divider = 1; divider < LANE_COUNT; ++divider) {
        const float dividerX = LEFT_EDGE + LANE_WIDTH * divider;

        for (float y = markingOffset - 24.0f;
             y < Renderer::WORLD_HEIGHT; y += DASH_SPACING) {
            Renderer::drawRectangle(dividerX - DASH_WIDTH / 2.0f, y,
                                    DASH_WIDTH, DASH_HEIGHT,
                                    0.95f, 0.82f, 0.18f);
        }
    }
}

