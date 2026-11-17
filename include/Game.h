#ifndef HIGHWAY_RUSH_GAME_H
#define HIGHWAY_RUSH_GAME_H

#include "Player.h"
#include "Renderer.h"
#include "Road.h"

class Game {
public:
    Game();

    void resize(int framebufferWidth, int framebufferHeight);
    void render() const;

private:
    Renderer renderer;
    Road road;
    Player player;
};

#endif

