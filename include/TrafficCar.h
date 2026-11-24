#ifndef HIGHWAY_RUSH_TRAFFIC_CAR_H
#define HIGHWAY_RUSH_TRAFFIC_CAR_H

struct TrafficCar {
    static constexpr float HALF_WIDTH = 42.0f;
    static constexpr float HALF_HEIGHT = 74.0f;

    float x;
    float y;

    void draw() const;
};

#endif
