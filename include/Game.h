#ifndef HIGHWAY_RUSH_GAME_H
#define HIGHWAY_RUSH_GAME_H

#include <random>
#include <vector>

#include "Player.h"
#include "Renderer.h"
#include "Road.h"
#include "TrafficCar.h"

class Game {
public:
    Game();

    void resize(int framebufferWidth, int framebufferHeight);
    void update(float deltaTime, int steering, bool accelerating, bool braking);
    void render() const;
    bool hasCrashed() const;
    void restart();

private:
    Renderer renderer;
    Road road;
    Player player;
    std::vector<TrafficCar> traffic;
    std::mt19937 randomEngine{std::random_device{}()};
    float spawnDistance = 0.0f;
    bool crashed = false;

    void updateTraffic(float deltaTime);
};

#endif

