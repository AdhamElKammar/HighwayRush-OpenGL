#ifndef HIGHWAY_RUSH_ROAD_H
#define HIGHWAY_RUSH_ROAD_H

class Road {
public:
    static constexpr int LANE_COUNT = 3;
    static constexpr float LEFT_EDGE = 220.0f;
    static constexpr float RIGHT_EDGE = 1060.0f;

    static float laneCenter(int lane);

    void update(float distance);
    void draw() const;

private:
    float markingOffset = 0.0f;

    void drawRoadSurface() const;
    void drawLaneMarkings() const;
    void drawRoadsideScenery() const;
};

#endif

