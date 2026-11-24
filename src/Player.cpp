#include "Player.h"

#include <algorithm>
#include <cmath>

#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Road.h"

Player::Player(float startX, float startY)
    : x(startX), y(startY) {
}

void Player::update(float deltaTime, int steering, bool accelerating,
                    bool braking) {
    constexpr float MAX_SPEED = 620.0f;
    constexpr float ACCELERATION = 320.0f;
    constexpr float BRAKING = 640.0f;
    constexpr float COASTING = 75.0f;
    constexpr float MAX_STEERING_SPEED = 360.0f;
    constexpr float STEERING_ACCELERATION = 1800.0f;

    float speedChange = -COASTING;
    if (braking) {
        speedChange = -BRAKING;
    } else if (accelerating) {
        speedChange = ACCELERATION;
    }
    speed = std::clamp(speed + speedChange * deltaTime, 0.0f, MAX_SPEED);

    const float targetSpeed = steering * MAX_STEERING_SPEED;
    const float steeringChange = STEERING_ACCELERATION * deltaTime;
    steeringSpeed += std::clamp(targetSpeed - steeringSpeed,
                                -steeringChange, steeringChange);

    // Include the wheels when keeping the whole car on the asphalt.
    const float nextX = x + steeringSpeed * deltaTime;
    x = std::clamp(nextX, Road::LEFT_EDGE + HALF_WIDTH,
                   Road::RIGHT_EDGE - HALF_WIDTH);
    if (x != nextX) {
        steeringSpeed = 0.0f;
    }
}

float Player::forwardSpeed() const {
    return speed;
}

bool Player::overlaps(float centerX, float centerY, float halfWidth,
                      float halfHeight) const {
    // The bounding boxes overlap when their projections overlap on both axes.
    return std::abs(x - centerX) < HALF_WIDTH + halfWidth &&
           std::abs(y - centerY) < HEIGHT / 2.0f + halfHeight;
}

void Player::draw() const {
    // Translation places the car using its center without changing every vertex.
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    drawWheels();
    drawBody();
    drawWindows();
    drawLights();

    glPopMatrix();
}

void Player::drawWheels() const {
    constexpr float WHEEL_WIDTH = 13.0f;
    constexpr float WHEEL_HEIGHT = 39.0f;
    constexpr float LEFT_WHEEL = -HALF_WIDTH;
    constexpr float RIGHT_WHEEL = HALF_WIDTH - WHEEL_WIDTH;

    Renderer::drawRectangle(LEFT_WHEEL, -HEIGHT / 2.0f + 22.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(RIGHT_WHEEL, -HEIGHT / 2.0f + 22.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(LEFT_WHEEL, HEIGHT / 2.0f - 61.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(RIGHT_WHEEL, HEIGHT / 2.0f - 61.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
}

void Player::drawBody() const {
    // The body is a polygon so its front and rear can taper like a real car.
    glColor3f(0.08f, 0.42f, 0.88f);
    glBegin(GL_POLYGON);
    glVertex2f(-WIDTH * 0.36f, -HEIGHT / 2.0f);
    glVertex2f(WIDTH * 0.36f, -HEIGHT / 2.0f);
    glVertex2f(WIDTH / 2.0f, -HEIGHT * 0.30f);
    glVertex2f(WIDTH / 2.0f, HEIGHT * 0.28f);
    glVertex2f(WIDTH * 0.32f, HEIGHT / 2.0f);
    glVertex2f(-WIDTH * 0.32f, HEIGHT / 2.0f);
    glVertex2f(-WIDTH / 2.0f, HEIGHT * 0.28f);
    glVertex2f(-WIDTH / 2.0f, -HEIGHT * 0.30f);
    glEnd();

    Renderer::drawRectangle(-WIDTH * 0.34f, -10.0f, WIDTH * 0.68f, 8.0f,
                            0.04f, 0.25f, 0.62f);
}

void Player::drawWindows() const {
    // The windshield is wider at the front, so a quadrilateral is suitable.
    glColor3f(0.20f, 0.58f, 0.72f);
    glBegin(GL_QUADS);
    glVertex2f(-WIDTH * 0.32f, 15.0f);
    glVertex2f(WIDTH * 0.32f, 15.0f);
    glVertex2f(WIDTH * 0.24f, 57.0f);
    glVertex2f(-WIDTH * 0.24f, 57.0f);
    glEnd();

    glColor3f(0.15f, 0.45f, 0.62f);
    glBegin(GL_QUADS);
    glVertex2f(-WIDTH * 0.30f, -45.0f);
    glVertex2f(WIDTH * 0.30f, -45.0f);
    glVertex2f(WIDTH * 0.33f, -14.0f);
    glVertex2f(-WIDTH * 0.33f, -14.0f);
    glEnd();
}

void Player::drawLights() const {
    // The front of the car points toward the top of the screen.
    Renderer::drawRectangle(-WIDTH * 0.31f, HEIGHT / 2.0f - 12.0f,
                            18.0f, 9.0f, 1.0f, 0.95f, 0.55f);
    Renderer::drawRectangle(WIDTH * 0.31f - 18.0f, HEIGHT / 2.0f - 12.0f,
                            18.0f, 9.0f, 1.0f, 0.95f, 0.55f);
    Renderer::drawRectangle(-WIDTH * 0.31f, -HEIGHT / 2.0f + 3.0f,
                            17.0f, 9.0f, 0.90f, 0.08f, 0.08f);
    Renderer::drawRectangle(WIDTH * 0.31f - 17.0f, -HEIGHT / 2.0f + 3.0f,
                            17.0f, 9.0f, 0.90f, 0.08f, 0.08f);
}

