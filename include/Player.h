#ifndef HIGHWAY_RUSH_PLAYER_H
#define HIGHWAY_RUSH_PLAYER_H

class Player {
public:
    Player(float startX, float startY);
    void draw() const;

private:
    float x;
    float y;
    float width;
    float height;

    void drawWheels() const;
    void drawBody() const;
    void drawWindows() const;
    void drawLights() const;
};

#endif

