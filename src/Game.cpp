#include "Game.h"

Game::Game()
    : player(Renderer::WORLD_WIDTH / 2.0f, 115.0f) {
}

void Game::resize(int framebufferWidth, int framebufferHeight) {
    renderer.setViewport(framebufferWidth, framebufferHeight);
}

void Game::render() const {
    renderer.drawScene(road, player);
}

