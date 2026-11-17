#include "Player.h"

#include <GLFW/glfw3.h>

#include "Renderer.h"

Player::Player(float startX, float startY)
    : x(startX), y(startY), width(92.0f), height(170.0f) {
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

    Renderer::drawRectangle(-width / 2.0f - 6.0f, -height / 2.0f + 22.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(width / 2.0f - 7.0f, -height / 2.0f + 22.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(-width / 2.0f - 6.0f, height / 2.0f - 61.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
    Renderer::drawRectangle(width / 2.0f - 7.0f, height / 2.0f - 61.0f,
                            WHEEL_WIDTH, WHEEL_HEIGHT, 0.03f, 0.03f, 0.04f);
}

void Player::drawBody() const {
    // The body is a polygon so its front and rear can taper like a real car.
    glColor3f(0.08f, 0.42f, 0.88f);
    glBegin(GL_POLYGON);
    glVertex2f(-width * 0.36f, -height / 2.0f);
    glVertex2f(width * 0.36f, -height / 2.0f);
    glVertex2f(width / 2.0f, -height * 0.30f);
    glVertex2f(width / 2.0f, height * 0.28f);
    glVertex2f(width * 0.32f, height / 2.0f);
    glVertex2f(-width * 0.32f, height / 2.0f);
    glVertex2f(-width / 2.0f, height * 0.28f);
    glVertex2f(-width / 2.0f, -height * 0.30f);
    glEnd();

    Renderer::drawRectangle(-width * 0.34f, -10.0f, width * 0.68f, 8.0f,
                            0.04f, 0.25f, 0.62f);
}

void Player::drawWindows() const {
    // The windshield is wider at the front, so a quadrilateral is suitable.
    glColor3f(0.20f, 0.58f, 0.72f);
    glBegin(GL_QUADS);
    glVertex2f(-width * 0.32f, 15.0f);
    glVertex2f(width * 0.32f, 15.0f);
    glVertex2f(width * 0.24f, 57.0f);
    glVertex2f(-width * 0.24f, 57.0f);
    glEnd();

    glColor3f(0.15f, 0.45f, 0.62f);
    glBegin(GL_QUADS);
    glVertex2f(-width * 0.30f, -45.0f);
    glVertex2f(width * 0.30f, -45.0f);
    glVertex2f(width * 0.33f, -14.0f);
    glVertex2f(-width * 0.33f, -14.0f);
    glEnd();
}

void Player::drawLights() const {
    // The front of the car points toward the top of the screen.
    Renderer::drawRectangle(-width * 0.31f, height / 2.0f - 12.0f,
                            18.0f, 9.0f, 1.0f, 0.95f, 0.55f);
    Renderer::drawRectangle(width * 0.31f - 18.0f, height / 2.0f - 12.0f,
                            18.0f, 9.0f, 1.0f, 0.95f, 0.55f);
    Renderer::drawRectangle(-width * 0.31f, -height / 2.0f + 3.0f,
                            17.0f, 9.0f, 0.90f, 0.08f, 0.08f);
    Renderer::drawRectangle(width * 0.31f - 17.0f, -height / 2.0f + 3.0f,
                            17.0f, 9.0f, 0.90f, 0.08f, 0.08f);
}

