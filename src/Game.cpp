#include "Game.h"

#include <algorithm>

namespace {
constexpr int START_LANE = 1;
constexpr float START_Y = 115.0f;
}

Game::Game()
    : player(Road::laneCenter(START_LANE), START_Y) {
}

void Game::resize(int framebufferWidth, int framebufferHeight) {
    renderer.setViewport(framebufferWidth, framebufferHeight);
}

void Game::render() const {
    renderer.drawScene(road, player, traffic);
}

void Game::update(float deltaTime, int steering, bool accelerating, bool braking) {
    if (crashed) {
        return;
    }

    player.update(deltaTime, steering, accelerating, braking);
    road.update(player.forwardSpeed() * deltaTime);
    updateTraffic(deltaTime);

    for (const TrafficCar& car : traffic) {
        if (player.overlaps(car.x, car.y, TrafficCar::HALF_WIDTH,
                            TrafficCar::HALF_HEIGHT)) {
            crashed = true;
            return;
        }
    }
}

void Game::updateTraffic(float deltaTime) {
    constexpr float TRAFFIC_SPEED = 150.0f;
    constexpr float SPAWN_SPACING = 520.0f;
    constexpr float SPAWN_Y = Renderer::WORLD_HEIGHT + TrafficCar::HALF_HEIGHT;

    // Traffic moves down the screen when the player is catching up to it.
    const float closingDistance = (player.forwardSpeed() - TRAFFIC_SPEED) * deltaTime;
    for (TrafficCar& car : traffic) {
        car.y -= closingDistance;
    }

    traffic.erase(std::remove_if(traffic.begin(), traffic.end(),
                                 [](const TrafficCar& car) {
                                     return car.y <= -TrafficCar::HALF_HEIGHT ||
                                            car.y > SPAWN_Y;
                                 }),
                  traffic.end());

    // Count relative travel so same-lane cars stay spaced even during braking.
    spawnDistance = std::max(0.0f, spawnDistance + closingDistance);
    if (spawnDistance >= SPAWN_SPACING) {
        std::uniform_int_distribution<int> chooseLane(0, Road::LANE_COUNT - 1);
        const int lane = chooseLane(randomEngine);
        spawnDistance -= SPAWN_SPACING;
        traffic.push_back({Road::laneCenter(lane), SPAWN_Y - spawnDistance});
    }
}

bool Game::hasCrashed() const {
    return crashed;
}

void Game::restart() {
    road = Road{};
    player = Player{Road::laneCenter(START_LANE), START_Y};
    traffic.clear();
    spawnDistance = 0.0f;
    crashed = false;
}

