#ifndef HIGHWAY_RUSH_PLAYER_H
#define HIGHWAY_RUSH_PLAYER_H

class Player {
public:
    Player(float startX, float startY);
    void update(float deltaTime, int steering, bool accelerating, bool braking);
    float forwardSpeed() const;
    bool overlaps(float centerX, float centerY, float halfWidth,
                  float halfHeight) const;
    void draw() const;

private:
    static constexpr float WIDTH = 92.0f;
    static constexpr float HEIGHT = 170.0f;
    static constexpr float WHEEL_OVERHANG = 6.0f;
    static constexpr float HALF_WIDTH = WIDTH / 2.0f + WHEEL_OVERHANG;

    float x;
    float y;
    float speed = 0.0f;
    float steeringSpeed = 0.0f;

    void drawWheels() const;
    void drawBody() const;
    void drawWindows() const;
    void drawLights() const;
};

#endif

