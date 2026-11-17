#ifndef HIGHWAY_RUSH_RENDERER_H
#define HIGHWAY_RUSH_RENDERER_H

class Road;
class Player;

class Renderer {
public:
    static constexpr int WORLD_WIDTH = 1280;
    static constexpr int WORLD_HEIGHT = 720;

    void setViewport(int framebufferWidth, int framebufferHeight) const;
    void drawScene(const Road& road, const Player& player) const;

    static void drawRectangle(float left, float bottom, float width,
                              float height, float red, float green, float blue);
    static void drawCircle(float centerX, float centerY, float radius,
                           float red, float green, float blue,
                           int numberOfSides = 32);
};

#endif

