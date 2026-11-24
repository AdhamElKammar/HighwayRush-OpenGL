#include "TrafficCar.h"

#include "Renderer.h"

void TrafficCar::draw() const {
    Renderer::drawRectangle(x - HALF_WIDTH, y - HALF_HEIGHT,
                            2.0f * HALF_WIDTH, 2.0f * HALF_HEIGHT,
                            0.76f, 0.22f, 0.10f);
    Renderer::drawRectangle(x - 31.0f, y + 18.0f, 62.0f, 27.0f,
                            0.23f, 0.35f, 0.40f);
    Renderer::drawRectangle(x - 31.0f, y - 42.0f, 62.0f, 19.0f,
                            0.19f, 0.28f, 0.33f);
    Renderer::drawRectangle(x - 34.0f, y - HALF_HEIGHT + 5.0f,
                            15.0f, 8.0f, 1.0f, 0.34f, 0.22f);
    Renderer::drawRectangle(x + 19.0f, y - HALF_HEIGHT + 5.0f,
                            15.0f, 8.0f, 1.0f, 0.34f, 0.22f);
}
